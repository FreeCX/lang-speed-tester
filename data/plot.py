#!/bin/env python
from matplotlib import pyplot as plt
from pylab import loadtxt

if __name__ == '__main__':
    data = loadtxt('lang-speed-data')
    Y = list(map(lambda x: x[0], data))
    for row in range(1, len(data[0])):
        X = list(map(lambda x: x[row] * 1E-6, data))
        plt.semilogx(Y, X, label='{}'.format(row))
    plt.grid()
    plt.legend()
    plt.show()
