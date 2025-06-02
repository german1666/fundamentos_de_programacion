'''
Clase:        6
Tema:         Bloques iterativos
Descripción:
Dada una lista ingresada por el usuario, elimina los elementos duplicados
manteniendo la primera aparición de cada número.

Entrada:
* La primera línea contiene n enteros a,....
an (1 ≤ aj ≤ 106)

Salida:
* Una línea con los enteros únicos en su orden de aparición, separados por espacios.

Autor:        Luis German Dueñas Bernal
Fecha:        2025-06-2
Estado:       [ Terminado ]
'''

nums = input("Ingresa numeros separados por espacios y eliminare los numeros repetidos: ")

cadena = str(nums)
lista = cadena.split()
# print(lista)

sin_repetidos = []
# def encontrar_repetido(lista, sin_repetidos):
for num in lista:
  if num not in sin_repetidos:
    sin_repetidos.append(num)

cadena_sin_repetidos = ""
for num in sin_repetidos:
  cadena_sin_repetidos += num + " "

print(f"Los números sin repetirse son: {cadena_sin_repetidos}")