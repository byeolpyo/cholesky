#include "types.h"
#include "compute.h"
#include "table.h"
#include "graph.h"
#include "arch.h"

int main(int argc, char* argv[]) {
    
    int nmax = 100;
   

    vvi f1 = {
        {-1, -1, 0},
        {1, -1, 0}
    };
    vvi f2 = {
        {1, 0, 1},
        {-1, 1, 0}
    };
    
    vvi f3 = {
        {1, 1, -1}
    };
        
   

    /*
    vi wezl[3];
    vi ep[3];
    vi takty[3];
    vf p[3];
    vf czas[3];
    */
    for(int N = nmax-1; N < nmax; N++) {

        table t = generate_table(N);
        
        //print_table(t);
        std::cout << std::endl;
        graph g = generate_dag(t);
        auto a1 = generate_arch(g, f1);
        auto a2 = generate_arch(g, f2);
        auto a3 = generate_arch(g, f3);
        /*
        wezl[0].push_back(g.first.size());
        ep[0].push_back(get_ep(a1));
        takty[0].push_back(get_tick(a1));
        p[0].push_back(avg_arch_load(a1, g.first.size()));
        czas[0].push_back((56*N-1+get_tick(a1))/(320000000.0));
        
        wezl[1].push_back(g.first.size());
        ep[1].push_back(get_ep(a2));
        takty[1].push_back(get_tick(a2));
        p[1].push_back(avg_arch_load(a2, g.first.size()));
        czas[1].push_back((56*N-1+get_tick(a2))/(320000000.0));
        
        wezl[2].push_back(g.first.size());
        ep[2].push_back(get_ep(a3));
        takty[2].push_back(get_tick(a3));
        p[2].push_back(avg_arch_load(a3, g.first.size()));
        czas[2].push_back((get_ep(a3)+get_tick(a3))/(320000000.0));
        */
        
        //print_vertex_list(g.first); 
        //print_edge_list(g.second); 
        std::cout << "Liczba wezlow - " << g.first.size() << std::endl;
            
        std::cout << "Architektura 1:" << std::endl;
        print_F(f1);
        std::cout << std::endl;
        //print_arch(a1);
        print_parameters(a1.first);
        std::cout << std::endl;
        std::cout << "P[%] = " << avg_arch_load(a1, g.first.size()) << std::endl;
        std::cout << "czas wykonania (s) " << (56*N-1+get_tick(a1))/(320000000.0) << std::endl;

        std::cout << "Architektura 2:" << std::endl;
        print_F(f2);
        std::cout << std::endl;
        //print_arch(a2);
        print_parameters(a2.first);
        std::cout << std::endl;
        std::cout << "P[%] = " << avg_arch_load(a2, g.first.size()) << std::endl;
        std::cout << "czas wykonania (s) " << (56*N-1+get_tick(a2))/(320000000.0) << std::endl;

        std::cout << "Architektura 3:" << std::endl;
        print_F(f3);
        std::cout << std::endl;
        //print_arch(a3);
        print_parameters(a3.first);
        std::cout << std::endl;
        std::cout << "P[%] = " << avg_arch_load(a3, g.first.size()) << std::endl;
        std::cout << "czas wykonania (s) " << (get_ep(a3)+get_tick(a3))/(320000000.0) << std::endl;
    } 

    /*
    for(int i = 0; i < 3; i++) {
        for(auto x : wezl[i]) {
            std::cout << x << " ";
        }
        std::cout << std::endl;
        for(auto x : ep[i]) {
            std::cout << x << " ";
        }
        std::cout << std::endl;
        for(auto x : takty[i]) {
            std::cout << x << " ";
        }
        std::cout << std::endl;
        for(auto x : p[i]) {
            std::cout << x << " ";
        }
        std::cout << std::endl;
        for(auto x : czas[i]) {
            std::cout << x << " ";
        }
        std::cout << std::endl;
        std::cout << std::endl;
    }

    */
    return 0;
}
