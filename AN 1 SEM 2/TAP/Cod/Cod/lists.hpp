/*Lists of lists -- elements of a list are partitioned in consecutive sublists (groups), whose both ends are stored in a dedicated structure
1) class block_list: generic class with a (rather lengthy) list of some basic group/element operations
2) class partition_refinement: implements the basic partition refinement strategy, and Hopcroft rule for LexDFS.
@author: G. Ducoffe
*/

#ifndef __LISTS__
#define __LISTS__

/*dependencies*/
#include<list>
#include<unordered_map>
#include<unordered_set>
#include<queue>
#include<iterator>
using namespace std;

/*----------------------------------- Block List ------------------------------------------------------------------*/

class block_list {

	private:

	/*intermediate structure*/

	//---------------representation of a group---------------------------/
	struct group{
		unsigned int id;
		unsigned int size;
		list<unsigned int>::iterator first;
		list<unsigned int>::iterator last;

		//constructor for an empty group
		group(unsigned int n) : id(n), size(0) {}
	};
	//-------------------------------------------------------------------/

	//pointers of an element to itself and to its group
	struct node_info {
		list<unsigned int>::iterator _pos; //position in the list
		list<group>::iterator _group; //group containing the element
	};

	/*internal structure*/

	list<unsigned int> elements; //elements, ordered by groups
	unordered_map<unsigned int,node_info> index_elt;

	list<group> groups; //all groups, in order
	unordered_map<unsigned int, list<group>::iterator> index_grp;

	public:

	/*basic operations*/

	inline bool empty(void)	const { return elements.empty(); }
	inline unsigned int size(void) const { return elements.size();}
	inline unsigned int group_count(void) const { return groups.size(); }
	inline unsigned int group_size(unsigned int n) const { return (index_grp.at(n))->size; }

	inline bool contains_elt(unsigned int e) const { return (index_elt.find(e) != index_elt.end()); }
	inline bool contains_grp(unsigned int n) const { return (index_grp.find(n) != index_grp.end()); }

	inline unsigned int group_first(unsigned int n) const { return *((index_grp.at(n))->first); }
	inline unsigned int group_last(unsigned int n) const { return *((index_grp.at(n))->last); }
	inline unsigned int group_id(unsigned int e) const { return ((index_elt.at(e))._group)->id; }

	//here it would be appropriate to define iterators...
	inline unsigned int front_elt(void) const { return elements.front(); }
	inline unsigned int back_elt(void) const { return elements.back(); }
	inline unsigned int front_grp(void) const { return groups.front().id; }
	inline unsigned int back_grp(void) const { return groups.back().id; }
	unsigned int next_elt(unsigned int) const;
	unsigned int prev_elt(unsigned int) const;
	unsigned int next_grp(unsigned int) const;
	unsigned int prev_grp(unsigned int) const;

	void make_first(unsigned int); //makes of an element (if it is present) the first of her group
	void make_last(unsigned int); //makes of an element (if it is present) the last of her group

	bool push_front(unsigned int); //insertion of a new front element (inserted in the first group)
	bool push_back(unsigned int); //insertion of a new back element (inserted in the last group)

	bool extend_left(unsigned int); //insertion of the last element in the previous group (as new first element)
	bool extend_right(unsigned int); //insertion of the first element in the next group (as new last element)

	bool grp_insert_front(unsigned int); //insertion of a new empty group at the front
	bool grp_insert_back(unsigned int); //insertion of a new empty group at the back
	bool grp_insert_before(unsigned int,unsigned int); //insert a new empty group before an existing group
	bool grp_insert_after(unsigned int, unsigned int); //insert a new empty group after an existing group

	bool erase_elt(unsigned int);
	bool erase_grp(unsigned int);
};

/*----------------------------------- Partition Refinement ------------------------------------------------------------------*/

class partition_refinement  {

	private:

		block_list _p;
		unsigned int _id;

  	public:
		partition_refinement(const unordered_set<unsigned int>&); //init

		inline bool empty(void) const { return _p.empty(); }

		unsigned int next(void); //returns (and removes) any element from the last set

		void refine(const unordered_set<unsigned int>&); //used for LexBFS
};

#endif
