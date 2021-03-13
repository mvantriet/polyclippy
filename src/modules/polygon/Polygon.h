#ifndef _POLYGON_H_
#define _POLYGON_H_

#include "Edge.h"
#include "Shape.h"

enum polygon_allocation_result_enum
{
	SUCCESS_NEW,
	FAIL,
	UNSUPPORTED,
	SUCCESS_OVERWRITTEN
};

typedef enum polygon_allocation_result_enum POLYGON_ALLOCATION_RESULT;

class Polygon : public Shape
{
private:
	Edge* p_edges;
	unsigned int max_nof_edges;
	unsigned int nof_edges_added;
	bool copied;
	unsigned int get_nof_points();

#ifdef DEBUG
	void print_polygon_array(Point<int>** pp_point_array, unsigned int nof_points);
#endif

public:
	Polygon();
	Polygon(unsigned int nof_edges);
	Polygon(Point<int>** pp_point_array, unsigned int nof_points_in_array);
	virtual ~Polygon();
	void add_edge(int x1, int y1, int x2, int y2, unsigned int edge_index);
	Edge* get_edges();
	Edge* get_edge(unsigned int idx);
	unsigned int get_max_nof_edges();
	unsigned int get_nof_edges();
	void set_nof_edges(unsigned int nof_edges);
	void init_edge_array(unsigned int nof_edges);
	Polygon* clone();
	Polygon* intersect(Polygon* p_clip);
};

#endif
