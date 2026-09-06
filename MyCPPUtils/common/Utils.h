#pragma once
// ============================================================
// Utils.h
// General helpers: input, random, string, file, split, sort, etc.
// 
// Author: @kingstapestry 
// ============================================================

#include <string>
#include <iostream>
#include <limits>
#include <sstream>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <vector>
#include <array>
#include <algorithm>
#include <optional>
#include <random>

// Platform-specific includes for sleep function
#ifdef _WIN32
#include <Windows.h>	
#else
#include <unistd.h>	
#endif // _WIN32


namespace Utils {



	// ========== INPUT ==========

	// --------------------------------------------------------
	// Clears any leftover characters in the input buffer.
	// --------------------------------------------------------
	inline void clearInput() {
		std::cin.clear();
		std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
	}

	// --------------------------------------------------------
	// Reads a full line of text (supports spaces).
	// Example: std::string name = Utils::inputLine("Enter name: ");
	// --------------------------------------------------------
	inline std::string inputLine(const std::string& prompt = "") {
		if (!prompt.empty()) std::cout << prompt;
		std::string value;
		std::getline(std::cin, value);
		return value;
	}

	// --------------------------------------------------------
	// Reads an integer with validation,
	// keeps asking until the user enters a valid number.
	// --------------------------------------------------------
	inline int inputInt(const std::string& prompt = "") {
		if (!prompt.empty()) std::cout << prompt;
		int value;
		while (!(std::cin >> value)) {
			std::cout << "Invalid number. Try again: ";
			clearInput();
		}
		clearInput();
		return value;
	}

	// --------------------------------------------------------
	// Reads a decimal number (double) with validation.
	// --------------------------------------------------------
	inline double inputDouble(const std::string& prompt = "") {
		if (!prompt.empty()) std::cout << prompt;
		double value;
		while (!(std::cin >> value)) {
			std::cout << "Invalid number. Try again: ";
			clearInput();
		}
		clearInput();
		return value;
	}

	// --------------------------------------------------------
	// Safe A/B/C/D input.
	// --------------------------------------------------------
	inline char inputABCD(const std::string& prompt = "Your answer (A/B/C/D): ") {
		while (true) {
			std::string input = inputLine(prompt);
			if (input.empty()) continue;
			char answer = static_cast<char>(std::toupper(input[0]));
			if (answer == 'A' || answer == 'B' || answer == 'C' || answer == 'D') {
				return answer;
			}
			std::cout << "Invalid input. Please enter A, B, C or D.\n";
		}
	}



	// ========== STRING ==========

	// --------------------------------------------------------
	// Converts almost anything to string (useful for building HTML or debug).
	// --------------------------------------------------------
	template<typename T>
	inline std::string toString(const T& value) {
		std::ostringstream oss;
		oss << value;
		return oss.str();
	}

	// --------------------------------------------------------
	// Remove leading and trailing spaces from a string. 
	// --------------------------------------------------------
	inline std::string trim(const std::string& str) {
		size_t first = str.find_first_not_of(" \t\r\n");
		if (first == std::string::npos) return "";
		size_t last = str.find_last_not_of(" \t\r\n");
		return str.substr(first, last - first + 1);
	}

	// --------------------------------------------------------
	// Converts string to uppercase. 
	// --------------------------------------------------------
	inline std::string toUpper(std::string str) {
		for (char& c : str) c = static_cast<char>(std::toupper(c));
		return str;
	}



	// ========== MATH ==========

	// --------------------------------------------------------
	// Forces a value to stay between min and max.
	// Example: amountBeforeTax = Utils::clamp(amountBeforeTax, 0, 100);
	// --------------------------------------------------------
	template<typename T>
	inline T clamp(T value, T minVal, T maxVal) {
		if (value < minVal) return minVal;
		if (value > maxVal) return maxVal;
		return value;
	}

	// --------------------------------------------------------
	// Calculate percentage of a part relative to a total as a whole number.
	// --------------------------------------------------------
	inline int percent(int part, int total) {
		if (total <= 0) return 0;
		return (part * 100) / total;
	}



	// ========== RANDOM ==========

	// --------------------------------------------------------
	// Seed RNG
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
	inline bool chance(int percentChance) {
		return (rand() % 100) < percentChance;
	}

	// --------------------------------------------------------
	// Returns random element from a vector.
	// --------------------------------------------------------
	template<typename T>
	T& randomElement(std::vector<T>& list) {
		return list[randomInt(0, static_cast<int>(list.size()) - 1)];
	}

	// --------------------------------------------------------
	// Returns random element from a vector (const version).
	// --------------------------------------------------------
	template <typename T>
	const T& randomElement(const std::vector<T>& list) {
		return list[randomInt(0, static_cast<int>(list.size()) - 1)];
	}

	// --------------------------------------------------------
	// Shuffles elements in a vector.
	// --------------------------------------------------------
	template<typename T>
	void shuffle(std::vector<T>& list) {
		static std::random_device rd;
		static std::mt19937 g(rd());
		std::shuffle(list.begin(), list.end(), g);
	}



	// ========== SPLIT ==========

	// --------------------------------------------------------
	// Split a single string by a delimiter.
	// Example: split("red,green,blue", ',') -> {"red", "green", "blue"}
	// --------------------------------------------------------
	inline std::vector<std::string> split(const std::string& text, char delimiter) {
		std::vector<std::string> result;
		std::stringstream ss(text);
		std::string item;
		while (std::getline(ss, item, delimiter)) {
			result.push_back(item);
		}
		return result;
	}

