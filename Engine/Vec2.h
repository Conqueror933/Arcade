#pragma once
#include <cmath>
#include <algorithm>
#include <iostream>

template<typename T>
class Vec2
{
public:	//Ctor, Dtor, Copy, Move
	Vec2() = default;
	Vec2(T in_x, T in_y)
	{
		x = in_x;
		y = in_y;
	}

	Vec2(const Vec2& rhs) : x(rhs.x), y(rhs.y){}
	Vec2& operator= (const Vec2& rhs) { return *this = Vec2(rhs); }
	//Vec2(Vec2&& rhs);
	//Vec2& operator= (Vec2&& rhs);
	~Vec2() = default;

public: //Math
	Vec2<T> operator+(const Vec2<T>& rhs)
	{
		return Vec2<T>{ x + rhs.x, y + rhs.y };
	}
	Vec2<T>& operator+=(Vec2<T>& rhs)
	{
		return Vec2<T>{this.x + rhs.x, this.y + rhs.y};
	}

	Vec2<T> operator-(const Vec2<T>& rhs)
	{
		return Vec2<T>{ x - rhs.x, y - rhs.y };
	}
	Vec2<T>& operator-=(Vec2<T>& rhs)
	{
		return Vec2<T>{this.x - rhs.x, this.y - rhs.y};
	}

	Vec2<T> operator*(const Vec2<T>& rhs)
	{
		return Vec2<T>{ x * rhs.x, y * rhs.y };
	}
	Vec2<T>& operator*=(Vec2<T>& rhs)
	{
		return Vec2<T>{this.x * rhs.x, this.y * rhs.y};
	}

	Vec2<T> operator/(const Vec2<T>& rhs)
	{
		return Vec2<T>{ x / rhs.x, y / rhs.y };
	}
	Vec2<T>& operator/=(Vec2<T>& rhs)
	{
		return Vec2<T>{this.x / rhs.x, this.y / rhs.y};
	}

public: //Comparison
	bool operator==(const Vec2<T> rhs)
	{
		return x == rhs.x && y == rhs.y;
	}
	bool operator!=(const Vec2<T> rhs)
	{
		return x != rhs.x || y != rhs.y;
	}
	//bool operator<(const Vec2<T> rhs)
	//{
	//	return x < rhs.x && y < rhs.y;
	//}
	//bool operator>(const Vec2<T> rhs)
	//{
	//	return x > rhs.x && y > rhs.y;
	//}
	//bool operator<=(const Vec2<T> rhs)
	//{
	//	return x <= rhs.x && y <= rhs.y;
	//}
	//bool operator>=(const Vec2<T> rhs)
	//{
	//	return x >= rhs.x && y >= rhs.y;
	//}

public:
	T x;
	T y;
};