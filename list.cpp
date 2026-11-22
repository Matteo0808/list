#include <stdio.h>
#include <string.h>
#include <assert.h>

#define LIST_DEBUG
#define DUMP_ALWAYS
#define CONSOLE_OUTPUT_MODE

#define LIST_INSERT_BEFORE_INDEX(list, index, val) ListInsertBeforeIndex((list), (index), (val), (__FILE__), (__FUNCTION__), (__LINE__))
#define LIST_INSERT_AFTER_INDEX(list, index, val) ListInsertAfterIndex((list), (index), (val), (__FILE__), (__FUNCTION__), (__LINE__))
#define LIST_PUSH_HEAD(list, val) ListPushHead((list), (val), (__FILE__), (__FUNCTION__), (__LINE__))
#define LIST_PUSH_TAIL(list, val) ListPushTail((list), (val), (__FILE__), (__FUNCTION__), (__LINE__))
#define LIST_INSERT_BEFORE_ELEM(list, index, val) ListInsertBeforeElem((list), (index), (val), (__FILE__), (__FUNCTION__), (__LINE__))
#define LIST_INSERT_AFTER_ELEM(list, index, val) ListInsertAfterElem((list), (index), (val), (__FILE__), (__FUNCTION__), (__LINE__))
#define LIST_KILL_ELEM_BY_MEMORY_INDEX(list, index) ListKillElemByMemoryIndex((list), (index), (__FILE__), (__FUNCTION__), (__LINE__))
#define LIST_KILL_ELEM_BY_LOGICAL_INDEX(list, index) ListKillElemByLogicalIndex((list), (index), (__FILE__), (__FUNCTION__), (__LINE__))
#define LIST_DUMP(list) ListDump((list), (__FILE__), (__FUNCTION__), (__LINE__))

#ifdef CONSOLE_OUTPUT_MODE
#define CONSOLE_OUTPUT(...) __VA_ARGS__
#else
#define CONSOLE_OUTPUT(...)
#endif

#ifdef LIST_DEBUG
#define LIST_VERIFY(do_dump)    do{\
                                    if(ListVerify(list, do_dump, callFile, callFunc, callLine) != LIST_ERROR_NO_ERROR){\
                                        CONSOLE_OUTPUT(fprintf(stderr, "Verification wasn't passed. Check Dump!\n");)\
                                        return LIST_ERROR_VERIFICATION_FAILED;\
                                    }\
                                }while(0)
#else
#define LIST_VERIFY(do_dump)
#endif

typedef int listElem_t;

const char *const ERROR_COL = "#ff0000";
const char *const EDGE_RED_COL = "#ff0000";
const char *const EDGE_GREEN_COL = "#00ff00";
const char *const DUMMY_COL = "#ffd000";
const char *const HEAD_COL = "#ff6600";
const char *const TAIL_COL ="#ff00bb";
const char *const FIRST_FREE_COL = "#ff92c3";
const char *const FILLED_COL = "#2958ff";
const char *const FREE_COL = "#00ff4c";
const char *const BG_COL = "#c0f3ff";
const char *const SEP_LINE = "____________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________\n\n\n";

const size_t global_minListSize = 10;
const size_t global_Fiasco = 0xF1A5C0;

enum list_returns_t{
    LIST_RETURN_SUCCESS = 0,
    LIST_RETURN_ERROR = 1
};

enum list_errors_t{
    LIST_ERROR_NO_ERROR,
    LIST_ERROR_ALLOCA,
    LIST_ERROR_INDEX_OUT_OF_RANGE,
    LIST_ERROR_INVALID_INDEX,
    LIST_ERROR_VERIFICATION_FAILED,
    LIST_ERROR_LIST_IS_FULL,

};

enum placement_t{
    BEFORE = 0,
    AFTER = 1
};

enum dodump_t{
    DONT_DO_DUMP = 0,
    DO_DUMP = 1    
};
#ifdef DUMP_ALWAYS
    #define DONT_DO_DUMP DO_DUMP
#endif

struct list_t{
    listElem_t *value;
    size_t *next;
    size_t *prev;
    size_t free;
    size_t size;
    size_t capacity;
};

list_errors_t ListConstructor(list_t *list, size_t capacity);
void ListDestructor(list_t *list);

