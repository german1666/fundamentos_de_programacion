'''
Clase:        10
Tema:         Matrices
Descripción:
Dada una matriz binaria ingresada por el 
usuario, verifica para cada celda de una 
matriz binaria cuántos elementos con valor 
de 1 hay en las celdas vecinas (arriba, abajo, 
izquierda, derecha, diagonales).

Entrada:
• Dos números N,M con la dimensión de la 
matriz. N conjuntos de M cantidad de 
números enteros separados por coma.

Salida:
• Matriz NxM. Cada celda contiene la suma 
de elementos con valor de 1 en las celdas 
vecinas .

Autor:        Luis German Dueñas Bernal
Fecha:        2025-06-14
Estado:       [ Terminado ]
'''

n = int(input())
m = int(input())
i = 0
matrix = []
sum = []

def input_matrix(a,b):
  raw = input()
  temp = list(map(int, raw.split(",")))
  if len(temp) != m:
    print("Ingresa la cantidad M de elementos correcta")
    return input_matrix(n,m)
  else: 
    matrix.append(temp)

for i in range(n):
  input_matrix(n,m)

# print(matrix)

def count_neighbors(matrix, row, column):
    count = 0
    rows = len(matrix)
    cols = len(matrix[0])
    for x in [row - 1, row, row + 1]:
     for y in [column - 1, column,  column + 1]:
        if 0 <= x < rows and 0 <= y < cols:
                if x == row and y == column:
                    continue
                if matrix[x][y] == 1:
                    count += 1
    return count

for row in range(len(matrix)):
    row_sum = []
    for column in range(len(matrix[row])):
        row_sum.append(count_neighbors(matrix, row, column))
    sum.append(row_sum)  

for row in sum:
    print(row)
