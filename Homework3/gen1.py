import random
const = 31
a = 0
b = []
b.append(a)
print(".word",end= "  ")
for i in range(1,const + 1):
    a+= 1
    b.append(a)
for i in range(1, 2000):
    c = random.randint(0,const)
    d = random.randint(0,const)
    e = b[c]
    b[c] = b[d]
    b[d] = e
for i in b:
    print(i, end=" ")
# print("-2")
for i in b:
    print(-1, end=" ")
print()
print(".word", 2*(const+1))
print()
for i in b:
    print("minHeap.insert({0})".format(i))