'''
Clase:        10
Tema:         Matrices
Descripción:
Dada una matriz cuadrada ingresada por el 
usuario, crea dos listas, una con los 
elementos de la diagonal principal y la otra 
con los elementos de la diagonal 
secundaria.

Autor:        Luis German Dueñas Bernal
Fecha:        2025-06-9
Estado:       [ Terminado ]
'''

n = int(input())
matrix = []
diagonal = []
sec_diagonal = []
for i in range(n):
  raw = input()
  temp = list(map(int, raw.split(",")))
  matrix.append(temp)

# print(matrix)

for i in range(len(matrix)):
    for j in range(len(matrix[i])):
      if i == j:
        diagonal.append(matrix[i][j])
print(diagonal)


for i in range(len(matrix) -1, -1, -1):
    for j in range(len(matrix[i]) -1, -1, -1):
      if i == j:
        sec_diagonal.append(matrix[i][j])
print(sec_diagonal)