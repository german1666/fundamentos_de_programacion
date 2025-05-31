'''
Clase:        3
Tema:         5. Bloques iterativos
Descripción:
Genera un número aleatorio entre 1 y 100 y pide al usuario que lo adivine.
El programa debe seguir pidiendo números hasta que acierte. En cada
intento fallido el programa notificará al usuario si el número secreto es
mayor o menor al último valor ingresado.

Entrada:
• Números enteros entre 1 y 100.

Salida:
• Tres posibles salidas: “El número secreto es menor”, “El número secreto
es mayor”, ¡Felicidades! Has adivinado el número secreto”

Conceptos explorados:
• Uso de bucles indefinidos

Ejemplo (Respetar el formato de entrada y salida):

Ingresa un numero entre 1 y 100: 50
El número secreto es mayor
Ingresa un numero entre 1 y 100: 75
El número secreto es menor
Ingresa un numero entre 1 y 100: 56
!Felicidades¡ Has adivinado el número secreto: 56

Ejercicio requerido (tarea 8)

Autor:        Luis German Dueñas Bernal
Fecha:        2025-28-15
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