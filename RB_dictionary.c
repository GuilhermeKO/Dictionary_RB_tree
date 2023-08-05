#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h> 

typedef struct NOH {
    char *palavra; 
    struct NOH *next; 
    struct NOH *prev; 
} NOH;

typedef struct LISTA {
    NOH *head;   
} LISTA;

typedef struct NODE {
    char *cor;
    char *letra;
    int nivel;
    struct NODE *esq; 
    struct NODE *dir;
    struct NODE *pai;
    LISTA *lista;
} NODE;

void *cria_lista();
void printa_lista();
void fix_insere_tree();
void fix_deleta_tree();
void LL();
void RR();
void printa_tree();
void free_tree();
NOH *busca_lista();
LISTA *insere_lista();
LISTA *deleta_lista();
NODE *find_raiz();
NODE *min_node();
NODE *transplante();
NODE *busca_tree();
NODE *insere_tree();
NODE *deleta_tree();

int main(){
    NODE *NILL = (NODE*) malloc(sizeof(NODE));
    NILL -> cor = "B";
    
    NODE *raiz = NILL;  
    NODE *aux = NILL;
    char palavra[10000];
    char letra[5];
    int qtd_palavras = 0, qtd_repetidas = 0;

    while(1){
        scanf("%s", palavra);
        letra[0] = toupper(palavra[0]);
        
        if(strcmp(palavra, "0") == 0)
            break;
        ++qtd_palavras;

        aux = busca_tree(raiz, NILL, strdup(letra));
        if(aux == NILL)
            raiz = insere_tree(raiz, NILL, strdup(letra), palavra);
        else {
            NOH *check = NULL;
                check = busca_lista(aux->lista, palavra);
                if(check != NULL)
                    ++qtd_repetidas;
                else
                    aux->lista = insere_lista(aux->lista, palavra);
        }
    }

    printf("Todos os dados foram carregados com sucesso!!\n");
    if(qtd_repetidas != 0)
        printf("Existiram %d palavras repetidas\n", qtd_repetidas);
    printf("Total de %d palavras inseridas no dicionário\n\n", qtd_palavras);   
    
    int comando, flag = 1;

    while(flag){
        puts("*** MENU DE OPÇÕES: ENTRE COM A OPÇÃO DESEJADA ***\n");
        puts("1. Pesquisa");
        puts("2. Inserção");
        puts("3. Remoção");
        puts("4. Impressão de um nó");
        puts("5. Impressão da árvore");
        puts("6. Sair\n");

        scanf("%d", &comando);

        if(comando == 1){
            puts("1");
            puts("Informe a palavra a ser Pesquisada:\n");
            scanf("%s", palavra);
            printf("%s\n", palavra);
            letra[0] = toupper(palavra[0]);
            aux = busca_tree(raiz, NILL, strdup(letra));
            if(aux == NILL)
                puts("Palavra Inexistente!\n");
            else {
                NOH *N = busca_lista(aux->lista, palavra);
                if(N == NULL)
                    puts("Palavra Inexistente!\n");
                else {
                    if(strcmp(aux->cor, "B") == 0)
                        printf("A Palavra '%s' foi encontrada no NÓ '%s' preto nível %d\n\n", palavra, aux->letra, aux->nivel);
                    else
                        printf("A Palavra '%s' foi encontrada no NÓ '%s' vermelho nível %d\n\n", palavra, aux->letra, aux->nivel);
                }
            }   

        } else if(comando == 2){
            puts("2");
            puts("Informe a palavra a ser Inserida:\n");
            scanf("%s", palavra);
            printf("%s\n", palavra);
            letra[0] = toupper(palavra[0]);
            
            aux = busca_tree(raiz, NILL, strdup(letra));
            if(aux == NILL){
                raiz = insere_tree(raiz, NILL, strdup(letra), palavra);
                aux = busca_tree(raiz, NILL, strdup(letra));
                if(strcmp(aux->cor, "B") == 0)
                    printf("A palavra '%s' foi Inserida com sucesso no NÓ '%s' preto nível %d\n\n", palavra, aux->letra, aux->nivel);
                else
                    printf("A palavra '%s' foi Inserida com sucesso no NÓ '%s' vermelho nível %d\n\n", palavra, aux->letra, aux->nivel);
            } else {    
                NOH *check = NULL;
                check = busca_lista(aux->lista, palavra);
                if(check != NULL)
                    printf("A Palavra '%s' já consta no dicionário\n\n", palavra);
                else {
                    aux->lista = insere_lista(aux->lista, palavra);
                    if(strcmp(aux->cor, "B") == 0)
                        printf("A palavra '%s' foi Inserida com sucesso no NÓ '%s' preto nível %d\n\n", palavra, aux->letra, aux->nivel);
                    else
                        printf("A palavra '%s' foi Inserida com sucesso no NÓ '%s' vermelho nível %d\n\n", palavra, aux->letra, aux->nivel);
                }
            }
        
        } else if(comando == 3){
            puts("3");
            puts("Informe a palavra a ser Excluída:\n");
            scanf("%s", palavra);
            printf("%s\n", palavra);
            letra[0] = toupper(palavra[0]);
            
            aux = busca_tree(raiz, NILL, strdup(letra));

            if(aux == NILL)
                printf("A Palavra '%s' não consta no Dicionário\n\n", palavra);
            else {
                NOH *check = aux->lista->head;
                    check = busca_lista(aux->lista, palavra);
                    if(check == NULL) 
                        printf("A Palavra '%s' não consta no Dicionário\n\n", palavra);
                    else {
                        aux->lista = deleta_lista(aux->lista, palavra);
                        if(aux->lista == NULL)
                            raiz = deleta_tree(raiz, NILL, busca_tree(raiz, NILL, letra)); 

                        if(strcmp(aux->cor, "B") == 0)
                        printf("A palavra '%s' foi Excluída com sucesso do NÓ '%s' preto nível %d\n\n", palavra, aux->letra, aux->nivel);
                    else
                        printf("A palavra '%s' foi Excluída com sucesso do NÓ '%s' vermelho nível %d\n\n", palavra, aux->letra, aux->nivel);
                    }
            }

        } else if(comando == 4){
            puts("4");
            puts("Informe o nó que deseja Imprimir(Ou seja, primeira letra.)\n");
            scanf("%s", palavra);
            letra[0] = toupper(palavra[0]);
            printf("%s\n", letra);

            aux = busca_tree(raiz, NILL, strdup(letra));
            if(aux == NILL)
                puts("Nó Inexistente...\n");
            else{
                if(strcmp(aux->cor, "B") == 0)
                    printf("\nA(s) Palavra(s) contida(s) no NÓ '%s' preto nível %d são:\n\n", letra, aux->nivel);
                else
                    printf("\nA(s) Palavra(s) contida(s) no NÓ '%s' vermelho nível %d são:\n\n", letra, aux->nivel);
                
                printa_lista(aux -> lista);
                puts("");
            } 
            
        } else if(comando == 5){
            puts("5");
            puts("Imprimindo Árvore...\n");
            printa_tree(raiz, NILL);
        } else
            flag = 0;
    }
    
    puts("6\nPrograma Encerrado!!");
    free(aux);
    free_tree(raiz, NILL); 

    return 0;
}

