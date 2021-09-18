# Graph Neural Network
The goal of this project is to evaluate and empirically confirm my own intuitions of how an artificial neurak network capable of
simulating the brains of living organisms should be built. This will likely be an evolutionarily optimized graph network of
some sort, trained through the Hopfield training mechanism, i.e. synapse growth based on neuronal input correlations. I break this
effort down into the following sub-projects:
* CorrelationCausalAnalysis
  An attempt to quantify an ML learning algorithm's ability to tease apart correlation from causal relationship. This can be accomplished based on allowing the agent
  to perform experiments in a causal graph.
* Entropy
  Here the entropy of different graph networks is compared. The assumption is that living organisms, or neural circuits, can be characterized as regions of space
  which regulate themselves such that the delta entropy over time is minimized, respecting the 2nd law of thermodynamics. A preliminary goal is to craft an algorithm
  which can gauge network entropy, and in a 2nd step an algorithm which can adjust weights of a network in order to reduce network entropy.
* GRAPHNN
  This sub-folder contains all attempts to actually implement and evaluate a graph neural network.
* Hopfield EndToENd
  This is an evaluation of different Hopfield neural network implementations, with the goal of generlizing the binary model to more useful versions.
