#include <iostream>
#include "HashMap.h"

int main()
{
	HashMap<int, int, std::hash<int>> hash;
	hash.insert(10, 25);
	hash.insert(10, 15);

	for (int i = 0; i < 10; i++)
	{
		hash.insert(i, i);
	}

	std::cout << hash.find(10);
	
	return 0;
}