#include "Vehicle.h"
#include "MyMathLib.h"

using namespace sf;

Vehicle::Vehicle(sf::RenderWindow* window)
{
	acceleration = Vector2f(0, 0);
	veclocity = Vector2f(0, 0);
	location = (Vector2f)sf::Mouse::getPosition(*window);
	r = 25.0f;

	maxSpeed = 200;
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

	if (shape.getPosition().x > window->getSize().x - 5)
		shape.setPosition(5, shape.getPosition().y);
	if (shape.getPosition().x < 5)
		shape.setPosition(window->getSize().x - 5, shape.getPosition().y);
	if (shape.getPosition().y > window->getSize().y - 5)
		shape.setPosition(shape.getPosition().x, 5);
	if (shape.getPosition().y < 5)
		shape.setPosition(shape.getPosition().y, window->getSize().y - 5);
}

void Vehicle::ApplyForce(sf::Vector2f steer)
{
	acceleration += steer;
}
void Vehicle::SeekNearbyGroup(sf::Vector2f target)
{
	location = shape.getPosition();

	Vector2f desired = Vector2f(0, 0);
	if (MyMathLib::Magnitude(target - location) > r)
	{
		desired = MyMathLib::Normalize((target - location)) * maxSpeed;
		Vector2f steer = desired - veclocity;
		ApplyForce(steer);
	}
	else
		desired *= MyMathLib::map(
			MyMathLib::Magnitude(target - location),
			Vector2f(0, 0),
			Vector2f(r * 4, maxSpeed));


}