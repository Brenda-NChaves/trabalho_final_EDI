#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include "trabalho.h"

//funções implementadas aq


//FUNÇÕES DO MENU
void menu()
{
    int n;
    printf("1.Cadasto\n2.Consulta\n3.Atualização\n4.Exclusão\n5.Empréstimo\n6.Devolução\n0.Sair\n");
    scanf("%d",&n);

    switch (n)
    {
    case 1:
        cadastro();
        break;
    case 2:
        consulta();
        break;
    case 3:
        atualiza();
        break;
    case 4:
        excluir();
        break;
    case 5:
        emprestar();
        break;
    case 6:
        devolver();
        break;
    case 0:
        sair();
        break;
    
    default:
        printf("Opção inválida, tente novamente");
    }

}

void cadastro()
{
    int n;
    printf("1.Livros\n2.Usuários\n0.Voltar\n");
    scanf("%d",&n);

    switch (n)
    {
    case 1:
        
        break;
    case 2:
        
        break;
    case 0:
        menu();
        
        break;
    
    
    default:
        printf("Opção inválida, tente novamente");
    }

}
void consulta()
{
    int n;
    printf("1.Livros\n2.Usuários\n3.Empréstimos\n0.Voltar\n");
    scanf("%d",&n);

    switch (n)
    {
    case 1:
        
        break;
    case 2:
        
        break;
    case 3:
        
        break;
    case 0:
        menu();
        break;
    
    
    default:
        printf("Opção inválida, tente novamente");
    }

}

void atualiza()
{
    int n;
    printf("1.Livros\n2.Usuários\n0.Voltar\n");
    scanf("%d",&n);

    switch (n)
    {
    case 1:
        
        break;
    case 2:
        
        break;
    case 0:
        menu();
        
        break;
    
    
    default:
        printf("Opção inválida, tente novamente");
    }

}
void excluir()
{
    int n;
    printf("1.Livros\n2.Usuários\n0.Voltar\n");
    scanf("%d",&n);

    switch (n)
    {
    case 1:
        
        break;
    case 2:
        
        break;
    case 0:
        menu();
        
        break;
    
    
    default:
        printf("Opção inválida, tente novamente");
    }

}
void devolver()
{
    int n;
    printf("ID: ");
    scanf("%d",&n);

    switch (n)
    {
    case 1:
        
        break;
    case 2:
        
        break;
    
    
    default:
        printf("Opção inválida, tente novamente");
    }

}

void sair()
{

}
//FIM DAS FUNÇÕES DO MENU

Usuario setUser(char email[30],char nome[50])
{
    Usuario u;
    strcpy(u.email,email);
    strcpy(u.nome,nome);
    return u;
}

Livro setLivro(char title[50], char autor[50],int ano, int id, int status, char email[30])
{
    Livro l;
    strcpy(l.title,title);
    strcpy(l.autor,autor);
    strcpy(l.email,email);
    l.ano = ano;
    l.id = id;
    l.status = status;

    return l;
}