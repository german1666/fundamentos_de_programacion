#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <limits>
#include <cctype>

class Libro {
public:
    std::string titulo;
    std::string autor;
    int añoPublicacion;
    bool estaDisponible;

    Libro() : añoPublicacion(0), estaDisponible(true) {}
    Libro(std::string t, std::string a, int año)
        : titulo(std::move(t)), autor(std::move(a)), añoPublicacion(año), estaDisponible(true) {}

    void mostrarDetallesCompletos() const {
        std::cout << "--- Detalles del libro ---\n";
        std::cout << "Titulo: " << titulo << "\n";
        std::cout << "Autor: " << autor << "\n";
        std::cout << "Año: " << añoPublicacion << "\n";
        std::cout << "Disponible: " << (estaDisponible ? "Si" : "No") << "\n";
    }
};

class Usuario {
public:
    std::string nombre;
    std::vector<std::string> titulosPrestados;

    explicit Usuario(std::string n = "") : nombre(std::move(n)) {}

    bool tieneLibro(const std::string& titulo) const {
        return std::find(titulosPrestados.begin(), titulosPrestados.end(), titulo) != titulosPrestados.end();
    }

    void prestar(const std::string& titulo) {
        if (!tieneLibro(titulo)) titulosPrestados.push_back(titulo);
    }

    void devolver(const std::string& titulo) {
        auto it = std::remove(titulosPrestados.begin(), titulosPrestados.end(), titulo);
        if (it != titulosPrestados.end()) titulosPrestados.erase(it, titulosPrestados.end());
    }
};

class Biblioteca {
private:
    std::vector<Libro> coleccion;
    std::vector<Usuario> usuarios;

    static std::string aMinusculas(std::string s) {
        for (char& c : s) c = static_cast<char>(std::tolower(static_cast<unsigned char>(c)));
        return s;
    }

public:
    void agregarLibro(const Libro& nuevoLibro) {
        for (const auto& l : coleccion) {
            if (aMinusculas(l.titulo) == aMinusculas(nuevoLibro.titulo)) {
                std::cout << "Ya existe un libro con el titulo \"" << nuevoLibro.titulo << "\"\n";
                return;
            }
        }
        coleccion.push_back(nuevoLibro);
        std::cout << "Libro agregado: " << nuevoLibro.titulo << "\n";
    }

    void mostrarInventario() const {
        if (coleccion.empty()) {
            std::cout << "No hay libros en la biblioteca.\n";
            return;
        }
        for (const auto& l : coleccion) {
            l.mostrarDetallesCompletos();
            std::cout << "---------------------\n";
        }
    }

    Libro* buscarLibro(const std::string& tituloBuscado) {
        std::string q = aMinusculas(tituloBuscado);
        for (auto& l : coleccion) {
            if (aMinusculas(l.titulo) == q) return &l;
        }
        return nullptr;
    }

    Usuario* buscarUsuario(const std::string& nombre) {
        std::string q = aMinusculas(nombre);
        for (auto& u : usuarios) {
            if (aMinusculas(u.nombre) == q) return &u;
        }
        return nullptr;
    }

    void registrarUsuario(const std::string& nombre) {
        if (buscarUsuario(nombre)) {
            std::cout << "El usuario \"" << nombre << "\" ya existe.\n";
            return;
        }
        usuarios.emplace_back(nombre);
        std::cout << "Usuario registrado: " << nombre << "\n";
    }

    void mostrarUsuarios() const {
        if (usuarios.empty()) {
            std::cout << "No hay usuarios registrados.\n";
            return;
        }
        for (const auto& u : usuarios) {
            std::cout << "Usuario: " << u.nombre << "\n";
            std::cout << "Prestamos: ";
            if (u.titulosPrestados.empty()) {
                std::cout << "(ninguno)";
            } else {
                for (size_t i = 0; i < u.titulosPrestados.size(); ++i) {
                    std::cout << u.titulosPrestados[i];
                    if (i + 1 < u.titulosPrestados.size()) std::cout << ", ";
                }
            }
            std::cout << "\n---------------------\n";
        }
    }

    void prestarLibro(const std::string& tituloPrestamo, const std::string& nombreUsuario) {
        Libro* l = buscarLibro(tituloPrestamo);
        if (!l) {
            std::cout << "El libro no existe en la biblioteca.\n";
            return;
        }
        if (!l->estaDisponible) {
            std::cout << "El libro ya esta prestado.\n";
            return;
        }
        Usuario* u = buscarUsuario(nombreUsuario);
        if (!u) {
            std::cout << "El usuario no esta registrado.\n";
            return;
        }
        l->estaDisponible = false;
        u->prestar(l->titulo);
        std::cout << "Se presto el libro: " << l->titulo << " a " << u->nombre << "\n";
    }

    void devolverLibro(const std::string& tituloDevolucion) {
        Libro* l = buscarLibro(tituloDevolucion);
        if (!l) {
            std::cout << "El libro no existe en la biblioteca.\n";
            return;
        }
        if (l->estaDisponible) {
            std::cout << "El libro ya estaba disponible.\n";
            return;
        }
        l->estaDisponible = true;
        for (auto& u : usuarios) {
            if (u.tieneLibro(l->titulo)) {
                u.devolver(l->titulo);
                std::cout << "Se devolvio el libro: " << l->titulo << " por " << u.nombre << "\n";
                return;
            }
        }
        std::cout << "Libro marcado disponible, pero no se encontro usuario que lo tuviera.\n";
    }

