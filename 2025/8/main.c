#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <inttypes.h>

struct Set;

typedef struct Node {
    int x;
    int y;
    int z;
    int setID;
}Node;

typedef struct Edge {
    Node* a;
    Node* b;
    double distance;
} Edge;

typedef struct Set {
   int size;
} Set; 

int sad(char* buffer, int len) {
    int res = 0;
    for(int i = len; i >= 0; i--) {
        res += (buffer[i] - '0') * pow(10, len - i);
    }
    return res;
}

double calculateDistance(Node* a, Node* b) {
    return sqrt(pow((a->x - b->x), 2) + pow((a->y - b->y), 2) + pow((a->z - b->z), 2));
}

void insertionSort(Edge* edges, int len) {
    for(int i = 1; i < len; i++) {
        for(int j = i; j > 0; j--) {
            Edge x = edges[j];
            Edge y = edges[j - 1];
            int dist1 = calculateDistance(x.a, x.b);
            int dist2 = calculateDistance(y.a, y.b);
            if(dist1 > dist2) {
                break;
            }
            edges[j - 1] = x;
            edges[j] = y;
        }
    }
}

void sortEdges(Edge* edges, int start, int end) {
    int len = end - start;
    if(len == 1) {
        return;
    }
    if(len == 2) {
        Edge x = edges[end - 1];
        Edge y = edges[start];
        if(x.distance < y.distance) {
            Edge temp = y;
            edges[start] = x;
            edges[end - 1] = temp;
        }
        return;
    }
    int mid = start + (end - start) / 2;   
    sortEdges(edges, start, mid);
    sortEdges(edges, mid, end);
    Edge* temp = calloc(len, sizeof(Edge));
    if(!temp) {
        printf("Calloc died\n");
        exit(0);
    }
    int pointer1 = start;
    int pointer2 = mid;
    for(int i = 0; i < len; i++) {
        if(pointer1 == mid) {
            temp[i] = edges[pointer2++];
            continue;
        }
        if(pointer2 == end) {
            temp[i] = edges[pointer1++];
            continue;
        }
        if(edges[pointer1].distance < edges[pointer2].distance) {
            temp[i] = edges[pointer1++];
        }
        else {
            temp[i] = edges[pointer2++];
        }
    }
    for(int i = 0; i < len; i++) {
        edges[start + i] = temp[i];
    }
    memset(temp, 0, sizeof(Edge) * len);
    free(temp);
    temp = NULL;
}

void sortSet(Set* sets, int len) {
    for(int i = 1; i < len; i++) {
        for(int j = i; j > 0; j--) {
            Set x = sets[j];
            Set y = sets[j - 1];
            if(x.size > y.size) {
                break;
            }
            sets[j - 1] = x;
            sets[j] = y;
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
    int ind = 0;
    int coords[3] = {0};
    int coordInd = 0;
    Node* nodes = calloc(1000, sizeof(Node));
    Set* sets = calloc(1000, sizeof(Set));
    
    if(!nodes || !sets) {
        printf("Calloc died\n");
        exit(0);
    }
    while(fread(line + pos, 1, 1, file) && line[0] != '\n') {
        if(line[pos] == ',') {
            pos--;
            coords[coordInd] = sad(line, pos);
            coordInd++;
            pos = -1;
        }
        else if(line[pos] == '\n' && pos != 0) {
            pos --;
            coords[coordInd] = sad(line, pos);
            Node node = {coords[0], coords[1], coords[2], ind};
            Set set = {1};
            memcpy(nodes + ind, &node, sizeof(Node));
            sets[ind] = set;
            ind++;
            coordInd = 0;
            pos = -1;
        }
        pos++; 
    }

    Edge* edges = calloc(ind * (ind - 1) / 2, sizeof(Edge));
    if(!edges) {
        printf("Calloc died");
        exit(0);
    }
    int edgeInd = 0;
    for(int i = 0; i < ind; i++) {
        for(int j = i + 1; j < ind; j++){
            double distance = calculateDistance(&nodes[i], &nodes[j]);
            Edge edge = {&nodes[i], &nodes[j], distance};
            edges[edgeInd] = edge;
            edgeInd++;
        }
    }
    sortEdges(edges, 0, edgeInd);
    insertionSort(edges, edgeInd);
    long res2 = 0;
    int part1 = 0;
    int i = -1;
    while(1){
        i++;
        if(part1 && i == 1000) {
            break;
        }
        Edge edge = edges[i];
        int aID = edge.a->setID;
        int bID = edge.b->setID;
        Set a = sets[aID];
        Set b = sets[bID];
        if(edge.a->setID == edge.b->setID) {
            continue;
        }
        else if(a.size > b.size) {
            sets[bID].size += sets[aID].size;
            sets[aID].size = -1;
            for(int j = 0; j < ind; j++) {
                if(nodes[j].setID == aID) {
                    nodes[j].setID = bID;
                }
            }
            if(sets[bID].size == ind) {
                printf("%d:%ld\n", edge.a->x, edge.b->x);
                res2 = edge.a->x * edge.b->x;
                break;
            }
        }
        else {
            sets[aID].size += sets[bID].size;
            sets[bID].size = -1;
            for(int j = 0; j < ind; j++) {
                if(nodes[j].setID == bID) {
                    nodes[j].setID = aID;
                }
            }
            if(sets[aID].size == ind) {
                printf("%d:%ld\n", edge.a->x, edge.b->x);
                res2 = edge.a->x * edge.b->x;
                break;
            }
        }
    }
    sortSet(sets, ind);
    res = sets[ind - 1].size * sets[ind - 2].size * sets[ind - 3].size;
    fclose(file);
    memset(line, 0, 15);
    free(line);
    line = NULL;
    printf("%d:%ld\n", res, res2);
    return 0; 
}
