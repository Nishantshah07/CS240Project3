// Copyright 2026 Nishantshah07 bguliano

#include <iostream>
#include "myset.h"

using csce240h_project3::MySet;
using std::cin;
using std::cout;
using std::endl;

// Converts one character to lowercase without using extra libraries
char ToLowerChar(char c) {
  if (c >= 'A' && c <= 'Z')
    return c + 32;
  return c;
}

// Compares two C-style strings while ignoring capitalization
bool EqualsIgnoreCase(const char first[], const char second[]) {
  int i = 0;

  while (first[i] != '\0' && second[i] != '\0') {
    if (ToLowerChar(first[i]) != ToLowerChar(second[i]))
      return false;
    ++i;
  }

  return first[i] == '\0' && second[i] == '\0';
}

// Prints all sets
template <class T>
void PrintAllSets(MySet<T> sets[], int number_of_sets) {
  for (int i = 0; i < number_of_sets; ++i) {
    cout << "Set" << i + 1 << ": ";
    sets[i].Print();
    cout << endl;
  }
}

// Gets a valid set number from the user
int GetSetNumber(int number_of_sets) {
  int set_number;

  cout << "Select a set by number ";
  cout << "(1 = Set1, 2 = Set2, etc.): ";
  cin >> set_number;

  while (set_number < 1 || set_number > number_of_sets) {
    cout << "Invalid set number. Enter a number from 1 to ";
    cout << number_of_sets << ": ";
    cin >> set_number;
  }

  return set_number;
}

