#pragma once
#include <SFML/Graphics.hpp>
class Vehicle
{
public:
	Vehicle(sf::RenderWindow* window);
	~Vehicle();
	void ApplyForce(sf::Vector2f steer);
	void Update(sf::RenderWindow* window, float deltaTime);
	void SeekNearbyGroup(sf::Vector2f target);
	sf::CircleShape shape;
	sf::Vector2f location;
	sf::Vector2f veclocity;
	sf::Vector2f acceleration;
	float maxSpeed;
private:
	float maxForce;
	float r;
};

