/*Graph searches for unweighted graphs
--> DFS, (Lex)BFS
@author: G. Ducoffe
*/

#ifndef __SEARCH__
#define __SEARCH__

#include "graphs.hpp"

list<unsigned int> dfs(unsigned int,const Graph&);
list<unsigned int> bfs(unsigned int,const Graph&);
list<unsigned int> lexbfs(unsigned int,const Graph&);

#endif