void *cria_lista(){
    LISTA *new_lista = (LISTA*) malloc(sizeof(LISTA));
    new_lista->head = NULL;

    return new_lista;
}

NOH *busca_lista(LISTA *lista, char *palavra){
    NOH *aux = lista->head;
    while(aux != NULL){
        if(strcmp(palavra, aux->palavra) == 0)
            return aux;
        aux = aux->next;
    }
    return NULL;
}

LISTA *insere_lista(LISTA *lista, char *palavra){
    NOH *new_node = (NOH*) malloc(sizeof(NOH));
    new_node->palavra = strdup(palavra);

    if(lista->head == NULL){ 
        lista->head = new_node;
        new_node->next = NULL;
        new_node->prev = NULL;
    
    } else {
        if(strcmp(palavra, lista->head->palavra) < 0){ 
            new_node->prev = NULL;
            new_node->next = lista->head;
            lista->head->prev = new_node;
            lista->head = new_node;
        
        } else {    
            NOH *aux = lista->head;
            while(strcmp(palavra, aux->palavra) > 0 && aux->next != NULL)
                aux = aux->next;
            
            if(aux->next == NULL && strcmp(palavra, aux->palavra) > 0){ 
                new_node->next = NULL;
                new_node->prev = aux;
                aux->next = new_node;
            } else { 
                new_node->next = aux;
                new_node->prev = aux->prev;
                aux->prev->next = new_node;
                aux->prev = new_node;
            }
        }
    }
    return lista;
}

