#pragma once
// ============================================================
// DynamicMenu.h
// Create console menus easily
// 
// Author: @kingstapestry 
// ============================================================

#include <string>
#include <vector>
#include <functional>
#include <iostream>
#include "../common/Utils.h"

namespace Menu {

	// --------------------------------------------------------
	// One menu option (text + function to run)
	//--------------------------------------------------------
	struct Option {
		std::string text;	// what the user sees
		std::function<void()> action;	// what happens when chosen
	};

	class DynamicMenu {
	private:
		std::string _title;	// menu title
		std::vector<Option> _options;	// list of all options
		bool _running = true;	// controls the loop

	public:
		// Constructor
		DynamicMenu(const std::string& menuTitle = "Menu") : _title(menuTitle) {}

		// --------------------------------------------------------
		// Add a normal option
		// --------------------------------------------------------
		void add(const std::string& text, std::function<void()> action) {
			_options.push_back({ text, action });
		}

		// --------------------------------------------------------
		// Add an exit option that stops the menu
		// --------------------------------------------------------
		void addExit(const std::string& text = "Exit") {
			// [this] captures the current menu object so we can set running = false
			_options.push_back({ text, [this]() { _running = false; } });
		}

		// --------------------------------------------------------
		// Start the menu
		// --------------------------------------------------------
		void run() {
			while (_running) {
				std::cout << "\n=== " << _title << " ===\n";

				// Print all options numbered from 1
				for (size_t i = 0; i < _options.size(); ++i) {
					std::cout << (i + 1) << " - " << _options[i].text << "\n";
				}

				int choice = Utils::inputInt("\nEnter choice: ");

				// Check if the choice is valid
				if (choice >= 1 && choice <= static_cast<int>(_options.size())) {
					_options[choice - 1].action();	// run selected function
				}
				else {
					std::cout << "Invalid choice. Please try again.\n";
				}
			}
		}

		// --------------------------------------------------------
		// Stop the menu
		// --------------------------------------------------------
		void stop() { _running = false; }
	};

} // namespace Menu