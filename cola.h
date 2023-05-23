#ifndef COLA_H
#define COLA_H
#include "ldl.h"
template<typename T>
class Cola {
    private:
        LDL<T> lista;
    public:
        Cola() {}
        ~Cola() {}
        bool is_empty() const;
        void empty();
        size_t size() const;
        const T& front() const;
        const T& back() const;
        void push(const T& element);
        void pop();
        T& operator [](size_t position);
        void print();
        void swap(size_t position_1, size_t position_2);
        void erase(size_t position);
        const char* get_type() const;
};
template<typename T>
bool Cola<T>::is_empty() const {
    return lista.empty();
}
template<typename T>
void Cola<T>::empty() {
    while(!is_empty()) {
        lista.pop_front();
    }
}
template<typename T>
size_t Cola<T>::size() const {
    return lista.size();
}
template<typename T>
const T& Cola<T>::front() const {
    if(is_empty()) {
        throw std::runtime_error("Trying front() from empty queue");
    }
    return lista.front();
}
template<typename T>
const T& Cola<T>::back() const{
    if(is_empty()){
        throw std::runtime_error("Trying back() from empty queue");
    }
    return lista.back();
}
template<typename T>
void Cola<T>::push(const T& element) {
    lista.push_back(element);
}
template<typename T>
void Cola<T>::pop() {
    if (is_empty()) {
        throw std::runtime_error("Trying pop() from empty queue");
    }
    lista.pop_front();
}
template<typename T> T& Cola<T>::operator [](size_t position) {
    return lista.operator[](position);
}
template <typename T> void Cola<T>::print() {
    lista.print();
}
template <typename T> void Cola<T>::swap(size_t position_1, size_t position_2) {
    lista.swap(position_1, position_2);
}
template <typename T> void Cola<T>::erase(size_t position)  {
    lista.erase(position);
}
template <typename T> const char* Cola<T>::get_type() const {
    return lista.get_type();
}
#endif
