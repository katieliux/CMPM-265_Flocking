#pragma once
#include <SFML/Graphics.hpp>
static class MyMathLib
{
public:
	sf::Vector2f static Normalize(sf::Vector2f vector);
	float static Magnitude(sf::Vector2f vector);
	float static DotProduct(sf::Vector2f vector_0, sf::Vector2f vector_1);
	float static map(float val, sf::Vector2f min, sf::Vector2f max);
};

