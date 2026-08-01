#pragma once
// ============================================================
// EntityManager.h
// Simple generic manager for any type of object
// 
// Author: @kingstapestry 
// ============================================================

#include <vector>
#include <optional>
#include <algorithm>

namespace Data {

	template<typename T>

	class Manager {
	private:
		std::vector<T> _items;	// internal storage

	public:

		// --------------------------------------------------------
		// Add a new item
		// --------------------------------------------------------
		void add(const T& item) {
			_items.push_back(item);
		}

		// --------------------------------------------------------
		// Remove all items that match a condition
		// Returns true if at least one item was removed
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
		// --------------------------------------------------------
		template<typename Predicate>
		std::optional<T> findIf(Predicate condition) {
			auto it = std::find_if(_items.begin(), _items.end(), condition);
			if (it != _items.end()) return *it;
			return std::nullopt;	// not found
		}

		// --------------------------------------------------------
		// Access the full list
		// --------------------------------------------------------
		std::vector<T>& all() { return _items; }
		const std::vector<T>& all() const { return _items; }

		size_t size() const { return _items.size(); }
		bool empty() const { return _items.empty(); }
		void clear() { _items.clear(); }
	};

} // namespace Data