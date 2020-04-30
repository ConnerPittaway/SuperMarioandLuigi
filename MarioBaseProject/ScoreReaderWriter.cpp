#include "ScoreReaderWriter.h"

ScoreReaderWriter::ScoreReaderWriter()
{
}

ScoreReaderWriter::~ScoreReaderWriter()
{
	scores.clear();
}

void ScoreReaderWriter::WriteScores()
{
	std::ofstream outScores("Scores/Scores.txt");

	// Check if the file was opened.
	if (!outScores.is_open())
	{
		std::cout << "Error file did not open" << std::endl;
	}
	else
	{
		for (unsigned int i = 0; i < scores.size(); i++)
		{
			//std::cout << "Stored Score is: " << scores[i] << std::endl;
			if(scores[i] > 0)
			outScores << scores[i] << std::endl;
		}
	}
	std::cout << "Scores and names written" << std::endl;
	outScores.close();
}

void ScoreReaderWriter::ReadScores()
{
	//Read scores from file into array
	std::ifstream inScores("Scores/Scores.txt");
	int temp;

	while(inScores >> temp)
	{
		if (inScores.eof()) break;
		scores.push_back(temp); //Add scores to vector
		//std::cout << "temp is " << temp << std::endl;
	}
	inScores.close();
}

void ScoreReaderWriter::SortScores()
{
	std::sort(scores.begin(), scores.end(), std::greater<int>()); //Sort scores highest to lowest

	std::cout << "Sorted \n";
	for (auto x : scores)
		std::cout << x << " ";
}

void ScoreReaderWriter::InputScore(int ScoreToInput)
{
	scores.push_back(ScoreToInput);
}

