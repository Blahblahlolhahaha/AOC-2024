#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>

int main() {
    FILE* file = fopen("input", "r");
    if(file){
        fseek(file, 0L, SEEK_END);
        long size = ftell(file);
        fseek(file, 0L, SEEK_SET);
        char* input = (char*) malloc(size);
        long max_disk_size = size * 9 * sizeof(long);
        int* disk = (int*) malloc(max_disk_size);
        if(input && disk){
            memset(input, 0, size);
            memset(disk, 0, max_disk_size);
            int read = fread(input,1, size,file);
            if(read){
                int disk_size = 0;
                for(long i = 0; i < size; i++){
                    if(input[i] < 48){
                        continue;
                    }
                    int file_size = input[i] - 48;
                    for(int j = 0; j < file_size; j++){
                        disk[disk_size + j] = (i+1) % 2 == 0 ? -1: i/2;
                    }
                    disk_size += file_size;
                }
                long checksum = 0;
                for(int i = 0; i< disk_size; i++){
                    int id = disk[i];
                    if(id != -1){
                        checksum += id * i;
                        continue;
                    }
                    for(int j = disk_size - 1; j > i;j--){
                        int test = disk[j];
                        if(test != -1){
                            checksum += test * i;
                            disk[j] = -1;
                            break;    
                        }
                    }
                }
                printf("%lu\n",checksum);
            }
            memset(input,0,size);
            free(input);
            input = NULL;
        
            memset(disk,0,max_disk_size);
            free(disk);
            disk = NULL;

        }
        
    }
}
