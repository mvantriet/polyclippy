#ifndef _EDGE_H_
#define _EDGE_H_

#ifdef __cplusplus

#include "Point.h"

class Edge
{
private:
	Point<int>* p1;
	Point<int>* p2;
public:
	Edge();
	Edge(Point<int>* p1, Point<int>* p2);
	~Edge();
	void setP1(Point<int>* p1);
	void setP2(Point<int>* p2);
	void init();
	Point<int>* getP1();
	Point<int>* getP2();
	double getLength();
	Edge* clone();
	void edge_intersection(Edge* p_edge_intersect, Point<double>* p_point_result);
	void edge_intersection(Edge* p_edge_intersect, Point<int>* p_point_result);
};

#endif

#endif
