import matplotlib.pyplot as plt
import matplotlib as mpl
mpl.rc('text', usetex=True)
mpl.rcParams.update({'font.size':18})

def inlinePlot(name, x, y, xlabel='', ylabel='', title='', xlim={}, ylim={}, kind='plot',
               tight_layout_pad=1.05, figsize=[10,8], savefig=False, show=True, **options):
    
    plt.figure(name, figsize=figsize)
    if   kind=='semilogx': plt.semilogx(x, y, **options)
    elif kind=='semilogy': plt.semilogy(x, y, **options)
    elif kind=='loglog'  : plt.loglog(x, y, **options)
    else: plt.plot(x, y, **options)
    plt.xlabel(xlabel)
    plt.ylabel(ylabel)
    plt.title(title)
    plt.xlim(**xlim)
    plt.ylim(**ylim)
    plt.tight_layout(pad=tight_layout_pad)
    if savefig: plt.savefig(name+'.png')
    if show: plt.show()