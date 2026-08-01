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

	inline void clear() {
#ifdef _WIN32
		system("cls");
#else
		system("clear");
#endif 
	}

	inline void pause() {
		std::cout << "\nPress Enter to continue...";
		std::cin.ignore();
		std::cin.get();
	}

	inline void title(const std::string& text) {
		std::cout << "\n========== " << text << " ==========\n";
	}

	inline void line(char symbol = '-', int length = 40) {
		std::cout << std::string(length, symbol) << "\n";
	}

} // namespace Console