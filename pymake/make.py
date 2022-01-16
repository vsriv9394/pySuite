import sys, os
from copy import deepcopy
from subprocess import call
from .makefile import options as default_options

###############################################################################

def get_LDFLAGS(path):
    filename = os.path.basename(path)
    assert(len(filename)>6)
    assert(filename[:3]=='lib' and filename[-3:]=='.so')
    libname = filename[3:-3]
    dirname = os.path.dirname(os.path.abspath(path))
    return '-Wl,-rpath='+dirname+' -L'+dirname+' -l'+libname

###############################################################################

def getCompilerOptions():
    _options = deepcopy(default_options)
    if os.path.exists('makefile.py'):
        exec(open('makefile.py').read() + '\n_options.update(options)\n')
    for i, path in enumerate(_options['includes']):
        _options['includes'][i] = '-I' + path
    for i, path in enumerate(_options['libs']):
        _options['libs'][i] = get_LDFLAGS(path)
    return _options

###############################################################################

def make(flags={}):
    #==========================================================================
    def appendNewItems(src, dest):
        for item in src:
            if item not in dest: dest.append(item)
    #==========================================================================
    def makeDependencies():
        for path in includes:
            if path not in flags.keys():
                os.chdir(path); make(flags=flags); os.chdir(pwd)
            appendNewItems(flags[path]['LD'], flags[pwd]['LD'])
            appendNewItems(flags[path]['C'],  flags[pwd]['C'] )
    #==========================================================================
    def addExternals():
        appendNewItems(options['libs'], flags[pwd]['LD'])
        appendNewItems(options['includes'], flags[pwd]['C'])
        appendNewItems(options['defs'], flags[pwd]['defs'])
    #==========================================================================
    pwd        = os.getcwd()
    className  = os.path.basename(pwd)
    options    = getCompilerOptions()
    flags[pwd] = {'LD' : [], 'C' : [], 'defs': []}

    includes, variables, subroutines = parseCFiles(className)
    makeDependencies()
    addExternals()
    compileCFiles(options['compiler'], className, flags[pwd])
    writePyFile(className, includes, variables, subroutines)
    flags[pwd]['LD'].append(get_LDFLAGS('./lib'+className+'.so'))

###############################################################################

def pyType(token):
    
    if token=='char*':
        return 'C.c_char_p'
    
    elif token=='void*':
        return 'C.c_void_p'
    
    elif token[-1]=='*':
        return 'C.POINTER(' + pyType(token[:-1]) + ')'
    
    elif token in ['int', 'double', 'char']:
        return 'C.c_'+token
    
    else: return token

###############################################################################

def formatVarDecl(varName, varType):
    
    while varName[0]=='*':
        varName = varName[1:]
        varType += '*'
    varType = pyType(varType)

    if varName[-1] not in [')',']']:
        return varName, varType

    if varName[0]=='(' and varName[-1]==')':
        return formatVarDecl(varName[1:-1], varType)
    
    if varName[-1]==']':
        i=-2; c=''
        while varName[i]!='[':
            c = varName[i] + c
            i -= 1
        varName = varName[:i]
        assert c!='', \
            'Cannot handle zero-dimensional array type (e.g. int a[])'
        if varType[-1] in [str(i) for i in range(9)]:
            varType = '(' + varType + ')'
        varType += '*' + c
        return formatVarDecl(varName, varType)

###############################################################################

def getTokenizedLine(f):
    return f.readline().strip().rstrip(',;').split()

###############################################################################

def parseCFiles(className):
    includes, variables = parseHeaderFile(className)
    subroutines = parseSourceFiles(className)
    return includes, variables, subroutines

###############################################################################

def parseHeaderFile(className):
    #=====================================================================
    def skipToTokens(f, chkTokens):
        while True:
            tokens = getTokenizedLine(f)
            if len(tokens)==len(chkTokens):
                matchFound = True
                for i in range(len(tokens)):
                    matchFound = matchFound and tokens[i]==chkTokens[i]
                if matchFound: break
    #=====================================================================
    def getIncludePaths(f):
        includes = []
        tokens = getTokenizedLine(f)
        while True:
            if len(tokens)==0: continue
            elif tokens[0]=='//INCLUDES_END': break
            else:
                relPath = tokens[1].strip('"')
                absPath = os.path.abspath(relPath)
                includes.append(os.path.dirname(absPath))
                tokens = getTokenizedLine(f)
        return includes
    #=====================================================================
    def getVars(f):
        vars = {}
        getTokenizedLine(f) # Skip line with opening brace
        tokens = getTokenizedLine(f)
        while tokens[0]!='}':
            varType, varName = tokens[0], tokens[1]
            varName, varType = formatVarDecl(varName, varType)
            vars[varName] = varType
            tokens = getTokenizedLine(f)
        return vars
    #=====================================================================
    with open(className+'.h', 'r') as f:
        skipToTokens(f, ['//INCLUDES_BEGIN'])
        includes = getIncludePaths(f)
        skipToTokens(f, ['typedef', 'struct'])
        variables = getVars(f)
    return includes, variables
    
###############################################################################

def parseSourceFiles(className):
    subroutines = {}
    for filename in os.listdir('src'):
        if filename[-2:]=='.c':
            name, args = parseSourceFile(className, filename)
            subroutines[name] = args
    return subroutines
    
###############################################################################

