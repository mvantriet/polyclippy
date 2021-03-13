#include <stdlib.h>
#include "Edge.h"
#include "math.h"
#include "MathUtil.h"

Edge::Edge()
{
	this->init();
}

Edge::Edge(Point<int>* p1, Point<int>* p2)
{
	this->p1 = p1;
	this->p2 = p2;
}

Edge::~Edge()
{
	delete this->p1;
	delete this->p2;
}

void Edge::init()
{
	this->p1 = new Point<int>(0,0);
	this->p2 = new Point<int>(0,0);
}

Point<int>* Edge::getP1()
{
	return this->p1;
}

Point<int>* Edge::getP2()
{
	return this->p2;
}

void Edge::setP1(Point<int>* p1)
{
	this->p1 = p1;
}

void Edge::setP2(Point<int>* p2)
{
	this->p2 = p2;
}

double Edge::getLength()
{
	double xAbs = fabs(this->p1->getX() - this->p2->getX());
	double yAbs = fabs(this->p1->getY() - this->p2->getY());
	return sqrt(pow(xAbs,2) + pow(yAbs,2));
}

Edge* Edge::clone()
{
	Point<int>* p;

	Edge* p_edge = new Edge();

	Point<int>* p1 = this->getP1()->clone();
	Point<int>* p2 = this->getP2()->clone();

	p_edge->setP1(p1);
	p_edge->setP2(p2);

	return p_edge;
}

void Edge::edge_intersection(Edge* p_edge_intersect, Point<double>* p_point_result)
{
	int xdiff_this;
	int xdiff_target;
	int ydiff_this;
	int ydiff_target;
	int diff_det;
	int this_edge_det;
	int intersect_edge_det;
	double intersection_x;
	double intersection_y;

	// Calculate the absolute difference in X and Y for this edge
	xdiff_this = this->p1->getX() - this->p2->getX();
	xdiff_target = p_edge_intersect->p1->getX() - p_edge_intersect->p2->getX();

	// Calculate the absolute difference in X and Y for the edge to intersect with
	ydiff_this = this->p1->getY() - this->p2->getY();
	ydiff_target = p_edge_intersect->getP1()->getY() - p_edge_intersect->getP2()->getY();

	// Calc determinaant of diff to check if it's paralell (det == 0)
	diff_det = math_util::determinant_2D<int>(xdiff_this,ydiff_this,xdiff_target,ydiff_target);

	if (diff_det == 0)
	{
		return;
	}

	this_edge_det = math_util::determinant_2D<int>(this->p1, this->p2);
	intersect_edge_det = math_util::determinant_2D<int>(p_edge_intersect->getP1(), p_edge_intersect->getP2());

	intersection_x = math_util::determinant_2D<int>(this_edge_det, intersect_edge_det, xdiff_this, xdiff_target);
	intersection_y = math_util::determinant_2D<int>(this_edge_det, intersect_edge_det, ydiff_this, ydiff_target);

	// Divide by diff_det to get the coordinates of the intersection
	intersection_x = intersection_x / diff_det;
	intersection_y = intersection_y / diff_det;

	p_point_result->setX(intersection_x);
	p_point_result->setY(intersection_y);
}

void Edge::edge_intersection(Edge* p_edge_intersect, Point<int>* p_point_result)
{
	// Support integers
	Point<double> result;
	this->edge_intersection(p_edge_intersect, &result);
	p_point_result->setX((int)result.getX());
	p_point_result->setY((int)result.getY());
}
