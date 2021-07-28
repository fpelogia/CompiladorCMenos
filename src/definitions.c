#include "definitions.h"

#define RED() printf("\033[1;31m");
#define BLACK() printf("\033[0m");

static char* escopo = "global";
static int argcount = 0;
static int numglobals = 0;
// Guarda dados referentes às funções chamadas
area_ativacao *listaChamadas;// Lista com as áreas de ativação
ListaInstrAsm CodAsm;
int gpr[N_GPRS]; // vetor com disponibilidade dos Registradores
//ListaReg reg_escopo[MAX_FUNC_DECL];
char* reg_temp_usado[N_GPRS + 1];
int n_reg_temp_usado;//começa como zero



void imprimeTokens(char* nomearq){
    FILE* fc = fopen("sample.c","r");
    if(fc == NULL){
        printf("Falha na leitura do código fonte");
        Erro = 1;
        return;
    }
    char linha[MAX_LINHA];
    bool primeira_vez = true, leftover = false;
    while(1){
        if(fgets(linha, MAX_LINHA, fc) == NULL){
            break;
        }
        if(linha[0] == '\n'){
            if(fgets(linha, MAX_LINHA, fc) == NULL){
                break;
            }
        }

        Token rt;
        int nlsalva;
        if(primeira_vez){
            nlsalva= numlinha + 1;
            primeira_vez = false;
        }else{
            nlsalva = numlinha;
        }
        printf("\n%d: %s", nlsalva, linha);
        if(leftover){
            if(rt == ID || rt == NUM){
                printf("\t%d: %s, val= %s\n",numlinha, nome_token(rt), yytext);
            }else{
                printf("\t%d: %s\n",numlinha, nome_token(rt));
            }
            leftover = false;
        }
        do{
            rt = retornaToken();
            if(rt == EOF ) break;
            else if(numlinha != nlsalva){
                leftover = true;
                
                break;
            }
            if(rt == ID || rt == NUM){
                printf("\t%d: %s, val= %s\n",numlinha, nome_token(rt), yytext);
            }else{
                printf("\t%d: %s\n",numlinha, nome_token(rt));
            }
        }while(1);
    }
    fclose(fc);

}

// Cria e retorna um novo Nó do tipo "Declaração"
NoArvore * novoNoDecl(TipoDecl tipo)
{ NoArvore * no = (NoArvore *) malloc(sizeof(NoArvore));
  int i;
  if (no==NULL)
    fprintf(stderr,"Out of memory error at line %d\n",numlinha);
  else {
    for (i=0;i<MAXFILHOS;i++) no->filho[i] = NULL;
    no->irmao = NULL;
    no->tipo_de_no = TDecl;
    no->tipo.decl = tipo;
    no->numlinha = numlinha;
  }
  return no;
}


// Cria e retorna um novo Nó do tipo "Statement"
NoArvore * novoNoStmt(TipoStmt tipo)
{ NoArvore * t = (NoArvore *) malloc(sizeof(NoArvore));
  int i;
  if (t==NULL)
    fprintf(stderr,"Out of memory error at line %d\n",numlinha);
  else {
    for (i=0;i<MAXFILHOS;i++) t->filho[i] = NULL;
    t->irmao = NULL;
    t->tipo_de_no = TStmt;
    t->tipo.stmt = tipo;
    t->numlinha = numlinha;
  }
  return t;
}

// Cria e retorna um novo Nó do tipo "exp"
NoArvore * novoNoExp(TipoExp tipo)
{ NoArvore * t = (NoArvore *) malloc(sizeof(NoArvore));
  int i;
  if (t==NULL)
    fprintf(stderr,"Out of memory error at line %d\n",numlinha);
  else {
    for (i=0;i<MAXFILHOS;i++) t->filho[i] = NULL;
    t->irmao = NULL;
    t->tipo_de_no = TExp;
    t->tipo.exp = tipo;
    t->numlinha = numlinha;
  }
  return t;
}

char * copiaString(char * s)
{ int n;
  char * t;
  if (s==NULL) return NULL;
  n = strlen(s)+1;
  t = malloc(n);
  if (t==NULL)
    fprintf(stdout,"Sem memória na linha %d\n",numlinha);
  else strcpy(t,s);
  return t;
}

