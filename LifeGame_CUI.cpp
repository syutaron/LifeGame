#include "LifeGame.hpp"
#include <chrono>
#include <iostream>

extern unsigned long profile_ref_count;

int main()
{
	LifeGame lg;

	auto start = std::chrono::system_clock::now();

	for (int i = 0; i < 1000; i++)
	{
		lg.update();
	}

	auto end = std::chrono::system_clock::now();

	std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << std::endl;
	std::cout << "ŽQÆ‰ñ”:" << profile_ref_count << std::endl;
	return 0;
}
