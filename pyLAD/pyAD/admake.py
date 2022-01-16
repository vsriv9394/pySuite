import os, inspect
from subprocess import call
def mycall(cmd): call(cmd, shell=True)

from numpy.lib.arraysetops import isin
from .adClasses import *
from .writeFunctions import *
    
def generateInput(content):
    if len(content)==0: return Scalar()
    else: return [generateInput(content[1:]) for _ in range(content[0])]

def generateShape(A):
    if not isinstance(A, list): return []
    else:
        rtn = [len(A)]
        rtn.extend(generateShape(A[0]))
        return rtn

def setAsOutput(A):
    if not isinstance(A, list): return Scalar(A).asOutput()
    else: return [setAsOutput(a) for a in A]

def compileBranch(maxLen, func, inputs_AD, inputs):
    outputs, outputs_AD = func(inputs_AD=inputs_AD, inputs=inputs)
    for name, content in outputs_AD.items(): outputs_AD[name] = setAsOutput(content)
    newLen = len(GraphEntity.graph.nodeList)
    GraphEntity.graph.forwardBuffer.write('getOutputs(self, %d);' % (newLen))
    GraphEntity.graph.forwardBuffer.write('#ifndef DISABLE_DERIVS')
    GraphEntity.graph.forwardBuffer.write('updateDerivs(self, %d);' % (newLen))
    GraphEntity.graph.forwardBuffer.write('#endif')
    GraphEntity.graph.rollBackToLastTrueBranchAndSwitchIt()
    maxLen += newLen-maxLen if newLen>maxLen else 0
    return maxLen, outputs, outputs_AD

def admake(func, disableDerivs=False):

    GraphEntity.graph = Graph()
    
    functionName = 'ADF_' + func.__name__
    dirName      = os.path.join(os.getcwd(), functionName)
    argspec      = inspect.getfullargspec(func)
    inShapes     = argspec.defaults
    outShapes    = [{}, {}]
    maxLen       = 0

    inputs_AD = {}
    for name, content in inShapes[0].items():
        inputs_AD[name] = generateInput(content)
    
    inputs = {}
    for name, content in inShapes[1].items():
        inputs[name] = generateInput(content)
    
    maxLen, outputs, outputs_AD = compileBranch(maxLen, func, inputs_AD, inputs)
    while len(GraphEntity.graph.knownConditionals)>0:
        maxLen, outputs, outputs_AD = compileBranch(maxLen, func, inputs_AD, inputs)

    for name, content in outputs.items():
        outShapes[0][name] = generateShape(content)
    
    for name, content in outputs_AD.items():
        outShapes[1][name] = generateShape(content)

    vars = {
        'inputs_AD'  : inShapes[0],
        'inputs'     : inShapes[1],
        'outputs'    : outShapes[0],
        'outputs_AD' : outShapes[1],
    }

    mycall('mkdir -p %s/src' % (dirName))
    
    calculateBuffer = FormattedBuffer()
    GraphEntity.graph.reverseBuffer.lines.reverse()
    writeCalculateFile(
        calculateBuffer, functionName, vars,
        GraphEntity.graph.forwardBuffer,
        GraphEntity.graph.reverseBuffer
    )
    with open(dirName+'/src/calculate.c', 'w') as f:
        f.write(calculateBuffer.getContents())
    
    structBuffer = FormattedBuffer()
    writeStructFile(
        structBuffer, functionName,
        inShapes[0],  inShapes[1],
        outShapes[0], outShapes[1], maxLen
    )
    with open(dirName+'/'+functionName+'.h', 'w') as f:
        f.write(structBuffer.getContents())
    
    writeOtherFiles(dirName, functionName, vars)

    os.chdir(functionName)
    if disableDerivs:
        with open('makefile.py','w') as f:
            f.write('options = { "defs" : "-DDISABLE_DERIVS" }')
    mycall('pymake > pymake_log.txt')
    os.chdir('..')
