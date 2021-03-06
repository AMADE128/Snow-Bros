#ifndef __MONKEY__
#define __MONKEY__

#include "Enemy.h"
#include "Path.h"

class Monkey : public Enemy
{
public:
	// Constructor (x y coordinates in the world)
	// Creates animation and movement data and the collider
	Monkey(int x, int y);

	// The enemy is going to follow the different steps in the path
	// Position will be updated depending on the speed defined at each step
	void Update() override;

	void Fall(Collider* collider) override;

	void StopMovement(Collider* collider) override;

	void Freeze(Collider* collider) override;

	// This enemy has one sprite and one frame
	// We are keeping it an animation for consistency with other enemies
	Animation idle;
	Animation l_walk;
	Animation r_walk;
	Animation l_stun;
	Animation r_stun;

	Animation* lastAnim;

	Animation snowball;

	bool stunt = false;

	bool CleanUp();

private:
	// A set of steps that define the position in the screen
	// And an animation for each step
	Path path;

	bool fall = false;
	bool groundCollision = true;

};

#endif
