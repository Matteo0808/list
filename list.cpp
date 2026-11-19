#include <stdio.h>
#include <assert.h>

#define lval list->value
#define lnext list->next
#define lprev list->prev
#define lfree list->free
#define lsize list->size
#define lcapacity list->capacity

#define DUMMY_COL "#ffd000"
#define HEAD_COL "#ff6600"
#define TAIL_COL "#ff00bb"
#define FIRST_FREE_COL "#ff92c3"
#define FILLED_COL "#2958ff"
#define FREE_COL "#00ff4c"       //"#987a4b"
#define BG_COL "#c0f3ff"

#define SEP_LINE "________________________________________________________________________________________________________________________________________________________________________________________________________________________\n\n\n"



#define ListInsertBeforeIndex(list, index, val) _ListInsertBeforeIndex(list, index, val, __FILE__, __FUNCTION__, __LINE__)
#define ListInsertAfterIndex(list, index, val) _ListInsertAfterIndex(list, index, val, __FILE__, __FUNCTION__, __LINE__)
#define ListPushHead(list, val) _ListPushHead(list, val, __FILE__, __FUNCTION__, __LINE__)
#define ListPushTail(list, val) _ListPushTail(list, val, __FILE__, __FUNCTION__, __LINE__)
#define ListInsertBeforeElem(list, index, val) _ListInsertBeforeElem(list, index, val, __FILE__, __FUNCTION__, __LINE__)
#define ListInsertAfterElem(list, index, val) _ListInsertAfterElem(list, index, val, __FILE__, __FUNCTION__, __LINE__)
#define ListKillIndex(list, index, val) _ListKillIndex(list, index, __FILE__, __FUNCTION__, __LINE__)
#define ListKillElem(list, index, val) _ListKillElem(list, index, __FILE__, __FUNCTION__, __LINE__)
#define ListDump(list) _ListDump(list, __FILE__, __FUNCTION__, __LINE__)


typedef int listElem_t;

const size_t global_minListSize = 10;
const size_t global_Fiasco = 0xF1A5C0;



enum list_returns_t{
    LIST_RETURN_SUCCESS = 0,
    LIST_RETURN_ERROR = 1
};

enum placement_t{
    BEFORE = 0,
    AFTER = 1
};

enum dodump_t{
    DONT_DO_DUMP = 0,
    DO_DUMP = 1    
};


struct list_t{
    listElem_t *value;
    size_t *next;
    size_t *prev;
    size_t free;
    size_t size;
    size_t capacity;
};



void ListConstructor(list_t *list, size_t capacity);
void ListDestructor(list_t *list);

void _ListInsertBeforeIndex(list_t *list, size_t index, listElem_t val, const char *callFile, const char *callFunc, ssize_t callLine);
void _ListInsertAfterIndex(list_t *list, size_t index, listElem_t val, const char *callFile, const char *callFunc, ssize_t callLine);
bool CheckIndex(const list_t *list, size_t index);

size_t Iterate(const list_t *list, size_t index);
void _ListPushTail(list_t *list, listElem_t val, const char *callFile, const char *callFunc, ssize_t callLine);
void _ListPushHead(list_t *list, listElem_t val, const char *callFile, const char *callFunc, ssize_t callLine);
void _ListInsertBeforeElem(list_t *list, size_t index, listElem_t val, const char *callFile, const char *callFunc, ssize_t callLine);
void _ListInsertAfterElem(list_t *list, size_t index, listElem_t val, const char *callFile, const char *callFunc, ssize_t callLine);
void _ListKillElem(list_t *list, size_t index, const char *callFile, const char *callFunc, ssize_t callLine);

list_returns_t ListVerify(const list_t *list, dodump_t mode, const char *callFile, const char *callFunc, ssize_t callLine);

void ListPrint(const list_t *list);
void ListFullPrint(const list_t *list);

void _ListDump(const list_t *list, const char *callFile, const char *callFunc, ssize_t callLine);
void GetListPng(const list_t *list, char *png_list_fileName);
void GetRealListPng(const list_t *list, char *png_real_list_fileName);
void ListHTmlFileAppend(const list_t *list, const char *png_list_fileName, const char *png_real_list_fileName);
void ListHtmlCreateHead(FILE *fileDump);
void ListHtmlCreateTable(const list_t *list, FILE *fileDump);
const char *GetColor(const list_t *list, size_t i);
const char *GetStatus(const list_t *list, size_t i);


