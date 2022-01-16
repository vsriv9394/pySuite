import os
import numpy as np

from ..adClasses import FormattedBuffer

pyad_dir = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))

def writeStructFile(buffer: FormattedBuffer, functionName, inputs_AD, inputs, outputs, outputs_AD, max_size):
    buffer.write('#ifndef '+functionName+'_h')
    buffer.write('#define '+functionName+'_h')
    buffer.write('#pragma pack(1)')
    buffer.write('')
    buffer.write('//INCLUDES_BEGIN')
    buffer.write('#include "'+pyad_dir+'/ArrayAD/ArrayAD.h"')
    buffer.write('#include "'+pyad_dir+'/JacobianAD/JacobianAD.h"')
    buffer.write('//INCLUDES_END')
    buffer.write('')
    buffer.write('typedef struct')
    buffer.openScope()
    buffer.write('double ___phi[%d];' % (max_size))
    buffer.write('double ___psi[%d];' % (max_size))
    for name in  inputs_AD.keys(): buffer.write('double *'+name+';')
    for name in     inputs.keys(): buffer.write('double *'+name+';')
    for name in    outputs.keys(): buffer.write('double *'+name+';')
    for name in outputs_AD.keys(): buffer.write('double *'+name+';')
    for oName in outputs_AD.keys():
        for iName in inputs_AD.keys():
            buffer.write('double *d_'+oName+'__d_'+iName+';')
    buffer.closeScope()
    buffer.write(functionName+';')
    buffer.write('')
    buffer.write('void init__'+functionName+'(void *_self);')
    buffer.write('void calculate__'+functionName+'(void *_self);')
    buffer.write('')
    buffer.write('#endif')

def writeOtherFiles(dirName, functionName, vars):
    with open(dirName+'/src/init.c', 'w') as f:
        f.write('#include "../'+functionName+'.h"\n')
        f.write('\n')
        f.write('void init__'+functionName+'\n')
        f.write('(\n')
        f.write('\tvoid *_self\n')
        f.write(')\n')
        f.write('{\n')
        f.write('\t'+functionName+'* self = _self;\n')
        for name in vars['inputs_AD'].keys():  f.write('\tself->'+name+' = NULL;\n')
        for name in vars['inputs'].keys():     f.write('\tself->'+name+' = NULL;\n')
        for name in vars['outputs_AD'].keys(): f.write('\tself->'+name+' = NULL;\n')
        for name in vars['outputs'].keys():    f.write('\tself->'+name+' = NULL;\n')
        for oName in vars['outputs_AD'].keys():
            for iName in vars['inputs_AD'].keys():
                f.write('\tself->d_'+oName+'__d_'+iName+' = NULL;\n')
        f.write('}\n')
