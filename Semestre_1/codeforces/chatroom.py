s = input()
for i in s:
    if (i != 'h' and i != 'e' and i != 'l' and i !='o'):
        s = s.replace(i, "")
contadorh = 0
contadore = 0
contadorl = 0
contadoro = 0
copia = ''
for i in s:
    if i == "h" or contadorh >= 1:
        if contadorh < 1:
            copia += "h"
            contadorh += 1
        else:
            if i == "e" or contadore >= 1:
                if contadore < 1:
                    copia += "e"
                    contadore += 1
                else:
                    if i == "l" or contadorl >= 1:
                        if contadorl < 2:
                            copia += "l"
                            contadorl += 1
                        else:
                            if i == "o":
                                copia += "o"
                                break
if (copia == 'hello' and contadorl >= 2):
    print("YES")
else:
    print("NO")