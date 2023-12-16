#ifndef ARCH_H
#define ARCH_H

#include <iostream>
#include <ctime>
#include <random>
#include <map>

#include "types.h"
#include "graph.h"
/* 
 *            -1   -1   -1  0   -1   -1  16  -1
<1, 1>  ->  {nop, nop, nop, 0, nop, nop, 16, nop};
*/
using proc_list_w_op = std::map<vi, vi>;
using arch = std::pair<proc_list_w_op, std::vector<vvi>>;

vvi     generate_random_F(int m);
void    print_F(vvi F);
vvi     translate_to_coords(vvi F, vertex_list vl);
vi      translate_to_time(vertex_list vl);
void    print_arch(vvi tran_coords, vi tran_time);
proc_list_w_op    collapse_list_to_arch(vvi tran_coords, vi tran_time);
std::vector<vvi>     generate_connections(proc_list_w_op p_op, edge_list el);


/* prz. z listy wezlow na czas (vertex_list, macierz) -> para operacja czas? */
/* "przetlumacz" z listy wezlow na wsp. w macierzy proc(vertex_list, macierz) -> lista proc. */

#endif
