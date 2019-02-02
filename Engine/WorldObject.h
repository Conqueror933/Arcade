#pragma once

#include <vector>
#include "Vec2.h"
#include "Colors.h"
#include "Graphics.h"

class WorldObject
{
public:
	WorldObject() = default;
	WorldObject(Graphics* gfx, Vec2<int> position, Vec2<int> size, Color backgroundcolor, Color foregroundcolor);
	WorldObject(const WorldObject& other);
	//WorldObject& operator=(const WorldObject& other) { return *this = WorldObject(other); }
	//WorldObject(WorldObject&& other){}
	//WorldObject& operator=(WorldObject&& other) { std::swap(size, other.size); }
	virtual ~WorldObject();

	virtual void Update() = 0;
	virtual void Draw() = 0;

//protected:
	Vec2<int> position;
	Vec2<int> size;
	Color backgroundcolor;
	Color foregroundcolor;
protected:
	Graphics* gfx;
};

