#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <dir.h>

#define lval list->value
#define lnext list->next
#define lprev list->prev
#define lfree list->free
#define lsize list->size
#define lcapacity list->capacity

typedef int listElem_t;



const size_t global_minListSize = 10;
const size_t global_Fiasco = 0xF1A5C0;



struct list_t{
    listElem_t *value;
    size_t *next;
    size_t *prev;
    size_t free;
    size_t size;
    size_t capacity;
};



size_t Iterate(list_t *list, size_t index);

void ListConstructor(list_t *list, size_t capacity);
void ListDestructor(list_t *list);

void ListPushTail(list_t *list, listElem_t val);
void ListPushHead(list_t *list, listElem_t val);
void ListInsertBefore(list_t *list, size_t index, listElem_t val);
void ListInsertAfter(list_t *list, size_t index, listElem_t val);
void ListKillElem(list_t *list, size_t index);

void ListPrint(list_t *list);
void ListFullPrint(list_t *list);
void ListDump(list_t *list);
void ListHTmlFileAppend(const char *png_fileName);


int main(){

    list_t list = {};

    ListConstructor(&list, global_minListSize);    

    ListPushTail(&list, 10);
    ListDump(&list);
    
    ListPushTail(&list, 20);
    ListDump(&list);    

    ListPushTail(&list, 30);
    ListDump(&list);    

    ListPushHead(&list, 40);
    ListDump(&list);    

    ListPushHead(&list, 50);
    ListDump(&list);    

    ListInsertAfter(&list, 3, 60);
    ListDump(&list);    

    ListInsertBefore(&list, 4, 70);
    ListDump(&list);

    return 0;
}

void ListConstructor(list_t *list, size_t capacity){
    assert(list != NULL);

    lval = (listElem_t *)calloc(capacity + 1, sizeof(listElem_t));
    if(lval == NULL){
        printf("Calloc error\n");
        return;
    }

    lnext = (size_t *)calloc(capacity + 1, sizeof(size_t));
    if(lnext == NULL){
        printf("Calloc next error\n");
        free(lval);
        return;
    }

    lprev = (size_t *)calloc(capacity + 1, sizeof(size_t));
    if(lprev == NULL){
        printf("Calloc prev error\n");
        free(lval);
        free(lnext);
        return;
    }

    lval[0] = 0;
    lnext[0] = 0;
    lprev[0] = 0;

    for(size_t index = 1; index < capacity + 1; index++){
        lval[index] = global_Fiasco;
        lnext[index] = index + 1;
        lprev[index] = index - 1;
        if(index == capacity){
            lval[index] = global_Fiasco;
            lnext[index] = 0;
            lprev[index] = index - 1;
        }
    }
    lfree = 1;
    lsize = 0;
    lcapacity = capacity;
}

size_t Iterate(list_t *list, size_t index){
    assert(list != NULL);
    
    size_t elem = lnext[0];

    if(index == 0){
        return 0;
    }

    for(size_t i = 1; i < index; i++){
        elem = lnext[elem];
    }
    return elem;
}

void ListPushTail(list_t *list, listElem_t val){
    assert(list != NULL);

    ListInsertBefore(list, 0, val);
}

void ListPushHead(list_t *list, listElem_t val){
    assert(list != NULL);

    ListInsertAfter(list, 0, val);
}

void ListInsertBefore(list_t *list, size_t index, listElem_t val){
    assert(list != NULL);

    if(lsize >= lcapacity){
        printf("The list is full!\n Call ResizeUp...\n");
        return;
    }

    size_t elem = Iterate(list, index);
    size_t freeElem = lfree;
    lfree = lnext[freeElem];

    lnext[freeElem] = elem;
    lval[freeElem] = val;
    lprev[freeElem] = lprev[elem];
    
    lnext[lprev[elem]] = freeElem;
    lprev[elem] = freeElem;
    
    lsize++;
}

void ListInsertAfter(list_t *list, size_t index, listElem_t val){
    assert(list != NULL);

    if(lsize >= lcapacity){
        printf("The list is full!\n Call ResizeUp...\n");
        return;
    }

    size_t elem = Iterate(list, index);
    size_t freeElem = lfree;
    lfree = lnext[freeElem];

    lprev[freeElem] = elem;
    lval[freeElem] = val;
    lnext[freeElem] = lnext[elem];
    
    lprev[lnext[elem]] = freeElem;
    lnext[elem] = freeElem;
    
    lsize++;
}

void ListKillElem(list_t *list, size_t index){
    assert(list != NULL);

    if(index >= lsize){
        printf("Index out of range!\n");
        return;
    }

    size_t elem = Iterate(list, index);

    if(elem == lnext[0]){
        lnext[0] = lnext[elem];
    }
    if(elem == lprev[0]){
        lprev[0] = lprev[elem];
    }

    lval[elem] = global_Fiasco;

    lnext[lprev[elem]] = lnext[elem];
    lprev[lnext[elem]] = lprev[elem];

    lnext[elem] = lfree;
    lfree = elem;

    lsize--;
}

