#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include <ctype.h>
#include "trabalho.h"

//funções implementadas aq
//essas duas foram geradas com IA
void paraMaiusculo(char *str) {
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i]==' ') continue;
        str[i] = toupper((unsigned char)str[i]);
    }
}

void paraMaiusculo(char *str)
{
    for (int i = 0; str[i] != '\0'; i++)
    {
        unsigned char c = (unsigned char)str[i];

        // Letras ASCII
        if (c < 128)
        {
            str[i] = (char)toupper(c);
        }

        // Caracteres acentuados em UTF-8
        else if (c == 0xC3 && str[i+1] != '\0')
        {
            unsigned char prox = (unsigned char)str[i+1];

            switch (prox)
            {
                case 0xA0: str[i+1] = 0x80; break; // à -> À
                case 0xA1: str[i+1] = 0x81; break; // á -> Á
                case 0xA2: str[i+1] = 0x82; break; // â -> Â
                case 0xA3: str[i+1] = 0x83; break; // ã -> Ã
                case 0xA7: str[i+1] = 0x87; break; // ç -> Ç
                case 0xA8: str[i+1] = 0x88; break; // è -> È
                case 0xA9: str[i+1] = 0x89; break; // é -> É
                case 0xAA: str[i+1] = 0x8A; break; // ê -> Ê
                case 0xAD: str[i+1] = 0x8D; break; // í -> Í
                case 0xB2: str[i+1] = 0x92; break; // ò -> Ò
                case 0xB3: str[i+1] = 0x93; break; // ó -> Ó
                case 0xB4: str[i+1] = 0x94; break; // ô -> Ô
                case 0xB5: str[i+1] = 0x95; break; // õ -> Õ
                case 0xBA: str[i+1] = 0x9A; break; // ú -> Ú
            }

            i++; // Pula o segundo byte do caractere
        }
    }
}

//FUNÇÕES MENU

//adicionar nos parametros a lista de livros
void menu(tLivros *TL,lUsers *TU, lLivros *LL)
{
    int n;
    printf("1.Cadasto\n2.Consulta\n3.Atualização\n4.Exclusão\n5.Empréstimo\n6.Devolução\n7.Exibir estatísticas\n0.Sair\n");
    scanf("%d",&n);

    switch (n)
    {
    case 1:
        cadastro(TL,TU,LL);
        break;
    case 2:
        consulta(TL,TU);
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
    case 7:
        estatisticas();
        break;
    case 0:
        sair();
        break;
    
    default:
        printf("Opção inválida, tente novamente");
    }

}

void cadastro(tLivros *TL, lUsers *U, lLivros *L)
{
    int n;
    printf("1.Livros\n2.Usuários\n0.Voltar\n");
    scanf("%d",&n);
    getchar();

    switch (n)
    {
    case 1:
    {
        char titulo[50];
        char autor[50];
        int ano, id;
        printf("Cadastro de livro\nTítulo: ");
        fgets(titulo,sizeof(titulo),stdin);
        autor[strcspn(autor,"\n")] = '\0';
        paraMaiusculo(titulo);
        getchar();

        printf("Autor: ");
        fgets(autor,sizeof(autor),stdin);
        autor[strcspn(autor, "\n")] = '\0';
        paraMaiusculo(autor);


        printf("Ano de publicação: ");
        scanf("%d",&ano);

        printf("ID único: ");
        scanf("%d",&id);

        nLivros *livro = setNodeL(setLivro(titulo,autor,ano,id));
        addNodeL(L,livro);

        break;
    }   
    case 2:
    {
        char email[255];
        char nome [50];

        printf("Cadastro de Usuário\nEmail: ");
        scanf("%254s",email);
        paraMinusculo(email);
        getchar();

        printf("Nome: ");
        fgets(nome,sizeof(nome),stdin);
        nome[strcspn(nome, "\n")] = '\0';
        paraMaiusculo(nome);

        nUser *user = setNodeU(setUser(email,nome));
        addNodeU(U,user);
        
        break;
    }
    case 0:
        return;
    
    default:
        printf("Opção inválida, tente novamente");
    }

}
void consulta(tLivros *TL,lUsers *TU)
{
    int n;
    printf("1.Livros\n2.Usuários\n3.Empréstimos\n0.Voltar\n");
    scanf("%d",&n);

    switch (n)
    {
    case 1:
    {


        break;
    }
    case 2:
        
        break;
    case 3:
        
        break;
    case 0:
        
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
      
        
        break;
    
    
    default:
        printf("Opção inválida, tente novamente");
    }
}

