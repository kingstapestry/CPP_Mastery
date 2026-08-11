#pragma once
// ============================================================
// Utils.h
// Collection of small helper functions for safer, cleaner input,
// random numbers, and other common tasks in Modern C++
// 
// Author: @kingstapestry 
// ============================================================

#include <string>
#include <iostream>
#include <limits>
#include <sstream>
#include <cstdlib>
#include <ctime>
#include <array>
#include <fstream>

// Platform-specific includes for sleep function
#ifdef _WIN32
#include <Windows.h>	
#else
#include <unistd.h>	
#endif // _WIN32


namespace Utils {

	// --------------------------------------------------------
	// Clears any leftover characters in the input buffer.
	// Always call this after std::cin >> number
	// so that the next getline() works correctly.
	// --------------------------------------------------------
	inline void clearInput() {
		std::cin.clear();		// reset error flags (e.g. if user typed letters instead of numbers)
		// Discard everything up to and including the next newline
		std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
	}

	// --------------------------------------------------------
	// Reads a full line of text (supports spaces)
	// Example: std::string name = Utils::inputLine("Enter name: ");
	// --------------------------------------------------------
	inline std::string inputLine(const std::string& prompt = "") {
		if (!prompt.empty()) {
			std::cout << prompt;
		}
		std::string value;
		std::getline(std::cin, value);
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
		while (!(std::cin >> value)) {
			std::cout << "Invalid number. Try again: ";
			clearInput();
		}
		clearInput();
		return value;
	}

	// --------------------------------------------------------
	// Reads a decimal number (double) with validation
	// --------------------------------------------------------
	inline double inputDouble(const std::string& prompt = "") {
		if (!prompt.empty()) {
			std::cout << prompt;
		}

		double value;
		while (!(std::cin >> value)) {	// try to read a double
			std::cout << "Invalid number. Try again: ";
			clearInput();
		}
		clearInput();
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

	// --------------------------------------------------------
	// Forces a value to stay between min and max
	// Example: amountBeforeTax = Utils::clamp(amountBeforeTax, 0, 100);
	// --------------------------------------------------------
	template<typename T>
	inline T clamp(T value, T minVal, T maxVal) {
		if (value < minVal) return minVal;
		if (value > maxVal) return maxVal;
		return value;
	}

	// --------------------------------------------------------
	// Call this ONCE at the beginning of main() if you use randomInt or chance
	// It seeds the RNG
	// --------------------------------------------------------
	inline void initRandom() {
		srand(static_cast<unsigned>(time(nullptr)));
	}

	// --------------------------------------------------------
	// Returns a random integer between min and max (inclusive)
	// Example: int shuffle = Utils::randomInt(10, 25);
	// --------------------------------------------------------
	inline int randomInt(int min, int max) {
		return min + (rand() % (max - min + 1));
	}

	// --------------------------------------------------------
	// Returns true with a certain percentage chance (0–100)
	// Example: if (Utils::chance(30)) { /* 30% chance */ }
	// --------------------------------------------------------
	inline bool chance(int percent) {
		return (rand() % 100) < percent;
	}

	// --------------------------------------------------------
	// Pauses the program for X number of milliseconds
	// Example: Utils::sleepMs(1000);	// wait 1 second
	// --------------------------------------------------------
	inline void sleepMs(int ms) {
#ifdef _WIN32
		Sleep(ms);
#else
		usleep(ms * 1000);
#endif // _WIN32

	}

	// --------------------------------------------------------
	// Asks a yes/no question. Returns true if the user says yes.
	// --------------------------------------------------------
	inline bool confirm(const std::string& prompt = "Are you sure? (y/n): ") {
		std::string answer = inputLine(prompt);
		return (answer == "y" || answer == "Y" || answer == "yes" || answer == "Yes");
	}

	// --------------------------------------------------------
	// Prints an array
	// --------------------------------------------------------
	template<typename T, size_t N>
	inline void printArray(const std::array<T, N>& arr, const std::string& title = "Array") {
		std::cout << "\n=== " << title << " ===\n";
		for (size_t i = 0; i < arr.size(); ++i) {
			std::cout << i << ": " << arr[i] << "\n";
		}
	}

	// --------------------------------------------------------
	// Finds a value in an array. Returns index or -1 if not found
	// --------------------------------------------------------
	template<typename T, size_t N>
	inline int findInArray(const std::array<T, N>& arr, const T& value) {
		for (size_t i = 0; i < arr.size(); ++i) {
			if (arr[i] == value) {
				return static_cast<int>(i);
			}
		}
		return -1;
	}

	// --------------------------------------------------------
	// Writes content to a file. Returns true on success
	// --------------------------------------------------------
	inline bool writeToFile(const std::string& filename, const std::string& content) {
		std::ofstream file(filename);
		if (!file.is_open()) return false;
		file << content;
		file.close();
		return true;
	}

	// --------------------------------------------------------
	// Reads an entire file into a string. Returns empty string on failure
	// --------------------------------------------------------
	inline std::string readFromFile(const std::string& filename) {
		std::fstream file(filename);
		if (!file.is_open()) return "";
		std::stringstream buffer;
		buffer << file.rdbuf();
		return buffer.str();
	}

} // namespace Utils