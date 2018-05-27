#include "Vehicle.h"
#include "MyMathLib.h"

using namespace sf;

Vehicle::Vehicle(sf::RenderWindow* window)
{
	acceleration = Vector2f(0, 0);
	veclocity = Vector2f(0, 0);
	location = (Vector2f)sf::Mouse::getPosition(*window);
	slowdownDist = 50.0f;

	maxSpeed = 400;
	maxForce = 1.0f;

	shape.setRadius(6);
	shape.setPointCount(3);
	shape.setScale(1, 2);
	shape.setPosition(location);
} 


Vehicle::~Vehicle()
{
}

void Vehicle::Update(sf::RenderWindow* window, float deltaTime)
{
	// TODO: Clamp velocity and force
	veclocity += acceleration * deltaTime;
	location += veclocity * deltaTime;
	acceleration = acceleration * 0.0f;

	shape.setRotation(atan2(veclocity.x, -veclocity.y) * 180 / 3.14f);
	shape.setPosition(location);
}

void Vehicle::ApplyForce(sf::Vector2f steer)
{
	acceleration = steer;
}
