max = 0
input_list = []

for i in range(9):
    num = int(input())
    input_list.append(num)
    if num > max:
        max = num

print(max)
print(input_list.index(max)+1)