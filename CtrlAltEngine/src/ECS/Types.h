#pragma once
#ifndef TYPE_H
#define TYPE_H

#include <bitset>
#include <vector>

namespace ECS
{
	using EntityID = uint64_t;

	using EntityIndex = uint32_t;

	using EntityVersion = uint32_t;

	// Component ID
	using ComponentID = std::size_t;

	// Group ID
	using Group = std::size_t;

	// Max number of components
	constexpr std::size_t MAX_COMPONENTS = 32;

	// Max number of groups
	constexpr std::size_t MAX_GROUPS = 32;

	// Signature
	using Signature = std::bitset<MAX_COMPONENTS>;

	// Group Bitset
	using GroupBitset = std::bitset<MAX_GROUPS>;

	// Component Array
	template <typename T>
	std::vector<T> componentArray;

	// Group Array
	std::vector<GroupBitset> groupArray;
}


#endif