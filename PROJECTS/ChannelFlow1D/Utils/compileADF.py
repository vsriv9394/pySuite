import os
from subprocess import call
from pyad.pyAD import *

def compileADFs(TurbModel, adfList=[]):
    
    def residuals(
        inputs_AD = {
            'phi'      : [TurbModel.nStates],
            'grad_phi' : [TurbModel.nStates],
            'hess_phi' : [TurbModel.nStates],
        },
        inputs = {
            'nu'       : [],
            'dpdx'     : [],
            'wallDist' : [],
        }
    ):
        model = TurbModel(inputs_AD, inputs)
        outputs = { }
        outputs_AD = model.residuals
        return outputs, outputs_AD

    call('mkdir -p ADF', shell=True)
    os.chdir('ADF')
    admake(residuals)
    for adf in adfList: admake(adf)
    os.chdir('..')