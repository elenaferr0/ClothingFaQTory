

#ifndef SHARED_PTR_H
#define SHARED_PTR_H


namespace Core::Containers {
    template<typename T>
    class SharedPtr {
        public:
            SharedPtr(T* ptr = nullptr);

            SharedPtr(const SharedPtr<T>& other);

            SharedPtr<T>& operator=(const SharedPtr<T>& other);

            ~SharedPtr();

            T* get() const;

            T& operator*() const;

            T* operator->() const;

            int use_count() const;

            operator bool() const;

        private:
            T* pointer;
            int refCount;
    };


    template<class T>
    SharedPtr<T>::SharedPtr(T* ptr) : pointer(ptr) {
        if (pointer) {
            refCount = 1;
        } else {
            refCount = 0;
        }
    }

    template<class T>
    SharedPtr<T>::SharedPtr(const SharedPtr<T>& other) : pointer(other.pointer) {
        if (pointer) {
            ++other.refCount;
            refCount = other.refCount;
        } else {
            refCount = 0;
        }
    }

    template<class T>
    SharedPtr<T>& SharedPtr<T>::operator=(const SharedPtr<T>& other) {
        if (this != &other) {
            if (pointer) {
                if (refCount == 0) {
                    delete pointer;
                }
            }

            pointer = other.pointer;
            if (pointer) {
                ++other.refCount;
                refCount = other.refCount;
            } else {
                refCount = 0;
            }
        }
        return *this;
    }

    template<class T>
    SharedPtr<T>::~SharedPtr() {
        if (pointer) {
            if (refCount == 0) {
                delete pointer;
            }
        }
    }

    template<class T>
    T* SharedPtr<T>::get() const { return pointer; }

    template<class T>
    T& SharedPtr<T>::operator*() const { return *pointer; }

    template<class T>
    T* SharedPtr<T>::operator->() const { return pointer; }

    template<class T>
    int SharedPtr<T>::use_count() const { return refCount; }

    template<class T>
    SharedPtr<T>::operator bool() const { return pointer; }

}


#endif //SHARED_PTR_H
