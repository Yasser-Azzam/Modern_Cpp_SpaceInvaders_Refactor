#pragma once 
#include <iostream>
#include <string>
#include <fstream>

//TODO: unused code file, delete it

struct Entity
{
	float x, y;

	void LoadLevelFromAFile(const std::string& filename);
};