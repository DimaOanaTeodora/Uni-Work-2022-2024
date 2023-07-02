#include "graphs.hpp"
#include "bag.hpp"
#include <omp.h>
#include <queue>
#include <iostream>
using namespace std;

void ParallelGraphAlgorithms::make_directed(Graph& G) {
	if(!G.directed()){
		
		G.is_directed = 1;
		
		for(unsigned int v: G.vertex_list())
		 G.In[v]; //create inlist
		
		for(unsigned int v : G.vertex_list()){
			if(G.degree(v) > 0){
				#pragma omp parallel for
				for(unsigned int i = 0 ; i < G.Out[v]._map.bucket_count(); i++){
					for(auto it = G.Out[v]._map.begin(i); it != G.Out[v]._map.end(i); it++){
				 		G.insert(G.In[it->first],v,1);
				 	}
				}
			}
		}
	}
}

void ParallelGraphAlgorithms::isolate(unsigned int v, Graph& G){
	if(G.in_degree(v) > 0){
		Graph::AdjList& Nv = G.In[v];
		#pragma omp parallel for
		for(unsigned int i = 0 ; i < Nv._map.bucket_count(); i++){
			for(auto it = Nv._map.begin(i); it != Nv._map.end(i); it++){
				G.erase(G.Out[it->first],v);
			}
		}		
	}
}

void ParallelGraphAlgorithms::pdfs_rec(unsigned int v, Graph& G){
	
	cout << v << ' ';
	
	isolate(v,G);
	
	while(G.out_degree(v) > 0){
		unsigned int u = G.Out[v]._list.front();
		pdfs_rec(u,G);	
	}		
	
}

void ParallelGraphAlgorithms::parallel_dfs(unsigned int s, Graph G){
	 
	make_directed(G);

	cout << "PDFS: ";
	pdfs_rec(s,G);
	cout << endl << endl;
}

void ParallelGraphAlgorithms::parallel_bfs(unsigned int s, Graph G){
	make_directed(G);

	queue<unsigned int> q;
	q.push(s);
	isolate(s,G);
	cout << "PBFS: ";
	while(!q.empty()){
		unsigned int v = q.front();
		q.pop();
		cout << v << ' ';
		for(unsigned int u : G.neighbours(v)){
			q.push(u);
			isolate(u,G);
		}
	}
	cout << endl << endl;
}

void ParallelGraphAlgorithms::vertex_centric_pbfs(unsigned int s, Graph G, ParallelGraphAlgorithms::bfs_t& T){
	
	#pragma omp parallel for
	for(unsigned int i = 0; i < G.Out.bucket_count(); i++){
	  for(auto it = G.Out.begin(i); it != G.Out.end(i); it++){
	  	T._p[it->first] = -1;
	   	T._d[it->first] = -1;	
	  }	
	}
	
	T._d[s] = 0;
	
	unsigned int d(0);
	bool flag(1);
	while(flag){
		
		flag = 0;
		
		#pragma omp parallel for
		for(unsigned int i = 0 ; i < G.Out.bucket_count(); i++){
			for(auto it = G.Out.begin(i); it != G.Out.end(i); it++){
				
				unsigned int v = it->first;
				
				if(T._d[v] == d){
					
					#pragma omp parallel for
					for(unsigned int j = 0; j < G.Out[v]._map.bucket_count(); j++){
						for(auto n_it = G.Out[v]._map.begin(j); n_it != G.Out[v]._map.end(j); n_it++){
							
							unsigned int u = n_it -> first;
							
							if(T._d[u] == -1) {
								T._d[u] = d + 1; flag = 1;	
							}else if(T._d[u] < d) T._p[v] = u;
							
						}
					}
					
					
					if(v == s) T._p[s] = s;
						
				} 
				
			}
		}
		
		d++;
		
	}
	
}

