#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int comp(const void *a, const void *b){
    return (*(int*)a) - (*(int*)b);
}

char** str_split(char* input, char* delimiter, int* count){
    *count = 0;
    int length = strlen(input);
    int deLen = strlen(delimiter);
    for(int i = 0; i< length; i++){
        if(i + deLen > length){
            break;
        }
        char* sad = (char*) malloc(deLen + 1);
        sad[deLen] = 0;
        if(sad){
            strncpy(sad,input+i,deLen);
            if(strcmp(sad,delimiter) == 0){
                *count = *count + 1;
            }
        }
        
        memset(sad,0,deLen);
        free(sad);
        sad = NULL;
    }
    char* temp = (char*) malloc(length + deLen + 1);
    char** result = (char**)malloc(*count*8);
    if(result && temp){
        strncpy(temp,input,length);
        strncpy(temp+length,delimiter,deLen);
        char* token = strtok(temp, delimiter);
        int based = 0;
        while(token){
            int tok_len = strlen(token);
            result[based] = (char*) malloc(tok_len + 1);
            if(result[based]){
                result[based][tok_len + 1] = 0;
                strncpy(result[based],token,tok_len);
            }
            based ++;
            token = strtok(NULL,delimiter);
        }
        memset(temp,0,length + deLen +1);
        free(temp);
        temp = NULL;
    }
    return result;
}



int main(){
    FILE* file = fopen("input","r");
    char* sad = (char*) malloc(14001);
    
    if(sad){
        int bytes = fread(sad,1,14000,file);
        if(bytes == 0){
            printf("sad\n");
        }
        int count = 0;
        char** result = str_split(sad,"\n",&count);
        int left[count];
        int right[count];
        for(int i = 0; i<count;i++){
            char* line = result[i];
            int num = 0; 
            char** gg = str_split(line,"   ",&num);
            left[i] = atoi(gg[0]);
            right[i] = atoi(gg[1]);
        }
        qsort(left,count,sizeof(int),comp);
        qsort(right,count,sizeof(int),comp);
        //part 1
        int distance = 0;
        for(int i = 0;i < count;i++){
            int dist = left[i] - right[i];
            if(dist < 0){
                dist  = -dist;
            }
            distance += dist;
        }
        printf("%d\n", distance);
        
        //part 2
        int similarity = 0;
        for(int i = 0;i< count;i++){
            int gg = 0;
            int leftie = left[i];
            for(int x = 0;x< count; x++){
                int rightie = right[x];
                if(rightie > leftie){
                    break;
                }
                if(leftie == rightie){
                    gg++;
                }
            }
            similarity += gg * leftie;
        }
        printf("%d\n",similarity);
    }
    return 0;
}
