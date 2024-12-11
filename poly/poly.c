#include <stdio.h>
#include "error.h"
#include "poly.h"

#define TABLE   (2048)
typedef struct poly_t poly_t;

struct poly_t{
    long coeff[TABLE];  
};

poly_t*	new_poly_from_string(const char* c){
    long i;
    long flag = 0;
    long nbr = -1;
    long nbr_c = 0;
    long sign = 1;
    poly_t *pol = malloc(sizeof(poly_t));
    for(i=0;i<TABLE;i++){
        pol->coeff[i] = 0;
    }   
        for(;;){
        
        if(*c >= '0' && *c <= '9'){
            if (nbr == -1) nbr = 0;
            nbr = nbr * 10 + *c - '0';
            goto end;
        }

        if(*c == '-') sign = -1;
        if(*c== '+') sign = 1;
        if(*c == 'x'){

            nbr_c = nbr;
            if(nbr == -1) {
                nbr_c = sign;
            }
            c++;
            if(*c == '^'){
                flag = 1;
            }
            else{
                pol->coeff[1] = sign * nbr_c;
                

            }
            nbr=-1;
            
            goto end;
        }

        if(nbr != -1) 
        {
            if(flag){
                pol->coeff[nbr] = sign * nbr_c;
                flag = 0;
            }
            else{
                pol->coeff[0] =sign * nbr;
            }
            nbr = -1;
            
            
        }
        if(*c == '\0') break;
        end:
        c++;
    }
   
    return pol;
}


void free_poly(poly_t* c){
    free(c);
}   

poly_t* mul(poly_t* p1, poly_t* p2) {
    long i, j;
    poly_t* p3 = malloc(sizeof(poly_t));
    for (i = TABLE; i > -1; i--) {
        p3->coeff[i] = 0;
        for (j = 0; j < TABLE; j++) {
            if(i + j<TABLE) p3->coeff[i + j] += p2->coeff[i] * p1->coeff[j];
        }
    }

   
    return p3;
}

void print_poly(poly_t* p){
    long coef;
    long f = 0;
    for (long i = 2047; i >= 0; --i)
    {
        coef = p->coeff[i];
        if(coef != 0){
            if(coef < 0){
            printf(" - ");
            coef = -coef;
            }else if(f != 0 ){
                printf(" + ");
            }

            if(coef != 1 || i == 0) {
                printf("%ld", coef);
                f=1;
                
            }
            if(i > 0 ){
                printf("x"); 
                f=1;
            } 
            if(i > 1) printf("^%ld", i);  
            }
        
    }
    printf("\n");

}
