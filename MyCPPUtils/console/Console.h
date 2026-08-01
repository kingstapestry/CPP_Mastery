#pragma once
// ============================================================
// Console.h
// Simple console helpers
// 
// Author: @kingstapestry 
// ============================================================

#include <iostream>
#include <string>

#ifdef _WIN32
#include <Windows.h>
#endif 

namespace Console {

	// --------------------------------------------------------
	// Clear terminal screen
	// --------------------------------------------------------
	inline void clear() {
#ifdef _WIN32
		system("cls");
#else
		system("clear");
#endif 
	}

	// --------------------------------------------------------
	// Pause until user press Enter
	// --------------------------------------------------------
	inline void pause() {
		std::cout << "\nPress Enter to continue...";
		std::cin.ignore();
		std::cin.get();
	}

	// --------------------------------------------------------
	// Print a nice section title
	// --------------------------------------------------------
	inline void title(const std::string& text) {
		std::cout << "\n========== " << text << " ==========\n";
	}

	// --------------------------------------------------------
	// Print a seperator line
	// --------------------------------------------------------
	inline void line(char symbol = '-', int length = 40) {
		std::cout << std::string(length, symbol) << "\n";
	}

} // namespace Console