void ParallelGraphAlgorithms::simple_pbfs(unsigned int s, Graph G, ParallelGraphAlgorithms::bfs_t& T){
	
	#pragma omp parallel for
	for(unsigned int i = 0; i < G.Out.bucket_count(); i++){
	  for(auto it = G.Out.begin(i); it != G.Out.end(i); it++){
	  	T._p[it->first] = -1;
	   	T._d[it->first] = -1;	
	  }	
	}
	
	T._p[s] = s;
	T._d[s] = 0;
	
	queue<unsigned int> CQ;
	CQ.push(s);
	
	unsigned int sz;
	while(!CQ.empty()){
		
		queue<unsigned int> NQ;
		
		sz = CQ.size();
		#pragma omp parallel for
		for(unsigned int i = 0; i < sz; i++){
			
			unsigned int v;
			#pragma omp critical
			{
				v = CQ.front();
				CQ.pop();
			}
						
			#pragma omp parallel for
			for(unsigned int j = 0; j < G.Out[v]._map.bucket_count(); j++){
				for(auto it = G.Out[v]._map.begin(j); it != G.Out[v]._map.end(j); it++){
					unsigned int u = it->first;
					#pragma omp critical
					if(T._p[u] == -1){
						T._p[u] = v;
						T._d[u] = T._d[v]+1;
						NQ.push(u);
					}
				}
			}

			
		}
		
		CQ = NQ;
		
	}
	
}

void ParallelGraphAlgorithms::bitmap_pbfs(unsigned int s, Graph G, ParallelGraphAlgorithms::bfs_t& T){
	
	unsigned int n = G.order();
	bool bitmap[n];
	
	#pragma omp parallel for
	for(unsigned int i = 0; i < G.Out.bucket_count(); i++){
	  for(auto it = G.Out.begin(i); it != G.Out.end(i); it++){
	  	T._p[it->first] = -1;
	   	T._d[it->first] = -1;
		bitmap[it->first] = 0;   	
	  }	
	}
	
	T._p[s] = s;
	T._d[s] = 0;
	bitmap[s] = 1;
	
	queue<unsigned int> CQ;
	CQ.push(s);
	
	unsigned int sz;
	while(!CQ.empty()){
		
		queue<unsigned int> NQ;
		
		sz = CQ.size();
		#pragma omp parallel for
		for(unsigned int i = 0; i < sz; i++){
			
			unsigned int v;
			#pragma omp critical
			{
				v = CQ.front();
				CQ.pop();
			}
						
			#pragma omp parallel for
			for(unsigned int j = 0; j < G.Out[v]._map.bucket_count(); j++){
				for(auto it = G.Out[v]._map.begin(j); it != G.Out[v]._map.end(j); it++){
					
					unsigned int u = it->first;
					
					bool a = bitmap[u];
					if(!a){
						bool prev;
						
						#pragma omp atomic capture
						{prev = bitmap[u]; bitmap[u] = 1;}
						
						if(!prev){
							T._p[u] = v;
							T._d[u] = T._d[v]+1;
							
							#pragma omp critical
							NQ.push(u);
						}
					}
				}
			}
		}
		
		CQ = NQ;
		
	}
	
}

void ParallelGraphAlgorithms::bag_pbfs(unsigned int s, Graph G, ParallelGraphAlgorithms::bfs_t& T){
	
	#pragma omp parallel for
	for(unsigned int i = 0; i < G.Out.bucket_count(); i++){
	  for(auto it = G.Out.begin(i); it != G.Out.end(i); it++){
	  	T._p[it->first] = -1;
	   	T._d[it->first] = -1;	
	  }	
	}
	
	T._p[s] = s;
	T._d[s] = 0;
	
	unsigned int d(0);
	
	bag CB;
	bag_insert(CB,s);
	
	while(!bag_is_empty(CB)){
		bag NB;
		process_layer(CB,NB,d,G,T);
		d++;
		CB = NB;
	}
	
}

#define GRAINSIZE 2

#pragma omp declare reduction(unite : bag : omp_out = bag_union(omp_out,omp_in))

void ParallelGraphAlgorithms::process_layer(bag& CB, bag& NB, unsigned int d, Graph& G, bfs_t& T){
	
	if(bag_size(CB) < GRAINSIZE){
		
		for(unsigned int u : CB.to_list()){
			
			#pragma omp parallel for reduction(unite : NB)
			for(unsigned int j = 0; j < G.Out[u]._map.bucket_count(); j++){
				for(auto it = G.Out[u]._map.begin(j); it != G.Out[u]._map.end(j); it++){
					
					unsigned int v = it->first;
							
					if(T._d[v] == -1){
						T._d[v] = d+1;
						T._p[v] = u;
						bag_insert(NB,v);
					}
							
				}
			}
	
		}
		
		return;
	}
	
	bag CB_half = bag_split(CB);
	
	#pragma omp parallel sections reduction(unite : NB)
	{
		#pragma omp section
		process_layer(CB,NB,d,G,T);
		
		#pragma omp section
		process_layer(CB_half,NB,d,G,T);
	} 

}

