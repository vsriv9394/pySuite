import os
from subprocess import call
from pyad.pyAD import *

def compileADFs(TurbModel, adfList=[]):
    
    def residuals(
        inputs_AD = {
            'phi'      : [TurbModel.nStates],
            'grad_phi' : [TurbModel.nStates],
            'hess_phi' : [TurbModel.nStates],
            'cb1'      : [],
        },
        inputs = {
            'nu'       : [],
            'dpdx'     : [],
            'wallDist' : [],
        }
    ):
        vars = {'phi':inputs_AD['phi'], 'grad_phi':inputs_AD['grad_phi'], 'hess_phi':inputs_AD['hess_phi']}
        constants = {'nu':inputs['nu'], 'dpdx':inputs['dpdx'], 'wallDist':inputs['wallDist'], 'TurbModel__cb1':inputs_AD['cb1']}
        model = TurbModel(vars, constants)
        outputs = { }
        outputs_AD = model.residuals
        return outputs, outputs_AD

    call('mkdir -p ADF', shell=True)
    os.chdir('ADF')
    admake(residuals)
    for adf in adfList: admake(adf)
    os.chdir('..')