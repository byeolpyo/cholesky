#ifndef TABLE_H
#define TABLE_H

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <tuple>

#include "types.h"

/*                        record
 *          ____________|   |   |_____________    
 *         /                |                 \
 *        /                 |                  \
 *       /             indexes_list             \
 *      /             /     |      \             \
 *  coord        indexes indexes indexes       op_type
 */ 

using coord         = vi;
using indexes       = vi;
using op_type       = std::string;

using indexes_list  = std::vector<indexes>;
using record        = std::tuple<coord, indexes_list, op_type>;
using table         = std::vector<record>;

table   generate_table(int n);
void    print_table(table t);

#endif
