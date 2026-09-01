/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cat.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kong <kong@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/31 14:48:28 by kong              #+#    #+#             */
/*   Updated: 2026/09/01 14:53:03 by kong             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cat.hpp"

Cat::Cat() : Animal()
{
	std::cout
		<< "~~ Cat Default Ctor called ~~" << std::endl;
	type = "Cat";
	brain = new Brain();
}

Cat::Cat(const Cat& other) : Animal(other)
{
	std::cout
		<< "~~ Cat Copy Ctor called ~~" << std::endl;
	brain = new Brain(*other.brain);
}

Cat& Cat::operator=(const Cat& other)
{
	std::cout
		<< "~~ Cat Copy Assignment Opt called ~~" << std::endl;
	Animal::operator=(other);
	if (this != &other)
	{
		delete brain;
		brain = new Brain(*other.brain);
	}
	return (*this);
}

Cat::~Cat()
{
	std::cout
		<< "~~ Cat Dtor called ~~" << std::endl;
	delete brain;
}

void	Cat::makeSound() const
{
	std::cout
		<< "Meowwww!" << std::endl;
}

std::string	Cat::getIdea(int i) const
{
	return (brain->getIdea(i));
}

void	Cat::setIdea(int i, const std::string& idea)
{
	brain->setIdea(i, idea);
}
