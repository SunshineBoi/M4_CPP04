/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kong <kong@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/31 16:05:26 by kong              #+#    #+#             */
/*   Updated: 2026/09/01 11:55:19 by kong             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Animal.hpp"
#include "Dog.hpp"
#include "Cat.hpp"
#include "WrongAnimal.hpp"
#include "WrongCat.hpp"

int main()
{
	std::cout << "===== 0. from pdf =====" << std::endl;
	const Animal* meta = new Animal();
	const Animal* j = new Dog();
	const Animal* i = new Cat();
	std::cout << j->getType() << " " << std::endl;
	std::cout << i->getType() << " " << std::endl;
	i->makeSound(); //will output the cat sound!
	j->makeSound();
	meta->makeSound();

	std::cout << "\n===== 1. direct construction, no polymorphism =====" << std::endl;
	{
		Dog	dog;
		Cat	cat;
		dog.makeSound();
		cat.makeSound();
	}

	std::cout << "\n===== 2. dynamic dispatch through Animal* =====" << std::endl;
	{
		Animal*	animals[3];
		animals[0] = new Animal();
		animals[1] = new Dog();
		animals[2] = new Cat();

		for (int i = 0; i < 3; i++)
		{
			std::cout << "type: " << animals[i]->getType() << " -> ";
			animals[i]->makeSound();
		}
		for (int i = 0; i < 3; i++)
			delete animals[i]; // virtual ~Animal() ensures Dog/Cat dtor runs before Animal's
	}

	std::cout << "\n===== 3. WrongAnimal/WrongCat: non-virtual makeSound() =====" << std::endl;
	{
		WrongAnimal*	wrongCatAsWrongAnimal = new WrongCat();
		WrongCat		realWrongCat;

		std::cout << "through WrongAnimal* (static binding)  : ";
		wrongCatAsWrongAnimal->makeSound(); // prints WrongAnimal's sound, NOT WrongCat's
		std::cout << "through WrongCat object directly        : ";
		realWrongCat.makeSound(); // prints WrongCat's own sound
		delete wrongCatAsWrongAnimal;
	}

	// Object slicing happens when you assign a derived class object to a base class object by value instead of by pointer or reference.
	// Because of this, the base class obj cannot fit the extra data or behaviors of the derived class.
	std::cout << "\n===== 4. object slicing: pass-by-value loses the derived part =====" << std::endl;
	{
		Dog		dog;
		Animal	sliced = dog; // only the Animal subobject is copied; Dog part is gone
		std::cout << "sliced.getType(): " << sliced.getType() << std::endl;
		std::cout << "sliced.makeSound() (falls back to Animal's, not Dog's): ";
		sliced.makeSound();
	}

	std::cout << "\n===== 5. copy constructor and copy assignment =====" << std::endl;
	{
		Dog	original;
		Dog	copyConstructed(original);
		Dog	copyAssigned;
		copyAssigned = original;

		std::cout << "original.getType()       : " << original.getType() << std::endl;
		std::cout << "copyConstructed.getType(): " << copyConstructed.getType() << std::endl;
		std::cout << "copyAssigned.getType()   : " << copyAssigned.getType() << std::endl;
	}

	std::cout << "\n===== 6. destructor order via base pointer (checking the virtual dtor) =====" << std::endl;
	{
		Animal*	a = new Cat();
		std::cout << "about to delete Cat through Animal* -- expect Cat dtor THEN Animal dtor" << std::endl;
		delete a;
	}

	return 0;
}

/*
* Regarding slicing, the main culprit is COPY-INITIALIZED.
* TLDR: A Base Class variable simply cannot hold a Derived Class. The derived class instance has to be a pointer / reference for Base Class var to hold.
E.g. both examples below trigger copy-initalized because we are passing argument by value, not pointer or reference.
>>> 
Animal a = shiba;  // slices

void speak(Animal a) {};
speak(shiba);  // slices too

Animal a = Dog(husky)  // slices too because Animal's copy ctor is invoked.
<<<
Animal type (base) cannot contain a larger Dog type (derived).

* The solution is: always refer the derived instance as pointer or reference
>>>
Dog     d;          // a real, full Dog, on the stack
Animal& ref = d;     // just an alias for d — no new object, no copy, no slicing
Animal* ptr = &d;    // just an address of d — same, no slicing
ref.makeSound();     // Woof! — dynamic dispatch still works
<<<

*/
