/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WrongAnimal.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kong <kong@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/31 14:47:53 by kong              #+#    #+#             */
/*   Updated: 2026/08/31 15:45:39 by kong             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "WrongAnimal.hpp"

WrongAnimal::WrongAnimal()
{
	type = "WrongAnimal";
	std::cout
		<< "~~ WrongAnimal Default Ctor called ~~" << std::endl;
}

WrongAnimal::WrongAnimal(const WrongAnimal& other)
{
	// WrongAnimal Class owns `type`
	this->type = other.type;
	std::cout
		<< "~~ WrongAnimal Copy Ctor called ~~" << std::endl;
}

WrongAnimal& WrongAnimal::operator=(const WrongAnimal& other)
{
	if (this != &other)
	{
		this->type = other.type;
	}
	std::cout
		<< "~~ WrongAnimal Copy Assignment Opt called ~~" << std::endl;
	return (*this);
}

WrongAnimal::~WrongAnimal()
{
	std::cout
		<< "~~ WrongAnimal Dtor called ~~" << std::endl;
}

void	WrongAnimal::makeSound() const
{
	std::cout
		<< "... UUU ee ee AAA ee ee ..." << std::endl;
}

std::string	WrongAnimal::getType() const
{
	return (type);
}
