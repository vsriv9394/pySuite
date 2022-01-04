import sys, os
from subprocess import call
def mycall(cmd): call(cmd, shell=True)
dirpath = os.path.dirname(os.path.abspath(__file__))
bashrc = os.path.join(os.path.expanduser('~'), '.bashrc')

def copyLinesWithoutPymakeBlock():
    newFile = ''; copyMode = True
    with open(bashrc, 'r') as f:
        lines = f.readlines()
    for line in lines:
        if line=='# >>> pymake block begins >>>\n':
            newFile = newFile[:-1] # Remove the preceding newline
            copyMode = False
        elif line=='# <<< pymake block ends <<<\n':
            copyMode = True
        elif copyMode: newFile += line
    return newFile

def getLinesForPymakeBlock():
    lines = '\n'
    lines += '# >>> pymake block begins >>>\n'
    lines += 'export PATH="'+dirpath+':$PATH"\n'
    lines += '# <<< pymake block ends <<<\n'
    return lines

def writeExecutable():
    filepath = os.path.join(dirpath, 'pymake')
    mycall('rm -f '+filepath)
    with open(filepath, 'w') as f:
        f.write('#!'+sys.executable+'\n')
        f.write('import sys\n')
        f.write('sys.path.insert(0, "'+os.path.dirname(dirpath)+'")\n')
        f.write('from pymake import make\n')
        f.write('sys.path.pop(0)\n')
        f.write('make()\n')
    mycall('chmod +x ' + filepath)

if __name__=='__main__':
    
    if len(sys.argv)==1:
        writeExecutable()
        contents = copyLinesWithoutPymakeBlock()
        contents += getLinesForPymakeBlock()
        with open(bashrc, 'w') as f: f.write(contents)
    
    elif sys.argv[1] in ['-u', '--uninstall']:
        contents = copyLinesWithoutPymakeBlock()
        with open(bashrc, 'w') as f: f.write(contents)

    elif sys.argv[1] in ['-h', '--help']:
        print(
'''
 - Run "python install.py" to create a "pymake" executable script and add
   the path to the "pymake" directory to PATH variable in "~/.bashrc".

 - Run "python install.py -u" or "python install.py --uninstall" to remove
   the entry added in the "~/.bashrc" file.

 - You might need to do a "source ~/.bashrc" or restart the terminal to
   observe changes.
'''
        )