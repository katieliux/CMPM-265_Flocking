#include "VehicleSystem.h"
#include "MyMathLib.h"

using namespace sf;
VehicleSystem::VehicleSystem()
{
	
}


VehicleSystem::~VehicleSystem()
{
}

void VehicleSystem::GetPath(Path* path)
{
	currentPath = path;
}

void VehicleSystem::AddVehicle(sf::RenderWindow* window)
{
	boids.push_back(Vehicle(window));
}

void VehicleSystem::Update(sf::RenderWindow* window, float deltaTime)
{
	for (auto &v : boids)
	{
		ApplyBehaviors(window, v);
		v.Update(window, deltaTime);
	}
}

void VehicleSystem::ApplyBehaviors(sf::RenderWindow * window, Vehicle & v)
{
	Vector2f wind = Vector2f(100, 0);
	//Vector2f gravity = Vector2f(0, 0.1);
	v.ApplyForce(wind);
	//v.ApplyForce(gravity);
	/*Seek(window, v);
	Separate(v);
	Alignment(v);
	Cohesion(v);*/
	FollowThePath(currentPath, v);
}

void VehicleSystem::Render(sf::RenderWindow* window)
{
	for (auto v : boids)
	{
		window->draw(v.shape);
	}
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

void VehicleSystem::FollowThePath(Path * p, Vehicle & v)
{
	if (p != nullptr)
	{

		Vector2f predictLoc = v.location + MyMathLib::Normalize(v.veclocity) * 25.0f;

		Vector2f a = p->start;
		Vector2f b = p->end;
			
		Vector2f normalPoint = GetNormalPoint(predictLoc, a, b);
	
		Vector2f dir = MyMathLib::Normalize(b - a) * 10.0f;
		
		Vector2f target = normalPoint + dir;

		float dist = MyMathLib::Magnitude(normalPoint - predictLoc);
		if (dist > p->radius)
			v.SeekNearbyGroup(target);
	}
}

Vector2f VehicleSystem::GetNormalPoint(Vector2f p, Vector2f a, Vector2f b)
{
	Vector2f ap = p - a;
	Vector2f ab = b - a;
	ab = MyMathLib::Normalize(ab);
	ab *= MyMathLib::DotProduct(ap, ab);
	Vector2f normalPoint = a + ab;

	return normalPoint;
}

void VehicleSystem::Separate(Vehicle& v)
{
	float desiredSeparation = r * 2;

	sf::Vector2f sum;
	int count = 0;
	for (auto other : boids)
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

void VehicleSystem::Alignment(Vehicle& v)
{
	float neighborDist = 100.0f;
	Vector2f sum;
	int count = 0;
	for (auto other : boids)
	{
		float d = MyMathLib::Magnitude(v.location - other.location);
		if ((d > 0) && (d < neighborDist))
		{
			sum += other.veclocity;
			count++;
		}
	}

	if (count > 0)
	{
		sum.x / count;
		sum.y / count;
		v.ApplyForce(MyMathLib::Normalize(sum) * v.maxSpeed - v.veclocity);
	}
	else
		v.ApplyForce(Vector2f(0,0));
}

void VehicleSystem::Cohesion(Vehicle& v)
{
	float neighborDist = 100.0f;
	Vector2f sum;
	int count = 0;
	for (auto other : boids)
	{
		float d = MyMathLib::Magnitude(v.location - other.location);
		if ((d > 0) && (d < neighborDist))
		{
			sum += other.location;
			count++;
		}
	}

	if (count > 0)
	{
		sum.x / count;
		sum.y / count;
		v.SeekNearbyGroup(sum);
	}
	else
		v.ApplyForce(Vector2f(0, 0));
}

