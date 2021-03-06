#include "Enemy_Demon.h"

#include <stdio.h>
#include "Application.h"
#include "ModuleRender.h"
#include "ModuleCollisions.h"
#include "ModuleParticles.h"
#include "ModuleTextures.h"
#include "ModuleEnemies.h"
#include "ModulePlayer.h"

Enemy_Demon::Enemy_Demon(int x, int y) : Enemy(x, y)
{

	//Idle animation
	idle.PushBack({ 3,2,29,30 });

	//life of the Enemy

	//Left Walk Animation
	l_walk.PushBack({ 32, 0, 32, 32 });
	l_walk.PushBack({ 64, 0, 32, 32 });
	l_walk.PushBack({ 96, 0, 32, 32 });
	l_walk.loop = true;
	l_walk.speed = 0.07f;

	//Right Walk
	r_walk.PushBack({ 256, 0, 32, 32 });
	r_walk.PushBack({ 224, 0, 32, 32 });
	r_walk.PushBack({ 192, 0, 32, 32 });
	r_walk.loop = true;
	r_walk.speed = 0.07f;

	//Left Stun
	l_stun.PushBack({ 0, 32, 32, 32 });
	l_stun.PushBack({ 32, 32, 32, 32 });
	l_stun.loop = true;
	l_stun.speed = 0.05f;

	//Right Snowball
	r_stun.PushBack({ 256, 32, 32, 32 });
	r_stun.PushBack({ 288, 32, 32, 32 });
	r_stun.loop = true;
	r_stun.speed = 0.05f;


	path.PushBack({ 1, 0 }, 1000, &r_walk);
	path.PushBack({ 1, 0 }, 2000, &l_walk);
	path.PushBack({ 0, 0 }, 594058, &r_stun);
	path.PushBack({ 0, 0 }, 594058, &l_stun);

	collider = App->collisions->AddCollider({ (position.x) + 14, position.y, 32 * 4 - 15, 32 * 4 - 15 }, Collider::Type::ENEMY, (Module*)App->enemies);
}

void Enemy_Demon::Update()
{

	path.Update();

	if ((life == 7 && stunt == true) && (currentAnim != &r_walk && currentAnim != &l_walk && currentAnim != nullptr))
	{
		if(lastAnim == &r_walk)
		{
			path.currentStep = 0;
		}

		else if (lastAnim == &l_walk)
		{
			path.currentStep = 1; 
		}

		this->collider->type = this->collider->ENEMY;
		
		stunt = false;
	}

	if (life > 1 && this->collider->type != this->collider->NONE && this->collider->type != this->collider->ENEMY)
	{
		this->collider->type = this->collider->NONE;
	}


	if (currentAnim == &r_walk)
	{
		position.x+= 2;
	}

	if (currentAnim == &l_walk)
	{
		//position = spawnPos - path.GetRelativePosition();
		position.x-= 2;
	}

	if (life >= 7)
	{
		currentAnim = path.GetCurrentAnimation();
	}
	// Call to the base class. It must be called at the end
	// It will update the collider depending on the position

	Enemy::Update();
}

void Enemy_Demon::Fall(Collider* collider) {

	/*if (fall == false)
	{
		fall = true;
	}*/
	
	
	
	//position.x = 0;
	if (currentAnim == &r_walk)
	{
		currentAnim = &l_walk;
		path.currentStep = 1;
		path.currentStepFrame = 0;
	}
	
	else if (currentAnim == &l_walk)
	{
		//path.relativePosition = { 0,0 };
		currentAnim = &r_walk;
		path.currentStep = 0;
		path.currentStepFrame = 0;
	}

}

void Enemy_Demon::StopMovementY(Collider* collider) {
	/*if(groundCollision == false)
	{
		groundCollision = true;
	}*/
}

void Enemy_Demon::StopMovement(Collider* collider) {
		
	//position.x = 0;
	/*if (this->collider->type == collider->FREEZE_BALL && App->player->pushing == true)
	{	
		App->player->wallCollision = true;
	}*/
	
	if (currentAnim == &r_walk)
	{
		currentAnim = &l_walk;
		path.currentStep = 1;
		path.currentStepFrame = 0;
	}

	else if (currentAnim == &l_walk)
	{
		//path.relativePosition = { 0,0 };
		currentAnim = &r_walk;
		path.currentStep = 0;
		path.currentStepFrame = 0;
	}

}

bool Enemy_Demon::CleanUp()
{
	App->collisions->RemoveCollider(collider);

	return true;
}

void Enemy_Demon::Freeze(Collider* collider) {

   	if (life >= 0)
	{
		life--;
	}

	if (currentAnim == &r_walk && life > 0)
	{
		lastAnim = &r_walk;
		currentAnim = &r_stun;
		path.currentStep = 2;
		path.currentStepFrame = 0;
	}

	else if (currentAnim == &l_walk && life > 0)
	{
		lastAnim = &l_walk;
		currentAnim = &l_stun;
		path.currentStep = 3;
		path.currentStepFrame = 0;
	}

	switch (life)
	{
	case 1:
		App->player->score += 500;
		/*App->particles->snowball[3].lifetime = 0;
		App->particles->AddParticle(App->particles->snowball[4], position.x, position.y, Collider::NONE);*/
		this->collider->type = this->collider->FREEZE_BALL;

		break;
	case 2:
		App->player->score += 10;
 		this->collider->type = this->collider->NONE;
		//App->particles->snowball[2].lifetime = 0;
		/*App->particles->AddParticle(App->particles->snowball[3], position.x, position.y, Collider::NONE);*/
		break;
	case 3:
		App->player->score += 10;
		//App->particles->snowball[1].lifetime = 0;
		/*App->particles->AddParticle(App->particles->snowball[2], position.x, position.y, Collider::NONE);*/
		break;
	case 4:
		App->player->score += 10;
		//App->particles->snowball[0].lifetime = 0;
		/*App->particles->AddParticle(App->particles->snowball[1], position.x, position.y, Collider::NONE);*/
		break;
	case 5:
		App->player->score += 10;
		/*App->particles->AddParticle(App->particles->snowball[0], position.x, position.y, Collider::NONE);*/
		break;
	case 6:
		App->player->score += 10;
		
		/*App->particles->AddParticle(App->particles->snowball[0], position.x, position.y, Collider::NONE);*/
		this->collider->type = this->collider->NONE;
		stunt = true;
		break;
	case 7:
		break;

	}
}

/*void Enemy_Demon::BallPush(Collider* c1)
{
	if (this->collider->type == this->collider->FREEZE_BALL && App->player->pushing == true)
	{

		for (int i = 0; i < 100; i++)
		{
			if (App->particles->particles[i] != nullptr && App->particles->particles[i]->position.x == this->position.x && App->particles->particles[i]->position.y == this->position.y)
			{
				App->particles->particles[i]->position.x++;
			}
		}

		this->position.x++;
		this->collider->SetPos(this->collider->rect.x + 1, this->collider->rect.y);
	}
}*/