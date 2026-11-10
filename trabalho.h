#include <stdio.h>
#include <stdlib.h>
#include<string.h>

//cabeçalho
//structs aq

typedef struct usuario
{
    char email[255],nome[50];
    int emp;

}Usuario;

typedef struct livro
{
    char titulo[50];
    char autor[50];
    int ano, id, status,emp;
    char email[255];
}Livro;

//nó e arvore para os livros
typedef struct lnodelivros
{
    Livro info;
    struct lnodelivros *next;
}nLivros;

typedef struct tnodelivros
{
    int id;
    nLivros *endereco;
    struct tnodelivros *left, *right;
}TNLivros;

typedef struct treelivros
{
    TNLivros *root;
}tLivros;

//nó e lista para livros


typedef struct listlivros
{
    nLivros *first;
    int qtelem;
    int qtelemTotal;
}lLivros;


//nós e lista para os usuários
typedef struct nodeuser
{
    Usuario info;
    struct nodeuser *next;
}nUser;

typedef struct listusuarios
{
    nUser *fisrt;
    int qtelem;
}lUsers;


#ifndef TRABALHO_H
#define TRABALHO_H

// FUNÇÕES DE MENU
void paraMaiusculo(char *str);
void menu(tLivros *TL, lUsers *LU, lLivros *LL);
void cadastro(tLivros *TL, lUsers *U, lLivros *L);
void consulta(tLivros *TL, lUsers *LU, lLivros *LL);
void atualiza(tLivros *TL, lUsers *LU);
void excluir(tLivros *TL, lUsers *LU, lLivros *LL);
void emprestar(tLivros *TL, lUsers *LU);
void devolver(tLivros *TL);
void estatisticas(lUsers *LU, lLivros *LL);
void sair(tLivros *TL, lUsers *LU, lLivros *LL);

// CONSTRUÇÃO DE NÓS E LISTAS
Usuario setUser(char email[30], char nome[50]);
Livro setLivro(char title[50], char autor[50], int ano, lLivros *L);

nLivros *setNodeL(Livro L);
nUser *setNodeU(Usuario U);
TNLivros *setNodeTL(int id, nLivros *endereco);

void initLlivros(lLivros *l);
void initlUser(lUsers *u);
void initTlivros(tLivros *t);

void addNodeLL(lLivros *LL, nLivros *l);
void addNodeU(lUsers *LU, nUser *User);

// AVL
int depthSubTree(TNLivros *root);

TNLivros *ll(TNLivros *root);
TNLivros *rr(TNLivros *root);
TNLivros *lr(TNLivros *root);
TNLivros *rl(TNLivros *root);

TNLivros *balanceCheck(TNLivros *root);
TNLivros *insertNodeR(TNLivros *root, TNLivros *n);

// FUNÇÕES DE BUSCA
nLivros *findID(TNLivros *L, int id);
void findAutor(nLivros *L, char autor[50]);
nUser *findEmail(nUser *U, char email[255]);
void findNome(nUser *U, char nome[50]);
void findLporU(nLivros *L, char email[255]);

void GetM(char *c, int tam);

// LIBERAÇÃO DE MEMÓRIA
void freeMemoryLL(nLivros *l);
void freeMemoryLU(nUser *u);
void freeMemoryTL(TNLivros *l);

// EXCLUSÃO
void delNodeLU(lUsers *s, nUser *U);
void delNodeLL(lLivros *s, int id);
void delNodeTL(tLivros *n, int v);

#endif


int main()
{

    tLivros *TL =(tLivros *)malloc(sizeof(tLivros));
    lUsers *LU =(lUsers *)malloc(sizeof(lUsers));
    lLivros *LL = (lLivros *)malloc(sizeof(lLivros));
    initLlivros(LL);
    initlUser(LU);
    initTlivros(TL);

    while(1){
        menu(TL,LU,LL);
    }
    


    return 0;
}