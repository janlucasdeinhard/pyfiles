import numpy as np

class HopfieldBinary:
    def __init__(self,num_nodes):
        # Total number of nodes in the network
        self.num_nodes = num_nodes
        # Initialize weight matrix
        self.W = np.zeros(shape=[self.num_nodes,self.num_nodes])
        return
    def train(self,X):
        num_training_samples = X.shape[0]
        # Iterate all training samples
        for i in range(X.shape[1]):
            # Iterate all other nodes
            for j in range(i,X.shape[1]):
                # No self-correlations
                if i==j:
                    self.W[i,j] = 0
                    continue
                corr = 0
                # Calculate average correlation per synapse
                for x in range(num_training_samples): corr += (X[x,i]*X[x,j])
                corr /= num_training_samples
                # Set (symmetric) weight matrix between both current nodes
                self.W[i,j] = corr
                self.W[j,i] = corr
        return