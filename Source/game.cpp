#include "game.h"
#include <iostream>
#include <vector>
#include <chrono>
#include <thread>
#include <fstream>
#include "Collision_System.h"

// MATH FUNCTIONS
float lineLength(Vector2 A, Vector2 B) //Uses pythagoras to calculate the length of a line
{
	float length = sqrtf(pow(B.x - A.x, 2) + pow(B.y - A.y, 2));

	return length;
}

bool pointInCircle(Vector2 circlePos, float radius, Vector2 point) // Uses pythagoras to calculate if a point is within a circle or not
{
	float distanceToCentre = lineLength(circlePos, point);

	if (distanceToCentre < radius)
	{
		return true;
	}
	else
	{
		return false;
	}
}
//TODO:^^those two functions are free functions used for collision detection,
//I dont see any issues with them but I should keep an eye on them just in case


Game::Game(State initialState)
	: gameState(initialState)
	, score(0)
	, background(600) // ✅ constructed here
{
	float window_width = static_cast<float>(GetScreenWidth());
	float window_height = static_cast<float>(GetScreenHeight());

	float wall_distance = window_width / (wallCount + 1);

	for (int i = 0; i < wallCount; i++)
	{
		Wall newWall;
		newWall.position.y = window_height - 250;
		newWall.position.x = wall_distance * (i + 1);
		newWall.active = true;
		Walls.push_back(newWall);
	}

	player = Player{};

	SpawnAliens();
}

//I see no issue here, with the "end", "continue" and "launch" functions.
// they seem to have been made a for a single and they only do that
//in the case of "End()" you could argue its doing multiple things(clear the screen, check if the score is a new high score and change game state)
//but I can't think of a better way that I would find more readable/optimal(for now at least) 
void Game::End()
{
	//SAVE SCORE AND UPDATE SCOREBOARD
	Projectiles.clear();
	Walls.clear();
	Aliens.clear();
	newHighScore = CheckNewHighScore();
	gameState = State::ENDSCREEN;
}

void Game::Continue()
{
	SaveLeaderboard();
	gameState = State::STARTSCREEN;
}

// TODO: Game::Update() is really long and deeply nested.
// It mixes input handling, physics, collision detection, spawning, scoring, and cleanup.
// Extract responsibilities into smaller functions or systems and reduce nesting by using algorithms if possible.
void Game::Update()
{
	HandleInput();

	if (gameState != State::GAMEPLAY) return;

	player.Update();

	for (auto& alien : Aliens) {
		alien.Update();
		if (alien.position.y > GetScreenHeight() - player.player_base_height)
			End();
	}

	for (auto& proj : Projectiles) proj.Update();
	for (auto& wall : Walls) wall.Update();

	HandleCollisions();

	UpdateBackground();

	if (Aliens.empty())
		SpawnAliens();

	SpawnEnemyProjectile();

	if (player.lives < 1)
		End();
}


void Game::Render()
{
	switch (gameState)
	{
	case State::STARTSCREEN:
		RenderStartScreen();
		break;

	case State::GAMEPLAY:
		RenderGameplay();
		break;

	case State::ENDSCREEN:
		RenderEndScreen();
		break;
	default:
		//SHOULD NOT HAPPEN
		break;
	}
}

void Game::SpawnAliens()
{
	for (int row = 0; row < formationHeight; row++) {
		for (int col = 0; col < formationWidth; col++) {
			Alien newAlien = Alien();
			newAlien.position.x = formationX + 450 + (col * alienSpacing);
			newAlien.position.y = formationY + (row * alienSpacing);
			Aliens.push_back(newAlien);
			std::cout << "Find Alien -X:" << newAlien.position.x << std::endl;
			std::cout << "Find Alien -Y:" << newAlien.position.y << std::endl;
		}
	}

}

bool Game::CheckNewHighScore()
{
	if (score > Leaderboard[4].score)
	{
		return true;
	}

	return false;
}

void Game::InsertNewHighScore(std::string name)
{
	PlayerData newData;
	newData.name = name;
	newData.score = score;

	for (int i = 0; i < Leaderboard.size(); i++)
	{
		if (newData.score > Leaderboard[i].score)
		{

			Leaderboard.insert(Leaderboard.begin() + i, newData);

			Leaderboard.pop_back();

			i = Leaderboard.size();

		}
	}
}

void Game::LoadLeaderboard()
{
}

//Dunno what is going on here, the file doesn't exist so this function isn't necessary but it wont build or compile if i remove it
void Game::SaveLeaderboard()
{

}

void Game::HandleCollisions()
{
	CollisionSystem::HandleProjectileCollisions(*this);
}


void Game::HandleInput()
{
	if (gameState == State::GAMEPLAY)
	{
		// Player shooting
		if (IsKeyPressed(KEY_SPACE))
			SpawnPlayerProjectile();

		// Quit
		if (IsKeyReleased(KEY_Q))
			End();
	}
	else if (gameState == State::STARTSCREEN)
	{
		if (IsKeyReleased(KEY_SPACE))
			*this = Game{ State::GAMEPLAY };
	}
	else if (gameState == State::ENDSCREEN)
	{
		EndScreenInput();
	}
}

