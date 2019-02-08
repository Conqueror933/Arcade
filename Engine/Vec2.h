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
	template<typename S>
	explicit Vec2(const Vec2<S>& rhs)
	{
		x = (T)rhs.x;
		y = (T)rhs.y;
	}

	//Vec2(const Vec2& rhs) : x(rhs.x), y(rhs.y){}
	//Vec2& operator= (const Vec2& rhs) { return *this = Vec2(rhs); }
	//Vec2(Vec2&& rhs);
	//Vec2& operator= (Vec2&& rhs);
	~Vec2() = default;

public: //Math
	// +
	Vec2<T> operator+(const Vec2<T>& rhs)
	{
		return Vec2<T>{ x + rhs.x, y + rhs.y };
	}
	Vec2<T>& operator+=(Vec2<T>& rhs)
	{
		return Vec2<T>{this.x + rhs.x, this.y + rhs.y};
	}
	Vec2<T> operator+(const T rhs)
	{
		return Vec2<T>{ x + rhs, y + rhs };
	}
	Vec2<T> operator+(const T rhs) const
	{
		return Vec2<T>{ x + rhs, y + rhs };
	}
	// -
	Vec2<T> operator-(const Vec2<T>& rhs)
	{
		return Vec2<T>{ x - rhs.x, y - rhs.y };
	}
	Vec2<T>& operator-=(Vec2<T>& rhs)
	{
		return Vec2<T>{this.x - rhs.x, this.y - rhs.y};
	}
	Vec2<T> operator-(const T rhs)
	{
		return Vec2<T>{ x - rhs, y - rhs };
	}
	Vec2<T> operator-(const T rhs) const
	{
		return Vec2<T>{ x - rhs, y - rhs };
	}
	// *
	Vec2<T> operator*(const Vec2<T>& rhs)
	{
		return Vec2<T>{ x * rhs.x, y * rhs.y };
	}
	Vec2<T>& operator*=(Vec2<T>& rhs)
	{
		return Vec2<T>{this.x * rhs.x, this.y * rhs.y};
	}
	Vec2<T> operator*(const T rhs)
	{
		return Vec2<T>{ x * rhs, y * rhs };
	}
	// /
	Vec2<T> operator/(const Vec2<T>& rhs)
	{
		return Vec2<T>{ x / rhs.x, y / rhs.y };
	}
	Vec2<T>& operator/=(Vec2<T>& rhs)
	{
		return Vec2<T>{this.x / rhs.x, this.y / rhs.y};
	}
	Vec2<T> operator/(const T rhs)
	{
		return Vec2<T>{ x / rhs, y / rhs };
	}
	// special
	Vec2<T> static constminus(const Vec2<T>& lhs, const Vec2<T>& rhs)
	{
		return Vec2<T>{lhs.x - rhs.x, lhs.y - rhs.y};
	}

public: //Comparison
	bool operator==(const Vec2<T>& rhs)
	{
		return x == rhs.x && y == rhs.y;
	}
	bool operator!=(const Vec2<T>& rhs)
	{
		return x != rhs.x || y != rhs.y;
	}

	int static pickHighest(const Vec2<T>& rhs)
	{
		return rhs.x > rhs.y ? rhs.x : rhs.y;
	}
	int static pickLowest(const Vec2<T>& rhs)
	{
		return rhs.x < rhs.y ? rhs.x : rhs.y;
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