#pragma once
#include <functional>
#include <utility>
#include <forward_list>
#include <vector>
#include <stdexcept>

template <typename Key, typename Value, typename Hash = std::hash<Key>>
class HashMap
{
private:

	std::vector<std::forward_list<std::pair<Key, Value>>> buckets;
	size_t capacity;
	size_t size;
	Hash hasher;

	void rehash()
	{
		std::vector<std::forward_list<std::pair<Key, Value>>> new_buckets(capacity *= 2);

		for (const auto& i : buckets)
		{
			for (const auto& j : i)
			{
				size_t index = hasher(j.first) % capacity;
				new_buckets[index].push_front(std::make_pair(j.first, j.second));
			}
		}
		buckets = std::move(new_buckets);
	}

	void remove(const Key& key,size_t index)
	{
		buckets[index].remove_if([&key](const std::pair<Key, Value>& pair) {
			return key == pair.first;
		});
		--size;
	}

public:
	HashMap()
		:size(0),capacity(10),hasher(),buckets(10) {}


	void insert(const Key& key, const Value& value)
	{
		size_t index = hasher(key) % capacity;

		for (const auto& i : buckets[index])
		{
			if (i.first == key) return;
		}
		buckets[index].push_front(std::make_pair(key, value));
		++size;

		if (static_cast<double>(size) / capacity >= 0.7)
		{
			rehash();
		}
	}

	void erase(const Key& key)
	{
		size_t index = hasher(key) % capacity;
		for (const auto& i : buckets[index])
		{
			if (i.first == key)
			{
				remove(key, index);
				return;
			}
		}
		throw std::out_of_range("Key not found");
	}

	 const Value& find(const Key& key) const
	{
		size_t index = hasher(key) % capacity;

		for (const auto& i : buckets[index])
		{
			if (i.first == key) return i.second;
		}
		throw std::out_of_range("Key not found");
	}
};
