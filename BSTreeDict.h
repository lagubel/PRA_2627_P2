#ifndef BSTREEDICT_H
#define BSTREEDICT_H

#include <ostream>
#include <stdexcept>
#include "Dict.h"
#include "BSTree.h"
#include "TableEntry.h"

template <typename V>
class BSTreeDict: public Dict<V> {
private:
    BSTree<TableEntry<V>>* tree;

public:
    // Constructor
    BSTreeDict() {
        tree = new BSTree<TableEntry<V>>();
    }

    // Destructor
    ~BSTreeDict() {
        delete tree;
    }

    // Método insert heredado de Dict
    void insert(std::string key, V value) override {
        TableEntry<V> entry(key, value);
        tree->insert(entry);
    }

    // Método search heredado de Dict
    V search(std::string key) override {
        TableEntry<V> entry(key);
        return tree->search(entry).value;
    }

    // Método remove heredado de Dict
    V remove(std::string key) override {
        TableEntry<V> entry(key);
        V val = tree->search(entry).value;
        tree->remove(entry);
        return val;
    }

    // Método entries heredado de Dict
    int entries() override {
        return tree->size();
    }

    // Sobrecarga del operador []
    V operator[](std::string key) {
        return search(key);
    }

    // Sobrecarga global del operador <<
    friend std::ostream& operator<<(std::ostream &out, const BSTreeDict<V> &bs) {
        out << *(bs.tree);
        return out;
    }
};

#endif // BSTREEDICT_H
