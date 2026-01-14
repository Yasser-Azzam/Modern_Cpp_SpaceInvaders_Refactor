#include "game.h"
#include <iostream>
#include <vector>
#include <chrono>
#include <thread>
#include <fstream>
#include "Collision_System.h"
#include "Player_System.h"
#include "Alien_System.h"
#include "Wall_System.h"
#include "Projectile_System.h"
#include "UI_System.h"
#include "Input_System.h"
#include "Math_Utilities.h"


Game::Game(State initialState)
	: gameState(initialState)
	, score(0)
{
	BackgroundSystem::Initialize(stars, config.starCount);

	SpawnWalls();

	player = Player{};

	SpawnAliens();
}

void Game::End() noexcept
{
	CleanupWorld();
	newHighScore = CheckNewHighScore();
	gameState = State::ENDSCREEN;
}

void Game::Continue() noexcept
{
	gameState = State::STARTSCREEN;
}

void Game::Reset(State initialState)
{
	ResetGameState(initialState);
	ResetPlayerAndCombat();
	ResetWorld();
	ResetBackground();
	ResetUI();
}

void Game::ResetGameState(State initialState) noexcept
{
	gameState = initialState;
	score = 0;
	shootTimer = 0;
	newHighScore = false;
}

void Game::ResetPlayerAndCombat() noexcept
{
	player = Player{};
	Projectiles.clear();
}

void Game::ResetWorld()
{
	SpawnWalls();
	Aliens.clear();
	SpawnAliens();
}

void Game::ResetBackground()
{
	BackgroundSystem::Initialize(stars, 600);
}

void Game::ResetUI() noexcept
{
	playerName.clear();
	mouseOnText = false;
	framesCounter = 0;
}

void Game::CleanupWorld() noexcept
{
	Projectiles.clear();
	Walls.clear();
	Aliens.clear();
}

void Game::Update()
{
	InputSystem::HandleGameInput(*this);

	if (gameState != State::GAMEPLAY) return;

	PlayerSystem::Update(player);
	AlienSystem::Update(Aliens);
	WallSystem::Update(Walls);
	ProjectileSystem::Update(Projectiles);

	CollisionContext ctx{
		player,
		Aliens,
		Walls,
		Projectiles,
		score
	};

	CollisionSystem::HandleProjectileCollisions(ctx);

	UpdateBackground();

	if (Aliens.empty()) SpawnAliens();
	SpawnEnemyProjectile();

	if (player.lives < 1) End();
}


void Game::Render() noexcept
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
	for (int row = 0; row < config.alienFormationHeight; row++)
	{
		for (int col = 0; col < config.alienFormationWidth; col++) 
		{
			Alien newAlien = Alien();
			newAlien.position.x = static_cast<float>(formationX + 450 + (col * config.alienSpacing));
			newAlien.position.y = static_cast<float>(formationY + (row * config.alienSpacing));
			Aliens.push_back(newAlien);
			std::cout << "Find Alien -X:" << newAlien.position.x << std::endl;
			std::cout << "Find Alien -Y:" << newAlien.position.y << std::endl;
		}
	}

}

void Game::SpawnWalls()
{
	Walls.clear();
	const float window_width = static_cast<float>(GetScreenWidth());
	const float window_height = static_cast<float>(GetScreenHeight());
	const float wall_distance = window_width / (wallCount + 1);

	for (int i = 0; i < wallCount; i++)
	{
		Wall newWall;
		newWall.position.y = window_height - 250;
		newWall.position.x = wall_distance * (i + 1);
		newWall.active = true;
		Walls.push_back(newWall);
	}
}

bool Game::CheckNewHighScore() noexcept
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

			i = static_cast<int>(Leaderboard.size());

		}
	}
}

void Game::SpawnPlayerProjectile()
{
	const float window_height = static_cast<float>(GetScreenHeight());
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

	const int index = Aliens.size() > 1 ? rand() % Aliens.size() : 0;

	Projectile newProjectile;
	newProjectile.position = Aliens[index].position;
	newProjectile.position.y += 40;
	newProjectile.speed = -15;
	newProjectile.type = EntityType::ENEMY_PROJECTILE;
	Projectiles.push_back(newProjectile);
}

void Game::UpdateBackground() noexcept
{
	playerPos = { player.x_pos, static_cast<float>(player.player_base_height) };
	cornerPos = { 0, static_cast<float>(player.player_base_height) };
	offset = MathUtilities::Distance(playerPos, cornerPos) * -1;
	BackgroundSystem::Update(stars, offset / config.backgroundScrollDivisor);
}

void Game::RenderStartScreen() const noexcept
{
	DrawText("SPACE INVADERS", 200, 100, 160, YELLOW);

	DrawText("PRESS SPACE TO BEGIN", 200, 350, 40, YELLOW);

}

void Game::RenderGameplay() const noexcept
{
	BackgroundSystem::Render(stars);

	PlayerSystem::Render(player, resources);
	AlienSystem::Render(Aliens, resources);
	WallSystem::Render(Walls, resources);
	ProjectileSystem::Render(Projectiles, resources);
	UISystem::RenderHUD(*this);
}

void Game::RenderEndScreen() const noexcept
{
	if (newHighScore)
		UISystem::RenderHighScoreEntry(*this);
	else
		UISystem::RenderLeaderboard(*this);
}

Player::Player() noexcept
{
	x_pos = static_cast<float>(GetScreenWidth()) / 2.0f;
}

void Player::TakeDamage(int amount) noexcept
{
	lives -= amount;
	if (lives < 0) lives = 0;
}

Vector2 Player::GetPosition() const noexcept
{
	return { x_pos, GetScreenHeight() - player_base_height };
}

float Player::GetRadius() const noexcept
{
	return radius;
}

int Player::GetLives() const noexcept
{
	return lives;
}

void Wall::TakeDamage(int amount) noexcept
{
	health -= amount;
	if (health < 0) health = 0;
	active = health > 0;
}

bool Wall::IsDestroyed() const noexcept
{
	return !active;
}

Vector2 Wall::GetPosition() const noexcept
{
	return position;
}

float Wall::GetRadius() const noexcept
{
	return static_cast<float>(radius);
}

Vector2 Alien::GetPosition() const noexcept
{
	return position;
}

float Alien::GetRadius() const noexcept
{
	return radius;
}