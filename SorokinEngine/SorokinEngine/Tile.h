#include <cstdint>
#pragma once

class Tile
{
public:
	Tile(uint8_t id);
	~Tile();

	//uint8_t inline getID() { return id }

private:
	uint8_t id;
	bool bIsActive;

};

