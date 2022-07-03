S = 5
T = 7
import random
print('%d %d %d' % (S, T, S * T))
for i in range(1, S + 1):
    for j in range(S + 1, S + T + 1):
            print('%d %d %d' % (i, j, random.randint(1, 10)))
