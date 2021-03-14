#include <stdio.h>
#include <iostream>
#include <assert.h>
#include "Edge.h"
#include "stdlib.h"

static void edge_tests();

int main(void)
{
	edge_tests();
}

void edge_tests()
{
	std::cout << "EDGE_TESTS" << std::endl << std::endl;

	// Intersection tests
	Edge* v1 = new Edge();
	Edge* v2 = new Edge();
	Point<double> result;
	result.setX(0);
	result.setY(0);

	// Intersection (2, 3)
	v1->getP1()->setX(1);
	v1->getP1()->setY(1);
	v1->getP2()->setX(3);
	v1->getP2()->setY(5);

	v2->getP1()->setX(2);
	v2->getP1()->setY(2);
	v2->getP2()->setX(2);
	v2->getP2()->setY(8);

	v1->edge_intersection(v2, &result);

	assert(result.getX() == 2);
	assert(result.getY() == 3);

	// No intersection!

	// Reinitialize the point
	result.setX(0);
	result.setY(0);
	std::cout << "(" << result.getX() << "," << result.getY() << ")" << std::endl;
	v1->getP1()->setX(1);
	v1->getP1()->setY(1);
	v1->getP2()->setX(3);
	v1->getP2()->setY(5);

	v2->getP1()->setX(4);
	v2->getP1()->setY(4);
	v2->getP2()->setX(6);
	v2->getP2()->setY(8);

	v1->edge_intersection(v2, &result);

	std::cout << "(" << result.getX() << "," << result.getY() << ")" << std::endl;
	// Check if indeed no intersection
	assert(result.getX() == 0);
	assert(result.getY() == 0);

	std::cout << "END OF EDGE_TESTS" << std::endl;
}