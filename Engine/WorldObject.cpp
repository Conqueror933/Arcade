#include "WorldObject.h"



WorldObject::WorldObject(Graphics* gfx, Vec2<int> position, Vec2<int> size, Color backgroundcolor, Color foregroundcolor)
	:
	gfx(gfx),
	position(position),
	size(size),
	backgroundcolor(backgroundcolor),
	foregroundcolor(foregroundcolor)
{
}

WorldObject::WorldObject(const WorldObject & other)
	:
	position(other.position),
	size(other.size),
	backgroundcolor(other.backgroundcolor),
	foregroundcolor(other.foregroundcolor)
{
}

WorldObject::~WorldObject()
{
}
