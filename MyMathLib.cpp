#include "MyMathLib.h"
using namespace sf;
sf::Vector2f MyMathLib::Normalize(sf::Vector2f vector)
{
	if (powf(vector.x, 2.0f) + powf(vector.y, 2.0f) == 0)
		return vector;
	else
	{
		vector.x = vector.x / sqrtf(powf(vector.x, 2.0f) + powf(vector.y, 2.0f));
		vector.y = vector.y / sqrtf(powf(vector.x, 2.0f) + powf(vector.y, 2.0f));
		return vector;
	}
}

float MyMathLib::Magnitude(sf::Vector2f vector)
{
	return sqrtf(powf(vector.x, 2.0f) + powf(vector.y, 2.0f));
}

float MyMathLib::DotProduct(sf::Vector2f vector_0, sf::Vector2f vector_1)
{
	return vector_0.x * vector_1.x + vector_0.y * vector_1.y;
}