#include "lists.hpp"

/*----------------------------------- Block List ------------------------------------------------------------------*/

unsigned int block_list::next_elt(unsigned int e) const{
	auto pos = index_elt.at(e)._pos;
	return *next(pos);
}

unsigned int block_list::prev_elt(unsigned int e) const{
	auto pos = index_elt.at(e)._pos;
	return *prev(pos);
}

unsigned int block_list::next_grp(unsigned int n) const{
	auto pos = index_grp.at(n);
	return next(pos)->id;
}

unsigned int block_list::prev_grp(unsigned int n) const{
	auto pos = index_grp.at(n);
	return prev(pos)->id;
}

void block_list::make_first(unsigned int e){
	if(contains_elt(e)){
	 auto pos = index_elt[e]._pos;
	 auto grp = index_elt[e]._group;
	 if(e == group_first(grp->id)) return;
     index_elt[e]._pos = elements.insert(grp->first,e);
     grp->first--;
     if(grp->last == pos) grp->last--;
     elements.erase(pos);
	}
}

void block_list::make_last(unsigned int e){
	if(contains_elt(e)){
	 auto pos = index_elt[e]._pos;
	 auto grp = index_elt[e]._group;
	 if(e == group_last(grp->id)) return;
	 index_elt[e]._pos = elements.insert(next(grp->last),e);
	 grp->last++;
     if(grp->first==pos) grp->first++;
     elements.erase(pos);
	}
}

bool block_list::push_front(unsigned int e){
	if(contains_elt(e)) return 0;
	if(groups.empty()) grp_insert_front(0);
	elements.push_front(e);
	index_elt[e]._pos = elements.begin(); index_elt[e]._group = groups.begin();
	groups.front().first = index_elt[e]._pos; if(groups.front().size == 0) { groups.front().last = index_elt[e]._pos;}
	groups.front().size++;
	return 1;
}

bool block_list::push_back(unsigned int e){
	if(contains_elt(e)) return 0;
	if(groups.empty()) return push_front(e);
	elements.push_back(e);
	index_elt[e]._pos = prev(elements.end()); index_elt[e]._group = prev(groups.end());
	groups.back().last = index_elt[e]._pos; if(groups.back().size == 0) { groups.back().first = index_elt[e]._pos;}
	groups.back().size++;
	return 1;
}

bool block_list::extend_left(unsigned int n){
	if(!contains_grp(n) || n == front_grp()) return 0;
	unsigned int g = prev_grp(n);
	if(group_size(g) == 0) return 0;
	unsigned int u = group_last(g);
	index_elt[u]._group = index_grp[n];
	index_grp[n]->first = index_grp[g]->last;
	if(group_size(n) == 0) index_grp[n]->last = index_grp[g]->last;
	index_grp[n]->size++;
	index_grp[g]->size--;
	if(group_size(g) > 0) index_grp[g]->last--;
	return 1;
}

bool block_list::extend_right(unsigned int n){
	if(!contains_grp(n) || n == back_grp()) return 0;
	unsigned int g = next_grp(n);
	if(group_size(g) == 0) return 0;
	unsigned int u = group_first(g);
	index_elt[u]._group = index_grp[n];
	index_grp[n]->last = index_grp[g]->first;
	if(group_size(n) == 0) index_grp[n]->first = index_grp[g]->first;
	index_grp[n]->size++;
	index_grp[g]->size--;
	if(group_size(g) > 0) index_grp[g]->first++;
	return 1;
}

bool block_list::grp_insert_front(unsigned int n){
	if(contains_grp(n)) return 0;
	group newgrp(n);
	groups.push_front(newgrp);
	index_grp[n] = groups.begin();
	return 1;
}

bool block_list::grp_insert_back(unsigned int n){
	if(contains_grp(n)) return 0;
	group newgrp(n);
	groups.push_back(newgrp);
	index_grp[n] = prev(groups.end());
	return 1;
}

bool block_list::grp_insert_before(unsigned int n,unsigned int g){
	if(contains_grp(n) || !contains_grp(g)) return 0;
	group newgrp(n);
	index_grp[n] = groups.insert(index_grp[g],newgrp);
	return 1;
}

bool block_list::grp_insert_after(unsigned int n, unsigned int g){
	if(!contains_grp(g)) return 0;
	if(g == back_grp()) return grp_insert_back(n);
	else return grp_insert_before(n,next_grp(g));
}

bool block_list::erase_elt(unsigned int e){
	if(!contains_elt(e)) return 0;
	make_last(e);
	unsigned int n = group_id(e);
	index_grp[n]->size--;
	if(index_grp[n]->size > 0) index_grp[n]->last--;
	elements.erase(index_elt[e]._pos);
	index_elt.erase(e);
	return 1;
}

bool block_list::erase_grp(unsigned int n){
	while(group_size(n) > 0)
	 erase_elt(group_first(n));
	groups.erase(index_grp[n]);
	index_grp.erase(n);
}

/*----------------------------------- Partition Refinement ------------------------------------------------------------------*/

partition_refinement::partition_refinement(const unordered_set<unsigned int>& V) : _id(0) {
	_p.grp_insert_front(_id);
	for(unsigned int v : V){
		_p.push_front(v);
	}
}

unsigned int partition_refinement::next(void){
	unsigned int v = _p.back_elt(); _p.erase_elt(v);
	unsigned int g = _p.back_grp(); if(_p.group_size(g) == 0){ _p.erase_grp(g);	}
	return v;
}

void partition_refinement::refine(const unordered_set<unsigned int>& S){
	unordered_set<unsigned int> hit_groups;
	for(unsigned int s : S){
		_p.make_last(s);
		hit_groups.insert(_p.group_id(s));
	}
	for(unsigned int g : hit_groups){
		_p.grp_insert_after(++_id,g);
		while( _p.group_size(g) > 0 && S.find(_p.group_last(g)) != S.end() ){
			_p.extend_left(_p.next_grp(g));
		}
		if(_p.group_size(g)==0) _p.erase_grp(g);
	}
}