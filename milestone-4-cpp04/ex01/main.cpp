/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 15:41:36 by elagouch          #+#    #+#             */
/*   Updated: 2025/09/10 16:51:15 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Animal.hpp"
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

  // Test brain ideas
  dogBrain->setIdea(0, "Chase the mailman!");
  dogBrain->setIdea(1, "Bury the bone in the garden");
  catBrain->setIdea(0, "Knock things off the table");
  catBrain->setIdea(1, "Sleep for 20 hours");

  std::cout << "Dog's first idea: " << dogBrain->getIdea(0) << std::endl;
  std::cout << "Cat's first idea: " << catBrain->getIdea(0) << std::endl;
}

void testRequiredExample() {
  std::cout << "\n=== Required Example Test ===" << std::endl;

  const Animal *j = new Dog();
  const Animal *i = new Cat();

  j->makeSound();
  i->makeSound();

  delete j; // Should not create a leak
  delete i;

  std::cout << "No memory leaks in required example!" << std::endl;
}

void testDeepCopy() {
  std::cout << "\n=== Deep Copy Test ===" << std::endl;

  // Create original dog
  Dog originalDog;
  originalDog.getBrain()->setIdea(0, "Original dog idea");
  originalDog.getBrain()->setIdea(1, "Another original idea");

  std::cout << "Original dog's first idea: "
            << originalDog.getBrain()->getIdea(0) << std::endl;

  // Test copy constructor
  {
    Dog copiedDog(originalDog);
    std::cout << "Copied dog's first idea: " << copiedDog.getBrain()->getIdea(0)
              << std::endl;

    // Modify copied dog's brain - should NOT affect original
    copiedDog.getBrain()->setIdea(0, "Modified copy idea");

    std::cout << "After modifying copy:" << std::endl;
    std::cout << "Original dog's first idea: "
              << originalDog.getBrain()->getIdea(0) << std::endl;
    std::cout << "Copied dog's first idea: " << copiedDog.getBrain()->getIdea(0)
              << std::endl;

    // Verify different brain addresses
    std::cout << "Original brain: " << originalDog.getBrain() << std::endl;
    std::cout << "Copied brain: " << copiedDog.getBrain() << std::endl;
    std::cout << "Different brains (deep copy): "
              << (originalDog.getBrain() != copiedDog.getBrain()) << std::endl;
  }

  // Test assignment operator
  Dog assignedDog;
  assignedDog.getBrain()->setIdea(0, "Assigned dog original idea");

  std::cout << "\nBefore assignment:" << std::endl;
  std::cout << "Original: " << originalDog.getBrain()->getIdea(0) << std::endl;
  std::cout << "Assigned: " << assignedDog.getBrain()->getIdea(0) << std::endl;

  assignedDog = originalDog;

  std::cout << "After assignment:" << std::endl;
  std::cout << "Original: " << originalDog.getBrain()->getIdea(0) << std::endl;
  std::cout << "Assigned: " << assignedDog.getBrain()->getIdea(0) << std::endl;

  // Modify assigned dog - should NOT affect original
  assignedDog.getBrain()->setIdea(0, "Modified assigned idea");

  std::cout << "After modifying assigned:" << std::endl;
  std::cout << "Original: " << originalDog.getBrain()->getIdea(0) << std::endl;
  std::cout << "Assigned: " << assignedDog.getBrain()->getIdea(0) << std::endl;
}

void testAnimalArray() {
  std::cout << "\n=== Animal Array Test ===" << std::endl;

  const int size = 10;
  Animal *animals[size];

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

void testCatSpecificDeepCopy() {
  std::cout << "\n=== Cat Deep Copy Test ===" << std::endl;

  Cat originalCat;
  originalCat.getBrain()->setIdea(0, "Sleep in the sun");
  originalCat.getBrain()->setIdea(1, "Catch that red dot");

  Cat copiedCat(originalCat);

  // Modify original
  originalCat.getBrain()->setIdea(0, "Modified original cat idea");

  std::cout << "Original cat idea: " << originalCat.getBrain()->getIdea(0)
            << std::endl;
  std::cout << "Copied cat idea: " << copiedCat.getBrain()->getIdea(0)
            << std::endl;
  std::cout << "Deep copy successful: "
            << (originalCat.getBrain()->getIdea(0) !=
                copiedCat.getBrain()->getIdea(0))
            << std::endl;
}

void testMemoryLeakPrevention() {
  std::cout << "\n=== Memory Leak Prevention Test ===" << std::endl;

  std::cout
      << "Creating and immediately deleting animals through base pointers:"
      << std::endl;

  for (int i = 0; i < 5; i++) {
    Animal *animal;
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
  testDeepCopy();
  testAnimalArray();
  testCatSpecificDeepCopy();
  testMemoryLeakPrevention();

  std::cout << "\n=== ALL TESTS COMPLETED ===" << std::endl;
  std::cout
      << "If no memory leaks reported by valgrind, implementation is correct!"
      << std::endl;

  return 0;
}
