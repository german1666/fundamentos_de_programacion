'''
Clase:        7
Tema:         Introducción a NumPy
Descripción:
Instrucciones:
Responde cada pregunta escribiendo el código necesario para obtener la respuesta.
Agrega también comentarios o respuestas escritas cuando se solicite explicación.
No borres las secciones anteriores del archivo python desarrollado para esta guía de trabajo, simplemente agrega tus respuestas al final.
Puedes auxiliarte de tu herramienta IA preferida, pero recuerda las buenas prácticas para su uso. Somos responsables de comprender el resultado.
Cuestionario.
1. ¿Cuál es el consumo del hogar 5 el viernes (día 5)?
2. Usando indexación, muestra el consumo de los últimos 3 hogares el domingo.
3. Calcula el promedio de consumo los fines de semana (sábado y domingo, columnas 5 y 6).
4. ¿Qué día de la semana tiene la mayor desviación estándar entre hogares? Explica qué indica esto.
5. Identifica los 3 hogares con menor consumo total durante la semana. Muestra sus índices y valores.
6. Si el hogar 3 aumenta su consumo en un 10% cada día, ¿cuál sería su nuevo consumo total semanal?


Autor:        Luis German Dueñas Bernal
Fecha:        2025-06-3
Estado:       [ Terminado ]
'''
import numpy as np

# my_list = [1, 2, 3, 4, 5]
# arr = np.array(my_list)
# print(arr)

# zeros = np.zeros(5)
# print(zeros)

# ones = np.ones(5)
# print(ones)

# arr1 = np.array([1, 2, 3])
# arr2 = np.array([4, 5, 6])
# resultado = arr1 + arr2
# resultado = arr1 * arr2

# print(resultado)

# arr = np.array([1, 2, 3])
# result = arr + 5

# arr1 = np.array([1, 2, 3])
# arr2 = np.array([[10], [20], [30]])
# result = arr1 + arr2

# arr = np.array([1, 2, 3, 4, 5])
# slice = arr[1:4]
# Recupera los elementos 2, 3 y 4

# Indexación booleana
# arr = np.array([1, 2, 3, 4, 5])
# mask = arr > 2
# result = arr[mask]
# Recupera los elementos donde la condición es verdadera: [3, 4, 5]

# arr = np.array([1, 2, 3, 4, 5])
# indices = np.array([0, 2, 4])
# result = arr[indices] 
# Recupera los elementos en los índices especificados: [1, 3, 5]

# #Concatenación
# arr1 = np.array([1, 2, 3])
# arr2 = np.array([4, 5, 6])
# concatenated = np.concatenate((arr1, arr2))

# print(concatenated)

# #División
# arr = np.array([1, 2, 3, 4, 5, 6])
# split = np.split(arr, 3) 
# # Divide la matriz en 3 partes iguales
# print(split)

consumo = np.array([
    [12.5, 13.2, 11.9, 14.0, 13.5, 15.0, 14.3],
    [10.1, 10.5, 10.0, 11.2, 11.5, 12.0, 11.8],
    [14.0, 14.2, 13.9, 15.5, 15.1, 16.0, 15.8],
    [9.0, 9.2, 8.9, 9.5, 9.8, 10.0, 9.7],
    [16.2, 16.5, 16.0, 17.1, 17.4, 18.0, 17.8],
    [11.0, 11.3, 11.1, 12.0, 12.4, 12.8, 12.5],
    [13.5, 13.8, 13.2, 14.1, 14.6, 15.0, 14.9],
    [10.8, 11.0, 10.6, 11.5, 11.8, 12.2, 12.0],
    [15.1, 15.5, 15.0, 16.0, 16.4, 17.0, 16.7],
    [8.5, 8.7, 8.4, 9.0, 9.2, 9.5, 9.3],
])


print("Dimensiones:", consumo.ndim)    # 2 (filas y columnas)
print("Forma:", consumo.shape)    # (10, 7) → 10 filas y 7 columnas
print("Tipo de datos:", consumo.dtype)    # float64 (números decimales)
print("Consumo primer hogar:", consumo[0])    # Todos los datos de la fila 0
print("Consumo el miércoles (día 3):", consumo[:, 2])    # Todos los datos de la columna 2

