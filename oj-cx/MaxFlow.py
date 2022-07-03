N = 600
M = 10000

import random

list = []

f = open('data.txt', 'w')

f.write('{} {}\n'.format(N, M))
count = 0
while count < M:
    u = random.randint(1, N)
    v = random.randint(1, N)
    w = random.randint(0, 1000)
    # if w < 500:
    #     w = 1
    # else:
    #     w = 1000
    if u == v or (u, v) in list or (v, u) in list:
        continue
    list.append((u, v))
    f.write('{} {} {}\n'.format(u, v, w))
    count += 1

u = random.randint(1, N)
v = random.randint(1, N)
f.write('{} {}\n'.format(u, v))
