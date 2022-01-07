#include "definitions.h"

#define RED() printf("\033[1;31m");
#define BLACK() printf("\033[0m");

static char* escopo = "global";
static int argcount = 0;
static int numglobals = 0;
// Guarda dados referentes às funções chamadas
ListaInstrAsm CodAsm;
int gpr[N_GPRS]; // vetor com disponibilidade dos Registradores
//ListaReg reg_escopo[MAX_FUNC_DECL];
char* reg_temp_usado[N_GPRS + 1];
int n_reg_temp_usado = 0;
static int desl_acumulado[MAX_FUNC_DECL];
static int desl_var[MAX_FUNC_DECL][MAX_VARS_TOTAL];
static Pilha pilha_reg_params;

static int num_instr_asm_geradas = 0; // importante
end_abs listaEnderecos[MAX_ENDERECOS];
static int tam_lista_enderecos = 0;

char** CodBin;//código binário
static int tam_cod_bin = 0;

void imprimeTokens(char* nomearq){
    FILE* fc = fopen(nomearq,"r");
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
        char* nome_tok;
        nome_tok = nome_token(rt);
        if(leftover){
            if(rt == ID || rt == NUM){
                printf("\t%d: %s, val= %s\n",numlinha, nome_tok, yytext);
            }else{
                printf("\t%d: %s\n",numlinha, nome_tok);
            }
            leftover = false;
        }
        free(nome_tok);
        do{
            rt = retornaToken();
            nome_tok = nome_token(rt);
            if(rt == EOF ){
                free(nome_tok);
                break;
            }
            else if(numlinha != nlsalva){
                leftover = true;
                free(nome_tok);
                break;
            }
            if(rt == ID || rt == NUM){
                printf("\t%d: %s, val= %s\n",numlinha, nome_tok, yytext);
            }else{
                printf("\t%d: %s\n",numlinha, nome_tok);
            }
            free(nome_tok);
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
    { 
        char* nome_tok;
        switch (arv->tipo.exp) {
        case E_Op:  
          nome_tok = nome_token(arv->atrib.op);
          fprintf(stdout,"Op:%s\n", nome_tok );
          free(nome_tok);
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
    NoQuad *novoNoQ = malloc(sizeof(NoQuad));
    Quad *novaQ = malloc(sizeof(Quad));
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
        }
        lq_p->prox = novoNoQ;
    }else{
        lq->prim = novoNoQ;
    }
}

void imprimeListaQuad(ListaQuad *lq){
    NoQuad* lq_p = lq->prim;
    while(lq_p->prox != NULL){
        printf("(%s,%s,%s,%s)\n",lq_p->quad->op, lq_p->quad->c1, lq_p->quad->c2, lq_p->quad->c3);
        lq_p = lq_p->prox;
    }
    printf("(%s,%s,%s,%s)\n",lq_p->quad->op, lq_p->quad->c1, lq_p->quad->c2, lq_p->quad->c3);
}

void destroiListaQuad(ListaQuad *lq){
    NoQuad* lq_p = lq->prim;
    while(lq_p->prox != NULL){
        NoQuad* aux = lq_p;
        lq_p = lq_p->prox;
        free(aux->quad);
        free(aux);
    }
    lq = NULL;
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

int treg_inverso ( char* tr ){
    int i, count = 0;
    char* string_num = malloc((strlen(tr))*sizeof(char));
    for(i=1;i<strlen(tr);i++){
        string_num[count++] = tr[i];
    }
    string_num[count] = '\0';
    int val = atoi(string_num);
    free(string_num);
    return val;
}

void inicializaListaInstrAsm(ListaInstrAsm *lia){
    lia->prim = NULL;
}

void insereInstrAsm(ListaInstrAsm* lia, TipoAsm tipo, char* nome, int rd, int rs1, int rs2, char* imediato){
    NoInstrAsm *novoNoIASM = malloc(sizeof(NoInstrAsm));
    InstrAsm *novaIASM = malloc(sizeof(InstrAsm));
    novaIASM->tipo = tipo;
    novaIASM->nome = strdup(nome);
    novaIASM->rd = rd;
    novaIASM->rs1 = rs1;
    novaIASM->rs2 = rs2;
    novaIASM->imediato = strdup(imediato);
    novoNoIASM->instr = novaIASM;
    novoNoIASM->prox = NULL;
    
    if(lia->prim != NULL){
        NoInstrAsm* lia_p = lia->prim;
        while(lia_p->prox != NULL){
            lia_p = lia_p->prox;
        }
        lia_p->prox = novoNoIASM;
    }else{
        lia->prim = novoNoIASM;
    }
    num_instr_asm_geradas++;
}


void destroiListaInstrAsm(ListaInstrAsm *lia){
    NoInstrAsm* lia_p = lia->prim;
    while(lia_p->prox != NULL){
        NoInstrAsm* aux = lia_p;
        lia_p = lia_p->prox;
        free(aux->instr);
        free(aux);
    }
    lia = NULL;
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
            return i;
        }
    }
}