size_t GetNext(const list_t *list, size_t index);
size_t GetPrev(const list_t *list, size_t index);
size_t GetElemByLogicalIndex(const list_t *list, size_t index);

list_errors_t ListInsertBeforeIndex(list_t *list, size_t index, listElem_t val, const char *callFile, const char *callFunc, ssize_t callLine);
list_errors_t ListInsertAfterIndex(list_t *list, size_t index, listElem_t val, const char *callFile, const char *callFunc, ssize_t callLine);
bool CheckMemoryIndex(const list_t *list, size_t index);
list_errors_t ListPushTail(list_t *list, listElem_t val, const char *callFile, const char *callFunc, ssize_t callLine);
list_errors_t ListPushHead(list_t *list, listElem_t val, const char *callFile, const char *callFunc, ssize_t callLine);
list_errors_t ListInsertBeforeElem(list_t *list, size_t index, listElem_t val, const char *callFile, const char *callFunc, ssize_t callLine);
list_errors_t ListInsertAfterElem(list_t *list, size_t index, listElem_t val, const char *callFile, const char *callFunc, ssize_t callLine);
list_errors_t ListKillElemByMemoryIndex(list_t *list, size_t index, const char *callFile, const char *callFunc, ssize_t callLine);
list_errors_t ListKillElemByLogicalIndex(list_t *list, size_t index, const char *callFile, const char *callFunc, ssize_t callLine);

list_errors_t ListVerify(const list_t *list, dodump_t mode, const char *callFile, const char *callFunc, ssize_t callLine);

void ListPrint(const list_t *list);
void ListFullPrint(const list_t *list);

void ListDump(const list_t *list, const char *callFile, const char *callFunc, ssize_t callLine);
void GetListPng(const list_t *list, char *png_list_fileName);
void GetRealListPng(const list_t *list, char *png_real_list_fileName);
void ListHtmlFileAppend(const list_t *list, const char *png_list_fileName, const char *png_real_list_fileName, const char *callFile, const char *callFunc, ssize_t callLine);
void ListHtmlCreateHead(FILE *fileDump);
void ListHtmlCreateTable(const list_t *list, FILE *fileDump);
const char *GetColor(const list_t *list, size_t i);
const char *GetStatus(const list_t *list, size_t i);
const char *GetEdgeColor(const list_t *list, size_t index);
bool IsIndexValid(const list_t *list, size_t index);


//TODO - dir = both DONE
//TODO - table in dump DONE
//TODO - insert second implementation DONE
//TODO - verify DONE
//TODO - defines
//TODO - only 1 dump
//TODO - ebaniy slavic podkinul rabotki
//TODO - remake defines
//TODO - remake enums
//TODO - remake functions all
//TODO - do defines verifies
//TODO - asserts!!
//TODO - errors

int main(){

    list_t list = {};

    ListConstructor(&list, 15);

    LIST_INSERT_AFTER_INDEX(&list, 0, 0);
    LIST_INSERT_AFTER_INDEX(&list, 1, 1);
    LIST_INSERT_AFTER_INDEX(&list, 2, 2);
    LIST_INSERT_AFTER_INDEX(&list, 3, 3);
    LIST_INSERT_AFTER_INDEX(&list, 4, 4);
    LIST_INSERT_AFTER_INDEX(&list, 5, 5);
    LIST_INSERT_AFTER_INDEX(&list, 6, 6);
    LIST_INSERT_AFTER_INDEX(&list, 7, 7);
    LIST_INSERT_AFTER_INDEX(&list, 8, 8);
    LIST_INSERT_AFTER_INDEX(&list, 9, 9);
    LIST_INSERT_AFTER_INDEX(&list, 10, 10);
    LIST_INSERT_AFTER_INDEX(&list, 11, 11);

    LIST_KILL_ELEM_BY_MEMORY_INDEX(&list, 4);
    LIST_KILL_ELEM_BY_MEMORY_INDEX(&list, 7);

    list.prev[8] = 70;


    LIST_DUMP(&list);

    ListDestructor(&list);

    return 0;
}

