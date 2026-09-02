/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AAnimal.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kong <kong@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/02 10:26:00 by kong              #+#    #+#             */
/*   Updated: 2026/09/02 10:26:24 by kong             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AAnimal.hpp"

AAnimal::AAnimal()
{
	type = "AAnimal";
	std::cout
		<< "~~ AAnimal Default Ctor called ~~" << std::endl;
}

AAnimal::AAnimal(const AAnimal& other)
{
	// AAnimal Class owns `type`
	this->type = other.type;
	std::cout
		<< "~~ AAnimal Copy Ctor called ~~" << std::endl;
}

AAnimal& AAnimal::operator=(const AAnimal& other)
{
	if (this != &other)
	{
		this->type = other.type;
	}
	std::cout
		<< "~~ AAnimal Copy Assignment Opt called ~~" << std::endl;
	return (*this);
}

AAnimal::~AAnimal()
{
	std::cout
		<< "~~ AAnimal Dtor called ~~" << std::endl;
}

void	AAnimal::makeSound() const
{
	std::cout
		<< "... UUU ee ee AAA ee ee ..." << std::endl;
}

std::string	AAnimal::getType() const
{
	return (type);
}
