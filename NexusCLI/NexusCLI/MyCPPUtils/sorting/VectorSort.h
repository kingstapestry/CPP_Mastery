#pragma once
// ============================================================
// VectorSort.h
// Easy way to sort vectors of class objects
// 
// Author: @kingstapestry 
// ============================================================

#include <vector>
#include <algorithm>


namespace Sort {

	// --------------------------------------------------------
	// Sort a vector by any member variable of the class
	//
	// Examples:
	//   Sort::by(products, &Product::price);		// low to high
	//   Sort::by(products, &Product::name, false); // Z to A
	// --------------------------------------------------------
	template<typename T, typename Member>
	void by(std::vector<T>& data, Member T::* member, bool ascending = true) {
		std::sort(data.begin(), data.end(),
			[member, ascending](const T& a, const T& b) {
				// Compare the chosen member of the two objects
				if (ascending) {
					return (a.*member) < (b.*member);	// ascending order
				}
				else {
					return (a.*member) > (b.*member);	// descending order
				}
			});
	}

	// --------------------------------------------------------
	// Advanced: Sort using your own custom comparison function
	// --------------------------------------------------------
	template<typename T, typename Compare>
	void byCustom(std::vector<T>& data, Compare compareFunction) {
		std::sort(data.begin(), data.end(), compareFunction);
	}

} // namespace Sort