# Promedio de consumo por hogar
promedio_por_hogar = np.mean(consumo, axis=1)

# Promedio de consumo diario de todos los hogares 
promedio_por_dia = np.mean(consumo, axis=0)

# Suma total de consumo en la semana de los 10 hogares
total_consumo = np.sum(consumo)

print(promedio_por_hogar)
print(promedio_por_dia)
print(total_consumo)

# máximo por hogar
maximos = np.max(consumo, axis=1)

# Mínimo por día 
minimos = np.min(consumo, axis=0)

# Desviación estándar global
desviacion = np.std(consumo)

print(maximos)
print(minimos)
print(f"DESVIACIÓN ESTANDAR GLOBAL: {desviacion}")

# Suma de consumo por hogar (semana)
consumo_total_hogar = np.sum(consumo, axis=1)

# Índice del hogar con mayor consumo total
hogar_mayor_consumo = np.argmax(consumo_total_hogar)

# Índice del hogar con menor consumo total
hogar_mas_eficiente = np.argmin(consumo_total_hogar)

print("Consumo total por hogar: ", consumo_total_hogar)
print("Hogar con mayor consumo: ", hogar_mayor_consumo)
print("Hogar más eficiente: ", hogar_mas_eficiente)

# Suma por hogar (semana)
consumo_total_hogar = np.sum(consumo, axis=1)
print(f"Consumo total de cada hogar durante la semana: {consumo_total_hogar}")

# Compara cada hogar con un valor mayor a 100
altos = consumo_total_hogar > 100
# Filtrando hogares que cumplen la condición:
consumo_mayor_100 = np.where(altos)[0]

print(f"ids de hogares con consumo mayor a 100: {consumo_mayor_100}")

# Aplicando normalización MinMax al conjunto de datos
consumo_normalizado = (consumo - consumo.min()) / (consumo.max() - consumo.min())

# Resultado
print(consumo_normalizado)


## CUESTIONARIO
# 1
consumo_viernes = consumo[4,4]
print(f"CONSUMO DE DÍA VIERNES: {consumo_viernes}")

# 2 
consumo_domingo = consumo[-3:, 6]
print(f"CONSUMO DE LOS ÚLTIMOS HOGARES EL DÍA DOMINGO: {consumo_domingo}")

# 3
# Calcula el promedio de consumo los fines de semana (sábado y domingo, columnas 5 y 6).
promedio_fines = np.mean(consumo[:, [5,6]])
print(f"PROMEDIO DE CONSUMO LOS FINES DE SEMANA: {promedio_fines}")

# 4. 
# ¿Qué día de la semana tiene la mayor desviación estándar entre hogares? Explica qué indica esto.
desviacion_por_dia = np.std(consumo, axis=0)
dia_mayor_desviacion = np.argmax(desviacion_por_dia)
dias_semana = ["Lunes", "Martes", "Miércoles", "Jueves", "Viernes", "Sábado", "Domingo"]
print(f"DIA CON MAYOR DESVIACIÓN: {dias_semana[dia_mayor_desviacion]}")
# La desviación estandar significa que los datos obtenidos del día sabado varian más entre cada uno, son menos regulares, por ello existe una desviación.
# print(desviacion_por_dia)

# 5
# Identifica los 3 hogares con menor consumo total durante la semana. Muestra sus índices y valores.
indices_menor_consumo = np.argsort(consumo_total_hogar)[:3]
valores_menor_consumo = consumo_total_hogar[indices_menor_consumo]

# print("Índices menor consumo total:", indices_menor_consumo)
print("VALORES DE MENOR CONSUMO TOTAL DE LOS HOGARES", valores_menor_consumo)


# # 6 
# Si el hogar 3 aumenta su consumo en un 10% cada día, ¿cuál sería su nuevo consumo total semanal?
consumo_hogar3 = consumo[3]
consumo_hogar3_aumentado = consumo_hogar3 * 1.10
nuevo_total_hogar3 = np.sum(consumo_hogar3_aumentado)

print(f"NUEVO CONSUMO TOTAL DEL 10%: {nuevo_total_hogar3}")