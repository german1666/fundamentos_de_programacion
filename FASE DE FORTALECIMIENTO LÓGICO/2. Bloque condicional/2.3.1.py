'''
Clase:        2
Tema:         Bloque condicional
Descripción:  
Dados tres enteros a, b y k, imprime el resultado de a / b con k decimales exactos (sin redondear).
Conceptos explorados:
* Operaciones aritmeticas
* Manejo de negativos y ceros
* Precisión arbitraria en decimales.

Autor:        Luis German Dueñas Bernal
Fecha:        2025-14-15
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
