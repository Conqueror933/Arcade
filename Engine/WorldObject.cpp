#include "WorldObject.h"



WorldObject::WorldObject(Vec2<int> position, Vec2<int> size, Color backgroundcolor, Color foregroundcolor)
	:
	position(position),
	size(size),
	backgroundcolor(backgroundcolor),
	foregroundcolor(foregroundcolor)
{
}

WorldObject::~WorldObject()
{
}
