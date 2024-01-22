#ifndef ARCH_H
#define ARCH_H

#include <iostream>
#include <ctime>
#include <random>
#include <map>

#include "types.h"
#include "graph.h"

using proc_list_w_op    = std::map<vi, vi>;
using proc_conn         = std::set<vvi>;       
using arch              = std::pair<proc_list_w_op, std::set<vvi>>;

vvi             generate_random_F(int m);
void            print_F(vvi F);
vvi             translate_to_coords(vvi F, vertex_list vl);
vi              schedule(graph g, vvi coords);
vi              translate_to_time(vertex_list vl);
void            print_parameters(proc_list_w_op p_op);
void            print_op_list(proc_list_w_op p_op);
void            print_conn(proc_conn p_c);
void            print_arch(arch a);
float           avg_arch_load(arch a, int l_op);
int             get_tick(arch a);
int             get_ep(arch a);
proc_list_w_op  collapse_list_to_arch(vvi tran_coords, vi tran_time);
proc_conn       generate_connections(vvi coords, edge_list el);
arch            generate_arch(graph g, vvi F);

#endif
