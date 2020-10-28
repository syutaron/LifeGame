#pragma once
#include <iostream>
#include <vector>
#include <array>
#include <random>

using CellType = unsigned long long;

constexpr CellType makeOverhungMask(int bit_size, CellType msb)
{
	return bit_size == 1 ? msb : makeOverhungMask(bit_size - 1, msb | (msb >> 1));
}
class LifeGameBit
{
public:

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

	LifeGameBit(std::mt19937_64& mt);
	void initWithRand(std::mt19937_64& mt);
	bool at(size_t x, size_t y) const;
	void set(size_t x, size_t y);
	void update();
	CellType updateOneCell(size_t idx_x, size_t y);
};

