#pragma once

#include <vector>
#include <array>
#include <string>
#include <map>
#include <fstream>
#include "Vec2.h"
#include "Graphics.h"
#include "Colors.h"

//#pragma pack(push,2)
struct mBitmapFileHdr_t
{
	uint16_t bfType;//FileType
	uint32_t bfSizeHeader;//FileSize
	uint16_t bfReserved1;//Reserved1
	uint16_t bfReserved2;//Reserved2
	uint32_t bfOffsetBits;//BitmapOffset
};

struct mBitmapInfoHdr_t
{
	uint32_t biSizeHeader;//Size
	uint32_t biWidth;//Width
	uint32_t biHeight;//Height
	uint16_t biPlanes;//Planes
	uint16_t biBitCount;//BitsPerPixel
	uint32_t biCompression;//Compression
	uint32_t biSizeImage;//SizeOfBitmap
	uint32_t biXPelsPerMeter;//HorzResolution
	uint32_t biYPelsPerMeter;//VertResolution
	uint32_t biClrUsed;//ColorsUsed
	uint32_t biClrImportant;//ColorsImportant
};

struct mBitmapHeader
{
	mBitmapFileHdr_t hdr;
	mBitmapInfoHdr_t info;
};
//#pragma pop

class Bitmap
{
public:
	Bitmap(Graphics& gfx, std::string filename);
	virtual ~Bitmap();

protected:
	Graphics & gfx;
	mBitmapHeader bH;
	std::vector<Color> bitmapColors;

private:
	void readBMP(const std::string &file);
};

class Text : public Bitmap
{
public:
	Text(Graphics& gfx, std::string filename);
	void Draw(std::string str, Vec2<int> position, int letterspace, Color c);
	void Draw(const char* str, Vec2<int> position, int letterspace, Color c);
	inline void DrawRectangle(int x0, int y0, int x1, int y1, Color c)
	{
		gfx.DrawRectangle(x0, y0, x1, y1, c);
	}
	inline void DrawRectangleDim(int x0, int y0, int width, int height, Color c)
	{
		gfx.DrawRectangleDim(x0, y0, width, height, c);
	}
	int GetLetterWidth(char letter)
	{
		if (letter == ' ')
			return space;
		else
			return letters[letter].second;
	}
	int GetLetterHeight()
	{
		return bH.info.biHeight;
	}

private:
	void DrawLetter(const char letter, Vec2<int> position, Color c);

private:
	//char = letter, int = x position of letter in bitmap int = width of letter in bitmap
	std::map<char, std::pair<int, int>> letters;
	static constexpr int space = 10;
};
