'''
Clase:        1
Tema:         Variables, tipos, entradas y salidas
Descripción:  
Dados tres enteros a, b y k, imprime el resultado de a / b con k decimales exactos (sin redondear).
Conceptos explorados:
* Operaciones aritmeticas
* Manejo de negativos y ceros
* Precisión arbitraria en decimales.

Autor:        Luis German Dueñas Bernal
Fecha:        2025-05-15
Estado:       [ Terminado ]
'''

while True:
  try:
    a = int(input("dame un número para la variable a "))
    b = int(input("dame un número para la variable b "))
    k = int(input("dame un número para la variable k "))
    break
  except ValueError:
    print("ingresa un numero por favor")

division = a / b
print (f"La división de {a} / {b} con {k} decimales es : {division:.{k}f}")
