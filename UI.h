#pragma once
#include <SFML/Graphics.hpp>
#include "VehicleSystem.h"

class UI
{
public:
	UI(sf::RenderWindow* window, VehicleSystem* v_s);
	~UI();
	void Update();
	void Render(sf::RenderWindow* window);
private:

	sf::Text* toggleList;
	sf::Text* countTitle;
	sf::Text* countNumber;
	sf::Font* font;
	sf::RenderWindow* window;
	VehicleSystem* vSystem;

};

