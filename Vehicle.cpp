#include "Vehicle.h"
#include "MyMathLib.h"

using namespace sf;

Vehicle::Vehicle()
{
	acceleration = Vector2f(0, 0);
	veclocity = Vector2f(0, 0);
	location = Vector2f(0, 0);

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
	Seek(window, deltaTime);
}

void Vehicle::Seek(sf::RenderWindow * window, float deltaTime)
{
	Vector2f target = (Vector2f)sf::Mouse::getPosition(*window);
	location = shape.getPosition();

	Vector2f desired = Vector2f(0, 0);
	if (MyMathLib::Magnitude(target - location) > slowdownDist)
		desired = MyMathLib::Normalize((target - location)) * maxSpeed;
	else
		desired = MyMathLib::Normalize(target - location) * maxSpeed
		* MyMathLib::Magnitude(target - location)  / slowdownDist;
	
	Vector2f steer = desired - veclocity;

	// TODO: Clamp velocity and force
	acceleration = steer;
	veclocity += acceleration * deltaTime;
	location += veclocity * deltaTime;
	acceleration = acceleration * 0.0f;

	
	shape.setRotation(atan2(veclocity.x, -veclocity.y) * 180 / 3.14f);
	shape.setPosition(location);
}
