'''
Clase:        6
Tema:         Bloques iterativos
Descripción:
Un número en una lista es "líder" si es estrictamente mayor que todos los elementos a su derecha. Dada una lista de números ingresada por el usuario, imprime todos los números líderes.
Entrada:
* La primera línea contiene n enteros a1,...., an
(1 ≤ ai ≤ 10°)
Salida:
* Una línea con todos los números líderes en el orden en que aparecen en el arreglo.

Autor:        Luis German Dueñas Bernal
Fecha:        2025-06-2
Estado:       [ Terminado ]
'''

# 1 65 1 1 16 5 6 8 6 4
lista = list(map(int, input().split()))
# print(lista)
a = 0
b = a + 1
lider = []

for num in lista:
  if b < len(lista):
    while True:
      if b == len(lista):
        # print(f"{lista[a]} comparado con {lista[b]}")
        lider.append(lista[a])
        break
      if lista[a] < lista[b]:
        # print(f"{lista[a]} < {lista[b]}")
        break
      else:
        # print(f"{lista[a]} > {lista[b]}")
        b += 1
  a = a +1
  b = a +1
  
print(lider)
response = ""
for num in lider:
  response += str(num) + " "
print(response)

# print(a)
# print(b)
# print(len(lista))