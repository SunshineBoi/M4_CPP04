/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Animal.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kong <kong@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/31 14:47:53 by kong              #+#    #+#             */
/*   Updated: 2026/08/31 16:12:07 by kong             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Animal.hpp"

Animal::Animal()
{
	type = "Animal";
	std::cout
		<< "~~ Animal Default Ctor called ~~" << std::endl;
}

Animal::Animal(const Animal& other)
{
	// Animal Class owns `type`
	this->type = other.type;
	std::cout
		<< "~~ Animal Copy Ctor called ~~" << std::endl;
}

Animal& Animal::operator=(const Animal& other)
{
	if (this != &other)
	{
		this->type = other.type;
	}
	std::cout
		<< "~~ Animal Copy Assignment Opt called ~~" << std::endl;
	return (*this);
}

Animal::~Animal()
{
	std::cout
		<< "~~ Animal Dtor called ~~" << std::endl;
}

void	Animal::makeSound() const
{
	std::cout
		<< "... UUU ee ee AAA ee ee ..." << std::endl;
}

std::string	Animal::getType() const
{
	return (type);
}
