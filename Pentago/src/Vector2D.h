#pragma once

namespace SFMath
{
	template <class T>
	class Point2D
	{
	public:

		Point2D()
			:x(0),y(0)
		{
		}

		Point2D(T px, T py)
			:x(px),y(py)
		{
		}

		T x, y;

		void operator += (const Point2D& p)
		{
			x += p.x;
			y += p.y;
		}

		void operator -= (const Point2D& p)
		{
			x -= p.x;
			y -= p.y;
		}
	};

	template <class V>
	class Vector2D : public Point2D<V>
	{
	public:

		Vector2D()
		{
			x = 0;
			y = 0;
		}

		Vector2D(V px, V py)
			:Point2D<V>(px,py)
		{

		}

		void Normalize()
		{
			V len = this->LengthSqr();
			
			if(abs(x) > 0)
				x /= len;
			if(abs(y) > 0)
				y /= len;
		}
		
		V Length()
		{
			return x*x+y*y;
		}

		V LengthSqr()
		{
			return sqrt(Length());
		}

		void operator *= (const float& p)
		{
			x *= p;
			y *= p;
		}

		Vector2D operator * (const float& p) const
		{
			Vector2D<V> temp;
			temp.x = x * p;
			temp.y = y * p;
			return temp;
		}

		Vector2D operator + (const Vector2D& p) const
		{
			Vector2D result = Vector2D(x,y);
			result.x += p.x;
			result.y += p.y;

			return result;
		}

		Vector2D operator - (const Vector2D& p) const
		{
			Vector2D result = Vector2D(x,y);
			result.x -= p.x;
			result.y -= p.y;

			return result;
		}

		void operator -= (const Vector2D& p)
		{
			x -= p.x;
			y -= p.y;
		}
	};

	typedef Vector2D<float> Vector2Df;
	typedef Vector2D<int> Vector2Di;
};