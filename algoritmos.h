#ifndef ALGORITMOS_H
#define ALGORITMOS_H
#include "cola.h"
template <typename T> void bubble_sort(Cola<T>* arr, size_t size) {
    if(size <= 1) {
        return;
    }
    bool swapped;
    T temp;
    for(size_t i(0); i < size - 1; ++i) {
        swapped = false;
        for(size_t j = 0; j < size - i - 1; ++j) {
            if(arr->operator[](j) > arr->operator[](j + 1)) {
                arr->swap(j, j + 1);
                swapped = true;
            }
        }
        if(!swapped) {
            break;
        }
    }
}
template <typename T> void insertion_sort(Cola<T>* arr, size_t size) {
    for(size_t i(1); i < size; ++i) {
        T key = arr->operator[](i);
        ssize_t j(i - 1);
        while(j >= 0 && arr->operator[](j) > key) {
            arr->operator[](j + 1) = arr->operator[](j);
            --j;
        }
        arr->operator[](j + 1) = key;
    }
}
template <typename T> void insertion(T* arr, size_t size) {
    for(size_t i(1); i < size; ++i) {
        T key = arr[i];
        ssize_t j(i - 1);
        while(j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            --j;
        }
        arr[j + 1] = key;
    }
}
template <typename T> void shell_sort(Cola<T>* arr, size_t size) {
    for(size_t gap(size / 2); gap > 0; gap /= 2) {
        for(size_t i(gap); i < size; ++i) {
            T temp(arr->operator[](i));
            size_t j;
            for(j = i; j >= gap && arr->operator[](j - gap) > temp; j -= gap) {
                arr->operator[](j) = arr->operator[](j - gap);
            }
            arr->operator[](j) = temp;
        }
    }
}
template <typename T> void selection_sort(Cola<T>* arr, size_t size) {
    for(size_t i(0); i < size - 1; ++i) {
        size_t min_index(i);
        for(size_t j(i + 1); j < size; j++) {
            if(arr->operator[](j) < arr->operator[](min_index)) {
                min_index = j;
            }
        }
        if(min_index != i) {
            arr->swap(i, min_index);
        }
    }
}
template <typename T> size_t partition(Cola<T>* arr, size_t start, size_t end) {
    T pivot(arr->operator[](start));
    size_t count(0);
    for(size_t i(start + 1); i <= end; ++i) {
        if(arr->operator[](i) <= pivot) {
            ++count;
        }
    }
    size_t pivot_index(start + count);
    arr->swap(pivot_index, start);
    size_t i(start), j(end);
    while(i < pivot_index && j > pivot_index) {
        while(arr->operator[](i) <= pivot) {
            ++i;
        }
        while(arr->operator[](j) > pivot) {
            --j;
        }
        if(i < pivot_index && j > pivot_index) {
            arr->swap(i++, j--);
        }
    }
    return pivot_index;
}
template <typename T> void quick_sorter(Cola<T>* arr, size_t start, size_t end) {
    if(start >= end) {
        return;
    }
    size_t p(partition(arr, start, end));
    quick_sorter(arr, start, p - 1);
    quick_sorter(arr, p + 1, end);
}
template <typename T> void quick_sort(Cola<T>* arr, size_t size) {
    quick_sorter(arr, 0, size - 1);
}
template <typename T> void merge(Cola<T>* arr, size_t low, size_t mid, size_t high) {
    size_t leftSize(mid - low + 1);
    size_t rightSize(high - mid);
    T* leftArr(new T[leftSize]);
    T* rightArr(new T[rightSize]);
    for(size_t i(0); i < leftSize; i++) {
        leftArr[i] = arr->operator[](low + i);
    }
    for(size_t j = 0; j < rightSize; j++) {
        rightArr[j] = arr->operator[](mid + 1 + j);
    }
    size_t i(0);
    size_t j(0);
    size_t k(low);
    while(i < leftSize && j < rightSize) {
        if (leftArr[i] <= rightArr[j]) {
            arr->operator[](k) = leftArr[i];
            ++i;
        } else {
            arr->operator[](k) = rightArr[j];
            ++j;
        }
        ++k;
    }
    while(i < leftSize) {
        arr->operator[](k) = leftArr[i];
        ++i;
        ++k;
    }
    while(j < rightSize) {
        arr->operator[](k) = rightArr[j];
        ++j;
        ++k;
    }
    delete[] leftArr;
    delete[] rightArr;
}
template <typename T> void merge_sort(Cola<T>* arr, size_t low, size_t high) {
    if(low < high) {
        size_t mid(low + (high - low) / 2);
        merge_sort(arr, low, mid);
        merge_sort(arr, mid + 1, high);
        merge(arr, low, mid, high);
    }
}
template <typename T> void merge_sort(Cola<T>* arr, size_t size) {
    merge_sort(arr, 0, size - 1);
}
template <typename T> size_t sequential_search(Cola<T>* cola, size_t size, T target) {
    for(size_t i(0); i < size; ++i) {
        if(cola->operator[](i) == target) {
            return i;
        }
    }
    return size;
}
template <typename T> size_t binary(T* arr, size_t left, size_t right, T target) {
    size_t size = right;
    while(left <= right) {
        int mid((left + right) / 2);
        if(arr[mid] == target) {
            return mid;
        } else if(arr[mid] < target) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return size;
}
template <typename T> size_t binary_search(Cola<T>* cola, size_t size, T target) {
    T* arr(new T[cola->size()]);
    for(size_t i(0); i < size; ++i) {
        arr[i] = cola->operator[](i);
    }
    insertion(arr, size);
    size_t op(binary(arr, (size_t)0, size, target));
    for(size_t i(0); i < size; ++i) {
        if(cola->operator[](i) == arr[op]) {
            return i;
        }
    }
    return size;
}
#endif