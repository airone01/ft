/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 15:41:36 by elagouch          #+#    #+#             */
/*   Updated: 2025/09/10 15:00:27 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Animal.hpp"
#include "Cat.hpp"
#include "Dog.hpp"
#include "WrongAnimal.hpp"
#include "WrongCat.hpp"
#include <iostream>

void testBasicPolymorphism() {
  std::cout << "\n=== Basic Polymorphism Test ===" << std::endl;

  const Animal *meta = new Animal();
  const Animal *j = new Dog();
  const Animal *i = new Cat();

  std::cout << "Types:" << std::endl;
  std::cout << "j type: " << j->getType() << std::endl;
  std::cout << "i type: " << i->getType() << std::endl;
  std::cout << "meta type: " << meta->getType() << std::endl;

  std::cout << "\nSounds:" << std::endl;
  i->makeSound();    // Should output cat sound
  j->makeSound();    // Should output dog sound
  meta->makeSound(); // Should output animal sound (or nothing)

  delete i;
  delete j;
  delete meta;
}

void testWrongPolymorphism() {
  std::cout << "\n=== Wrong Polymorphism Test ===" << std::endl;

  const WrongAnimal *wrong_meta = new WrongAnimal();
  const WrongAnimal *wrong_cat = new WrongCat();

  std::cout << "Types:" << std::endl;
  std::cout << "wrong_cat type: " << wrong_cat->getType() << std::endl;
  std::cout << "wrong_meta type: " << wrong_meta->getType() << std::endl;

  std::cout << "\nSounds (should both be WrongAnimal sound):" << std::endl;
  wrong_cat->makeSound();  // Should output WrongAnimal sound (not WrongCat)
  wrong_meta->makeSound(); // Should output WrongAnimal sound

  delete wrong_cat;
  delete wrong_meta;
}

void testDirectInstantiation() {
  std::cout << "\n=== Direct Instantiation Test ===" << std::endl;

  Dog dog;
  Cat cat;
  Animal animal;

  std::cout << "Direct objects:" << std::endl;
  std::cout << "Dog type: " << dog.getType() << std::endl;
  std::cout << "Cat type: " << cat.getType() << std::endl;
  std::cout << "Animal type: " << animal.getType() << std::endl;

  std::cout << "\nDirect sounds:" << std::endl;
  dog.makeSound();
  cat.makeSound();
  animal.makeSound();
}

void testCopyConstructors() {
  std::cout << "\n=== Copy Constructor Test ===" << std::endl;

  Dog original_dog;
  Cat original_cat;

  std::cout << "Original objects:" << std::endl;
  original_dog.makeSound();
  original_cat.makeSound();

  Dog copied_dog(original_dog);
  Cat copied_cat(original_cat);

  std::cout << "Copied objects:" << std::endl;
  copied_dog.makeSound();
  copied_cat.makeSound();

  std::cout << "Types match: " << std::endl;
  std::cout << "Dog: " << (original_dog.getType() == copied_dog.getType())
            << std::endl;
  std::cout << "Cat: " << (original_cat.getType() == copied_cat.getType())
            << std::endl;
}

void testArrayOfAnimals() {
  std::cout << "\n=== Array of Animals Test ===" << std::endl;

  const int size = 6;
  Animal *animals[size];

  // Fill array with different animals
  animals[0] = new Animal();
  animals[1] = new Dog();
  animals[2] = new Cat();
  animals[3] = new Dog();
  animals[4] = new Cat();
  animals[5] = new Animal();

  std::cout << "Array of animals making sounds:" << std::endl;
  for (int i = 0; i < size; i++) {
    std::cout << "Animal " << i << " (" << animals[i]->getType() << "): ";
    animals[i]->makeSound();
  }

  // Clean up
  for (int i = 0; i < size; i++) {
    delete animals[i];
  }
}

void testDestructorOrder() {
  std::cout << "\n=== Destructor Order Test ===" << std::endl;
  std::cout << "Watch the destruction order:" << std::endl;

  {
    Dog local_dog;
    Cat local_cat;
    std::cout << "About to leave scope..." << std::endl;
  }
  std::cout << "Left scope." << std::endl;
}

int main() {
  std::cout << "=== ANIMAL POLYMORPHISM TESTS ===" << std::endl;

  testBasicPolymorphism();
  testWrongPolymorphism();
  testDirectInstantiation();
  testCopyConstructors();
  testArrayOfAnimals();
  testDestructorOrder();

  std::cout << "\n=== ALL TESTS COMPLETED ===" << std::endl;
  return 0;
}
