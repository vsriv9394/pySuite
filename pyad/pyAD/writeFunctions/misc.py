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
    buffer.write('#include "'+pyad_dir+'/VarAD/VarAD.h"')
    buffer.write('#include "'+pyad_dir+'/JacAD/JacAD.h"')
    buffer.write('//INCLUDES_END')
    buffer.write('')
    buffer.write('typedef struct')
    buffer.openScope()
    buffer.write('double ___phi[%d];' % (max_size))
    buffer.write('double ___psi[%d];' % (max_size))
    for name in  inputs_AD.keys(): buffer.write('VarAD *'+name+';')
    for name in     inputs.keys(): buffer.write('double *'+name+';')
    for name in    outputs.keys(): buffer.write('double *'+name+';')
    for name in outputs_AD.keys(): buffer.write('VarAD *'+name+';')
    buffer.closeScope()
    buffer.write(functionName+';')
    buffer.write('')
    buffer.write('void init__'+functionName+'(void *_self);')
    buffer.write('void calculate__'+functionName+'(void *_self);')
    buffer.write('void setup__'+functionName+'(void *_self);')
    line = 'void setVars__'+functionName+'(void *_self'
    for name in  inputs_AD.keys(): line += ', void *'+name
    for name in     inputs.keys(): line += ', void *'+name
    for name in    outputs.keys(): line += ', void *'+name
    for name in outputs_AD.keys(): line += ', void *'+name
    line += ');'
    buffer.write(line)
    buffer.write('')
    buffer.write('#endif')

def writeOtherFiles(dirName, functionName, vars):
    with open(dirName+'/src/setVars.c', 'w') as f:
        f.write('#include "../'+functionName+'.h"\n')
        f.write('\n')
        f.write('void setVars__'+functionName+'\n')
        f.write('(\n')
        f.write('\tvoid *_self')
        for name in vars[ 'inputs_AD'].keys(): f.write(',\n\tvoid *'+name)
        for name in vars[    'inputs'].keys(): f.write(',\n\tvoid *'+name)
        for name in vars[   'outputs'].keys(): f.write(',\n\tvoid *'+name)
        for name in vars['outputs_AD'].keys(): f.write(',\n\tvoid *'+name)
        f.write('\n)\n')
        f.write('{\n')
        f.write('\t'+functionName+'* self = _self;\n')
        for name in vars['inputs_AD'].keys():  f.write('\tself->'+name+' = '+name+';\n')
        for name in vars['inputs'].keys():     f.write('\tself->'+name+' = '+name+';\n')
        for name in vars['outputs_AD'].keys(): f.write('\tself->'+name+' = '+name+';\n')
        for name in vars['outputs'].keys():    f.write('\tself->'+name+' = '+name+';\n')
        f.write('}\n')
    
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
        f.write('}\n')
    
    with open(dirName+'/src/setup.c', 'w') as f:
        f.write('#include "../'+functionName+'.h"\n')
        f.write('\n')
        f.write('void setup__'+functionName+'\n')
        f.write('(\n')
        f.write('\tvoid *_self\n')
        f.write(')\n')
        f.write('{\n')
        f.write('\t'+functionName+'* self = _self;\n\n')
        nInputs = 0
        for shape in vars['inputs_AD'].values(): nInputs += int(np.prod(shape))
        f.write('\tvoid *ptrToDep[%d]; int iInput = 0;\n\n' % (nInputs))
        for name, shape in vars['inputs_AD'].items():
                f.write('\tfor(int i=0; i<%d; i++)\n' % (int(np.prod(shape))))
                f.write('\t\tptrToDep[iInput++] = (void*)(self->'+name+'+i);\n\n')
        for name, shape in vars['outputs_AD'].items():
                f.write('\tfor(int i=0; i<%d; i++)\n' % (int(np.prod(shape))))
                f.write('\t\tsetupDeps__VarAD(self->'+name+'+i, %d, ptrToDep);\n\n' % (nInputs))
        f.write('}\n')