LISTA *deleta_lista(LISTA *lista, char *palavra){
    NOH *aux = busca_lista(lista, palavra);
   
    if(aux->prev == NULL && aux->next == NULL){
        lista->head = NULL;
    } else if(aux->prev == NULL && aux->next != NULL){ 
        lista->head = aux->next;
        aux->next->prev = NULL;
    } else if(aux->prev != NULL && aux->next == NULL) 
        aux->prev->next = NULL;
    else { 
        aux->prev->next = aux->next;
        aux->next->prev = aux->prev;
    }

    if(lista->head == NULL)
        return NULL;
    
    free(aux);

    return lista;
}

void printa_lista(LISTA *lista){
    NOH *aux = lista->head;
    if(aux == NULL)
        printf("lista vazia!\n");
    else {
        while(aux->next != NULL){
            printf("%s\n", aux->palavra);
            aux = aux->next;
        }
        printf("%s\n", aux->palavra);
    }
}

int find_nivel(NODE *raiz, NODE *NILL){
    NODE *aux = raiz;
    int cont = 1;
    while(aux->pai != NILL){
        ++cont;
        aux = aux->pai; 
    }
    return cont;
}

NODE *find_raiz(NODE *raiz, NODE *NILL){
    NODE *aux = raiz;
    while(aux->pai != NILL){
        aux = aux->pai;
    }
    return aux;
}

NODE *min_node(NODE *NILL, NODE *a){
    while(a->esq != NILL)
        a = a->esq;

    return a;
}

NODE *transplante(NODE *raiz, NODE *NILL, NODE *a, NODE *b){
    if(a->pai == NILL)
        raiz = b;
    else if(a == a->pai->esq)
        a->pai->esq = b;
    else
        a->pai->dir = b;

    b->pai = a->pai;
    raiz = find_raiz(raiz, NILL);
    return raiz;
}

NODE *busca_tree(NODE *raiz, NODE *NILL, char *letra){
    NODE *aux = raiz;
    int cont = 1;

    while(aux != NILL){
        if(strcmp(letra, aux->letra) < 0){
            aux = aux->esq;
            ++cont;
        } else if(strcmp(letra, aux->letra) > 0){
            aux = aux->dir;
            ++cont;
        } else if(strcmp(letra, aux->letra) == 0){
            aux->nivel = cont;
            return aux;
        }
    }
    return NILL;
}

NODE *insere_tree(NODE *raiz, NODE *NILL, char *letra, char *palavra){
    NODE *v = (NODE*) malloc(sizeof(NODE));
    v->cor = "R";
    v->letra = letra;
    v->esq = NILL;
    v->dir = NILL;

    LISTA *L = cria_lista();
    L = insere_lista(L, palavra);
    v->lista = L;

    NODE *x = raiz;
    NODE *y = NILL;

    while(x != NILL){
        y = x;
        if(strcmp(v->letra, x->letra) <= 0)
            x = x->esq;
        else
            x = x->dir;
    }

    if(y == NILL)
        raiz = v;
    else if(strcmp(v->letra, y->letra) <= 0)
        y->esq = v;
    else
        y->dir = v;

    v->pai = y;

    fix_insere_tree(raiz, NILL, v);
    raiz = find_raiz(raiz, NILL);

    return raiz;
}

void fix_insere_tree(NODE *raiz, NODE *NILL, NODE *v){
    while(strcmp(v->pai->cor, "R") == 0){

        if(v->pai == v->pai->pai->esq){
            if(strcmp(v->pai->pai->dir->cor, "R") == 0){
                v->pai->cor = "B";
                v->pai->pai->dir->cor = "B";
                v->pai->pai->cor = "R";
                v = v->pai->pai; 
            
            } else {
                if(v == v->pai->dir){
                    v = v->pai;
                    LL(raiz, NILL, v);
                }

                v->pai->cor = "B";
                v->pai->pai->cor = "R";
                RR(raiz, NILL, v->pai->pai);
            }
            
        } else { 
            if(strcmp(v->pai->pai->esq->cor, "R") == 0){ 
                v->pai->cor = "B";
                v->pai->pai->esq-> cor = "B";
                v->pai->pai->cor = "R";
                v = v->pai->pai;
            
            } else { 
                if(v == v->pai->esq){
                    v = v->pai;
                    RR(raiz, NILL, v);
                }

                v->pai->cor = "B";
                v->pai->pai->cor = "R";
                LL(raiz, NILL, v->pai->pai);
            }
        }
    }
    raiz = find_raiz(raiz, NILL);
    raiz->cor = "B";
}

