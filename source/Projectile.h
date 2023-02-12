#include <stdio.h>
#include "Tuple.h"

#ifndef _PROJECTILE_H
#define _PROJECTILE_H

class Projectile {
	public:
		Projectile(Tuple *position, Tuple *velocity) : position(position), velocity(velocity) {};

		Tuple* position;
		Tuple* velocity;

	~Projectile()
	{
		delete position;
		delete velocity;
	}
};

class Environment {
	public:
		Environment(Tuple *gravity, Tuple *wind) : gravity(gravity), wind(wind) {};

		Tuple* gravity;
		Tuple* wind;
		
		~Environment()
		{
			delete gravity;
			delete wind;
		}
};

Projectile* tick(Environment *environment, Projectile *projectile) {
	Tuple *position = projectile->position->add(projectile->velocity);
	Tuple *velocityPlusGravity = projectile->velocity->add(environment->gravity);
	Tuple *velocity = velocityPlusGravity->add(environment->wind);
	delete velocityPlusGravity;
	
	return new Projectile(position, velocity);
}

#endif