    bool guardar(const std::string& archivoLibros = "libros.txt",
                 const std::string& archivoUsuarios = "usuarios.txt") const {
        std::ofstream fb(archivoLibros);
        if (!fb) { std::cout << "No se pudo abrir " << archivoLibros << " para escritura.\n"; return false; }
        for (const auto& l : coleccion) {
            fb << l.titulo << "|" << l.autor << "|" << l.añoPublicacion << "|" << (l.estaDisponible ? 1 : 0) << "\n";
        }
        fb.close();

        std::ofstream fu(archivoUsuarios);
        if (!fu) { std::cout << "No se pudo abrir " << archivoUsuarios << " para escritura.\n"; return false; }
        for (const auto& u : usuarios) {
            fu << u.nombre << "|";
            for (size_t i = 0; i < u.titulosPrestados.size(); ++i) {
                fu << u.titulosPrestados[i];
                if (i + 1 < u.titulosPrestados.size()) fu << ",";
            }
            fu << "\n";
        }
        fu.close();

        std::cout << "Estado guardado en \"" << archivoLibros << "\" y \"" << archivoUsuarios << "\".\n";
        return true;
    }

    bool cargar(const std::string& archivoLibros = "libros.txt",
                const std::string& archivoUsuarios = "usuarios.txt") {
        std::ifstream fb(archivoLibros);
        if (!fb) { std::cout << "No se pudo abrir " << archivoLibros << " para lectura.\n"; return false; }

        coleccion.clear();
        std::string linea;
        while (std::getline(fb, linea)) {
            if (linea.empty()) continue;
            std::stringstream ss(linea);
            std::string t, a, añoStr, dispStr;

            if (!std::getline(ss, t, '|')) continue;
            if (!std::getline(ss, a, '|')) continue;
            if (!std::getline(ss, añoStr, '|')) continue;
            if (!std::getline(ss, dispStr, '|')) continue;

            Libro l;
            l.titulo = t;
            l.autor = a;
            l.añoPublicacion = std::stoi(añoStr);
            l.estaDisponible = (dispStr == "1");
            coleccion.push_back(l);
        }
        fb.close();

        std::ifstream fu(archivoUsuarios);
        if (!fu) { std::cout << "No se pudo abrir " << archivoUsuarios << " para lectura.\n"; return false; }

        usuarios.clear();
        while (std::getline(fu, linea)) {
            if (linea.empty()) continue;
            std::stringstream ss(linea);
            std::string nombre, lista;
            if (!std::getline(ss, nombre, '|')) continue;
            std::getline(ss, lista);

            Usuario u(nombre);
            if (!lista.empty()) {
                std::stringstream ls(lista);
                std::string titulo;
                while (std::getline(ls, titulo, ',')) {
                    if (!titulo.empty()) u.titulosPrestados.push_back(titulo);
                }
            }
            usuarios.push_back(u);
        }
        fu.close();

        for (auto& u : usuarios) {
            for (const auto& titulo : u.titulosPrestados) {
                if (Libro* l = buscarLibro(titulo)) l->estaDisponible = false;
            }
        }

        std::cout << "Estado cargado desde archivos.\n";
        return true;
    }
};

static void limpiarEntrada() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

int main() {
    Biblioteca miBiblioteca;
    int opcion = 0;

    Libro libroInicial;
    libroInicial.titulo = "El Hobbit";
    libroInicial.autor = "J.R.R. Tolkien";
    libroInicial.añoPublicacion = 1937;
    miBiblioteca.agregarLibro(libroInicial);

    while (true) {
        std::cout << "\n--- BIBLIOTECA DIGITAL ---\n";
        std::cout << "1. Anadir libro\n";
        std::cout << "2. Mostrar inventario\n";
        std::cout << "3. Prestar libro\n";
        std::cout << "4. Devolver libro\n";
        std::cout << "5. Registrar usuario\n";
        std::cout << "6. Mostrar usuarios\n";
        std::cout << "7. Guardar estado\n";
        std::cout << "8. Cargar estado\n";
        std::cout << "9. Salir\n";
        std::cout << "Seleccione una opcion: ";

        if (!(std::cin >> opcion)) {
            limpiarEntrada();
            std::cout << "Entrada invalida.\n";
            continue;
        }
        limpiarEntrada();

        if (opcion == 1) {
            Libro nuevo;
            std::cout << "Titulo: "; std::getline(std::cin, nuevo.titulo);
            std::cout << "Autor: "; std::getline(std::cin, nuevo.autor);
            std::cout << "Año de publicacion: ";
            if (!(std::cin >> nuevo.añoPublicacion)) { limpiarEntrada(); std::cout << "Año invalido.\n"; continue; }
            limpiarEntrada();
            miBiblioteca.agregarLibro(nuevo);
        } else if (opcion == 2) {
            miBiblioteca.mostrarInventario();
        } else if (opcion == 3) {
            std::string titulo, nombre;
            std::cout << "Titulo a prestar: "; std::getline(std::cin, titulo);
            std::cout << "Nombre del usuario: "; std::getline(std::cin, nombre);
            miBiblioteca.prestarLibro(titulo, nombre);
        } else if (opcion == 4) {
            std::string titulo;
            std::cout << "Titulo a devolver: "; std::getline(std::cin, titulo);
            miBiblioteca.devolverLibro(titulo);
        } else if (opcion == 5) {
            std::string nombre;
            std::cout << "Nombre del usuario a registrar: "; std::getline(std::cin, nombre);
            miBiblioteca.registrarUsuario(nombre);
        } else if (opcion == 6) {
            miBiblioteca.mostrarUsuarios();
        } else if (opcion == 7) {
            miBiblioteca.guardar();
        } else if (opcion == 8) {
            miBiblioteca.cargar();
        } else if (opcion == 9) {
            std::cout << "Saliendo...\n";
            break;
        } else {
            std::cout << "Opcion invalida.\n";
        }
    }

    return 0;
}

