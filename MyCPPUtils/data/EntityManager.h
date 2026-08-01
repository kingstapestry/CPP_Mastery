#pragma once
// ============================================================
// EntityManager.h
// Simple generic manager
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
		std::vector<T> _items;

	public:

		void add(const T& item) {
			_items.push_back(item);
		}

		// Remove items that match a condition
		template<typename Predicate>
		bool removeIf(Predicate condition) {
			auto newEnd = std::remove_if(_items.begin(), _items.end(), condition);
			if (newEnd == _items.end()) return false;
			_items.erase(newEnd, _items.end());
			return true;
		}

		// Find first matching item
		template<typename Predicate>
		std::optional<T> findIf(Predicate condition) {
			auto it = std::find_if(_items.begin(), _items.end(), condition);
			if (it != _items.end()) return *it;
			return std::nullopt;
		}

		std::vector<T>& all() { return _items; }
		const std::vector<T>& all() const { return _items; }

		size_t size() const { return _items.size(); }
		bool empty() const { return _items.empty(); }
		void clear() { _items.clear(); }
	};

} // namespace Data