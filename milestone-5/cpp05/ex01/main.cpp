/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 11:54:40 by elagouch          #+#    #+#             */
/*   Updated: 2026/01/05 10:11:09 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "Bureaucrat.hpp"
#include "Form.hpp"

int main()
{
	std::cout << "--- TEST 1: Form Construction (Bounds) ---" << std::endl;
	try {
		Form invalid("Invalid", 0, 100); // Grade too high
	} catch (std::exception &e) {
		std::cout << "Exception caught: " << e.what() << std::endl;
	}

	try {
		Form invalid("Invalid", 151, 100); // Grade too low
	} catch (std::exception &e) {
		std::cout << "Exception caught: " << e.what() << std::endl;
	}

	std::cout << "\n--- TEST 2: Signing - Failure Case ---" << std::endl;
	try {
		Bureaucrat bob("Bob", 100);
		Form taxForm("Tax Form", 50, 100); // Requires 50 to sign

		std::cout << bob << std::endl;
		std::cout << taxForm << std::endl;

		// Bob (100) tries to sign Tax Form (50) -> Should fail
		bob.signForm(taxForm);
	} catch (std::exception &e) {
		std::cout << "Expected crash: " << e.what() << std::endl;
	}

	std::cout << "\n--- TEST 3: Signing - Success Case ---" << std::endl;
	try {
		Bureaucrat alice("Alice", 10);
		Form contract("Contract", 50, 50); // Requires 50 to sign

		std::cout << alice << std::endl;
		std::cout << contract << std::endl;

		// Alice (10) tries to sign Contract (50) -> Should succeed
		alice.signForm(contract);

		std::cout << "Form status after signing: " << contract << std::endl;

		// Try signing again (logic usually allows it, but Form stays signed)
		alice.signForm(contract);
	} catch (std::exception &e) {
		std::cout << "Unexpected crash: " << e.what() << std::endl;
	}

	return 0;
}
