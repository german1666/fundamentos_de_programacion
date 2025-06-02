'''
Clase:        2
Tema:         Bloque condicional
Descripción:  
Solicita una cadena de texto que representa una contraseña, y verifica si la contraseña
cumple con las siguientes condiciones: tener al menos 8 caracteres, un número y una
mayúscula.

Entrada:
• Una cadena de texto

Salida:
• Dos posibles valores: "Contraseña segura" o "Contraseña no segura".

Restricciones:
• Sin restricciones

Sugerencia:
• Investigar sobre los métodos isdigit() y isupper()

Autor:        Luis German Dueñas Bernal
Fecha:        2025-05-12
Estado:       [ Terminado ]
'''

CONTRA = input("Ingresa una contraseña: ")
chars = 0
nums = 0
mayus = 0
for char in CONTRA:
    chars += 1
    if char in "1234567890":
      nums += 1
    elif char in "ABCDEFGHIJKLMNOPQRSTUVWXYZ":
      mayus += 1

if chars >= 8 and nums >= 1 and mayus >= 1:
    print("Contraseña segura")
else:
  print("Contraseña no segura")
