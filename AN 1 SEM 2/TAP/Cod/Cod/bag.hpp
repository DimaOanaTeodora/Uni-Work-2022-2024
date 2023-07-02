/*Pennant and Bag data structures
@author: G. Ducoffe
*/

#ifndef __PENNANT_AND_BAG__
#define __PENNANT_AND_BAG__

#include<vector>
#include<list>
using namespace std;

struct pennant 
{
	unsigned int _value;
	pennant *left, *right;
	~pennant();
};

pennant *pennant_union(pennant*,pennant*);
pennant *pennant_split(pennant*);

struct bag {
	vector<pennant*> _S;
	unsigned int _sz;
	bag();
	list<unsigned int> to_list(void) const; //an iterator would be more appropriate
};

bool bag_is_empty(const bag&);
unsigned int bag_size(const bag&);
void bag_insert(bag&,unsigned int);
bag bag_union(bag&,bag&);
bag bag_split(bag&);

#endif
