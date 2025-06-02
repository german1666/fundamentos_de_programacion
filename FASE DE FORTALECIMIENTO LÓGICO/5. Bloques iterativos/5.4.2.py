'''
Clase:        5
Tema:         Bloques iterativos
Descripción:
Pide un número al usuario y suma sus dígitos hasta que quede un solo digito. Ejemplo:
Si el usuario ingresa 9875, entonces: 9+8+7+5 = 29 → 2+9 = 11 → 1+1 = 2.
Entrada:
* Un numero entero.
Restricciones:
* 1 ≤ número ≤ 10^9
Conceptos explorados:
* Bucles y control de flujo.

Autor:        Luis German Dueñas Bernal
Fecha:        2025-05-28
Estado:       [ Terminado ]
'''

while True:
  try:
    n = int(input("Ingresa un número entero del 1 a 1000000000 "))
  except ValueError:
    print("Ingresa un valor numérico")
    continue
  if n > 1000000000 or n < 1 :
      print("Ingresa un número válido")
  else:
      break

cadena = str(n)
while len(cadena) > 1:
  sum = 0
  for i in cadena:
    sum += int(i)
  print(f" {cadena} = {sum}")
  cadena = str(sum)
