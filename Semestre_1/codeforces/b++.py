n = int(input())
x = 0
for i in range(n):
    condition = input('')
    if condition == '++X' or condition =='X++':
        x += 1
    if condition == '--X' or condition =='X--':
        x -= 1
print(x)
