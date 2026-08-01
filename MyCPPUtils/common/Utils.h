#pragma once
// ============================================================
// Utils.h
// Small helper functions for safer and cleaner input
// 
// Author: @kingstapestry 
// ============================================================

#include <string>
#include <iostream>
#include <limits>
#include <sstream>

namespace Utils {

	// --------------------------------------------------------
	// Clears any leftover characters in the input buffer.
	// Always call this after std::cin >> number
	// so that the next getline() works correctly.
	// --------------------------------------------------------
	inline void clearInput() {
		std::cin.clear();	// reset error flags (e.g. if user typed letters instead of numbers)
		// Discard everything up to and including the next newline
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}

	// --------------------------------------------------------
	// Reads a full line of text (supports spaces)
	// Example: std::string name = Utils::inputLine("Enter name: ")
	// --------------------------------------------------------
	inline std::string inputLine(const std::string& prompt = "") {
		if (!prompt.empty()) {
			std::cout << prompt;	// show the prompt if provided
		}
		std::string value;
		std::getline(std::cin, value);	// read entire line including spaces
		return value;
	}

	// --------------------------------------------------------
	// Reads an integer with validation
	// Keeps asking until the user enters a valid number
	// --------------------------------------------------------
	inline int inputInt(const std::string& prompt = "") {
		if (!prompt.empty()) {
			std::cout << prompt;
		}

		int value;
		while (!(std::cin >> value)) {	// try to read an int
			std::cout << "Invalid number. Try again: ";
			clearInput();	// clear bad input
		}
		clearInput();	// clear leftover newline
		return value;
	}

	// --------------------------------------------------------
	// Reads a decimal number (double) with validation
	// --------------------------------------------------------
	inline int inputDouble(const std::string& prompt = "") {
		if (!prompt.empty()) {
			std::cout << prompt;
		}

		double value;
		while (!(std::cin >> value)) {	// try to read a double
			std::cout << "Invalid number. Try again: ";
			clearInput();	// clear bad input
		}
		clearInput();	// clear leftover newline
		return value;
	}

	// --------------------------------------------------------
	// Converts almost anything to string (useful for building HTML or debug)
	// --------------------------------------------------------
	template<typename T>
	inline std::string toString(const T& value) {
		std::ostringstream oss;
		oss << value;
		return oss.str();
	}

} // namespace Utils