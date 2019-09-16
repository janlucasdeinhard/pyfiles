regression_matrix <- function(data,p,constant){
  
  nrow <- as.numeric(dim(data)[1])
  nvar <- as.numeric(dim(data)[2])
  
  Y1 <- as.matrix(data,ncol=nvar)
  X <- embed(Y1,p+1)
  X <- X[,(nvar+1):ncol(X)]
  
  if(constant==TRUE){
    X <- cbind(rep(1,nrow-p),X)
  }
  
  Y = matrix(Y1[(p+1):nrow(Y1),])
  nvar2 = ncol(X)
  
  return = list(Y=Y,X=X,nvar2=nvar2,nrow=nrow)
  
}

ar_companion_matrix <- function(beta){
  
  if(is.matrix(beta)==FALSE){
    stop('error: beta must be matrix')
  }
  
  k = nrow(beta) - 1
  FF <- matrix(0, nrow=k, ncol=k)
  
  FF[2:k,1:(k-1)] <- diag(1,nrow = k-1, ncol = k-1)
  temp <- t(beta[2:(k+1),1:1])
  
  FF[1:1,1:k] <- temp
  return(temp)
}

gibbs_sampler <- function(X,Y,B0,sigma0,sigma2,theta0,D0,reps,out,out1){
  
  
  
  
  return = list(out,out1)
}