#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <ostream>
#include <stdexcept>
#include <string>
#include "Dict.h"
#include "TableEntry.h"
#include "../../P1/PRA_2627_P1/ListLinked.h"  // ¡Ajusta esta ruta según la ubicación real de tu P1!

template <typename V>
class HashTable : public Dict<V> {
private:
    int n;       // Número de elementos almacenados
    int max;     // Tamaño de la tabla hash (número de cubetas)
    ListLinked<TableEntry<V>>* table; // Array de punteros a listas enlazadas

    // Función hash
    int h(std::string key) const {
        int sum = 0;
        for (size_t i = 0; i < key.length(); ++i) {
            sum += int(key.at(i));
        }
        return sum % max;
    }

public:
    // Constructor
    HashTable(int size) {
        max = size;
        n = 0;
        table = new ListLinked<TableEntry<V>>[max];
    }

    // Destructor
    ~HashTable() {
        delete[] table;
    }

    // Devuelve el número total de cubetas
    int capacity() {
        return max;
    }

    // Método insert heredado de Dict
    void insert(std::string key, V value) override {
        int idx = h(key);
        TableEntry<V> entry(key, value);
        
        // Comprobamos si la clave ya existe en la lista de la cubeta
        if (table[idx].search(entry) != -1) {
            throw std::runtime_error("La clave ya existe en el diccionario.");
        }
        
        table[idx].prepend(entry);
        n++;
    }

    // Método search heredado de Dict
    V search(std::string key) override {
        int idx = h(key);
        TableEntry<V> entry(key);
        int pos = table[idx].search(entry);
        
        if (pos == -1) {
            throw std::runtime_error("La clave no se encuentra en el diccionario.");
        }
        
        return table[idx].get(pos).value;
    }

    // Método remove heredado de Dict
    V remove(std::string key) override {
        int idx = h(key);
        TableEntry<V> entry(key);
        int pos = table[idx].search(entry);
        
        if (pos == -1) {
            throw std::runtime_error("La clave no se encuentra en el diccionario para eliminar.");
        }
        
        V val = table[idx].get(pos).value;
        table[idx].remove(pos);
        n--;
        return val;
    }

    // Método entries heredado de Dict
    int entries() override {
        return n;
    }

    // Sobrecarga del operador []
    V operator[](std::string key) {
        return search(key);
    }

    // Sobrecarga global del operador <<
    friend std::ostream& operator<<(std::ostream &out, const HashTable<V> &th) {
        out << "HashTable [entries: " << th.n << ", capacity: " << th.max << "]\n";
        for (int i = 0; i < th.max; ++i) {
            out << "Cubeta " << i << ": " << th.table[i] << "\n";
        }
        return out;
    }
};

#endif // HASHTABLE_H
