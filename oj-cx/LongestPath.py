N = 1000
M = 2000
Q = 10

import random

f = open('data.txt', 'w')

f.write('{} {}\n'.format(N, M))
for i in range(M):
    u = random.randint(1, N)
    v = random.randint(1, N)
    w = random.randint(0, 1000)
    f.write('{} {} {}\n'.format(u, v, w))
f.write('{}\n'.format(Q))
for i in range(Q):
    u = random.randint(1, N)
    v = random.randint(1, N)
    f.write('{} {}\n'.format(u, v))
