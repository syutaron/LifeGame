#include "LifeGameBit.h"



static constexpr int BIT_SIZE = sizeof(CellType) * 8;

using Board = std::vector<std::vector<CellType>>;

static constexpr int BOARD_SIZE = 1024;
static constexpr int NEEDS_WIDTH = (BOARD_SIZE + BIT_SIZE - 1) / BIT_SIZE;	// êÿÇËè„Ç∞
static constexpr CellType MLB = 1;
static constexpr CellType MSB = static_cast<CellType>(1) << (BIT_SIZE - 1);
static constexpr CellType overhang_bit_mask = makeOverhungMask((BOARD_SIZE - 1) % BIT_SIZE + 1, MSB);
static constexpr int view = static_cast<int>(MSB);

Board board;
Board back_buffer;

LifeGameBit::LifeGameBit(std::mt19937_64& mt)
	: board(BOARD_SIZE + 2, std::vector<CellType>(NEEDS_WIDTH + 2))
	, back_buffer(BOARD_SIZE + 2, std::vector<CellType>(NEEDS_WIDTH + 2))
{
	// initWithRand(mt);
}

void LifeGameBit::initWithRand(std::mt19937_64& mt)
{
	for (int y = 1; y < BOARD_SIZE + 1; y++)
	{
		for (int x = 1; x < board[0].size() - 1; x++)
		{
			board[y][x] = mt();
		}
		board[y][board[y].size() - 2] &= overhang_bit_mask;
	}
}

bool LifeGameBit::at(size_t x, size_t y) const
{
	if ((board[y + 1][x / BIT_SIZE + 1] & MSB >> (x % BIT_SIZE)) != 0)
		return true;
	return false;
}

void LifeGameBit::set(size_t x, size_t y)
{
	board[y + 1][x / BIT_SIZE + 1] |= (MSB >> (x % BIT_SIZE));
}

void LifeGameBit::update()
{
	for (int y = 1; y < BOARD_SIZE + 1; y++)
	{
		for (int x = 1; x < board[0].size() - 2; x++)
		{
			back_buffer[y][x] = updateOneCell(x, y);
		}
		back_buffer[y][board[0].size() - 2] = updateOneCell(board[0].size() - 2, y) & overhang_bit_mask;
	}

	std::swap(board, back_buffer);
}

CellType LifeGameBit::updateOneCell(size_t idx_x, size_t y)
{
	// std::array<CellType, 8> nbd;
	CellType nbd0, nbd1, nbd2, nbd3, nbd4, nbd5, nbd6, nbd7;

	CellType c = board[y][idx_x];
	nbd2 = board[y - 1][idx_x]; // n
	nbd5 = board[y + 1][idx_x]; // s

	nbd0 = c >> 1 | (board[y][idx_x - 1] & MLB) << (BIT_SIZE - 1); // w
	nbd1 = c << 1 | (board[y][idx_x + 1] & MSB) >> (BIT_SIZE - 1); // e
	nbd3 = nbd2 >> 1 | (board[y - 1][idx_x - 1] & MLB) << (BIT_SIZE - 1); // nw
	nbd4 = nbd2 << 1 | (board[y - 1][idx_x + 1] & MSB) >> (BIT_SIZE - 1); // ne
	nbd6 = nbd5 >> 1 | (board[y + 1][idx_x - 1] & MLB) << (BIT_SIZE - 1); // sw
	nbd7 = nbd5 << 1 | (board[y + 1][idx_x + 1] & MSB) >> (BIT_SIZE - 1); // se

	// std::array<CellType, 4> s;
	CellType s0, s1, s2, s3;

	s2 = nbd0 & nbd1;
	s1 = nbd0 ^ nbd1;
	s0 = ~(nbd0 | nbd1);

	s3 = s2 & nbd2;
	s2 = (s2 & ~nbd2) | (s1 & nbd2);
	s1 = (s1 & ~nbd2) | (s0 & nbd2);
	s0 = s0 & ~nbd2;

	s3 = (s3 & ~nbd3) | (s2 & nbd3);
	s2 = (s2 & ~nbd3) | (s1 & nbd3);
	s1 = (s1 & ~nbd3) | (s0 & nbd3);
	s0 = s0 & ~nbd3;

	s3 = (s3 & ~nbd4) | (s2 & nbd4);
	s2 = (s2 & ~nbd4) | (s1 & nbd4);
	s1 = (s1 & ~nbd4) | (s0 & nbd4);
	s0 = s0 & ~nbd4;

	s3 = (s3 & ~nbd5) | (s2 & nbd5);
	s2 = (s2 & ~nbd5) | (s1 & nbd5);
	s1 = (s1 & ~nbd5) | (s0 & nbd5);
	s0 = s0 & ~nbd5;

	s3 = (s3 & ~nbd6) | (s2 & nbd6);
	s2 = (s2 & ~nbd6) | (s1 & nbd6);
	s1 = (s1 & ~nbd6) | (s0 & nbd6);

	s3 = (s3 & ~nbd7) | (s2 & nbd7);
	s2 = (s2 & ~nbd7) | (s1 & nbd7);

	return s3 | (c & s2);
}