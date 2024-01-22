#include "arch.h"

static bool seed_initialized = false;

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

static void print_vi(vi v) {
    for(auto x : v) {
        std::cout << x << " ";
    } 
}

vi schedule(graph g, vvi coords) {
    std::map<std::pair<vi, int>, int> sch_map;
    vertex_list vl = g.first;
    edge_list el = g.second;
    vi sch(vl.size());

    std::sort(el.begin(), el.end());

    for(auto e : el) {
        sch[e.second] = std::max(sch[e.second], sch[e.first]+1);
        auto my_pair = std::pair<vi, int>{coords[e.second], sch[e.second]};
        auto it = sch_map.find(my_pair);
        if(it != sch_map.end()) {
            if(sch_map[my_pair] != e.second)
                sch[e.second] += 1;
        }
        sch_map.insert({{coords[e.second], sch[e.second]}, e.second});
    }

    return sch;
}


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

proc_conn generate_connections(vvi coords, edge_list el) {
    proc_conn res;
    
    for(auto e : el) {
        vvi c = {coords[e.first], coords[e.second]};
        res.insert(c);
    } 
    return res;
}

void print_parameters(proc_list_w_op p_op) {
    std::cout << "Liczba EP - " << p_op.size() << std::endl;
    std::cout << "Liczba taktow - " <<(*(p_op.begin())).second.size() << std::endl;
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
//    print_parameters(a.first);
    print_conn(a.second);
}

arch generate_arch(graph g, vvi F) {
    auto t_s = translate_to_coords(F, g.first);
    auto t_t = schedule(g, t_s);

    proc_list_w_op p_op = collapse_list_to_arch(t_s, t_t);
    proc_conn p_c = generate_connections(t_s, g.second);
    return {p_op, p_c};
}
