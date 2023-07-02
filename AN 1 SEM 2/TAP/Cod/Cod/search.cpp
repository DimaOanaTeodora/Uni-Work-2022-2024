#include "search.hpp"

#include "lists.hpp"
#include <queue>
#include <stack>
#include <unordered_set>
using namespace std;

/*-------------------------------------------- Graph Search -----------------------------------------*/

list<unsigned int> dfs(unsigned int s,const Graph& G){
	list<unsigned int> output;
	unordered_set<unsigned int> visited;
	stack<unsigned int> p;
	
	p.push(s);
	
	while(!p.empty()){
		
		unsigned int v = p.top();
		p.pop();
		
		if(visited.find(v) == visited.end()){
			visited.insert(v);
			output.push_back(v);
			list<unsigned int> Nv = G.neighbours(v);
			Nv.reverse(); 
			for(unsigned int u : Nv)
			 p.push(u);
		}
		
	}
	
	return output;
}


list<unsigned int> bfs(unsigned int s,const Graph& G){
	list<unsigned int> output;
	unordered_set<unsigned int> visited;
	queue<unsigned int> q;
	
	visited.insert(s);
	q.push(s);
	
	while(!q.empty()){
	
		unsigned int v = q.front();
		q.pop();
		output.push_back(v);
	
		for(unsigned int u : G.neighbours(v))
		 if(visited.find(u) == visited.end()){
		 	visited.insert(u);
		 	q.push(u);
		 }
	}
	
	return output;
}

list<unsigned int> lexbfs(unsigned int s, const Graph& G){
	
	list<unsigned int> output;
	unordered_set<unsigned int> visited;
	
	unordered_set<unsigned int> V;
	for(unsigned int v : G.vertex_list())
	 V.insert(v);
	partition_refinement p(V);
	
	unordered_set<unsigned int> S;
	S.insert(s);
	p.refine(S);
	
	while(!p.empty()){
		
		unsigned int v = p.next();
		visited.insert(v);
		output.push_back(v);
		
		S.clear();
		for(unsigned int u : G.neighbours(v))
		 if(visited.find(u) == visited.end())
		  S.insert(u);
		p.refine(S);
	}
	
	return output;
}
