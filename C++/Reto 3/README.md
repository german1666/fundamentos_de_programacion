# Sistema de Gestión de Biblioteca Escolar  
### Proyecto académico — Programación Orientada a Objetos

## Datos del estudiante
- **Estudiante:** Luis German Dueñas Bernal  
- **Carné:** KEY_000019  
- **Docente:** José Montalvo  
- **Materia:** Programación Orientada a Objetos  
- **Institución:** Key Institute — El Salvador  


## Descripción general
Este proyecto implementa un **sistema de gestión de biblioteca escolar** en tres fases:  
1. **Diseño conceptual** mediante diagrama ER.  
2. **Normalización** hasta la Tercera Forma Normal (3FN).  
3. **Implementación en C++** con `struct`, `vector` y archivos `.txt` para persistencia.  

Integra teoría de bases de datos y práctica en programación, con el objetivo de simular la gestión de autores, libros, estudiantes y préstamos.

## Entregables por fase

### Fase 1 — Diseño (ER)
- Archivo: **Diagrama ER — Biblioteca Escolar.png**  
- Herramienta: dbdiagram.io  
- Contenido:  
  - Entidades: Autor, Libro, Estudiante, Prestamo.  
  - Relaciones:  
    - Autor 1 — N Libro  
    - Libro 1 — N Prestamo  
    - Estudiante 1 — N Prestamo  
  - Restricciones: ISBN único, un préstamo activo por libro.  
- [Ver diagrama en línea](https://dbdiagram.io/d/Diagrama-ER-—-Biblioteca-Escolar-Fase-1-68d3418b7c85fb99610ba822)


### Fase 2 — Normalización
- Archivo: **Normalizacion_Biblioteca_Fase2.pdf**  
- Contenido:  
  - Tablas iniciales (modelo relacional directo del ER).  
  - Explicación de 1FN, 2FN y 3FN con ejemplos de redundancia evitada.  
  - Tablas finales en 3FN:  
    - **Autor(id_autor PK, nombre, nacionalidad)**  
    - **Libro(id_libro PK, titulo, isbn UNIQUE, anio_publicacion, id_autor FK)**  
    - **Estudiante(id_estudiante PK, nombre, grado)**  
    - **Prestamo(id_prestamo PK, id_libro FK, id_estudiante FK, fecha_prestamo, fecha_devolucion)**  


### Fase 3 — Implementación en C++
- Archivo: **main.cpp**  
- Lenguaje: C++17 estándar (sin librerías externas).  
- Estructuras: `struct` para cada entidad, `vector` como tabla en memoria.  
- Persistencia: archivos `.txt` en formato CSV simple.  
- Funcionalidades:  
  - CRUD completo (Autores, Libros, Estudiantes, Prestamos).  
  - Consultas:  
    - Listar préstamos por estudiante.  
    - Autor(es) con más libros registrados.  
  - Reglas de negocio:  
    - IDs únicos.  
    - ISBN único.  
    - Un préstamo activo por libro.  
    - No eliminar entidades con préstamos activos.  

#### Compilación y ejecución
```bash
# Compilar
g++ -std=c++17 -O2 -o biblioteca main.cpp

# Ejecutar
./biblioteca
```

#### Menú principal
```
1.  Agregar Autor
2.  Listar Autores
3.  Actualizar Autor
4.  Eliminar Autor
5.  Agregar Libro (autor por NOMBRE)
6.  Listar Libros
7.  Actualizar Libro
8.  Eliminar Libro
9.  Agregar Estudiante
10. Listar Estudiantes
11. Actualizar Estudiante
12. Eliminar Estudiante
13. Registrar Prestamo
14. Devolver Libro
15. Listar prestamos por Estudiante
16. Autor con mas libros
17. Listar Todos los Prestamos
18. Actualizar Prestamo
19. Eliminar Prestamo (solo cerrados)
0.  Guardar y salir
```


## Conclusión
Con este proyecto se logró:  
- Aplicar la teoría de **modelado de datos** (ER y normalización).  
- Garantizar integridad y evitar redundancias con **3FN**.  
- Desarrollar un sistema funcional en **C++** con persistencia en archivos.  

Este prototipo demuestra cómo los fundamentos de bases de datos y la programación orientada a objetos se integran en un proyecto práctico de gestión escolar.
