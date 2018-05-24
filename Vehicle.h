#pragma once
#include <SFML/Graphics.hpp>
class Vehicle
{
public:
	Vehicle();
	~Vehicle();
	void Update(sf::RenderWindow* window, float deltaTime);
	void Seek(sf::RenderWindow * window, float deltaTime);
	sf::CircleShape shape;
private:
	sf::Vector2f location;
	sf::Vector2f veclocity;
	sf::Vector2f acceleration;
	float maxSpeed;
	float maxForce;

	float slowdownDist;
};