//TODO - dir = both DONE
//TODO - table in dump DONE
//TODO - insert second implementation DONE
//TODO - verify DONE
//TODO - defines
//TODO - only 1 dump

int main(){

    list_t list = {};

    ListConstructor(&list, global_minListSize);

    ListPushTail(&list, 10);

    ListPushTail(&list, 20);

    ListPushHead(&list, 30);

    ListInsertAfterIndex(&list, 1, 40);

    ListInsertAfterIndex(&list, 11, 50);

    ListInsertAfterIndex(&list, 1, 60);

    ListInsertAfterIndex(&list, 1, 70);

    ListInsertAfterIndex(&list, 1, 80);

    ListInsertAfterIndex(&list, 1, 90);

    ListInsertAfterIndex(&list, 1, 100);

    ListInsertAfterIndex(&list, 1, 110);

    ListInsertAfterIndex(&list, 1, 120);

    ListInsertAfterIndex(&list, 1, 130);

    ListInsertAfterIndex(&list, 1, 140);

    ListDestructor(&list);

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
        if(index == capacity){
            lval[index] = global_Fiasco;
            lnext[index] = 0;
            lprev[index] = -1;
            break;
        }
        lval[index] = global_Fiasco;
        lnext[index] = index + 1;
        lprev[index] = -1;
    }
    lfree = 1;
    lsize = 0;
    lcapacity = capacity;
}

void _ListInsertBeforeIndex(list_t *list, size_t index, listElem_t val, const char *callFile, const char *callFunc, ssize_t callLine){
    assert(list != NULL);

    if(ListVerify(list, DO_DUMP, callFile, callFunc, callLine) == LIST_RETURN_ERROR){
        fprintf(stderr, "Verification wasn't passed. Check Dump!\n");
        return;
    }

    if(!CheckIndex(list, index)){
        fprintf(stderr, "Invalid index for insertion!\n");
        return;
    }
    if(lsize >= lcapacity){
        printf("The list is full!\n");
        return;
    }

    size_t freeElem = lfree;
    lfree = lnext[freeElem];

    lprev[freeElem] = index;
    lval[freeElem] = val;
    lnext[freeElem] = lnext[index];
    
    lprev[lnext[index]] = freeElem;
    lnext[index] = freeElem;
    
    lsize++;

    if(ListVerify(list, DONT_DO_DUMP, callFile, callFunc, callLine) == LIST_RETURN_ERROR){
        fprintf(stderr, "Verification wasn't passed. Check Dump!\n");
        return;
    }
}

void _ListInsertAfterIndex(list_t *list, size_t index, listElem_t val, const char *callFile, const char *callFunc, ssize_t callLine){
    assert(list != NULL);

    if(ListVerify(list, DO_DUMP, callFile, callFunc, callLine) == LIST_RETURN_ERROR){
        fprintf(stderr, "Verification wasn't passed. Check Dump!\n");
        return;
    }

    if(!CheckIndex(list, index)){
        fprintf(stderr, "Invalid index for insertion!\n");
        return;
    }
    if(lsize >= lcapacity){
        printf("The list is full!\n");
        return;
    }

    size_t freeElem = lfree;
    lfree = lnext[freeElem];

    lprev[freeElem] = index;
    lval[freeElem] = val;
    lnext[freeElem] = lnext[index];
    
    lprev[lnext[index]] = freeElem;
    lnext[index] = freeElem;
    
    lsize++;

    if(ListVerify(list, DONT_DO_DUMP, callFile, callFunc, callLine) == LIST_RETURN_ERROR){
        fprintf(stderr, "Verification wasn't passed. Check Dump!\n");
        return;
    }
}