void percorreListaQuad(ListaQuad *lq){ 
    int primeira_fun = 1;
    NoQuad* lq_p = lq->prim;
    while(lq_p->prox != NULL){
        //printf("\t\t\t(%s,%s,%s,%s)\n",lq_p->quad->op, lq_p->quad->c1, lq_p->quad->c2, lq_p->quad->c3);

        if(eh_operacao(lq_p->quad->op)){
            gera_asm_operacao(lq_p->quad->op, lq_p->quad->c1, lq_p->quad->c2, lq_p->quad->c3);        
        }
        if(eh_comparacao(lq_p->quad->op)){
            gera_asm_comparacao(lq_p->quad->op, lq_p->quad->c1, lq_p->quad->c2, lq_p->quad->c3);        
        }
        if(strcmp(lq_p->quad->op, "LOAD") == 0){
            gera_asm_LOAD(lq_p->quad->c1, lq_p->quad->c2, lq_p->quad->c3);
            
        }
        if(strcmp(lq_p->quad->op, "FUN") == 0){
            if(primeira_fun){
                printf("%d: jal $aux main\n",num_instr_asm_geradas);
                TipoAsm tipo = J;
                insereInstrAsm(&CodAsm, tipo, "jal", $aux, -1, -1, "main");
                primeira_fun = 0;
            }
            escopo = lq_p->quad->c2;
            gera_asm_FUN(lq_p->quad->c2);
        }

        if(strcmp(lq_p->quad->op, "IFF") == 0){
            gera_asm_IFF(lq_p->quad->c1, lq_p->quad->c2);
        }

        if(strcmp(lq_p->quad->op, "ARG") == 0){
            argcount++; // sinaliza para os próximos LOADs
            gera_asm_ARG(lq_p->quad->c1, lq_p->quad->c2, lq_p->quad->c3);
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

        if(strcmp(lq_p->quad->op, "GOTO") == 0){
            gera_asm_GOTO(lq_p->quad->c1);
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

        if(strcmp(lq_p->quad->op, "PARAM") == 0){
            gera_asm_PARAM(lq_p->quad->c1);
        }

        lq_p = lq_p->prox;
    }
    //printf("\t\t\t(%s,%s,%s,%s)\n",lq_p->quad->op, lq_p->quad->c1, lq_p->quad->c2, lq_p->quad->c3);
    
    int i;
    printf("\n\n====== Lista de Endereços ======\n");
    for(i = 0; i < tam_lista_enderecos; i++){
        printf("Endereço de %s: %d\n", listaEnderecos[i].nome, listaEnderecos[i].endereco);
    }
    printf("================================\n\n");
}

void gera_asm_FUN(char *nome){

    TipoAsm tipo;
    printf("\n%s:\n", nome);

    // registra funcao na lista de endereços, para obter endereco abs depois
    end_abs ea;
    ea.nome = nome;
    ea.endereco = num_instr_asm_geradas;
    listaEnderecos[tam_lista_enderecos++] = ea;

    if(strcmp(nome, "main") == 0 && numglobals == 0){
        printf("%d: addi $sp, $zero, %d\n",num_instr_asm_geradas, 1);
        tipo = I;
        insereInstrAsm(&CodAsm, tipo, "addi", $sp, $zero, -1, "1");
    }else{
        printf("%d: addi $sp, $sp, %d\n",num_instr_asm_geradas, 1);
        tipo = I;
        insereInstrAsm(&CodAsm, tipo, "addi", $sp, $sp, -1, "1");
    }
    printf("%d: add $fp, $zero, $sp\n",num_instr_asm_geradas);
    tipo = R;
    insereInstrAsm(&CodAsm, tipo, "add", $fp, $zero, $sp, "");
    /* fp(0) conterá o endereço da função que chamou (não se aplica p/ main)
     */
}

void gera_asm_END(char* c1){
    // c1: nome da função a ser terminada
    TipoAsm tipo;
    if(strcmp(c1, "main")!=0){
        printf("%d: lw $fp, $fp(0)\n",num_instr_asm_geradas);// fp volta a apontar para o frame da função que chamou
        tipo = I;
        insereInstrAsm(&CodAsm, tipo, "lw", $fp, $fp, -1, "0");

        printf("%d: addi $sp, $fp, -1\n",num_instr_asm_geradas);
        insereInstrAsm(&CodAsm, tipo, "addi", $sp, $fp, -1, "-1");
        printf("%d: jalr $aux, $ra(0)\n",num_instr_asm_geradas);//pula de volta para a função que chamou
        insereInstrAsm(&CodAsm, tipo, "jalr", $aux, $ra, -1, "0");
    }
    tam_lista_escopos--; // [PERIGOSO]
    n_reg_temp_usado = 0;
}

void gera_asm_LAB(char* c1){
    // c1: nome do label a ser criado
    printf("%s:\n", c1);
    end_abs ea;
    ea.nome = c1;
    ea.endereco = num_instr_asm_geradas;
    listaEnderecos[tam_lista_enderecos++] = ea;
}

void gera_asm_GOTO(char* c1){
    // c1: nome do label de destino
    printf("%d: jal $aux %s\n",num_instr_asm_geradas, c1);
    TipoAsm tipo = J;
    insereInstrAsm(&CodAsm, tipo, "jal", $aux, -1, -1, c1);
}

void gera_asm_IFF(char* c1, char* c2){
    // c1: registrador com 0 ou 1 
    // c2: nome do label a saltar caso seja 0
    printf("%d: beq $%s, $zero, %s\n",num_instr_asm_geradas, c1, c2);
    TipoAsm tipo = B;
    insereInstrAsm(&CodAsm, tipo, "beq", -1, treg_inverso(c1), $zero, c2);
}

void gera_asm_STORE(char* c1, char* c2, char* c3){
    // c1: nome da variável
    // c2: registrador com valor
    // c3: (opcional) registrador com o indice
    int desl, eh_global, ie, id;
    TipoAsm tipo;
    id = var_id(c1, escopo, &eh_global)-1;
    if(eh_global){
        ie = 0;
    }else{
        ie = indiceEscopo(escopo);
    }
    desl = desl_var[ie][id];

    if(strcmp(c3, " ")!=0){//vetor
        desl += treg_inverso(c3);
    }
    if(eh_global){
        char* strdesl = malloc(4*sizeof(char));
        if(strcmp(c3, " ")!=0){//vetor
            // uso c3 como base pra somar índice
            printf("%d: sw $%s, $%s(%d)\n",num_instr_asm_geradas, c2, c3, desl);
            tipo = S;
            sprintf(strdesl,"%d",desl);
            insereInstrAsm(&CodAsm, tipo, "sw", -1, treg_inverso(c3), treg_inverso(c2), strdesl);
        }else{
            printf("%d: sw $%s, $zero(%d)\n",num_instr_asm_geradas, c2, desl);
            tipo = S;
            sprintf(strdesl,"%d",desl);
            insereInstrAsm(&CodAsm, tipo, "sw", -1, $zero, treg_inverso(c2), strdesl);
        }
        free(strdesl);
    }else{
        if(strcmp(c3, " ")!=0){//vetor
            // somo deslocamento do índice na base, por estar em registrador
            
            char* strdesl = malloc(4*sizeof(char));
            if(desl <= argcount){// é argumento
                printf("%d: lw $aux, $fp(%d)\n",num_instr_asm_geradas, desl);//define base como valor na memória (referência)
                tipo = I;
                sprintf(strdesl,"%d",desl);
                insereInstrAsm(&CodAsm, tipo, "lw", $aux, $fp, -1, strdesl);
                printf("%d: add $aux, $zero, $%s\n",num_instr_asm_geradas, c3);//soma desl. índice
                tipo = R;
                insereInstrAsm(&CodAsm, tipo, "add", $aux, $zero, treg_inverso(c3), "");
                printf("%d: sw $%s, $aux(0)\n",num_instr_asm_geradas, c2); // para para o registrador de destino
                tipo = S;
                insereInstrAsm(&CodAsm, tipo, "sw", -1, $aux, treg_inverso(c2), "0");
            }else{
                printf("%d: add $aux, $fp, $%s\n",num_instr_asm_geradas, c3);
                tipo = R;
                insereInstrAsm(&CodAsm, tipo, "add", $aux, $fp, treg_inverso(c3), "");
                printf("%d: lw $%s, $aux(%d)\n",num_instr_asm_geradas, c1, desl);
                tipo = I;
                sprintf(strdesl,"%d",desl);
                insereInstrAsm(&CodAsm, tipo, "lw", treg_inverso(c1), $aux, -1, strdesl);
            }
            free(strdesl);
        }else{
            char* strdesl = malloc(4*sizeof(char));
            printf("%d: sw $%s, $fp(%d)\n",num_instr_asm_geradas, c2, desl);
            tipo = S;
            sprintf(strdesl,"%d",desl);
            insereInstrAsm(&CodAsm, tipo, "sw", -1, $fp, treg_inverso(c2), strdesl);
            free(strdesl);
        }
    }
}


void gera_asm_ARG(char* c1, char* c2, char* c3){
    // c1: tipo ("int" ou "int[]")
    // c2: nome 
    // c3: escopo
    if(strcmp(c1, "int")==0){//variavel comum (passagem por valor)
        int eg;
        desl_var[indiceEscopo(escopo)][var_id(c2, escopo, &eg)-1] = desl_acumulado[indiceEscopo(escopo)] + 1;
        desl_acumulado[indiceEscopo(escopo)]++;
        printf("%d: addi $sp, $sp, 1\n",num_instr_asm_geradas);
        TipoAsm tipo = I;
        insereInstrAsm(&CodAsm, tipo, "addi", $sp, $sp, -1, "1");
    }else{// vetor (passagem por referencia)
        int eg;
        desl_var[indiceEscopo(escopo)][var_id(c2, escopo, &eg)-1] = desl_acumulado[indiceEscopo(escopo)] + 1;
        desl_acumulado[indiceEscopo(escopo)]++;
        printf("%d: addi $sp, $sp, 1\n",num_instr_asm_geradas);
        TipoAsm tipo = I;
        insereInstrAsm(&CodAsm, tipo, "addi", $sp, $sp, -1, "1");
    }
}

void gera_asm_RET(char* c1){
    // c1: registrador com valor a ser retornado
    printf("%d: add $rv, $%s, $zero\n",num_instr_asm_geradas, c1);
    TipoAsm tipo = R;
    insereInstrAsm(&CodAsm, tipo, "add", $rv, treg_inverso(c1), $zero, "");
}

void gera_asm_ASSIGN(char* c1, char* c2){
    printf("%d: add $%s, $%s, $zero\n",num_instr_asm_geradas, c1, c2);
    TipoAsm tipo = R;
    insereInstrAsm(&CodAsm, tipo, "add", treg_inverso(c1), treg_inverso(c2), $zero, "");
}

void gera_asm_LOAD(char* c1, char* c2, char* c3){
    // c1: registrador
    // c3: (opcional) registrador contendo o indice
    TipoAsm tipo;
    if(((c2[0] >= 48) && (c2[0] <= 57))&&(c2[0] != '-')){
        // c2 é um número
        printf("%d: addi $%s, $zero, %d\n",num_instr_asm_geradas, c1, atoi(c2));
        TipoAsm tipo = I;
        insereInstrAsm(&CodAsm, tipo, "addi", treg_inverso(c1), $zero, -1, c2);
    }else{
        // c2 é o nome de uma variável
        int desl, eh_global, id, ie;
        id = var_id(c2, escopo, &eh_global)-1;
        if(eh_global){
            ie = 0;
        }else{
            ie = indiceEscopo(escopo);
        }
        desl = desl_var[ie][id];

        char* strdesl = malloc(4*sizeof(char));
        if(eh_global){
            if(strcmp(c3, " ")!=0){//vetor
                // uso c3 como base pra somar índice
                printf("%d: lw $%s, $%s(%d)\n",num_instr_asm_geradas, c1, c3, desl);
                tipo = I;
                sprintf(strdesl,"%d",desl);
                insereInstrAsm(&CodAsm, tipo, "lw", treg_inverso(c1), treg_inverso(c3), -1, strdesl);
            }else{
                printf("%d: lw $%s, $zero(%d)\n",num_instr_asm_geradas, c1, desl);
                tipo = I;
                sprintf(strdesl,"%d",desl);
                insereInstrAsm(&CodAsm, tipo, "lw", treg_inverso(c1), $zero, -1, strdesl);
            }
        }else{
            if(strcmp(c3, " ")!=0){//vetor
                // somo deslocamento do índice na base, por estar em registrador
                if(desl <= argcount){// é argumento
                    printf("%d: lw $aux, $fp(%d)\n",num_instr_asm_geradas, desl);//define base como valor na memória (referência)
                    tipo = I;
                    sprintf(strdesl,"%d",desl);
                    insereInstrAsm(&CodAsm, tipo, "lw", $aux, $fp, -1, strdesl);
                    printf("%d: add $aux, $zero, $%s\n",num_instr_asm_geradas, c3);//soma desl. índice
                    tipo = R;
                    insereInstrAsm(&CodAsm, tipo, "add", $aux, $zero, treg_inverso(c3), "");
                    printf("%d: lw $%s, $aux(0)\n",num_instr_asm_geradas, c1); // passa para o registrador de destino
                    tipo = I;
                    insereInstrAsm(&CodAsm, tipo, "lw", treg_inverso(c1), $aux, -1, "0");
                }else{
                    printf("%d: add $aux, $fp, $%s\n",num_instr_asm_geradas, c3);
                    TipoAsm tipo = R;
                    insereInstrAsm(&CodAsm, tipo, "add", $aux, $fp, treg_inverso(c3), "");
                    printf("%d: lw $%s, $aux(%d)\n",num_instr_asm_geradas, c1, desl);
                    tipo = I;
                    sprintf(strdesl,"%d",desl);
                    insereInstrAsm(&CodAsm, tipo, "lw", treg_inverso(c1), $aux, -1, strdesl);
                }
            }else{
                printf("%d: lw $%s, $fp(%d)\n",num_instr_asm_geradas, c1, desl);
                tipo = I;
                sprintf(strdesl,"%d",desl);
                insereInstrAsm(&CodAsm, tipo, "lw", treg_inverso(c1), $fp, -1, strdesl);
            }
        }
        free(strdesl);
    }
}


void gera_asm_comparacao(char* op, char* c1, char* c2, char* c3){
    TipoAsm tipo;
    if(strcmp(op, "NEQ")==0){
        printf("%d: xor $%s, $%s, $%s\n",num_instr_asm_geradas, c3, c1, c2);
        // xor bit a bit gera 0 caso o valor seja igual
        tipo = R;
        insereInstrAsm(&CodAsm, tipo, "xor", treg_inverso(c3), treg_inverso(c1), treg_inverso(c2), "");
    }
    if(strcmp(op, "EQUAL")==0){
        printf("%d: xnor $%s, $%s, $%s\n",num_instr_asm_geradas, c3, c1, c2);
        tipo = R;
        insereInstrAsm(&CodAsm, tipo, "xnor", treg_inverso(c3), treg_inverso(c1), treg_inverso(c2), "");
    }
    if(strcmp(op, "LT")==0){
        printf("%d: slt $%s, $%s, $%s\n",num_instr_asm_geradas, c3, c1, c2);
        tipo = R;
        insereInstrAsm(&CodAsm, tipo, "slt", treg_inverso(c3), treg_inverso(c1), treg_inverso(c2), "");
    }
    if(strcmp(op, "GEQ")==0){
        printf("%d: slt $%s, $%s, $%s\n",num_instr_asm_geradas, c3, c1, c2);
        tipo = R;
        insereInstrAsm(&CodAsm, tipo, "slt", treg_inverso(c3), treg_inverso(c1), treg_inverso(c2), "");
        printf("%d: addi $aux, $zero, 1\n",num_instr_asm_geradas);
        tipo = I;
        insereInstrAsm(&CodAsm, tipo, "addi", $aux, $zero, -1, "1");
        printf("%d: sub $%s, $aux, $%s\n",num_instr_asm_geradas, c3, c3);
        tipo = R;
        insereInstrAsm(&CodAsm, tipo, "sub", treg_inverso(c3), $aux, treg_inverso(c3), "");
    }
    if(strcmp(op, "LEQ")==0){
        printf("%d: slet $%s, $%s, $%s\n",num_instr_asm_geradas, c3, c1, c2);
        tipo = R;
        insereInstrAsm(&CodAsm, tipo, "slet", treg_inverso(c3), treg_inverso(c1), treg_inverso(c2), "");
    }
    if(strcmp(op, "GT")==0){
        printf("%d: slet $%s, $%s, $%s\n",num_instr_asm_geradas, c3, c1, c2);
        tipo = R;
        insereInstrAsm(&CodAsm, tipo, "slet", treg_inverso(c3), treg_inverso(c1), treg_inverso(c2), "");
        printf("%d: addi $aux, $zero, 1\n",num_instr_asm_geradas);
        TipoAsm tipo = I;
        insereInstrAsm(&CodAsm, tipo, "addi", $aux, $zero, -1, "1");
        printf("%d: sub $%s, $aux, $%s\n",num_instr_asm_geradas, c3, c3);
        tipo = R;
        insereInstrAsm(&CodAsm, tipo, "sub", treg_inverso(c3), $aux, treg_inverso(c3), "");
    }
}

void gera_asm_operacao(char* op, char* c1, char* c2, char* c3){
    if(strcmp(op, "ADD") == 0){
        printf("%d: add $%s, $%s, $%s\n",num_instr_asm_geradas, c3, c1, c2);
        TipoAsm tipo = R;
        insereInstrAsm(&CodAsm, tipo, "add", treg_inverso(c3), treg_inverso(c1), treg_inverso(c2), "");
    }
    if(strcmp(op, "SUB") == 0){
        printf("%d: sub $%s, $%s, $%s\n",num_instr_asm_geradas, c3, c1, c2);
        TipoAsm tipo = R;
        insereInstrAsm(&CodAsm, tipo, "sub", treg_inverso(c3), treg_inverso(c1), treg_inverso(c2), "");
    }
    if(strcmp(op, "MUL") == 0){
        printf("%d: mul $%s, $%s, $%s\n",num_instr_asm_geradas, c3, c1, c2);
        TipoAsm tipo = R;
        insereInstrAsm(&CodAsm, tipo, "mul", treg_inverso(c3), treg_inverso(c1), treg_inverso(c2), "");
    }
    if(strcmp(op, "DIV") == 0){
        printf("%d: div $%s, $%s, $%s\n",num_instr_asm_geradas, c3, c1, c2);
        TipoAsm tipo = R;
        insereInstrAsm(&CodAsm, tipo, "div", treg_inverso(c3), treg_inverso(c1), treg_inverso(c2), "");
    }
}

int eh_operacao(char* op){
    return strcmp(op, "ADD") == 0 || strcmp(op, "SUB") == 0  || strcmp(op, "MUL") == 0 || strcmp(op, "DIV") == 0 ; }

int eh_comparacao(char* op){
    return strcmp(op, "LT") == 0 || strcmp(op, "GT") == 0  || strcmp(op, "GEQ") == 0 || strcmp(op, "LEQ") || strcmp(op, "EQUAL")== 0 || strcmp(op, "NEQ") ;
}

void gera_asm_PARAM(char* c1){
    push(&pilha_reg_params, c1);// empilha nome do registrador com o valor dentro
}

void gera_asm_CALL(char* c1, char* c2, char* c3){
    // c1: nome da função
    // c2: número de argumentos
    // c3: (opcional) registrador a ser armazenado

    TipoAsm tipo;

    if(strcmp(c1, "input") == 0){
        printf("%d: jal $ra, input\n",num_instr_asm_geradas);
        tipo = J;
        insereInstrAsm(&CodAsm, tipo, "jal", $ra, -1, -1, "input");
        return;
    }
    if(strcmp(c1, "output") == 0){
        if(atoi(c2) > 0){
            char* par_r = pop(&pilha_reg_params);
            printf("%d: add $aux, $zero, $%s\n",num_instr_asm_geradas, par_r);
            TipoAsm tipo = R;
            insereInstrAsm(&CodAsm, tipo, "add", $aux, $zero, treg_inverso(par_r), "");
        }
        printf("%d: jal $ra, output\n",num_instr_asm_geradas);
        tipo = J;
        insereInstrAsm(&CodAsm, tipo, "jal", $ra, -1, -1, "output");
        if(strcmp(c3, " ") != 0){
            printf("%d: add $%s, $rv, $zero\n",num_instr_asm_geradas, c3);
            TipoAsm tipo = R;
            insereInstrAsm(&CodAsm, tipo, "add", treg_inverso(c3), $rv, $zero,  "");
        }
        return;
    }

    int count = 1, n_regs, ie, i;
    ie = indiceEscopo(escopo);

    char* str = malloc(4*sizeof(char));
    char* qtdreg = malloc(4*sizeof(char));

    sprintf(qtdreg,"%d",n_reg_temp_usado);
    tipo = I;
    insereInstrAsm(&CodAsm, tipo, "addi", $sp, $sp, -1, qtdreg);

    free(qtdreg);
    
    //preenche valor para  argumentos
    tipo = S;
    char* reg_param;
    int num_parametros = atoi(c2);
    for (i = 0; i < num_parametros; i++){
        reg_param = pop(&pilha_reg_params);
        printf("%d: sw $%s, $sp(%d)\n",num_instr_asm_geradas, reg_param, 1 + num_parametros - i);
        sprintf(str,"%d",1 + num_parametros - i);
        insereInstrAsm(&CodAsm, tipo, "sw", -1, $sp, treg_inverso(reg_param), str);
    }

    printf("%d: sw $fp, $sp(1)\n",num_instr_asm_geradas);// armazena valor do fp de quem chamou... pra ser recuperado dps
    insereInstrAsm(&CodAsm, tipo, "sw", -1, $sp, $fp, "1");
    printf("%d: jal $ra, %s\n",num_instr_asm_geradas, c1);// no lugar do nome, enviar endereço relativo (conta com linhas)
    tipo = J;
    insereInstrAsm(&CodAsm, tipo, "jal", $ra, -1, -1, c1);

    free(str);

    if(strcmp(c3," ")!=0){ // armazenar resultado no reg c3
        printf("%d: add $%s, $rv, $zero\n",num_instr_asm_geradas, c3);
        TipoAsm tipo = R;
        insereInstrAsm(&CodAsm, tipo, "add", treg_inverso(c3), $rv, $zero, "");
    }
}

void gera_asm_ALLOC(char* c1, char* c2, char* c3){

    if(strcmp(c2, "global") == 0){
        numglobals++;
    }
    if(strcmp(c3, " ") == 0) {
        int eg;
        desl_var[indiceEscopo(escopo)][var_id(c1, escopo, &eg)-1] = desl_acumulado[indiceEscopo(escopo)] + 1;
        desl_acumulado[indiceEscopo(escopo)]++;
        TipoAsm tipo = I;
        if(numglobals == 1){
            printf("%d: addi $sp, $zero, 1\n",num_instr_asm_geradas);
            insereInstrAsm(&CodAsm, tipo, "addi", $sp, $zero, -1, "1");
        }else{
            printf("%d: addi $sp, $sp, 1\n",num_instr_asm_geradas);
            insereInstrAsm(&CodAsm, tipo, "addi", $sp, $sp, -1, "1");
        }
    }else{// vetor
        int eg;
        desl_var[indiceEscopo(escopo)][var_id(c1, escopo, &eg)-1] = desl_acumulado[indiceEscopo(escopo)] + 1;
        desl_acumulado[indiceEscopo(escopo)] += atoi(c3);
        TipoAsm tipo = I;
        if(numglobals == 1){
            printf("%d: addi $sp, $zero, %s\n",num_instr_asm_geradas, c3);
            insereInstrAsm(&CodAsm, tipo, "addi", $sp, $zero, -1, c3);
        }else{
            printf("%d: addi $sp, $sp, %s\n",num_instr_asm_geradas, c3);
            insereInstrAsm(&CodAsm, tipo, "addi", $sp, $sp, -1, c3);
        }
    }
}

//================( Gerador de Código Binário )======================

void preencheEnderecosASM_geraBIN(ListaInstrAsm *lia){

    inicializaListaCodBin(num_instr_asm_geradas);
    NoInstrAsm* lia_p = lia->prim;

    int linha_asm = 0;
    while(lia_p->prox != NULL){
        char c = lia_p->instr->imediato[0];
        if((c >= 'a' && c <= 'z') || c == 'L'){
            int i;
            for (i = 0; i < tam_lista_enderecos; i ++){
                printf("Procurando %s !\n", lia_p->instr->imediato);
                if(strcmp(lia_p->instr->imediato, listaEnderecos[i].nome) == 0){
                    char* str_endereco = malloc(10*sizeof(char));
                    sprintf(str_endereco,"%d",listaEnderecos[i].endereco - linha_asm); // relativo
                    printf("\t Endereço relativo: %s\n", str_endereco);
                    lia_p->instr->imediato = str_endereco; 
                }
            }

        }
        switch(lia_p->instr->tipo){
            case R:
                gera_bin_R(lia_p->instr);
                break;
            case I:
                gera_bin_I(lia_p->instr);
                break;
            case J:
                gera_bin_J(lia_p->instr);
                break;
            case B:
                gera_bin_B(lia_p->instr);
                break;
            case S:
                gera_bin_B(lia_p->instr);
                // Tipo S gera binário igual o Tipo B
                break;
        }
        lia_p = lia_p->prox;
        linha_asm++;
    }
    char c = lia_p->instr->imediato[0];
    if((c >= 'a' && c <= 'z') || c == 'L'){
        int i;
        for (i = 0; i < tam_lista_enderecos; i ++){
            if(strcmp(lia_p->instr->imediato, listaEnderecos[i].nome) == 0){
                char* str_endereco = malloc(10*sizeof(char));
                sprintf(str_endereco,"%d",listaEnderecos[i].endereco - linha_asm); // relativo
                printf("\t Endereço relativo: %s\n", str_endereco);
            lia_p->instr->imediato = str_endereco; 
        }
    }

}
switch(lia_p->instr->tipo){
    case R:
        gera_bin_R(lia_p->instr);
            break;
        case I:
            gera_bin_I(lia_p->instr);
            break;
        case J:
            gera_bin_J(lia_p->instr);
            break;
        case B:
            gera_bin_B(lia_p->instr);
            break;
        case S:
            gera_bin_B(lia_p->instr);
            // Tipo S gera binário igual o Tipo B
            break;
    }

    printf("\n==> Lista de Instruções Assembly com endereços atualizados! \n");
    printf("==> Código Binário Gerado ! \n\n");
}

// ======================== Geração de Código Binário ===============================
char* converte_n_bin(int x, int n){
    // 30 é maior do que qualquer campo
    char str[30] = {'\0'};
    char* inv = calloc(30, sizeof(char));
    int tam = 0;
    int negativo = (x < 0);

    x = (x >= 0)?x:-x; // x = |x|

    while(x >= 2){
        if(x%2 == 0)
            str[tam++] = '0';
        else
            str[tam++] = '1';
        x /= 2;
    }
    
    if(x == 0){
        str[tam] = '0';
    }else{
        str[tam] = '1';
    }

    int i, extra = n - tam - 1;
    for(i = 0; i < extra; i ++){
        inv[i] = '0';
    }
    for(i = 0; i <= tam; i ++){
        inv[extra + i] = str[tam - i];
    }

    // lógica do compl. de 2 : se negativo, inverter bits e somar 1
    if(negativo){
        for(i = 0; i < strlen(inv); i ++){
            if(inv[i] == '0'){
                inv[i] = '1';
            }else{
                inv[i] = '0';
            }
        }
        tam = strlen(inv);
        if(inv[tam] == '0')
            inv[tam] = '1';
        else{
            int temp = tam-1;
            while(inv[temp] != '0'){
                inv[temp] = '0';
                temp--;
            }
            inv[temp] = '1';
        }
    }
    return inv;
}

void gera_bin_R(InstrAsm* instr){
    char * binstr;
    char * instr_bin = calloc(34, sizeof(char));
    // f7 rs2 rs1 f3 rd opcode
    binstr = converte_n_bin(opcode_f3_f7(instr->nome, c_f7), 7);
    strcat(instr_bin, binstr);
    free(binstr);

    binstr = converte_n_bin(instr->rs2, 5);
    strcat(instr_bin, binstr);
    free(binstr);

    binstr = converte_n_bin(instr->rs1, 5);
    strcat(instr_bin, binstr);
    free(binstr);

    binstr = converte_n_bin(opcode_f3_f7(instr->nome, c_f3), 3);
    strcat(instr_bin, binstr);
    free(binstr);

    binstr = converte_n_bin(instr->rd, 5);
    strcat(instr_bin, binstr);
    free(binstr);

    binstr = converte_n_bin(51, 7);
    strcat(instr_bin, binstr);
    free(binstr);

    CodBin[tam_cod_bin++] = instr_bin;
}

void gera_bin_I(InstrAsm* instr){
    char * binstr;
    char * instr_bin = calloc(34, sizeof(char));
    // imed(12) rs1 f3 rd opcode

    binstr = converte_n_bin(atoi(instr->imediato), 12);
    strcat(instr_bin, binstr);
    free(binstr);

    binstr = converte_n_bin(instr->rs1, 5);
    strcat(instr_bin, binstr);
    free(binstr);

    binstr = converte_n_bin(opcode_f3_f7(instr->nome, c_f3), 3);
    strcat(instr_bin, binstr);
    free(binstr);

    binstr = converte_n_bin(instr->rd, 5);
    strcat(instr_bin, binstr);
    free(binstr);

    binstr = converte_n_bin(opcode_f3_f7(instr->nome, c_op), 7);
    strcat(instr_bin, binstr);
    free(binstr);

    CodBin[tam_cod_bin++] = instr_bin;
}

void gera_bin_J(InstrAsm* instr){
    char * binstr;
    char * instr_bin = calloc(34, sizeof(char));
    // imed(20) rd opcode

    binstr = converte_n_bin(atoi(instr->imediato), 20);
    strcat(instr_bin, binstr);
    free(binstr);

    binstr = converte_n_bin(instr->rd, 5);
    strcat(instr_bin, binstr);
    free(binstr);

    binstr = converte_n_bin(opcode_f3_f7(instr->nome, c_op), 7);
    strcat(instr_bin, binstr);
    free(binstr);

    CodBin[tam_cod_bin++] = instr_bin;
}

void gera_bin_B(InstrAsm* instr){
    char * binstr, *aux;
    char * instr_bin = calloc(34, sizeof(char));
    // imed(7) rs2 rs1 f3 imed(5) opcode

    aux = converte_n_bin(atoi(instr->imediato), 12);
    binstr = strndup(aux, 7);//primeiros 7 dig. do imediato
    strcat(instr_bin, binstr);
    free(binstr);

    binstr = converte_n_bin(instr->rs2, 5);
    strcat(instr_bin, binstr);
    free(binstr);

    binstr = converte_n_bin(instr->rs1, 5);
    strcat(instr_bin, binstr);
    free(binstr);
    
    binstr = converte_n_bin(opcode_f3_f7(instr->nome, c_f3), 3);
    strcat(instr_bin, binstr);
    free(binstr);

    binstr = strndup(aux+7, 5);//ultimos 5 dig. do imediato
    strcat(instr_bin, binstr);
    free(binstr);

    binstr = converte_n_bin(opcode_f3_f7(instr->nome, c_op), 7);
    strcat(instr_bin, binstr);
    free(binstr);

    CodBin[tam_cod_bin++] = instr_bin;
}

void inicializaListaCodBin(int tam){
    CodBin = malloc(tam*sizeof(char*));
}
void imprimeCodBin(){
    int i;
    for(i=0;i<tam_cod_bin;i++){
        printf("%d: %s\n", i, CodBin[i]);
        fprintf(arq_cod_bin, "%s\n",CodBin[i]);
        free(CodBin[i]);
    }
}

// de acordo com campo, a função pode retornar
// opcode, funct3 ou funct7 da instrucao
int opcode_f3_f7(char* nome, int campo){
    //nome: nome da instrução
//========================= Tipo R ====================
    if(strcmp(nome, "add")==0){
        switch(campo){
            case c_op:
                return 51;
                break;
            case c_f3:
                return 0;
                break;
            case c_f7:
                return 0;
                break;
            default:
                Erro = 1;
                break;
        }
    }else if(strcmp(nome, "sub")==0){
        switch(campo){
            case c_op:
                return 51;
                break;
            case c_f3:
                return 0;
                break;
            case c_f7:
                return 32;
                break;
            default:
                Erro = 1;
                break;
        }
    }else if(strcmp(nome, "slt")==0){
        switch(campo){
            case c_op:
                return 51;
                break;
            case c_f3:
                return 2;
                break;
            case c_f7:
                return 0;
                break;
            default:
                Erro = 1;
                break;
        }
    }else if(strcmp(nome, "slet")==0){
        switch(campo){
            case c_op:
                return 51;
                break;
            case c_f3:
                return 2;
                break;
            case c_f7:
                return 32;
                break;
            default:
                Erro = 1;
                break;
        }
    }else if(strcmp(nome, "mul")==0){
        switch(campo){
            case c_op:
                return 51;
                break;
            case c_f3:
                return 1;
                break;
            case c_f7:
                return 0;
                break;
            default:
                Erro = 1;
                break;
        }
    }else if(strcmp(nome, "div")==0){
        switch(campo){
            case c_op:
                return 51;
                break;
            case c_f3:
                return 1;
                break;
            case c_f7:
                return 32;
                break;
            default:
                Erro = 1;
                break;
        }
    }else if(strcmp(nome, "xor")==0){
        switch(campo){
            case c_op:
                return 51;
                break;
            case c_f3:
                return 4;
                break;
            case c_f7:
                return 0;
                break;
            default:
                Erro = 1;
                break;
        }
    }else if(strcmp(nome, "xnor")==0){
        switch(campo){
            case c_op:
                return 51;
                break;
            case c_f3:
                return 4;
                break;
            case c_f7:
                return 32;
                break;
            default:
                Erro = 1;
                break;
        }
    //======================= Tipo I ====================
    }else if(strcmp(nome, "addi")==0){
        switch(campo){
            case c_op:
                return 19;
                break;
            case c_f3:
                return 0;
                break;
            default:
                Erro = 1;
                break;
        }
    }else if(strcmp(nome, "jalr")==0){
        switch(campo){
            case c_op:
                return 103;
                break;
            case c_f3:
                return 0;
                break;
            default:
                Erro = 1;
                break;
        }
    }else if(strcmp(nome, "lw")==0){
        switch(campo){
            case c_op:
                return 3;
                break;
            case c_f3:
                return 2;
                break;
            default:
                Erro = 1;
                break;
        }
   // ======================= Tipo B ====================
    }else if(strcmp(nome, "beq")==0){
        switch(campo){
            case c_op:
                return 99;
                break;
            case c_f3:
                return 0;
                break;
            default:
                Erro = 1;
                break;
        }
    //======================= Tipo J ====================
    }else if(strcmp(nome, "jal")==0){
        switch(campo){
            case c_op:
                return 111;
                break;
            default:
                Erro = 1;
                break;
        }
    //======================= Tipo S ====================
    }else if(strcmp(nome, "sw")==0){
        switch(campo){
            case c_op:
                return 35;
                break;
            case c_f3:
                return 2;
            default:
                Erro = 1;
                break;
        }
    }
}

