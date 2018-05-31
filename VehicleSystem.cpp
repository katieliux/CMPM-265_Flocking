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
	Vector2f wind = Vector2f(10, 0);
	//Vector2f gravity = Vector2f(0, 0.1);
	v.ApplyForce(wind);
	//v.ApplyForce(gravity);
	//Seek(window, v);
	Separate(v);
	//Alignment(v);
	//Cohesion(v);
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

	Vector2f desired = MyMathLib::Normalize((target - v.location));

	if (MyMathLib::Magnitude(target - v.location) > r)
		desired *= v.maxSpeed;
	else
		desired *= MyMathLib::map(
			MyMathLib::Magnitude(target - v.location), 
			Vector2f(0, 0), 
			Vector2f(100.f, v.maxSpeed));

	Vector2f steer = desired - v.veclocity;
	v.ApplyForce(steer);
		//v.veclocity = v.veclocity * (MyMathLib::Magnitude(target - v.location) / r);
}

//void VehicleSystem::FollowThePath(Path * p, Vehicle & v)
//{
//	if (p != nullptr)
//	{
//		Vector2f predictLoc = v.location + MyMathLib::Normalize(v.veclocity) * 25.0f;
//
//		Vector2f a = p->start;
//		Vector2f b = p->end;
//			
//		Vector2f normalPoint = GetNormalPoint(predictLoc, a, b);
//	
//		Vector2f dir = MyMathLib::Normalize(b - a) * 10.0f;
//		
//		Vector2f target = normalPoint + dir;
//
//		float dist = MyMathLib::Magnitude(normalPoint - predictLoc);
//		if (dist > p->radius)
//			v.SeekNearbyGroup(target);
//	}
//}

void VehicleSystem::FollowThePath(Path * p, Vehicle & v)
{
	Vector2f target;
	Vector2f normal;
	Vector2f normalPoint;
	float worldRecord = 1000000;

	if (p != nullptr)
	{
		Vector2f predictLoc = v.location + MyMathLib::Normalize(v.veclocity) * 25.0f;

		for (int i = 0; i < 3; i++)
		{
			Vector2f a = p->lines[i].position;
			Vector2f b = p->lines[i + 1].position;

			normalPoint = GetNormalPoint(predictLoc, a, b);

			if (normalPoint.x < a.x || normalPoint.x > b.x)
				normalPoint = b;

			float dist = MyMathLib::Magnitude(predictLoc - normalPoint);

			if (dist < worldRecord)
			{
				worldRecord = dist;
				normal = normalPoint;
				Vector2f dir = b - a;
				dir = 10.0f * MyMathLib::Normalize(dir);
				target = normalPoint + dir;
			}
		}

		sf::Vector2f a = p->lines[3].position;
		sf::Vector2f b = p->lines[0].position;
		sf::Vector2f normalPoint = GetNormalPoint(predictLoc, a, b);

		if (normalPoint.x < a.x || normalPoint.x > b.x) {
			normalPoint = b;
		}

		float distance = MyMathLib::Magnitude(predictLoc - normalPoint);

		if (distance < worldRecord) {
			worldRecord = distance;
			normal = normalPoint;

			sf::Vector2f dir = b - a;
			dir = MyMathLib::Normalize(dir);
			dir *= 10.f;
			target = normalPoint;
			target += dir;
		}

		if (worldRecord > p->radius)
			return v.SeekNearbyGroup(target);
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