// why no error?
list_errors_t ListConstructor(list_t *list, size_t capacity){
    assert(list != NULL);

    list->value = (listElem_t *)calloc(capacity + 1, sizeof(listElem_t));
    if(list->value == NULL){
        CONSOLE_OUTPUT(fprintf(stderr, "Allocating value array error\n");)
        return LIST_ERROR_ALLOCA;
    }
    list->next = (size_t *)calloc(capacity + 1, sizeof(size_t));
    if(list->next == NULL){
        CONSOLE_OUTPUT(fprintf(stderr, "Allocating next array error\n");)
        free(list->value);
        return LIST_ERROR_ALLOCA;
    }
    list->prev = (size_t *)calloc(capacity + 1, sizeof(size_t));
    if(list->prev == NULL){
        CONSOLE_OUTPUT(fprintf(stderr, "Allocating prev array error\n");)
        free(list->value);
        free(list->next);
        return LIST_ERROR_ALLOCA;
    }
    list->value[0] = 0;
    list->next[0] = 0;
    list->prev[0] = 0;

    for(size_t index = 1; index < capacity + 1; index++){
        if(index == capacity){
            list->value[index] = global_Fiasco;
            list->next[index] = 0;
            list->prev[index] = -1;
            break;
        }
        list->value[index] = global_Fiasco;
        list->next[index] = index + 1;
        list->prev[index] = -1;
    }
    list->free = 1;
    list->size = 0;
    list->capacity = capacity;

    return LIST_ERROR_NO_ERROR;;
}

list_errors_t ListInsertBeforeIndex(list_t *list, size_t index, listElem_t val, const char *callFile, const char *callFunc, ssize_t callLine){
    assert(list != NULL);
    assert(callFile != NULL);
    assert(callFunc != NULL);

    LIST_VERIFY(DONT_DO_DUMP);

    if(!CheckMemoryIndex(list, index)){
        CONSOLE_OUTPUT(fprintf(stderr, "Invalid index for insertion!\n");)
        return LIST_ERROR_INVALID_INDEX;
    }
    if(list->size >= list->capacity + 1){
        CONSOLE_OUTPUT(fprintf(stderr, "The list is full!\n");)
        return LIST_ERROR_LIST_IS_FULL;
    }

    size_t freeElem = list->free;
    list->free = list->next[freeElem];

    list->next[freeElem] = index;
    list->value[freeElem] = val;
    list->prev[freeElem] = list->prev[index];
    
    list->next[list->prev[index]] = freeElem;
    list->prev[index] = freeElem;
    
    list->size++;

    LIST_VERIFY(DO_DUMP);

    return LIST_ERROR_NO_ERROR;
}

list_errors_t ListInsertAfterIndex(list_t *list, size_t index, listElem_t val, const char *callFile, const char *callFunc, ssize_t callLine){
    assert(list != NULL);
    assert(callFile != NULL);
    assert(callFunc != NULL);

    LIST_VERIFY(DONT_DO_DUMP);

    if(!CheckMemoryIndex(list, index)){
        CONSOLE_OUTPUT(fprintf(stderr, "Invalid index for insertion!\n");)
        return LIST_ERROR_INVALID_INDEX;
    }
    if(list->size >= list->capacity + 1){
        CONSOLE_OUTPUT(fprintf(stderr, "The list is full!\n");)
        return LIST_ERROR_LIST_IS_FULL;
    }

    size_t freeElem = list->free;
    list->free = list->next[freeElem];

    list->prev[freeElem] = index;
    list->value[freeElem] = val;
    list->next[freeElem] = list->next[index];
    
    list->prev[list->next[index]] = freeElem;
    list->next[index] = freeElem;
    
    list->size++;

    LIST_VERIFY(DO_DUMP);

    return LIST_ERROR_NO_ERROR;
}

bool CheckMemoryIndex(const list_t *list, size_t index){
    assert(list != NULL);

    if(((ssize_t)index < 0) || ((ssize_t)index > list->capacity)){
        return false;
    }
    else if(list->prev[index] == -1){
        return false;
    }
    else{
        return true;
    }
}

size_t GetNext(const list_t *list, size_t index){
    return list->next[index];
}

size_t GetPrev(const list_t *list, size_t index){
    return list->prev[index];
}