void Game::EndScreenInput()
{
	if (!newHighScore)
	{
		if (IsKeyReleased(KEY_ENTER))
			Continue();
		return;
	}

	mouseOnText = CheckCollisionPointRec(GetMousePosition(), textBox);

	SetMouseCursor(mouseOnText ? MOUSE_CURSOR_IBEAM
		: MOUSE_CURSOR_DEFAULT);

	if (mouseOnText)
	{
		int key = GetCharPressed();
		while (key > 0)
		{
			if ((key >= 32) && (key <= 125) && (letterCount < 8))
			{
				name[letterCount++] = (char)key;
				name[letterCount] = '\0';
			}
			key = GetCharPressed();
		}

		if (IsKeyPressed(KEY_BACKSPACE) && letterCount > 0)
		{
			name[--letterCount] = '\0';
		}

		framesCounter++;
	}
	else
	{
		framesCounter = 0;
	}

	if (letterCount > 0 && letterCount < 9 && IsKeyReleased(KEY_ENTER))
	{
		std::string nameEntry(name);

		InsertNewHighScore(nameEntry);

		newHighScore = false;
	}
}

void Game::SpawnPlayerProjectile()
{
	float window_height = static_cast<float>(GetScreenHeight());
	Projectile newProjectile;
	newProjectile.position.x = player.x_pos;
	newProjectile.position.y = window_height - 130;
	newProjectile.type = EntityType::PLAYER_PROJECTILE;
	Projectiles.push_back(newProjectile);
}

void Game::SpawnEnemyProjectile()
{
	if (shootTimer <= 59)
	{
		shootTimer++;
		return;
	}
	shootTimer = 0;

	int index = Aliens.size() > 1 ? rand() % Aliens.size() : 0;

	Projectile newProjectile;
	newProjectile.position = Aliens[index].position;
	newProjectile.position.y += 40;
	newProjectile.speed = -15;
	newProjectile.type = EntityType::ENEMY_PROJECTILE;
	Projectiles.push_back(newProjectile);
}

void Game::UpdateBackground()
{
	playerPos = { player.x_pos, (float)player.player_base_height };
	cornerPos = { 0, (float)player.player_base_height };
	offset = lineLength(playerPos, cornerPos) * -1;
	background.Update(offset / 15);
}

void Game::RenderStartScreen() const
{
	DrawText("SPACE INVADERS", 200, 100, 160, YELLOW);

	DrawText("PRESS SPACE TO BEGIN", 200, 350, 40, YELLOW);

}

void Game::RenderGameplay() const
{
	background.Render();

	RenderHUD();
	RenderPlayer();
	RenderProjectiles();
	RenderWalls();
	RenderAliens();
}

void Game::RenderEndScreen() const
{
	if (newHighScore)
		RenderHighScoreEntry();
	else
		RenderLeaderboard();
}

void Game::RenderHUD() const
{
	DrawText(TextFormat("Score: %i", score), 50, 20, 40, YELLOW);
	DrawText(TextFormat("Lives: %i", player.lives), 50, 70, 40, YELLOW);
}

void Game::RenderPlayer() const
{
	player.Render(GetPlayerTexture());
}

Texture2D Game::GetPlayerTexture() const
{
	return  resources.shipTextures[player.activeTexture].get();
}

void Game::RenderProjectiles() const
{
	for (const auto& proj : Projectiles)
		proj.Render(resources.laserTexture.get());
}

void Game::RenderWalls() const
{
	for (const auto& wall : Walls)
		wall.Render(resources.barrierTexture.get());
}

void Game::RenderAliens() const
{
	for (const auto& alien : Aliens)
		alien.Render(resources.alienTexture.get());
}

void Game::RenderHighScoreEntry() const
{
	DrawText("NEW HIGHSCORE!", 600, 300, 60, YELLOW);

	// BELOW CODE IS FOR NAME INPUT RENDER
	DrawText("PLACE MOUSE OVER INPUT BOX!", 600, 400, 20, YELLOW);

	DrawRectangleRec(textBox, LIGHTGRAY);
	if (mouseOnText)
	{
		// HOVER CONFIRMIATION
		DrawRectangleLines((int)textBox.x, (int)textBox.y, (int)textBox.width, (int)textBox.height, RED);
	}
	else
	{
		DrawRectangleLines((int)textBox.x, (int)textBox.y, (int)textBox.width, (int)textBox.height, DARKGRAY);
	}

	//Draw the name being typed out
	DrawText(name, (int)textBox.x + 5, (int)textBox.y + 8, 40, MAROON);

	//Draw the text explaining how many characters are used
	DrawText(TextFormat("INPUT CHARS: %i/%i", letterCount, 8), 600, 600, 20, YELLOW);

	if (mouseOnText)
	{
		if (letterCount < 9)
		{
			// Draw blinking underscore char
			if (((framesCounter / 20) % 2) == 0)
			{
				DrawText("_", (int)textBox.x + 8 + MeasureText(name, 40), (int)textBox.y + 12, 40, MAROON);
			}

		}
		else
		{
			//Name needs to be shorter
			DrawText("Press BACKSPACE to delete chars...", 600, 650, 20, YELLOW);
		}

	}

	// Explain how to continue when name is input
	if (letterCount > 0 && letterCount < 9)
	{
		DrawText("PRESS ENTER TO CONTINUE", 600, 800, 40, YELLOW);
	}
}

