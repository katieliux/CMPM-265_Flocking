#pragma once
#include <SFML/Graphics.hpp>
class Vehicle
{
public:
	Vehicle(sf::RenderWindow* window);
	~Vehicle();
	void ApplyForce(sf::Vector2f steer);
	void Update(sf::RenderWindow* window, float deltaTime);
	sf::CircleShape shape;

	sf::Vector2f location;
	sf::Vector2f veclocity;
	sf::Vector2f acceleration;
	float maxSpeed;
private:
	float maxForce;
	float slowdownDist;
};

