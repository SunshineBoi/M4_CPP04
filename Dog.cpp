/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Dog.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kong <kong@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/31 14:48:28 by kong              #+#    #+#             */
/*   Updated: 2026/08/31 16:11:47 by kong             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Dog.hpp"

Dog::Dog() : Animal()
{
	type = "Dog";
	std::cout
		<< "~~ Dog Default Ctor called ~~" << std::endl;
}

Dog::Dog(const Dog& other) : Animal(other)
{
	std::cout
		<< "~~ Dog Copy Ctor called ~~" << std::endl;
}

Dog& Dog::operator=(const Dog& other)
{
	Animal::operator=(other);
	std::cout
		<< "~~ Dog Copy Assignment Opt called ~~" << std::endl;
	return (*this);
}

Dog::~Dog()
{
	std::cout
		<< "~~ Dog Dtor called ~~" << std::endl;
}

void	Dog::makeSound() const
{
	std::cout
		<< "Woof Woof!" << std::endl;
}


