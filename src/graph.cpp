#include "graph.h"

graph generate_dag(table t) {
    edge_list a;
    graph g = {generate_vertex_list(t), generate_edge_list(t)};
    return g;
}

/* TODO faster */
edge_list generate_edge_list(table t) {
    edge_list res;

    int columns = std::get<1>(t[0]).size();
    int rows = t.size();

    indexes empty_indexes = {0, 0};

    for(int c = 0; c < columns; c++) {
        std::set<indexes> ix_value_set;

        for(auto x : t) {
            indexes_list tmp_il = std::get<1>(x);
            indexes tmp_ix = tmp_il[c]; 
            if(tmp_ix != empty_indexes) {
                ix_value_set.insert(tmp_ix);
            }
        }
        
        for(auto ix_value : ix_value_set) { 
            int i = 0;
            indexes tmpppppp = empty_indexes;
            
            for(i = 0; i < rows; i++) {
                indexes_list tmp_il = std::get<1>(t[i]);
                tmpppppp = tmp_il[c];
                if(tmpppppp == ix_value) {
                    break;
                }
            }

            int j = 1; 

            while(i+j < rows) {
                indexes_list tmp_il = std::get<1>(t[i+j]);
                indexes tmp_ix = tmp_il[c]; 
                if(tmp_ix != ix_value) {
                    j++;
                    continue;
                } 
                if(tmp_ix == ix_value) {
                    res.push_back({i, i+j});
                }
                i += j;
                j = 1;
            }

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
