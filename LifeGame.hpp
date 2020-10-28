#pragma once
#include <vector>
#include <random>
#include <array>
#include <iostream>

class LifeGame
{
public:

	static constexpr int BOARD_SIZE = 1024;

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
	bool at(size_t x, size_t y) const;
	void set(size_t x, size_t y);
	~LifeGame();

	bool first_count;
	int around_cell_cache;
};