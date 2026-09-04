#pragma once
#include <functional>
#include <utility>
#include <forward_list>
#include <vector>

template <typename Key,typename Value,typename Hash = std::hash<Key>>
class HashMap
{
private:
	struct Bucket
	{
		std::vector<std::forward_list<std::pair<Key, Value>>> collection;
		size_t capacity;
		
		Bucket()
			: collection(10),capacity(10) { }

		bool add_element(size_t index, Key key, Value value)
		{
			if (index >= capacity) 
				return false;

			collection[index].push_front(std::make_pair(key,value));
			return true;
		}

		const Value& find(size_t index,const Key& key) const
		{
			for (const auto i : collection[index])
			{
				if (key == i.first) return i.second;
			}
		}
	};

	Bucket bucket;
	Hash hasher;
	size_t size;

public:
	HashMap()
		: bucket(),size(0), hasher(){ }


	void insert(const Key& key ,const Value& value)
	{
		if (bucket.add_element(hasher(key) % bucket.capacity, key, value))
		{
			++size;

			if (bucket.capacity / size + 1 >= 7)
			{
				//rehash()
			}
		}
	}

	const Value& find(const Key& key) const
	{
		return bucket.find(hasher(key) % bucket.capacity, key);
	}

};

