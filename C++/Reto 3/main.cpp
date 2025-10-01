// main.cpp
// Sistema de Gestión de Biblioteca Escolar
// Fase 3 — Implementación en C++ (sin librerías externas)
// Autor: Luis German Dueñas Bernal
// Docente: José Montalvo
// Carné: KEY_000019
// Materia: Programación Orientada a Objetos
//
// Compilar: g++ -std=c++17 -O2 -o biblioteca main.cpp
// Ejecutar: ./biblioteca
//
// Notas de persistencia:
// - Se guardan archivos CSV simples separados por comas.
// - Para evitar problemas con comas en textos, al guardar se reemplazan por punto y coma ';'.
// - Las fechas se manejan como string (formato libre, ej. 2025-09-30).

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <limits>
#include <unordered_map>

using namespace std;



static inline string sanitize(const string& s) {

    string out = s;
    for (char& c : out) if (c == ',') c = ';';
    return out;
}

static inline string desanitize(const string& s) {

    string out = s;
    for (char& c : out) if (c == ';') c = ',';
    return out;
}

static inline vector<string> splitCSV(const string& line) {

    vector<string> parts;
    string cur;
    stringstream ss(line);
    while (getline(ss, cur, ',')) parts.push_back(cur);
    return parts;
}

static inline string trim(const string& s) {
    size_t a = s.find_first_not_of(" \t\r\n");
    if (a == string::npos) return "";
    size_t b = s.find_last_not_of(" \t\r\n");
    return s.substr(a, b - a + 1);
}

static inline void clearInput() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

static inline bool toBool(const string& s) {
    return (s == "1" || s == "true" || s == "True" || s == "TRUE");
}

static inline string boolStr(bool b) { return b ? "1" : "0"; }


struct Autor {
    int id_autor;
    string nombre;
    string nacionalidad;
};

struct Libro {
    int id_libro;
    string titulo;
    string isbn;
    int anio_publicacion;
    int id_autor;     
    bool disponible;  
};

struct Estudiante {
    int id_estudiante;
    string nombre;
    string grado;
};

struct Prestamo {
    int id_prestamo;
    int id_libro;         
    int id_estudiante;    
    string fecha_prestamo;
    string fecha_devolucion; 
};



class BibliotecaDB {
public:
    vector<Autor> autores;
    vector<Libro> libros;
    vector<Estudiante> estudiantes;
    vector<Prestamo> prestamos;


    int idxAutorById(int id) const {
        for (size_t i = 0; i < autores.size(); ++i) if (autores[i].id_autor == id) return (int)i;
        return -1;
    }
    int idxLibroById(int id) const {
        for (size_t i = 0; i < libros.size(); ++i) if (libros[i].id_libro == id) return (int)i;
        return -1;
    }
    int idxEstudianteById(int id) const {
        for (size_t i = 0; i < estudiantes.size(); ++i) if (estudiantes[i].id_estudiante == id) return (int)i;
        return -1;
    }
    int idxPrestamoById(int id) const {
        for (size_t i = 0; i < prestamos.size(); ++i) if (prestamos[i].id_prestamo == id) return (int)i;
        return -1;
    }
    int findAutorIdByNombreExacto(const string& nombre) const {
        for (const auto& a : autores) if (a.nombre == nombre) return a.id_autor;
        return -1;
    }
    bool isbnExiste(const string& isbn, int except_libro_id = -1) const {
        for (const auto& l : libros) if (l.isbn == isbn && l.id_libro != except_libro_id) return true;
        return false;
    }
    bool libroTienePrestamoActivo(int id_libro) const {
        for (const auto& p : prestamos) {
            if (p.id_libro == id_libro && trim(p.fecha_devolucion).empty()) return true;
        }
        return false;
    }
    void recalcularDisponiblesPorPrestamos() {
        for (auto& l : libros) {
            l.disponible = !libroTienePrestamoActivo(l.id_libro);
        }
    }


