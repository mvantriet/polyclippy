#include <stdio.h>
#include <iostream>
#include "Polygon.h"
#include "Edge.h"
#include <assert.h>
#include "stdlib.h"

static void polygon_intersection_test();

int main(void)
{
	polygon_intersection_test();
}

void polygon_intersection_test()
{
	Polygon* p_subject_polygon;
	Polygon* p_clip_polygon;
	Polygon* p_result_polygon;
	unsigned int i;

	std::cout << std::endl;
	std::cout << "Intersection test" << std::endl;

	p_subject_polygon = new Polygon(3);
	p_clip_polygon = new Polygon(3);

	p_subject_polygon->add_edge(0,0,6,0,0);
	p_subject_polygon->add_edge(6,0,6,3,1);
	p_subject_polygon->add_edge(6,3,0,0,2);

	p_clip_polygon->add_edge(2,2,8,2,0);
	p_clip_polygon->add_edge(8,2,8,5,1);
	p_clip_polygon->add_edge(8,5,2,2,2);

	std::cout << "intersect:" << std::endl;
	p_result_polygon = p_subject_polygon->intersect(p_clip_polygon);
	std::cout << std::endl << std::endl;


	/* This test is order dependent, if the intersect method is ever updated that influences
	 * the order of the result, this test will fail and needs to be updated. */
	assert(p_result_polygon->get_edge(0)->getP1()->getX() == 6);
	assert(p_result_polygon->get_edge(0)->getP1()->getY() == 2);
	assert(p_result_polygon->get_edge(0)->getP2()->getX() == 6);
	assert(p_result_polygon->get_edge(0)->getP2()->getY() == 3);

	assert(p_result_polygon->get_edge(1)->getP1()->getX() == 6);
	assert(p_result_polygon->get_edge(1)->getP1()->getY() == 3);
	assert(p_result_polygon->get_edge(1)->getP2()->getX() == 4);
	assert(p_result_polygon->get_edge(1)->getP2()->getY() == 2);

	assert(p_result_polygon->get_edge(2)->getP1()->getX() == 4);
	assert(p_result_polygon->get_edge(2)->getP1()->getY() == 2);
	assert(p_result_polygon->get_edge(2)->getP2()->getX() == 6);
	assert(p_result_polygon->get_edge(2)->getP2()->getY() == 2);

	std::cout << "Result polygon contains " << p_result_polygon->get_nof_edges() << std::endl;
	for (i = 0; i < p_result_polygon->get_nof_edges(); i++)
	{
		Edge* p = p_result_polygon->get_edge(i);
		std::cout << "E(" << i << ") ( " << p->getP1()->getX() << "," << p->getP1()->getY() << ") - (" << p->getP2()->getX() << "," << p->getP2()->getY() << ")" << std::endl;
	}

	delete p_subject_polygon;
	delete p_clip_polygon;
	delete p_result_polygon;
}