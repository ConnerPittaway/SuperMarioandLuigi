#include "LevelLoader.h"
#include <string>
#include <fstream>
#include <iostream>


LevelLoader::LevelLoader(std::string path)
{
	int LevelWidth = 0, LevelHeight = 0, LevelNum;
	std::string line;
	std::ifstream mapInput(path);
	std::vector<std::vector<char>> map;

	mapInput >> LevelWidth;
	mapInput >> LevelHeight;
	//mapInput >> LevelNum;

	x = LevelWidth;
	y = LevelHeight;
	
	while (std::getline(mapInput, line))
	{
		std::vector<char> row;
		for (char& c : line)
		{
			if (c != '\n')
				row.push_back(c);
		}
		map.push_back(row);
	}

	for (std::vector<char>& row : map) {
		for (char& c : row) {
			std::cout << c;
		}

		std::cout << '\n';
	}

	level = map;
}

int LevelLoader::GetTileAt(unsigned int h, unsigned int w)
{
	if (h <= y && w <= x && h > 0)
	{
		return (char)level.at(h).at(w);
	}
	else if (h >= y || w >= x)
	{
		return(0);
	}
	return 0;
}

void LevelLoader::ChangeTileAt(unsigned int row, unsigned int column, unsigned int newValue)
{
	level[row][column] = newValue;
}

int LevelLoader::GetRowSize()
{
	return x;
}

int LevelLoader::GetColumnSize()
{
	return y;
}
