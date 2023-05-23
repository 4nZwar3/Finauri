#include <random>
#include <algorithm>
#include "algoritmos.h"
enum OPC {
    STATS = 1,
    PRINT,
    PUSH,
    REMOVE,
    SEARCH,
    SORT,
    EXIT,
};
enum SEARCHERS {
    SEQ = 1,
    BIN,
    SEAXIT
};
enum SORTER {
    PRITN = 1,
    BUBBLE,
    INSERT,
    SHELL,
    SELECT,
    QUICK,
    MERGE,
    SHUFFLE,
    SORXIT
};
template <typename T> void cola_stats(Cola<T>* cola) {
    std::string vacio;
    std::string front;
    std::string back;
    if(cola->is_empty()) {
        vacio = "true";
        front = "empty";
        back = "empty";
    } else {
        vacio = "false";
        front = std::to_string(cola->front());
        back = std::to_string(cola->back());
    }
    std::cout << "empty(): " << vacio << std::endl
              << "size(): " << cola->size() << std::endl
              << "front(): " << front << std::endl
              << "back(): " << back << std::endl;
}
template <typename T> void pusher(Cola<T>* cola) {
    std::cout << "Inserte el valor que desea añadir: ";
    T data;
    std::cin >> data;
    std::cin.ignore();
    std::cout << "\033[2J\033[1;1H";
    cola->push(data);
}
template <typename T> void killer(Cola<T>* cola) {
    if(cola->is_empty()) {
        std::cout << "=> Lista vacía. <=\n";
        return;
    }
    std::cout << "\033[2J\033[1;1H";
    std::cout << "Inserte la posición de el valor que desea borrar: ";
    size_t position;
    std::cin >> position;
    std::cin.ignore();
    if(position > cola->size()) {
        std::cout << "=> Elemento no existente. <=\n";
    }
    cola->erase(--position);
}
template <typename T> void searcher(Cola<T>* cola, size_t method) {
    std::cout << "Inserte el valor que desea buscar: ";
    T data;
    std::cin >> data;
    std::cin.ignore();
    size_t position;
    std::cout << "\033[2J\033[1;1H";
    switch(method) {
        case 0:
            position = sequential_search(cola, cola->size(), data);
            break;
        case 1:
            position = binary_search(cola, cola->size(), data);
            break;
    }
    if(++position > cola->size()) {
        std::cout << "No se encontró <" << data << ">.\n";
        return;
    }
    std::cout << "Se encontró <" << data << "> en la posición [" << position << "].\n";
}
template <typename T> void shuffler(Cola<T>* cola) {
    size_t size = cola->size();
    std::random_device rd;
    std::mt19937 eng(rd());
    T* arr(new T[size]);
    for(size_t i(0); i < size; ++i) {
        arr[i] = cola->operator[](i);
    }
    std::shuffle(arr, arr + size, eng);
    for(size_t i(0); i < size; ++i) {
        cola->operator[](i) = arr[i];
    }
    delete[] arr;
}
template <typename T> void search_menu(Cola<T>* cola) {
    while (true) {
        std::cout << "\n\tMenú de busqueda\n"
                  << SEARCHERS::SEQ << ") Ejecutar busqueda sequencial.\n"
                  << SEARCHERS::BIN << ") Ejecutar busqueda binaria.\n"
                  << SEARCHERS::SEAXIT << ") Regresar.\n"
                  << "Seleccione una opción: ";
        int opc;
        std::cin >> opc;
        std::cin.ignore();
        std::cout << "\033[2J\033[1;1H";
        switch(opc) {
            case SEARCHERS::SEQ:
                searcher(cola, 0);
                break;
            case SEARCHERS::BIN:
                searcher(cola, 1);
                break;
            case SEARCHERS::SEAXIT:
                std::cout << "\033[2J\033[1;1H";
                return;
                break;
            default:
                std::cout << "=> Opción inválida <=\n";
                break;
        }
    }
}
template <typename T> void sort_menu(Cola<T>* cola) {
    while (true) {
        std::cout << "\n\tMenú de organizadores\n"
                  << SORTER::PRITN << ") Imprimir lista.\n"
                  << SORTER::BUBBLE << ") Ejecutar Bubble Sort.\n"
                  << SORTER::INSERT << ") Ejecutar Insertion Sort.\n"
                  << SORTER::SHELL << ") Ejecutar Shell Sort.\n"
                  << SORTER::SELECT << ") Ejecutar Selection Sort.\n"
                  << SORTER::QUICK << ") Ejecutar Quick Sort.\n"
                  << SORTER::MERGE << ") Ejecutar Merge Sort.\n"
                  << SORTER::SHUFFLE << ") Desorganizar lista.\n"
                  << SORTER::SORXIT << ") Regresar.\n"
                  << "Seleccione una opción: ";
        int opc;
        std::cin >> opc;
        std::cin.ignore();
        std::cout << "\033[2J\033[1;1H";
        switch(opc) {
            case SORTER::PRITN:
                cola->print();
                break;
            case SORTER::BUBBLE:
                bubble_sort(cola, cola->size());
                break;
            case SORTER::INSERT:
                insertion_sort(cola, cola->size());
                break;
            case SORTER::SHELL:
                shell_sort(cola, cola->size());
                break;
            case SORTER::SELECT:
                selection_sort(cola, cola->size());
                break;
            case SORTER::QUICK:
                quick_sort(cola, cola->size());
                break;
            case SORTER::MERGE:
                merge_sort(cola, cola->size());
                break;
            case SORTER::SHUFFLE:
                shuffler(cola);
                break;
            case SORTER::SORXIT:
                return;
                break;
            default:
                std::cout << "=> Opción inválida <=\n";
                break;
        }
    }
}
void menu() {
    Cola<int> cola;
    std::cout << "\033[2J\033[1;1H";
    while(true) {
        std::cout << "\n\tProyecto Final\n"
                  << OPC::STATS << ") Ver información de lista.\n"
                  << OPC::PRINT << ") Imprimir todos los nodos de la lista.\n"
                  << OPC::PUSH << ") Agregar nodo.\n"
                  << OPC::REMOVE << ") Eliminar nodo.\n"
                  << OPC::SEARCH << ") Menú de busqueda de nodos.\n"
                  << OPC::SORT << ") Menú de organizadores de lista.\n"
                  << OPC::EXIT << ") Salir.\n"
                  << "Seleccione una opción: ";
        int opc;
        std::cin >> opc;
        std::cin.ignore();
        std::cout << "\033[2J\033[1;1H";
        switch(opc) {
            case OPC::STATS:
                cola_stats(&cola);
                break;
            case OPC::PRINT:
                cola.print();
                break;
            case OPC::PUSH:
                pusher(&cola);
                break;
            case OPC::REMOVE:
                killer(&cola);
                break;
            case OPC::SEARCH:
                search_menu(&cola);
                break;
            case OPC::SORT:
                sort_menu(&cola);
                break;
            case OPC::EXIT:
                cola.empty();
                return;
                break;
            default:
                std::cout << "=> Opción inválida <=\n";
                break;
        }
    }
}
int main() {
    menu();
    std::cout << "Bonito día!\n";
    return 0;
}
