/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WrongCat.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kong <kong@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/31 14:48:28 by kong              #+#    #+#             */
/*   Updated: 2026/08/31 15:58:29 by kong             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "WrongCat.hpp"

WrongCat::WrongCat() : WrongAnimal()
{
	type = "WrongCat";
	std::cout
		<< "~~ WrongCat Default Ctor called ~~" << std::endl;
}

WrongCat::WrongCat(const WrongCat& other) : WrongAnimal(other)
{
	std::cout
		<< "~~ WrongCat Copy Ctor called ~~" << std::endl;
}

WrongCat& WrongCat::operator=(const WrongCat& other)
{
	WrongAnimal::operator=(other);
	std::cout
		<< "~~ WrongCat Copy Assignment Opt called ~~" << std::endl;
	return (*this);
}

WrongCat::~WrongCat()
{
	std::cout
		<< "~~ WrongCat Dtor called ~~" << std::endl;
}

void	WrongCat::makeSound() const
{
	std::cout
		<< "Meowwww!" << std::endl;
}


