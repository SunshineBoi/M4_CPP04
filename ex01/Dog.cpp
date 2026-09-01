/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Dog.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kong <kong@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/31 14:48:28 by kong              #+#    #+#             */
/*   Updated: 2026/09/01 14:53:02 by kong             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Dog.hpp"

Dog::Dog() : Animal()
{
	std::cout
		<< "~~ Dog Default Ctor called ~~" << std::endl;
	type = "Dog";
	brain = new Brain();
}

Dog::Dog(const Dog& other) : Animal(other)
{
	std::cout
		<< "~~ Dog Copy Ctor called ~~" << std::endl;
	brain = new Brain(*other.brain);
}

Dog& Dog::operator=(const Dog& other)
{
	std::cout
		<< "~~ Dog Copy Assignment Opt called ~~" << std::endl;
	Animal::operator=(other);
	if (this != &other)
	{
		delete brain;
		brain = new Brain(*other.brain);
	}
	return (*this);
}

Dog::~Dog()
{
	std::cout
		<< "~~ Dog Dtor called ~~" << std::endl;
	delete brain;
}

void	Dog::makeSound() const
{
	std::cout
		<< "Woof Woof!" << std::endl;
}

std::string	Dog::getIdea(int i) const
{
	return (brain->getIdea(i));
}

void	Dog::setIdea(int i, const std::string& idea)
{
	brain->setIdea(i, idea);
}
