#ifndef BSNODE_H
#define BSNODE_H

#include <ostream>

template <typename T>
class BSNode {
public:
    // Atributos públicos
    T elem;
    BSNode<T>* left;
    BSNode<T>* right;

    // Método constructor
    BSNode(T elem, BSNode<T>* left = nullptr, BSNode<T>* right = nullptr)
        : elem(elem), left(left), right(right) {}

    // Sobrecarga global del operador <<
    friend std::ostream& operator<<(std::ostream &out, const BSNode<T> &bsn) {
        out << bsn.elem;
        return out;
    }
};

#endif // BSNODE_H
