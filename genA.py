from random import randint
from random import shuffle

def gen():
    cand = []
    for i in range(300):
        total = 999 - i
        g = randint(1, total)
        s = randint(0, total - g)
        b = total - g - s
        cand.append((g,s,b, "Taiwan "*total +"Taiwan"))
    return cand

for i in range(3, 51):
    with open(f'{i}.in','w') as FILE:
        cand = gen()
        shuffle(cand)
        print(len(cand),file=FILE)
        for g, s, b, noc in cand:
            print(g,s,b,noc,file=FILE)