    bool agregarAutor(const Autor& a) {
        if (idxAutorById(a.id_autor) != -1) {
            cout << "Error: id_autor duplicado.\n";
            return false;
        }
        autores.push_back(a);
        guardarAutores();
        return true;
    }
    bool actualizarAutor(int id, const string& nombre, const string& nacionalidad) {
        int i = idxAutorById(id);
        if (i == -1) { cout << "Autor no encontrado.\n"; return false; }
        autores[i].nombre = nombre;
        autores[i].nacionalidad = nacionalidad;
        guardarAutores();
        return true;
    }
    bool eliminarAutor(int id) {
 
        for (const auto& l : libros) {
            if (l.id_autor == id) {
                cout << "No se puede eliminar autor: tiene libros asociados.\n";
                return false;
            }
        }
        int i = idxAutorById(id);
        if (i == -1) { cout << "Autor no encontrado.\n"; return false; }
        autores.erase(autores.begin() + i);
        guardarAutores();
        return true;
    }
    void listarAutores() const {
        cout << "\n-- AUTORES --\n";
        for (const auto& a : autores) {
            cout << "ID: " << a.id_autor
                 << " | Nombre: " << a.nombre
                 << " | Nacionalidad: " << a.nacionalidad << "\n";
        }
    }


    bool agregarLibro(Libro l) {
        if (idxLibroById(l.id_libro) != -1) { cout << "Error: id_libro duplicado.\n"; return false; }
        if (idxAutorById(l.id_autor) == -1) { cout << "Error: id_autor no existe.\n"; return false; }
        if (isbnExiste(l.isbn)) { cout << "Error: ISBN ya existe.\n"; return false; }
        l.disponible = true;
        libros.push_back(l);
        guardarLibros();
        return true;
    }
    bool actualizarLibro(int id, const string& titulo, const string& isbn, int anio, int id_autor_nuevo) {
        int i = idxLibroById(id);
        if (i == -1) { cout << "Libro no encontrado.\n"; return false; }
        if (idxAutorById(id_autor_nuevo) == -1) { cout << "id_autor no existe.\n"; return false; }
        if (isbnExiste(isbn, id)) { cout << "ISBN ya existe en otro libro.\n"; return false; }
        libros[i].titulo = titulo;
        libros[i].isbn = isbn;
        libros[i].anio_publicacion = anio;
        libros[i].id_autor = id_autor_nuevo;
        guardarLibros();
        return true;
    }
    bool eliminarLibro(int id) {

        if (libroTienePrestamoActivo(id)) {
            cout << "No se puede eliminar: libro con préstamo activo.\n";
            return false;
        }
        int i = idxLibroById(id);
        if (i == -1) { cout << "Libro no encontrado.\n"; return false; }

        libros.erase(libros.begin() + i);
        guardarLibros();
        return true;
    }
    void listarLibros() const {
        cout << "\n-- LIBROS --\n";
        for (const auto& l : libros) {
            string autorNombre = "(desconocido)";
            int ia = idxAutorById(l.id_autor);
            if (ia != -1) autorNombre = autores[ia].nombre;
            cout << "ID: " << l.id_libro
                 << " | Titulo: " << l.titulo
                 << " | ISBN: " << l.isbn
                 << " | Anio: " << l.anio_publicacion
                 << " | Autor: " << autorNombre
                 << " | Disponible: " << (l.disponible ? "Si" : "No")
                 << "\n";
        }
    }


    bool agregarEstudiante(const Estudiante& e) {
        if (idxEstudianteById(e.id_estudiante) != -1) { cout << "Error: id_estudiante duplicado.\n"; return false; }
        estudiantes.push_back(e);
        guardarEstudiantes();
        return true;
    }
    bool actualizarEstudiante(int id, const string& nombre, const string& grado) {
        int i = idxEstudianteById(id);
        if (i == -1) { cout << "Estudiante no encontrado.\n"; return false; }
        estudiantes[i].nombre = nombre;
        estudiantes[i].grado = grado;
        guardarEstudiantes();
        return true;
    }
    bool eliminarEstudiante(int id) {

        for (const auto& p : prestamos) {
            if (p.id_estudiante == id && trim(p.fecha_devolucion).empty()) {
                cout << "No se puede eliminar: estudiante tiene préstamo activo.\n";
                return false;
            }
        }
        int i = idxEstudianteById(id);
        if (i == -1) { cout << "Estudiante no encontrado.\n"; return false; }
        estudiantes.erase(estudiantes.begin() + i);
        guardarEstudiantes();
        return true;
    }
    void listarEstudiantes() const {
        cout << "\n-- ESTUDIANTES --\n";
        for (const auto& e : estudiantes) {
            cout << "ID: " << e.id_estudiante
                 << " | Nombre: " << e.nombre
                 << " | Grado: " << e.grado << "\n";
        }
    }


