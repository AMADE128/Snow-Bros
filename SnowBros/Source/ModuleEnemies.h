#ifndef __MODULE_ENEMIES_H__
#define __MODULE_ENEMIES_H__

#include "Module.h"

#define MAX_ENEMIES 100

enum class ENEMY_TYPE
{
	NO_TYPE,
	DEMON,
	FROG,
	MONKEY
};

struct EnemySpawnpoint
{
	ENEMY_TYPE type = ENEMY_TYPE::NO_TYPE;
	int x, y;
};

class Enemy;
struct SDL_Texture;

class ModuleEnemies : public Module
{
public:
	// Constructor
	ModuleEnemies(bool startEnabled);

	// Destructor
	~ModuleEnemies();

	// Called when the module is activated
	// Loads the necessary textures for the enemies
	bool Start() override;

	// Called at the middle of the application loop
	// Handles all enemies logic and spawning/despawning
	update_status Update() override;

	// Called at the end of the application loop
	// Iterates all the enemies and draws them
	update_status PostUpdate() override;

	// Called on application exit
	// Destroys all active enemies left in the array
	bool CleanUp() override;

	// Called when an enemi collider hits another collider
	// The enemy is destroyed and an explosion particle is fired
	void OnCollision(Collider* c1, Collider* c2) override;

	void Fall(Collider* c1, Collider* c2) override;

	void StopMovement(Collider* c1, Collider* c2) override;

	void StopMovementY(Collider* c1, Collider* c2) override;

	void Freeze(Collider* c1, Collider* c2) override;

	//void BallPush(Collider* c1, Collider* c2) override;

	// Add an enemy into the queue to be spawned later
	bool AddEnemy(ENEMY_TYPE type, int x, int y);

	// Iterates the queue and checks for camera position
	void HandleEnemiesSpawn();

	// Destroys any enemies that have moved outside the camera limits
	void HandleEnemiesDespawn();

	void WinCondition();

	// The enemies sprite sheet
	SDL_Texture* demon = nullptr;
	SDL_Texture* frog = nullptr;
	SDL_Texture* monkey = nullptr;
	/*SDL_Texture* snow = nullptr;*/

	// All spawned enemies in the scene
	Enemy* enemies[MAX_ENEMIES] = { nullptr };

	//Enemies life
	int life = 7;

	int scoreD = 500;

	//WIN CONDITION
	bool win = false;

	int enemydiesFont = -1;
	char enemydiesText[10] = { "\0" };

private:
	// Spawns a new enemy using the data from the queue
	void SpawnEnemy(const EnemySpawnpoint& info);

private:
	// A queue with all spawn points information
	EnemySpawnpoint spawnQueue[MAX_ENEMIES];

	// The audio fx for destroying an enemy
	//int enemyDestroyedFx = 0;

};

#endif // __MODULE_ENEMIES_H__
