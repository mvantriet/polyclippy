#ifndef _MATH_UTIL_H_
#define _MATH_UTIL_H_

#include "Point.h"

namespace math_util
{
	template<class T> T determinant_2D(T x1, T y1, T x2, T y2)
	{
		return x1 * y2 - y1 * x2;
	}

	template<class T> T determinant_2D(Point<T>* p1, Point<T>* p2)
	{
		T x1;
		T y1;
		T x2;
		T y2;
		x1 = p1->getX();
		y1 = p1->getY();
		x2 = p2->getX();
		y2 = p2->getY();

		return determinant_2D<T>(x1,y1,x2,y2);
	}

	template<class T> T cross_product_2D(Point<T>* p1, Point<T>* p2)
	{
		return p1->getX()*p2->getY() - p1->getY()*p2->getX();
	}

	template<class T> void cross_product_3D(T v1[3], T v2[3], T result[3])
	{
		result[0] = (v1[1] * v2[2]) - (v1[2] * v2[1]);
		result[1] = (v1[2] * v2[0]) - (v1[0] * v2[2]);
		result[2] = (v1[0] * v2[1]) - (v1[1] * v2[0]);
	}
}

#endif