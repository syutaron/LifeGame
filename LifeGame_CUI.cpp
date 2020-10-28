#include "LifeGame.hpp"
#include "LifeGameBit.h"
#include <chrono>
#include <iostream>

extern unsigned long profile_ref_count;

void printlnBit(unsigned char uc)
{
	for (int i = 0; i < 8; i++)
	{
		std::cout << (0x01 & (uc >> i)) << " ";
	}
	std::cout << std::endl;
}

void compBoard(const LifeGame& lg, const LifeGameBit& lgb)
{
	if (lg.BOARD_SIZE != lgb.BOARD_SIZE)
	{
		std::cout << "盤面のサイズが違う" << std::endl;
	}

	for (int y = 0; y < lg.BOARD_SIZE; y++)
	{
		for (int x = 0; x < lg.BOARD_SIZE; x++)
		{
			if (lg.at(x, y) != lgb.at(x, y))
			{
				std::cout << "セル (x, y) = (" << x << ", " << y << ") が一致しない" << std::endl;
				return;
			}
		}
	}

	std::cout << "全て一致" << std::endl;
}

void makeRandom(LifeGame& lg, LifeGameBit& lgb, std::mt19937_64& mt)
{
	for (int y = 0; y < lg.BOARD_SIZE; y++)
	{
		for (int x = 0; x < lg.BOARD_SIZE; x++)
		{
			if ((mt() & 3) == 0)
			{
				lg.set(x, y);
				lgb.set(x, y);
			}
		}
	}
}

int main()
{
	std::random_device rand;
	std::mt19937_64 mt(rand());

	LifeGameBit lgb(mt);
	LifeGame lg;

	makeRandom(lg, lgb, mt);

	auto start = std::chrono::system_clock::now();

	for (int i = 0; i < 200; i++)
	{
		// lg.update();
		lgb.update();
	}

	auto end = std::chrono::system_clock::now();

	std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << std::endl;

	// compBoard(lg, lgb);
	return 0;
}