def parseSourceFile(className, filename):
    #=====================================================================
    def skipToNonStaticFunctionAndGetName(f):
        while True:
            tokens = getTokenizedLine(f)
            if len(tokens)==2:
                if tokens[0]=='void' and tokens[1][0]!='*':
                    return tokens[1]
    #=====================================================================
    def removeSuffixFromName(cName):
        expectedSuffix = '__' + className
        pyName = cName[:-len(expectedSuffix)]
        assert cName[-len(expectedSuffix):]==expectedSuffix, \
            'Function "' + cName + '"' + \
            ' in file "'+ os.path.abspath(filename) + '"' + \
            ' must end in "' + expectedSuffix + '"'
        return pyName
    #=====================================================================
    def getArguments(f, cName):
        args = {}
        nArgs = 0
        getTokenizedLine(f) # Skip line with opening parenthesis
        tokens = getTokenizedLine(f)
        while tokens[0]!=')':
            argType = tokens[0]
            argName = tokens[1]
            argName, argType = formatVarDecl(argName, argType)
            if nArgs==0: \
                assert argType=='C.c_void_p' and argName=='_self', \
                'Function "' + cName + '"' + \
                ' in file "'+ os.path.abspath(filename) + '"' + \
                ' must have its first argument as "void* _self"'
            args[argName] = argType
            tokens = getTokenizedLine(f)
            nArgs += 1
        return args
    #=====================================================================
    with open('src/'+filename, 'r') as f:
        cName = skipToNonStaticFunctionAndGetName(f)
        pyName = removeSuffixFromName(cName)
        args = getArguments(f, cName)
    return pyName, args

###############################################################################

def compileCFiles(compiler, className, flags):
    print('\npymake ['+os.getcwd()+']:')
    call('mkdir -p obj', shell=True)
    with open('Makefile', 'w') as f:
        f.write('SRC := $(wildcard src/*.c)\n')
        f.write('OBJ := $(patsubst src/%.c,obj/%.o,$(SRC))\n')
        f.write('CFLAGS :=')
        for flag in flags['defs']: f.write(' \\\n\t'+flag)
        for flag in flags['C']: f.write(' \\\n\t'+flag)
        f.write('\nLDFLAGS :=')
        for flag in flags['LD'][::-1]: f.write(' \\\n\t'+flag)
        f.write('\n\nall: lib' + className + '.so\n\n')
        f.write('lib' + className + '.so: $(OBJ)\n')
        f.write('\t'+ compiler)
        f.write(' -O3 -shared -fPIC -o $@ $^ $(LDFLAGS)\n\n')
        f.write('obj/%.o: src/%.c ' + className + '.h\n')
        f.write('\t'+ compiler + ' $(CFLAGS) ')
        f.write('-c -O3 -fPIC -o $@ $<\n\n')
        f.write('clean:\n')
        f.write('\trm -rf __pycache__ obj ' + \
                className + '.py lib' + className + '.so Makefile\n\n')
    call('make -j', shell=True)

###############################################################################

def writePyFile(className, includes, variables, subroutines):
    #=====================================================================
    def writeImports(f, includes):
        f.write('import sys, os\n')
        f.write('import ctypes as C\n\n')
        for includePath in includes:
            includeName = os.path.basename(includePath)
            f.write('sys.path.insert(0, "'+includePath+'")\n')
            f.write('from '+includeName+' import '+includeName+'\n')
            f.write('sys.path.pop(0)\n\n')
    #=====================================================================
    def writeStructFields(f, variables):
        f.write('\t_fields_ = [\n')
        for varName, varType in variables.items():
            f.write('\t\t("'+varName+'", '+varType+'),\n')
        f.write('\t]\n\n')
    #=====================================================================
    def writeFunctionSignatures(f, subroutines):
        for name, args in subroutines.items():
            f.write('\tC_'+name+' = lib.'+name+'__'+className+'\n')
            f.write('\tC_'+name+'.restype = None\n')
            f.write('\tC_'+name+'.argtypes = [\n')
            for argType in args.values():
                f.write('\t\t'+argType+',\n')
            f.write('\t]\n\n')
    #=====================================================================
    def writeFunctions(f, subroutines):
        for name, args in subroutines.items():
            if name not in ['init']:
                f.write('\tdef '+name+'(\n')
                f.write('\t\tself,\n')
                for argName in args.keys():
                    if argName!='_self':
                        f.write('\t\t'+argName+',\n')
                f.write('\t):\n')
                f.write('\t\tself.C_'+name+'(\n')
                f.write('\t\t\tC.addressof(self),\n')
                for argName, argType in args.items():
                    if argName!='_self':
                        if argType=='C.c_void_p':
                            f.write('\t\t\tC.addressof('+argName+'),\n')
                        else:
                            f.write('\t\t\t'+argName+',\n')
                f.write('\t\t)\n\n')
    #=====================================================================
    with open(className+'.py', 'w') as f:
        writeImports(f, includes)
        f.write('lib = C.CDLL("'+os.getcwd()+'/lib'+className+'.so")\n\n')
        f.write('class '+className+'(C.Structure):\n\n')
        f.write('\t_pack_ = 1\n')
        writeStructFields(f, variables)
        writeFunctionSignatures(f, subroutines)
        f.write('\tdef __init__(self):\n')
        f.write('\t\tself.C_init(C.addressof(self))\n\n')
        writeFunctions(f, subroutines)
