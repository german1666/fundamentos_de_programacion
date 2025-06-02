'''
Clase:        5
Tema:         Bloques iterativos
Descripción:
Genera un número aleatorio entre 1 y 100 y pide al usuario que lo adivine.
El programa debe seguir pidiendo números hasta que acierte. En cada intento fallido el programa notificará al usuario si el número secreto es mayor o menor al último valor ingresado.
Entrada:
* Números enteros entre 1 y 100.
Salida:
* Tres posibles salidas: "El número secreto es menor", "El número secreto es mayor", ¡Felicidades! Has adivinado el número secreto"

Autor:        Luis German Dueñas Bernal
Fecha:        2025-05-28
Estado:       [ Terminado ]
'''

import random
ran = random.randint(1,100)

print(f"Ingresa un número entre {1} y {100}")
while True:
  num = int(input(f"Ingresa un numero entre {1} y {100}: "))
  if num == ran:
    print(f"¡Felicidades! Has adivinado el número secreto: {ran}")
    break
  else:
    if num > ran:
      print("El número secreto es menor")
    else:
      print("El número secreto es mayor")