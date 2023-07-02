/*Fibonacci heap
@author: G. Ducoffe
*/

#ifndef __FIBO_HEAP__
#define __FIBO_HEAP__

/*dependencies*/
#include <unordered_map>
#include <vector>
#include <limits>
using namespace std;

template<typename T>
class fibo_heap {
	
	private:
		
		struct node{

			T value;
			double priority;

			unsigned int degree;
			bool mark;
			node *father, *child, *prev, *next;

		};
		
	node *root;
	unsigned int _size;
	unordered_map<T,node*> index;
	
	public:
		
		fibo_heap(void);
		~fibo_heap();
		
		inline bool empty(void) const { return (size() == 0); }
		inline unsigned int size(void) const { return _size; }
		
		inline bool contains(T e) const { return (index.find(e) != index.end()); }
		double priority(T) const;
		T peek(void) const;
		
		bool insert(T,double);		
		void erase_min(void);
		bool erase(T);
		bool decrease_key(T,double);
	
	private:
		
		void meld(node*);
		void locate_min(void);
		unsigned int max_root_degree(void) const;
		node *merge(node*,node*);
		void consolidate(void);
		void cascade_cut(node*);
};

template<typename T>
fibo_heap<T>::fibo_heap(void): root(0), _size(0) {}

template<typename T>
fibo_heap<T>::~fibo_heap(){
	while(!empty())
		erase_min();
}

template<typename T>
void fibo_heap<T>::meld(node* r){
	if(root == nullptr) 
		root = r; 
	else if(r != nullptr){		
		node *tail = root->prev;
		root->prev = r->prev; root->prev->next = root;
		tail -> next = r; r->prev = tail;
		if(r->value < root->value)
		root = r;		
	}
}

template<typename T>
bool fibo_heap<T>::insert(T e, double p){
 	if(contains(e)) return 0;
 	
	node *n = new node; 
 	n->value = e; 
	n->priority = p;
	n->degree = 0;  
	n->mark = 0; 
	n->father = n->child = nullptr;
	n->prev = n->next = n;
	
	meld(n);
	
	_size++; 
	index[e] = n;
	  
	return 1;
}

template<typename T>
T fibo_heap<T>::peek(void) const {
	return root->value;
}

template<typename T>
void fibo_heap<T>::locate_min(void){
	if(!empty()){
		node *minNode = root;
		for(node *n = root->next; n != root; n = n->next)
		 if(n->value < minNode->value)
		  minNode = n;
		root = minNode;
	}	
}

template<typename T>
unsigned int fibo_heap<T>::max_root_degree(void) const{
	unsigned int rank = root->degree;
	for(node *n = root->next; n != root; n = n->next)
	 if(n->degree > rank)
	  rank = n->degree;
	return rank;
}

template<typename T>
typename fibo_heap<T>::node *fibo_heap<T>::merge(typename fibo_heap<T>::node *n1, typename fibo_heap<T>::node *n2){
	
	if(n1->value > n2->value) return merge(n2,n1);
	
	n1->degree++;
	
	n2->prev->next = n2->next;
	n2->next->prev = n2->prev;
	n2->father = n1;
	
	if(n1->child != nullptr) {
		n2->prev = n1->child->prev; n2->next = n1->child;
		n1->child->prev = n2; n2->prev->next = n2;
	} else { n2->prev = n2->next = n2; }
	n1->child = n2;
	
	if(n2==root) root = n1;
		
	return n1;
}

template<typename T>
void fibo_heap<T>::consolidate(void){
	
	vector<node*> rank(max_root_degree()+1,nullptr);
	
	for(node *n = root, *s = root->next; rank[n->degree] != n; n = s, s = s->next ){
		while(n->degree < rank.size() && rank[n->degree] != nullptr){
			n = merge(n,rank[n->degree]);
			rank[(n->degree)-1] = nullptr;
		}
		if(n->degree == rank.size()) rank.push_back(n);
		else rank[n->degree] = n;
	}
}

template<typename T>
void fibo_heap<T>::erase_min(void){
	
	if(empty()) return;
	
	node *r = root; //for future deletion
	index.erase(r->value);
	
	_size--;
	
	//detach all children nodes
	for(node *c = r->child; c != nullptr && c->father != nullptr; c = c->next)
	 c->father = nullptr;
	
	//detach from the list of all roots
	r->prev->next = r->next;
	r->next->prev = r->prev;
	root = (r == r->next) ? nullptr : r->next;
	
	meld(r->child);
	
	if(!empty()){
		consolidate();
		locate_min();
	}
	
	delete r;
	
}

template<typename T>
bool fibo_heap<T>::erase(T e){
  if(!contains(e)) return 0;
  decrease_key(e, priority(e) - priority(peek()) + 1); //new priority = min.priority - 1
  erase_min(); 
  return 1;
}

template<typename T>		
bool fibo_heap<T>::decrease_key(T e,double p){
	if(!contains(e)) return 0;
	node *n = index[e];
	n->priority -= p;
	if(n->father != nullptr && n->father->value > n->value)
	 cascade_cut(n);
	return 1;
}

template<typename T>
void fibo_heap<T>::cascade_cut(node *n){
	
 	node *f = n->father; n->father = nullptr;
 
 	if(n->next == n) f->child = nullptr;
	else { //deletion from the children list
		n->prev->next = n->next;
		n->next->prev = n->prev;
		if(n == f->child) f->child = n->next;
	}
	n->next = n->prev = n;
	n->mark = 0; 
	
	meld(n); //also updates the min. element

	f->degree--;	
	if(f->father != nullptr){
		if(!f->mark) f->mark = 1;
		else cascade_cut(f);
	}
}

template<typename T>
double fibo_heap<T>::priority(T e) const{
	if(!contains(e)) return numeric_limits<double>::infinity();
	else return (index.at(e))->priority;
}

#endif
