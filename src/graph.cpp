#include "graph.h"
#include <vector>
#include <map>

graph generate_dag(table t) {
    graph g = {generate_vertex_list(t), generate_edge_list(t)};
    return g;
}

/* this is my beloved O(n) child
 * trades O(n^2) time and O(1) space to O(n) time and O(n) space 
 * you can do O(n) and O(1) time by using a queue
 *
 * if you decided to do that email starforgeml@gmail.com lets talk
 */
edge_list generate_edge_list(table t) {
    edge_list res;
    indexes empty_indexes = {0, 0};

    std::map<indexes, std::set<int>> res_map;

    for(int i = 0; i < t.size(); i++) {
        indexes_list r_ix = std::get<1>(t[i]);
        for(auto x : r_ix) {
            if(x != empty_indexes) {
                res_map[x].insert(i);    
            }
        }
    }

    for(auto m : res_map) {
        vi paths;
        for(auto s : m.second) {
            paths.push_back(s);
        }
        for(int i = 0; i < paths.size()-1; i++) {
            res.push_back({paths[i], paths[i+1]});
        }
    }

    return res;
}

vertex_list generate_vertex_list(table t) {
    vertex_list res;
    for(auto rec : t) {
        res.push_back({std::get<0>(rec), std::get<2>(rec)});
    } 
    
    return res;
}

void print_edge_list(edge_list el) {
    std::cout << "src id\tdst id" << std::endl;
    for(auto x : el) {
        std::cout << x.first << "\t" << x.second << std::endl;
    }
}

void print_vertex_list(vertex_list vl) {
    std::cout << "id\ti j k\t" << "optype" << std::endl;
    int i = 0;
    for(auto x : vl) {
        std::cout << i << "\t";
        for(auto z : x.first) {
            std::cout << z << " ";
        }
        std::cout << "\t" << x.second << std::endl;
        i++;
    }
}
