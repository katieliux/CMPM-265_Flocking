#pragma once
#include <SFML/Graphics.hpp>
class Path
{
public:
	Path(sf::RenderWindow* window);
	~Path();
	void Render(sf::RenderWindow* window);

	sf::Vector2f start;
	sf::Vector2f end;
	sf::VertexArray lines;
	float radius;
};