char * retStrTipo(Tipo t){
    if (t == Integer)
        return "int";
    else if( t == Void){
        return "void";
    }else if( t == Array){
        return "int[]";
    }else{
        return "bool";
    }
}


static int indentno = 0;

#define INDENT indentno+=4
#define UNINDENT indentno-=4

static void imprimeEspacos(void)
{ int i;
  for (i=0;i<indentno;i++)
    fprintf(stdout," ");
}

void imprimeArvore( NoArvore * arv )
{ int i;
  INDENT;
  while (arv != NULL) {
    imprimeEspacos();
    if (arv->tipo_de_no==TStmt)
    { switch (arv->tipo.stmt) {
        case S_If:
          fprintf(stdout,"If\n");
          break;
        case S_While:
          fprintf(stdout,"While\n");
          break;
        case S_Atrib:
          fprintf(stdout,"Atribuição\n");
          break;
        case S_Retorno:
          fprintf(stdout,"Retorno\n");
          break;
        case S_Chamada:
          fprintf(stdout,"Chamada da Função %s\n",arv->atrib.nome);
          break;
        default:
          fprintf(stdout,"Tipo desconhecido de Stmt\n");
          break;
      }
    }
    else if (arv->tipo_de_no==TExp)
    { switch (arv->tipo.exp) {
        case E_Op:
          fprintf(stdout,"Op:%s\n", nome_token(arv->atrib.op));
          break;
        case E_Num:
          fprintf(stdout,"Num: %d\n",arv->atrib.val);
          break;
        case E_Id:
          // strcmp retorna 0 quando é igual
          if (strcmp(arv->atrib.nome,"void") == 0){
            fprintf(stdout,"void\n");
          }else if(strcmp(arv->atrib.nome,"sem_local_decl") == 0 || strcmp(arv->atrib.nome,"sem_stmt_lista")==0){
            // nada
          }else{
            fprintf(stdout,"Id: %s\n",arv->atrib.nome);
          }
          break;
        default:
          fprintf(stdout,"Tipo desconhecido de Exp\n");
          break;
      }
    }else if (arv->tipo_de_no==TDecl)
    { switch (arv->tipo.decl) {
        case D_var:
          fprintf(stdout,"Variável %s\n",arv->atrib.nome);
          break;         
        case D_func:
          //if (arv->tipo_c)
          fprintf(stdout,"Função %s\n",arv->atrib.nome);
          //else  
            //fprintf(stdout,"Função %s com tipo de retorno void \n",arv->atrib.nome, arv->tipo_c);
          break;
        case D_Tipo:
          if (arv->tipo_c == Integer)
            fprintf(stdout,"Tipo int\n");
          else if(arv->tipo_c == Array) 
            fprintf(stdout,"Tipo int[]\n");
          else
            fprintf(stdout,"Tipo void\n");
          break;
        default:
          fprintf(stdout,"Tipo desconhecido de Decl\n");
          break;
      }
    }
    else fprintf(stdout,"Tipo desconhecido de Nó\n");
    for (i=0;i<MAXFILHOS;i++){
        imprimeArvore(arv->filho[i]);
    }
    arv = arv->irmao;
  }
  UNINDENT;
}


