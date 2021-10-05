#include <stdlib.h>
#include <stdio.h>

#define GESTERRP(a,b) if( (a) == NULL ) {b}
#define GESTERRI(a,b) if( !(a) ) {b}

//il nodo della lista generico
typedef struct ln{
    void* el;
    struct ln* next;
    struct ln* prec;
} listNode;
//il tipo lista su cui applicare i metodi implementati
typedef struct l{
    listNode * head;
    listNode * tail;
    int elTot;
    int (*cmpf) (void*, void*);
} list;
//il tipo lista su cui applicare i metodi implementati
typedef struct h{
    list * vettTable;

} hashTable;

//crea una lista, allocandola nello heap, e restituendola al chiamante
list* createList(int (*cmpf) (void*, void*)){
    list* dummy;

    GESTERRP(dummy = malloc(sizeof(list)) , return NULL;)
    dummy->head = NULL;
    dummy->tail = NULL;
    dummy->elTot = 0;
    dummy->cmpf = cmpf;
    return dummy;
}

//debugging
void printList(list* l){

	GESTERRP(l, perror("we ma che fai bimbo"); return;)
    printf("\n" );
	listNode* dummy = l->head;
	while(dummy != NULL){
		printf("%d   ", *((int*)(dummy->el)) );
		dummy = dummy->next;
	}
    printf("\n" );
}



//agggiungi un elemento alla testa della lista, ritorna -1 se fallisce
int addHead(list* l, void* el){
    GESTERRP(l, return -1;)//gestione dell'errore da rivedere
    listNode* dummy;
    GESTERRP(dummy = malloc(sizeof(listNode)), return -1;)


    if(l->head == NULL && l->tail == NULL){

        dummy->next = NULL;
        dummy->prec = NULL;
        dummy->el = el;

        l->head = dummy;
        l->tail = dummy;
        l->elTot += 1;
    }
    else{
        dummy->next = l->head;
        l->head->prec = dummy;

        dummy->prec = NULL;
        dummy->el = el;
        l->head = dummy;
        l->elTot += 1;
    }
    return 0;
}
int addTail(list* l, void* el){
    GESTERRP(l, return -1;)//gestione dell'errore da rivedere
    listNode* dummy;
    GESTERRP(dummy = malloc(sizeof(listNode)), return -1;)


    if(l->head == NULL && l->tail == NULL){

        dummy->next = NULL;
        dummy->prec = NULL;
        dummy->el = el;

        l->head = dummy;
        l->tail = dummy;
        l->elTot += 1;
    }
    else{
        dummy->prec = l->tail;
        l->tail->next = dummy;

        dummy->next = NULL;
        dummy->el = el;
        l->tail = dummy;
        l->elTot += 1;
    }
    return 0;
}
//rimuove dalla testa, dalla coda e generale (che sfrutta gli altri 2 metodi)
//restituisce o l'elemento rimosso (void*) oppure null se non trova l'elemento
void* removeFirst(list* l){

    GESTERRP(l, return NULL;)//non si arresta
    GESTERRP(l->head, return NULL;)
    void* dummy = l->head->el;

    if(l->elTot == 1){
        l->tail = NULL;
    }
    l->head = l->head->next;
    free(l->head->prec);
    l->head->prec = NULL;
    l->elTot -=1;

    return dummy;
}
void* removeLast(list* l){

    GESTERRP(l, return NULL;)//non si arresta
    GESTERRP(l->tail, return NULL;)
    void* dummy = l->tail->el;

    if(l->elTot == 1){
        l->head = NULL;
    }
    l->tail = l->tail->prec;
    free(l->tail->next);
    l->tail->next = NULL;
    l->elTot -=1;

    return dummy;
}
void* removeEl(list* l, void* el){

    GESTERRP(l, return NULL;)//non si arresta
    GESTERRP(l->head, return NULL;)

    if(l->cmpf(l->head->el,el)) return removeFirst(l);
    else if(l->cmpf(l->tail->el,el)) return removeLast(l);
    else{
        listNode* dummy = l->head->next;
        void* ret = NULL;
        while(dummy != NULL && !(l->cmpf(dummy->el, el))) dummy = dummy->next;

        if(dummy != NULL){
            dummy->prec->next = dummy->next;
            dummy->next->prec = dummy->prec;
            ret = dummy->el;

            free(dummy);
        }
        return ret;
    }
}
int freeAll(list* l){
    listNode* dummy;
    while(l->head != NULL){
        dummy = l->head;
        l->head = l->head->next;
        free(dummy->el);
        free(dummy);
    }
    free(l);
    return 0;
}



















