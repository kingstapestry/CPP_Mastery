#pragma once
// ============================================================
// Console.h
// Simple helpers to make console output look cleaner
// 
// Author: @kingstapestry 
// ============================================================

#include <iostream>
#include <string>
#include <limits>
#include <iomanip>
#include <functional>
#include <algorithm>

// Platform-specific includes for clear function
#ifdef _WIN32
#include <Windows.h>	
#else
#include <unistd.h>		
#endif // _WIN32


namespace Console {

	// --------------------------------------------------------
	// Clear entire terminal screen
	// --------------------------------------------------------
	inline void clear() {
#ifdef _WIN32
		system("cls");
#else
		system("clear");
#endif 
	}

	// --------------------------------------------------------
	// Pause the program until user press Enter
	// --------------------------------------------------------
	inline void pause() {
		std::cout << "\nPress Enter to continue...";
		std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');	// ignore() with no args can itself wait for input, this fixes it
		std::cin.get();
	}

	// --------------------------------------------------------
	// Print a nice section title
	// Example: Console::title("CAR DEALERSHIP");
	// --------------------------------------------------------
	inline void title(const std::string& text) {
		std::cout << "\n========== " << text << " ==========\n";
	}

	// --------------------------------------------------------
	// Print a seperator line
	// Example: Console::line(); -> --------- till 40 (default)
	// Example: Console::line('=', 30); -> ========== till 30
	// --------------------------------------------------------
	inline void line(char symbol = '-', int length = 40) {
		std::cout << std::string(length, symbol) << "\n";
	}

	// --------------------------------------------------------
	// Prints a message and then pauses
	// --------------------------------------------------------
	inline void message(const std::string& text) {
		std::cout << text << "\n";
		pause();
	}

	// --------------------------------------------------------
	// Prints a red error-style message and then pauses
	// --------------------------------------------------------
	inline void error(const std::string& text) {
		std::cout << "\033[31m" << "[ERROR] " << text << "\033[0m" << "\n";
		pause();
	}

	// --------------------------------------------------------
	// Prints a green success-style message and then pauses
	// --------------------------------------------------------
	inline void success(const std::string& text) {
		std::cout << "\033[32m" << "[OK] " << text << "\033[0m" << "\n";
		pause();
	}

	// --------------------------------------------------------
	// Simple way to center a piece of text on the screen
	// --------------------------------------------------------
	inline void center(const std::string& text, int width = 50) {
		int padding = (width - static_cast<int>(text.length())) / 2;
		if (padding < 0) padding = 0;
		std::cout << std::string(padding, ' ') << text << "\n";
	}

	// --------------------------------------------------------
	// Header with lines above and below
	// --------------------------------------------------------
	inline void header(const std::string& text) {
		line('=');
		center(text);
		line('=');
	}

	// --------------------------------------------------------
	// Column definition
	// --------------------------------------------------------
	template<typename T>
	struct Column {
		std::string header;
		std::function<std::string(const T&)> getter;
	};

	// --------------------------------------------------------
	// Dynamic table that works with any class
	// --------------------------------------------------------
	template<typename T>
	inline void table(const std::vector<T>& items, const std::vector<Column<T>>& columns) {
		if (columns.empty()) return;

		// Calculate column widths
		std::vector<size_t> widths(columns.size());

		for (size_t i = 0; i < columns.size(); ++i) {
			widths[i] = columns[i].header.length();
		}

		for (const auto& item : items) {
			for (size_t i = 0; i < columns.size(); ++i) {
				std::string value = columns[i].getter(item);
				widths[i] = (std::max)(widths[i], value.length());
			}
		}

		// Print header
		for (size_t i = 0; i < columns.size(); ++i) {
			std::cout << std::left << std::setw(static_cast<int>(widths[i]) + 2) << columns[i].header;
		}
		std::cout << "\n";

		// Seperator
		for (size_t i = 0; i < columns.size(); ++i) {
			std::cout << std::string(widths[i], '-') << "  ";
		}
		std::cout << "\n";

		// Print rows
		for (const auto& item : items) {
			for (size_t i = 0; i < columns.size(); ++i) {
				std::string value = columns[i].getter(item);
				std::cout << std::left << std::setw(static_cast<int>(widths[i]) + 2) << value;
			}
			std::cout << "\n";
		}
	}

} // namespace Console