    bool registrarPrestamo(Prestamo p) {
        if (idxPrestamoById(p.id_prestamo) != -1) { cout << "Error: id_prestamo duplicado.\n"; return false; }
        if (idxLibroById(p.id_libro) == -1) { cout << "Error: id_libro no existe.\n"; return false; }
        if (idxEstudianteById(p.id_estudiante) == -1) { cout << "Error: id_estudiante no existe.\n"; return false; }

        if (libroTienePrestamoActivo(p.id_libro)) {
            cout << "No se puede prestar: ya existe un préstamo activo de este libro.\n";
            return false;
        }

        int il = idxLibroById(p.id_libro);
        libros[il].disponible = false;

        prestamos.push_back(p);
        guardarPrestamos();
        guardarLibros();
        return true;
    }
    bool actualizarPrestamo(int id, const string& fecha_prestamo_nueva, const string& fecha_devolucion_nueva) {
        int ip = idxPrestamoById(id);
        if (ip == -1) { cout << "Prestamo no encontrado.\n"; return false; }
        prestamos[ip].fecha_prestamo = fecha_prestamo_nueva;
        prestamos[ip].fecha_devolucion = fecha_devolucion_nueva;

        int il = idxLibroById(prestamos[ip].id_libro);
        if (il != -1) libros[il].disponible = !trim(fecha_devolucion_nueva).empty();
        guardarPrestamos();
        guardarLibros();
        return true;
    }
    bool eliminarPrestamo(int id) {
        int ip = idxPrestamoById(id);
        if (ip == -1) { cout << "Prestamo no encontrado.\n"; return false; }
        if (trim(prestamos[ip].fecha_devolucion).empty()) {
            cout << "No se puede eliminar: prestamo activo. Debe cerrarlo primero.\n";
            return false;
        }
        prestamos.erase(prestamos.begin() + ip);
        guardarPrestamos();
        return true;
    }
    void listarPrestamos() const {
        cout << "\n-- PRESTAMOS --\n";
        for (const auto& p : prestamos) {
            string titulo = "(libro desconocido)";
            string estNombre = "(estudiante desconocido)";
            int il = idxLibroById(p.id_libro);
            if (il != -1) titulo = libros[il].titulo;
            int ie = idxEstudianteById(p.id_estudiante);
            if (ie != -1) estNombre = estudiantes[ie].nombre;
            cout << "ID: " << p.id_prestamo
                 << " | Libro: " << titulo
                 << " | Estudiante: " << estNombre
                 << " | Prestamo: " << p.fecha_prestamo
                 << " | Devolucion: " << (trim(p.fecha_devolucion).empty() ? "(activo)" : p.fecha_devolucion) << "\n";
        }
    }
    bool devolverLibro(int id_prestamo, const string& fecha_devolucion) {
        int ip = idxPrestamoById(id_prestamo);
        if (ip == -1) { cout << "Prestamo no encontrado.\n"; return false; }
        if (!trim(prestamos[ip].fecha_devolucion).empty()) {
            cout << "Este prestamo ya fue cerrado.\n"; return false;
        }
        prestamos[ip].fecha_devolucion = fecha_devolucion;


        int il = idxLibroById(prestamos[ip].id_libro);
        if (il != -1) libros[il].disponible = true;

        guardarPrestamos();
        guardarLibros();
        return true;
    }


