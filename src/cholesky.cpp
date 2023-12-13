#include "types.h"
#include "compute.h"
#include "table.h"
#include "graph.h"

int main(int argc, char* argv[]) {
    table t = generate_table(4);
    print_table(t);
    std::cout << std::endl;
    
    graph g = generate_dag(t);
    
    print_vertex_list(g.first); 
    std::cout << std::endl;
    print_edge_list(g.second); 

    return 0;
}
