#pragma once

#include <vector>
#include "Vec2.h"
#include "Colors.h"

class WorldObject
{
public:
	WorldObject() = default;
	WorldObject(Vec2<int> position, Vec2<int> size, Color backgroundcolor, Color foregroundcolor);
	//WorldObject(const WorldObject& other) : WorldObject(other.position, other.size, other.backgroundcolor, other.foregroundcolor){}
	//WorldObject& operator=(const WorldObject& other) { return *this = WorldObject(other); }
	//WorldObject(WorldObject&& other){}
	//WorldObject& operator=(WorldObject&& other) { std::swap(size, other.size); }
	virtual ~WorldObject();

//protected:
	Vec2<int> position;
	Vec2<int> size;
	Color backgroundcolor;
	Color foregroundcolor;
};