    void listarPrestamosPorEstudiante(int id_estudiante) const {
        int ie = idxEstudianteById(id_estudiante);
        if (ie == -1) { cout << "Estudiante no encontrado.\n"; return; }
        cout << "\n-- Prestamos del estudiante: " << estudiantes[ie].nombre << " --\n";
        for (const auto& p : prestamos) {
            if (p.id_estudiante == id_estudiante) {
                string titulo = "(libro desconocido)";
                int il = idxLibroById(p.id_libro);
                if (il != -1) titulo = libros[il].titulo;
                cout << "Prestamo ID: " << p.id_prestamo
                     << " | Libro: " << titulo
                     << " | Fecha prestamo: " << p.fecha_prestamo
                     << " | Fecha devolucion: " << (trim(p.fecha_devolucion).empty() ? "(activo)" : p.fecha_devolucion)
                     << "\n";
            }
        }
    }
    void autorConMasLibros() const {
        unordered_map<int, int> cuenta;
        for (const auto& l : libros) cuenta[l.id_autor]++;
        if (cuenta.empty()) { cout << "No hay libros cargados.\n"; return; }
        int bestCount = 0;
        for (auto& kv : cuenta) bestCount = max(bestCount, kv.second);
        cout << "Autores con mas libros (" << bestCount << "):\n";
        for (auto& kv : cuenta) {
            if (kv.second == bestCount) {
                string nombre = "(desconocido)";
                int ia = idxAutorById(kv.first);
                if (ia != -1) nombre = autores[ia].nombre;
                cout << "- " << nombre << "\n";
            }
        }
    }

    void guardarAutores() const {
        ofstream f("autores.txt");
        for (const auto& a : autores) {
            f << a.id_autor << ","
              << sanitize(a.nombre) << ","
              << sanitize(a.nacionalidad) << "\n";
        }
    }
    void guardarLibros() const {
        ofstream f("libros.txt");
        for (const auto& l : libros) {
            f << l.id_libro << ","
              << sanitize(l.titulo) << ","
              << sanitize(l.isbn) << ","
              << l.anio_publicacion << ","
              << l.id_autor << ","
              << boolStr(l.disponible) << "\n";
        }
    }
    void guardarEstudiantes() const {
        ofstream f("estudiantes.txt");
        for (const auto& e : estudiantes) {
            f << e.id_estudiante << ","
              << sanitize(e.nombre) << ","
              << sanitize(e.grado) << "\n";
        }
    }
    void guardarPrestamos() const {
        ofstream f("prestamos.txt");
        for (const auto& p : prestamos) {
            f << p.id_prestamo << ","
              << p.id_libro << ","
              << p.id_estudiante << ","
              << sanitize(p.fecha_prestamo) << ","
              << sanitize(p.fecha_devolucion) << "\n";
        }
    }

    void cargarAutores() {
        autores.clear();
        ifstream f("autores.txt");
        string line;
        while (getline(f, line)) {
            auto v = splitCSV(line);
            if (v.size() < 3) continue;
            Autor a;
            a.id_autor = stoi(v[0]);
            a.nombre = desanitize(v[1]);
            a.nacionalidad = desanitize(v[2]);
            autores.push_back(a);
        }
    }
    void cargarLibros() {
        libros.clear();
        ifstream f("libros.txt");
        string line;
        while (getline(f, line)) {
            auto v = splitCSV(line);
            if (v.size() < 6) continue;
            Libro l;
            l.id_libro = stoi(v[0]);
            l.titulo = desanitize(v[1]);
            l.isbn = desanitize(v[2]);
            l.anio_publicacion = stoi(v[3]);
            l.id_autor = stoi(v[4]);
            l.disponible = toBool(v[5]);
            libros.push_back(l);
        }
    }
    void cargarEstudiantes() {
        estudiantes.clear();
        ifstream f("estudiantes.txt");
        string line;
        while (getline(f, line)) {
            auto v = splitCSV(line);
            if (v.size() < 3) continue;
            Estudiante e;
            e.id_estudiante = stoi(v[0]);
            e.nombre = desanitize(v[1]);
            e.grado = desanitize(v[2]);
            estudiantes.push_back(e);
        }
    }
    void cargarPrestamos() {
        prestamos.clear();
        ifstream f("prestamos.txt");
        string line;
        while (getline(f, line)) {
            auto v = splitCSV(line);
            if (v.size() < 5) continue;
            Prestamo p;
            p.id_prestamo = stoi(v[0]);
            p.id_libro = stoi(v[1]);
            p.id_estudiante = stoi(v[2]);
            p.fecha_prestamo = desanitize(v[3]);
            p.fecha_devolucion = desanitize(v[4]);
            prestamos.push_back(p);
        }
    }

