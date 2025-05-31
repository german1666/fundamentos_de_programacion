'''
Clase:        1
Tema:         Variables, tipos, entradas y salidas
Descripción:  
Solicita al usuario su nombre completo (asume dos nombres y
dos apellidos). Luego, el programa generará, su correo con el
formato:

• primer_nombre.primer_apellido@keyinstitute.edu.sv
Finalmente, el programa mostrará en pantalla el siguiente
mensaje:

El correo que se debe asignar al usuario ingresado es:
nombre.apellido@keyinstitute.edu.sv


Autor:        Luis German Dueñas Bernal
Fecha:        2025-05-15
Estado:       [ Terminado ]
'''

nombre = input("Ingresa tu nombre completo (Ejemplo: Luis German Dueñas Bernal): ")
nombre_cortado = nombre.split()
print(f"{nombre_cortado[0].lower()}.{nombre_cortado[2].lower()}@keyinstitute.edu.sv")
