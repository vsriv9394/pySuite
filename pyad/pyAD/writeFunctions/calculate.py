import os
import numpy as np
from ..adClasses import FormattedBuffer

defDir = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))

def writeCalculateFile(buffer: FormattedBuffer, functionName, vars, forwardBuffer, reverseBuffer):
    buffer.write('#include "../'+functionName+'.h"')
    buffer.write('#include "'+defDir+'/headers/defineOps.h"')
    buffer.write('')
    buffer.write('static void calculateDerivatives('+functionName+' *self);')
    buffer.write('static void updateDerivs('+functionName+' *self, VarAD *output);')
    buffer.write('static void updateAllDerivs('+functionName+' *self, int size);')
    buffer.write('static void setInputs('+functionName+' *self);')
    buffer.write('static void getOutputs('+functionName+' *self, int size);')
    calculate(buffer, functionName, forwardBuffer, list(vars['outputs_AD'].keys())[0])
    calculateDerivatives(buffer, functionName, reverseBuffer)
    updateDerivs(buffer, functionName, vars['inputs_AD'])
    updateAllDerivs(buffer, functionName, vars['outputs_AD'])
    setInputs(buffer, functionName, vars['inputs_AD'], vars['inputs'])
    getOutputs(buffer, functionName, vars['outputs'], vars['outputs_AD'])

def calculate(buffer: FormattedBuffer, functionName, forwardBuffer: FormattedBuffer, first_output_AD):
    buffer.write('')
    buffer.write('void calculate__'+functionName)
    buffer.write('(')
    buffer.write('\tvoid *_self')
    buffer.write(')')
    buffer.openScope()
    buffer.write(functionName+' *self = _self;')
    #buffer.write('if(self->'+first_output_AD+'[0].nDeps==-1)')
    #buffer.openScope()
    #buffer.write('setup__'+functionName+'(_self);')
    #buffer.closeScope()
    buffer.write('double *___psi = self->___psi;')
    buffer.write('double *___phi = self->___phi;')
    buffer.write('setInputs(self);')
    buffer.lines.append(forwardBuffer.getContents(indent=buffer.indent))
    buffer.closeScope()

def calculateDerivatives(buffer: FormattedBuffer, functionName, reverseBuffer: FormattedBuffer):
    buffer.write('')
    buffer.write('static void calculateDerivatives('+functionName+' *self)')
    buffer.openScope()
    buffer.write('double *___psi = self->___psi;')
    buffer.write('double *___phi = self->___phi;')
    buffer.lines.append(reverseBuffer.getContents(indent=buffer.indent))
    buffer.closeScope()
    buffer.write('')
    buffer.write('#include "'+defDir+'/headers/undefOps.h"')
    buffer.write('')

def updateDerivs(buffer: FormattedBuffer, functionName, inputs_AD):
    buffer.write('static void updateDerivs('+functionName+' *self, VarAD *output)')
    buffer.openScope()
    buffer.write('int iInput = 0;')
    for shape in inputs_AD.values():
        buffer.write('for(int i=0; i<%d; i++)' % (int(np.prod(shape))) )
        buffer.openScope()
        buffer.write('output->depSens[iInput] = self->___psi[iInput]; iInput++;')
        buffer.closeScope()
    buffer.closeScope()
    buffer.write('')

def updateAllDerivs(buffer: FormattedBuffer, functionName, outputs_AD):
    buffer.write('static void updateAllDerivs('+functionName+' *self, int size)')
    buffer.openScope()
    buffer.write('int iOutput = size-1;')
    nameList = list(outputs_AD.keys())[::-1]
    shapeList = list(outputs_AD.values())[::-1]
    for name, shape in zip(nameList, shapeList):
        buffer.write('for(int j=%d; j>=0; j--)' % (int(np.prod(shape))-1) )
        buffer.openScope()
        buffer.write('for(int iVar=0; iVar<size; iVar++) self->___psi[iVar] = 0.0;')
        buffer.write('VarAD *output = self->'+name+'+j;')
        buffer.write('self->___psi[iOutput] = 1.0; iOutput--;')
        buffer.write('calculateDerivatives(self);')
        buffer.write('updateDerivs(self, output);')
        buffer.closeScope()
    buffer.closeScope()
    buffer.write('')

def setInputs(buffer: FormattedBuffer, functionName, inputs_AD, inputs):
    buffer.write('static void setInputs('+functionName+' *self)')
    buffer.openScope()
    buffer.write('int iInput = 0;')
    for name, shape in inputs_AD.items():
        buffer.write('for(int i=0; i<%d; i++)' % (int(np.prod(shape))) )
        buffer.openScope()
        buffer.write('self->___phi[iInput] = self->'+name+'[i].data; iInput++;')
        buffer.closeScope()
    for name, shape in inputs.items():
        buffer.write('for(int i=0; i<%d; i++)' % (int(np.prod(shape))) )
        buffer.openScope()
        buffer.write('self->___phi[iInput] = self->'+name+'[i]; iInput++;')
        buffer.closeScope()
    buffer.closeScope()
    buffer.write('')

def getOutputs(buffer: FormattedBuffer, functionName, outputs, outputs_AD):
    buffer.write('static void getOutputs('+functionName+' *self, int size)')
    buffer.openScope()
    buffer.write('int iOutput = size-1;')
    nameList = list(outputs_AD.keys())[::-1]
    shapeList = list(outputs_AD.values())[::-1]
    for name, shape in zip(nameList, shapeList):
        buffer.write('for(int i=%d; i>=0; i--)' % (int(np.prod(shape))-1) )
        buffer.openScope()
        buffer.write('self->'+name+'[i].data = self->___phi[iOutput]; iOutput--;')
        buffer.closeScope()
    nameList = list(outputs.keys())[::-1]
    shapeList = list(outputs.values())[::-1]
    for name, shape in zip(nameList, shapeList):
        buffer.write('for(int i=%d; i>=0; i--)' % (int(np.prod(shape))-1) )
        buffer.openScope()
        buffer.write('self->'+name+'[i] = self->___phi[iOutput]; iOutput--;')
        buffer.closeScope()
    buffer.closeScope()
    buffer.write('')