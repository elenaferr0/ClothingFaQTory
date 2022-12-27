#ifndef MAP_H
#define MAP_H

#include <string>
#include <iostream>
#include <optional>
#include "linked_list.h"

using std::string;
using std::ostream;
using std::cout;
using std::endl;
using std::optional;
using std::nullopt;
using std::pair;

namespace Core::Containers {
    template<class K, class V>
    class Map;

    template<class K, class V>
    ostream& operator<<(ostream&, const Map<K, V>&);

    template<class K, class V>
    class Map {
        private:
            class Node {

                private:
                    enum Color {
                        RED,
                        BLACK,
                    };

                    K key;
                    V value;
                    Color color;
                    Node* parent;
                    Node* left;
                    Node* right;

                    friend class Map;

                public:
                    Node(K key = K(), V value = V(), Color color = BLACK, Node* parent = nullptr, Node* left = TNULL,
                         Node* right = TNULL) :
                            key(key),
                            value(value),
                            color(color),
                            parent(parent),
                            left(left),
                            right(right) {};
            };

            Node* root;
            unsigned int size;
            static Node* const TNULL;

            void inOrderHelper(Node* node) const;

            Node* searchTreeHelper(Node* node, K key) const;

            void fixErase(Node* x);

            void transplant(Node* u, Node* v);

            void eraseNodeHelper(Node* node, K key);

            void fixPut(Node* k);

            void printHelper(ostream& os, Node* root, string indent = "", bool visitRight = true) const;

            static Node* predecessor(Node* x);

            void leftRotate(Node* x);

            void rightRotate(Node* x);

            static Node* minimum(Node* node);

            static Node* successor(Node* x);

            void keysHelper(Node* node, LinkedList<K>& keys) const;

            void valuesHelper(Node* node, LinkedList<V>& values) const;

        public:
            Map() : root(TNULL), size(0) {};

            Map(const Map<K, V>& map) : root(inOrderCopy(map.root)), size(map.size) {};

            ~Map();

            bool empty() const;

            Map& operator=(const Map&);

            static void destroy(Node*);

            static Node* inOrderCopy(Node*);

            void inOrderTraversal() const;

            void erase(K key);

            void eraseAll();

            optional<V> get(K key) const;

            bool hasKey(const K&) const;

            unsigned int getSize() const;

            friend ostream& operator
            <<<K, V>(ostream&, const Map<K, V>&);

            class ConstIterator {
                private:
                    Map::Node* node;
                    bool isPastTheEnd;
                    bool isBeforeTheStart;
                public:
                    ConstIterator(Map::Node* n = TNULL) : node(n), isPastTheEnd(false), isBeforeTheStart(true) {};

                    bool operator==(const ConstIterator& i) const;

                    bool operator!=(const ConstIterator& i) const;

                    const ConstIterator operator++(int);  // postfix
                    ConstIterator& operator++();    // prefix

                    const ConstIterator operator--(int);  // postfix
                    ConstIterator& operator--();    // prefix

                    const pair <K, V> operator*() const;

                    friend class Map<K, V>;
            };

            bool put(const K& key, const V& value); // returns true if the element was already present

            ConstIterator cbegin() const;

            ConstIterator cend() const;

            LinkedList<K> keys() const;

            LinkedList<V> values() const;
    };

    template<class K, class V>
    void Map<K, V>::keysHelper(Map::Node* node, LinkedList<K>& keys) const {
        if (node->left) {
            keysHelper(node->left, keys);
        }
        keys.pushBack(node->key);
        if (node->right) {
            keysHelper(node->right, keys);
        }
    }

    template<class K, class V>
    void Map<K, V>::valuesHelper(Map::Node* node, LinkedList<V>& values) const {
        if (node->left) {
            valuesHelper(node->left, values);
        }
        values.pushBack(node->value);
        if (node->right) {
            valuesHelper(node->right, values);
        }
    }

    template<class K, class V>
    LinkedList<K> Map<K, V>::keys() const {
        LinkedList<K> keys = LinkedList<K>();
        keysHelper(root, keys);
        return keys;
    }

    template<class K, class V>
    LinkedList<V> Map<K, V>::values() const {
        LinkedList<V> values = LinkedList<V>();
        valuesHelper(root, values);
        return values;
    }

    template<class K, class V>
    typename Map<K, V>::Node* const Map<K, V>::TNULL = new Node();

