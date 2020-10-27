#include "LifeGame.hpp"

unsigned long profile_ref_count;


LifeGame::LifeGame()
	: generation(0)
	//, board(BOARD_SIZE + 2, std::vector<bool>(BOARD_SIZE + 2, false))
	//, back_buffer(BOARD_SIZE + 2, std::vector<bool>(BOARD_SIZE + 2, false))
	, mt(rand())
{
	board = new bool*[BOARD_SIZE + 2];
	back_buffer = new bool*[BOARD_SIZE + 2];
	for (int i = 0; i < BOARD_SIZE + 2; i++)
	{
		board[i] = new bool[BOARD_SIZE + 2];
		back_buffer[i] = new bool[BOARD_SIZE + 2];
	}
	initByRand();
}

LifeGame::~LifeGame()
{
	for (int i = 0; i < BOARD_SIZE + 2; i++)
	{
		delete[] board[i];
		delete[] back_buffer[i];
	}

	delete[] board;
	delete[] back_buffer;
}

void LifeGame::update()
{
	generation++;
	for (int y = 1; y < BOARD_SIZE + 1; y++)
	{
		first_count = true;
		for (int x = 1; x < BOARD_SIZE + 1; x++)
		{
			back_buffer[y][x] = false;
			int around_cell_count = countAroundCell(x, y);
			if (around_cell_count == 2)
			{
				back_buffer[y][x] = board[y][x];
			}
			else if (around_cell_count == 3)
			{
				back_buffer[y][x] = true;
			}
		}
	}

	std::swap(board, back_buffer);
}

void LifeGame::initByRand()
{
	for (int y = 1; y < BOARD_SIZE - 1; y++)
	{
		for (int x = 1; x < BOARD_SIZE - 1; x++)
		{
			board[y][x] = static_cast<bool>(mt() & 0x01);
		}
	}
}

/*int LifeGame::countAroundCell(int x, int y)
{
	int c = 0;
	for (int j = y - 1; j <= y + 1; j++)
	{
		for (int i = x - 1; i <= x + 1; i++)
		{
			profile_ref_count++;
			if (x == 0 && y == 0)
			{
				continue;
			}
			c += static_cast<int>(board[j][i]);
		}
	}

	return c;
}*/


int LifeGame::countAroundCell(int x, int y)
{
	if (first_count)
	{
		int c = 0;
		for (int j = y - 1; j <= y + 1; j++)
		{
			for (int i = x - 1; i <= x + 1; i++)
			{
				profile_ref_count++;
				if (x == 0 && y == 0)
				{
					continue;
				}
				c += static_cast<int>(board[j][i]);
			}
		}

		around_cell_cache = c;
		first_count = false;
	}
	else
	{
		for (int j = y - 1; j <= y + 1; j++)
		{
			around_cell_cache += static_cast<int>(board[j][x + 1]) - static_cast<int>(board[j][x - 2]);
			profile_ref_count++;
		}

		around_cell_cache += static_cast<int>(board[y][x - 1]);
		around_cell_cache -= static_cast<int>(board[y][x]);
	}

	return around_cell_cache;
}