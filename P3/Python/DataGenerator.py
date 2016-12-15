import random as r

data = []

# left, center left, center, center right, right, blob size
# turn left, turn right, drive straight
# turn left
for t in range(500):
    input_Data = [r.uniform(0.5, 1.0), r.uniform(0.0, 1.0), r.uniform(0.0, 1.0), r.uniform(0.0, 0.0), \
    r.uniform(0.0, 0.5), r.uniform(0.0, 1.0)]
    output = [r.uniform(0.5, 1.0), r.uniform(0.0, 0.5), r.uniform(0.0, 0.5)]
    data.append((input_Data, output))

# turn right
for  t in range(500):
    input_Data = [r.uniform(0.0, 0.5), r.uniform(0.0, 0.5), r.uniform(0.0, 1.0), r.uniform(0.5, 1.0), \
    r.uniform(0.5, 1.0), r.uniform(0.0, 1.0)]
    output = [r.uniform(0.0, 0.5), r.uniform(0.5, 1.0), r.uniform(0.0, 0.5)]
    data.append((input_Data, output))

# drive forward
for t in range(500):
    input_Data = [r.uniform(0.0, 0.5), r.uniform(0.0, 1.0), r.uniform(0.0, 0.5), r.uniform(0.0, 0.5), \
    r.uniform(0.0, 1.0), r.uniform(0.0, 1.0)]
    output = [r.uniform(0.0, 0.5), r.uniform(0.0, 0.5), r.uniform(0.5, 1.0)]
    data.append((input_Data, output))

# stop
for t in range(500):
    input_Data = [r.uniform(0.0, 0.5), r.uniform(0.0, 0.5), r.uniform(0.5, 1.0), r.uniform(0.0, 0.5), \
    r.uniform(0.0, 0.5), r.uniform(0.0, 1.0)]
    output = [r.uniform(0.0, 0.5), r.uniform(0.0, 0.5), r.uniform(0.5, 1.0)]
    data.append((input_Data, output))

i = 0
for d in data:
    print(i)
    print(d)
    i = i + 1

with open('data.txt', 'w') as fp:
    fp.write('2000\n')
    fp.write('\n'.join('{} {}'.format(d[0],d[1]) for d in data))
