#include <iostream>
#include "MySet.h"

using namespace csce240h_project3;

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
    std::cout << "Set" << i + 1 << ": ";
    sets[i].Print();
    std::cout << std::endl;
  }
}

// Gets a valid set number from the user
int GetSetNumber(int number_of_sets) {
  int set_number;

  std::cout << "Select a set by number ";
  std::cout << "(1 = Set1, 2 = Set2, etc.): ";
  std::cin >> set_number;

  while (set_number < 1 || set_number > number_of_sets) {
    std::cout << "Invalid set number. Enter a number from 1 to ";
    std::cout << number_of_sets << ": ";
    std::cin >> set_number;
  }

  return set_number;
}

// Runs the demo for either int or double sets
template <class T>
void RunDemo() {
  const int kMaxSets = 5;
  const int kMaxValues = 10;

  MySet<T> sets[kMaxSets];

  int number_of_sets;

  std::cout << "How many sets do you want to create? ";
  std::cout << "(minimum 2, maximum 5): ";
  std::cin >> number_of_sets;

  while (number_of_sets < 2 || number_of_sets > 5) {
    std::cout << "Invalid number of sets. Enter a number from 2 to 5: ";
    std::cin >> number_of_sets;
  }

  for (int i = 0; i < number_of_sets; ++i) {
    int set_size;

    std::cout << "Enter size of Set" << i + 1 << ": ";
    std::cin >> set_size;

    while (set_size < 0 || set_size > kMaxValues) {
      std::cout << "Invalid size. Enter a size from 0 to 10: ";
      std::cin >> set_size;
    }

    std::cout << "Enter values for Set" << i + 1 << ": ";

    for (int j = 0; j < set_size; ++j) {
      T value;
      std::cin >> value;
      sets[i].AddElement(value);
    }
  }

  std::cout << std::endl;
  std::cout << "Created sets:" << std::endl;
  PrintAllSets(sets, number_of_sets);

  char command[50];
  bool quit = false;

  while (!quit) {
    std::cout << std::endl;

    int selected_set_number = GetSetNumber(number_of_sets);
    int selected_index = selected_set_number - 1;

    std::cout << std::endl;
    std::cout << "Available methods:" << std::endl;
    std::cout << "IsElementOf" << std::endl;
    std::cout << "Cardinality" << std::endl;
    std::cout << "AddElement" << std::endl;
    std::cout << "RemoveElement" << std::endl;
    std::cout << "GetElement" << std::endl;
    std::cout << "IsSubsetOf" << std::endl;
    std::cout << "IsSupersetOf" << std::endl;
    std::cout << "Intersection" << std::endl;
    std::cout << "Union" << std::endl;
    std::cout << "Difference" << std::endl;
    std::cout << "Quit" << std::endl;

    std::cout << "Enter method name: ";
    std::cin >> command;

    if (EqualsIgnoreCase(command, "quit")) {
      quit = true;
    } else if (EqualsIgnoreCase(command, "iselementof")) {
      T value;

      std::cout << "Enter value to check: ";
      std::cin >> value;

      if (sets[selected_index].IsElementOf(value))
        std::cout << value << " is an element of Set";
      else
        std::cout << value << " is not an element of Set";

      std::cout << selected_set_number << "." << std::endl;

    } else if (EqualsIgnoreCase(command, "cardinality")) {
      std::cout << "Cardinality of Set" << selected_set_number << ": ";
      std::cout << sets[selected_index].Cardinality() << std::endl;

    } else if (EqualsIgnoreCase(command, "addelement")) {
      T value;

      std::cout << "Enter value to add: ";
      std::cin >> value;

      if (sets[selected_index].AddElement(value))
        std::cout << value << " was added." << std::endl;
      else
        std::cout << value << " was already in the set." << std::endl;

    } else if (EqualsIgnoreCase(command, "removeelement")) {
      T value;

      std::cout << "Enter value to remove: ";
      std::cin >> value;

      if (sets[selected_index].RemoveElement(value))
        std::cout << value << " was removed." << std::endl;
      else
        std::cout << value << " was not in the set." << std::endl;

    } else if (EqualsIgnoreCase(command, "getelement")) {
      int index;

      std::cout << "Enter index: ";
      std::cin >> index;

      std::cout << "Element at index " << index << ": ";
      std::cout << sets[selected_index].GetElement(index) << std::endl;

    } else if (EqualsIgnoreCase(command, "issubsetof")) {
      int other_set_number = GetSetNumber(number_of_sets);
      int other_index = other_set_number - 1;

      if (sets[selected_index].IsSubsetOf(sets[other_index])) {
        std::cout << "Set" << selected_set_number;
        std::cout << " is a subset of Set" << other_set_number << ".";
        std::cout << std::endl;
      } else {
        std::cout << "Set" << selected_set_number;
        std::cout << " is not a subset of Set" << other_set_number << ".";
        std::cout << std::endl;
      }

    } else if (EqualsIgnoreCase(command, "issupersetof")) {
      int other_set_number = GetSetNumber(number_of_sets);
      int other_index = other_set_number - 1;

      if (sets[selected_index].IsSupersetOf(sets[other_index])) {
        std::cout << "Set" << selected_set_number;
        std::cout << " is a superset of Set" << other_set_number << ".";
        std::cout << std::endl;
      } else {
        std::cout << "Set" << selected_set_number;
        std::cout << " is not a superset of Set" << other_set_number << ".";
        std::cout << std::endl;
      }

    } else if (EqualsIgnoreCase(command, "intersection")) {
      int other_set_number = GetSetNumber(number_of_sets);
      int other_index = other_set_number - 1;

      sets[selected_index].Intersection(sets[other_index]);

      std::cout << "Set" << selected_set_number;
      std::cout << " was changed to its intersection with Set";
      std::cout << other_set_number << "." << std::endl;

    } else if (EqualsIgnoreCase(command, "union")) {
      int other_set_number = GetSetNumber(number_of_sets);
      int other_index = other_set_number - 1;

      sets[selected_index].Union(sets[other_index]);

      std::cout << "Set" << selected_set_number;
      std::cout << " was changed to its union with Set";
      std::cout << other_set_number << "." << std::endl;

    } else if (EqualsIgnoreCase(command, "difference")) {
      int other_set_number = GetSetNumber(number_of_sets);
      int other_index = other_set_number - 1;

      sets[selected_index].Difference(sets[other_index]);

      std::cout << "Set" << selected_set_number;
      std::cout << " was changed to its difference with Set";
      std::cout << other_set_number << "." << std::endl;

    } else {
      std::cout << "Invalid method name." << std::endl;
    }

    if (!quit) {
      std::cout << "Set" << selected_set_number << ": ";
      sets[selected_index].Print();
      std::cout << std::endl;
    }
  }

  std::cout << std::endl;
  std::cout << "Operator demonstrations using Set1 and Set2:" << std::endl;

  MySet<T> union_set = sets[0] + sets[1];
  MySet<T> difference_set = sets[0] - sets[1];
  MySet<T> intersection_set = sets[0] * sets[1];

  std::cout << "Set1 + Set2 = ";
  union_set.Print();
  std::cout << std::endl;

  std::cout << "Set1 - Set2 = ";
  difference_set.Print();
  std::cout << std::endl;

  std::cout << "Set1 * Set2 = ";
  intersection_set.Print();
  std::cout << std::endl;

  std::cout << "Set1 == Set2 = ";

  if (sets[0] == sets[1])
    std::cout << "true";
  else
    std::cout << "false";

  std::cout << std::endl;
}

int main() {
  char type_choice[20];

  std::cout << "Enter type of sets, int or double: ";
  std::cin >> type_choice;

  while (!EqualsIgnoreCase(type_choice, "int") &&
         !EqualsIgnoreCase(type_choice, "double")) {
    std::cout << "Invalid type. Enter int or double: ";
    std::cin >> type_choice;
  }

  if (EqualsIgnoreCase(type_choice, "int"))
    RunDemo<int>();
  else
    RunDemo<double>();

  return 0;
}