    template<class K, class V>
    void Map<K, V>::eraseAll() {
        destroy(root);
        root = TNULL;
        size = 0;
    }

    template<class K, class V>
    void Map<K, V>::destroy(Node* node) {  // Must always be called from the root
        if (node == TNULL || !node) {
            return;
        }

        destroy(node->left);
        destroy(node->right);
        delete node;
    }

    template<class K, class V>
    typename Map<K, V>::Node* Map<K, V>::inOrderCopy(Node* node) {
        if (node == TNULL) {
            return TNULL;
        }

        Node* newNode = new Node(node->key, node->value, node->color, node->parent);

        newNode->left = inOrderCopy(node->left);
        newNode->right = inOrderCopy(node->right);
        return newNode;
    }

    template<class K, class V>
    Map<K, V>::~Map() {
        if (root != TNULL) {
            destroy(root);
        }
    }

    template<class K, class V>
    void Map<K, V>::inOrderHelper(Node* node) const {
        if (node != TNULL) {
            inOrderHelper(node->left);
            cout << "[k: " << node->key << ", v: " << node->value << "] ";
            inOrderHelper(node->right);
        }
    }

    template<class K, class V>
    typename Map<K, V>::Node* Map<K, V>::searchTreeHelper(Node* node, K key) const {
        if (node == TNULL || key == node->key) {
            return node;
        }

        if (key < node->key) {
            return searchTreeHelper(node->left, key);
        }
        return searchTreeHelper(node->right, key);
    }

    template<class K, class V>
    void Map<K, V>::fixErase(Node* x) { // fix the tree colors (rebalance after delete)
        Node* s;
        while (x != root && x->color == Node::BLACK) {
            if (x == x->parent->left) {
                s = x->parent->right;
                if (s->color == Node::RED) {
                    // case 3.1
                    s->color = Node::BLACK;
                    x->parent->color = Node::RED;
                    leftRotate(x->parent);
                    s = x->parent->right;
                }

                if (s->left->color == Node::BLACK && s->right->color == Node::BLACK) {
                    // case 3.2
                    s->color = Node::RED;
                    x = x->parent;
                } else {
                    if (s->right->color == Node::BLACK) {
                        // case 3.3
                        s->left->color = Node::BLACK;
                        s->color = Node::RED;
                        rightRotate(s);
                        s = x->parent->right;
                    }

                    // case 3.4
                    s->color = x->parent->color;
                    x->parent->color = Node::BLACK;
                    s->right->color = Node::BLACK;
                    leftRotate(x->parent);
                    x = root;
                }
            } else {
                s = x->parent->left;
                if (s->color == Node::RED) {
                    // case 3.1
                    s->color = Node::BLACK;
                    x->parent->color = Node::RED;
                    rightRotate(x->parent);
                    s = x->parent->left;
                }

                if (s->right->color == Node::BLACK) {
                    // case 3.2
                    s->color = Node::RED;
                    x = x->parent;
                } else {
                    if (s->left->color == Node::BLACK) {
                        // case 3.3
                        s->right->color = Node::BLACK;
                        s->color = Node::RED;
                        leftRotate(s);
                        s = x->parent->left;
                    }

                    // case 3.4
                    s->color = x->parent->color;
                    x->parent->color = Node::BLACK;
                    s->left->color = Node::BLACK;
                    rightRotate(x->parent);
                    x = root;
                }
            }
        }
        x->color = Node::BLACK;
    }

    template<class K, class V>
    void Map<K, V>::transplant(Node* u, Node* v) {
        if (u->parent == nullptr) {
            root = v;
        } else if (u == u->parent->left) {
            u->parent->left = v;
        } else {
            u->parent->right = v;
        }
        v->parent = u->parent;
    }

    template<class K, class V>
    void Map<K, V>::eraseNodeHelper(Node* node, K key) {
        Node* z = TNULL;
        Node* x;
        Node* y;
        while (node != TNULL) {
            if (node->key == key) {
                z = node;
            }

            if (node->key <= key) {
                node = node->right;
            } else {
                node = node->left;
            }
        }

        if (z == TNULL) {
            // Couldn'toolBar find key in the tree
            return;
        }

        y = z;
        int y_original_color = y->color;
        if (z->left == TNULL) {
            x = z->right;
            transplant(z, z->right);
        } else if (z->right == TNULL) {
            x = z->left;
            transplant(z, z->left);
        } else {
            y = minimum(z->right);
            y_original_color = y->color;
            x = y->right;
            if (y->parent == z) {
                x->parent = y;
            } else {
                transplant(y, y->right);
                y->right = z->right;
                y->right->parent = y;
            }

            transplant(z, y);
            y->left = z->left;
            y->left->parent = y;
            y->color = z->color;
        }
        delete z;
        if (y_original_color == Node::BLACK) {
            fixErase(x);
        }
        size--;
    }

