#pragma once
#include <SFML/Graphics.hpp>
static class MyMathLib
{
public:
	sf::Vector2f static Normalize(sf::Vector2f vector);
	float static Magnitude(sf::Vector2f vector);
};

