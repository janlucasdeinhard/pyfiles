import numpy as np
from numpy import random as rnd
from matplotlib import pyplot as plt
from scipy.interpolate import pchip
from torchvision.datasets import CIFAR10

class GenericScalarDistribution:
    def __init__(self,datapoints):
        self.datapoints = datapoints
        self.__build_interpolate()
        return
    def __build_interpolate(self):
        x0 = np.array(self.datapoints)[:,0]
        y0 = np.array(self.datapoints)[:,1]
        f = pchip(x0,y0)
        self.x = np.arange(np.min(x0),np.max(x0))
        yp = f(self.x)
        self.p = yp/yp.sum()
        return
    def plot_distribution(self):
        plt.plot(self.x,self.p)
        plt.xlabel('x')
        plt.ylabel('Pr(X=x)')
        plt.title('Probability Density')
        plt.show() 
        return self.x,self.p
    def sample(self,n=1):
        return rnd.choice(self.x,p=self.p,size=n)

class Cifar10Distribution():
    def __init__(self,datapoints,path_to_cifar10):
        self.pdf = GenericScalarDistribution(datapoints)
        self.datapoints = [None]*self.pdf.x.shape[0]
        self.path_to_cifar10 = path_to_cifar10
        self.__assign_random_datavectors()
        return
    def __assign_random_datavectors(self):
        x_train = CIFAR10(root=self.path_to_cifar10, download=True).data
        self.datapoints = x_train[rnd.permutation(np.arange(0,x_train.shape[0]))[:self.pdf.x.shape[0]],:,:,:]
        return
    def sample(self,n=1):
        return self.datapoints[[int(self.pdf.sample(n)[k]) for k in range(n)],:,:,:]
    def plot_distribution(self):
        self.pdf.plot_distribution()
        return
