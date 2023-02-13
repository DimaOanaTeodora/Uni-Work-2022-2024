
/*
        P1: Multikey QuickSort implementare cu TST
    
    */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct tnode *Tptr;
typedef struct tnode{
    char splitchar; // valoarea din nod
    Tptr lokid, eqkid, hikid; // cei trei copii
} Tnode;
Tptr root; // radacina

Tptr insert1(Tptr p, char *s){
    //printf("----- Inserare pentru %s ---- \n", s);
    // adaugarea unui string in copac (daca exista deja nu face nimic)
    if (p == 0) {
        // creare radacina
        p = (Tptr) malloc(sizeof(Tnode));
        p->splitchar = *s;
        p->lokid = p->eqkid = p->hikid = 0;
    }
    //printf("Nodul curent este %c \n", p->splitchar);
    if (*s < p->splitchar)
        p->lokid = insert1(p->lokid, s);
    else if (*s == p->splitchar) {
        if (*s != 0)
            p->eqkid = insert1(p->eqkid, ++s);
    } else
        p->hikid = insert1(p->hikid, s);

    return p;
}

int search1(char *s){
    // return 1 daca s e in arbore si 0 altfel
    // incepe cu radacina si merge pe arbore in jos
    printf("----- Cautare noua pentru %s ---- \n", s);
    Tptr p;
    p = root;
    while (p) {
        printf("Nodul curent este %c \n", p->splitchar);
        if (*s < p->splitchar)
            p = p->lokid;
        else if (*s == p->splitchar) {
            if (*s++ == 0) // am ajuns la finalul stringului
                return 1; 
            p = p->eqkid;
        } else
            p = p->hikid;
    }
    return 0; // n-am gasit nimic
}

int main(){
    
    root = insert1(root, "cat");
    insert1(root, "car");
    insert1(root, "dept");
    printf("Rezultatul cautarii %s este %x \n", "dept", search1("dept"));
    printf("Rezultatul cautarii %s este %x \n", "cam", search1("cam"));
    
    return 0;
}