def getIdInGraph(newNode, graph):
    notFoundInGraph = True
    for i, graphNode in enumerate(graph.nodeList):
        if type(newNode) is type(graphNode):
            if newNode.isIdenticalTo(graphNode):
                id = i
                notFoundInGraph = False
    if notFoundInGraph:
        id = len(graph.nodeList)
        graph.nodeList.append(newNode)
        graph.forwardBuffer.write(newNode.forwardStatement(id), newNode.forwardStatement(id) is not None)
        graph.reverseBuffer.write(newNode.reverseStatement(id), newNode.reverseStatement(id) is not None)
    return id

class inputNode:
    def __init__(self): pass
    def isIdenticalTo(self, node): return False
    def forwardStatement(self, id): return None
    def reverseStatement(self, id): return None

class outputNode:
    def __init__(self, refId): self.refId = refId
    def isIdenticalTo(self, node): return False
    def forwardStatement(self, id): return 'EQUAL(%d, %d)' % (id, self.refId)
    def reverseStatement(self, id): return 'D_EQUAL(%d, %d)' % (id, self.refId)

class constantNode:
    def __init__(self, value):      self.value = value
    def isIdenticalTo(self, node):  return self.value==node.value
    def forwardStatement(self, id): return 'CONST(%d, %.10le)' % (id, self.value)
    def reverseStatement(self, id): return None

class unaryNode:
    def __init__(self, operator, xid):
        self.operator = operator
        self.xid = xid
    
    def isIdenticalTo(self, node):
        return self.operator==node.operator and \
               self.xid==node.xid
    
    def forwardStatement(self, id):
        return '%s(%d, %d)' % (self.operator, id, self.xid)
    
    def reverseStatement(self, id):
        return 'D_%s(%d, %d)' % (self.operator, id, self.xid)

class binaryNode:
    def __init__(self, operator, xid, yid):
        self.operator = operator
        self.xid = xid
        self.yid = yid
    
    def isIdenticalTo(self, node):
        # Check for commutative variations as well
        return self.operator==node.operator and              \
             ((self.xid==node.xid and self.yid==node.yid) or \
              (self.xid==node.yid and self.yid==node.xid and \
               self.operator in ['ADD','MUL','FMAX','FMIN']))
    
    def forwardStatement(self, id):
        return '%s(%d, %d, %d)' % (self.operator, id, self.xid, self.yid)
    
    def reverseStatement(self, id):
        return 'D_%s(%d, %d, %d)' % (self.operator, id, self.xid, self.yid)