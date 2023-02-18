#include <gtest/gtest.h>
#include <iostream>
#include "Projectile.h"
#include "Tuple.h"
#include "Canvas.h"
#include "CanvasExporter.h"

using namespace std;

TEST(Projectile, CalculatesPositionCorrectly)
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

TEST(Projectile,TestWithCanvas)
{	
	Tuple *velocity = createVector(1, 1.8, 0)->normalize()->multiply(11.25);
	Projectile *projectile = new Projectile(createPoint(0, 1, 0), velocity);
	Tuple *gravity = createVector(0, -0.1, 0);
	Tuple *wind = createVector(-0.01, 0, 0);
	Environment *environment = new Environment(gravity, wind);

	int height = 550;
	int width = 900;
	Canvas *canvas = new Canvas(width, height);
	Color *redColor = new Color(1, 0, 0);

	while (projectile->position->y > 0)
	{
		Projectile *newProjectile = tick(environment, projectile);

		int y = height - projectile->position->y;
		int x = projectile->position->x;
		if (y >= 0 && y < height && x >= 0 && x < width) {
			canvas->writePixel(x, y, redColor);
		}

		delete projectile;
		projectile = newProjectile;
	}

	savePPMFileFromCanvas(canvas, "projectile.ppm");

	delete projectile;
	delete environment;
	delete canvas;
}