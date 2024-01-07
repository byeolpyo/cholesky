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
using proc_list_w_op    = std::map<vi, vi>;
using proc_conn         = std::vector<vvi>;       
using arch              = std::pair<proc_list_w_op, std::vector<vvi>>;

vvi     generate_random_F(int m);
void    print_F(vvi F);
vvi     translate_to_coords(vvi F, vertex_list vl);
vi      schedule(graph g, vvi coords);
vi      translate_to_time(vertex_list vl);
void    print_op_list(proc_list_w_op p_op);
void    print_conn(proc_conn p_c);
void    print_arch(arch a);
proc_list_w_op    collapse_list_to_arch(vvi tran_coords, vi tran_time);
proc_conn     generate_connections(proc_list_w_op p_op, edge_list el);
arch    generate_arch(graph g, vvi F);


/* prz. z listy wezlow na czas (vertex_list, macierz) -> para operacja czas? */
/* "przetlumacz" z listy wezlow na wsp. w macierzy proc(vertex_list, macierz) -> lista proc. */

#endif