/*------------------------------------------- Connected components ----------------------------------------------*/

void ParallelGraphAlgorithms::algorithm_S(Graph G, vector<unsigned int>& p, vector<unsigned int>& o){
	
	#pragma omp parallel for
	for(unsigned int i = 0; i < G.Out.bucket_count(); i++){
		for(auto it = G.Out.begin(i); it != G.Out.end(i); it++){
			unsigned int v = it->first;
			p[v] = v;
		}
	}
	
	bool not_done(1);
	while(not_done){
		not_done = parent_connect(G,p,o);
		bool not_star(1);
		while(not_star) not_star = shortcut(G,p,o);
	}
	
}

void ParallelGraphAlgorithms::algorithm_RA(Graph G, vector<unsigned int>& p, vector<unsigned int>& o){
	
	#pragma omp parallel for
	for(unsigned int i = 0; i < G.Out.bucket_count(); i++){
		for(auto it = G.Out.begin(i); it != G.Out.end(i); it++){
			unsigned int v = it->first;
			p[v] = v;
		}
	}
	
	bool not_done(1);
	while(not_done){
		bool a = direct_root_connect(G,p,o);
		bool b = shortcut(G,p,o);
		not_done = a || b;
		alter(G,p);
	}
	
}

void ParallelGraphAlgorithms::algorithm_A(Graph G, vector<unsigned int>& p, vector<unsigned int>& o){
	
	#pragma omp parallel for
	for(unsigned int i = 0; i < G.Out.bucket_count(); i++){
		for(auto it = G.Out.begin(i); it != G.Out.end(i); it++){
			unsigned int v = it->first;
			p[v] = v;
		}
	}
	
	bool not_done(1);
	while(not_done){
		bool a = direct_connect(G,p,o);
		bool b = shortcut(G,p,o);
		not_done = a || b;
		alter(G,p);
	}
	
}
		
bool ParallelGraphAlgorithms::direct_connect(Graph& G, vector<unsigned int>& p, vector<unsigned int>& o){
	
	bool changes(0);
	
	#pragma omp parallel for
	for(unsigned int i = 0; i < G.Out.bucket_count(); i++){
		for(auto itv = G.Out.begin(i); itv != G.Out.end(i); itv++){
			unsigned int v = itv->first;
			unsigned int parent = o[v] = p[v];
			#pragma omp parallel for reduction(min : parent)
			for(unsigned int j = 0; j < G.Out[v]._map.bucket_count(); j++){
				for(auto ite = G.Out[v]._map.begin(j); ite != G.Out[v]._map.end(j); ite++){
					unsigned int w = ite->first;
					if(v > w)
					 parent = min(parent,w);
				}
			}
			p[v] = parent;
			if(o[v] != p[v]) changes = 1;
		}
	}
	
	return changes;
}

bool ParallelGraphAlgorithms::parent_connect(Graph& G, vector<unsigned int>& p, vector<unsigned int>& o){
	
	bool changes(0);
	
	#pragma omp parallel for
	for(unsigned int i = 0; i < G.vertices.bucket_count(); i++){
		for(auto itv = G.vertices.begin(i); itv != G.vertices.end(i); itv++){
			unsigned int v = *itv;
			o[v] = p[v];
		}
	}
	
	#pragma omp parallel for
	for(unsigned int i = 0; i < G.Out.bucket_count(); i++){
		for(auto itv = G.Out.begin(i); itv != G.Out.end(i); itv++){
			
			unsigned int v = itv->first;
			
			#pragma omp parallel for
			for(unsigned int j = 0; j < G.Out[v]._map.bucket_count(); j++){
				for(auto ite = G.Out[v]._map.begin(j); ite != G.Out[v]._map.end(j); ite++){
					
					unsigned int w = ite->first;
					
					if(o[v] > o[w])
					 #pragma omp critical
					 p[o[v]] = min(p[o[v]],o[w]);
					
				}
			}
			
		}
	}
	
	return changes;
}

