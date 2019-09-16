library(ggplot)

df <- read.csv('.\\data\\GDPC1.csv',header=TRUE)
names <- c('Date','GDP')
Y <- data.frame(df[,2])

p = 2
T1 = nrow(Y)

results = list()
results <- regression_matrix(Y,p,TRUE)

X <- results$X
Y <- results$Y
nrow <- results$nrow
nvar <- results$nvar2

B <- c(rep(0,nvar))
B <- as.matrix(B, nrow=1, ncol=nvar)
sigma0 <- diag(1, nvar)

T0 = 1
D0 = 0.1
sigma2 = 1

reps = 15000
burn = 4000
horizon = 14

out = matrix(0, nrow=reps, ncol=nvar+1)

colnames(out) <- c('constant','beta1','beta2','sigma') 

out1 <- matrix(0,nrow = reps,ncol = horizon)
