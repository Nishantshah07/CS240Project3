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

  // copy each stored value into the new array
  for (int i = 0; i < size_; ++i)
    elements_[i] = other.elements_[i];
}

template <class T>
MySet<T>& MySet<T>::operator=(const MySet<T>& other) {
  // do not do anything if assigning the set to itself
  if (this != &other) {
    delete[] elements_;

    // copy over size and capacity from the right side
    size_ = other.size_;
    capacity_ = other.capacity_;
    elements_ = new T[capacity_];

    // copy each element into this set
    for (int i = 0; i < size_; ++i)
      elements_[i] = other.elements_[i];
  }

  // return this object so assignment can be chained
  return *this;
}

template <class T>
MySet<T>::~MySet() {
  delete[] elements_;

  // reset fields so the destroyed object no longer points at old memory
  elements_ = nullptr;
  size_ = 0;
  capacity_ = 0;
}

template <class T>
void MySet<T>::Print() const {
  std::cout << "{";

  // print each element with commas between values
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
  // do not add duplicates to the set
  if (IsElementOf(value))
    return false;

  // grow the array before adding if there is no more room
  if (size_ == capacity_)
    Resize();

  // place the new value at the end and increase size
  elements_[size_] = value;
  ++size_;
  return true;
}

template <class T>
bool MySet<T>::RemoveElement(const T& value) {
  // find where the value is stored before trying to remove it
  int index = IndexOf(value);

  // if not found, leave the set unchanged
  if (index == -1)
    return false;

  // shift values left to cover the removed value
  for (int i = index; i < size_ - 1; ++i)
    elements_[i] = elements_[i + 1];

  // update the size after removing the value
  --size_;

  // shrink the array if it has too much unused space (shrinks by factor of 4)
  if (capacity_ > 1 && size_ <= capacity_ / 4)
    Resize();

  // return true because a value was removed if we got here
  return true;
}

template <class T>
T MySet<T>::GetElement(int index) const {
  // validate index before accessing the array
  if (index < 0 || index >= size_) {
    std::cout << "Error: index out of range" << std::endl;
    return T();
  }

  return elements_[index];
}

template <class T>
bool MySet<T>::IsSubsetOf(const SetInterface<T>& superset) {
  // iterate over this set and make sure every value is in superset
  for (int i = 0; i < size_; ++i) {
    // if any value is missing, this cannot be a subset
    if (!superset.IsElementOf(elements_[i]))
      return false;
  }

  // if every value was found, this is a subset
  return true;
}

template <class T>
bool MySet<T>::IsSupersetOf(const SetInterface<T>& subset) {
  int subset_size = subset.Cardinality();

  // iterate over subset and make sure this set contains each value
  for (int i = 0; i < subset_size; ++i) {
    // if this set is missing a value, it cannot be a superset
    if (!IsElementOf(subset.GetElement(i)))
      return false;
  }

  // if every subset value was found, this is a superset
  return true;
}

template <class T>
void MySet<T>::Intersection(const SetInterface<T>& set2) {
  int i = 0;

  // iterate through this set and remove anything not in set2
  while (i < size_) {
    // do not increment i after removing, because elements already shift left
    if (!set2.IsElementOf(elements_[i])) {
      RemoveElement(elements_[i]);
    } else {
      ++i;
    }
  }
}

template <class T>
void MySet<T>::Union(const SetInterface<T>& set2) {
  // iterate over set2 and try to add each value into this set
  for (int i = 0; i < set2.Cardinality(); ++i) {
    // AddElement handles duplicates, so repeated values are skipped
    AddElement(set2.GetElement(i));
  }
}

template <class T>
void MySet<T>::Difference(const SetInterface<T>& set2) {
  int i = 0;

  // iterate through this set and remove anything also found in set2
  while (i < size_) {
    // do not increment i after removing, because elements shift left again
    if (set2.IsElementOf(elements_[i])) {
      RemoveElement(elements_[i]);
    } else {
      ++i;
    }
  }
}

template <class T>
MySet<T> MySet<T>::operator+(const SetInterface<T>& right) const {
  // make a copy so the original left side is unchanged
  MySet<T> result(*this);

  // union the copy with the right side and return it
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

  // same size and same values means the sets are equal
  return true;
}

template <class T>
bool MySet<T>::operator!=(const SetInterface<T>& right) const {
  return !(*this == right);
}

template <class T>
void MySet<T>::Resize() {
  int new_capacity = capacity_;

  // double the capacity when the array is full
  if (size_ == capacity_)
    new_capacity = capacity_ * 2;
  // shrink the capacity when the set is mostly empty
  else if (capacity_ > 1 && size_ <= capacity_ / 4)
    new_capacity = capacity_ / 2;

  // never let capacity go below 1
  if (new_capacity < 1)
    new_capacity = 1;

  // make sure capacity can still hold all current values
  if (new_capacity < size_)
    new_capacity = size_;

  // if nothing changed, no resize is needed
  if (new_capacity == capacity_)
    return;

  // after checks, make a new array and copy over existing set values
  T* new_elements = new T[new_capacity];

  for (int i = 0; i < size_; ++i)
    new_elements[i] = elements_[i];

  // delete the old array and replace it with the resized one
  delete[] elements_;
  elements_ = new_elements;
  capacity_ = new_capacity;
}

template <class T>
int MySet<T>::IndexOf(const T& value) const {
  // iterate over each set value looking for a match
  for (int i = 0; i < size_; ++i) {
    // if found, return the index of the matching value
    if (elements_[i] == value)
      return i;
  }

  // if the value was never found, return -1
  return -1;
}

}  // namespace csce240h_project3
