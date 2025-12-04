#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>


int8_t numOfRolls(int8_t** field, int i, int j, int ind, int lineLen) {
    int8_t total = 0;
    if( i !=0 ) {
        int8_t* line = field[i - 1];
        total += line[j] == 0 ? 0 : 1;
        if(j != 0 && line[j - 1] != 0) {
            total++;
        } 
        if(j != lineLen - 1 && line[j + 1] != 0) {
            total++;
        }
    }
    if(i != ind - 1) {
        int8_t* line = field[i + 1];
        total += line[j] == 0 ? 0 : 1;
        if(j != 0 && line[j - 1] != 0) {
            total++;
        } 
        if(j != lineLen - 1 && line[j + 1] != 0) {
            total++;
        }
    }
    int8_t* line = field[i];
    if(j != 0 && line[j - 1] != 0) {
        total++;
    } 
    if(j != lineLen - 1 && line[j + 1] != 0) {
        total++;
    }
    return total;
}

int dfs(int8_t** field, int i, int j, int ind, int lineLen) { 
    int total = 0;
    if( i !=0 ) {
        int8_t* line = field[i - 1];
        if(line[j] > 0) {
            line[j] -= 1;
            if(line[j] <= 4) {
                line[j] = 0;
                total++;
                total += dfs(field, i - 1, j, ind, lineLen);
            }
        }
        if(j != 0 && line[j - 1] > 0) {
            line[j -1] -= 1;
            if(line[j - 1] <= 4) {
                line[j - 1] = 0;
                total++;
                total += dfs(field, i - 1, j - 1, ind, lineLen);
            }
        } 
        if(j != lineLen - 1 && line[j + 1] > 0) {
            line[j + 1] -= 1;
            if(line[j + 1] <= 4) {
                line[j + 1] = 0;
                total++;
                total += dfs(field, i - 1, j + 1, ind, lineLen);
            }
        }
    }
    if(i != ind - 1) {
        int8_t* line = field[i + 1];
        if(line[j] > 0) {
            line[j] -= 1;
            if(line[j] <= 4) {
                line[j] = 0;
                total++;
                total += dfs(field, i + 1, j, ind, lineLen);
            }
        }
        if(j != 0 && line[j - 1] > 0) {
            line[j - 1] -= 1;
            if(line[j - 1] <= 4) {
                line[j - 1] = 0;
                total++;
                total += dfs(field, i + 1, j - 1, ind, lineLen);
            }
        } 
        if(j != lineLen - 1 && line[j + 1] > 0) {
            line[j + 1] -= 1;
            if(line[j + 1] <= 4) {
                line[j + 1] = 0;
                total++;
                total += dfs(field, i + 1, j + 1, ind, lineLen);
            }
        }
    }
    int8_t* line = field[i];
    if(j != 0 && line[j - 1] > 0) {
        line[j - 1] -= 1;
        //printf("%d:%d\n",field[i][j - 1], line[j - 1]);
        if(line[j - 1] <= 4){
            line[j - 1] = 0;
            total++;
            total += dfs(field, i, j - 1, ind, lineLen);
        }
    } 
    if(j != lineLen - 1 && line[j + 1] > 0) {
        line[j + 1] -= 1;
        if(line[j + 1] <= 4){
            line[j + 1] = 0;
            total++;
            total += dfs(field, i, j + 1, ind, lineLen);
        }
    }
    return total;
}

int main(int argc, char** argv){
    FILE* file = fopen(argv[1], "r");
    if(!file){
        printf("Cannot open file\n");
        exit(0);
    }
    int res = 0;
    char* line = (char*)calloc(256,1);
    if(!line){
        printf("Calloc died");
        exit(0);
    }
    int8_t** lines = calloc(256, sizeof(int8_t*));
    if(!lines){
        free(line);
        line = NULL;
        printf("Calloc died\n");
        exit(0);
    }
    int lineLen = -1;
    int pos = 0;
    int ind = 0;
    while(fread(line + pos, 1, 1, file)) {
        if(line[pos] == '\n') {
            if(lineLen == -1) {
                lineLen = pos;
            }
            lines[ind] = calloc(lineLen + 1, 1);
            if(!lines[ind]) {
                printf("Calloc died\n");
                exit(0);
            }
            for(int i = 0; i < lineLen; i++){
                if(line[i] == '@'){
                    lines[ind][i] = 1;
                }
                else{
                    lines[ind][i] = 0;
                }
            }
            memset(line, 0, 256);
            pos = 0;
            ind++;
        }
        else{
            if(line[pos] == '.') {
                line[pos] = 1;
            }
            pos += 1;
        }
    }
    for(int i = 0; i < ind; i++) {
        int8_t* line = lines[i];
        for(int j = 0; j < lineLen; j++) {
            if(line[j] == 1) {
                line[j] = numOfRolls(lines, i, j, ind, lineLen) + 1;
            }
        }
    }
    int curr = 0;
    for(int i = 0; i < ind; i++){
        for(int j = 0; j < lineLen; j++){
            if(lines[i][j] > 0 && lines[i][j] <= 4){
                lines[i][j] = 0;
                res += 1;
                res += dfs(lines, i, j, ind, lineLen);
            }
        } 
    }
    printf("%d\n", res);
    fclose(file);
    for(int i = 0; i < ind; i++){
        memset(lines[i], 0, lineLen);
        free(lines[i]);
        lines[i] = NULL;
    }
    free(line);
    line = NULL;
    return 0; 
}
