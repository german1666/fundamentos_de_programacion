'''
Clase:        1
Tema:         Variables, tipos, entradas y salidas
Descripción:  
Pide al usuario el total de una cuenta y el porcentaje de propina
(por ejemplo, 10%, 15%, 20%). Calcula y muestra en pantalla el 
total a pagar.

* El formato de la salida debe ser (el ejemplo asume un total de $10
y 10% de propina):

Total de la cuenta: $10.00
Propina: $1.00
Total de la cuenta con propina (10%): $11.00

Autor:        Luis German Dueñas Bernal
Fecha:        2025-05-15
Estado:       [ Terminado ]
'''

total = float(input("Ingresa el total de la cuenta $"))
propina = float(input("Ingresa el porcentaje de la propina %"))


propina_porcentaje = propina / 100
totalypropina = total + (total*propina_porcentaje)
print(f"Total: {total}$")
print(f"Total + propina del {int(propina)}% : {totalypropina}$")

"""Ejercicio #3"""

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

"""Contraseña segura"""

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

"""Calculo de impuesto"""

while True:
    try:
        consumo = input('Ingresa tus unidades de energía consumidas: ')
        consumo = float(consumo)
        if consumo <= 100:
            print("Tu impuesto a pagar es $0")
        elif 101 <= consumo < 200:
            print(f"Tu impuesto a pagar es ${consumo * 0.5}")
        else:
            print(f"Tu impuesto a pagar es ${consumo * 0.7}")
    except ValueError:
        print("Por favor, ingresa un valor numérico.")

    repetir = input("¿Reiniciar el programa? (s/n): ").lower().strip()
    if repetir != 's':
        print("Programa finalizado.")
        break

"""Números mágicos"""

numero = int(input("Ingresa un número (Entre 1 a 10^18)"))

if numero % 7 == 0 and numero % 5 != 0:
  print("El número es mágico")
else:
  print("El número no es mágico")