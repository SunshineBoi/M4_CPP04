/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kong <kong@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/31 16:05:26 by kong              #+#    #+#             */
/*   Updated: 2026/09/02 11:03:21 by kong             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AAnimal.hpp"
#include "Dog.hpp"
#include "Cat.hpp"
#include "WrongAnimal.hpp"
#include "WrongCat.hpp"

int main()
{
	std::cout << "===== 0. from pdf (AAnimal itself can no longer be instantiated) =====" << std::endl;
	// const AAnimal* meta = new AAnimal(); // no longer compiles: AAnimal is abstract
	const AAnimal* j = new Dog();
	const AAnimal* i = new Cat();
	std::cout << j->getType() << " " << std::endl;
	std::cout << i->getType() << " " << std::endl;
	i->makeSound(); //will output the cat sound!
	j->makeSound();
	delete j;
	delete i;

	std::cout << "\n===== 1. direct construction, no polymorphism =====" << std::endl;
	{
		Dog	dog;
		Cat	cat;
		dog.makeSound();
		cat.makeSound();
	}

	std::cout << "\n===== 2. dynamic dispatch through AAnimal* =====" << std::endl;
	{
		AAnimal*	animals[2];
		animals[0] = new Dog();
		animals[1] = new Cat();

		for (int i = 0; i < 2; i++)
		{
			std::cout << "type: " << animals[i]->getType() << " -> ";
			animals[i]->makeSound();
		}
		for (int i = 0; i < 2; i++)
			delete animals[i]; // virtual ~AAnimal() ensures Dog/Cat dtor runs before AAnimal's
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

	// Object slicing used to happen by copying a derived object into base-class
	// storage (see ex00). Now that AAnimal is abstract, that mistake can't even
	// compile anymore -- the line below is left commented out on purpose:
	//
	//     AAnimal sliced = dog;
	//     -> error: cannot declare variable 'sliced' to be of abstract type 'AAnimal'
	//
	// Making the base abstract closes off slicing at the base level entirely,
	// not just the specific case ex00 demonstrated.
	std::cout << "\n===== 4. slicing is now a compile error, not just a footgun =====" << std::endl;
	{
		Dog	dog;
		(void)dog;
		std::cout << "AAnimal sliced = dog; would fail to compile -- see comment above" << std::endl;
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
		AAnimal*	a = new Cat();
		std::cout << "about to delete Cat through AAnimal* -- expect Cat dtor THEN AAnimal dtor" << std::endl;
		delete a;
	}

	std::cout << "\n===== 7. array of AAnimal*, half Dog half Cat, deleted as AAnimal =====" << std::endl;
	{
		// Brain is private to Dog/Cat, not part of AAnimal's interface,
		// so getIdea/setIdea can't be reached through AAnimal* here on purpose.
		AAnimal* animals[] = { new Dog(), new Dog(), new Cat(), new Cat() };

		for (int i = 0; i < 4; i++)
			delete animals[i];
	}

	std::cout << "\n===== 8. Brain deep copy -- copy constructor (Dog) =====" << std::endl;
	{
		Dog			shiba;
		std::string	parkIdea = "i love park!";
		std::string	winterIdea = "i love winter!";

		shiba.setIdea(0, parkIdea);
		Dog	husky(shiba); // copy ctor: husky's Brain must be an independent copy
		husky.setIdea(0, "i love winter!");

		std::cout << "shiba.getIdea(0) : " << shiba.getIdea(0) << std::endl;
		std::cout << "husky.getIdea(0) : " << husky.getIdea(0) << std::endl;
		std::cout << (shiba.getIdea(0) != husky.getIdea(0)
			? "[OK]   deep copy confirmed -- ideas differ after mutating the copy"
			: "[FAIL] shallow copy! both Dogs share the same Brain") << std::endl;
	}

	std::cout << "\n===== 9. Brain deep copy -- copy assignment + self-assignment (Dog) =====" << std::endl;
	{
		Dog			dog1;
		Dog			dog2;
		std::string	idea1 = "chase the mailman";
		std::string	idea2 = "will be overwritten";
		std::string	changedIdea = "changed after assignment";

		dog1.setIdea(5, idea1);
		dog2.setIdea(5, idea2);
		dog2 = dog1; // operator=: dog2's old Brain must be freed, then deep-copied from dog1's
		dog1.setIdea(5, changedIdea);

		std::cout << "dog1.getIdea(5) : " << dog1.getIdea(5) << std::endl;
		std::cout << "dog2.getIdea(5) : " << dog2.getIdea(5) << std::endl;
		std::cout << (dog1.getIdea(5) != dog2.getIdea(5)
			? "[OK]   deep copy confirmed after operator="
			: "[FAIL] shallow copy! assignment shared the same Brain") << std::endl;

		dog2 = dog2; // self-assignment must not double-free / crash
		std::cout << "[OK]   self-assignment survived without crashing" << std::endl;
	}

	std::cout << "\n===== 10. same deep-copy checks, for Cat =====" << std::endl;
	{
		Cat			whiskers;
		std::string	napIdea = "nap all day";
		std::string	huntIdea = "hunt at night";

		whiskers.setIdea(0, napIdea);
		Cat	shadow(whiskers);
		shadow.setIdea(0, huntIdea);

		std::cout << "whiskers.getIdea(0) : " << whiskers.getIdea(0) << std::endl;
		std::cout << "shadow.getIdea(0)   : " << shadow.getIdea(0) << std::endl;
		std::cout << (whiskers.getIdea(0) != shadow.getIdea(0)
			? "[OK]   deep copy confirmed for Cat's Brain"
			: "[FAIL] shallow copy! Cat shares Brain") << std::endl;
	}

	return 0;
}

/*
* 1. Regarding slicing, the main culprit is COPY-INITIALIZED.
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


* 2. why temp value cant pass to a non-const reference?
>>> setIdea(std::string& idea)
self.setIdea("new idea");  // this wont work <<<
Because non-const expect modification to be reflected back.
Given it is a temporary string, it gets destroyed after expression ends.
C++ forbids it.

It works with either a copied value
>>> setIdea(std::string idea); <<<
or, a const-ref
>>> setIdea(const std::string& idea); <<<
*/