char* nome_token(Token t){
    char *nome;
    nome = malloc(MAX_TAM_TOKEN*sizeof(char));
    switch(t){
//        case FIMARQ:
  //          strcpy(nome,"fim do arquivo (EOF)");
    //        break;
      //  case ERRO:
        //    strcpy(nome,"Erro !");
          //  break;
        case ELSE:
            strcpy(nome,"ELSE");
            break;
        case IF:
            strcpy(nome,"IF");
            break;
        case INT:
            strcpy(nome,"INT");
            break;
        case RETURN:
            strcpy(nome,"RETURN");
            break;
        case VOID:
            strcpy(nome,"VOID");
            break;
        case WHILE:
            strcpy(nome,"WHILE");
            break;
        case ID:
            strcpy(nome,"ID");
            break;
        case NUM:
            strcpy(nome,"NUM");
            break;
        case IGUAL:
            strcpy(nome,"IGUAL");
            break;
        case IGUALIGUAL:
            strcpy(nome,"IGUALIGUAL");
            break;
        case DIF:
            strcpy(nome,"DIF");
            break;
        case MENOR:
            strcpy(nome,"MENOR");
            break;
        case MAIOR:
            strcpy(nome,"MAIOR");
            break;
        case MENIGUAL:
            strcpy(nome,"MENIGUAL");
            break;
        case MAIIGUAL:
            strcpy(nome,"MAIIGUAL");
            break;
        case MAIS:
            strcpy(nome,"MAIS");
            break;
        case MENOS:
            strcpy(nome,"MENOS");
            break;
        case VEZES:
            strcpy(nome,"VEZES");
            break;
        case DIV:
            strcpy(nome,"DIV");
            break;
        case FECHAPAR:
            strcpy(nome,"FECHAPAR");
            break;
        case ABREPAR:
            strcpy(nome,"ABREPAR");
            break;
        case PVIRG:
            strcpy(nome,"PVIRG");
            break;
        case VIRG:
            strcpy(nome,"VIRG");
            break;
        case ABRECOL:
            strcpy(nome,"ABRECOL");
            break;
        case FECHACOL:
            strcpy(nome,"FECHACOL");
            break;
        case ABRECH:
            strcpy(nome,"ABRECH");
            break;
        case FECHACH:
            strcpy(nome,"FECHACH");
            break;
        case COMENT:
            strcpy(nome,"COMENT");
            break;
        case ESPACO:
            strcpy(nome,"ESPACO");
            break;
        case ENTER:
            strcpy(nome,"ENTER");
            break;
        default:
            strcpy(nome, "OUTRO");
            break;
    }
    return nome;
}
//======================================= PILHA ===============================================
void inicializaPilha(Pilha *P){
    P = malloc(sizeof(Pilha*));
    P->numelementos = 0;
    P->topo = NULL;
}

void push(Pilha *P, char* nome){
    TNome *NomeStr = malloc(sizeof(TNome*));
    NomeStr->nome = strdup(nome);
    NomeStr->abaixo = P->topo;
    P->topo = NomeStr;
    P->numelementos ++;
}

char* pop(Pilha *P){
    char *nome = NULL;
    if (P->numelementos != 0){// pilha não vazia
        nome = strdup(P->topo->nome);
        TNome *topoAntigo;
        topoAntigo = P->topo;
        P->topo = topoAntigo->abaixo;
        P->numelementos --;
        nome = strdup(topoAntigo->nome);
        free(topoAntigo);
    }
    return nome;
}

// =========================== LISTA DE QUADRUPLAS ===============================

void inicializaListaQuad(ListaQuad *lq){
    lq->prim = NULL;
}

void insereQuad(ListaQuad *lq, char *op, char *c1, char *c2, char *c3){
    NoQuad *novoNoQ = malloc(sizeof(NoQuad*));
    Quad *novaQ = malloc(sizeof(Quad*));
    novaQ->op = strdup(op);
    novaQ->c1 = strdup(c1);
    novaQ->c2 = strdup(c2);
    novaQ->c3 = strdup(c3);
    novoNoQ->quad = novaQ;
    novoNoQ->prox = NULL;
    
    if(lq->prim != NULL){
        NoQuad* lq_p = lq->prim;
        while(lq_p->prox != NULL){
            lq_p = lq_p->prox;
            //lq_p->prox = novoNoQ;
        }
        lq_p->prox = novoNoQ;
    }else{
        lq->prim = novoNoQ;
    }
}

void imprimeListaQuad(ListaQuad *lq){
    NoQuad* lq_p = lq->prim;
    while(lq_p->prox != NULL){
        if(strcmp(lq_p->quad->op, "CALL")==0){
            char c1[strlen(lq_p->quad->c1)]; 
            int i;
            for (i = 0; i < strlen(lq_p->quad->c1); i++){
                if(lq_p->quad->c1[i] != '|'){
                    c1[i] = lq_p->quad->c1[i];
                }else{
                    c1[i] = '\0';
                    break;
                }
            } 
            printf("(%s,%s,%s,%s)\n",lq_p->quad->op, c1, lq_p->quad->c2, lq_p->quad->c3);
        }else{
            printf("(%s,%s,%s,%s)\n",lq_p->quad->op, lq_p->quad->c1, lq_p->quad->c2, lq_p->quad->c3);
        }
        lq_p = lq_p->prox;
    }
    printf("(%s,%s,%s,%s)\n",lq_p->quad->op, lq_p->quad->c1, lq_p->quad->c2, lq_p->quad->c3);
}

