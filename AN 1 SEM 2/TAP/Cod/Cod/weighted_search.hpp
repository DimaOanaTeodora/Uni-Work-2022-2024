/*Graph searches for weighted graphs
--> Dijkstra, A*, B
@author: G. Ducoffe
*/

#ifndef __WEIGHTED_SEARCH__
#define __WEIGHTED_SEARCH__

#include "graphs.hpp"
#include <unordered_map>
#include <unordered_set>
#include <functional>
using namespace std;

struct search_output {
	
	unordered_map<unsigned int, double> _dist; //distances from the source
	unordered_map<unsigned int, unsigned int> _tree; //pairs (child, parent)
	
};

search_output dijkstra_search(unsigned int,const Graph&);
search_output a_star_search(unsigned int,const unordered_set<unsigned int>&,const Graph&,function<double(unsigned int)>);
search_output b_search(unsigned int,const unordered_set<unsigned int>&,const Graph&,function<double(unsigned int)>);

#endif
