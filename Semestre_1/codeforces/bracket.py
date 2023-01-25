from unittest import case


t = int(input())
num_operations = 0
for t in range(t):
    count1 = 0
    count2 = 0
    contador_geral = 0
    n = int(input())
    caso = input('')
    reverse_case = caso[:: -1 ]
    if caso == reverse_case:
        print('1 0')
        break
    for i in caso:
        if i == '(':
            caso = caso.replace('(', '', 1)
            count1 += 1
        elif i ==')':
            caso = caso.replace(')', '', 1)
            count2 += 1
    print(caso)
        

