/*
 Partial-match folosind TST
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

Tptr insert1(Tptr p, char *s, char * insertstr){
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
        p->lokid = insert1(p->lokid, s, insertstr);
    else if (*s == p->splitchar) {
        if (*s == 0)
          p->eqkid = (Tptr) insertstr; // nou
       else
          p->eqkid = insert1(p->eqkid, ++s, insertstr);
    } else
        p->hikid = insert1(p->hikid, s, insertstr);

    return p;
}

char *srcharr[100000]; // pentru mai multe match-uri
int srchtop = 0, nodecnt = 0;
void pmsearch(Tptr p, char *s){
    printf("----- Cautare pentru pattern %s ---- \n", s);
    if (!p) return; // s-a terminat arborele
    
    nodecnt++;
    printf("Nodul curent este %c \n", p->splitchar);
    printf("Caracterul curent din pattern este %c \n", *s);
    if (*s == '.' || *s < p->splitchar){
        printf("Cautare in subarborele stang \n");
        pmsearch(p->lokid, s); // cautare pt caracterul "don't care" pe stanga sau in functie de string-ul de cautat
    }
    if (*s == '.' || *s == p->splitchar)
        if (p->splitchar && *s){
            printf("Cautare pe mijloc \n");
            pmsearch(p->eqkid, s + 1); // cautare pe mijloc
        }
    if (*s == 0 && p->splitchar == 0){
        printf("A fost gasit match s-a ajuns la capatul sirurilor \n");
        srcharr[srchtop++] =(char *) p->eqkid;//detectare match si adaugare pointer la cuvant
    }
    if (*s == '.' || *s > p->splitchar){
        printf("Cautare in subarborele drept \n");
        pmsearch(p->hikid, s); // cautare pt caracterul "don't care" pe dreapta sau in functie de string-ul de cautat
    }
}   
int main(){
    
    root = insert1(root, "banana", "banana");
    insert1(root, "core", "core");
    insert1(root, "code", "code");

    // srchtop = 0; 
    // pmsearch(root, ".a.a.a");
    // for(int i = 0; i< srchtop; i++){
    //     printf("Cautarea pentru patternul %s - am gasit %s \n", ".a.a.a", srcharr[i]);
    // }
    
    srchtop = 0; 
    pmsearch(root, "co.e");
    for(int i = 0; i< srchtop; i++){
        printf("Cautarea pentru patternul %s - am gasit %s \n", "c.d.", srcharr[i]);
    }
    
    // srchtop = 0; 
    // pmsearch(root, ".m.");
    // int print = 0;
    // for(int i = 0; i< srchtop; i++){
    //     printf("Cautarea pentru patternul %s - am gasit %s \n", ".m.", srcharr[i]);
    //     print = 1;
    // }
    // if(print == 0){
    //     printf("Nu am gasit nimic pentru %s \n", ".m.");
    // }
    return 0;
}