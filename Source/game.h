#pragma once
#include "raylib.h"
#include <vector>
#include "Resources.h"
#include <string>


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
	std::string name;
	int score;
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

	void Update();
	void Render(Texture2D texture);

};


struct Projectile
{
public: 
public:
	Vector2 position{};
	int speed = 15;
	EntityType type{};

	Vector2 lineStart{};
	Vector2 lineEnd{};

	void Update();
	void Render(Texture2D texture);
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

	void Update();
	void Render(Texture2D texture);
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

	void Update();
	void Render(Texture2D texture);
};


struct Star
{
	Vector2 initPosition{ 0.0f, 0.0f };
	Vector2 position{ 0.0f, 0.0f };

	Color color = GRAY;
	float size = 0.0f;

	void Update(float starOffset);
	void Render();
};

struct Background
{
public:
	std::vector<Star> Stars;

	explicit Background(int starAmount); // replaces Initialize()

	void Update(float offset);
	void Render();
};

struct Game
{
public:
	// NOTE:
	// Game still has too many responsibilities.
	// This is intentional for now — will be addressed in later steps.

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

	Background background;

	Vector2 playerPos{};
	Vector2 cornerPos{};
	float offset = 0.0f;

	// UI input (still legacy — will refactor later)
	char name[10] = "\0";
	int letterCount = 0;

	Rectangle textBox{ 600, 500, 225, 50 };
	bool mouseOnText = false;
	int framesCounter = 0;

	explicit Game(State initialState); // replaces Start()

	void Update();
	void Render();

	void End();
	void Continue();

	void SpawnAliens();

	bool CheckCollision(Vector2 circlePos, float circleRadius,
		Vector2 lineStart, Vector2 lineEnd);

	void HandleCollisions();
	void HandlePlayerProjectiles();
	void HandleEnemyProjectiles();

	bool CheckNewHighScore();
	void InsertNewHighScore(std::string name);

	void LoadLeaderboard();
	void SaveLeaderboard();

};