void destroiListaQuad(ListaQuad *lq){
    NoQuad* lq_p;
    do{
        if(lq->prim == NULL){
            break;
        }
        lq_p = lq->prim;
        while(lq_p->prox != NULL){
            lq_p = lq_p->prox;
        }
        //free(lq_p->quad);
        free(lq_p);
        lq_p = NULL;
    }while(lq_p != NULL);
    if(lq->prim != NULL)
        free(lq->prim);
}
//==================== Gerenciamento de registradores ================================

int usa_registrador(){
    int i = 0;
    //busca pelo primeiro registrador que esteja livre
    for (i = 0; i < N_GPRS; i++)
        if(gpr[i] == 0){// se encontrou
            gpr[i] = 1;// sinaliza utilização
            return i;// retorna índice do registrador
        }
    // se não encontrou, reporta erro
    Erro = 1;
    printf("Erro de síntese: não há registradores disponíveis\n");
    return -1;
}


/*
void inicializa_reg_escopo(){
    int i = 0;
    for (i = 0; i< N_GPRS + 1; i++){
        reg_escopo[i].n_regs = 0;
    }
}
void reporta_tempreg(int n, char* escopo){
    int i = indiceEscopo(escopo);
    reg_escopo[i].reg[reg_escopo[i].n_regs] = n; // reporta uso do registrador
    reg_escopo[i].n_regs++;// incrementa n_regs para escopo
}

void reporta_liberacao_tempreg(int n, char* escopo){
    int ie = indiceEscopo(escopo);
    int i, n_regs = reg_escopo[ie].n_regs, encontrou = 0;
    for (i = 0; i < n_regs; i++){
        if(i == n){
            reg_escopo[ie].reg[reg_escopo[i].n_regs] = n; // reporta uso do registrador
            encontrou = 1;
        }
        if(encontrou && i < n_regs - 1){
            reg_escopo[ie].reg[i] = reg_escopo[ie].reg[i+1];
        }
    }
    reg_escopo[ie].n_regs--;// decrementa n_regs para escopo
}
*/

void libera_registrador(int num){
    gpr[num] = 0; //define como não mais utilizado
    //reporta_liberacao_tempreg(num, escopo);
}

void libera_todos_os_registradores(){
    int i = 0;
    // percorre todos os registradores
    for (i = 0; i < N_GPRS; i++){
        gpr[i] = 0;// libera registrador
        //reporta_liberacao_tempreg(i, escopo);
    }
}

//==================== Geração de Código Assembly ====================================

void inicializaListaInstrAsm(ListaInstrAsm *lia){
    lia->prim = NULL;
}


void destroiListaInstrAsm(ListaInstrAsm *lia){
    // Essa função não está funcionando
    // tentar corrigir depois
    NoInstrAsm* lia_p;
    do{
        if(lia->prim == NULL){
            break;
        }
        lia_p = lia->prim;
        while(lia_p->prox != NULL){
            lia_p = lia_p->prox;
        }
        free(lia_p);
    }while(lia_p != NULL);
    if(lia->prim != NULL)
        free(lia->prim);
}

void registraEscopo(char* escopo){
    lista_escopos[tam_lista_escopos] = escopo; // salva nome da função;
    if(tam_lista_escopos < MAX_FUNC_DECL){
        tam_lista_escopos++;// registra declaração de nova função
    }
}

int indiceEscopo(char* escopo){
    int i = 0;
    for(i = 0; i< tam_lista_escopos; i++){
        if(strcmp(escopo, lista_escopos[i]) == 0){
            return i; // cuidado futuramente, com escopo global....
        }
    }
}

void reporta_reg_temp(char* tr){
    int i, ja_salvo = 0;
    for (i = 0; i < n_reg_temp_usado; i++){
        if(strcmp(tr, reg_temp_usado[i])==0){
            ja_salvo = 1;
            break;
        }
    }
    if(!ja_salvo){// novo registrador
        reg_temp_usado[n_reg_temp_usado++] = tr; 
    }else{
        
    }
}

