import numpy as np
from numpy import random as rnd
from WorldSimulators.TransferChannels import MIMOTimeInvariant

class ChannelInversionPrecoder:
    def __init__(self,channel):
        assert isinstance(channel,MIMOTimeInvariant),'arg0 must be channel instance'
        self.channel = channel
        self.num_RX = channel.H.shape[0]
        self.num_TX = channel.H.shape[1]
        self.estimate_with_basis()
    def estimate_with_basis(self,return_precoder_matrix=False):
        R = np.zeros([self.num_RX,self.num_TX])
        for k in range(self.num_TX):
            v = np.zeros(self.num_TX)
            v[k] = 1
            R[:,k] = self.channel.transfer_v(v).transpose().reshape(self.num_RX)
        self.Hinv = np.linalg.inv(R.transpose()@R)@R.transpose()
        self.channel_estimated = True
        if return_precoder_matrix:
            return self.Hinv
        else:
            return
    def precode_v(self,v):
        return self.Hinv@v
    def test_v(self,v,verbose=False):
        p = self.precode_v(v)
        o = self.channel.transfer_v(p)
        avg_squ_err = np.linalg.norm(invec-outvec,2)/num_RX
        if verbose: print('Avg. square error = {0:.4}'.format(avg_squ_err))
        return v,p,o,avg_squ_err
    def random_tests(self,num_tests=20):
        TESTSET = rnd.randn(self.num_RX,num_tests)/(self.num_RX*self.num_TX)
        RESULTS = []
        for k in range(TESTSET.shape[1]):
            RESULTS.append(self.channel.transfer_v(self.precode_v(TESTSET[:,k])).reshape(-1))
        RESULTS = np.array(RESULTS).transpose()
        C = np.zeros([TESTSET.shape[1],TESTSET.shape[1]])
        for m in range(TESTSET.shape[1]):
            for n in range(TESTSET.shape[1]):
                C[m,n] = TESTSET[:,m]@RESULTS[:,n]
        avg_squ_err = np.sqrt(np.sum((TESTSET-RESULTS)**2))/(TESTSET.shape[0]*TESTSET.shape[1])
        return avg_squ_err,C,(TESTSET,RESULTS)
