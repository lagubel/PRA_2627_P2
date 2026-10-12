#ifndef BSTREE_H
#define BSTREE_H

#include <ostream>
#include <stdexcept>
#include "BSNode.h"

template <typename T>
class BSTree {
private:
    int nelem;
    BSNode<T>* root;

    // Método privado recursivo para la búsqueda
    BSNode<T>* search(BSNode<T>* n, T e) const {
        if (n == nullptr) {
            throw std::runtime_error("Element not found");
        } else if (e < n->elem) {
            return search(n->left, e);
        } else if (e > n->elem) {
            return search(n->right, e);
        } else {
            return n;
        }
    }

    // Método privado recursivo para la inserción
    BSNode<T>* insert(BSNode<T>* n, T e) {
        if (n == nullptr) {
            return new BSNode<T>(e);
        } else if (e == n->elem) {
            throw std::runtime_error("Element already exists");
        } else if (e < n->elem) {
            n->left = insert(n->left, e);
        } else {
            n->right = insert(n->right, e);
        }
        return n;
    }

    // Método privado recursivo para el recorrido inorden
    void print_inorder(std::ostream &out, BSNode<T>* n) const {
        if (n != nullptr) {
            print_inorder(out, n->left);
            out << n->elem << " ";
            print_inorder(out, n->right);
        }
    }

    // Método privado para obtener el valor máximo de un subárbol
    T max(BSNode<T>* n) const {
        if (n == nullptr) {
            throw std::runtime_error("Tree is empty");
        }
        if (n->right == nullptr) {
            return n->elem;
        }
        return max(n->right);
    }

    // Método privado para eliminar el nodo máximo de un subárbol
    BSNode<T>* remove_max(BSNode<T>* n) {
        if (n->right == nullptr) {
            BSNode<T>* left_node = n->left;
            delete n;
            return left_node;
        }
        n->right = remove_max(n->right);
        return n;
    }

    // Método privado recursivo para la eliminación de un elemento
    BSNode<T>* remove(BSNode<T>* n, T e) {
        if (n == nullptr) {
            throw std::runtime_error("Element not found");
        } else if (e < n->elem) {
            n->left = remove(n->left, e);
        } else if (e > n->elem) {
            n->right = remove(n->right, e);
        } else {
            // Nodo encontrado
            if (n->left != nullptr && n->right != nullptr) {
                // Dos hijos: reemplazamos por el máximo del subárbol izquierdo
                T m = max(n->left);
                n->elem = m;
                n->left = remove_max(n->left);
            } else {
                // Cero o un hijo
                BSNode<T>* child = (n->left != nullptr) ? n->left : n->right;
                delete n;
                return child;
            }
        }
        return n;
    }

    // Método privado recursivo para la destrucción del árbol
    void delete_cascade(BSNode<T>* n) {
        if (n != nullptr) {
            delete_cascade(n->left);
            delete_cascade(n->right);
            delete n;
        }
    }

public:
    // Constructor
    BSTree() : nelem(0), root(nullptr) {}

    // Método size
    int size() const {
        return nelem;
    }

    // Método search lanzadera
    T search(T e) const {
        BSNode<T>* result = search(root, e);
        return result->elem;
    }

    // Sobrecarga del operador[]
    T operator[](T e) const {
        return search(e);
    }

    // Método insert lanzadera
    void insert(T e) {
        root = insert(root, e);
        nelem++;
    }

    // Método remove lanzadera
    void remove(T e) {
        root = remove(root, e);
        nelem--;
    }

    // Destructor
    ~BSTree() {
        delete_cascade(root);
    }

    // Sobrecarga global del operador <<
    friend std::ostream& operator<<(std::ostream &out, const BSTree<T> &bst) {
        bst.print_inorder(out, bst.root);
        return out;
    }
};

#endif // BSTREE_H
