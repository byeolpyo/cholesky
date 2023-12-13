#include "compute.h"

#define RAND_A -10
#define RAND_B 10

bool seed_initialized = false;

static int rand_range() {
    return (RAND_A)+std::rand()%((RAND_B)-(RAND_A));
}

vvf cholesky(vvf a, int n) {
    
    for(int i = 0; i < n; i++) {
       
        a[i][i] = sqrt(a[i][i]);
        
        for(int j = i+1; j < n; j++) {
            a[j][i] = a[j][i]/a[i][i];
        }

        for(int j = i+1; j < n; j++) {
            for(int k = i+1; k <= j; k++) {
                a[j][k] = a[j][k] - a[j][i]*a[k][i];
            }
        }
    }

    vvf l(n, vf(n));
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            if(i >= j) {
                l[i][j] = a[i][j];
            }
        }
    }
    return l;
}

void cholesky_benchmark(int rank, int rep_per_rank) {
    for(int n = 2; n <= rank; n++) {
        for(int i = 0; i < rep_per_rank; i++) {
            vvf a = random_spd_matrix(n); 
            auto start = std::chrono::high_resolution_clock::now(); 
            vvf l = cholesky(a, n);
            auto stop = std::chrono::high_resolution_clock::now(); 
            auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
            std::cout << duration.count() << " ";
        }
        std::cout << std::endl;
    }
}

void cholesky_test() {
    vvf a = random_spd_matrix(3); 
    std::cout << "Input matrix A:\n";
    print_matrix(a);
    vvf l = cholesky(a, 3);
    
    std::cout << "Output matrix L:\n";
    print_matrix(l);

    vvf lt = inverse(l, 3); 
    vvf l_times_lt = matmul_nxn(l, lt, 3);

    std::cout << "Result of matmul L*Lt:\n";
    print_matrix(l_times_lt);
}

vvf inverse(vvf a, int n) { 
    vvf res(n, vf(n));
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            res[i][j] = a[j][i];
        }
    }
    return res;
}

vvf matmul_nxn(vvf a, vvf b, int n) {
    vvf res(n, vf(n));
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            for(int k = 0; k < n; k++) {
                res[i][j] += a[i][k] * b[k][j];
            }
        }
    }
    return res; 
}


/* source: https://stackoverflow.com/questions/48736724/generate-matrix-symmetric-and-positive-definite */

vvf random_spd_matrix(int n) {  
    if(!seed_initialized) {
        std::srand(std::time(nullptr));
        seed_initialized = true;
    }
    
    vvf res; 
    for(int i = 0; i < n; i++) {
        vf row(n); 
        std::generate(row.begin(), row.end(), rand_range);
        res.push_back(row);
    } 
    
    vvf res_inv = inverse(res, n);
    res = matmul_nxn(res, res_inv, n);

    return res;
}

void print_matrix(vvf a) {
    for(auto r : a ) {
        for(auto x : r) {
            std::cout << std::fixed << std::setprecision(5) << x << "  \t";
        }
        std::cout << std::endl;
    }
}
