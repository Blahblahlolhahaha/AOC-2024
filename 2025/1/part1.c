#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

int main(){
    FILE* file = fopen("input", "r");
    if(!file){
        printf("Cannot open file\n");
        exit(0);
    }
    int start = 50;
    int res = 0;
    char* line = (char*)calloc(4,1);
    if(!line){
        printf("Calloc died");
        exit(0);
    }
    int pos = 0;
    while(fread(line + pos, 1, 1, file)) {
        if(line[pos] == '\n'){
            int neg = 0;
            if(line[0] == 'R'){
               neg = 1;
            }
            int index = 0;
            int sad = 0;
            while((pos - index - 1) != 0){
                sad += (line[pos - index - 1] - '0') * pow(10, index);
                index += 1;
            }
            if(neg){
                sad *= -1;
            }
            start = (start + sad) % 100;
            printf("%d:%d\n", sad, start);
            if(start == 0) {
                res++;
            }
            memset(line, 0, 4);
            pos = 0;

        }
        else{
            pos += 1;
        }
    }
    fclose(file);
    free(line);
    line = NULL;
    printf("%d\n", res);
    return 0; 
}