bool ParallelGraphAlgorithms::direct_root_connect(Graph& G, vector<unsigned int>& p, vector<unsigned int>& o){
	
	
	bool changes(0);
	
	#pragma omp parallel for
	for(unsigned int i = 0; i < G.Out.bucket_count(); i++){
		for(auto itv = G.Out.begin(i); itv != G.Out.end(i); itv++){
		
			unsigned int v = itv->first;
		
			if(p[v] == v){
				
				unsigned int parent = v; //=p[v]
				
				#pragma omp parallel for reduction(min : parent)
				for(unsigned int j = 0; j < G.Out[v]._map.bucket_count(); j++){
					for(auto ite = G.Out[v]._map.begin(j); ite != G.Out[v]._map.end(j); ite++){
						unsigned int w = ite->first;
						if(v > w)
						 parent = min(parent,w);
					}
				}
				
				p[v] = parent;
				if(p[v] != v) changes = 1;	
				
			}
			
		}
	}
	
	return changes;

}

bool ParallelGraphAlgorithms::parent_root_connect(Graph& G, vector<unsigned int>& p, vector<unsigned int>& o){

	bool changes(0);
	
	#pragma omp parallel for
	for(unsigned int i = 0; i < G.vertices.bucket_count(); i++){
		for(auto itv = G.vertices.begin(i); itv != G.vertices.end(i); itv++){
			unsigned int v = *itv;
			o[v] = p[v];
		}
	}
	
	#pragma omp parallel for
	for(unsigned int i = 0; i < G.Out.bucket_count(); i++){
		for(auto itv = G.Out.begin(i); itv != G.Out.end(i); itv++){
			
			unsigned int v = itv->first;
			
			#pragma omp parallel for
			for(unsigned int j = 0; j < G.Out[v]._map.bucket_count(); j++){
				for(auto ite = G.Out[v]._map.begin(j); ite != G.Out[v]._map.end(j); ite++){
					
					unsigned int w = ite->first;
					
					if(o[v] > o[w] && o[o[v]] == o[v])  
					 #pragma omp critical
					 p[o[v]] = min(p[o[v]],o[w]);
					
				}
			}
			
		}
	}
	
	return changes;	

}
		
bool ParallelGraphAlgorithms::shortcut(Graph& G, vector<unsigned int>& p, vector<unsigned int>& o){
	
	bool changes(0);
	
	#pragma omp parallel for
	for(unsigned int i = 0; i < G.vertices.bucket_count(); i++){
		for(auto it = G.vertices.begin(i); it != G.vertices.end(i); it++){
			unsigned int v = *it;
			o[v] = p[v];
		}
	}
	
	#pragma omp parallel for
	for(unsigned int i = 0; i < G.vertices.bucket_count(); i++){
		for(auto it = G.vertices.begin(i); it != G.vertices.end(i); it++){
			unsigned int v = *it;
			p[v] = o[o[v]];
			if(p[v] != o[v]) changes = 1;
		}
	}
	
	return changes;
}
		
void ParallelGraphAlgorithms::alter(Graph& G, vector<unsigned int>& p){
	
	#pragma omp parallel for
	for(unsigned int i = 0; i < G.Out.bucket_count(); i++){
		for(auto itv = G.Out.begin(i); itv != G.Out.end(i); itv++){
			
			unsigned int v = itv->first;
			
			#pragma omp parallel for
			for(unsigned int j = 0; j < G.Out[v]._map.bucket_count(); j++){
				for(auto ite = G.Out[v]._map.begin(j); ite != G.Out[v]._map.end(j); ite++){
					
					unsigned int w = ite->first;
					
					if(p[v] != p[w]){
					 
					 Graph::Edge e; //dummy
					 
					 #pragma omp critical
					 G.In[p[w]]._map[p[v]] = e;
					 
					}
				}
			}
			
		}
	}
	
	G.Out = unordered_map<unsigned int, Graph::AdjList>();	
	swap(G.Out,G.In);
	
}
