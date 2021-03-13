#include <string.h>
#include <math.h>
#include <assert.h>
#include <stdlib.h>
#include "Polygon.h"
#include "PolyUtil.h"
#include "PointUtil.h"

Polygon::Polygon() : Shape()
{
	this->max_nof_edges = 0;
	this->nof_edges_added = 0;
	this->p_edges = NULL;
	copied = false;
}

Polygon::Polygon(unsigned int max_nof_edges)
{
	this->max_nof_edges = max_nof_edges;
	this->nof_edges_added = 0;
	this->p_edges = NULL;
	init_edge_array(this->max_nof_edges);
	copied = false;
}

Polygon::Polygon(Point<int>** pp_point_array, unsigned int nof_points_in_array)
{
	unsigned int 	i;
	unsigned int	nof_edges;
	Edge* 		p_edge;

	/* Should have an equal number of points */
	assert(nof_points_in_array % 2 == 0);

	nof_edges = ceil(nof_points_in_array / 2.0);
	init_edge_array(nof_edges);

	for(i = 0; i < nof_edges; i++)
	{
		p_edge = this->get_edge(i);
		p_edge->setP1(pp_point_array[i*2]->clone());
		p_edge->setP2(pp_point_array[(i*2)+1]->clone());
	}
	this->max_nof_edges 	= nof_edges;
	this->nof_edges_added = nof_edges;
}

Polygon::~Polygon()
{
	delete this->p_edges;
}

Edge* Polygon::get_edges()
{
	return this->p_edges;
}

Edge* Polygon::get_edge(unsigned int idx)
{
	return &this->p_edges[idx];
}

unsigned int Polygon::get_nof_edges()
{
	return this->nof_edges_added;
}

unsigned int Polygon::get_max_nof_edges()
{
	return this->max_nof_edges;
}

void Polygon::add_edge(int x1, int y1, int x2, int y2, unsigned int edge_index)
{
	Edge* p_target_edge;
	Point<int>*  point;

	if(edge_index > this->max_nof_edges)
	{
		return;
	}else
	{
		p_target_edge = &this->p_edges[edge_index];
		point = p_target_edge->getP1();
		point->setX(x1);
		point->setY(y1);
		point = p_target_edge->getP2();
		point->setX(x2);
		point->setY(y2);
		this->nof_edges_added++;
	}
}

// use memcpy to support quick resizes : size change of 1 == 1 iteration, no matter the current size
void Polygon::init_edge_array(unsigned int nof_desired_edges)
{
	Edge* p_new;
	unsigned int nof_edges_to_copy;
	unsigned int i;
	unsigned int diff;

	if(nof_desired_edges == 0)
	{
		return;
	}
	else if (this->p_edges == NULL)
	{
		// Use malloc instead of new. See reason in the else, facilitating dynamics
		this->p_edges = (Edge*)malloc(sizeof(Edge)*nof_desired_edges);
		for (i=0; i < nof_desired_edges; i++)
		{
			this->p_edges[i].init();
		}
	}
	else if (this->max_nof_edges == nof_desired_edges )
	{
		return;
	}
	/* Increase/decrease the size, copy whatever is possible to the newly created array */
	else
	{
		p_new = (Edge*)malloc(sizeof(Edge)*nof_desired_edges);
		// Copy the desired number of edges if it fits in the current size, otherwise copy only the number of edges possible
		nof_edges_to_copy = (this->max_nof_edges > nof_desired_edges) ? nof_desired_edges : this->max_nof_edges;
		memcpy(p_new, this->p_edges, sizeof(Edge)*nof_edges_to_copy);
		for(i=0; i < nof_edges_to_copy; i++)
		{
			this->p_edges[i].setP1(NULL);
			this->p_edges[i].setP2(NULL);
		}
		if(nof_desired_edges > this->max_nof_edges)
		{
			diff = nof_desired_edges - this->max_nof_edges;
			for (i=0; i < diff; i++)
			{
				p_new[this->max_nof_edges+i].init();
			}
		}
		free(this->p_edges);
		this->p_edges = p_new;
		if(nof_edges_to_copy < this->nof_edges_added) this->nof_edges_added = nof_edges_to_copy;

		this->copied = true;
	}
	// If this function is called externally (e.g. when the user wants to reshape the polygon) the max_nof_edges needs
	this->max_nof_edges = nof_desired_edges;
}