	// --------------------------------------------------------
	// Read a file and split it into rows + columns.
	// Works for CSV (,), pipe-seperated (|), etc.
	// Returns a vector of rows, where each row is a vector of fields.
	// --------------------------------------------------------
	inline std::vector<std::vector<std::string>> splitFile(const std::string& filename, char delimiter = ',') {
		std::vector<std::vector<std::string>> data;
		std::ifstream file(filename);
		if (!file.is_open()) return data;

		std::string line;
		while (std::getline(file, line)) {
			if (line.empty()) continue;
			data.push_back(split(line, delimiter));
		}
		return data;
	}



	// ========== FILE ==========

	// --------------------------------------------------------
	// Writes content to a file. Returns true on success.
	// --------------------------------------------------------
	inline bool writeToFile(const std::string& filename, const std::string& content) {
		std::ofstream file(filename);
		if (!file.is_open()) return false;
		file << content;
		return true;
	}

	// --------------------------------------------------------
	// Reads an entire file into a string. Returns empty string on failure.
	// --------------------------------------------------------
	inline std::string readFromFile(const std::string& filename) {
		std::ifstream file(filename);
		if (!file.is_open()) return "";
		std::stringstream buffer;
		buffer << file.rdbuf();
		return buffer.str();
	}



	// ========== TIME ==========

	// --------------------------------------------------------
	// Pauses the program for X number of milliseconds.
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
	// Convert time_t to string.
	// --------------------------------------------------------
	inline std::string timeToString(std::time_t time) {
		char buffer[20];
		std::tm timeInfo{};

#ifdef _WIN32
		localtime_s(&timeInfo, &time);	// Windows
#else
		localtime_r(&item, &timeInfo);	// Linux/Mac
#endif // _WIN32

		std::strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M", &timeInfo);
		return std::string(buffer);
	}



	// ========== MONEY ==========

	// --------------------------------------------------------
	// Turns 1 million into 1,000,000.
	// --------------------------------------------------------
	inline std::string formatMoney(int amount) {
		std::string num = std::to_string(amount);
		std::string result;
		int count = 0;
		for (int i = static_cast<int>(num.length()) - 1; i >= 0; --i) {
			result = num[i] + result;
			count++;
			if (count % 3 == 0 && i != 0) result = "," + result;
		}
		return "$" + result;
	}



	// ========== CONFIRM ==========

	// --------------------------------------------------------
	// Asks a yes/no question. Returns true if the user says yes.
	// --------------------------------------------------------
	inline bool confirm(const std::string& prompt = "Are you sure? (y/n): ") {
		std::string answer = inputLine(prompt);
		return (answer == "y" || answer == "Y" || answer == "yes" || answer == "Yes");
	}



	// ========== SORTING (merged from VectorSort) ==========

	// --------------------------------------------------------
	// Sort a vector by any member variable of the class.
	//
	// Examples:
	//   sortBy(products, &Product::price);		// low to high
	//   sortBy(products, &Product::name, false); // Z to A
	// --------------------------------------------------------
	template<typename T, typename Member>
	void sortBy(std::vector<T>& data, Member T::* member, bool ascending = true) {
		std::sort(data.begin(), data.end(),
			[member, ascending](const T& a, const T& b) {
				if (ascending) return (a.*member) < (b.*member);
				return (a.*member) > (b.*member);
			});
	}

	// --------------------------------------------------------
	// Advanced: Sort using your own custom comparison function.
	// --------------------------------------------------------
	template<typename T, typename Compare>
	void sortByCustom(std::vector<T>& data, Compare compareFunction) {
		std::sort(data.begin(), data.end(), compareFunction);
	}



	// ========== NAME-BASED HELPERS (merged from ClassUtils) ==========

	// --------------------------------------------------------
	// Finds the index of an object by its .name member.
	// Returns -1 if not found
	// --------------------------------------------------------
	template<typename T>
	int findIndexByName(const std::vector<T>& list, const std::string& name) {
		for (size_t i = 0; i < list.size(); ++i) {
			if (list[i].name == name) return static_cast<int>(i);
		}
		return -1;
	}

	// --------------------------------------------------------
	// Returns true if an object with that name exists in the list.
	// --------------------------------------------------------
	template<typename T>
	bool existsByName(const std::vector<T>& list, const std::string& name) {
		return findIndexByName(list, name) != -1;
	}

	// --------------------------------------------------------
	// Removes the first object with the given name.
	// Returns true if it was removed, false if not found.
	// --------------------------------------------------------
	template<typename T>
	bool removeByName(std::vector<T>& list, const std::string& name) {
		int index = findIndexByName(list, name);
		if (index == -1) return false;
		list.erase(list.begin() + index);
		return true;
	}

	// --------------------------------------------------------
	// Returns a pointer to the object with the given name.
	// Returns nullptr if not found.
	// Useful when you want to modify the object.
	// --------------------------------------------------------
	template<typename T>
	T* getByName(std::vector<T>& list, const std::string& name) {
		int index = findIndexByName(list, name);
		if (index == -1) return nullptr;
		return &list[index];
	}



	// ========== ARRAYS ==========

	// --------------------------------------------------------
	// Prints an array.
	// --------------------------------------------------------
	template<typename T, size_t N>
	inline void printArray(const std::array<T, N>& arr, const std::string& title = "Array") {
		std::cout << "\n=== " << title << " ===\n";
		for (size_t i = 0; i < arr.size(); ++i) {
			std::cout << i << ": " << arr[i] << "\n";
		}
	}

	// --------------------------------------------------------
	// Finds a value in an array. Returns index or -1 if not found.
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

} // namespace Utils