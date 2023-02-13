/******************************************************************************

                            Online C Compiler.
                Code, Compile, Run and Debug C program online.
Write your code in this editor and press "Run" button to compile and execute it.
Source: https://www.digitalocean.com/community/tutorials/hash-table-in-c-plus-plus 

*******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int tabsize;

int hash_function(char *s){
    unsigned n = 0;
    for ( ; *s; s++)
        n = 31 * n + *s;
    return n % tabsize;
}

typedef struct Ht_item Ht_item;
struct Ht_item {
    char* key;
};

typedef struct HashTable HashTable;
struct HashTable {
    Ht_item** items; // vectori de pointeri la chei
    int size;
    int count;
};


HashTable* create_table(int size) {
    // creare tabel nou
    HashTable* table = (HashTable*) malloc (sizeof(HashTable));
    table->size = size;
    table->count = 0;
    table->items = (Ht_item**) calloc (table->size, sizeof(Ht_item*));
    for (int i=0; i<table->size; i++)
        table->items[i] = NULL;

    return table;
}


void ht_insert(HashTable* table, char* key) {
    // creare cheie
    
    Ht_item* item = (Ht_item*) malloc (sizeof(Ht_item));
    item->key = (char*) malloc (strlen(key) + 1);
    
    strcpy(item->key, key);

    // calculeaza index
    int index = hash_function(key);
    // verific daca cheia exista
    Ht_item* current_item = table->items[index];
    
    if (current_item == NULL) {
        // cheia nu exista deja => inserare
        table->items[index] = item; 
        table->count++;
    }
}


int ht_search(HashTable* table, char* key) {
    // cauta existenta key in hash table

    Ht_item* item = table->items[hash_function(key)];

    // daca a gasit ceva
    if (item != NULL) {
        if (strcmp(item->key, key) == 0)
            return 1;
    }
    return 0;
}


void print_table(HashTable* table) {
    // afisare tabel
    printf("\nHash Table\n-------------------\n");
    for (int i=0; i<table->size; i++) {
        if (table->items[i]) {
            printf("Index:%d, Key:%s \n", i, table->items[i]->key);
        }
    }
    printf("-------------------\n\n");
}

int main() {
   
    tabsize = 5;
    HashTable* ht = create_table(tabsize);
    ht_insert(ht, "ana");
    ht_insert(ht, "cat");
    ht_insert(ht, "car");
    
    printf("Is element ana? A:%x \n",  ht_search(ht, "ana"));
    printf("Is element car? A:%x \n",  ht_search(ht, "car"));
    printf("Is element ionel? A:%x \n",  ht_search(ht, "ionel"));
    print_table(ht);
    return 0;
}