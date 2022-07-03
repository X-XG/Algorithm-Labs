N = 50000

import random
L1 = random. sample(range(1,2*N),N)
f = open('stupid.txt','w')
f.write(str(N))
f.write('\n')
for i in range(N):
    f.write(str(L1[i]))
    f.write(' ')
