// Copyright 2026 bguliano, Nishantshah07

#include "MySet.h"

#include "setinterface.h"


namespace csce240h_project3 {
    template<class T>
    MySet<T>::MySet() : elements_(nullptr), size_(0), capacity_(0) {

    }

    template<class T>
    bool MySet<T>::AddElement(const T& value) {
        if (capacity_ < size_ + 1) {

            delete [] elements_;
            capacity_ += 1;
            elements_ = new T[capacity_];
        }
        elements_[size_] = value;
        size_++;
    }
}