    void guardarDatos() const {
        guardarAutores();
        guardarLibros();
        guardarEstudiantes();
        guardarPrestamos();
    }
    void cargarDatos() {
        cargarAutores();
        cargarLibros();
        cargarEstudiantes();
        cargarPrestamos();
  
        recalcularDisponiblesPorPrestamos();
        guardarLibros(); 
    }
};


int leerEntero(const string& prompt) {
    cout << prompt;
    int x;
    while (!(cin >> x)) {
        cout << "Entrada invalida. Intenta de nuevo: ";
        clearInput();
    }
    clearInput();
    return x;
}

string leerLinea(const string& prompt) {
    cout << prompt;
    string s;
    getline(cin, s);
    return s;
}



void menuAgregarAutor(BibliotecaDB& db) {
    Autor a;
    a.id_autor = leerEntero("ID Autor: ");
    a.nombre = leerLinea("Nombre: ");
    a.nacionalidad = leerLinea("Nacionalidad: ");
    if (db.agregarAutor(a)) cout << "Autor agregado.\n";
}

void menuActualizarAutor(BibliotecaDB& db) {
    int id = leerEntero("ID Autor a actualizar: ");
    string nombre = leerLinea("Nuevo nombre: ");
    string nac = leerLinea("Nueva nacionalidad: ");
    if (db.actualizarAutor(id, nombre, nac)) cout << "Autor actualizado.\n";
}

void menuEliminarAutor(BibliotecaDB& db) {
    int id = leerEntero("ID Autor a eliminar: ");
    if (db.eliminarAutor(id)) cout << "Autor eliminado.\n";
}

void menuAgregarLibro(BibliotecaDB& db) {
    Libro l;
    l.id_libro = leerEntero("ID Libro: ");
    l.titulo = leerLinea("Titulo: ");
    l.isbn = leerLinea("ISBN: ");
    l.anio_publicacion = leerEntero("Anio de publicacion: ");


    string nombreAutor = leerLinea("Nombre del Autor (exacto): ");
    int idAutor = db.findAutorIdByNombreExacto(nombreAutor);
    if (idAutor == -1) {
        cout << "Autor no encontrado. Debes crearlo primero en 'Agregar Autor'.\n";
        return;
    }
    l.id_autor = idAutor;

    if (db.agregarLibro(l)) cout << "Libro agregado.\n";
}

void menuActualizarLibro(BibliotecaDB& db) {
    int id = leerEntero("ID Libro a actualizar: ");
    string titulo = leerLinea("Nuevo titulo: ");
    string isbn = leerLinea("Nuevo ISBN: ");
    int anio = leerEntero("Nuevo anio: ");
    string nombreAutor = leerLinea("Nombre del Autor (exacto): ");
    int idAutor = db.findAutorIdByNombreExacto(nombreAutor);
    if (idAutor == -1) { cout << "Autor no encontrado.\n"; return; }
    if (db.actualizarLibro(id, titulo, isbn, anio, idAutor)) cout << "Libro actualizado.\n";
}

void menuEliminarLibro(BibliotecaDB& db) {
    int id = leerEntero("ID Libro a eliminar: ");
    if (db.eliminarLibro(id)) cout << "Libro eliminado.\n";
}

void menuAgregarEstudiante(BibliotecaDB& db) {
    Estudiante e;
    e.id_estudiante = leerEntero("ID Estudiante: ");
    e.nombre = leerLinea("Nombre: ");
    e.grado = leerLinea("Grado (ej. '2o Bachillerato'): ");
    if (db.agregarEstudiante(e)) cout << "Estudiante agregado.\n";
}

void menuActualizarEstudiante(BibliotecaDB& db) {
    int id = leerEntero("ID Estudiante a actualizar: ");
    string nombre = leerLinea("Nuevo nombre: ");
    string grado = leerLinea("Nuevo grado: ");
    if (db.actualizarEstudiante(id, nombre, grado)) cout << "Estudiante actualizado.\n";
}

void menuEliminarEstudiante(BibliotecaDB& db) {
    int id = leerEntero("ID Estudiante a eliminar: ");
    if (db.eliminarEstudiante(id)) cout << "Estudiante eliminado.\n";
}

