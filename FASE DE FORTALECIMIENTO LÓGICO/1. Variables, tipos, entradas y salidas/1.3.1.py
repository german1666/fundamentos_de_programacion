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
Fecha:        2025-05-12
Estado:       [ Terminado ]
'''

total = float(input("Ingresa el total de la cuenta $"))
propina = float(input("Ingresa el porcentaje de la propina %"))


propina_porcentaje = propina / 100
totalypropina = total + (total*propina_porcentaje)
print(f"Total: {total}$")
print(f"Total + propina del {int(propina)}% : {totalypropina}$")
