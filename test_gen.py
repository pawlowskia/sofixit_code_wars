import os
import random

if not os.path.exists('./tests'):
    os.makedirs('./tests')

for i in range(100):
    if i < 5:
        continue

    N = random.randint(0, int(1000))

    numbers = [random.randint(0, int(1e6)) for j in range(N)]

    with open(f'./tests/test{i+1}.txt', 'w') as f:
        f.write(f'{N}\n')
        f.write(' '.join(map(str, numbers)))