// Runs the demo for either int or double sets
template <class T>
void RunDemo() {
  // set demo parameters
  const int kMinSets = 2;
  const int kMaxSets = 5;
  const int kMinValues = 0;
  const int kMaxValues = 10;

  MySet<T> sets[kMaxSets];

  int number_of_sets;

  // gets the number of sets and input validation
  cout << "How many sets do you want to create? ";
  cout << "(minimum " << kMinSets << ", maximum " << kMaxSets << "): ";
  cin >> number_of_sets;

  // ensure input is correct before continuing
  while (number_of_sets < kMinSets || number_of_sets > kMaxSets) {
    cout << "Invalid number of sets. Enter a number from ";
    cout << kMinSets << " to " << kMaxSets << ": ";
    cin >> number_of_sets;
  }

  // fill each set requested
  for (int i = 0; i < number_of_sets; ++i) {
    int set_size;

    // gets each starting set and demos AddElement rejecting duplicates
    cout << "Enter size of Set" << i + 1 << ": ";
    cin >> set_size;

    while (set_size < kMinValues || set_size > kMaxValues) {
      cout << "Invalid size. Enter a size from ";
      cout << kMinValues << " to " << kMaxValues << ": ";
      cin >> set_size;
    }

    cout << "Enter values for Set" << i + 1 << ": ";

    for (int j = 0; j < set_size; ++j) {
      T value;
      cin >> value;
      sets[i].AddElement(value);
    }
  }

  cout << endl;
  cout << "Created sets:" << endl;
  PrintAllSets(sets, number_of_sets);

  // certain commands can be executed in demo
  char command[50];
  bool quit = false;

  // loop until user specifies quit
  while (!quit) {
    cout << endl;

    int selected_set_number = GetSetNumber(number_of_sets);
    int selected_index = selected_set_number - 1;

    // shows the required methods available from SetInterface
    cout << endl;
    cout << "Available methods:" << endl;
    cout << "IsElementOf" << endl;
    cout << "Cardinality" << endl;
    cout << "AddElement" << endl;
    cout << "RemoveElement" << endl;
    cout << "GetElement" << endl;
    cout << "IsSubsetOf" << endl;
    cout << "IsSupersetOf" << endl;
    cout << "Intersection" << endl;
    cout << "Union" << endl;
    cout << "Difference" << endl;
    cout << "Quit" << endl;

    cout << "Enter method name: ";
    cin >> command;

    // essentially a large if-else chain checking for each command
    if (EqualsIgnoreCase(command, "quit")) {
      quit = true;
    }

    // IsElementOf
    // checks whether one value is in the selected set
    else if (EqualsIgnoreCase(command, "iselementof")) {
      T value;

      cout << "Enter value to check: ";
      cin >> value;

      if (sets[selected_index].IsElementOf(value))
        cout << value << " is an element of Set";
      else
        cout << value << " is not an element of Set";

      cout << selected_set_number << "." << endl;

    }

    // Cardinality
    // gets the number of unique values in the set
    else if (EqualsIgnoreCase(command, "cardinality")) {
      cout << "Cardinality of Set" << selected_set_number << ": ";
      cout << sets[selected_index].Cardinality() << endl;

    }

    // AddElement
    // adds a new value or rejecting a duplicate value
    else if (EqualsIgnoreCase(command, "addelement")) {
      T value;

      cout << "Enter value to add: ";
      cin >> value;

      if (sets[selected_index].AddElement(value))
        cout << value << " was added." << endl;
      else
        cout << value << " was already in the set." << endl;

    }

    // RemoveElement
    // removes a value or leaves the set unchanged
    else if (EqualsIgnoreCase(command, "removeelement")) {
      T value;

      cout << "Enter value to remove: ";
      cin >> value;

      if (sets[selected_index].RemoveElement(value))
        cout << value << " was removed." << endl;
      else
        cout << value << " was not in the set." << endl;

    }

    // GetElement
    // retrieves an element by its array index
    else if (EqualsIgnoreCase(command, "getelement")) {
      int index;

      cout << "Enter index: ";
      cin >> index;

      cout << "Element at index " << index << ": ";
      cout << sets[selected_index].GetElement(index) << endl;

    }

    // IsSubsetOf
    // compares the selected set to another possible superset
    else if (EqualsIgnoreCase(command, "issubsetof")) {
      int other_set_number = GetSetNumber(number_of_sets);
      int other_index = other_set_number - 1;

      if (sets[selected_index].IsSubsetOf(sets[other_index])) {
        cout << "Set" << selected_set_number;
        cout << " is a subset of Set" << other_set_number << ".";
        cout << endl;
      } else {
        cout << "Set" << selected_set_number;
        cout << " is not a subset of Set" << other_set_number << ".";
        cout << endl;
      }

    }

    // IsSupersetOf
    // compares the selected set to another possible subset
    else if (EqualsIgnoreCase(command, "issupersetof")) {
      int other_set_number = GetSetNumber(number_of_sets);
      int other_index = other_set_number - 1;

      if (sets[selected_index].IsSupersetOf(sets[other_index])) {
        cout << "Set" << selected_set_number;
        cout << " is a superset of Set" << other_set_number << ".";
        cout << endl;
      } else {
        cout << "Set" << selected_set_number;
        cout << " is not a superset of Set" << other_set_number << ".";
        cout << endl;
      }

    }

    // Intersection
    // changes the set to only values in both sets
    else if (EqualsIgnoreCase(command, "intersection")) {
      int other_set_number = GetSetNumber(number_of_sets);
      int other_index = other_set_number - 1;

      sets[selected_index].Intersection(sets[other_index]);

      cout << "Set" << selected_set_number;
      cout << " was changed to its intersection with Set";
      cout << other_set_number << "." << endl;

    }

    // Union
    // changes the set to include values from both sets
    else if (EqualsIgnoreCase(command, "union")) {
      int other_set_number = GetSetNumber(number_of_sets);
      int other_index = other_set_number - 1;

      sets[selected_index].Union(sets[other_index]);

      cout << "Set" << selected_set_number;
      cout << " was changed to its union with Set";
      cout << other_set_number << "." << endl;

    }

    // Difference
    // removes values that are also in the other set
    else if (EqualsIgnoreCase(command, "difference")) {
      int other_set_number = GetSetNumber(number_of_sets);
      int other_index = other_set_number - 1;

      sets[selected_index].Difference(sets[other_index]);

      cout << "Set" << selected_set_number;
      cout << " was changed to its difference with Set";
      cout << other_set_number << "." << endl;

    }

    // invalid command
    else {
      cout << "Invalid method name." << endl;
    }

    // shows the result of the method that was just demonstrated
    if (!quit) {
      cout << "Set" << selected_set_number << ": ";
      sets[selected_index].Print();
      cout << endl;
    }
  }

  cout << endl;
  cout << "Additional functionality operator demonstrations using Set1 and Set2:" << endl;

  // demos overloaded operators that return new MySet objects
  // this is why minimum number of sets is 2
  MySet<T> union_set = sets[0] + sets[1];
  MySet<T> difference_set = sets[0] - sets[1];
  MySet<T> intersection_set = sets[0] * sets[1];

  cout << "Set1 + Set2 = ";
  union_set.Print();
  cout << endl;

  cout << "Set1 - Set2 = ";
  difference_set.Print();
  cout << endl;

  cout << "Set1 * Set2 = ";
  intersection_set.Print();
  cout << endl;

  cout << "Set1 == Set2 = ";

  if (sets[0] == sets[1])
    cout << "true";
  else
    cout << "false";

  cout << endl;
}

int main() {
  char type_choice[20];

  // lets the user choose which template type to demonstrate
  cout << "Enter type of sets, int or double: ";
  cin >> type_choice;

  // keep asking if invalid input
  while (!EqualsIgnoreCase(type_choice, "int") &&
         !EqualsIgnoreCase(type_choice, "double")) {
    cout << "Invalid type. Enter int or double: ";
    cin >> type_choice;
  }

  if (EqualsIgnoreCase(type_choice, "int"))
    RunDemo<int>();
  else
    RunDemo<double>();

  return 0;
}
