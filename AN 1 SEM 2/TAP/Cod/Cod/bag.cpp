#include "bag.hpp"
#include <queue>
using namespace std;

pennant::~pennant(){
	if(left != nullptr) delete left;
	if(right != nullptr) delete right;
}

pennant *pennant_union(pennant *x, pennant *y){
	y->right = x->left;
	x->left = y;
	return x;
}

pennant *pennant_split(pennant *x){
	pennant *y = x->left;
	x->left = y->right;
	y->right = nullptr;
	return y;
}

bag::bag() : _sz(0) {}

list<unsigned int> bag::to_list(void) const {
	list<unsigned int> content;
	
	for(unsigned int i = 0; i < _S.size(); i++)
	 if(_S[i] != nullptr){
	 	queue<pennant*> q;
	 	q.push(_S[i]);
	 	while(!q.empty()){
	 		pennant *p = q.front();
	 		q.pop();
	 		content.push_back(p->_value);
	 		if(p->left != nullptr) q.push(p->left);
	 		if(p->right != nullptr) q.push(p->right);
		}
	 }
	
	return content;
}

bool bag_is_empty(const bag& B){
	return (B._sz == 0);
}

unsigned int bag_size(const bag& B){
	return B._sz;
}

void bag_insert(bag& B, unsigned int x){
	
	pennant *p = new pennant;
	p->_value = x;
	p->left = p->right = nullptr;
	
	unsigned int k(0);
	while(k < B._S.size() && B._S[k] != nullptr){
		p = pennant_union(p,B._S[k]);
		B._S[k++] = nullptr;
	}
	
	if(k==B._S.size()) B._S.push_back(p);
	else B._S[k] = p;
	
	B._sz++;
}

bag bag_union(bag& B1, bag& B2){
	
	pennant *x, *y, *z = nullptr;
	
	if(B1._S.size() < B2._S.size())
	 B1._S.resize(B2._S.size(),nullptr);
	else if(B2._S.size() < B1._S.size())
	 B2._S.resize(B1._S.size(),nullptr);
	
	unsigned int r = B1._S.size();
	
	for(unsigned int k = 0; k < r; k++){
		
		x = B1._S[k]; y = B2._S[k];
		
		if(x == nullptr && y == nullptr && z == nullptr){
			B1._S[k] = nullptr; z = nullptr;
		} 
		else if(x != nullptr && y == nullptr && z == nullptr){
			B1._S[k] = x; z = nullptr;
		}
		else if(x == nullptr && y != nullptr && z == nullptr){
			B1._S[k] = y; z = nullptr;
		}
		else if(x == nullptr && y == nullptr && z != nullptr){
			B1._S[k] = z; z = nullptr;
		}
		else if(x != nullptr && y != nullptr && z == nullptr){
			B1._S[k] = nullptr; z = pennant_union(x,y);
		}
		else if(x != nullptr && y == nullptr && z != nullptr){
			B1._S[k] = nullptr; z = pennant_union(x,z);
		}
		else if(x == nullptr && y != nullptr && z != nullptr){
			B1._S[k] = nullptr; z = pennant_union(y,z);
		}
		else{
			B1._S[k] = x; z = pennant_union(y,z);
		}
	}
	if(z != nullptr) B1._S.push_back(z);
	
	B1._sz += B2._sz;
	
	return B1;
}

bag bag_split(bag& B1){
	
	bag B2;
	pennant *y = B1._S[0];
	B1._S[0] = nullptr;
	for(unsigned int k = 1; k < B1._S.size(); k++){
		if(B1._S[k] != nullptr){
			B2._S.push_back(pennant_split(B1._S[k]));
			B1._S[k-1] = B1._S[k];
			B1._S[k] = nullptr;
		} else B2._S.push_back(nullptr);
	}
	B1._S.pop_back();
	
	B1._sz = B2._sz = B1._sz / 2;
	
	if(y != nullptr) {
		bag_insert(B1,y->_value); delete y;
	}
	
	return B2;
}
