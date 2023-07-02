#include "weighted_search.hpp"
#include "fibo_heap.hpp"

search_output dijkstra_search(unsigned int s,const Graph& G){
	
	search_output res;
	res._tree[s] = s; //root
	
	fibo_heap<unsigned int> H;
	H.insert(s,0);
	
	while(!H.empty()){
		unsigned int v = H.peek();
		res._dist[v] = H.priority(v);
		H.erase_min();
		for(unsigned int u : G.neighbours(v)){
			double d = res._dist[v] + G.weight(v,u);
			if(res._dist.find(u) == res._dist.end() && d < H.priority(u)){
				res._tree[u] = v;
				if(!H.insert(u,d))
				 H.decrease_key(u,H.priority(u) - d);
			}
		}
	}
	
	return res;
}


search_output a_star_search(unsigned int s, const unordered_set<unsigned int>& T, const Graph& G, function<double(unsigned int)> h){
	
	search_output res;
	res._tree[s] = s;
	
	unordered_set<unsigned int> open, closed;
	fibo_heap<unsigned int> q;
	q.insert(s,h(s));
	open.insert(s);


	while(!q.empty()){
		
		unsigned int v = q.peek();
		res._dist[v] = q.priority(v) - h(v);
		q.erase_min();
		open.erase(v); closed.insert(v);
		
		if(T.find(v) != T.end()) break;
		else{
			for(unsigned int u : G.neighbours(v)){
				
				double d = res._dist[v] + G.weight(v,u);
				
				if(open.find(u) != open.end() && (q.priority(u) - h(u)) > d ){
					res._tree[u] = v;
					q.decrease_key(u,q.priority(u)-d-h(u));
				}else if(closed.find(u) != closed.end() && res._dist[u] > d){
					res._tree[u] = v;
					q.insert(u,d+h(u));
					closed.erase(u); open.insert(u);
				}else if(open.find(u) == open.end() && closed.find(u) == closed.end()){
					res._tree[u] = v;
					q.insert(u,d+h(u));
					open.insert(u);
				}
			}	
		}
	}
		
	return res;
	
}

search_output b_search(unsigned int s, const unordered_set<unsigned int>& T, const Graph& G, function<double(unsigned int)> h){
	
	search_output res;
	res._tree[s] = s;
	
	unordered_set<unsigned int> open, closed;
	fibo_heap<unsigned int> qa, qd; //first heap for A*, second heap for Dijkstra
	qd.insert(s,0);
	open.insert(s);
	
	double F = h(s);
	
	while(!qa.empty() || !qd.empty()){
		
		if(qd.empty()){
			
			F = qa.priority(qa.peek());
			
			while(!qa.empty() && qa.priority(qa.peek()) == F){
				qd.insert(qa.peek(),qa.priority(qa.peek())-h(qa.peek()));
				qa.erase_min();
			} 
		}
		
		unsigned int v = qd.peek();
		res._dist[v] = qd.priority(v);
		qd.erase_min();
		open.erase(v); closed.insert(v);
		
		if(T.find(v) != T.end()) break;
		else{
			for(unsigned int u : G.neighbours(v)){
				
				double d = res._dist[v] + G.weight(v,u);
				
				if(open.find(u) != open.end()){
					
					unsigned int curr_dist = (qd.contains(u)) ? qd.priority(u) : (qa.priority(u) - h(u));
					
					if(curr_dist > d){
						
						res._tree[u] = v;
						
						if(d+h(u) <= F){
							if(curr_dist + h(u) > F) {
								qa.erase(u); qd.insert(u,d);
							}else qd.decrease_key(u,curr_dist-d);
						}else qa.decrease_key(u,curr_dist-d);
						
					}
					
				}else if(closed.find(u) != closed.end()){
					if(res._dist[u] > d){
					  res._tree[u] = v;
					  if(d+h(u) <= F) qd.insert(u,d);
					  else qa.insert(u,d+h(u));
					  closed.erase(u); open.insert(u);	
					}
				}else {
					res._tree[u] = v;
					if(d+h(u)<= F) qd.insert(u,d);
					else qa.insert(u,d+h(u));
					open.insert(u);
				}
			}	
		}
	}	
	return res;
	
}
