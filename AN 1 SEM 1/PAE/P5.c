/*
Nearest neighbor searching folosind TST
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
    // adaugarea unui string in copac (daca exista deja nu face nimic)
    if (p == 0) {
        // creare radacina
        p = (Tptr) malloc(sizeof(Tnode));
        p->splitchar = *s;
        p->lokid = p->eqkid = p->hikid = 0;
    }
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

char *srcharr[100000];
int srchtop = 0, nodecnt = 0;

void nearsearch(Tptr p, char *s, int d){
    printf("----- Cautare pentru sirul %s cu distanta %d ---- \n", s, d);
    if (!p || d < 0) return; // nod null sau distanta negativa
    nodecnt++;
    
    printf("Nodul curent este %c \n", p->splitchar);
    //printf("Caracterul curent din sir este %c \n", *s);
    if (d > 0 || *s < p->splitchar){ // cauta copilul apropiat daca d >0 sau daca caracterul este pe partea apropiata lui splitchar
        printf("Cautare in subarborele stang \n");
        nearsearch(p->lokid, s, d);
    }
    
    if (p->splitchar == 0) { // check match sau merge recurisv pe copilul din mijloc
        // acest if else preia si d==0
        printf("Verificare match \n");
        if ((int) strlen(s) <= d)
            srcharr[srchtop++] = (char * ) p->eqkid;
    }else{
        printf("Cautare pe mijloc \n");
        nearsearch(p->eqkid, *s ? s + 1 : s, (*s==p->splitchar) ? d : d - 1);
    }
    
    if (d > 0 || *s > p->splitchar){ // cauta copilul apropiat daca d >0 sau daca caracterul este pe partea apropiata lui splitchar
        printf("Cautare in subarborele drept \n");
        nearsearch(p->hikid, s, d);
    }
}

int main(){
    
    root = insert1(root, "banana", "banana");
    insert1(root, "code", "code");
    insert1(root, "coma", "coma");

    // soda -> code, come
    srchtop = 0;
    nearsearch(root, "soda", 2);
    for(int i = 0; i< srchtop; i++){
        printf("Cautarea pentru %s - am gasit %s \n", "soda", srcharr[i]);
    }
    return 0;
}