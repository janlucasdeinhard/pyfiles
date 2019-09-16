library(tidyverse)
library(dplyr)
library(arules)
library(HMM)
library(recipes)
library(mlbench)
library(caret)


Y = read.csv('data/all_stocks.csv',header=TRUE)
Y$dm = rowMeans(Y[c('high','low')])

Y$diff = c(NaN,diff(Y$dm,lag = 1))

Y0 = filter(Y,Name=='AAPL')

disc <- discretize(Y0$diff,cuts=10,labels=seq(min(Y0$diff),max(Y0$diff),length.out=10),prefix=NULL)
Y0$binned = as.numeric(as.character(predict(disc,Y0$diff)))
