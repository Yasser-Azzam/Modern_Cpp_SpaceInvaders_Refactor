#pragma once
#include "raylib.h"
#include <vector>
#include "Resources.h"
#include <string>
#include "Background_System.h"


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

	Player(); 

	void TakeDamage(int amount = 1);
	Vector2 GetPosition() const;
	float GetRadius() const;
	int GetLives() const;
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

	bool isAlive() const { return alive; }
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

	void TakeDamage(int amount = 1);
	bool IsDestroyed() const;
	Vector2 GetPosition() const;
	float GetRadius() const;
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

	Vector2 GetPosition() const;
	float GetRadius() const;
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

	int score = 0;
	int wallCount = 5;

	float shootTimer = 0.0f;

	int formationWidth = 8;
	int formationHeight = 5;
	int alienSpacing = 80;
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

	// UI input (still legacy — will refactor later)
	std::string playerName;
	const size_t maxNameLength = 8;

	Rectangle textBox{ 600, 500, 225, 50 };
	bool mouseOnText = false;
	int framesCounter = 0;

	explicit Game(State initialState); // replaces Start()

	void Update();
	void Render();

	void End();
	void Continue();
	void Reset(State initialState);

	void SpawnAliens();
	void SpawnWalls();
	void SpawnEnemyProjectile();
	void SpawnPlayerProjectile();

	void UpdateBackground();

	void RenderStartScreen() const;
	void RenderGameplay() const;
	void RenderEndScreen() const;

	bool CheckNewHighScore();
	void InsertNewHighScore(std::string name);

	void LoadLeaderboard();
	void SaveLeaderboard();
};