void percorreListaQuad(ListaQuad *lq){
    int primeira_fun = 1;
    NoQuad* lq_p = lq->prim;
    while(lq_p->prox != NULL){
        if(eh_operacao(lq_p->quad->op))   gera_asm_R(lq_p->quad->op, lq_p->quad->c1, lq_p->quad->c2, lq_p->quad->c3);        
        if(strcmp(lq_p->quad->op, "LOAD") == 0){
            gera_asm_LOAD(lq_p->quad->c1, lq_p->quad->c2, lq_p->quad->c3);
            
        }

        if(strcmp(lq_p->quad->op, "FUN") == 0){
            if(primeira_fun){
                printf("jal $zero main         (obs: pensar no endereço relativo \"antecipado\")\n");//trocar depois para o endereço relativo
                primeira_fun = 0;
            }
            escopo = lq_p->quad->c2;
            gera_asm_FUN(lq_p->quad->c2);
        }

        if(strcmp(lq_p->quad->op, "ARG") == 0){
            argcount++; // sinaliza para os próximos LOADs
        }

        if(strcmp(lq_p->quad->op, "ASSIGN") == 0){
            gera_asm_ASSIGN(lq_p->quad->c1, lq_p->quad->c2);
        }

        if(strcmp(lq_p->quad->op, "STORE") == 0){
            gera_asm_STORE(lq_p->quad->c1, lq_p->quad->c2, lq_p->quad->c3);
        }

        if(strcmp(lq_p->quad->op, "RET") == 0){
            gera_asm_RET(lq_p->quad->c1);
        }

        if(strcmp(lq_p->quad->op, "LAB") == 0){
            gera_asm_LAB(lq_p->quad->c1);
        }

        if(strcmp(lq_p->quad->op, "END") == 0){
            gera_asm_END(lq_p->quad->c1);
        }

        if(strcmp(lq_p->quad->op, "CALL") == 0){
            gera_asm_CALL(lq_p->quad->c1, lq_p->quad->c2, lq_p->quad->c3);
        }

        if(strcmp(lq_p->quad->op, "ALLOC") == 0){
            gera_asm_ALLOC(lq_p->quad->c1, lq_p->quad->c2, lq_p->quad->c3);
        }
        lq_p = lq_p->prox;
    }
    //printf("(%s,%s,%s,%s)\n",lq_p->quad->op, lq_p->quad->c1, lq_p->quad->c2, lq_p->quad->c3);
}

void gera_asm_FUN(char *nome){
    int i;
    /*for (i = 1; i < tam_lista_escopos; i++){
        total_ativacoes += 1 + numlocals[i];//
    }*/
    printf("\n%s:\n", nome);
    if(strcmp(nome, "main") != 0){
        printf("addi $sp, $sp, %d\n", 2);
    }
    printf("addi $fp, $zero, $sp\n");
    /* fp(-1) conterá o endereço da função que chamou (não se aplica p/ main)
     * fp(0) conterá o valor para retorno
     */
}

void gera_asm_END(char* c1){
    // c1: nome da função a ser terminada
    printf("add $fp, $zero, $fp(-1)\n");// fp volta a apontar para o frame da função que chamou
    if(strcmp(c1, "main")==0){
        printf("halt\n");
    }else{
        printf("jalr $zero $ra\n");//pula de volta para a função que chamou
    }
    tam_lista_escopos--; // [PERIGOSO]
    n_reg_temp_usado = 0;
}

void gera_asm_LAB(char* c1){
    // c1: nome do label a ser criado
    printf("%s:\n", c1);
}

void gera_asm_STORE(char* c1, char* c2, char* c3){
    // c1: nome da variável
    // c2: registrador com valor
    // c3: (opcional) indice
    int desl, eh_global;
    desl = var_endereco(c1, escopo, &eh_global);
    if(strcmp(c3, " ")!=0){//vetor
        desl += atoi(c3);
    }
    if(eh_global){
        printf("sw $%s, $zero(%d)\n", c2, desl);
    }else{
        printf("sw $%s, $fp(%d)\n", c2, desl);
    }
}

void gera_asm_RET(char* c1){
    // c1: registrador com valor a ser retornado
    // ideia: simplesmente carrega no endereço de memória que fp carrega
    printf("sw $%s, $fp(0)\n", c1);
}

void gera_asm_ASSIGN(char* c1, char* c2){
    printf("add $%s, $%s, $zero\n", c1, c2);
}

