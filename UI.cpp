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
	toggleList->setString("LMB: Add 1 boid \nRMB: Remove 1 boid \nW: Toggle wind: " + vSystem->GetWindToggleStatus() + 
		"\nG : Toggle gravity: " + vSystem->GetGravityToggleStatus() + 
		"\nM : Follow mouse position: " + vSystem->GetSeekingToggleStatus() +
		"\nS : Toggle Separating: " + vSystem->GetSeparateToggleStatus() +
		"\nC : Toggle cohesion: " + vSystem->GetCohesionToggleStatus() +
		"\nA : Toggle alignment: " + vSystem->GetAlignmentToggleStatus() +
		"\nP : Follow the path: " + vSystem->GetPathingToggleStatus() +
		"\nSpace : Change path");

}

void UI::Render(sf::RenderWindow * window)
{
	window->draw(*toggleList);
	window->draw(*countTitle);
	window->draw(*countNumber);
}
