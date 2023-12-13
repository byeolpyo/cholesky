#ifndef COMPUTE_H
#define COMPUTE_H

#include <iostream>
#include <ctime>
#include <vector>
#include <cmath>
#include <chrono>
#include <iomanip>

#include "types.h"
#include "compute.h"

vvf     cholesky(vvf a, int n);
void    cholesky_benchmark(int rank, int rep_per_rank);
void    cholesky_test();
vvf     inverse(vvf a, int n);
vvf     matmul_nxn(vvf a, vvf b, int n);
vvf     random_spd_matrix(int n);
void    print_matrix(vvf a);

#endif
