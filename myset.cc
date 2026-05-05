// Copyright 2026 Nishantshah07 bguliano

#include <iostream>
#include "myset.h"

namespace csce240h_project3 {

template <class T>
MySet<T>::MySet() {
  size_ = 0;
  capacity_ = 1;
  elements_ = new T[capacity_];
}

template <class T>
MySet<T>::MySet(const MySet<T>& other) {
  size_ = other.size_;
  capacity_ = other.capacity_;
  elements_ = new T[capacity_];

  for (int i = 0; i < size_; ++i)
    elements_[i] = other.elements_[i];
}

template <class T>
MySet<T>& MySet<T>::operator=(const MySet<T>& other) {
  if (this != &other) {
    delete[] elements_;

    size_ = other.size_;
    capacity_ = other.capacity_;
    elements_ = new T[capacity_];

    for (int i = 0; i < size_; ++i)
      elements_[i] = other.elements_[i];
  }

  return *this;
}

template <class T>
MySet<T>::~MySet() {
  delete[] elements_;
  elements_ = nullptr;
  size_ = 0;
  capacity_ = 0;
}

template <class T>
void MySet<T>::Print() const {
  std::cout << "{";

  for (int i = 0; i < size_; ++i) {
    std::cout << elements_[i];
    if (i < size_ - 1)
      std::cout << ",";
  }

  std::cout << "}";
}

template <class T>
bool MySet<T>::IsElementOf(T value) const {
  return IndexOf(value) != -1;
}

template <class T>
int MySet<T>::Cardinality() const {
  return size_;
}

template <class T>
bool MySet<T>::AddElement(const T& value) {
  if (IsElementOf(value))
    return false;

  if (size_ == capacity_)
    Resize();

  elements_[size_] = value;
  ++size_;
  return true;
}

template <class T>
bool MySet<T>::RemoveElement(const T& value) {
  int index = IndexOf(value);

  if (index == -1)
    return false;

  for (int i = index; i < size_ - 1; ++i)
    elements_[i] = elements_[i + 1];

  --size_;

  if (capacity_ > 1 && size_ <= capacity_ / 4)
    Resize();

  return true;
}

template <class T>
T MySet<T>::GetElement(int index) const {
  if (index < 0 || index >= size_) {
    std::cout << "Error: index out of range" << std::endl;
    return T();
  }

  return elements_[index];
}

template <class T>
bool MySet<T>::IsSubsetOf(const SetInterface<T>& superset) {
  for (int i = 0; i < size_; ++i) {
    if (!superset.IsElementOf(elements_[i]))
      return false;
  }

  return true;
}

template <class T>
bool MySet<T>::IsSupersetOf(const SetInterface<T>& subset) {
  int subset_size = subset.Cardinality();

  for (int i = 0; i < subset_size; ++i) {
    if (!IsElementOf(subset.GetElement(i)))
      return false;
  }

  return true;
}

template <class T>
void MySet<T>::Intersection(const SetInterface<T>& set2) {
  int i = 0;

  while (i < size_) {
    if (!set2.IsElementOf(elements_[i]))
      RemoveElement(elements_[i]);
    else
      ++i;
  }
}

template <class T>
void MySet<T>::Union(const SetInterface<T>& set2) {
  int set2_size = set2.Cardinality();

  for (int i = 0; i < set2_size; ++i)
    AddElement(set2.GetElement(i));
}

template <class T>
void MySet<T>::Difference(const SetInterface<T>& set2) {
  int i = 0;

  while (i < size_) {
    if (set2.IsElementOf(elements_[i]))
      RemoveElement(elements_[i]);
    else
      ++i;
  }
}

template <class T>
MySet<T> MySet<T>::operator+(const SetInterface<T>& right) const {
  MySet<T> result(*this);
  result.Union(right);
  return result;
}

template <class T>
MySet<T> MySet<T>::operator*(const SetInterface<T>& right) const {
  MySet<T> result(*this);
  result.Intersection(right);
  return result;
}

template <class T>
MySet<T> MySet<T>::operator-(const SetInterface<T>& right) const {
  MySet<T> result(*this);
  result.Difference(right);
  return result;
}

template <class T>
bool MySet<T>::operator==(const SetInterface<T>& right) const {
  if (size_ != right.Cardinality())
    return false;

  for (int i = 0; i < size_; ++i) {
    if (!right.IsElementOf(elements_[i]))
      return false;
  }

  return true;
}

template <class T>
bool MySet<T>::operator!=(const SetInterface<T>& right) const {
  return !(*this == right);
}

template <class T>
void MySet<T>::Resize() {
  int new_capacity = capacity_;

  if (size_ == capacity_)
    new_capacity = capacity_ * 2;
  else if (capacity_ > 1 && size_ <= capacity_ / 4)
    new_capacity = capacity_ / 2;

  if (new_capacity < 1)
    new_capacity = 1;

  if (new_capacity < size_)
    new_capacity = size_;

  if (new_capacity == capacity_)
    return;

  T* new_elements = new T[new_capacity];

  for (int i = 0; i < size_; ++i)
    new_elements[i] = elements_[i];

  delete[] elements_;
  elements_ = new_elements;
  capacity_ = new_capacity;
}

template <class T>
int MySet<T>::IndexOf(const T& value) const {
  for (int i = 0; i < size_; ++i) {
    if (elements_[i] == value)
      return i;
  }

  return -1;
}

}  // namespace csce240h_project3
