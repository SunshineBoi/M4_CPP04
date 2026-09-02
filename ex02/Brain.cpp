/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Brain.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kong <kong@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/01 12:13:51 by kong              #+#    #+#             */
/*   Updated: 2026/09/01 14:54:04 by kong             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Brain.hpp"

Brain::Brain()
{
	std::cout
		<< "~~ Brain Default Ctor called ~~" << std::endl;
}

Brain::Brain(const Brain& other)
{
	for (int i = 0; i < 100; i++)
	{
		ideas[i] = other.ideas[i];
	}
	std::cout
		<< "~~ Brain Copy Ctor called ~~" << std::endl;
}

Brain& Brain::operator=(const Brain& other)
{
	if (this != &other)
	{
		for (int i = 0; i < 100; i++)
			ideas[i] = other.ideas[i];
	}
	std::cout
		<< "~~ Brain Copy Assignment Opt called ~~" << std::endl;
	return (*this);
}

Brain::~Brain()
{
	std::cout
		<< "~~ Brain Dtor called ~~" << std::endl;
}

std::string Brain::getIdea(int i) const
{
	return (ideas[i]);
}

void	Brain::setIdea(int i, const std::string& idea)
{
	ideas[i] = idea;
}
