/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   megaphone.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 12:42:16 by elagouch          #+#    #+#             */
/*   Updated: 2025/06/22 12:48:55 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <cctype>

int main(int argc, char **argv)
{
	if (argc == 1)
	{
		std::cout << "* GEGAGEDIGEDAGEDAGO *" << std::endl;
		return 0;
	}

	for (int i = 1; i < argc; i++)
	{
		for (int j = 0; argv[i][j]; j++)
			// static cast bc otherwise args are numbers
			std::cout << static_cast<char>(std::toupper(argv[i][j]));
	}
	std::cout << std::endl;

	return 0;
}
