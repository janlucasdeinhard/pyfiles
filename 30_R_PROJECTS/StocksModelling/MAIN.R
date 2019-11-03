library(tidyverse)
library(dplyr)
library(arules)
library(HMM)
library(recipes)
library(mlbench)
library(caret)


Y = read.csv('data/all_stocks.csv',header=TRUE)
Y$dm = rowMeans(Y[c('high','low')])

Y0 = filter(Y,Name=='AAPL')
Y0$diff = c(NaN,diff(Y0$dm,lag = 1))
Y0$N = c(1:nlevels(Y0$date))

Y0$obs = rep('n',dim(Y0)[1])
Y0$obs[Y0$diff < (-2)] = 'ds'
Y0$obs[(Y0$diff >= (-2)) & (Y0$diff < (-0.5))] = 'd'
Y0$obs[(Y0$diff > (0.5)) & (Y0$diff <= (2))] = 'r'
Y0$obs[Y0$diff > (2)] = 'rs'

plot(Y0$N,Y0$diff,'l')

Thmm = matrix(c(0.4,0.5,0.1,0,0.2,0.6,0.2,0,0,0.1,0.6,0.3,0,0,0.1,0.9),nrow=4,ncol=4)
Ohmm = matrix(c(0.2,0.1,0.05,0.01,0.4,0.15,0.15,0.09,0.3,0.5,0.2,0.3,0.05,0.15,0.4,0.4,0.05,0.1,0.2,0.2),nrow=5,ncol=4) 

hmm = initHMM(States=c("G","S","D","X"),Symbols=c("rs","r","n","d","ds"),transProbs=Thmm,emissionProbs=Ohmm)
bw_res = baumWelch(hmm,Y0$obs)