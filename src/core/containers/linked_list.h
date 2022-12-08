
#ifndef MY_LIST_H
#define MY_LIST_H

#include <iostream>

using std::ostream;
using std::endl;

namespace Core::Containers {
    template<class T>
    class LinkedList;

    template<class T>
    ostream& operator<<(ostream&, const LinkedList<T>&);

    template<class T>
    class LinkedList {
    private:
        class Node {
            T value;
            Node* next;

            Node(T value, Node* next = nullptr) : value(value), next(next) {};

            friend class LinkedList;

        };

        Node* head;
        int size;

        static Node* copy(Node*, Node*);

        static void destroy(Node*);

        void printHelper(ostream&, Node*) const;

        friend ostream& operator
        <<<>(ostream&, const LinkedList<T>&);

    public:

        LinkedList() : head(nullptr), size(0) {};

        LinkedList(const LinkedList& list) : head(copy(list.head)), size(list.size) {};

        LinkedList& operator=(const LinkedList&);

        ~

        LinkedList();

        void pushBack(T item);

        void pushFront(T item);

        T front();

        T back();

        void popBack();

        void popFront();

        class ConstIterator {
            friend class LinkedList<T>;

        private:
            const Node* node;
            bool isPastTheEnd;

            ConstIterator(const Node* node, bool isPastTheEnd) : node(node), isPastTheEnd(isPastTheEnd) {}

        public:
            ConstIterator() : node(nullptr), isPastTheEnd(false) {}

            ConstIterator& operator++();

            ConstIterator operator++(int);

            const T& operator*() const;

            const T* operator->() const;

            bool operator==(const ConstIterator&) const;

            bool operator!=(const ConstIterator&) const;
        };

        ConstIterator begin() const;

        ConstIterator end() const;
    };

    template<class T>
    void LinkedList<T>::printHelper(ostream& os, typename LinkedList<T>::Node* node) const {
        if (node != nullptr) {
            os << node->value << " ";
            return printHelper(os, node->next);
        }
    }

    template<class T>
    void LinkedList<T>::destroy(LinkedList::Node* node) {
        if (node == nullptr) {
            return;
        }
        destroy(node->next);
        delete node;
    }

    template<class T>
    ostream& operator<<(ostream& os, const LinkedList<T>& list) {
        if (list.size == 0) {
            os << "empty map";
        } else {
            os << "[";
            list.printHelper(os, list.head);
            os << "]" << endl;
        }
        return os;
    }

    template<class T>
    LinkedList<T>::~LinkedList() {
        destroy(head);
    }

    template<class T>
    typename LinkedList<T>::Node* LinkedList<T>::copy(LinkedList::Node* src, LinkedList::Node* dest) {
        if (src == nullptr) {
            return nullptr;
        }
        dest = new Node(src->value);
        dest->next = copy(src->next, dest);
        return dest;
    }

    template<class T>
    bool LinkedList<T>::ConstIterator::operator==(const LinkedList<T>::ConstIterator& cit) const {
        return node == cit.node;
    }

    template<class T>
    bool LinkedList<T>::ConstIterator::operator!=(const LinkedList<T>::ConstIterator& cit) const {
        return node != cit.node;
    }

    template<class T>
    LinkedList<T>& LinkedList<T>::operator=(const LinkedList<T>& list) {
        if (this != &list) {
            destroy(head);
            head = copy(list.head);
        }
        return *this;
    }

    template<class T>
    void LinkedList<T>::pushBack(T item) {
        Node* temp = new Node(item);

        if (size == 0) {
            head = temp;
            size++;
            return;
        }

        Node* current = head;
        while (current->next != nullptr) {
            current = current->next;
        }

        current->next = temp;
        size++;
    }

    template<class T>
    void LinkedList<T>::pushFront(T item) {
        LinkedList<T>::Node* temp = new Node(item);
        temp->next = head;
        head = temp;
        size++;
    }

    template<class T>
    T LinkedList<T>::front() {
        return head->value;
    }

    template<class T>
    T LinkedList<T>::back() {
        if (head == nullptr) {
            return T();
        }

        Node* current = head;
        while (current->next != nullptr) {
            current = current->next;
        }
        return current->value;
    }

    template<class T>
    void LinkedList<T>::popBack() {
        if (head == nullptr) {
            return;
        }

        Node* current = head;
        Node* previous = nullptr;

        while (current->next != nullptr) {
            previous = current;
            current = current->next;
        }

        if (current == head) {
            head = nullptr;
        } else {
            previous->next = nullptr;
        }

        delete current;
        size--;
    }

    template<class T>
    void LinkedList<T>::popFront() {
        if (head == nullptr) {
            return;
        }

        Node* temp = head->next;
        delete head;
        head = temp;
        size--;
    }

    template<class T>
    typename LinkedList<T>::ConstIterator& LinkedList<T>::ConstIterator::operator++() {
        if (!isPastTheEnd && node != nullptr) {
            node = node->next;
        } else {
            isPastTheEnd = true;
        }
        return *this;
    }

    template<class T>
    typename LinkedList<T>::ConstIterator LinkedList<T>::ConstIterator::operator++(int) {
        ConstIterator temp = *this;
        if (!isPastTheEnd && node != nullptr) {
            node = node->next;
        } else {
            isPastTheEnd = true;
        }

        return temp;
    }

    template<class T>
    const T& LinkedList<T>::ConstIterator::operator*() const {
        return node->value;
    }

    template<class T>
    const T* LinkedList<T>::ConstIterator::operator->() const {
        return &(node->value);
    }

    template<class T>
    typename LinkedList<T>::ConstIterator LinkedList<T>::begin() const {
        return ConstIterator(head, false);
    }

    template<class T>
    typename LinkedList<T>::ConstIterator LinkedList<T>::end() const {
        return ConstIterator(nullptr, true);
    }
}
#endif //MY_LIST_H