    template<class K, class V>
    // fix the insertion (balance the red-black colors)
    void Map<K, V>::fixPut(Node* k) {
        Node* u;
        while (k->parent->color == Node::RED) {
            if (k->parent == k->parent->parent->right) {
                u = k->parent->parent->left; // uncle
                if (u->color == Node::RED) {
                    // case 3.1
                    u->color = Node::BLACK;
                    k->parent->color = Node::BLACK;
                    k->parent->parent->color = Node::RED;
                    k = k->parent->parent;
                } else {
                    if (k == k->parent->left) {
                        // case 3.2.2
                        k = k->parent;
                        rightRotate(k);
                    }
                    // case 3.2.1
                    k->parent->color = Node::BLACK;
                    k->parent->parent->color = Node::RED;
                    leftRotate(k->parent->parent);
                }
            } else {
                u = k->parent->parent->right; // uncle

                if (u->color == Node::RED) {
                    // mirror case 3.1
                    u->color = Node::BLACK;
                    k->parent->color = Node::BLACK;
                    k->parent->parent->color = Node::RED;
                    k = k->parent->parent;
                } else {
                    if (k == k->parent->right) {
                        // mirror case 3.2.2
                        k = k->parent;
                        leftRotate(k);
                    }
                    // mirror case 3.2.1
                    k->parent->color = Node::BLACK;
                    k->parent->parent->color = Node::RED;
                    rightRotate(k->parent->parent);
                }
            }
            if (k == root) {
                break;
            }
        }
        root->color = Node::BLACK;
    }

    template<class K, class V>
    void Map<K, V>::printHelper(ostream& os, Node* root, string indent, bool visitRight) const {
        if (root != TNULL) {
            os << indent;
            if (visitRight) {
                os << "R----";
                indent += "     ";
            } else {
                os << "L----";
                indent += "|    ";
            }

            os << "[k: " << root->key << ", val: " << root->value << " (" << (root->color ? "B" : "R") << ")]" << endl;
            printHelper(os, root->left, indent, false);
            printHelper(os, root->right, indent, true);
        }
    }

    template<class K, class V>
    void Map<K, V>::inOrderTraversal() const {
        inOrderHelper(this->root);
    }

    template<class K, class V>
    optional<V> Map<K, V>::get(K key) const {
        Node* n = searchTreeHelper(this->root, key);
        return (n && n != TNULL) ? optional(n->value) : nullopt;
    }

    template<class K, class V>
    typename Map<K, V>::Node* Map<K, V>::minimum(Node* node) { // find the node with the minimum key
        if (node == TNULL) {
            return TNULL;
        }

        while (node->left != TNULL) {
            node = node->left;
        }
        return node;
    }

    template<class K, class V>
    typename Map<K, V>::Node* Map<K, V>::successor(Node* x) {// find the successor of a given node in the inorder visit
        if (x->right != TNULL) {
            return minimum(x->right);
        }

        Node* parent = x->parent;
        while (parent && parent != TNULL && x == parent->right) {
            x = parent;
            parent = parent->parent;
        }

        return parent ? parent : TNULL;
    }

    template<class K, class V>
    void Map<K, V>::leftRotate(Node* x) { // rotate left at node x
        Node* y = x->right;
        x->right = y->left;
        if (y->left != TNULL) {
            y->left->parent = x;
        }
        y->parent = x->parent;
        if (x->parent == nullptr) {
            this->root = y;
        } else if (x == x->parent->left) {
            x->parent->left = y;
        } else {
            x->parent->right = y;
        }
        y->left = x;
        x->parent = y;
    }

    template<class K, class V>
    void Map<K, V>::rightRotate(Node* x) { // rotate right at node x
        Node* y = x->left;
        x->left = y->right;
        if (y->right != TNULL) {
            y->right->parent = x;
        }
        y->parent = x->parent;
        if (x->parent == nullptr) {
            this->root = y;
        } else if (x == x->parent->right) {
            x->parent->right = y;
        } else {
            x->parent->left = y;
        }
        y->right = x;
        x->parent = y;
    }