size_t GetElemByLogicalIndex(const list_t *list, size_t index){
    assert(list != NULL);
    if(((ssize_t)index < 0) || ((ssize_t)index > list->capacity)){
        return -1;
    }

    size_t elem = list->next[0];

    if(index == 0){
        return 0;
    }

    for(size_t i = 1; i < index; i++){
        elem = GetNext(list, elem);
    }
    return elem;
}

list_errors_t ListPushHead(list_t *list, listElem_t val, const char *callFile, const char *callFunc, ssize_t callLine){
    assert(list != NULL);
    assert(callFile != NULL);
    assert(callFunc != NULL);

    list_errors_t err = ListInsertAfterElem(list, 0, val, callFile, callFunc, callLine);
    return err;
}

list_errors_t ListPushTail(list_t *list, listElem_t val, const char *callFile, const char *callFunc, ssize_t callLine){
    assert(list != NULL);
    assert(callFile != NULL);
    assert(callFunc != NULL);

    list_errors_t err = ListInsertBeforeElem(list, 0, val, callFile, callFunc, callLine);
    return err;
}

list_errors_t ListInsertBeforeElem(list_t *list, size_t index, listElem_t val, const char *callFile, const char *callFunc, ssize_t callLine){
    assert(list != NULL);
    assert(callFile != NULL);
    assert(callFunc != NULL);

    LIST_VERIFY(DONT_DO_DUMP);

    
    if(list->size >= list->capacity + 1){
        CONSOLE_OUTPUT(fprintf(stderr, "The list is full!\n");)
        return LIST_ERROR_LIST_IS_FULL;
    }

    size_t elem = GetElemByLogicalIndex(list, index);
    size_t freeElem = list->free;
    list->free = list->next[freeElem];

    list->next[freeElem] = elem;
    list->value[freeElem] = val;
    list->prev[freeElem] = list->prev[elem];
    
    list->next[list->prev[elem]] = freeElem;
    list->prev[elem] = freeElem;
    
    list->size++;

    LIST_VERIFY(DO_DUMP);

    return LIST_ERROR_NO_ERROR;
}

list_errors_t ListInsertAfterElem(list_t *list, size_t index, listElem_t val, const char *callFile, const char *callFunc, ssize_t callLine){
    assert(list != NULL);
    assert(callFile != NULL);
    assert(callFunc != NULL);

    LIST_VERIFY(DONT_DO_DUMP);

    if(list->size >= list->capacity + 1){
        CONSOLE_OUTPUT(fprintf(stderr, "The list is full!\n");)
        return LIST_ERROR_LIST_IS_FULL;
    }

    size_t elem = GetElemByLogicalIndex(list, index);
    size_t freeElem = list->free;
    list->free = list->next[freeElem];

    list->prev[freeElem] = elem;
    list->value[freeElem] = val;
    list->next[freeElem] = list->next[elem];
    
    list->prev[list->next[elem]] = freeElem;
    list->next[elem] = freeElem;
    
    list->size++;

    LIST_VERIFY(DO_DUMP);

    return LIST_ERROR_NO_ERROR;
}

list_errors_t ListKillElemByMemoryIndex(list_t *list, size_t index, const char *callFile, const char *callFunc, ssize_t callLine){
    assert(list != NULL);
    assert(callFile != NULL);
    assert(callFunc != NULL);

    LIST_VERIFY(DONT_DO_DUMP);

    if(index <= 0 || index >= list->capacity){
        CONSOLE_OUTPUT(fprintf(stderr, "Index out of range!\n");)
        return LIST_ERROR_INDEX_OUT_OF_RANGE;
    }
    if(list->prev[index] == -1){
        CONSOLE_OUTPUT(fprintf(stderr, "Invalid index!\n");)
        return LIST_ERROR_INVALID_INDEX;
    }

    list->value[index] = global_Fiasco;

    list->next[list->prev[index]] = list->next[index];
    list->prev[list->next[index]] = list->prev[index];

    list->next[index] = list->free;
    list->free = index;

    list->prev[index] = -1;
    list->size--;

    LIST_VERIFY(DO_DUMP);

    return LIST_ERROR_NO_ERROR;
}

