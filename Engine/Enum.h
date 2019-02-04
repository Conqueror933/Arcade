#pragma once

enum Direction
{
	etop,
	ebottom,
	eleft,
	eright,
	error = -1
};

enum Gamestate
{
	GsError = -1,
	GsMenu,
	GstwoPlayer,
	GsAILevel1,
	GsAILevel2,
	GsAILevel3,
	GsOptionen
};