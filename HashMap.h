#pragma once
#include <functional>
#include <utility>
#include <forward_list>
#include <vector>
#include <math.h>

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

		Bucket(size_t size, size_t capacity)
			:collection(size),capacity(capacity){ }

		Bucket(const Bucket& other)
			:collection(other.collection),capacity(other.capacity){ }

		Bucket(Bucket&& other) noexcept
			:collection(std::move(other.collection)),capacity(other.capacity){ }

		const Bucket& operator = (const Bucket& other)
		{
			if (this == &other) return *this;

			this->collection = other.collection;
			this->capacity = other.capacity;
			
			return *this;
		}

		const Bucket& operator = (Bucket&& other) noexcept
		{
			if (this == &other) return *this;

			this->collection = std::move(other.collection);

			if (this->capacity < other.capacity)
			{
				this->capacity = other.capacity;
			}
			return *this;
		}

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

		void resize_collection(size_t capacity)
		{
			collection.resize(capacity);
			collection.reserve(capacity);

			this->capacity = capacity;
		}
	};

	Bucket bucket;
	Hash hasher;
	size_t size;
	size_t n;

	void rehash()
	{
		++n;
		Bucket new_bucket;
		new_bucket = std::move(bucket);

		this->bucket = std::move(new_bucket);
		bucket.resize_collection(bucket.capacity * 2);
	}

public:
	HashMap()
		: bucket(),size(0), hasher(),n(0){ }


	void insert(const Key& key ,const Value& value)
	{
		int iterator = 0;
		for (const auto i : bucket.collection)
		{
			for (const auto j : bucket.collection[iterator])
			{
				if (j.first == key) return;
			}
			iterator++;
		}

		if(bucket.add_element(hasher(key) % bucket.capacity, key, value)) ++size;

		if (static_cast<double>(size / bucket.capacity) >= 0.7)
		{
			rehash();
		}
	}

	const Value& find(const Key& key) const
	{
		return bucket.find(hasher(key) % static_cast<size_t>((bucket.capacity / pow(2,n))), key);
	}
};

