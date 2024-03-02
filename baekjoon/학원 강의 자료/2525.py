a, b = map(int, input().split())
c = int(input())

b = b + c
while b >= 60:
    b = b - 60
    a = a + 1

while a >= 24:
    a = a - 24

print(a, b)