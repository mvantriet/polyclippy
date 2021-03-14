#include <stdio.h>
#include <iostream>
#include "Polygon.h"
#include "Edge.h"
#include <assert.h>
#include "stdlib.h"

void polygon_tests();

int main(void)
{
	polygon_tests();
}

void polygon_tests()
{
	std::cout << "POLYGON_TESTS" << std::endl << std::endl;

	unsigned int i;

	Polygon* p_polygon = new Polygon(10);

	// Fill
	for (i = 0; i < p_polygon->get_max_nof_edges(); i++)
	{
		p_polygon->add_edge(i,0,0,0,i);
	}

	std::cout << "Original" << std::endl;
	for (i = 0; i < p_polygon->get_nof_edges(); i++)
	{
		Edge* p = p_polygon->get_edge(i);
		std::cout << "V(" << i << ") ( " << p->getP1()->getX() << "," << p->getP1()->getY() << ") - (" << p->getP2()->getX() << "," << p->getP2()->getY() << ")" << std::endl;
	}

	p_polygon->init_edge_array(4);
	p_polygon->init_edge_array(13);

	std::cout << std::endl;
	std::cout << "Changed size" << std::endl;
	for (i = 0; i < p_polygon->get_nof_edges(); i++)
	{
		Edge* p = p_polygon->get_edge(i);
		std::cout << "E(" << i << ") ( " << p->getP1()->getX() << "," << p->getP1()->getY() << ") - (" << p->getP2()->getX() << "," << p->getP2()->getY() << ")" << std::endl;
	}


	Polygon* p_polygon_clone = p_polygon->clone();

	std::cout << std::endl;
	std::cout << "Cloned" << std::endl;
	for (i = 0; i < p_polygon_clone->get_nof_edges(); i++)
	{
		Edge* p = p_polygon_clone->get_edge(i);
		std::cout << "E(" << i << ") ( " << p->getP1()->getX() << "," << p->getP1()->getY() << ") - (" << p->getP2()->getX() << "," << p->getP2()->getY() << ")" << std::endl;
	}

	std::cout << "END OF POLYGON_TESTS" << std::endl;

}