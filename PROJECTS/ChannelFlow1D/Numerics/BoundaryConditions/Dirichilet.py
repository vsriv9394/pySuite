from pyad.pyAD import *

def dirichiletBC(
    inputs_AD = { },
    inputs = { 'value': [] }
):

    outputs = { }
    outputs_AD = { 'phi_b': inputs['value'] }
    return outputs, outputs_AD