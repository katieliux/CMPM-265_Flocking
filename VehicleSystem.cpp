#include "VehicleSystem.h"
#include "MyMathLib.h"

using namespace sf;
VehicleSystem::VehicleSystem(sf::RenderWindow* window)
{
	gridWidth = window->getSize().x / COLUMNS;
	gridHeight = window->getSize().y / ROWS;
}


VehicleSystem::~VehicleSystem()
{
	for (int i = 0; i < ROWS; i++)
		for (int j = 0; j < COLUMNS; j++) 
			grid[i][j].clear();
}

void VehicleSystem::Update(sf::RenderWindow* window, float deltaTime)
{
	for (auto &v : boids)
	{
//		Vector2i currBucket = GetBucket(v.location);
		ApplyBehaviors(window, v);
		v.Update(window, deltaTime);
		//Vector2i newBucket = GetBucket(v.location);
		//if (currBucket != newBucket)
		//{
		//	BucketRemove(currBucket, &v);
		//	BucketAdd(newBucket, &v);
		//}
		//Vehicle* m_v = grid[newBucket.x]->at(newBucket.y);
		//ApplyBehaviors(window, *grid[newBucket.x]->at(newBucket.y));
	}
}

void VehicleSystem::ApplyBehaviors(sf::RenderWindow * window, Vehicle & v)
{
	if (windToggle)
	{
		Vector2f wind = Vector2f(1, 0);
		v.ApplyForce(wind);
	}
	if (gravityToggle)
	{
		Vector2f gravity = Vector2f(0, 0.1);
		v.ApplyForce(gravity);
	}
	if (seekToggle)
		Seek(window, v);
	if(separateToggle)
		Separate(v);
	if (alignmentToggle)
		Alignment(v);
	if (cohesionToggle)
		Cohesion(v);
	if(pathingToggle)
		FollowThePath(currentPath, v);
}

void VehicleSystem::Render(sf::RenderWindow* window)
{
	for (auto v : boids)
	{
		window->draw(v.shape);
	}
}

void VehicleSystem::AddVehicle(sf::RenderWindow* window)
{
	boids.push_back(Vehicle(window));
}

void VehicleSystem::RemoveVehicle()
{
	boids.pop_back();
}

#pragma region Pathing
void VehicleSystem::GetPath(Path* path)
{
	currentPath = path;
}

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
#pragma endregion

#pragma region Behaviors
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
			Vector2f(r * 4, v.maxSpeed));

	Vector2f steer = desired - v.veclocity;
	v.ApplyForce(steer);
	//v.veclocity = v.veclocity * (MyMathLib::Magnitude(target - v.location) / r);
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
			sf::Vector2f diff = MyMathLib::Normalize(v.location - other.location) / d;
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
		v.ApplyForce(Vector2f(0, 0));
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
#pragma endregion

#pragma region Bucket
sf::Vector2i VehicleSystem::GetBucket(sf::Vector2f pos)
{
	return sf::Vector2i(pos.x / gridWidth, pos.y / gridHeight);
}

void VehicleSystem::BucketAdd(sf::Vector2i bucket, Vehicle* v)
{
	grid[bucket.x][bucket.y].push_back(v);
}

void VehicleSystem::BucketRemove(sf::Vector2i bucket, Vehicle* v)
{
	auto i = std::find(grid[bucket.x][bucket.y].begin(), grid[bucket.x][bucket.y].end(), v);
	if (i != grid[bucket.x][bucket.y].end())
		grid[bucket.x][bucket.y].erase(i);
}
#pragma endregion

#pragma region Toggle 
void VehicleSystem::WindToggle()
{
	windToggle = !windToggle;
}

void VehicleSystem::GravityToggle()
{
	gravityToggle = !gravityToggle;
}

void VehicleSystem::SeekToggle()
{
	seekToggle = !seekToggle;
	pathingToggle = !pathingToggle;
}

void VehicleSystem::SeparateToggle()
{
	separateToggle = !separateToggle;
}

void VehicleSystem::AlignmentToggle()
{
	alignmentToggle = !alignmentToggle;
}

void VehicleSystem::CohesionToggle()
{
	cohesionToggle = !cohesionToggle;
}

void VehicleSystem::PathingToggle()
{
	pathingToggle = !pathingToggle;
	seekToggle = !seekToggle;
}
#pragma endregion 