void menuRegistrarPrestamo(BibliotecaDB& db) {
    Prestamo p;
    p.id_prestamo = leerEntero("ID Prestamo: ");
    p.id_libro = leerEntero("ID Libro: ");
    p.id_estudiante = leerEntero("ID Estudiante: ");
    p.fecha_prestamo = leerLinea("Fecha de prestamo (YYYY-MM-DD u otro): ");
    p.fecha_devolucion = ""; // activo
    if (db.registrarPrestamo(p)) cout << "Prestamo registrado.\n";
}

void menuActualizarPrestamo(BibliotecaDB& db) {
    int id = leerEntero("ID Prestamo a actualizar: ");
    string fp = leerLinea("Nueva fecha prestamo: ");
    string fd = leerLinea("Nueva fecha devolucion (vacío si activo): ");
    if (db.actualizarPrestamo(id, fp, fd)) cout << "Prestamo actualizado.\n";
}

void menuEliminarPrestamo(BibliotecaDB& db) {
    int id = leerEntero("ID Prestamo a eliminar: ");
    if (db.eliminarPrestamo(id)) cout << "Prestamo eliminado.\n";
}

void menuDevolverLibro(BibliotecaDB& db) {
    int idp = leerEntero("ID Prestamo a cerrar: ");
    string fdev = leerLinea("Fecha de devolucion: ");
    if (db.devolverLibro(idp, fdev)) cout << "Prestamo cerrado y libro disponible.\n";
}

void menuPrestamosPorEstudiante(BibliotecaDB& db) {
    int id = leerEntero("ID Estudiante: ");
    db.listarPrestamosPorEstudiante(id);
}

void menuAutorMasLibros(BibliotecaDB& db) {
    db.autorConMasLibros();
}



int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    BibliotecaDB db;
    db.cargarDatos();

    while (true) {
        cout << "\n===== MENU BIBLIOTECA =====\n";
        cout << "1. Agregar Autor\n";
        cout << "2. Listar Autores\n";
        cout << "3. Actualizar Autor\n";
        cout << "4. Eliminar Autor\n";
        cout << "5. Agregar Libro (autor por NOMBRE)\n";
        cout << "6. Listar Libros\n";
        cout << "7. Actualizar Libro\n";
        cout << "8. Eliminar Libro\n";
        cout << "9. Agregar Estudiante\n";
        cout << "10. Listar Estudiantes\n";
        cout << "11. Actualizar Estudiante\n";
        cout << "12. Eliminar Estudiante\n";
        cout << "13. Registrar Prestamo\n";
        cout << "14. Devolver Libro\n";
        cout << "15. Listar prestamos por Estudiante\n";
        cout << "16. Autor con mas libros\n";
        cout << "17. Listar Todos los Prestamos\n";
        cout << "18. Actualizar Prestamo\n";
        cout << "19. Eliminar Prestamo (solo cerrados)\n";
        cout << "0. Guardar y salir\n";
        cout << "Opcion: ";

        int opc;
        if (!(cin >> opc)) {
            cout << "Entrada invalida.\n";
            clearInput();
            continue;
        }
        clearInput();

        switch (opc) {
            case 1:  menuAgregarAutor(db); break;
            case 2:  db.listarAutores(); break;
            case 3:  menuActualizarAutor(db); break;
            case 4:  menuEliminarAutor(db); break;
            case 5:  menuAgregarLibro(db); break;
            case 6:  db.listarLibros(); break;
            case 7:  menuActualizarLibro(db); break;
            case 8:  menuEliminarLibro(db); break;
            case 9:  menuAgregarEstudiante(db); break;
            case 10: db.listarEstudiantes(); break;
            case 11: menuActualizarEstudiante(db); break;
            case 12: menuEliminarEstudiante(db); break;
            case 13: menuRegistrarPrestamo(db); break;
            case 14: menuDevolverLibro(db); break;
            case 15: menuPrestamosPorEstudiante(db); break;
            case 16: menuAutorMasLibros(db); break;
            case 17: db.listarPrestamos(); break;
            case 18: menuActualizarPrestamo(db); break;
            case 19: menuEliminarPrestamo(db); break;
            case 0:
                db.guardarDatos();
                cout << "Datos guardados. Adios!\n";
                return 0;
            default:
                cout << "Opcion no valida.\n";
        }
    }
}