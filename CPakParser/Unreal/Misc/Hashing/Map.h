#pragma once

#include "parallel_hashmap/phmap.h"

#include "Serialization/Archives.h"

template <class K, class V>
using TMap = phmap::flat_hash_map<K, V>;

template<class T>
FArchive& operator<<(FArchive& Ar, phmap::flat_hash_set<T>& InSet)
{
	int32_t NewNumElements = 0;
	Ar << NewNumElements;

	if (!NewNumElements) return Ar;

	InSet.clear();
	InSet.reserve(NewNumElements);

	for (size_t i = 0; i < NewNumElements; i++)
	{
		T Element;
		Ar << Element;
		InSet.insert(Element);
	}

	return Ar;
}

template<class Key, class Value>
FArchive& operator<<(FArchive& Ar, TMap<Key, Value>& InMap)
{
	auto Pairs = phmap::flat_hash_set<std::pair<Key, Value>>();

	int32_t NewNumElements = 0;
	Ar << NewNumElements;

	if (!NewNumElements) return Ar;

	InMap.reserve(NewNumElements);

	for (size_t i = 0; i < NewNumElements; i++)
	{
		auto Pair = std::pair<Key, Value>();

		Ar << Pair;

		InMap.insert_or_assign(Pair.first, Pair.second);
	}

	return Ar;
}