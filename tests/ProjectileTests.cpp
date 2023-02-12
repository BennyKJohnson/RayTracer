#include <gtest/gtest.h>
#include <iostream>
#include "Projectile.h"
#include "Tuple.h"
using namespace std;

TEST(Projectile, Test)
{
	Projectile *projectile = new Projectile(createPoint(0, 1, 0), createVector(1, 1, 0)->normalize());
	Environment *environment = new Environment(createVector(0, -0.1, 0), createVector(-0.01, 0, 0));
	while (projectile->position->y > 0)
	{
		Projectile *newProjectile = tick(environment, projectile);
		delete projectile;
		projectile = newProjectile;
	}

	EXPECT_FLOAT_EQ(projectile->position->x, 10.660816);

	delete projectile;
	delete environment;
}