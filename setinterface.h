// Copyright 2026 csce240h
#ifndef _SETINTERFACE_H_
#define _SETINTERFACE_H_

namespace csce240h_project3 {

// A mathematical set is an unordered collection of distinct objects.
// Regardless of how a set is implemented, it should have the functionality
// included as pure virtual functions in the abstract class defined below.
template<class T>
class SetInterface {
 public:
  // prints the set using list notation to the standard output device
  // e.g. the empty set should print as {}
  // the set containing the two values "hi" and "yo" should print as {hi,yo}
  virtual void Print() const = 0;

  // IsElementOf returns true if the argument is an element in the set,
  // and false if the argument is not in the set
  virtual bool IsElementOf(T value) const = 0;

  // GetCardinality returns the number of distinct elements in the set
  virtual int Cardinality() const = 0;

  // if the argument is not already a member of the set,
  //    AddElement will increase the cardinality of the set by 1, add value of
  //    the argument as a member of the set, and return true
  // if the argument is already a member of the set,
  //    AddElement will leave the set unchanged and return false
  virtual bool AddElement(const T&) = 0;

  // if the argument is a member of the set,
  //    RemoveElement will decrease the cardinality of the set by 1, remove
  //    the value from the set, and return true
  // if the argument is not a member of the set,
  //    RemoveElement will leave the set unchanged and return false
  virtual bool RemoveElement(const T&) = 0;
  
  //Get the element at any given index
  virtual T GetElement(int index) const = 0;

  // IsSubsetOf returns true if all of the elements in the set are also
  // in the argument, and returns false otherwise
  // For example, if S1 is the set {1,3,5} and S2 is the set {1,2,3,4,5}
  // S1.IsSubsetOf(S2) should return true
  virtual bool IsSubsetOf(const SetInterface<T>& superset) = 0;

  // IsSupersetOf returns true if all of the elements in the argument
  // are also in the set, and returns false otherwise
  // For example, if S1 is the set {1,3,5} and S2 is the set {1,2,3,4,5}
  // S1.IsSupersetOf(S2) should return false
  virtual bool IsSupersetOf(const SetInterface<T>& subset) = 0;

  // Intersection will turn the set into the intersection of itself and
  // the set argument. For example, if S1 is the set {1,2,3,4,5} and S2
  // is the set {2,4,6,8}, S1.Intersection(S2) will turn S1 into the set
  // {2,4}
  virtual void Intersection(const SetInterface<T>& set2) = 0;

  // Union will turn the set into the union of itself and the set argument.
  // For example, if S1 is the set {1,2,3,4,5} and S2 is the set {2,4,6,8},
  // S1.Union(S2) will turn S1 into the set {1,2,3,4,5,6,8}
  virtual void Union(const SetInterface<T>& set2) = 0;

  // Difference will turn the set into the set difference of itself with the
  // set argument. For example, if S1 is the set {1,2,3,4,5} and S2 is the
  // set {2,4,6,8}, S1.Difference(S2) will turn S1 into the set {1,3,5}
  virtual void Difference(const SetInterface<T>& set2) = 0;
};

}  // end namespace csce240h_exam3

#endif  // end _SETINTERFACE_H_
