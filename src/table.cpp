#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <tuple>

#include "types.h"
#include "table.h"

table generate_table(int n) { 
    /* 
     * INSTRUKCJA 1 a[i][i] = sqrt(a[i][i]); 
     */

    table t; 
    indexes empty_indexes = {0, 0};

    for(int i = 0; i < n; i++) {
        for(int j = i; j<=i; j++) {
            for(int k = j; k <= j; k++) {
                
                coord           tmp_ws{i+1, j+1, k+1};
                indexes         tmp_ix{i+1, i+1};
                indexes_list    tmp_gr{tmp_ix, empty_indexes, tmp_ix, empty_indexes};
                record          tmp_rk{tmp_ws, tmp_gr, "sqrt"};
                
                t.push_back(tmp_rk);
            }
        }
    }

    /*
     * INSTRUKCJA 2 a[j][i] = a[j][i]/a[i][i]; 
     */
   
    for(int i = 0; i < n; i++) {
        for(int j = i+1; j<n; j++) {
            for(int k = i; k <= i; k++) {
                 coord         tmp_ws{i+1, j+1, k+1};
                 indexes       tmp_ix1{i+1, i+1};
                 indexes       tmp_ix2{j+1, i+1};
                 indexes_list  tmp_gr{tmp_ix1, tmp_ix2, empty_indexes, empty_indexes};
                 record        tmp_rk{tmp_ws, tmp_gr, "div"};
                 t.push_back(tmp_rk);
            }
        }
    }
    
    /*
     * INTSTRUKCJA 3 a[j][k] = a[j][k] - a[j][i]*a[k][i];
     */ 
    
    for(int i = 0; i < n; i++) {
        for(int j = i+1; j<n; j++) {
            for(int k = i+1; k <= j; k++) {
                coord         tmp_ws{i+1, j+1, k+1};
                indexes       tmp_ix1{j+1, i+1};
                indexes       tmp_ix2{j+1, k+1};
                indexes       tmp_ix3{k+1, i+1};
                
                indexes_list  tmp_gr{empty_indexes, tmp_ix1, tmp_ix2, tmp_ix3};

                record        tmp_rk{tmp_ws, tmp_gr, "sub-mul"};
                t.push_back(tmp_rk);
            }
        }
    }

    sort(t.begin(), t.end());

    return t;
}

void print_table(table t) {
    std::cout << "id\ti j k\ta(i,i)\ta(j,i)\ta(j,k)\ta(k,i)\toptype\n";
    int i = 0;
    for(auto x : t) {
        std::cout << i++ << "\t";
        for(auto wsp : std::get<0>(x)) {
            std::cout << wsp << " ";
        }
        std::cout << "\b\t  ";
        for(auto g_r : std::get<1>(x)) {
            for(auto ind : g_r) {
                if(ind != 0)
                    std::cout << ind << " ";
            }
            std::cout << "\t  ";
        }
        std::cout << "\b\b";
        std::cout << std::get<2>(x);
        std::cout << "\n";
    }
}

