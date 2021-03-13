#ifndef _POLY_UTIL_H_
#define _POLY_UTIL_H_

#include "Point.h"
#include "Edge.h"
#include "Polygon.h"

namespace polygon_util
{
	template <class T> void set_polygon_point_array(Polygon* p_polygon, Point<T>** pp_point_array)
	{
		unsigned int i;
		unsigned int nof_edges;
		Edge* p_edge;

		nof_edges = p_polygon->get_nof_edges();

		for(i = 0; i < nof_edges; i++)
		{
			p_edge = p_polygon->get_edge(i);
			pp_point_array[i*2] = p_edge->getP1();
			pp_point_array[(i*2)+1] = p_edge->getP2();
		}
	}
	template <class T> void copy_point_array(Point<T>** pp_point_array_to, Point<T>** pp_point_array_source, unsigned int nof_points)
	{
		unsigned int i;
		for(i = 0; i < nof_points; i++)
		{
			pp_point_array_to[i] = pp_point_array_source[i];
		}
	}

	template <class T> void empty_point_array(Point<T>** pp_point_array, unsigned int nof_points)
	{
		unsigned int i;
		for (i = 0; i < nof_points; i++)
		{
			pp_point_array[i] = NULL;
		}

	}

	template <class T> Point<T>* perform_subject_clip_polygon_edge_intersection(Point<T>* p_subject_line_p1, Point<T>* p_subject_line_p2, Edge* p_clip_boundary_edge)
	{
		Edge subject_line_segment_edge;
		Point<T> intersection_point;

		subject_line_segment_edge.setP1(p_subject_line_p1);
		subject_line_segment_edge.setP2(p_subject_line_p2);

		p_clip_boundary_edge->edge_intersection(&subject_line_segment_edge, &intersection_point);

		subject_line_segment_edge.setP1(NULL);
		subject_line_segment_edge.setP2(NULL);

		return intersection_point.clone();
	}
}

#endif