#include "arch.h"

static bool seed_initialized = false;

static vvi matmul(vvi a, vvi b) {
    vvi res;
    for(int i = 0; i < a.size(); i++) {
        vi tmp_row;
        for(int j = 0; j < b[0].size(); j++) {
            int tmp_val = 0;
            for(int k = 0; k < b.size(); k++) {
                tmp_val += a[i][k] * b[k][j];
            }
            tmp_row.push_back(tmp_val);

        }
        res.push_back(tmp_row);
    }
    return res;
}

static vvi matmul_t(vvi a, vvi b) {
    vvi res;
    for(int i = 0; i < a.size(); i++) {
        vi tmp_row;
        for(int j = 0; j < b.size(); j++) {
            int tmp_val = 0;
            for(int k = 0; k < b[0].size(); k++) {
                tmp_val += a[i][k] * b[j][k];
            }
            tmp_row.push_back(tmp_val);

        }
        res.push_back(tmp_row);
    }
    return res;
}

static vi matmul_v_t(vvi a, vi b) {
    vi res;
    for(int i = 0; i < a.size(); i++) {
        int tmp_val = 0;
        for(int k = 0; k < b.size(); k++) {
            tmp_val += a[i][k] * b[k];
        }
        res.push_back(tmp_val);    
    }
    return res;
}


vvi generate_random_F(int m) {
    if(!seed_initialized) {
        std::srand(std::time(nullptr));
        seed_initialized = true;
    }

    vvi F;
    for(int i = 0 ; i < m; i++) {
        vi tmp;
        for(int j = 0; j < 3; j++) {
            int random = (std::rand()%3)-1;
            tmp.push_back(random);
        }
        F.push_back(tmp);
    }
    
    /* D in this case is the identity matrix so you never have to check */

    return F;
}

void print_F(vvi F) {
    for(auto r : F) {
        for(auto x : r) {
            std::cout << x << "\t";
        }
        std::cout << std::endl;
    }
}

vvi translate_to_coords(vvi F, vertex_list vl) {
    vvi res;
    for(auto ver : vl) {
        vi translated_coord = matmul_v_t(F, ver.first); 
        res.push_back(translated_coord);
    }
    return res;
}

/* TODO greedy scheduling 
 * search over the dag
 * assign cycles greedily
 *      if(incoming vertices are assigned) {
 *          assign (max of incoming) + 1
 *      }
 *      else wait?
 *
 *
 * otherwise -> color the graph
 * */


static void print_vi(vi v) {
    for(auto x : v) {
        std::cout << x << " ";
    } 
}

/* TODO faster! */
vi schedule(graph g, vvi coords) {
    std::map<std::pair<vi, int>, int> sch_map;
    vertex_list vl = g.first;
    edge_list el = g.second;
    vi sch(vl.size());

    for(int i = 0; i < vl.size(); i++) {
        
        for(auto e : el) {
            if(e.first == i) {
                sch[e.second] = std::max(sch[e.second], sch[i]+1);
                auto my_pair = std::pair<vi, int>{coords[e.second], sch[e.second]};
                auto it = sch_map.find(my_pair);
                if(it != sch_map.end()) {
                    if(sch_map[my_pair] != e.second)
                        sch[e.second] += 1;
                }
                sch_map.insert({{coords[e.second], sch[e.second]}, e.second});
            }
        }
    }
    
    return sch;
}
vi translate_to_time(vertex_list vl) {
    vi res;
    for(auto ver : vl) {
        int transl = 0;
        for(auto x : ver.first) {
            transl += x * 1;
        }
        res.push_back(transl);
    }
    return res;
}
/*
void print_arch(vvi tran_coords, vi tran_time) {
    std::cout << "coords\t\tstep\n";
    for(int i = 0; i < tran_time.size(); i++) {
        for(auto x : tran_coords[i]) {
            std::cout << x << " ";
        }
        std::cout << "\t\t" << tran_time[i] << std::endl;
    }
}
*/

/* 24 takty na wszystkie operacje
 * 320 mhz 
 *
 *
 * */

/* TODO change representation 
 * instead of
 * EP -> - - - - - 1 - - - - 56 - - - 100
 *
 * do this:
 *
 * EP -> 1 (cycle 5), 56 (cycle 9), 100 (cycle 13)
 * */

proc_list_w_op collapse_list_to_arch(vvi tran_coords, vi tran_time) {
    proc_list_w_op res;

    int max_step = *std::max_element(tran_time.begin(), tran_time.end());
    max_step += 1;

    for(auto c : tran_coords) {
        vi instructions(max_step, -1);
        res.insert({c, instructions});
    }
    
    for(int i = 0; i < tran_coords.size(); i++) {
        res[tran_coords[i]][tran_time[i]] = i;
    }
    return res;
}

/* TODO faster? */
proc_conn generate_connections(proc_list_w_op p_op, edge_list el) {
    proc_conn res;
    proc_list_w_op::iterator it1 = p_op.begin();
    while(it1 != p_op.end()) {
        auto it2 = p_op.begin();
        while(it2 != p_op.end()) {
            if(it1 == it2) {
                it2++;
                continue;
            };
            for(auto edg : el) {
                vi proc1 = it1->second;
                vi proc1_coords = it1->first;
                vi proc2 = it2->second;
                vi proc2_coords = it2->first;
                int a = edg.first; 
                int b = edg.second; 
                auto f1 = std::find(proc1.begin(), proc1.end(), a);
                auto f2 = std::find(proc2.begin(), proc2.end(), b);
               
                if(f1 != proc1.end() && f2 != proc2.end()) {
                    res.push_back({proc1_coords, proc2_coords});
                    break;
                } 
                std::find(proc1.begin(), proc1.end(), b);
                std::find(proc2.begin(), proc2.end(), a);
                
                if(f1 != proc1.end() && f2 != proc2.end()) {
                    res.push_back({proc2_coords, proc1_coords});
                    break;
                } 
            }
            it2++;
        }
        it1++;
    }
    return res;
}

void print_op_list(proc_list_w_op p_op) {
    for(auto i : p_op) {
        for(auto x : i.first) {
            std::cout << x << " ";
        }
        
        std::cout << " -> ";
        for(auto x : i.second) {
            if(x == -1) {
                std::cout << "- ";
            }
            else {
                std::cout << x << " ";
            }
        }
        std::cout << std::endl;
    }

    std::cout << "Liczba EP - " << p_op.size() << std::endl;
    std::cout << "Liczba taktow - " <<(*(p_op.begin())).second.size() << std::endl;
}

float avg_arch_load(arch a, int l_op) {
    auto p = a.first;
    int l_ep = p.size();
    int T = (*(p.begin())).second.size();
    return ((float)l_op)/((float)T*(float)l_ep)*100.0;
}

int get_tick(arch a) {
    return (*(a.first.begin())).second.size();
}

int get_ep(arch a) {
    return a.first.size();
}

void print_conn(proc_conn p_c) {
    for(auto p : p_c) {
        for(auto i : p ) {
            for(auto x : i) {
                std::cout << x << " ";
            }
            std::cout << "\t";
        }
        std::cout << std::endl;
    }
}

void print_arch(arch a) {
    print_op_list(a.first);
    std::cout << std::endl;
    print_conn(a.second);
}

arch generate_arch(graph g, vvi F) {
    auto t_s = translate_to_coords(F, g.first);
    auto t_t = schedule(g, t_s);

    //auto t_t = translate_to_time(g.first);
    proc_list_w_op p_op = collapse_list_to_arch(t_s, t_t);
    proc_conn p_c = generate_connections(p_op, g.second);
    return {p_op, p_c};
}
