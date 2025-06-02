'''
Clase:        2
Tema:         Bloque condicional
Desarrollar un programa en Python que permita calcular el impuesto que debe pagar
un usuario por el consumo de energía. El cálculo debe realizarse basado en la siguiente
tabla.

Entrada:
• Unidades consumidas (entero).

Salida:
• Impuesto aplicado ($).
Restricciones:
• Sin restricciones.

Autor:        Luis German Dueñas Bernal
Fecha:        2025-05-12
Estado:       [ Terminado ]
'''

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