#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <vector>
#include <set>
#include <tuple>

#include "types.h"
#include "table.h"

using vertex        = std::pair<coord, op_type>;
using vertex_list   = std::vector<vertex>;

using edge          = std::pair<int, int>;    /* referring to id of the vertex in the list, not its coords */
using edge_list     = std::vector<edge>;

using graph         = std::pair<vertex_list, edge_list>;


graph           generate_dag(table t);
edge_list       generate_edge_list(table t);
vertex_list     generate_vertex_list(table t);
void            print_edge_list(edge_list el);
void            print_vertex_list(vertex_list vl);

#endif
