#include "Path.h"

Path::Path(sf::RenderWindow* window)
{
	radius = 1;
	lines.resize(4);
	lines.setPrimitiveType(sf::LinesStrip);

	start = sf::Vector2f(0, window->getSize().y / 3);
	mid_0 = sf::Vector2f(std::rand() % (window->getSize().x/ 2), std::rand() % (window->getSize().y/2));
	mid_1 = sf::Vector2f(std::rand() % (window->getSize().x/ 2), std::rand() % (window->getSize().y/2));
	end = sf::Vector2f(window->getSize().x, window->getSize().y);

	lines[0].position = start;
	lines[1].position = mid_0;
	lines[2].position = mid_1;
	lines[3].position = end;
}


Path::~Path()
{
}

void Path::Render(sf::RenderWindow* window)
{
	window->draw(lines);
}
