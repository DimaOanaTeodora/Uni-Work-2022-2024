/******************************************************************************

                            Online C Compiler.
                Code, Compile, Run and Debug C program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum ntype {NO,YES};

typedef struct Node {
  char word;
  struct Node* lChild;
  struct Node* rChild;
  struct Node* mChild;
  enum ntype type; 
}Node;

Node* ROOT;

Node* create_node (char w, enum ntype t){
    /*
    Creaza primul nod
    pointer catre sine
    cuvantul
    stanga
    dreapta
    mijloc
    tipul
    */
  Node *_node = (struct Node*)malloc(sizeof (struct Node));
  _node->word = w;
  _node->lChild = NULL;
  _node->mChild = NULL;
  _node->rChild= NULL;
  _node->type = t;

  return _node;
}

Node* insert_node (const char* string, Node* node){
  if(NULL == node) // daca nu are radacina
    node = create_node(string[0], NO);

  // cauta unde sa-l puna
  if(string[0] < node->word) // in stanga
	  node->lChild = insert_node(string, node->lChild);
  else if(string[0] > node->word) // in dreapta
	  node->rChild = insert_node(string, node->rChild);
  else {
      // daca e o singura litera
	  if(strlen(string) == 1) {
		  node->type = YES;
		  return node;
	  } else // daca nu e o singura litera repeta procesul pe mijloc
		  node->mChild = insert_node(++string, node -> mChild);
  }

  return node;
}


struct Node* find_node(const char* string){
  // cauatre dupa un cuvant
  int i = 0;
  Node* _node = ROOT;

  // parcurge sirul
  while(i < strlen(string)) {
	  if(NULL  == _node) // daca a trecut de radacina
		  break;
	  if(string[i] < _node->word)// vede pe ce subarbore sa se duca
		  _node = _node->lChild;
	  else if(string[i] > _node->word)
		  _node = _node->rChild;
	  else {
		  if(i++ == strlen(string) - 1)
		      return _node;
		  else
		      _node = _node -> mChild;
	  }
  }

  return NULL;
}

void deep_search(const char* pattern, Node* start){
    // cauatre dupa un pattern
    
	if(start->type != NO)
		printf("FOUND:%s%c\n",pattern,start->word);

    // cauta pe subarbori
	if(start->lChild != NULL)
		deep_search(pattern, start->lChild);

	if(start->rChild != NULL)
		deep_search(pattern, start->rChild);

	if(start->mChild != NULL) {
		char *_pattern = (char *)malloc(strlen(pattern) + 2);
		sprintf(_pattern,"%s%c",pattern,start->word);
		deep_search(_pattern,start->mChild);
	}
}

void print_words_with_prefix (const char* pattern){

	Node* current = find_node(pattern);

	if(NULL == current)
		printf("no words with prefix %s\n",pattern);
	else {
		deep_search(pattern,current->mChild);
	}
}
int main(void)
{
  ROOT = create_node(' ',YES);
  printf("ROOT addr:%p\n",ROOT);
  char* a = "he";
  insert_node(a,ROOT);
  insert_node("cat",ROOT);
  insert_node("car",ROOT);
  insert_node("murder",ROOT);
  insert_node("menu",ROOT);

  printf("find 'cat' at %p\n",find_node("cat"));
  printf("find 'menu' at %p\n",find_node("menu"));
  printf("find 'dragon' at %p\n",find_node("dragon"));
  print_words_with_prefix("h");
  print_words_with_prefix("ca");
  return 0;
}