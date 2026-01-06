/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 15:41:36 by elagouch          #+#    #+#             */
/*   Updated: 2025/09/14 12:33:43 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AAnimal.hpp"
#include "Brain.hpp"
#include "Cat.hpp"
#include "Dog.hpp"
#include <iostream>

void testBasicBrainFunctionality() {
  std::cout << "\n=== Basic Brain Functionality Test ===" << std::endl;

  Dog dog;
  Cat cat;

  // Test that they have different brains
  Brain *dogBrain = dog.getBrain();
  Brain *catBrain = cat.getBrain();

  std::cout << "Dog brain address: " << dogBrain << std::endl;
  std::cout << "Cat brain address: " << catBrain << std::endl;
  std::cout << "Different brain addresses: " << (dogBrain != catBrain)
            << std::endl;
}

void testRequiredExample() {
  std::cout << "\n=== Required Example Test ===" << std::endl;

  const AAnimal *j = new Dog();
  const AAnimal *i = new Cat();

  j->makeSound();
  i->makeSound();

  delete j; // Should not create a leak
  delete i;

  std::cout << "No memory leaks in required example!" << std::endl;
}

void testAnimalArray() {
  std::cout << "\n=== Animal Array Test ===" << std::endl;

  const int size = 10;
  AAnimal *animals[size];

  std::cout << "Creating array of " << size
            << " animals (half dogs, half cats):" << std::endl;

  // Fill array - half dogs, half cats
  for (int i = 0; i < size; i++) {
    if (i < size / 2) {
      animals[i] = new Dog();
    } else {
      animals[i] = new Cat();
    }
  }

  std::cout << "\nArray contents:" << std::endl;
  for (int i = 0; i < size; i++) {
    std::cout << "Animal " << i << ": " << animals[i]->getType() << " - ";
    animals[i]->makeSound();
  }

  std::cout << "\nDeleting animals (watch destructor order):" << std::endl;
  for (int i = 0; i < size; i++) {
    delete animals[i];
  }

  std::cout << "Array cleanup completed!" << std::endl;
}

void testMemoryLeakPrevention() {
  std::cout << "\n=== Memory Leak Prevention Test ===" << std::endl;

  std::cout
      << "Creating and immediately deleting animals through base pointers:"
      << std::endl;

  for (int i = 0; i < 5; i++) {
    AAnimal *animal;
    if (i % 2 == 0) {
      animal = new Dog();
    } else {
      animal = new Cat();
    }

    // Use the animal briefly
    animal->makeSound();

    // Delete through base pointer - should call proper destructor chain
    delete animal;
    std::cout << "--- Animal " << i << " deleted ---" << std::endl;
  }
}

int main() {
  std::cout << "=== EXERCISE 01: BRAIN TESTS ===" << std::endl;

  testBasicBrainFunctionality();
  testRequiredExample();
  testAnimalArray();
  testMemoryLeakPrevention();

  // Proof that Animal is abstract and thus non-instanciable
  // The following does not compile
  // Animal an;

  std::cout << "\n=== ALL TESTS COMPLETED ===" << std::endl;
  std::cout
      << "If no memory leaks reported by valgrind, implementation is correct!"
      << std::endl;

  return 0;
}
