#include <iostream>
#include "HashMap.h"

int main()
{
	HashMap<int, int> hash;
	hash.insert(10, 25);
	hash.insert(10, 15);

	for (int i = 0; i < 6; ++i)
	{
		hash.insert(i, i);
	}
	
	
	hash.erase(10);
	try
	{
		std::cout << "Key: 10\tValue: " << hash.find(10) << std::endl;
	}
	catch (...)
	{
		std::cout << "Key not found...\n";
	}




	 
	return 0;
}