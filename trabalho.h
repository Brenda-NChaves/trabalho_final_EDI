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
    char email[30];
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

// Conversão de letras
void paraMinusculo(char texto[]);
void paraMaiusculo(char *str);
void GetMaieMin(char *c, int tam, int flag);

// Funções do menu
void menu(tLivros *TL, lUsers *LU, lLivros *LL);
void cadastro(tLivros *TL, lUsers *U, lLivros *LL);
void consulta(tLivros *TL, lUsers *LU, lLivros *LL);
void atualiza(tLivros *TL, lUsers *LU, lLivros *LL);
void excluir();
void emprestar();
void devolver();
void estatisticas();
void sair();

// Construção de estruturas
Usuario setUser(char email[30], char nome[50]);
Livro setLivro(char title[50], char autor[50], int ano, lLivros *L);

TNLivros *setNodeTL(int id, nLivros *l);
nLivros *setNodeL(Livro L);
nUser *setNodeU(Usuario U);

// Inicialização
void initLlivros(lLivros *l);
void initlUser(lUsers *u);
void initTlivros(tLivros *t);

// Inserção
void addNodeLL(lLivros *LL, nLivros *l);
void addNodeU(lUsers *LU, nUser *User);

// Busca
nLivros *findID(TNLivros *L, int id);
void findAutor(nLivros *L, char autor[50]);
nUser *findEmail(nUser *U, char email[255]);
void findNome(nUser *U, char nome[50]);
void findLporU(nLivros *L, char email[255]);


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