#include <stdio.h>
#include <stdlib.h>
#include "error.h"
#include "poly.h"

#define N   (256)
typedef struct poly_t poly_t;

struct poly_t{
    long coeff[N];  
    long exp[N];
    long s;
};

poly_t*	new_poly_from_string(const char* c){
    long i;
    long s = 0; 
    long flag = 0;
    long nbr = -1;
    long sign = 1;
    poly_t *pol = malloc(sizeof(poly_t));
    for(i=0;i<N;i++){
        pol->coeff[i] = 0;
        pol->exp[i] = 0;

    }   
        for(;;){
        
        if(*c >= '0' && *c <= '9'){
            if (nbr == -1) nbr = 0;
            nbr = nbr * 10 + *c - '0';
            c++;
            continue;
        }
        if(nbr != -1){
            if(flag) pol->exp[s] = nbr;
            else  pol->coeff[s] = sign * nbr;
            
            nbr = -1;
            flag = 0;
        }
        if(*c == 'x'){
            if(pol->coeff[s] == 0) pol->coeff[s] = sign;
                
            
            pol->exp[s] = 1;
            c++;
            if(*c == '^') flag = 1;    
            c++;
        }
        if(*c == '-'){
            s++;
            c +=1;
            sign = -1;
        }
        if(*c == '+'){
            s++;
            sign = 1;
            c += 1;
        }
        if(*c == '\0') break;
        if(*c == ' ') c++;
        
    }
    pol->s = s;
    return pol;
}


void free_poly(poly_t* c){
    free(c);
}   

poly_t* mul(poly_t* p1, poly_t* p2) {
    long i, j, k, coeff, exp;
    long s = 0;
    poly_t* p3 = malloc(sizeof(poly_t));

    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            coeff = p1->coeff[i] * p2->coeff[j];
            exp = p1->exp[i] + p2->exp[j];

            for (k = 0; k < s; k++) {
                if (p3->exp[k] == exp) {
                    p3->coeff[k] += coeff; 
                    break;
                }
            }

            if (k == s) {
                p3->coeff[s] = coeff;
                p3->exp[s] = exp;
                s++;
            }
        }
    }

    for (i = 0; i < s - 1; i++) {
        for (j = 0; j < s - i - 1; j++) {
            if (p3->exp[j] < p3->exp[j + 1]) {
                coeff = p3->coeff[j];
                exp = p3->exp[j];
                long j1 = j +1;
                p3->coeff[j] = p3->coeff[j1];
                p3->exp[j] = p3->exp[j1];
                p3->coeff[j1] = coeff;
                p3->exp[j1] = exp;
            }
        }
    }
    p3->s = s;
    return p3;
}

void print_poly(poly_t* p){
    long coef, expo, terms = p->s+1;
    for (long i = TABLE; i > 0; --i)
    {
        coef = p->coeff[i];
        expo = p->exp[i];
        if(coef < 0){
            printf(" - ");
            coef = -coef;
        }else if(i != 0 && coef != 0){
            printf(" + ");
        }
        if(coef != 1 || expo == 0) {
            if(coef != 0) printf("%ld", coef);
        }
        if(expo > 0) printf("x"); 
        if(expo > 1) printf("^%ld", expo);  
    }
    printf("\n");

}
