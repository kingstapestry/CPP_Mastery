#pragma once
// ============================================================
// EntityManager.h
// Simple generic container that can store any type of object
// Useful for shops, product lists, customer lists, etc.
// 
// Author: @kingstapestry 
// ============================================================

#include <vector>
#include <optional>
#include <algorithm>
#include <initializer_list>


namespace Data {

	template<typename T>
	class Manager {
	private:
		std::vector<T> _items;	// internal storage for the actual list of objects

	public:
		Manager() = default;

		// --------------------------------------------------------
		// Supports initializer list
		// --------------------------------------------------------
		Manager(std::initializer_list<T> list) {
			for (const auto& item : list) {
				_items.push_back(item);
			}
		}

		// --------------------------------------------------------
		// Add a new item to the manager
		// --------------------------------------------------------
		void add(const T& item) {
			_items.push_back(item);
		}

		// --------------------------------------------------------
		// Remove all items that match a condition
		// Returns true if at least one item was removed
		// Example: manager.removeIf([](const Customer& c){ return c.name == "John"; });
		// --------------------------------------------------------
		template<typename Predicate>
		bool removeIf(Predicate condition) {
			auto newEnd = std::remove_if(_items.begin(), _items.end(), condition);
			if (newEnd == _items.end()) return false;	// nothing removed
			_items.erase(newEnd, _items.end());
			return true;
		}

		// --------------------------------------------------------
		// Find the first item that matches a condition
		// Returns: std::nullopt if nothing is found
		// --------------------------------------------------------
		template<typename Predicate>
		std::optional<T> findIf(Predicate condition) {
			auto it = std::find_if(_items.begin(), _items.end(), condition);
			if (it != _items.end()) return *it;
			return std::nullopt;	// not found
		}

		// --------------------------------------------------------
		// Returns the full list (can be modified)
		// --------------------------------------------------------
		std::vector<T>& all() { return _items; }

		// --------------------------------------------------------
		// Returns the full list (read-only)
		// --------------------------------------------------------
		const std::vector<T>& all() const { return _items; }

		// --------------------------------------------------------
		// Helpers
		// --------------------------------------------------------
		size_t size() const { return _items.size(); }
		bool empty() const { return _items.empty(); }
		void clear() { _items.clear(); }
	};

} // namespace Data