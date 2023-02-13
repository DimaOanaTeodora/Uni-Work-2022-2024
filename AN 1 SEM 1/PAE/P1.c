
/*
        P1: Multikey QuickSort implementare fara TST
    
    */
#include <stdio.h>
#include <stdlib.h>
#define swap(a, b) { char *t=x[a]; x[a]=x[b]; x[b]=t; }
#define i2c(i) x[i] [depth]
#define min(a,b) (((a)<(b))?(a):(b))

void printVect(char* x[], int n){
    printf("Vectorul este: ");
    for(int i = 0; i < n; i++){
        printf("%s ", x[i]);
    }
    printf("\n");
}

void vecswap(int i, int j, int n, char *x[]){
    /*
     mută secvențe de elemente egale din pozițiile lor temporare de la sfarsitul vectorului înapoi
     la locul lor corespunzător din mijloc
    */
    printf("Vector swap(%x, %x, %x) \n", i, j, n);
    printf("Inainte de swap ");
    printVect(x, n);
    int copy = n;
    while (n-- > 0) {
        swap(i, j);
        i++;
        j++;
    }
    printf("Dupa swap ");
    printVect(x, copy);
}
void ssortl(char *x[], int n, int depth){ 
    printf("----- Apel nou functie sort -------- \n");
    printVect(x, n);
    printf("n = %x \n",  n);
    printf("depth = %x \n", depth);
    
    int a, b, c, d, r;
    char v;
    if (n <= 1){ // subvectorul are un singur element => nu mai avem ce sorta
        printf("Vector cu max 1 elm => STOP \n");
        return;
    }
        
    a = rand() % n; //aleg pivotul random
    printf("Pivot = %s \n", x[a]);
    swap (0, a); // mut pivotul pe prima pozitie
    printf("Swap(0, %x) \n", a);
    v = i2c(0); // caracterul de pe pozitia depth
    printf("Caracter de pe pozitia depth v= %c \n", v);
    a = b = 1; // a si b pleaca de la al doilea elem
    c = d = n - 1; // c si d pleaca de la coada vectorului
    
    while(1) {
        printf("START while a=%x si b=%x si c=%x si d=%x \n", a, b, c, d);
        while (b <= c && (r = i2c(b)-v) <= 0) { 
            // pune toate elem care au caracterul depth dupa pivot in ordine
            
            printf("Valoarea r este diferenta dintre %c si pivotul depth %c \n", i2c(b), v);
            if (r == 0) { 
                // daca sunt egale swap cu prima pozitie de dupa ultimul swap si merge mai departe
                printf("Sunt egale => swap(a,b) = swap(%x, %x) \n", a, b);
                swap(a, b); 
                a++; 
            }
            b++;
        }
        printf("Dupa primul subwhile a=%x b=%x c=%x d=%x \n", a, b, c, d);
        printVect(x, n);
        while (b <= c && (r = i2c(c)-v) >= 0) { 
            printf("Valoarea r este diferenta dintre %c si pivotul depth %c \n", i2c(c), v);
            if (r == 0) { 
                // daca sunt egale swap cu prima pozitie de dupa ultimul swap si merge mai departe
                printf("Sunt egale => swap(c,d) = swap(%x, %x) \n", c, d);
                swap(c, d);
                d--; 
            }
            c--;
        }
        printf("Dupa al doilea subwhile a=%x b=%x c=%x d=%x \n", a, b, c, d);
        printVect(x, n);
        if (b > c){ 
            printf("b > c STOP WHILE \n");
            break;
        }
        swap(b, c);
        printf("swap(%x, %x) \n", b, c);
        b++;
        c--;
    }
    printf("------------ \n");
    printf("Dupa while mare  a=%x b=%x c=%x d=%x \n", a, b, c, d);
    // muta elementele egale cu pivotul in mijloc + 1
    r = min(a, b - a); // cate muta
    vecswap(0, b - r, r, x);
    r = min(d - c, n - d - 1); // cate muta
    vecswap(b, n - r, r, x);
    
    printf(">>>>>Dupa cele 2 swaps \n");
    printVect(x, n);
        
    // apeluri pe subvectori pt acelasi depth
    ssortl(x, b - a, depth); // subvectorul stang
    if (i2c(b-a) != 0) // nu a ajuns la finalul sirului
        ssortl(x + (b-a), a + n - d - 1, depth + 1); // trec mai departe pana la finalul sirului
    ssortl(x + n - (d - c) , d - c, depth); // subvectorul drept
}


int main()
{
    char *x[] = {"aa","dm","dm","hs", "fg", "da" };
    int n = 6, depth = 0;
    ssortl(x, n, depth);
    printVect(x, n);
    return 0;
}
