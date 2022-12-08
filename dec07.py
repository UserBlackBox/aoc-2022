f = open("data/dec07.processed")
root = [0, {}]

for line in list(f):
    line = line.strip().split()
    path = line[0]
    if len(line) > 1:
        size = int(line[1])
        path = path[1:].split('/')
        target_dir = root
        for i in path[:-1]:
            target_dir = target_dir[1][i]
        target_dir[1][path[-1]] = size
    else:
        path = path[1:].split('/')
        target_dir = root
        for i in path[:-2]:
            target_dir = target_dir[1][i]
        target_dir[1][path[-2]] = [0, {}]

global s
s = 0
sizes = []

def calcSizes(x) -> int:
    if isinstance(x, list):
        for file in x[1].keys():
            x[0] += calcSizes(x[1][file])
        if x[0] <= 100000:
            global s
            s += x[0]
        sizes.append(x[0])
        return x[0]
    else:
        return x

calcSizes(root)
print(s)
sizes.sort()
for i in sizes:
    if i > 30000000 - (70000000 - root[0]):
        print(i)
        break
