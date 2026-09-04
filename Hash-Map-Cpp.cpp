#include <iostream>
#include "HashMap.h"

int main()
{
	HashMap<int, int, std::hash<int>> hash;
	hash.insert(10, 25);

	std::cout << hash.find(10);
	
	return 0;
}