bool CheckIndex(const list_t *list, size_t index){
    assert(list != NULL);

    if((index < 0) || (index >= lcapacity)){
        return false;
    }
    else if(lprev[index] == -1){
        return false;
    }
    else{
        return true;
    }

}
size_t Iterate(const list_t *list, size_t index){
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

void _ListPushTail(list_t *list, listElem_t val, const char *callFile, const char *callFunc, ssize_t callLine){
    assert(list != NULL);

    ListInsertBeforeElem(list, 0, val);
}

void _ListPushHead(list_t *list, listElem_t val, const char *callFile, const char *callFunc, ssize_t callLine){
    assert(list != NULL);

    ListInsertAfterElem(list, 0, val);

}

void _ListInsertBeforeElem(list_t *list, size_t index, listElem_t val, const char *callFile, const char *callFunc, ssize_t callLine){
    assert(list != NULL);

    if(ListVerify(list, DO_DUMP, callFile, callFunc, callLine) == LIST_RETURN_ERROR){
        fprintf(stderr, "Verification wasn't passed. Check Dump!\n");
        return;
    }
    
    if(lsize >= lcapacity){
        printf("The list is full!\n");
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

    if(ListVerify(list, DONT_DO_DUMP, callFile, callFunc, callLine) == LIST_RETURN_ERROR){
        fprintf(stderr, "Verification wasn't passed. Check Dump!\n");
        return;
    }
}

void _ListInsertAfterElem(list_t *list, size_t index, listElem_t val, const char *callFile, const char *callFunc, ssize_t callLine){
    assert(list != NULL);

    if(ListVerify(list, DO_DUMP, callFile, callFunc, callLine) == LIST_RETURN_ERROR){
        fprintf(stderr, "Verification wasn't passed. Check Dump!\n");
        return;
    }

    if(lsize >= lcapacity){
        printf("The list is full!\n");
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

    if(ListVerify(list, DONT_DO_DUMP, callFile, callFunc, callLine) == LIST_RETURN_ERROR){
        fprintf(stderr, "Verification wasn't passed. Check Dump!\n");
        return;
    }
}

void _ListKillElem(list_t *list, size_t index, const char *callFile, const char *callFunc, ssize_t callLine){
    assert(list != NULL);

    if(ListVerify(list, DO_DUMP, callFile, callFunc, callLine) == LIST_RETURN_ERROR){
        fprintf(stderr, "Verification wasn't passed. Check Dump!\n");
        return;
    }

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

    if(ListVerify(list, DONT_DO_DUMP, callFile, callFunc, callLine) == LIST_RETURN_ERROR){
        fprintf(stderr, "Verification wasn't passed. Check Dump!\n");        
        return;
    }
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

void ListPrint(const list_t *list){
    size_t elem = 0;
    printf("[");  
    for(size_t i = 0; i < lsize; i++){
        elem = lnext[elem];
        printf("%d ", lval[elem]);
    }
    printf("\b]\n");
}

void ListFullPrint(const list_t *list){
    ListPrint(list);
    
    printf("head = %llu\n", lnext[0]);
    printf("tail = %llu\n", lprev[0]);
    printf("free = %llu\n", lfree);
    printf("size = %llu\n", lsize);
    printf("capacity = %llu\n", lcapacity);

    for(size_t i = 0; i < lcapacity + 1; i++){
        printf("[%llu] value=%d next=%llu prev=%lld\n", i,
               lval[i],
               lnext[i],
               lprev[i]);
    }
}

void _ListDump(const list_t *list, const char *callFile, const char *callFunc, ssize_t callLine){

    char png_list_fileName[64] = "";
    char png_real_list_fileName[64] = "";

    GetListPng(list, png_list_fileName);
    GetRealListPng(list, png_real_list_fileName);

    ListHTmlFileAppend(list, png_list_fileName, png_real_list_fileName);
}

void GetListPng(const list_t *list, char *png_list_fileName){

    static int dumpListCounter = 0;
    dumpListCounter++;

    char dot_list_fileName[64] = "";
    char cmd[64] = "";

    sprintf(dot_list_fileName, "dots\\dump_list_%d.dot", dumpListCounter);
    sprintf(png_list_fileName, "pngs\\dump_list_%d.png", dumpListCounter);

    FILE *fileDump = fopen(dot_list_fileName, "w");
    if(fileDump == NULL){
        printf("Error in dot file opening\n");
        return;
    }

    fputs("digraph G{\n", fileDump);
    fputs("\trankdir = LR;\n", fileDump);
    fputs("\tbgcolor = \"" BG_COL "\"\n", fileDump);
    for(size_t i = 0; i < lsize + 1; i++){
        const char *color = NULL;
        if(i == 0){
            color = DUMMY_COL;
            fprintf(fileDump, "\tnode0[shape = Mrecord, style = filled, fillcolor = \"%s\", label = \"dummy | {index | 0} | {next | %llu} | {prev | %lld}\"];\n",
                    color, lnext[0], lprev[0]);
            continue;
        }
        size_t elem = Iterate(list, i);
        color = GetColor(list, elem);
        fprintf(fileDump, "\tnode%llu[shape = Mrecord, style = filled, fillcolor = \"%s\", label = \"%d | {index | %llu} | {next | %llu} | {prev | %lld}\"];\n",
                i, color, lval[elem], elem, lnext[elem], lprev[elem]);
    }
    for(size_t i = 0; i <= lsize; i++){
        if(i == lsize){
            fprintf(fileDump, "\tnode%llu:s->node0:s[dir = both];\n", i);                                  
            break;
        }
        fprintf(fileDump, "\tnode%llu:e->node%llu:w[dir = both];\n", i, i + 1);
    }
    fputs("}", fileDump);

    fclose(fileDump);

    sprintf(cmd, "dot -Tpng %s -o %s", dot_list_fileName, png_list_fileName);

    system(cmd);
}

void GetRealListPng(const list_t *list, char *png_real_list_fileName){
    static int dumpRealListCounter = 0;
    dumpRealListCounter++;

    char dot_real_list_fileName[64] = "";
    char cmd[64] = "";

    sprintf(dot_real_list_fileName, "dots\\dump__real_list_%d.dot", dumpRealListCounter);
    sprintf(png_real_list_fileName, "pngs\\dump_real_list_%d.png", dumpRealListCounter);

    FILE *fileDump = fopen(dot_real_list_fileName, "w");
    if(fileDump == NULL){
        printf("Error in dot file opening\n");
        return;
    }

    fputs("digraph G{\n", fileDump);
    fputs("\trankdir = LR;\n", fileDump);
    fputs("\tbgcolor = \"" BG_COL "\"\n", fileDump);
    for(size_t i = 0; i <= lcapacity; i++){
        const char *color = GetColor(list, i);
        fprintf(fileDump, "\tnode%llu[shape = Mrecord, style = filled, fillcolor = \"%s\", label = \"%d | {index | %llu} | {next | %llu} | {prev | %lld}\"];\n",
                i, color, lval[i], i, lnext[i], lprev[i]);
    }
    for(size_t i = 0; i <= lcapacity; i++){
        if(i == lcapacity){
            fprintf(fileDump, "\tnode%llu:s->node0:s[dir = both];\n", i);                                  
            break;
        }
        fprintf(fileDump, "\tnode%llu:e->node%llu:w[dir = both];\n", i, i + 1);
    }
    fputs("}", fileDump);

    fclose(fileDump);

    sprintf(cmd, "dot -Tpng %s -o %s", dot_real_list_fileName, png_real_list_fileName);

    system(cmd);
}

void ListHTmlFileAppend(const list_t *list, const char *png_list_fileName, const char *png_real_list_fileName){
    
    static bool isInitialized = false;
    const char *html_fileName = "dump.html";    

    if(isInitialized == false){
        FILE *fileDump = fopen(html_fileName, "w");
        if(fileDump == NULL){
            printf("Error in html file opening\n");
            return;
        }

        ListHtmlCreateHead(fileDump);

        fprintf(fileDump, "<h1>ListDump is working...</h1>\n");
        ListHtmlCreateTable(list, fileDump);
        
        fprintf(fileDump, "<h2>List:</h2>\n");
        fprintf(fileDump, "<img src=%s>\n", png_list_fileName);
        fprintf(fileDump, "<h2>List in memory:</h2>\n");
        fprintf(fileDump, "<img src=%s>\n", png_real_list_fileName);
        fprintf(fileDump, SEP_LINE);

        isInitialized = true;
        fclose(fileDump);
    }    
    else{

        FILE *fileDump = fopen(html_fileName, "a");
        if(fileDump == NULL){
            printf("Error in html file opening\n");
            return;
        }

        fprintf(fileDump, "<h1>ListDump is working...</h1>\n");        
        ListHtmlCreateTable(list, fileDump);

        fprintf(fileDump, "<h2>List:</h2>\n");
        fprintf(fileDump, "<img src=%s>\n", png_list_fileName);
        fprintf(fileDump, "<h2>List in memory:</h2>\n");
        fprintf(fileDump, "<img src=%s>\n", png_real_list_fileName);
        fprintf(fileDump, SEP_LINE);

        fclose(fileDump);
    }
}

void ListHtmlCreateHead(FILE *fileDump){
    fputs("<head>\n", fileDump);
    fputs("<title>LIST DUMP</title>\n", fileDump);
    fputs("<link rel=\"icon\" href=\"favicon.ico\" sizes=\"32x32\">", fileDump);
    fputs("</head>\n\n", fileDump);
    fputs("<body style=\"background-color: " BG_COL ";\">\n", fileDump);
    fputs("<pre>\n", fileDump);
}

void ListHtmlCreateTable(const list_t *list, FILE *fileDump){
    assert(list != NULL);

    fprintf(fileDump, "<table border = \"1\">\n");
    fprintf(fileDump, "<thead>\n");
    fprintf(fileDump, "<th>INDEX</th>\n");
    fprintf(fileDump, "<th>VALUE</th>\n");
    fprintf(fileDump, "<th>NEXT</th>\n");
    fprintf(fileDump, "<th>PREV</th>\n");
    fprintf(fileDump, "<th>STATUS</th>\n");
    fprintf(fileDump, "</thead>\n");
    fprintf(fileDump, "<tbody>\n");

    for(size_t i = 0; i < lcapacity + 1; i++){
        const char *status = GetStatus(list, i);
        const char *color = GetColor(list, i);
        fprintf(fileDump, "<tr>\n");
        fprintf(fileDump, "<td style = \"color: %s;\">%llu</td>\n", color, i);
        fprintf(fileDump, "<td style = \"color: %s;\">%d</td>\n", color, lval[i]);
        fprintf(fileDump, "<td style = \"color: %s;\">%llu</td>\n", color, lnext[i]);
        fprintf(fileDump, "<td style = \"color: %s;\">%lld</td>\n", color, lprev[i]);
        fprintf(fileDump, "<td style = \"color: %s;\">%s</td>\n", color, status);
        fprintf(fileDump, "</tr>\n");
    }
    fprintf(fileDump, "</tbody>\n");
    fprintf(fileDump, "</table>\n");
}

const char *GetColor(const list_t *list, size_t index){
    assert(list != NULL);

    if(index == 0){
        return DUMMY_COL;
    }
    else if(index == lnext[0]){
        return HEAD_COL;
    }
    else if(index == lprev[0]){
        return TAIL_COL;
    }
    else if(index == lfree){
        return FIRST_FREE_COL;
    }
    else if(lprev[index] == -1){
        return FREE_COL;
    }
    else{
        return FILLED_COL; 
    }
}

const char *GetStatus(const list_t *list, size_t index){
    assert(list != NULL);

    if(index == 0){
        return "DUMMY";
    }
    else if(index == lnext[0]){
        return "HEAD";
    }
    else if(index == lprev[0]){
        return "TAIL";
    }
    else if(index == lfree){
        return "FIRST_FREE";
    }
    else if(lval[index] == global_Fiasco){
        return "FREE";
    }
    else{
        return "FILLED"; 
    }
}

list_returns_t ListVerify(const list_t *list, dodump_t mode, const char *callFile, const char *callFunc, ssize_t callLine){
    assert(list != NULL);
    if(mode == DO_DUMP){
        _ListDump(list, callFile, callFunc, callLine);
    }

    if(lsize > lcapacity){
        fprintf(stderr, "List size is over list capacity!\n");
        return LIST_RETURN_ERROR;
    }
    if(lsize < 0){
        fprintf(stderr, "Size is below zero!\n");
        return LIST_RETURN_ERROR;
    }
    if(lcapacity <= 0){
        fprintf(stderr, "Capacity is below zero!\n");
        return LIST_RETURN_ERROR;
    }
    for(size_t i = 0; i < lsize + 1; i++){
        size_t elem1 = Iterate(list, i);
        size_t elem2 = Iterate(list, i + 1);
        if(lnext[elem1] != elem2 || lprev[elem2] != elem1){
            fprintf(stderr, "Next - prev connection lost\n");
            return LIST_RETURN_ERROR;
        }
    }
    return LIST_RETURN_SUCCESS;
}