void ListDestructor(list_t *list){

    for(size_t index = 0; index < lcapacity + 1; index++){
        lprev[index] = global_Fiasco;
        lval[index] = global_Fiasco;
        lnext[index] = global_Fiasco;
    }

    lfree = global_Fiasco;
    lsize = global_Fiasco;
    lcapacity = global_Fiasco;

    free(lval);
    free(lnext);
    free(lprev);
}

void ListPrint(list_t *list){
    size_t elem = 0;
    printf("[");  
    for(size_t i = 0; i < lsize; i++){
        elem = lnext[elem];
        printf("%d ", lval[elem]);
    }
    printf("\b]\n");
}

void ListFullPrint(list_t *list){
    ListPrint(list);
    
    printf("head = %llu\n", lnext[0]);
    printf("tail = %llu\n", lprev[0]);
    printf("free = %llu\n", lfree);
    printf("size = %llu\n", lsize);
    printf("capacity = %llu\n", lcapacity);

    for(size_t i = 0; i <= lcapacity; i++){
        printf("[%llu] value=%d next=%llu prev=%llu\n", i,
               lval[i],
               lnext[i],
               lprev[i]);
    }
}

void ListDump(list_t *list){

    static int dumpCounter = 0;
    dumpCounter++;

    char dot_fileName[16] = "";
    char png_fileName[16] = "";
    char cmd[64] = "";

    sprintf(dot_fileName, "dots\\dump_%d.dot", dumpCounter);
    sprintf(png_fileName, "pngs\\dump_%d.png", dumpCounter);

    FILE *fileDump = fopen(dot_fileName, "w");
    if(fileDump == NULL){
        printf("Error in dot file opening\n");
        return;
    }

    fputs("digraph G{\n", fileDump);
    fputs("\trankdir = LR;\n", fileDump);
    fputs("\tbgcolor = \"#9debfd\"\n", fileDump);
    for(size_t i = 0; i <= lsize; i++){
        if(i == 0){
            fprintf(fileDump, "\tnode0[shape = Mrecord, style = filled, fillcolor = \"#d4ff00\", label = \"dummy | {index | 0} | {next | %llu} | {prev | %llu}\"];\n",
                    lnext[0], lprev[0]);
            continue;
        }
        size_t elem = Iterate(list, i);
        fprintf(fileDump, "\tnode%llu[shape = Mrecord, style = filled, fillcolor = \"#88fcab\", label = \"%d | {index | %llu} | {next | %llu} | {prev | %llu}\"];\n",
                i, lval[elem], elem, lnext[elem], lprev[elem]);
    }
    for(size_t i = 0; i <= lsize; i++){
        if(i == lsize){
            fprintf(fileDump, "\tnode%llu:s->node0:s;\n", i);
            break;
        }
        fprintf(fileDump, "\tnode%llu:e->node%llu:w;\n", i, i + 1);
    }
    fputs("}", fileDump);

    fclose(fileDump);

    sprintf(cmd, "dot -Tpng %s -o %s", dot_fileName, png_fileName);

    system(cmd);

    ListHTmlFileAppend(png_fileName);
}

void ListHTmlFileAppend(const char *png_fileName){
    
    static bool isInitialized = false;
    const char *html_fileName = "dump.html";

    if(isInitialized == false){
        FILE *fileDump = fopen(html_fileName, "w");
        if(fileDump == NULL){
            printf("Error in html file opening\n");
            return;
        }

        fputs("<head>\n", fileDump);
        fputs("<title>LIST DUMP</title>\n", fileDump);
        fputs("</head>\n\n", fileDump);
        fputs("<body style=\"background-color: #9debfd;\">\n", fileDump);
        fputs("<pre>\n", fileDump);

        fputs("<h2>ListDump is working...</h2>\n", fileDump);
        fprintf(fileDump, "<img src=%s>\n", png_fileName);
        fputs("________________________________________________________________________________________________________________________________________________________________________________________________________________________\n\n\n", fileDump);


        isInitialized = true;

        fclose(fileDump);
    }    
    else{

        FILE *fileDump = fopen(html_fileName, "a");
        if(fileDump == NULL){
            printf("Error in html file opening\n");
            return;
        }

        fputs("<h2>ListDump is working...</h2>\n", fileDump);
        fprintf(fileDump, "<img src=%s>\n", png_fileName);
        fputs("________________________________________________________________________________________________________________________________________________________________________________________________________________________\n\n\n", fileDump);

        fclose(fileDump);
    }    
}