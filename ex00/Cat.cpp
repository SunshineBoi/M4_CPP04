/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cat.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kong <kong@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/31 14:48:28 by kong              #+#    #+#             */
/*   Updated: 2026/08/31 16:11:43 by kong             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cat.hpp"

Cat::Cat() : Animal()
{
	type = "Cat";
	std::cout
		<< "~~ Cat Default Ctor called ~~" << std::endl;
}

Cat::Cat(const Cat& other) : Animal(other)
{
	std::cout
		<< "~~ Cat Copy Ctor called ~~" << std::endl;
}

Cat& Cat::operator=(const Cat& other)
{
	Animal::operator=(other);
	std::cout
		<< "~~ Cat Copy Assignment Opt called ~~" << std::endl;
	return (*this);
}

Cat::~Cat()
{
	std::cout
		<< "~~ Cat Dtor called ~~" << std::endl;
}

void	Cat::makeSound() const
{
	std::cout
		<< "Meowwww!" << std::endl;
}


