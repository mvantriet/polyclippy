#include <stdio.h>
#include <iostream>
#include <assert.h>
#include "Point.h"
#include "PointUtil.h"
#include "stdlib.h"

static void util_tests();

int main(void)
{
	util_tests();
}

void util_tests()
{
	std::cout << "UTIL_TESTS" << std::endl << std::endl;

	Point<int> point;
	Point<int> boundary_point_1;
	Point<int> boundary_point_2;

	Point<int> boundary[2];
	bool inside;

	// Inside
	point.setX(6);
	point.setY(3);

	boundary[0].setX(2);
	boundary[0].setY(2);
	boundary[1].setX(8);
	boundary[1].setY(5);

	inside = point_util::point_inside_boundary<int>(&point, &boundary[0], &boundary[1]);
	assert(inside==true);

	// Outisde
	point.setX(0);
	point.setY(0);

	boundary[0].setX(8);
	boundary[0].setY(2);
	boundary[1].setX(2);
	boundary[1].setY(2);

	inside = point_util::point_inside_boundary<int>(&point, &boundary[0], &boundary[1]);
	assert(inside==false);

	// Inside (counter intuitive)
	// TODO: Validate if inside functions works correctly when the cross product between point and boundary points becomes zero
	boundary_point_1.setX(2);
	boundary_point_1.setY(3);
	boundary_point_2.setX(2);
	boundary_point_2.setY(3);

	point.setX(0);
	point.setY(0);

	inside = point_util::point_inside_boundary<int>(&point, &boundary_point_1, &boundary_point_2);
	assert(inside==true);

	std::cout << "END OF UTIL_TESTS" << std::endl;
}