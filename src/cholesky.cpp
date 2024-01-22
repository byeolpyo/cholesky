#include "types.h"
#include "compute.h"
#include "table.h"
#include "graph.h"
#include "arch.h"

int main(int argc, char* argv[]) {
    
    int nmin = 4;
    int nmax = 4;
   

    vvi f1 = {
        {-1, -1, 0},
        {1, -1, 0}
    };
    vvi f2 = {
        {-1, 0, 1},
        {1, 1, 0}
    };
    
    vvi f3 = {
        {1, 1, -1}
    };
        
    for(int N = 2; N <= nmax; N+=1) {

        table t = generate_table(N);
        graph g = generate_dag(t);
        
        print_table(t);
        
        auto a1 = generate_arch(g, f1); 
        auto a2 = generate_arch(g, f2);
        auto a3 = generate_arch(g, f3);

        std::cout << std::endl;
        print_vertex_list(g.first);
        std::cout << std::endl;
        print_edge_list(g.second);
       
        std::cout << "Liczba wezlow - " << g.first.size() << std::endl;
 
        std::cout << std::endl;
        std::cout << "Architektura 1:" << std::endl;
        print_F(f1);
        std::cout << std::endl;
        print_arch(a1);
        print_parameters(a1.first);
        std::cout << std::endl;
        std::cout << "P[%] = " << avg_arch_load(a1, g.first.size()) << std::endl;
        std::cout << "czas wykonania (s) " << (56*N-28+get_tick(a1))/(320000000.0) << std::endl;

        std::cout << "Architektura 2:" << std::endl;
        print_F(f2);
        std::cout << std::endl;
        print_arch(a2);
        print_parameters(a2.first);
        std::cout << std::endl;
        std::cout << "P[%] = " << avg_arch_load(a2, g.first.size()) << std::endl;
        std::cout << "czas wykonania (s) " << (56*N-28+get_tick(a2))/(320000000.0) << std::endl;
        
        std::cout << "Architektura 3:" << std::endl;
        print_F(f3);
        std::cout << std::endl;
        print_arch(a3);
        print_parameters(a3.first);
        std::cout << std::endl;
        std::cout << "P[%] = " << avg_arch_load(a3, g.first.size()) << std::endl;
        std::cout << "czas wykonania (s) " << (get_ep(a3)+get_tick(a3))/(320000000.0) << std::endl;
    } 

    return 0;
}
