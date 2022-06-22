#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "sheet.h"

std::vector<Note> ReadSheet(std::string path)
{
	std::vector<Note> ret;

	std::ifstream file;
	file.open(path, std::ios::in);
	
	int input;
	int index = 0;
	Note current{};
	while (file >> input)
	{
		if (index == 0)
		{
			current.Note = input;
			index++;
		}
		else if (index == 1)
		{
			current.Velocity = input;
			index++;
		}
		else
		{
			current.Duration = input;
			ret.push_back(current);
			current = Note{};
			index = 0;
		}
	}
	file.close();

	return ret;
}