#pragma once
// ============================================================
// ClassUtils.h
// Helpers for working with vectors of class objects
// Again extremely useful for shops, products, customers, etc.
// 
// Author: @kingstapestry 
// ============================================================

#include <vector>
#include <string>
#include <iostream>
#include <optional>


namespace ClassUtils {

	// --------------------------------------------------------
	// Finds the index of an object by its .name member
	// Returns -1 if not found
	// --------------------------------------------------------
	template<typename T>
	int findIndexByName(const std::vector<T>& list, const std::string& name) {
		for (size_t i = 0; i < list.size(); ++i) {
			if (list[i].name == name) {
				return static_cast<int>(i);
			}
		}
		return -1;
	}

	// --------------------------------------------------------
	// Returns true if an object with that name exists in the list
	// --------------------------------------------------------
	template<typename T>
	bool existsByName(const std::vector<T>& list, const std::string& name) {
		return findIndexByName(list, name) != -1;
	}

	// --------------------------------------------------------
	// Removes the first object with the given name
	// Returns true if it was removed, false if not found
	// --------------------------------------------------------
	template<typename T>
	bool removeByName(std::vector<T>& list, const std::string& name) {
		int index = findIndexByName(list, name);
		if (index == -1) return false;
		list.erase(list.begin() + index);
		return true;
	}

	// --------------------------------------------------------
	// Returns a pointer to the object with the given name
	// Returns nullptr if not found
	// Useful when you want to modify the object
	// --------------------------------------------------------
	template<typename T>
	T* getByName(std::vector<T>& list, const std::string& name) {
		int index = findIndexByName(list, name);
		if (index == -1) return nullptr;
		return &list[index];
	}

	// --------------------------------------------------------
	// Prints a numbered list of objects (must have a .name member)
	// --------------------------------------------------------
	template<typename T>
	void printNames(const std::vector<T>& list, const std::string& title = "Items") {
		std::cout << "\n=== " << title << " ===\n";
		if (list.empty()) {
			std::cout << "(empty)\n";
			return;
		}
		for (size_t i = 0; i < list.size(); ++i) {
			std::cout << (i + 1) << ". " << list[i].name << "\n";
		}
	}

	// --------------------------------------------------------
	// Safely gets an object by index
	// Returns std::nullopt if the index is invalid
	// --------------------------------------------------------
	template<typename T>
	std::optional<T> getAt(const std::vector<T>& list, int index) {
		if (index < 0 || index >= static_cast<int>(list.size())) {
			return std::nullopt;
		}
		return list[index];
	}

} // namespace ClassUtils