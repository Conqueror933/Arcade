#pragma once
#include <cmath>
#include <algorithm>
#include <iostream>
#include <limits>

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
	//Vec2(Vec2&& rhs) = delete;
	//Vec2& operator= (Vec2&& rhs) = delete;
	~Vec2() = default;

public: //Math
	// +
	Vec2<T> operator+(const Vec2<T>& rhs) const
	{
		return Vec2<T>{ x + rhs.x, y + rhs.y };
	}
	Vec2<T>& operator+=(Vec2<T>& rhs)
	{
		return Vec2<T>{this.x + rhs.x, this.y + rhs.y};
	}
	Vec2<T> operator+(const T rhs) const
	{
		return Vec2<T>{ x + rhs, y + rhs };
	}
	// -
	Vec2<T> operator-(const Vec2<T>& rhs) const
	{
		return Vec2<T>{ x - rhs.x, y - rhs.y };
	}
	Vec2<T>& operator-=(Vec2<T>& rhs)
	{
		return Vec2<T>{this.x - rhs.x, this.y - rhs.y};
	}
	Vec2<T> operator-(const T rhs) const
	{
		return Vec2<T>{ x - rhs, y - rhs };
	}
	// *
	Vec2<T> operator*(const Vec2<T>& rhs) const
	{
		return Vec2<T>{ x * rhs.x, y * rhs.y };
	}
	Vec2<T>& operator*=(Vec2<T>& rhs)
	{
		return Vec2<T>{this.x * rhs.x, this.y * rhs.y};
	}
	Vec2<T> operator*(const T rhs) const
	{
		return Vec2<T>{ x * rhs, y * rhs };
	}
	// /
	Vec2<T> operator/(const Vec2<T>& rhs) const
	{
		return Vec2<T>{ x / rhs.x, y / rhs.y };
	}
	Vec2<T>& operator/=(Vec2<T>& rhs)
	{
		return Vec2<T>{this.x / rhs.x, this.y / rhs.y};
	}
	Vec2<T> operator/(const T rhs) const
	{
		return Vec2<T>{ x / rhs, y / rhs };
	}
	// Vector Operations
	T dotproduct(const Vec2<T>& rhs) const
	{
		return x * rhs.x + y * rhs.y;
	}
	T getLengthSquared() const
	{
		return x * x + y * y;
	}
	T getLength() const
	{
		return std::sqrt(getLengthSquared());
	}
	Vec2<T>& Normalize()
	{
		const T length = getLength();
		x /= getLength();
		y /= getLength();
		return *this;
	}
	Vec2<T> GetNormalized() const
	{
		Vec2<T> norm = *this;
		norm.Normalize();
		return norm;
	}
	T GetDistanceSquared(const Vec2<T>& rhs)
	{
		return (x - rhs.x) * (x - rhs.x) + (y - rhs.y) * (y - rhs.y);
	}
	T GetDistance(const Vec2<T>& rhs)
	{
		return std::sqrt(getDistanceSquared());
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

template<typename T> T findSmallest(T arr[], int n)
{
	T temp = arr[0]; for (int i = 0; i < n; i++) if (temp > arr[i]) temp = arr[i]; return temp;
}
template<typename T> T findBiggest(T arr[], int n)
{
	T temp = arr[0]; for (int i = 0; i < n; i++) if (temp < arr[i]) temp = arr[i]; return temp;
}

namespace Vec2Math
{
	template<typename T> struct Circle { Vec2<T> pos; T size; };
	template<typename T> struct Line { Vec2<T> p1, p2; }; //technically a LineSegment
	template<typename T> struct Triangle { Vec2<T> p1, p2, p3; };
	//template<typename T> struct Rect { Vec2<T> p1, p2, p3, p4; }; //"Rectangle" already exists
	namespace AxisAligned
	{
		template<typename T> bool isColliding(const T& x1, const T& x2, const T& y1, const T& y2, const Vec2<T>& point)
		{
			T left	 = x1 < x2 ? x1 : x2;
			T right	 = x1 > x2 ? x1 : x2;
			T top	 = y1 < y2 ? y1 : y2;
			T bottom = y1 > y2 ? y1 : y2;
			return left <= point.x && right >= point.x && top <= point.y && bottom >= point.y;
		}
		template<typename T> bool isColliding(const Vec2<T>& p1, const Vec2<T>& p2, const Vec2<T>& point)
		{
			return isColliding(p1.x, p2.x, p1.y, p2.y, point);
		}
		template<typename T> bool isColliding(const Line<T>& line, const Vec2<T>& point)
		{
			return isColliding(line.p1, line.p2, point);
		}
		//template<typename T> bool isColliding(const Rect<T>& rect, const Vec2<T>& point)
		//{
		//	T temp[] = { rect.p1.x, rect.p2.x, rect.p3.x, rect.p4.x };
		//	const T min_x = findSmallest(temp, 4);
		//	temp = { rect.p1.y, rect.p2.y, rect.p3.y, rect.p4.y };
		//	const T min_y = findSmallest(temp, 4);
		//	temp = { rect.p1.x, rect.p2.x, rect.p3.x, rect.p4.x };
		//	const T max_x = findBiggest(temp, 4);
		//	temp = { rect.p1.y, rect.p2.y, rect.p3.y, rect.p4.y };
		//	const T max_y = findBiggest(temp, 4);
		//	return isColliding(min_x, max_x, min_y, max_y, point);
		//}
	}
	//helper functions
	template<typename T> const T getSlope(const Vec2<T>& p1, const Vec2<T>& p2)
	{
		return p1.x != p2.x ? (p2.y - p1.y) / (p2.x - p1.x) : std::numeric_limits<T>::max();
	}
	template<typename T> const T getSlope(const Line<T>& line)
	{
		return getSlope(line.p1, line.p2);
	}
	template<typename T> const T getYOffset(const Line<T>& line)
	{
		return line.p1.y - getSlope(line) * line.p1.x;
	}
	template<typename T> const T getYOffset(const Vec2<T>& point, const T slope)
	{
		return point.p1.y - slope * point.p1.x;
	}

	template<typename T> Vec2<T> getCollisionPoint(const T& slope1, const T& slope2, const T& YOffset1, const T& YOffset2)
	{//find point where (infinite)lines meet
		const T x = (YOffset2 - YOffset1) / (slope1 - slope2);
		const T y = slope1 * x + YOffset1;
		return Vec2<T>{x, y};
	}
	template<typename T> Vec2<T> getCollisionPoint(const Line<T>& line1, const Line<T>& line2)
	{ //get y = m * x + b from the 2 points
		const T m1 = getSlope(line1);
		const T m2 = getSlope(line2);
		const T b1 = getYOffset(line1);
		const T b2 = getYOffset(line2);
		return getCollisionPoint(m1, m2, b1, b2);
	}
	template<typename T> T getTriArea(const Vec2<T>& p1, const Vec2<T>& p2, const Vec2<T>& p3)
	{
		//return ((p1.x - p3.x) * (p2.y - p3.y) - (p2.x - p3.x) * (p1.y - p3.y)) / (T)2.0; //https://www.gamedev.net/forums/?topic_id=295943
		return std::abs((p1.x * (p2.y - p3.y) + p2.x * (p3.y - p1.y) + p3.x * (p1.y - p2.y)) / (T)2.0); 
		//https://www.mathopenref.com/coordtrianglearea.html
	}
	template<typename T> T getTriArea(const Triangle<T>& tri)
	{
		return getTriArea(tri.p1, tri.p2, tri.p3);
	}

	//Point colliding with X
	template<typename T> bool isColliding(const Vec2<T>& point1, const Vec2<T>& point2)
	{
		return point1 == point2;
	}
	template<typename T> bool isColliding(const Vec2<T>& point, const Line<T>& line)
	{
		if (line.p1.x != line.p2.x) //dont divide by 0
		{
			if (AxisAligned::isColliding(line, point))
			{
				//get y = m * x + b from the 2 points
				const T m = getSlope(line);
				const T b = getYOffset(line);
				//if point is on line return true
				if (point.y == m * point.x + b) return true;
			}
			return false;
		}
		else return point.x == line.p1.x && point.y >= line.p1.y && point.y <= line.p2.y;
	}
	//template<typename T> bool isColliding(const Vec2<T>& point, const Rect<T>& rect)
	//{
	//
	//}
	template<typename T> bool isColliding(const Vec2<T>& point, const Circle<T>& circle)
	{
		return point.GetDistanceSquared(circle) < circle.size * circle.size;
	}

	//Line colliding with X
	template<typename T> bool isColliding(const Line<T>& line, const Vec2<T>& point)
	{
		return isColliding(point, line);
	}
	template<typename T> bool isColliding(const Line<T>& line1, const Line<T>& line2)
	{
		const auto col = getCollisionPoint(line1, line2);
		const bool b = true;
		b = b && AxisAligned::isColliding(line1, col);
		b = b && AxisAligned::isColliding(line2, col);
		return b;
	}
	//template<typename T> bool isColliding(const Line<T>& line, const Rect<T>& rect)
	//{
	//
	//}
	template<typename T> bool isColliding(const Line<T>& line, const Circle<T>& circle)
	{
		//find 90° twisted line, line that up with the circle, check distance<size, check end points
		const T m1 = getSlope(line);
		const T m2 = (T)-1.0 / getSlope(line); //orthogonalSlope
		const T b1 = getYOffset(line);
		const T b2 = getYOffset(circle.pos, m);
		const auto col = getCollisionPoint(m1, m2, b1, b2);
		//return std::abs(col - circle.pos) < circle.size;
		return circle.pos.GetDistanceSquared(col) < circle.size * circle.size;
	}

	//Triangle colliding with X
	template<typename T> bool isColliding(const Triangle<T>& tri, const Vec2<T>& point)
	{
		T TotalArea = getTriArea(tri);
		T area1 = getTriArea(point, tri.p1, tri.p2);
		T area2 = getTriArea(point, tri.p2, tri.p3);
		T area3 = getTriArea(point, tri.p1, tri.p3);
		if (area1 + area2 + area3 > TotalArea) return false;
		else return true;
	}
	template<typename T> bool isColliding(const Triangle<T>& tri, const Line<T>& line)
	{
		bool collision = false;
		collision = collision || isColliding(line, { tri.p1, tri.p2 });
		collision = collision || isColliding(line, { tri.p2, tri.p3 });
		collision = collision || isColliding(line, { tri.p1, tri.p3 });
		if (collision) return true; //armortizing cause line within triangle should never if rarely be the case
		else return isColliding(tri, line.p1);
	}
	template<typename T> bool isColliding(const Triangle<T>& tri, const Circle<T>& circle)
	{
		//pick your armortizing, 1st check edges, 2nd check within
		bool collision = false;
		collision = collision || isColliding(circle, { tri.p1, tri.p2 });
		collision = collision || isColliding(circle, { tri.p2, tri.p3 });
		collision = collision || isColliding(circle, { tri.p1, tri.p3 });
		if (collision) return true;
		else return isColliding(tri, circle.pos);
	}
	template<typename T> bool isColliding(const Triangle<T>& tri1, const Triangle<T>& tri2)
	{ //no optimization done
		bool collision = false;
		collision = collision || isColliding({ tri1.p1, tri1.p2 }, { tri2.p1, tri2.p2 });
		collision = collision || isColliding({ tri1.p2, tri1.p3 }, { tri2.p1, tri2.p2 });
		collision = collision || isColliding({ tri1.p1, tri1.p3 }, { tri2.p1, tri2.p2 });
		collision = collision || isColliding({ tri1.p1, tri1.p2 }, { tri2.p2, tri2.p3 });
		collision = collision || isColliding({ tri1.p2, tri1.p3 }, { tri2.p2, tri2.p3 });
		collision = collision || isColliding({ tri1.p1, tri1.p3 }, { tri2.p2, tri2.p3 });
		collision = collision || isColliding({ tri1.p1, tri1.p2 }, { tri2.p1, tri2.p3 });
		collision = collision || isColliding({ tri1.p2, tri1.p3 }, { tri2.p1, tri2.p3 });
		collision = collision || isColliding({ tri1.p1, tri1.p3 }, { tri2.p1, tri2.p3 });
		collision = collision || isColliding(tri1, tri2.p1);
		collision = collision || isColliding(tri1, tri2.p2);
		collision = collision || isColliding(tri1, tri2.p3);
		return collision;
	}
	//template<typename T> bool isColliding(const Triangle<T>& tri, const Rect<T>& rect)
	//{

	//}

	//Rectangle colliding with X
	//template<typename T> bool isColliding(const Rect<T>& rect, const Vec2<T>& point)
	//{
	//
	//}
	//template<typename T> bool isColliding(const Rect<T>& rect, const Line<T>& line)
	//{
	//
	//}
	//template<typename T> bool isColliding(const Rect<T>& rect1, const Rect<T>& rect2)
	//{
	//
	//}
	//template<typename T> bool isColliding(const Rect<T>& rect, const Circle<T>& circle)
	//{
	//
	//}

	//Circle colliding with X
	template<typename T> bool isColliding(const Circle<T>& circle, const Vec2<T>& point)
	{
		return isColliding(point, circle);
	}
	template<typename T> bool isColliding(const Circle<T>& circle, const Line<T>& line)
	{
		return isColliding(line, circle);
	}
	//template<typename T> bool isColliding(const Circle<T>& circle, const Rect<T>& rect)
	//{
	//
	//}
	template<typename T> bool isColliding(const Circle<T>& circle1, const Circle<T>& circle2)
	{
		return circle1.pos.GetDistanceSquared(circle2.pos) < circle1.size * circle1.size + circle2.size * circle2.size;
	}

	template<typename T>
	void DoRebound(const Vec2<T>& wall, Vec2<T>& ballvelocity)
	{
		auto wn = wall.GetNormalized();
		ballvelocity = 2 * (ballvelocity * wn) * wn - ballvelocity;
	}
}