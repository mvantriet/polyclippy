#ifndef _POINT_UTIL_H_
#define _POINT_UTIL_H_

#include "Point.h"
#include "MathUtil.h"

namespace point_util
{
	template<class T> bool point_inside_boundary(Point<T>* target_point, Point<T>* boundary_point_1, Point<T>* boundary_point_2)
	{
		bool inside;
		T xdiff;
		T ydiff;
		T point_position_vector[3];
		T boundary_vector[3];
		T cross_product[3];

		point_position_vector[0] = boundary_point_1->getX() - target_point->getX();
		point_position_vector[1] = boundary_point_1->getY() - target_point->getY();
		boundary_vector[0] = boundary_point_2->getX() - boundary_point_1->getX();
		boundary_vector[1] = boundary_point_2->getY() - boundary_point_1->getY();
		// Add zero, 3D is supported by this function by not used
		point_position_vector[2] = 0;
		boundary_vector[2] = 0;

		// Calculate the cross vector of the point position vector and the boundary vector
		math_util::cross_product_3D<T>(&point_position_vector[0], &boundary_vector[0], &cross_product[0]);

		// Check the z-axis of the cross product, if it is negative or zero it means it's inside
		inside = (cross_product[2] <= 0) ? true : false;
		return inside;
	}


	template<class T> bool point_inside_boundary(Point<T>* target_point, Point<T> boundary_points[2])
	{
		return point_inside_boundary(target_point, &boundary_points[0], &boundary_points[1]);
	}
}


#endif