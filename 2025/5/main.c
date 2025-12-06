#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <inttypes.h>

uint64_t sad(char* buffer, int len) {
    uint64_t res = 0;
    for(int i = len; i >= 0; i--) {
        res += (buffer[i] - '0') * pow(10, len - i);
    }
    return res;
}

int das(char* buffer, uint64_t target) {
    int i = 0;
    int len = log10(target) + 1;
    while(target > 0) {
        buffer[len - i - 1] = '0' + (target % 10);
        target /= 10;
        i++;
    }
    return len;
}

void insertionSort(uint64_t* numbers, int len) {
    for(int i = 1; i < len; i++) {
        for(int j = i; j >= 0; j--) {
            if( numbers[j] >= numbers[j - 1]) {
                break;
            }
            numbers[j] = numbers[j] ^ numbers[j - 1];
            numbers[j - 1] = numbers[j] ^ numbers[j - 1];
            numbers[j] = numbers[j] ^ numbers[j - 1];
        }
    }
}

int main(int argc, char** argv) {
    FILE* file = fopen(argv[1], "r");
    if(!file) {
        printf("Cannot open file\n");
        exit(0);
    }
    uint64_t res = 0;
    char* line = (char*)calloc(16,1);
    if(!line) {
        printf("Calloc died");
        exit(0);
    }
    int pos = 0;
    uint64_t start = 0;
    uint64_t end = 0;
    uint64_t starts[256] = {0};
    uint64_t ends[256] = {0};
    int ind = 0;
    while(fread(line + pos, 1, 1, file) && line[0] != '\n') {
        if(line[pos] == '-') {
            pos--;
            start = sad(line, pos);
            pos = -1;
        }
        else if(line[pos] == '\n' && pos != 0) {
            pos --;
            end = sad(line, pos);
            starts[ind] = start;
            ends[ind] = end;
            ind++;
            pos = -1;
        }
        pos++; 
    }
    
    insertionSort(starts, ind);
    insertionSort(ends, ind); 
    
    int num_intervals = 1;
    for(int i = 1; i < ind; i++) {
        if(ends[num_intervals - 1] >= starts[i] && ends[num_intervals - 1] < ends[i]) {
            ends[num_intervals - 1] = ends[i];
        } 
        else if(!(ends[num_intervals - 1] >= ends[i])) {
            ends[num_intervals] = ends[i];
            starts[num_intervals] = starts[i];
            num_intervals++;
        }
    }
    uint64_t part2Res = 0;
    for(int i = 0; i < num_intervals; i++){
        printf("%" PRIu64 "-%" PRIu64 "\n", starts[i], ends[i]);
        part2Res += ends[i] - starts[i] + 1;
    }
    pos = 0;
    while(fread(line + pos, 1, 1, file)) {
        if(line[pos] == '\n' && pos != 0) {
            pos --;
            uint64_t id = sad(line, pos);
            for(int i = 0; i < num_intervals; i++) {
                if(starts[i] <= id && ends[i] >= id) {
                   res++;
                   break;
                }
            } 
            pos = -1;
        }
        pos++; 
    }
    fclose(file);
    memset(line, 0, 15);
    free(line);
    line = NULL;
    printf("%ld\n", num_intervals);
    printf("%ld\n", res);
    printf("%" PRIu64 "\n", part2Res);
    return 0; 
}
