
#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <iostream>

using std::ostream;
using std::endl;
using std::initializer_list;
using std::string;

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

            static Node* copy(Node*);

            static void destroy(Node*);

            void printHelper(ostream&, Node*) const;

            friend ostream& operator
            <<<>(ostream&, const LinkedList<T>&);

            Node* getLastElement() const;

            void quickSortHelper(Node*, Node*);

        public:

            LinkedList() : head(nullptr), size(0) {};

            LinkedList(initializer_list <T> init);

            LinkedList(const LinkedList& list) : head(copy(list.head)), size(list.size) {};

            LinkedList& operator=(const LinkedList&);

        bool operator==(const LinkedList& other) const;

        LinkedList<T> operator+(const LinkedList<T>& other) const;

        ~LinkedList();

        string join(const string& separator) const;

        void pushBack(const T& item);

        void pushFront(const T& item);

        void remove(const T& item);

        T front();

        T back();

        void popBack();

        void popFront();

        bool isEmpty() const;

            int getSize() const;

            LinkedList<T> findCommonElements(const LinkedList<T>&) const;

            bool contains(T value) const;

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

            void popElement(ConstIterator&);

            void popElement(T&);

            void sort();

    };

    template<class T>
    string LinkedList<T>::join(const string& separator) const {
        string result;
        Node* current = head;
        while (current) {
            result += current->value;
            if (current->next) {
                result += separator;
            }
            current = current->next;
        }
        return result;
    }

    template<class T>
    void LinkedList<T>::quickSortHelper(LinkedList::Node* first, LinkedList::Node* last) {
        if (first == nullptr || first == last) {
            return;
        }
        Node* pivot = first;
        Node* current = first->next;
        Node* tail = first;
        while (current != last) {
            if (current->value < pivot->value) {
                tail = tail->next;
                std::swap(current->value, tail->value);
            }
            current = current->next;
        }
        std::swap(pivot->value, tail->value);
        quicksort(first, tail);
        quicksort(tail->next, last);
    }

    template<class T>
    typename LinkedList<T>::Node* LinkedList<T>::getLastElement() const {
        if (head == nullptr) {
            return nullptr;
        }
        Node* current = head;
        while (current->next != nullptr) {
            current = current->next;
        }
        return current;
    }

    template<class T>
    void LinkedList<T>::sort() {
        quickSortHelper(head, getLastElement());
    }

    template<class T>
    bool LinkedList<T>::contains(T value) const {
        Node* current = head;
        while (current != nullptr) {
            if (current->value == value) {
                return true;
            }
            current = current->next;
        }
        return false;
    }

    template<class T>
    LinkedList<T> LinkedList<T>::findCommonElements(const LinkedList<T>& other) const {
        LinkedList<T> common;
        Node* currentListIndex = head;
        Node* otherListIndex = other.head;

        while (currentListIndex != nullptr && otherListIndex != nullptr) {
            if (currentListIndex->value == otherListIndex->value) {
                common.pushBack(currentListIndex->value);
                currentListIndex = currentListIndex->next;
                otherListIndex = otherListIndex->next;
            } else if (currentListIndex->value < otherListIndex->value) {
                currentListIndex = currentListIndex->next;
            } else {
                otherListIndex = otherListIndex->next;
            }
        }
        return common;
    }

    template<class T>
    void LinkedList<T>::popElement(LinkedList::ConstIterator& it) {
        size--;
        // Check if the iterator is at the head of the list
        if (it.node == head) {
            Node* temp = head;
            head = head->next;
            delete temp;
            return;
        }

        // Iterate through the list and find the element
        Node* prev = head;
        Node* curr = head->next;
        while (curr != it.node) {
            prev = curr;
            curr = curr->next;
        }

        // Remove the element from the list
        prev->next = curr->next;
        delete curr;
    }

    template<class T>
    void LinkedList<T>::popElement(T& element) {
        // Check if the element is at the head of the list
        if (head != nullptr && head->value == element) {
            Node* temp = head;
            head = head->next;
            delete temp;
            size--;
            return;
        }

        // Iterate through the list and find the element
        Node* prev = head;
        Node* curr = head->next;
        while (curr != nullptr) {
            if (curr->value == element) {
                // Remove the element from the list
                prev->next = curr->next;
                delete curr;
                size--;
                return;
            }
            prev = curr;
            curr = curr->next;
        }
    }

    template<class T>
    int LinkedList<T>::getSize() const {
        return size;
    }

    template<class T>
    LinkedList<T>::LinkedList(std::initializer_list<T> init) : head(nullptr), size(0) {
        for (auto it = init.begin(); it != init.end(); it++) {
            pushBack(*it);
        }
    }

    template<class T>
    bool LinkedList<T>::isEmpty() const {
        return size == 0;
    }

    template<class T>
    bool LinkedList<T>::operator==(const LinkedList<T>& other) const {
        // Compare the sizes of the lists
        if (size != other.size) {
            return false;
        }

        // Iterate through the elements in both lists and compare them
        Node* p1 = head;
        Node* p2 = other.head;
        while (p1 != nullptr) {
            if (p1->value != p2->value) {
                return false;
            }
            p1 = p1->next;
            p2 = p2->next;
        }

        // If we reach here, the lists are equal
        return true;
    }

    template<class T>
    LinkedList<T> LinkedList<T>::operator+(const LinkedList<T>& other) const {
        // Create a new linked list to store the concatenation
        LinkedList result;

        // Add the elements from this linked list to the result
        Node* p = head;
        while (p != nullptr) {
            result.insert(p->value);
            p = p->next;
        }

        // Add the elements from the other linked list to the result
        p = other.head;
        while (p != nullptr) {
            result.insert(p->value);
            p = p->next;
        }

        // Return the result
        return result;
    }

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
            os << "empty list";
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
    typename LinkedList<T>::Node* LinkedList<T>::copy(LinkedList::Node* p) {
        if (p == nullptr) {
            return nullptr;
        }
        Node* result = new Node(p->value);
        result->next = copy(p->next);
        return result;
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
    void LinkedList<T>::pushBack(const T& item) {
        Node* temp = new Node(item);

        if (head == nullptr) {
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
    void LinkedList<T>::pushFront(const T& item) {
        LinkedList < T > ::Node * temp = new Node(item);
        temp->next = head;
        head = temp;
        size++;
    }

    template<class T>
    void LinkedList<T>::remove(const T& value) {
        Node* current = head;
        Node* prev = nullptr;

        while (current != nullptr) {
            if (current->value == value) {
                if (prev != nullptr) {
                    prev->next = current->next;
                } else {
                    head = current->next;
                }

                delete current;
                return;
            }

            prev = current;
            current = current->next;
        }
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
#endif //LINKED_LIST_H
