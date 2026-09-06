#pragma once
// ============================================================
// DynamicMenu.h
// Make it easy to create interactive numbered menus.
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
	// One option in the menu
	// text = what the user sees
	// action = the function that runs when chosen
	//--------------------------------------------------------
	struct Option {
		std::string text;				// what the user sees
		std::function<void()> action;	// what happens when chosen
	};

	class DynamicMenu {
	private:
		std::string _title;				// menu title
		std::vector<Option> _options;	// list of all options
		bool _running = true;			// controls the loop

	public:
		// Constructor - set the menu title
		DynamicMenu(const std::string& menuTitle = "Menu") : _title(menuTitle) {}

		// --------------------------------------------------------
		// Add a normal option to the options list
		// Lambda: [](){ ... } anonymous function with an empty capture list [] and no params (), ready to run a block of code
		// std::function<void()> action is the type that receives the lambda inside this method
		// Example: menu.add("View Shop", [](){ /* your_function() */ });
		// --------------------------------------------------------
		void add(const std::string& text, std::function<void()> action) {
			_options.push_back({ text, action });
		}

		// --------------------------------------------------------
		// Add an exit option that stops the menu loop
		// --------------------------------------------------------
		void addExit(const std::string& text = "Exit") {
			// [this] captures the current menu object so we can set _running = false
			_options.push_back({ text, [this]() { _running = false; } });
		}

		// --------------------------------------------------------
		// Start the menu and keeps showing it until the user choose to Exit
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
		// Stop the menu (rarely needed)
		// --------------------------------------------------------
		void stop() { _running = false; }
	};

} // namespace Menu