NODE *deleta_tree(NODE *raiz, NODE *NILL, NODE *v){
    NODE *y, *x;
    char *cor_original;

    y = v;
    cor_original = y->cor;

    if(v->esq == NILL){
        x = v->dir;
        raiz = transplante(raiz, NILL, v, v->dir);
    } else if(v->dir == NILL){
        x = v->esq;
        raiz = transplante(raiz, NILL, v, v->esq);
    } else {
        y = min_node(NILL, v->dir);
        cor_original = y->cor;

        x = y->dir;

        if(y->pai == v)
            x->pai = y;
        else {
            raiz = transplante(raiz, NILL, y, y->dir);
            y->dir = v->dir;
            y->dir->pai = y;
        }

        raiz = transplante(raiz, NILL, v, y);
        y->esq = v->esq;
        y->esq->pai = y;
        y->cor = v->cor;
    }
    
    if(strcmp(cor_original, "B") == 0)
        fix_deleta_tree(raiz, NILL, x);

    raiz = find_raiz(raiz, NILL);
    return raiz;
}

void fix_deleta_tree(NODE *raiz, NODE *NILL, NODE *x){
    NODE *w;
    while(x != raiz && (strcmp(x->cor, "B") == 0)){

        if(x == x->pai->esq){
            w = x->pai->dir;
            
            if(strcmp(w->cor, "R") == 0){
                w->cor = "B";
                x->pai->cor = "R";
                LL(raiz, NILL, x->pai);
                w = x->pai->dir;
            }

            if((strcmp(w->esq->cor, "B") == 0) && (strcmp(w->dir->cor, "B") == 0)){
                w->cor = "R";
                x->pai->cor = "B";
                x = x->pai;
            } else {
                if(strcmp(w->dir->cor, "B") == 0){
                    w->cor = "R";
                    w->esq->cor = "B";
                    RR(raiz, NILL, w);
                    w = x->pai->dir;
                }

                w->cor = x->pai->cor;
                x->pai->cor = "B";
                x->dir->cor = "B";
                LL(raiz, NILL, x->pai);
                x = raiz;
            }
        
        } else {
            w = x->pai->esq;

            if(strcmp(w->cor, "R") == 0){
                w->cor = "B";
                x->pai->cor = "B";
                RR(raiz, NILL, x->pai);
                w = x->pai->esq;
            }

            if((strcmp(w->esq->cor, "B") == 0) && (strcmp(w->dir->cor, "B") == 0)){
                w->cor = "R";
                x->pai->cor = "B";
                x = x->pai;
            
            } else {
                if(strcmp(w->esq->cor, "B") == 0){
                    w->cor = "R";
                    w->dir->cor = "B";
                    LL(raiz, NILL, x->pai->esq);
                }

                w->cor = x->pai->cor;
                x->pai->cor = "B";
                w->esq->cor = "B";
                RR(raiz, NILL, x->pai);
                x = raiz;
            }
        }
    }

    raiz = find_raiz(raiz, NILL);
    x->cor = "B";   
}

void LL(NODE *raiz, NODE *NILL, NODE *x){
    NODE *y;
    y = x->dir;
    x->dir = y->esq;
    
    if(y->esq != NILL)
        y->esq->pai = x;

    y->pai = x->pai;
    
    if(y->pai == NILL)
        raiz = y;
    else if(x == x->pai->esq) 
        x->pai->esq = y;
    else 
        x->pai->dir = y;

    y->esq = x;
    x->pai = y;
}

void RR(NODE *raiz, NODE *NILL, NODE *x){
    NODE *y;
    y = x->esq;
    x->esq = y->dir;
    
    if(y->dir != NILL)
        y->dir->pai = x;

    y->pai = x->pai;
    
    if(y->pai == NILL)
        raiz = y;
    else if(x == x->pai->esq)
        x->pai->esq = y;
    else
        x->pai->dir = y;

    y->dir = x;
    x->pai = y;
}

void printa_tree(NODE *raiz, NODE *NILL){ 
    NODE *aux = raiz;
    if(aux != NILL){ 
        aux->nivel = find_nivel(aux, NILL);
        printa_tree(aux->esq, NILL); 
        
        if(strcmp(aux->cor, "B") == 0)
            printf("- Nó %s preto nível %d -\n", aux->letra, aux->nivel); 
        else
            printf("- Nó %s vermelho nível %d -\n", aux->letra, aux->nivel); 
        
        printa_lista(aux -> lista);
        puts("");
        
        printa_tree(aux->dir, NILL); 
    } 
} 

void free_tree(NODE *raiz, NODE *NILL){ 
    if(raiz != NILL){ 
        free_tree(raiz->esq, NILL); 
        free_tree(raiz->dir, NILL); 
        free(raiz); 
    } 
}