void gera_asm_LOAD(char* c1, char* c2, char* c3){
    // c1: registrador
    // c3: (opcional) indice
    if((c2[0] >= 48) && (c2[0] <= 57)){
        // c2 é um número
        printf("addi $%s, $zero, %d\n", c1, atoi(c2));
    }else if (argcount > 0){ // Carregamento de um argumento
        // c2 é o nome de uma variável
        int desl, eh_global;
        desl = var_endereco(c2, escopo, &eh_global);
        if(strcmp(c3, " ")!=0){//vetor
            desl += atoi(c3);
        }
        printf("lw $%s, $ap(%d)\n", c1, desl);// nesse caso, nunca será global
        argcount--;
    }else{
        // c2 é o nome de uma variável
        int desl, eh_global;
        desl = var_endereco(c2, escopo, &eh_global);
        if(strcmp(c3, " ")!=0){//vetor
            desl += atoi(c3);
        }
        printf("BUSQUEI %s e recebi desl %d\n", c2, desl);
        if(eh_global){
            printf("lw $%s, $zero(%d)\n", c1, desl);
        }else{
            printf("lw $%s, $fp(%d)\n", c1, desl);
        }
    }
    reporta_reg_temp(c1);
}


void gera_asm_R(char* op, char* c1, char* c2, char* c3){
    if(strcmp(op, "ADD") == 0){
        printf("add $%s, $%s, $%s\n", c3, c1, c2);
    }
    if(strcmp(op, "SUB") == 0){
        printf("sub $%s, $%s, $%s\n", c3, c1, c2);
    }
    if(strcmp(op, "MUL") == 0){
        printf("mul $%s, $%s, $%s\n", c3, c1, c2);
    }
    if(strcmp(op, "DIV") == 0){
        printf("div $%s, $%s, $%s\n", c3, c1, c2);
    }
}

int eh_operacao(char* op){
    return strcmp(op, "ADD") == 0 || strcmp(op, "SUB") == 0  || strcmp(op, "MUL") == 0 || strcmp(op, "DIV") == 0 ;
}

void gera_asm_CALL(char* c1, char* c2, char* c3){
    // c1: nome da função | nome escopo
    // c2: número de argumentos
    // c3: (opcional) registrador a ser armazenado
    //char** la
    //cadastraChamada(c1, escopo, NULL); // o terceiro campo pode receber uma lista global preenchida
    int count = 1, n_regs, ie, i;
    ie = indiceEscopo(escopo);
    //n_regs = reg_escopo[ie].n_regs;

    //salva registradores
    for (i = 0; i < n_reg_temp_usado; i++){
        printf("sw %s $sp(%d)\n", reg_temp_usado[i], i+1);
        count++;
    }
    printf("addi $sp, $sp, %d\n", n_reg_temp_usado);
    printf("jal $ra, %s\n", c1);// no lugar do nome, enviar endereço relativo (conta com linhas)
    //restaura registradores
    for (i = 0; i < n_reg_temp_usado; i++){
        printf("lw %s $sp(%d)\n", reg_temp_usado[i], i+1);
        count++;
    }
    printf("addi $sp, $sp, %d\n", -1*n_reg_temp_usado);

    if(strcmp(c3," ")==0){ // armazenar resultado no reg c3
    
    }
}

void gera_asm_ALLOC(char* c1, char* c2, char* c3){

    if(strcmp(c2, "global") == 0){
        numglobals++;
    }
    if(strcmp(c3, " ") == 0) {
        if(numglobals == 1){
            printf("addi $sp, $zero, 1\n");
        }else{
            printf("addi $sp, $sp, 1\n");
        }
    }else{// vetor
        if(numglobals == 1){
            printf("addi $sp, $zero, %s\n", c3);
        }else{
            printf("addi $sp, $sp, %s\n", c3);
        }
    }
}

//===================================================
void cadastraChamada(endereco_m func, endereco_m escopo, variavel* lista_args){
    area_ativacao* lc_p = listaChamadas;
    while(lc_p->prox != NULL){
        lc_p = lc_p->prox;
    }
    area_ativacao* nova_aa = malloc(sizeof(area_ativacao));
    nova_aa->func_fp = func;
    nova_aa->quem_chamou = escopo;
}
