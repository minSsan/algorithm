result = [ 0 for i in range(10) ] # [0, 0, 0, 0, ... , 0]

a = int(input())
b = int(input())
c = int(input())

num = a * b * c

while num != 0:
    result[num % 10] += 1
    num = num // 10

for i in range(10):
    print(result[i])