list_errors_t ListKillElemByLogicalIndex(list_t *list, size_t index, const char *callFile, const char *callFunc, ssize_t callLine){
    assert(list != NULL);
    assert(callFile != NULL);
    assert(callFunc != NULL);

    LIST_VERIFY(DONT_DO_DUMP);

    if(index <= 0 || index >= list->size){
        CONSOLE_OUTPUT(fprintf(stderr, "Index out of range!\n");)
        return LIST_ERROR_INDEX_OUT_OF_RANGE;
    }

    size_t elem = GetElemByLogicalIndex(list, index);

    list->value[elem] = global_Fiasco;

    list->next[list->prev[elem]] = list->next[elem];
    list->prev[list->next[elem]] = list->prev[elem];

    list->next[elem] = list->free;
    list->free = elem;

    list->prev[elem] = -1;
    list->size--;

    LIST_VERIFY(DO_DUMP);

    return LIST_ERROR_NO_ERROR;
}

void ListDestructor(list_t *list){
    if(list == NULL){
        CONSOLE_OUTPUT(fprintf(stderr, "List was already destroyed\n");)
        return;
    }

    list->free = global_Fiasco;
    list->size = global_Fiasco;
    list->capacity = global_Fiasco;

    free(list->value);
    free(list->next);
    free(list->prev);
}

list_errors_t ListVerify(const list_t *list, dodump_t mode, const char *callFile, const char *callFunc, ssize_t callLine){
    assert(callFile != NULL);
    assert(callFunc != NULL);
    if(list == NULL){
        CONSOLE_OUTPUT(fprintf(stderr, "list ptr = NULL!\n");)
        return LIST_ERROR_VERIFICATION_FAILED;
    }

    if((ssize_t)list->size > (ssize_t)list->capacity){
        CONSOLE_OUTPUT(fprintf(stderr, "List size is over list capacity!\n");)
        ListDump(list, callFile, callFunc, callLine);
        return LIST_ERROR_VERIFICATION_FAILED;
    }
    if((ssize_t)list->size < 0){
        CONSOLE_OUTPUT(fprintf(stderr, "Size is below zero!\n");)
        ListDump(list, callFile, callFunc, callLine);
        return LIST_ERROR_VERIFICATION_FAILED;
    }
    if((ssize_t)list->capacity <= 0){
        CONSOLE_OUTPUT(fprintf(stderr, "Capacity is below zero!\n");)
        return LIST_ERROR_VERIFICATION_FAILED;
    }
    for(size_t i = 0; i < list->size; i++){
        size_t elem1 = GetElemByLogicalIndex(list, i);
        size_t elem2 = GetElemByLogicalIndex(list, i + 1);
        if(list->next[elem1] != elem2 || list->prev[elem2] != elem1){
            CONSOLE_OUTPUT(fprintf(stderr, "Next - prev connection lost\n");)
            ListDump(list, callFile, callFunc, callLine);
            return LIST_ERROR_VERIFICATION_FAILED;
        }
    }

    if(mode == DO_DUMP){
        ListDump(list, callFile, callFunc, callLine);
    }

    return LIST_ERROR_NO_ERROR;
}


//===========================================================DUMP======================================================//

void ListDump(const list_t *list, const char *callFile, const char *callFunc, ssize_t callLine){
    assert(list != NULL);
    assert(callFile != NULL);
    assert(callFunc != NULL);

    static char png_list_fileName[64] = "";
    static char png_real_list_fileName[64] = "";

    GetListPng(list, png_list_fileName);
    GetRealListPng(list, png_real_list_fileName);

    ListHtmlFileAppend(list, png_list_fileName, png_real_list_fileName, callFile, callFunc, callLine);
}

