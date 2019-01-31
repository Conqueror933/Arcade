#include "Bitmap.h"



Bitmap::Bitmap(Graphics& gfx, std::string filename)
	:
	gfx(gfx)
{
	readBMP(filename);
}

Bitmap::~Bitmap()
{
}

void Bitmap::readBMP(const std::string &file)
{
	static constexpr size_t HEADER_SIZE = 54;

	std::ifstream bmp(file, std::ios::binary);
	if (!bmp.is_open()) return;

	std::array<char, HEADER_SIZE> header;
	bmp.read(header.data(), HEADER_SIZE);
	
	//Header
	bH.hdr.bfType = *reinterpret_cast<WORD *>(&header[0]);
	if (bH.hdr.bfType != 19778) throw "BMP could not be loaded"; //19778 = 'BM' //Windows 3.x bmp file
	bH.hdr.bfSizeHeader = *reinterpret_cast<DWORD *>(&header[2]);
	bH.hdr.bfReserved1 = *reinterpret_cast<WORD *>(&header[6]);
	bH.hdr.bfReserved2 = *reinterpret_cast<WORD *>(&header[8]);
	bH.hdr.bfOffsetBits = *reinterpret_cast<DWORD *>(&header[10]);
	
	//Bitmap header
	bH.info.biSizeHeader = *reinterpret_cast<DWORD *>(&header[14]);
	bH.info.biWidth = *reinterpret_cast<LONG *>(&header[18]); //actually 4 byte
	bH.info.biHeight = *reinterpret_cast<LONG *>(&header[22]); //actually 4 byte
	bH.info.biPlanes = *reinterpret_cast<WORD *>(&header[26]);
	bH.info.biBitCount = *reinterpret_cast<WORD *>(&header[28]);	//check file format
	bH.info.biCompression = *reinterpret_cast<DWORD *>(&header[30]);	//if 0 -> Windows 3.x //if !0 -> Windows NT bmp
	bH.info.biSizeImage = *reinterpret_cast<DWORD *>(&header[34]);
	bH.info.biXPelsPerMeter = *reinterpret_cast<LONG *>(&header[38]); //actually 4 byte
	bH.info.biYPelsPerMeter = *reinterpret_cast<LONG *>(&header[42]); //actually 4 byte
	bH.info.biClrUsed = *reinterpret_cast<DWORD *>(&header[46]);
	bH.info.biClrImportant = *reinterpret_cast<DWORD *>(&header[50]);
	
	//Extract Color palette
	auto temp_SIZE = (bH.hdr.bfOffsetBits - HEADER_SIZE);
	std::vector<char> temp(temp_SIZE);
	bmp.seekg(HEADER_SIZE);
	bmp.read(temp.data(), temp_SIZE);
	//convert from char to Color (int)
	std::vector<Color> ColorPalette; ColorPalette.reserve(temp_SIZE / 4);
	for (int i = 0; i < temp_SIZE; i += 4)
	{
		ColorPalette.emplace_back(Color(
			static_cast<unsigned char>(temp[i + 3]),
			static_cast<unsigned char>(temp[i + 2]),
			static_cast<unsigned char>(temp[i + 1]),
			static_cast<unsigned char>(temp[i + 0])));
	}

	auto ghostbytes = bH.info.biSizeImage * 2 - bH.info.biWidth * bH.info.biHeight;
	auto ghostbytesperline = ghostbytes / 2 / bH.info.biHeight;

	//Read raw Bitmap data
	std::vector<char> img(bH.info.biSizeImage);
	bmp.seekg(bH.hdr.bfOffsetBits);
	bmp.read(img.data(), bH.info.biSizeImage);
	//Reserve space to avoid reallocation
	bitmapColors.reserve(bH.info.biWidth * bH.info.biHeight);
	//for every BYTE in the image... 
	auto j = 0u;
	for (auto i = 0u; i < bH.info.biSizeImage; i++)
	{
		if (j >= bH.info.biWidth/2) //avoid the fucking padding crap, jeez
		{
			if (j == bH.info.biWidth/2 + ghostbytesperline - 1)
			{
				j = 0;
				continue;
			}
			j++;
			continue;
		}
		j++;
		//...extract PixelColor stored in first 4 BITS pointing to a location in the ColorPalette and...
		bitmapColors.emplace_back(Color(ColorPalette[(img[i] & 0xF0) >> 4]));
		//...extract PixelColor stored in second 4 BITS pointing to a location in the ColorPalette...
		bitmapColors.emplace_back(Color(ColorPalette[img[i] & 0x0F]));
		//...and store them as full fledged Color Objects in the bitmapColors vector
	}
}

