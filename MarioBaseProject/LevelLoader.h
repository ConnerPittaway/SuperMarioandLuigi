#pragma once
#include <string>
#include <vector>
#include "Constants.h"

class LevelLoader
{
public:
	LevelLoader(std::string path);
	~LevelLoader();

	std::vector<std::vector<char>> level;
	int x, y, num;

	int GetTileAt(unsigned int h, unsigned int w);
	void ChangeTileAt(unsigned int row, unsigned int column, unsigned int newValue);
	void ShowMap();

	int GetRowSize();
	int GetColumnSize();
private:

};

