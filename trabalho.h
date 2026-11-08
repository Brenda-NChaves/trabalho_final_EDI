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

typedef struct lnodelivros
{
    Livro info;
    struct lnodelivros *next;
}nLivros;

typedef struct listlivros
{
    nLivros *first;
    int qtelem;
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
}lUsers;



int main()
{



    return 0;
}