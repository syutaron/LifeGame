#pragma once
#include <vector>
#include <random>
#include <array>

class LifeGame
{
public:

	static constexpr int BOARD_SIZE = 500;

//	using Board = std::vector<std::vector<bool>>;
 	using Board = bool**;

	Board board;
	Board back_buffer;

	int generation;

	std::random_device rand;
	std::mt19937 mt;

	LifeGame();
	void initByRand();
	void update();
	int countAroundCell(int x, int y);
	~LifeGame();

	bool first_count;
	int around_cell_cache;
};