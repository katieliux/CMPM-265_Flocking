#include "UI.h"

UI::UI(sf::RenderWindow* window, VehicleSystem* v_s)
{
	toggleList = new sf::Text;
	countTitle = new sf::Text;
	countNumber = new sf::Text; 
	font = new sf::Font;
	this->window = window;
	vSystem = v_s;

	font->loadFromFile("Fonts/visitor1.ttf");
	toggleList->setFont(*font);
	toggleList->setCharacterSize(16);
	toggleList->setString("W: Toggle wind \nG : Toggle gravity \nM : Follow mouse position \nS : Toggle Separating \nC : Toggle cohesion \nA : Toggle alignment \nP : Follow the path \nSpace : Change path");
	toggleList->setPosition(10, 10);

	countTitle->setFont(*font);
	countTitle->setCharacterSize(16);
	countTitle->setString("Boids count");
	countTitle->setPosition(700, 10);

	countNumber->setFont(*font);
	countNumber->setCharacterSize(16);
	countNumber->setPosition(700, 30);
	countNumber->setOrigin(-countTitle->getLocalBounds().width/2, 0);


}


UI::~UI()
{
}

void UI::Update()
{
	countNumber->setString("" + std::to_string(vSystem->GetBoidsCount()));
	toggleList->setString("W: Toggle wind: " + std::to_string(vSystem->windToggle) + 
		"\nG : Toggle gravity: " + std::to_string(vSystem->gravityToggle) + 
		"\nM : Follow mouse position: " + std::to_string(vSystem->seekToggle) +
		"\nS : Toggle Separating: " + std::to_string(vSystem->separateToggle) +
		"\nC : Toggle cohesion: " + std::to_string(vSystem->cohesionToggle) +
		"\nA : Toggle alignment: " + std::to_string(vSystem->alignmentToggle) +
		"\nP : Follow the path: " + std::to_string(vSystem->pathingToggle) +
		"\nSpace : Change path");

}

void UI::Render(sf::RenderWindow * window)
{
	window->draw(*toggleList);
	window->draw(*countTitle);
	window->draw(*countNumber);
}
