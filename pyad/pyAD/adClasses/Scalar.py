import numpy as np

from .GraphEntity import GraphEntity
from .ConditionalSwitch import ConditionalSwitch
from .Node import *

class Scalar(GraphEntity):

    def getScalar(self, node):
        return Scalar(id=getIdInGraph(node, self.graph))

    def asOutput(self):
        return self.getScalar(outputNode(self.id))

    def __init__(self, value=None, id=None):
        if id is None:
            if value is None: self.id = getIdInGraph(inputNode(), self.graph)
            elif isinstance(value, Scalar): self.id = value.id
            else: self.id = getIdInGraph(constantNode(value), self.graph)
        else: self.id = id
    
    def binary(self, other, operator):
        return self.getScalar(binaryNode(operator, self.id, Scalar(value=other).id))
    
    def rBinary(self, other, operator):
        return self.getScalar(binaryNode(operator, Scalar(value=other).id, self.id))
    
    def unary(self, operator):
        return self.getScalar(unaryNode(operator, self.id))

    def conditional(self, other, operator):
        self.graph.conditionalCount += 1
        if self.graph.conditionalCount > len(self.graph.knownConditionals):
            self.graph.knownConditionals.append(ConditionalSwitch(operator, self.id, Scalar(value=other).id))
            self.graph.knownConditionals[-1].initializeTrueBranch()
        return self.graph.knownConditionals[-1].value

    def     __add__(self, other): return self.binary(other, 'ADD')
    def     __sub__(self, other): return self.binary(other, 'SUB')
    def     __mul__(self, other): return self.binary(other, 'MUL')
    def     __div__(self, other): return self.binary(other, 'DIV')
    def     __pow__(self, other): return self.binary(other, 'POW')
    def __truediv__(self, other): return self.binary(other, 'DIV')

    def     __radd__(self, other): return self.rBinary(other, 'ADD')
    def     __rsub__(self, other): return self.rBinary(other, 'SUB')
    def     __rmul__(self, other): return self.rBinary(other, 'MUL')
    def     __rdiv__(self, other): return self.rBinary(other, 'DIV')
    def     __rpow__(self, other): return self.rBinary(other, 'POW')
    def __rtruediv__(self, other): return self.rBinary(other, 'DIV')

    def __eq__(self, other): return self.conditional(other, '==')
    def __ne__(self, other): return self.conditional(other, '!=')
    def __gt__(self, other): return self.conditional(other, '>')
    def __lt__(self, other): return self.conditional(other, '<')
    def __ge__(self, other): return self.conditional(other, '>=')
    def __le__(self, other): return self.conditional(other, '<=')

    def __fmax__(self, other): return self.binary(other, 'FMAX')
    def __fmin__(self, other): return self.binary(other, 'FMIN')

    def  __neg__(self): return self.unary('NEG')
    def  __exp__(self): return self.unary('EXP')
    def  __log__(self): return self.unary('LOG')
    def  __sin__(self): return self.unary('SIN')
    def  __cos__(self): return self.unary('COS')
    def  __tan__(self): return self.unary('TAN')
    def __fabs__(self): return self.unary('FABS')
    def __sqrt__(self): return self.unary('SQRT')
    def __sinh__(self): return self.unary('SINH')
    def __cosh__(self): return self.unary('COSH')
    def __tanh__(self): return self.unary('TANH')

def fmax(x,y):
    if not isinstance(x,Scalar) and not isinstance(y,Scalar): return np.maximum(x, y)
    else: return x.__fmax__(y) if isinstance(x,Scalar) else y.__fmax__(x)

def fmin(x,y):
    if not isinstance(x,Scalar) and not isinstance(y,Scalar): return np.minimum(x, y)
    else: return x.__fmin__(y) if isinstance(x,Scalar) else y.__fmin__(x)

def  exp(x): return np.exp(x)  if not isinstance(x,Scalar) else x.__exp__()
def  log(x): return np.log(x)  if not isinstance(x,Scalar) else x.__log__()
def  sin(x): return np.sin(x)  if not isinstance(x,Scalar) else x.__sin__()
def  cos(x): return np.cos(x)  if not isinstance(x,Scalar) else x.__cos__()
def  tan(x): return np.tan(x)  if not isinstance(x,Scalar) else x.__tan__()
def fabs(x): return np.abs(x)  if not isinstance(x,Scalar) else x.__fabs__()
def sqrt(x): return np.sqrt(x) if not isinstance(x,Scalar) else x.__sqrt__()
def sinh(x): return np.sinh(x) if not isinstance(x,Scalar) else x.__sinh__()
def cosh(x): return np.cosh(x) if not isinstance(x,Scalar) else x.__cosh__()
def tanh(x): return np.tanh(x) if not isinstance(x,Scalar) else x.__tanh__()