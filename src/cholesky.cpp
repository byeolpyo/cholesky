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
    print_vertex_list(g.first); 
    
    std::cout << std::endl;
    print_edge_list(g.second); 
   
    auto f1 = generate_random_F(2);
    auto f2 = generate_random_F(2);
    auto f3 = generate_random_F(1);
    //print_F(f1);
    /*
    std::cout << std::endl;
    print_F(f2);
    std::cout << std::endl;
    print_F(f3);
    */

    auto t1_s = translate_to_coords(f1, g.first);
    auto t1_t = translate_to_time(g.first);
    //print_arch(t1_s, t1_t);
    /*
    print_F(t1_s);
    for(auto x : t1_t) {
        std::cout << x << "\n";
    }
    */
    proc_list_w_op p_op = collapse_list_to_arch(t1_s, t1_t);
    generate_connections(p_op, g.second);
    return 0;
}
