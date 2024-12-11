#include "stdio.h"

#define L   (10)
#define N   (154)

int main(){
    long i;
    long line = 0;
    long word_count = 0;
    long word_exist = 0;
    long values[N] = {0};
    long index;
    char words[N][L];
    char current_word[L];
    long flag = 0;
    char str[4][10] = { "deleted", "not found", "added", "counted"};
    char *dest;
    char *src;
    s:
    while (scanf("%99s", current_word) == 1) {
        line++;
        word_exist = 0;
        
        for (i = 0; i < word_count; i++) {
            dest = words[i];
            src = current_word; 
            while (*dest && (*dest == *src)) {
                dest++;
                src++;
            }
            if (*dest - *src == 0) {
                word_exist = 1;
                break;
            }

        }
        if (!word_exist) {
            dest = words[word_count]; 
            src = current_word;  
            while ((*dest++ = *src++) != '\0');  
            word_count++;
            
        }

        if (line == 1) goto not_prime;
        
        for (long i = 2; i < line; i++) {
            if (line % i == 0){ 
                goto not_prime;
            }
        }
        
        if(values[i] != 0) flag = 0; 
        else flag = 1;
        values[i] = 0;
        printf("trying to delete %s: %s\n",current_word, str[flag]);
        goto s;
        
        not_prime:
            if (values[i] == 0) flag = 2;
            else flag = 3;
            printf("%s %s\n", str[flag],current_word);
            values[i] += 1;        
    }
    
    index = 0;
    for (i = 1; i < word_count; i++) {
        if (values[i] > values[index]) {
            index = i;
        }
    }
    printf("result: %s %ld\n", words[index], values[index]);

    }