'''
Clase:        2
Tema:         Bloque condicional
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
Fecha:        2025-14-15
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