    template<class K, class V>
    bool Map<K, V>::put(const K& key, const V& value) {
        // in order for put to work, it's MANDATORY that K is either primitive or redefines == operator

        Node* node = new Node(key, value, Node::RED, nullptr, TNULL, TNULL);

        Node* parent = nullptr;
        Node* current = this->root;

        while (current != TNULL) {
            parent = current;
            if (node->key < current->key) {
                current = current->left;
            } else if (node->key == current->key) {
                node->value = value;
                return true; // key already exists in the tree, so do nothing
            } else {
                current = current->right;
            }
        }

        node->parent = parent; // parent is parent of current
        if (parent == nullptr) {
            root = node;
        } else if (node->key < parent->key) {
            parent->left = node;
        } else {
            parent->right = node;
        }

        size++;

        // if new node is a root node, simply return
        if (node->parent == nullptr) {
            node->color = Node::BLACK;
            return false;
        }

        // if the grandparent is null, simply return
        if (node->parent->parent == nullptr) {
            return false;
        }

        // Fix the tree
        fixPut(node);
        return false;
    }

// delete the node from the tree
    template<class K, class V>
    void Map<K, V>::erase(K key) {
        eraseNodeHelper(this->root, key);
    }

    template<class K, class V>
    unsigned int Map<K, V>::getSize() const {
        return size;
    }

    template<class K, class V>
    bool Map<K, V>::empty() const {
        return size == 0;
    }

    template<class K, class V>
    Map<K, V>& Map<K, V>::operator=(const Map<K, V>& map) {
        if (this != &map) {
            destroy(root);
            root = inOrderCopy(map.root);
        }
        size = map.size;
        return *this;
    }


    template<class K, class V>
    ostream& operator<<(ostream& os, const Map<K, V>& map) {
        if (map.empty()) {
            return os << "empty getEntityOrError" << endl;
        }

        map.printHelper(os, map.root);
        return os;
    }

    template<class K, class V>
    bool Map<K, V>::ConstIterator::operator==(const ConstIterator& i) const {
        return node == i.node;
    }

    template<class K, class V>
    bool Map<K, V>::ConstIterator::operator!=(const ConstIterator& i) const {
        return node != i.node;
    }

    template<class K, class V>
    const typename Map<K, V>::ConstIterator Map<K, V>::ConstIterator::operator++(int) { // postfix
        ConstIterator copy = *this;

        if (node && !isPastTheEnd) {
            node = Map<K, V>::successor(node);
            if (node == TNULL) {
                isPastTheEnd = true;
            }
        }

        return copy;
    }

    template<class K, class V>
    typename Map<K, V>::ConstIterator& Map<K, V>::ConstIterator::operator--() { // prefix
        if (node && !isBeforeTheStart) {
            node = Map<K, V>::predecessor(node);

            if (node == TNULL) {
                isBeforeTheStart = true;
            }
        }
        return *this;
    }


    template<class K, class V>
    bool Map<K, V>::hasKey(const K& key) const {
        return searchTreeHelper(root, key) != TNULL;
    }

    template<class K, class V>
    typename Map<K, V>::ConstIterator Map<K, V>::cbegin() const {
        return {minimum(root)};
    }

    template<class K, class V>
    typename Map<K, V>::ConstIterator Map<K, V>::cend() const {
        return {TNULL};
    }

    template<class K, class V>
    const pair <K, V> Containers::Map<K, V>::ConstIterator::operator*() const {
        return pair(node->key, node->value);
    }

    template<class K, class V>
    typename Map<K, V>::ConstIterator& Map<K, V>::ConstIterator::operator++() {
        if (node && !isPastTheEnd) {
            node = Map<K, V>::successor(node);

            if (node == TNULL) {
                isPastTheEnd = true;
            }
        }
        return *this;
    }

    template<class K, class V>
    const typename Map<K, V>::ConstIterator Map<K, V>::ConstIterator::operator--(int) {
        ConstIterator copy(*this);

        if (node && !isBeforeTheStart) {
            node = Map<K, V>::predecessor(node);
            if (node == TNULL) {
                isBeforeTheStart = true;
            }
        }

        return copy;
    }
}

#endif // MAP_H
