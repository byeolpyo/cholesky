#include "types.h"
#include "compute.h"
#include "table.h"
#include "graph.h"
#include "arch.h"

int main(int argc, char* argv[]) {
    
    table t = generate_table(4);
    /*
    print_table(t);
    std::cout << std::endl;
    */
    graph g = generate_dag(t);
//    print_vertex_list(g.first); 
    
//    print_edge_list(g.second); 
   
    auto f1 = generate_random_F(2);
    auto f2 = generate_random_F(2);
    auto f3 = generate_random_F(1);
    
    auto a1 = generate_arch(g, f1);
    auto a2 = generate_arch(g, f2);
    auto a3 = generate_arch(g, f3);
    
    std::cout << "Architektura 1:" << std::endl;
    print_F(f1);
    std::cout << std::endl;
    print_arch(a1);
    std::cout << std::endl;

    std::cout << "Architektura 2:" << std::endl;
    print_F(f2);
    std::cout << std::endl;
    print_arch(a2);
    std::cout << std::endl;

    std::cout << "Architektura 3:" << std::endl;
    print_F(f3);
    std::cout << std::endl;
    print_arch(a3);
    std::cout << std::endl;


    /*
    std::cout << std::endl;
    print_F(f2);
    std::cout << std::endl;
    print_F(f3);
    */
    return 0;
}
