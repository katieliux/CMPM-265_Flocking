#include "Path.h"

Path::Path(sf::RenderWindow* window)
{
	radius = 1;
	lines.resize(2);
	lines.setPrimitiveType(sf::LinesStrip);

	start = sf::Vector2f(0, window->getSize().y / 3);
	end = sf::Vector2f(window->getSize().x, window->getSize().y);

	lines[0].position = start;
	lines[1].position = end;
}


Path::~Path()
{
}

void Path::Render(sf::RenderWindow* window)
{
	window->draw(lines);
}
