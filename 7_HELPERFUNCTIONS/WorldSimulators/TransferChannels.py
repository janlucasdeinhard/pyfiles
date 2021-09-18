from numpy import random as rnd

class MIMOTimeInvariant:    
    def __init__(self,n,m,mu_d=0,sigma_d=0):
        
        self.out_size = n
        self.in_size = m
        self.H = rnd.randn(n,m)
        self.mu_d = mu_d
        self.sigma_d = sigma_d
    def transfer_v(self,x):
        try:
            x = x.reshape(self.in_size,-1)
        except: raise Exception('Wrong input shape. Expected shape (-1,{}), found shape {}'.format(self.in_size,x.shape))
        r = self.sigma_d*rnd.randn(self.out_size,1) + self.mu_d
        y = self.H.dot(x) + r
        return y.reshape(-1,self.out_size)