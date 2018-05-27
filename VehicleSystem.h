#pragma once
#include <vector>
#include <algorithm>
#include <iostream>
#include "Vehicle.h"

class VehicleSystem
{
public:
	VehicleSystem();
	~VehicleSystem();
	void AddVehicle(sf::RenderWindow* window);
	void Update(sf::RenderWindow* window, float deltaTime);
	void ApplyBehaviors(sf::RenderWindow * window, Vehicle & v);
	void Render(sf::RenderWindow* window);
private:
	std::vector<Vehicle> vehicleList;

	float r = 50.0f;
	void Separate(Vehicle& v);
	void Seek(sf::RenderWindow * window, Vehicle& v);
};

