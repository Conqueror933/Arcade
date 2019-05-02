#include "Label.h"

Label::Label(Graphics& gfx, Text& text, std::string s, Vec2<int> position, Vec2<int> size,
	const int letterspacing, const int border, Color backgroundcolor, Color textcolor)
	:
	gfx(gfx), position(position), size(size), background(backgroundcolor), textcolor(textcolor),
	text(text),
	s(s),
	letterspacing(letterspacing),
	border(border)
{
}

Label::Label(const Label& other)
	:
	gfx(other.gfx), position(other.position), size(other.size), background(other.background), textcolor(other.textcolor),
	text(other.text),
	s(other.s),
	letterspacing(other.letterspacing),
	border(other.border)
{
}

void Label::Draw()
{
	//check if label background is desired
	if (background != Colors::Magenta)
		gfx.DrawRectangleDim(position.x, position.y, size.x, size.y, background);

	//get the width & height of the text
	const char* str = s.c_str();
	int width = 0;
	for (auto i = 0; str[i] != 0; i++)
	{
		width += text.GetLetterWidth(str[i]);
		width += letterspacing;
	}
	width -= letterspacing; //remove spacing past the last
	int height = text.GetLetterHeight();

	//if default settings are enabled, make default background
	if (size == Vec2<int>{0, 0})
	{
		size.x = width + border;
		size.y = height + border;
	}

	//if text fits in background draw text
	if (width < size.x && height < size.y)
	{
		auto x = size.x - width;
		auto y = size.y - height;
		Vec2<int> vec = { position.x + x / 2, position.y + y / 2 };
		text.Draw(s, vec, letterspacing, textcolor);
	}
}