void GetListPng(const list_t *list, char *png_list_fileName){
    assert(list != NULL);
    assert(png_list_fileName != NULL);

    static size_t dumpListCounter = 0;
    dumpListCounter++;

    static char dot_list_fileName[128] = "";
    static char cmd[128] = "";

    sprintf(dot_list_fileName, "dots\\dump_list_%d.dot", dumpListCounter);
    sprintf(png_list_fileName, "pngs\\dump_list_%d.png", dumpListCounter);

    FILE *fileDump = fopen(dot_list_fileName, "w");
    if(fileDump == NULL){
        CONSOLE_OUTPUT(fprintf(stderr, "Error in dot file opening\n");)
        return;
    }

    fprintf(fileDump, "digraph G{\n");
    fprintf(fileDump, "\trankdir = LR;\n");
    fprintf(fileDump, "\tbgcolor = \"%s\"\n", BG_COL);
    for(size_t i = 0; i < list->size + 1; i++){
        const char *color = NULL;
        if(i == 0){
            color = DUMMY_COL;
            fprintf(fileDump, 
                    "\tnode0[shape = Mrecord,"
                    "style = filled,"
                    "fillcolor = \"%s\","
                    "label = \"dummy | {index | 0} | {next | %llu} | {prev | %lld}\"];\n",
                    color, list->next[0], list->prev[0]);
            continue;
        }
        size_t elem = GetElemByLogicalIndex(list, i);
        if(!IsIndexValid(list, elem)){
            CONSOLE_OUTPUT(fprintf(stderr, "Was gotten invalid index!!\n");)
            // break;
            for(size_t j = 0; j < i - 1; j++){
                fprintf(fileDump, "\tnode%llu->node%llu[style = invis, weight = 100];\n", j, list->next[j]);
            }

            for(size_t j = 0; j < i - 1; j++){
                fprintf(fileDump, "\tnode%llu:e->node%llu:w[dir = both];\n", j, j + 1);
            }
            fprintf(fileDump, "}");
            fclose(fileDump);

            sprintf(cmd, "dot -Tpng %s -o %s", dot_list_fileName, png_list_fileName);
            system(cmd);
            return;
        }
        color = GetColor(list, elem);
        fprintf(fileDump,
                "\tnode%llu[shape = Mrecord,"
                "style = filled,"
                "fillcolor = \"%s\","
                "label = \"%d | {index | %llu} | {next | %llu} | {prev | %lld}\"];\n",
                i, color, list->value[elem], elem, list->next[elem], list->prev[elem]);
    }

    for(size_t i = 0; i < list->size; i++){
        fprintf(fileDump, "\tnode%llu->node%llu[style = invis, weight = 100];\n", i, list->next[i]);
    }

    for(size_t i = 0; i < list->size + 1; i++){
        if(i == list->size){
            fprintf(fileDump, "\tnode%llu:s->node0:s[dir = both];\n", i);                                  
            break;
        }
        fprintf(fileDump, "\tnode%llu:e->node%llu:w[dir = both];\n", i, i + 1);
    }


    fprintf(fileDump, "}");
    fclose(fileDump);

    sprintf(cmd, "dot -Tpng %s -o %s", dot_list_fileName, png_list_fileName);
    system(cmd);
}

