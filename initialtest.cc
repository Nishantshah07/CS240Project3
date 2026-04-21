// Copyright 2026 csce240h
#include"setinterface.h"
#include"myset.h"

using csce240h_project3::SetInterface;
using csce240h_project3::MySet;

int main() {
  SetInterface<int> * ptr = new MySet<int>();
  ptr->Print();  // should output {} to the standard output device
  return 0;
}
