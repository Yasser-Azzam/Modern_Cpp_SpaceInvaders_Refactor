#pragma once
#include "raylib.h"
#include "vector"

struct Resources 
{
	// TODO: Resources acquires Raylib textures but does not release them.
	// Violates RAII and causes resource leaks, make RAII wrapper types with destructor that unloads textures
	// and make Resources follow the Rule of 0 since no special constructor/copy/move/destructor needed.

	void Load();
	//void Unload();

	std::vector<Texture2D> shipTextures;
	Texture2D alienTexture;
	Texture2D barrierTexture;
	Texture2D laserTexture;

};