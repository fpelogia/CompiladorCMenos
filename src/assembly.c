#include "assembly.h"


void percorreListaQuad(ListaQuad *lq){
    NoQuad* lq_p = lq->prim;
    while(lq_p->prox != NULL){
        printf("(%s,%s,%s,%s)\n",lq_p->quad->op, lq_p->quad->c1, lq_p->quad->c2, lq_p->quad->c3);
        if(strcmp(lq_p->quad->op, "ADD"))   gera_asm_R(lq_p->quad->op, lq_p->quad->c1, lq_p->quad->c2, lq_p->quad->c3);        
        lq_p = lq_p->prox;
    }
    printf("(%s,%s,%s,%s)\n",lq_p->quad->op, lq_p->quad->c1, lq_p->quad->c2, lq_p->quad->c3);
}
void gera_asm_R(char* op, char* c1, char* c2, char* c3){
    printf("\t%s %s, %s, %s", op, c3, c1, c2);
}
