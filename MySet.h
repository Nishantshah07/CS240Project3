#ifndef _MYSET_H_
#define _MYSET_H_

#include <iostream>
#include "setinterface.h"

namespace csce240h_project3 {

template <class T>
class MySet : public SetInterface<T> {
 public:
  // constructors / destructor
  MySet();
  MySet(const MySet<T>& other);
  MySet<T>& operator=(const MySet<T>& other);
  ~MySet();

  // required interface functions
  void Print() const override;
  bool IsElementOf(T value) const override;
  int Cardinality() const override;
  bool AddElement(const T& value) override;
  bool RemoveElement(const T& value) override;
  T GetElement(int index) const override;

  bool IsSubsetOf(const SetInterface<T>& superset) override;
bool IsSupersetOf(const SetInterface<T>& subset) override;

  void Intersection(const SetInterface<T>& set2) override;
  void Union(const SetInterface<T>& set2) override;
  void Difference(const SetInterface<T>& set2) override;

  MySet<T> operator+(const SetInterface<T>& right) const;
  MySet<T> operator*(const SetInterface<T>& right) const;
  MySet<T> operator-(const SetInterface<T>& right) const;
  bool operator==(const SetInterface<T>& right) const;
  bool operator!=(const SetInterface<T>& right) const;

 private:
  T* elements_;
  int size_;
  int capacity_;

  void Resize();
  int IndexOf(const T& value) const;
};

}  // namespace csce240h_project3

#include "MySet.cc"
#endif  // _MYSET_H_