void GetRealListPng(const list_t *list, char *png_real_list_fileName){
    assert(list != NULL);
    assert(png_real_list_fileName != NULL);

    static int dumpRealListCounter = 0;
    dumpRealListCounter++;

    static char dot_real_list_fileName[128] = "";
    static char cmd[128] = "";

    sprintf(dot_real_list_fileName, "dots\\dump__real_list_%d.dot", dumpRealListCounter);
    sprintf(png_real_list_fileName, "pngs\\dump_real_list_%d.png", dumpRealListCounter);


    FILE *fileDump = fopen(dot_real_list_fileName, "w");
    if(fileDump == NULL){
        CONSOLE_OUTPUT(fprintf(stderr, "Error in dot file opening\n");)
        return;
    }

    fprintf(fileDump, "digraph G{\n");
    fprintf(fileDump, "\trankdir = LR;\n");
    fprintf(fileDump, "\tbgcolor = \"%s\"\n", BG_COL);
    for(size_t i = 0; i < list->capacity + 1; i++){
        const char *color = GetColor(list, i);
        if(color == ERROR_COL){
            const char *edgeColorNext = NULL;
            const char *edgeColorPrev = NULL;
            if(((ssize_t)(list->next[i]) < 0) || ((ssize_t)(list->next[i])) > (ssize_t)(list->capacity)){
                edgeColorNext = EDGE_RED_COL;
            }
            else{
                edgeColorNext = EDGE_GREEN_COL;
            }
            if(((ssize_t)(list->prev[i]) < -1) || ((ssize_t)(list->prev[i]) > (ssize_t)(list->capacity))){
                edgeColorPrev = ERROR_COL;
            }
            else{
                edgeColorPrev = FILLED_COL;
            }
            fprintf(fileDump, "\tnode%llu->node%llu[color = \"%s\"];\n", i, list->prev[i], edgeColorPrev);
            fprintf(fileDump, "\tnode%llu->node%llu[color = \"%s\"];\n", i, list->next[i], edgeColorNext);
        }
        if(i == 0){
            fprintf(fileDump, 
                    "\tnode0[shape = Mrecord,"
                    "style = filled,"
                    "fillcolor = \"%s\","
                    "label = \"dummy | {index | 0} | {next | %lld} | {prev | %lld}\"];\n",
                    color, list->next[0], list->prev[0]);
            continue;
        }
        fprintf(fileDump,
                "\tnode%llu[shape = Mrecord,"
                "style = filled,"
                "fillcolor = \"%s\","
                "label = \"%d | {index | %lld} | {next | %lld} | {prev | %lld}\"];\n",
                i, color, list->value[i], i, list->next[i], list->prev[i]);
    }

    for(size_t i = 0; i < list->capacity; i++){
        fprintf(fileDump, "\tnode%llu->node%llu[style = invis, weight = 100];\n", i, i + 1);
    }

    for(size_t i = 0; i < list->capacity + 1; i++){
        const char *edgeColor = GetEdgeColor(list, i);
        if(edgeColor == ERROR_COL){
            
            fprintf(fileDump, "\tnode%llu->node%llu[color = \"%s\"];\n", i, list->next[i], edgeColor);
            continue;
        }
        if(edgeColor == NULL){
            continue;
        }
        if(list->prev[i] == -1 && list->next[i] == 0){
            continue;
        }
        fprintf(fileDump, "\tnode%llu->node%llu[dir = both, color = \"%s\"];\n", i, list->next[i], edgeColor);
    }

    fprintf(fileDump, "}");
    fclose(fileDump);

    sprintf(cmd, "dot -Tpng %s -o %s", dot_real_list_fileName, png_real_list_fileName);
    system(cmd);
}

