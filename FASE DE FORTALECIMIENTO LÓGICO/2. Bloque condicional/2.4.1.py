'''
Clase:        2
Tema:         Bloque condicional
Crea un programa en Python para determinar si un número es "mágico"
Un numero es "mágico" sì es divisible por 7 pero no por 5

Entrada:
* Un entero

Salida:
* "Mágico' o "Normal'

Restricciones:
* 1≤n ≤ 10^18

Autor:        Luis German Dueñas Bernal
Fecha:        2025-05-12
Estado:       [ Terminado ]
'''

numero = int(input("Ingresa un número (Entre 1 a 10^18)"))
if numero % 7 == 0 and numero % 5 != 0:
  print("El número es mágico")
else:
  print("El número no es mágico")