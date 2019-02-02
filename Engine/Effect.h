#pragma once

#include "Graphics.h"
#include "Colors.h"

namespace ButtonEffect
{
	class Standard
	{
	public:
		Standard() = default;
		void operator()(Graphics& gfx, int xDest, int yDest, Color cSrc) const
		{
			gfx.PutPixel(xDest, yDest, cSrc);
		}
	};
	class Shade
	{
	public:
		Shade(float factor) : factor(factor) {}
		void operator()(Graphics& gfx, int xDest, int yDest, Color cSrc) const
		{
			cSrc.Shade(factor);
			gfx.PutPixel(xDest, yDest, cSrc);
		}
	private:
		float factor;
	};
	class Chroma
	{
	public:
		Chroma(Color c) : chroma(c) {}
		void operator()(Graphics& gfx, int xDest, int yDest, Color cSrc) const
		{
			if (cSrc != chroma)
			{
				gfx.PutPixel(xDest, yDest, cSrc);
			}
		}
	private:
		Color chroma;
	};
}