#include "VehicleSystem.h"
#include "MyMathLib.h"
using namespace sf;
VehicleSystem::VehicleSystem()
{
	
}


VehicleSystem::~VehicleSystem()
{
}

void VehicleSystem::AddVehicle(sf::RenderWindow* window)
{
	vehicleList.push_back(Vehicle(window));
}

void VehicleSystem::Update(sf::RenderWindow* window, float deltaTime)
{
	for (auto &v : vehicleList)
	{
		ApplyBehaviors(window, v);
		v.Update(window, deltaTime);
	}
}

void VehicleSystem::ApplyBehaviors(sf::RenderWindow * window, Vehicle & v)
{
	Seek(window, v);
	Separate(v);
}

void VehicleSystem::Render(sf::RenderWindow* window)
{
	window->clear();
	for (auto v : vehicleList)
	{
		window->draw(v.shape);
	}
	window->display();
}

void VehicleSystem::Seek(sf::RenderWindow * window, Vehicle& v)
{
	Vector2f target = (Vector2f)sf::Mouse::getPosition(*window);
	v.location = v.shape.getPosition();

	Vector2f desired = Vector2f(0, 0);
	if (MyMathLib::Magnitude(target - v.location) > r)
		desired = MyMathLib::Normalize((target - v.location)) * v.maxSpeed;
	else
		desired = MyMathLib::Normalize(target - v.location) * v.maxSpeed
		* MyMathLib::Magnitude(target - v.location) / r;

	Vector2f steer = desired - v.veclocity;
	v.ApplyForce(steer);
}

void VehicleSystem::Separate(Vehicle& v)
{
	float desiredSeparation = r;

	sf::Vector2f sum;
	int count = 0;
	for (auto other : vehicleList)
	{
		float d = MyMathLib::Magnitude(v.location - other.location);
		if ((d > 0) && (d < desiredSeparation))
		{
			sf::Vector2f diff = MyMathLib::Normalize(v.location - other.location)/d;
			sum += diff;
			count++;
		}	
	}
	if (count > 0)
	{
		sum.x / count;
		sum.y / count;
		v.ApplyForce(MyMathLib::Normalize(sum) * v.maxSpeed - v.veclocity);
	}
}

