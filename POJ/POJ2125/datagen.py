#! /usr/bin/env python

from random import randint
from sys import argv

N, M, A = map(int, argv[1:])

print N,M
for _ in [0,0]:
    print ' '.join([str(randint(1,A)) for i in range(0,N)])
for i in range(0,M):
    print randint(1,N), randint(1,N)
