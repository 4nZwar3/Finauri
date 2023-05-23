#ifndef LDL_H
#define LDL_H
#include <iostream>
#include <stdexcept>
#include <memory>
template<typename T>
class LDL {
	private:
		struct NodeLDL {
			T data;
			std::shared_ptr<NodeLDL> prev;
			std::shared_ptr<NodeLDL> next;
			NodeLDL(const T& element, std::shared_ptr<NodeLDL> p = nullptr, std::shared_ptr<NodeLDL> n = nullptr) : data(element), prev(p), next(n) {}
		};
		size_t lsize;
		std::shared_ptr<NodeLDL> lfront;
		std::shared_ptr<NodeLDL> lback;

	public:
		LDL() {
			lsize = 0;
			lfront = nullptr;
			lback = nullptr;
		}
		~LDL() {
			clear();
		}
		bool empty() const;
		size_t size() const;
		void push_front(const T& element);
		void push_back(const T& element);
		const T& front() const;
		const T& back() const;
		void pop_front();
		void pop_back();
		void insert(size_t position, const T& element);
		void erase(size_t position);
		void clear();
		void remove(const T& value);
		T& operator [](size_t position);
		void print();
        void swap(size_t position_1, size_t position_2);
        const char* get_type() const;
};
template<typename T>
bool LDL<T>::empty() const {
    return lsize == 0;
}
template<typename T>
size_t LDL<T>::size() const {
    return lsize;
}
template<typename T>
void LDL<T>::push_front(const T& element) {
    if(empty()) {
        lfront = std::make_shared<NodeLDL>(element);
        lback = lfront;
    } else {
        std::shared_ptr<NodeLDL> new_node = std::make_shared<NodeLDL>(element, nullptr, lfront);
        lfront->prev = new_node;
        lfront = new_node;
    }
    ++lsize;
}
template<typename T>
void LDL<T>::push_back(const T& element) {
    if(empty()) {
        lfront = std::make_shared<NodeLDL>(element);
        lback = lfront;
    } else {
        std::shared_ptr<NodeLDL> new_node = std::make_shared<NodeLDL>(element, lback);
        lback->next = new_node;
        lback = new_node;
    }
    ++lsize;
}
template<typename T>
const T& LDL<T>::front() const {
    if(empty()) {
        throw std::runtime_error("Trying front() from empty list");
    }
    return lfront->data;
}

template<typename T>
const T& LDL<T>::back() const {
    if(empty()) {
        throw std::runtime_error("Trying back() from empty list");
    }
    return lback->data;
}
template<typename T>
void LDL<T>::pop_front() {
    if(empty()) {
        throw std::runtime_error("Trying pop_front() from empty list");
    }
    if(size() == 1) {
        lfront = nullptr;
        lback = nullptr;
    } else {
        lfront = lfront->next;
        lfront->prev = nullptr;
    }
    --lsize;
}
template<typename T>
void LDL<T>::pop_back() {
    if(empty()) {
        throw std::runtime_error("Trying pop_back() from empty list");
    }
    if(size() == 1) {
        lfront = nullptr;
        lback = nullptr;
    } else {
        lback = lback->prev;
        lback->next = nullptr;
    }
    --lsize;
}
template<typename T>
void LDL<T>::insert(size_t position, const T& element) {
    if(empty()) {
        throw std::runtime_error("Trying insert() in empty list");
    }
    if(position > size()) {
        throw std::range_error("Trying insert() in non valid position");
    } else if(position == 0) {
        push_front(element);
    } else if(position == size()) {
        push_back(element);
    } else {
        std::shared_ptr<NodeLDL> temp = lfront;
        for(size_t i(0); i < position - 1; ++i) {
            temp = temp->next;
        }
        std::shared_ptr<NodeLDL> new_node = std::make_shared<NodeLDL>(element, temp, temp->next);
        temp->next = new_node;
        new_node->next->prev = new_node;
        ++lsize;
    }
}
template<typename T>
void LDL<T>::erase(size_t position) {
    if(empty()) {
        throw std::runtime_error("Trying erase() from empty list");
        return;
    }
    if(position >= size()) {
        throw std::runtime_error("Trying front() in non valid position");
        return;
    }
    if(position == 0) {
        pop_front();
    } else if (position == size() - 1) {
        pop_back();
    } else {
        std::shared_ptr<NodeLDL> temp = lfront;
        for(size_t i(0); i < position - 1; ++i) {
            temp = temp->next;
        }
        temp->next = temp->next->next;
        temp->next->prev = temp;

        --lsize;
    }
}
template<typename T>
void LDL<T>::clear() {
    while(!empty()) {
        pop_front();
    }
}
template<typename T>
void LDL<T>::remove(const T& value) {
    if(empty()) {
        throw std::runtime_error("Trying remove() from empty list");
        return;
    }
    T data;
    size_t i(0);
    std::shared_ptr<NodeLDL> temp = lfront;
    while(temp != nullptr) {
        data = temp->data;
        temp = temp->next;
        if (data == value) {
            erase(i);
            --i;
        }
        ++i;
    }
}
template<typename T>
T& LDL<T>::operator[](size_t position) {
    if(empty()) {
        throw std::runtime_error("Trying [] from empty list");
    }
    if(position >= size()) {
        throw std::range_error("Trying [] from non valid position");
    }
    std::shared_ptr<NodeLDL> temp = lfront;
    for(size_t i(0); i < position; ++i) {
        temp = temp->next;
    }
    return temp->data;
}
template <typename T> void LDL<T>::print() {
    if(size() == 0) {
        std::cout << "=> Lista vacía. <=\n";
        return;
    }
    std::cout << "\033[2J\033[1;1H";
    std::cout << "[posicion] <valor>\n";
	for(size_t i(0); i < size(); ++i) {
		std::cout << "   [" << i + 1 << "]       <" << operator[](i) << ">\n";
	}
}
template <typename T> void LDL<T>::swap(size_t position_1, size_t position_2) {
    std::swap(operator[](position_1), operator[](position_2));
}
template <typename T> const char* LDL<T>::get_type() const {
    return typeid(T).name();
}
#endif // LDL_H
