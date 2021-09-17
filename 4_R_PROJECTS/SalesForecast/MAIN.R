library(tidyverse)
library(dplyr)

bf <- read.csv('..\\..\\..\\TF_data\\TESTS\\SHS_CSV\\export.csv',sep = '\t', nrows = 100000)
df <- bf[which(bf['ACC'] == 'SU-1-1LC5AT'),]

time.sorted <- df[order(df$Date),]
time.min <- time.sorted[1]
time.max <- time.sorted[length(time.sorted)]

