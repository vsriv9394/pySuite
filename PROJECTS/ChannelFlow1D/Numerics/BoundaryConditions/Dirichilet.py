from pyad.pyAD import *

def dirichiletBC(
    inputs_AD = { 'phi' : [] },
    inputs = { 'value': [] }
):

    outputs = { }
    outputs_AD = { 'R_phi': inputs['value'] - inputs_AD['phi'] }
    return outputs, outputs_AD