void Text::DrawLetter(const char letter, Vec2<int> position, Color c)
{
	//read bitmap
	auto xpos = letters[letter].first;
	auto ypos = 10;
	auto width = letters[letter].second;
	auto xend = xpos + width;

	for (auto i = xpos; i < xend; i++)
	{
		for (auto j = 0; j < ypos; j++)
		{
			if (bitmapColors[i * ypos + j] != Colors::Magenta)
				gfx.PutPixel(position.x + i-xpos, position.y + j, c);
		}
	}
}

Text::Text(Graphics& gfx, std::string filename) 
	: 
	Bitmap(gfx, filename) 
{
	auto hw = bH.info.biHeight * bH.info.biWidth;
	std::vector<Color> temp;
	temp.reserve(hw);
	for (auto i = 0; i < bH.info.biWidth; i++)
	{
		for (auto j = bH.info.biHeight; j > 0; j--)
		{
			temp.emplace_back(bitmapColors[(j-1)*bH.info.biWidth+i]);
		}
	}
	bitmapColors = temp;

	letters.emplace(std::make_pair('A', std::make_pair(0, 10)));
	letters.emplace(std::make_pair('B', std::make_pair(10, 10)));
	letters.emplace(std::make_pair('C', std::make_pair(20, 9)));
	letters.emplace(std::make_pair('D', std::make_pair(29, 10)));
	letters.emplace(std::make_pair('E', std::make_pair(39, 9)));
	letters.emplace(std::make_pair('F', std::make_pair(48, 9)));
	letters.emplace(std::make_pair('G', std::make_pair(57, 10)));
	letters.emplace(std::make_pair('H', std::make_pair(67, 10)));
	letters.emplace(std::make_pair('I', std::make_pair(77, 4)));
	letters.emplace(std::make_pair('J', std::make_pair(81, 8)));
	letters.emplace(std::make_pair('K', std::make_pair(89, 10)));
	letters.emplace(std::make_pair('L', std::make_pair(99, 9)));
	letters.emplace(std::make_pair('M', std::make_pair(108, 12)));
	letters.emplace(std::make_pair('N', std::make_pair(120, 10)));
	letters.emplace(std::make_pair('O', std::make_pair(130, 10)));
	letters.emplace(std::make_pair('P', std::make_pair(140, 10)));
	letters.emplace(std::make_pair('Q', std::make_pair(150, 10)));
	letters.emplace(std::make_pair('R', std::make_pair(160, 11)));
	letters.emplace(std::make_pair('S', std::make_pair(171, 9)));
	letters.emplace(std::make_pair('T', std::make_pair(180, 10)));
	letters.emplace(std::make_pair('U', std::make_pair(190, 10)));
	letters.emplace(std::make_pair('V', std::make_pair(200, 10)));
	letters.emplace(std::make_pair('W', std::make_pair(210, 16)));
	letters.emplace(std::make_pair('X', std::make_pair(226, 11)));
	letters.emplace(std::make_pair('Y', std::make_pair(237, 12)));
	letters.emplace(std::make_pair('Z', std::make_pair(249, 11)));
}

void Text::Draw(std::string str, Vec2<int> position, Color c)
{
	Draw(str.c_str(), position, c);
}

void Text::Draw(const char* str, Vec2<int> position, Color c)
{
	for (auto i = 0; str[i] != 0; i++)
	{
		if (str[i] == ' ') 
		{ 
			position.x = position.x + 10;
		}
		else
		{
			auto width = letters[str[i]].second;
			DrawLetter(str[i], position, c);
			position.x = position.x + width;
		}
	}
}