void emprestar()
{
    //sempre que emprestra eu tenho que somar um na quantidade de vezes que o livro foi emprestado
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

void estatisticas()
{
    int n;
    printf("1.livro mais emprestado\n2.Usuário com mais empréstimos ativos\n3.Livros atrasados\n0.Voltar\n");
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
       
        break;
    
    default:
        printf("Opção inválida, tente novamente");
    }

}

void sair()
{

}


//FIM DAS FUNÇÕES MENU

//FUNÇÕES PARA CONSTRUIR OS NÓS E AS ÁRVORES
Usuario setUser(char email[30],char nome[50])
{
    Usuario u;
    strcpy(u.email,email);
    strcpy(u.nome,nome);
    return u;
}

Livro setLivro(char title[50], char autor[50],int ano, int id)
{
    Livro l;
    strcpy(l.titulo,title);
    strcpy(l.autor,autor);
    l.email[0]='\0';
    l.ano = ano;
    l.id = id;
    l.status = 0;
    l.emp=0;

    return l;
}

//cria um nó de livro para a arvore
TNLivros *setNodeTL(int id, nLivros *l)
{
    TNLivros *NL = (nLivros *)malloc(sizeof(nLivros));
    NL->id = id;
    NL->endereco = l;
    NL->left=NULL;
    NL->right=NULL;

    return NL;
}
//cria um nó 

//cria um nó de livro para a lista
nLivros *setNodeL(Livro L)
{
    nLivros *NL = (nLivros *)malloc(sizeof(nLivros));
    NL->info = L;
    NL->next=NULL;

    return NL;
}
//cria um nó de usuário
nUser *setNodeU(Usuario U)
{
    nUser *User = (nUser *)malloc(sizeof(nUser));
    User->info = U;
    User->next=NULL;


    return User;
}

//inicializa a lista de usuários
void initLlivros(lLivros *l)
{
    l->first=NULL;
    l->qtelem=0;
}

//inicializa a lista de usuários
void initlUser (lUsers *u)
{
    u->fisrt=NULL;
}
//inicializa a árvore de livros
void initTlivros (tLivros *t)
{
    t->root=NULL;
}

//adiciona o livro na lista ordnado por ID
void addNodeLL(lLivros *LL, nLivros *l)
{
    nLivros *aux= LL->first,*prev=LL->first;
    if (LL->first==NULL ) {
		LL->first=l;
		LL->qtelem++;
		return;
	}

	while (aux != NULL)
	{
		if (l->info.id < aux->info.id)
		{
		    LL->qtelem++;
			if(aux==LL->first){
			    l->next=aux;
			    LL->first=l;
			    return;
		    }
		    prev->next=l;
		    l->next=aux;
		    return;
		}
		prev=aux;
		aux=aux->next;
	}
	// o novo elemento vai ser incluído no fim
	prev->next=l;
	LL->qtelem++;
	return;	
}
//adiciona um usurário na arvore
//terminar de ajeitar esse usando strcmp
nUser *addNodeU (lUsers *TU, nUser *User) 
{
	
}

//adiciona um livro na arvore
/* REAFZAER ESSA AQ QUE ADICNA O NO DE LIVRO NA ARVORE
nLivros *addNodeTL (tLivros *TL, nLivros *Livro) 
{
	if (TL->root==NULL)
	   return TL->root = Livro;
    if (TL->root-> == Livro->info.id)
    {
        printf("Esse ID já existe no sistema, cadastre com outro ID\n");
        return TL->root;
    }
	if (Livro->info.id < TL->root->info.id) 
	   TL->root->left=insertNodeR(TL->root->left,Livro);
	else {
	   TL->root->right=insertNodeR(TL->root->right,Livro);
    }
	return TL->root;
}
    */
// FIM DAS FUNÇÕES PARA CONSTRUIR OS NÓS, ÁRVORE LISTAS


//FUNÇÕES DE BUSCA

//bbusca se tem o id na arvore
nLivros *findID(TNLivros *L, int id)
{
    if(L==NULL){
        printf("ID não encontrado\n");
        return NULL;
    }
    if (L->id == id) return L->endereco;
    if(id < L->id) findID(L->left, id);
    if(id > L->id) findID(L->right, id);
   
}
//a única coisa que faz é encotrar livros
int findAutor(nLivros *L, char autor[50])
{   
  
    
}

nUser *findEmail (nUser *U, char email[255])
{
  
}
int *findNome (nUser *U, char nome[50])
{
}


//FIM DAS FUNÇÕES DE BUSCA