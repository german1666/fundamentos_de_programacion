'''
Clase:        10
Tema:         Matrices
Descripción:
Dada una matriz cuadrada ingresada por el 
usuario, comprueba si la matriz cuadrada es 
simétrica respecto a su diagonal principal.

Entrada:
• Numero entero N con la dimensión de la 
matriz. N conjuntos de números enteros 
separados por coma.

Salida:
• Una línea con una cadena de texto. “La 
matriz es simétrica” si es simétrica; “La 
matriz no es simétrica” en caso contrario.

Autor:        Luis German Dueñas Bernal
Fecha:        2025-06-9
Estado:       [ Terminado ]
'''

n = int(input())
matrix = []

for i in range(n):
  raw = input()
  temp = list(map(int, raw.split(",")))
  matrix.append(temp)
# print("MATRIX")
#MATRIZ SIMÉTRICA 3X3
# 3
# 1,2,3
# 2,3,2
# 3,2,1

# MATRIZ SIMÉTRICA 5X5
# 5
# 1, 2, 3, 4, 5
# 2, 1, 6, 7, 8
# 3, 6, 1, 9, 10
# 4, 7, 9, 1, 11
# 5, 8, 10, 11, 1

sym = True
for row in range(len(matrix)):
    for column in range(len(matrix[row])):
      if row != column:
        if matrix[row][column] != matrix[column][row]:
          sym = False
        # print(matrix[row][column])
        # print(matrix[column][row])
if sym == True:
  print("La matriz es simétrica")
else:
  print("La matriz no es simétrica")