void ListHtmlFileAppend(const list_t *list, const char *png_list_fileName, const char *png_real_list_fileName, const char *callFile, const char *callFunc, ssize_t callLine){
    assert(list != NULL);
    assert(png_list_fileName != NULL);
    assert(png_real_list_fileName != NULL);
    assert(callFile != NULL);
    assert(callFunc != NULL);
    
    static bool isInitialized = 0;
    const char *html_fileName = "dump.html";    

    if(isInitialized == false){
        FILE *fileDump = fopen(html_fileName, "w");
        if(fileDump == NULL){
            CONSOLE_OUTPUT(fprintf(stderr, "Error in html file opening\n");)
            return;
        }
        ListHtmlCreateHead(fileDump);

        fprintf(fileDump, "<h1>ListDump is working...</h1>\n");
        fprintf(fileDump, "Function was called by %s at %s:%llu\n", callFile, callFunc, callLine);
        fprintf(fileDump, "List size = %llu\n", list->size);
        fprintf(fileDump, "List capacity = %llu\n", list->capacity);
        ListHtmlCreateTable(list, fileDump);
        
        fprintf(fileDump, "<h2>List:</h2>\n");
        fprintf(fileDump, "<img src=%s>\n", png_list_fileName);
        fprintf(fileDump, "<h2>List in memory:</h2>\n");
        fprintf(fileDump, "<img src=%s>\n", png_real_list_fileName);
        fprintf(fileDump, SEP_LINE);

        isInitialized = 1;
        fclose(fileDump);
    }    
    else{
        FILE *fileDump = fopen(html_fileName, "a");
        if(fileDump == NULL){
            CONSOLE_OUTPUT(fprintf(stderr, "Error in html file opening\n");)
            return;
        }

        fprintf(fileDump, "<h1>ListDump is working...</h1>\n");
        fprintf(fileDump, "Function was called by %s at %s:%llu\n", callFile, callFunc, callLine);
        fprintf(fileDump, "List size = %llu\n", list->size);
        fprintf(fileDump, "List capacity = %llu\n", list->capacity);  
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
    assert(fileDump != NULL);

    fprintf(fileDump, "<head>\n");
    fprintf(fileDump, "<title>LIST DUMP</title>\n");
    fprintf(fileDump, "<link rel=\"icon\" href=\"favicon.ico\" sizes=\"32x32\">");
    fprintf(fileDump, "</head>\n\n");
    fprintf(fileDump, "<body style=\"background-color: %s;\">\n", BG_COL);
    fprintf(fileDump, "<pre>\n");
}

void ListHtmlCreateTable(const list_t *list, FILE *fileDump){
    assert(list != NULL);
    assert(fileDump != NULL);

    fprintf(fileDump, "<table border = \"1\">\n");
    fprintf(fileDump, "<thead>\n");
    fprintf(fileDump, "<th>INDEX</th>\n");
    fprintf(fileDump, "<th>VALUE</th>\n");
    fprintf(fileDump, "<th>NEXT</th>\n");
    fprintf(fileDump, "<th>PREV</th>\n");
    fprintf(fileDump, "<th>STATUS</th>\n");
    fprintf(fileDump, "</thead>\n");
    fprintf(fileDump, "<tbody>\n");

    for(size_t i = 0; i < list->capacity + 1; i++){
        const char *status = GetStatus(list, i);
        const char *color = GetColor(list, i);
        fprintf(fileDump, "<tr>\n");
        fprintf(fileDump, "<td style = \"color: %s;\">%llu</td>\n", color, i);
        fprintf(fileDump, "<td style = \"color: %s;\">%d</td>\n", color, list->value[i]);
        fprintf(fileDump, "<td style = \"color: %s;\">%llu</td>\n", color, list->next[i]);
        fprintf(fileDump, "<td style = \"color: %s;\">%lld</td>\n", color, list->prev[i]);
        fprintf(fileDump, "<td style = \"color: %s;\">%s</td>\n", color, status);
        fprintf(fileDump, "</tr>\n");
    }
    fprintf(fileDump, "</tbody>\n");
    fprintf(fileDump, "</table>\n");
}

bool IsIndexValid(const list_t *list, size_t index){
    if((((ssize_t)(list->next[index]) < 0) || ((ssize_t)(list->next[index]) > (ssize_t)(list->capacity))) || (((ssize_t)(list->prev[index]) < -1) || ((ssize_t)(list->prev[index]) > (ssize_t)(list->capacity)))){
        return false;
    }
    else{
        return true;
    }
}

const char *GetColor(const list_t *list, size_t index){
    assert(list != NULL);

    if(!IsIndexValid(list, index)){
        return ERROR_COL;
    }
    else if(index == 0){
        return DUMMY_COL;
    }
    else if(index == list->next[0]){
        return HEAD_COL;
    }
    else if(index == list->prev[0]){
        return TAIL_COL;
    }
    else if(index == list->free){
        return FIRST_FREE_COL;
    }
    else if(list->prev[index] == -1){
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
    else if(index == list->next[0]){
        return "HEAD";
    }
    else if(index == list->prev[0]){
        return "TAIL";
    }
    else if(index == list->free){
        return "FIRST_FREE";
    }
    else if(list->value[index] == global_Fiasco){
        return "FREE";
    }
    else{
        return "FILLED"; 
    }
}

const char *GetEdgeColor(const list_t *list, size_t index){
    if(list->prev[index] == -1){
        return FIRST_FREE_COL;
    }

    if(!IsIndexValid(list, index)){
        return NULL;
    }
    if(list->prev[list->next[index]] != index){
        return EDGE_RED_COL;
    }
    else{
        return EDGE_GREEN_COL;
    }
}

//===========================================================PRINT=====================================================//

void ListPrint(const list_t *list){
    size_t elem = 0;
    printf("[");  
    for(size_t i = 0; i < list->size; i++){
        elem = list->next[elem];
        printf("%d ", list->value[elem]);
    }
    printf("\b]\n");
}

void ListFullPrint(const list_t *list){
    assert(list != NULL);

    ListPrint(list);
    printf("head = %llu\n", list->next[0]);
    printf("tail = %llu\n", list->prev[0]);
    printf("free = %llu\n", list->free);
    printf("size = %llu\n", list->size);
    printf("capacity = %llu\n", list->capacity);

    for(size_t i = 0; i < list->capacity + 1; i++){
        printf("[%llu] value=%d next=%llu prev=%lld\n", i,
               list->value[i],
               list->next[i],
               list->prev[i]);
    }
}