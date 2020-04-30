#pragma once
#include <vector>
#include <string.h>
#include <fstream>
#include <iostream>
#include <algorithm>

class ScoreReaderWriter
{
public:
	ScoreReaderWriter();
	~ScoreReaderWriter();

	void WriteScores();
	void ReadScores();

	void SortScores();
	void InputScore(int ScoreToInput);

	std::vector<int> scores;
};

