#pragma once
#include "raylib.h"
#include <vector>
#include "Resources.h"
#include <string>
#include "Background_System.h"
#include "GameConfig.h"

enum struct State
{
	STARTSCREEN,
	GAMEPLAY,
	ENDSCREEN
};

enum struct EntityType
{
	PLAYER,
	ENEMY,
	PLAYER_PROJECTILE,
	ENEMY_PROJECTILE
};

struct PlayerData
{
	std::string name{};
	int score{};
};

struct Player
{
public:
	float x_pos;
	float speed = 7.0f;
	float player_base_height = 70.0f;
	float radius = 50.0f;

	int lives = 3;
	int direction = 0;
	int activeTexture = 0;
	float timer = 0.0f;

	EntityType type = EntityType::PLAYER;

	Player() noexcept;

	void TakeDamage(int amount = 1) noexcept;
	Vector2 GetPosition() const noexcept;
	float GetRadius() const noexcept;
	int GetLives() const noexcept;
};


struct Projectile
{
public: 
public:
	Vector2 position{};
	int speed = 15;
	EntityType type{};
	bool alive = true;

	Vector2 lineStart{};
	Vector2 lineEnd{};

	bool isAlive() const noexcept { return alive; }
};

struct Wall 
{
public: 
	Vector2 position{ 0.0f, 0.0f };
	Rectangle rec{};
	bool active = true;

	Color color = WHITE;
	int health = 50;
	int radius = 60;

	void TakeDamage(int amount = 1) noexcept;
	bool IsDestroyed() const noexcept;
	Vector2 GetPosition() const noexcept;
	float GetRadius() const noexcept;
};

struct Alien
{
public:
	
	Color color = WHITE;
	Vector2 position{ 0.0f, 0.0f };

	float radius = 30.0f;
	bool moveRight = true;
	bool alive = true;


	EntityType type = EntityType::ENEMY;
	int speed = 2;

	Vector2 GetPosition() const noexcept;
	float GetRadius() const noexcept;
};

struct Background
{
public:
	std::vector<Star> Stars;
};

struct Game
{
public:
	State gameState;

	GameConfig config{};

	int score = 0;
	int wallCount = 5;

	float shootTimer = 0.0f;

	int formationX = 100;
	int formationY = 50;

	bool newHighScore = false;

	Resources resources;
	Player player;

	std::vector<Projectile> Projectiles;
	std::vector<Wall> Walls;
	std::vector<Alien> Aliens;

	std::vector<PlayerData> Leaderboard{
		{"Player 1", 500},
		{"Player 2", 400},
		{"Player 3", 300},
		{"Player 4", 200},
		{"Player 5", 100}
	};

	std::vector<Star> stars;

	Vector2 playerPos{};
	Vector2 cornerPos{};
	float offset = 0.0f;

	std::string playerName;

	Rectangle textBox{ 600, 500, 225, 50 };
	bool mouseOnText = false;
	int framesCounter = 0;

	explicit Game(State initialState);

	void Update();
	void Render() noexcept;

	void End() noexcept;
	void Continue() noexcept;
	void Reset(State initialState);

	void ResetGameState(State initialState) noexcept;
	void ResetPlayerAndCombat() noexcept;
	void ResetWorld();
	void ResetBackground();
	void ResetUI() noexcept;
	void CleanupWorld() noexcept;

	void SpawnAliens();
	void SpawnWalls();
	void SpawnEnemyProjectile();
	void SpawnPlayerProjectile();

	void UpdateBackground() noexcept;

	void RenderStartScreen() const noexcept;
	void RenderGameplay() const noexcept;
	void RenderEndScreen() const noexcept;

	bool CheckNewHighScore() noexcept;
	void InsertNewHighScore(std::string name);
};