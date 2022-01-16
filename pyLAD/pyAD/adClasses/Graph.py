from .FormattedBuffer import FormattedBuffer

class Graph:

    def __init__(self):
        self.nodeList          = []
        self.conditionalCount  = 0
        self.knownConditionals = []
        self.forwardBuffer     = FormattedBuffer()
        self.reverseBuffer     = FormattedBuffer(openTag='}',closeTag='{')

    def rollBackToLastTrueBranchAndSwitchIt(self):
        while self.conditionalCount > 0:
            if self.knownConditionals[-1].value==False:
                self.knownConditionals[-1].finalizeFalseBranch()
                del self.knownConditionals[-1]
                self.conditionalCount -= 1
            else: break
        if self.conditionalCount > 0:
            self.knownConditionals[-1].switchToFalseBranch()
            self.conditionalCount = 0