Polygon* Polygon::intersect(Polygon* p_clip)
{
	unsigned int nof_points_subject_polygon;
	unsigned int nof_points_clip_polygon;
	unsigned int nof_points_input_list;
	unsigned int nof_points_in_output_polygon;
	unsigned int max_nof_points_input_list;
	unsigned int clip_polygon_point_idx;
	unsigned int subject_polygon_point_idx;
	bool subject_vertex_inside;
	bool input_list_previous_vertex_inside;

	Point<int>* p_clip_polygon_previous_point;
	Point<int>* p_input_list_previous_point;
	Point<int>* p_intersection_point;

	Edge clip_boundary_edge;

	nof_points_subject_polygon = this->get_nof_points();
	nof_points_clip_polygon = p_clip->get_nof_points();

	// The number of points in the output polygon, which is constructed while the algorithm runs, cannot exceed the maximum number of vertices
	max_nof_points_input_list = (nof_points_subject_polygon >= nof_points_clip_polygon) ? nof_points_subject_polygon : nof_points_clip_polygon;

	Point<int>* pp_point_subject_polygon[nof_points_subject_polygon];
	Point<int>* pp_point_clip_polygon[nof_points_clip_polygon];
	Point<int>* pp_input_list_polygon[max_nof_points_input_list];
	Point<int>* pp_output_polygon[max_nof_points_input_list];

	polygon_util::set_polygon_point_array(this, pp_point_subject_polygon);
	polygon_util::set_polygon_point_array(p_clip, pp_point_clip_polygon);

	polygon_util::set_polygon_point_array(this, pp_output_polygon);
	nof_points_in_output_polygon = max_nof_points_input_list;

	p_clip_polygon_previous_point = pp_point_clip_polygon[nof_points_clip_polygon-1];

	for(clip_polygon_point_idx = 0; clip_polygon_point_idx < nof_points_clip_polygon; clip_polygon_point_idx++)
	{
		// Construct a clip boundary based on the clip polygon point and the previous point
		clip_boundary_edge.setP1(pp_point_clip_polygon[clip_polygon_point_idx]);
		clip_boundary_edge.setP2(p_clip_polygon_previous_point);

		// Copy clipped_polygon to the input_list
		polygon_util::copy_point_array(pp_input_list_polygon, pp_output_polygon, nof_points_in_output_polygon);

		nof_points_input_list = nof_points_in_output_polygon;

		polygon_util::empty_point_array(pp_output_polygon, nof_points_in_output_polygon);
		nof_points_in_output_polygon = 0;

		if (nof_points_input_list > 0)
		{
			p_input_list_previous_point = pp_input_list_polygon[nof_points_input_list-1];
		}

		// Iterate over each subject polygon point
		for(subject_polygon_point_idx = 0; subject_polygon_point_idx < nof_points_input_list; subject_polygon_point_idx++)
		{
			// Check if the subject point is inside
			bool subject_vertex_inside 				= point_util::point_inside_boundary(pp_input_list_polygon[subject_polygon_point_idx], clip_boundary_edge.getP1(), clip_boundary_edge.getP2());
			// Check if the previous point in the input list (current output polygon)
			bool input_list_previous_vertex_inside 	= point_util::point_inside_boundary(p_input_list_previous_point, clip_boundary_edge.getP1(), clip_boundary_edge.getP2());

			// If the subject point is inside, add the input list point (output polygon) to the output list (empty at each clip polygon for loop)
			if(subject_vertex_inside == true)
			{
				// If the previous vertex is not inside, calculate the intersection of the current edge of the output polygon with the clip boundary
				if(input_list_previous_vertex_inside == false)
				{
					Point<int>* p = polygon_util::perform_subject_clip_polygon_edge_intersection(pp_input_list_polygon[subject_polygon_point_idx], p_input_list_previous_point, &clip_boundary_edge);
					pp_output_polygon[nof_points_in_output_polygon] = p;
					nof_points_in_output_polygon++;
				}

				pp_output_polygon[nof_points_in_output_polygon] = pp_input_list_polygon[subject_polygon_point_idx];
				nof_points_in_output_polygon++;
			}
			else if (input_list_previous_vertex_inside == true)
			{
				Point<int>* p = polygon_util::perform_subject_clip_polygon_edge_intersection(pp_input_list_polygon[subject_polygon_point_idx], p_input_list_previous_point, &clip_boundary_edge);
				pp_output_polygon[nof_points_in_output_polygon] = p;
				nof_points_in_output_polygon++;
			}
			// Prepare next iteration
			p_input_list_previous_point = pp_input_list_polygon[subject_polygon_point_idx];
			p_clip_polygon_previous_point = pp_point_clip_polygon[clip_polygon_point_idx];
		}
	}

	// Connect first and last point to close the polygon
	pp_output_polygon[nof_points_in_output_polygon] = pp_output_polygon[nof_points_in_output_polygon-1];
	nof_points_in_output_polygon++;
	pp_output_polygon[nof_points_in_output_polygon] = pp_output_polygon[0];
	nof_points_in_output_polygon++;

	// Create a new polygon instance based on the output polygon array and return it
	return new Polygon(pp_output_polygon, nof_points_in_output_polygon);
}

void Polygon::set_nof_edges(unsigned int nof_edges)
{
	this->nof_edges_added = nof_edges;
}

unsigned int Polygon::get_nof_points()
{
	return this->get_nof_edges()*2;
}

Polygon* Polygon::clone()
{
	unsigned int i;
	Edge* p_edges_clone;
	Edge* p_edge_clone;
	Edge* p_edge_org;
	Polygon* p_clone = new Polygon(this->max_nof_edges);
	p_edges_clone = p_clone->get_edges();

	for (i=0; i<p_clone->get_max_nof_edges(); i++)
	{
		p_edge_clone = &p_edges_clone[i];
		p_edge_org = this->get_edge(i);
		p_edge_clone->setP1(this->get_edge(i)->getP1()->clone());
		p_edge_clone->setP2(this->get_edge(i)->getP2()->clone());
	}
	p_clone->set_nof_edges(this->nof_edges_added);
	return p_clone;
}