#pragma once
#include <vector>
#include <algorithm>
#include <iostream>
#include "Vehicle.h"
#include "Path.h"

class VehicleSystem
{
public:
	VehicleSystem(sf::RenderWindow* window);
	~VehicleSystem();
	void AddVehicle(sf::RenderWindow* window);
	void RemoveVehicle();
	void Update(sf::RenderWindow* window, float deltaTime);
	void ApplyBehaviors(sf::RenderWindow * window, Vehicle & v);
	void Render(sf::RenderWindow* window);
	void GetPath(Path* path);

	void WindToggle();
	void GravityToggle();
	void SeekToggle();
	void SeparateToggle();
	void AlignmentToggle();
	void CohesionToggle();
	void PathingToggle();
private:
	std::vector<Vehicle> boids;

	float r = 25.0f;
	void Separate(Vehicle& v);
	void Alignment(Vehicle& v);
	void Cohesion(Vehicle& v);
	void Seek(sf::RenderWindow * window, Vehicle& v);
	void FollowThePath(Path* path, Vehicle& v);
	sf::Vector2f GetNormalPoint(sf::Vector2f p, sf::Vector2f a, sf::Vector2f b);
	Path* currentPath = nullptr;

	static const int COLUMNS = 10;
	static const int ROWS = 10;
	int gridWidth;
	int gridHeight;
	std::vector<Vehicle*> grid[ROWS][COLUMNS];
	sf::Vector2i GetBucket(sf::Vector2f pos);
	void BucketAdd(sf::Vector2i bucket, Vehicle* v);
	void BucketRemove(sf::Vector2i bucket, Vehicle* v);

	bool windToggle = true;
	bool gravityToggle = true;
	bool seekToggle = true;
	bool separateToggle = true;
	bool alignmentToggle = true;
	bool cohesionToggle = true;
	bool pathingToggle = false;

};