void Game::RenderLeaderboard() const
{
	DrawText("PRESS ENTER TO CONTINUE", 600, 200, 40, YELLOW);
	DrawText("LEADERBOARD", 50, 100, 40, YELLOW);

	for (int i = 0; i < Leaderboard.size(); i++)
	{
		const char* tempNameDisplay = Leaderboard[i].name.c_str();
		DrawText(tempNameDisplay, 50, 140 + (i * 40), 40, YELLOW);
		DrawText(TextFormat("%i", Leaderboard[i].score),
			350, 140 + (i * 40), 40, YELLOW);
	}
}

Player::Player()
{
	x_pos = static_cast<float>(GetScreenWidth()) / 2.0f;
}

void Player::Update() 
{

	//Movement
	direction = 0;
	if (IsKeyDown(KEY_LEFT))
	{
		direction--;
	}
	if (IsKeyDown(KEY_RIGHT))
	{
		direction++;
	}

	x_pos += speed * direction;

	if (x_pos < 0 + radius)
	{
		x_pos = 0 + radius;
	}
	else if (x_pos > GetScreenWidth() - radius)
	{
		x_pos = GetScreenWidth() - radius;
	}


	//Determine frame for animation
	timer += GetFrameTime();

	if (timer > 0.4 && activeTexture == 2)
	{
		activeTexture = 0;
		timer = 0;
	}
	else if (timer > 0.4)
	{
		activeTexture++;
		timer = 0;
	}

	
}

void Player::Render(Texture2D texture) const
{
	float window_height = GetScreenHeight(); 

	DrawTexturePro(texture,
		{
			0,
			0,
			352,
			352,
		},
		{
			x_pos, window_height - player_base_height,
			100,
			100,
		}, { 50, 50 },
		0,
		WHITE);
}


void Projectile::Update()
{
	position.y -= speed;

	// UPDATE LINE POSITION
	lineStart.y = position.y - 15;
	lineEnd.y   = position.y + 15;

	lineStart.x = position.x;
	lineEnd.x   = position.x;
}

void Projectile::Render(Texture2D texture) const
{
	DrawTexturePro(texture,
		{
			0,
			0,
			176,
			176,
		},
		{
			position.x,
			position.y,
			50,
			50,
		}, { 25 , 25 },
		0,
		WHITE);
}

void Wall::Render(Texture2D texture) const
{
	DrawTexturePro(texture,
		{
			0,
			0,
			704,
			704,
		},
		{
			position.x,
			position.y,
			200,
			200,
		}, { 100 , 100 },
		0,
		WHITE);


	DrawText(TextFormat("%i", health), position.x-21, position.y+10, 40, RED);
	
}

void Wall::Update() 
{

	// set walls as inactive when out of health
	if (health < 1)
	{
		active = false;
	}


}

void Alien::Update() 
{
	int window_width = GetScreenWidth(); 

	if (moveRight)
	{
		position.x += speed; 

		if (position.x >= GetScreenWidth())
		{
			moveRight = false; 
			position.y += 50; 
		}
	}
	else 
	{
		position.x -= speed; 

		if (position.x <= 0)
		{
			moveRight = true; 
			position.y += 50; 
		}
	}
}

void Alien::Render(Texture2D texture) const
{

	

	DrawTexturePro(texture,
		{
			0,
			0,
			352,
			352,
		},
		{
			position.x,
			position.y,
			100,
			100,
		}, {50 , 50},
		0,
		WHITE);
}


//BACKGROUND
void Star::Update(float starOffset)
{
	position.x = initPosition.x + starOffset;
	position.y = initPosition.y;

}

void Star::Render() const
{
	DrawCircle((int)position.x, (int)position.y, size, color);
}


Background::Background(int starAmount)
{
	Stars.reserve(starAmount);

	for (int i = 0; i < starAmount; i++)
	{
		Star newStar;
		newStar.initPosition.x = GetRandomValue(-150, GetScreenWidth() + 150);
		newStar.initPosition.y = GetRandomValue(0, GetScreenHeight());
		newStar.color = SKYBLUE;
		newStar.size = GetRandomValue(1, 4) / 2.0f;

		Stars.push_back(newStar);
	}
}

void Background::Update(float offset)
{
	for (int i = 0; i < Stars.size(); i++)
	{
		Stars[i].Update(offset);
	}
	
}

void Background::Render() const
{
	for (int i = 0; i < Stars.size(); i++)
	{
		Stars[i].Render();
	}
}
