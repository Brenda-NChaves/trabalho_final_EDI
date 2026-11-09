#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include <ctype.h>
#include "trabalho.h"

//funções implementadas aq
//essas duas foram geradas com IA
void paraMinusculo(char texto[])
{
    for (int i = 0; texto[i] != '\0'; i++)
    {
        if ((unsigned char)texto[i] == 0xC3 && texto[i+1] != '\0')
        {
            switch ((unsigned char)texto[i+1])
            {
                case 0x80: texto[i+1] = (char)0xA0; break; // À → à
                case 0x81: texto[i+1] = (char)0xA1; break; // Á → á
                case 0x82: texto[i+1] = (char)0xA2; break; // Â → â
                case 0x83: texto[i+1] = (char)0xA3; break; // Ã → ã
                case 0x87: texto[i+1] = (char)0xA7; break; // Ç → ç
                case 0x88: texto[i+1] = (char)0xA8; break; // È → è
                case 0x89: texto[i+1] = (char)0xA9; break; // É → é
                case 0x8A: texto[i+1] = (char)0xAA; break; // Ê → ê
                case 0x8D: texto[i+1] = (char)0xAD; break; // Í → í
                case 0x92: texto[i+1] = (char)0xB2; break; // Ò → ò
                case 0x93: texto[i+1] = (char)0xB3; break; // Ó → ó
                case 0x94: texto[i+1] = (char)0xB4; break; // Ô → ô
                case 0x95: texto[i+1] = (char)0xB5; break; // Õ → õ
                case 0x9A: texto[i+1] = (char)0xBA; break; // Ú → ú
            }
            i++;
        }
        else
        {
            texto[i] = (char)tolower((unsigned char)texto[i]);
        }
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
void menu(tLivros *TL,lUsers *LU, lLivros *LL)
{
    int n;
    printf("1.Cadasto\n2.Consulta\n3.Atualização\n4.Exclusão\n5.Empréstimo\n6.Devolução\n7.Exibir estatísticas\n0.Sair\n");
    scanf("%d",&n);

    switch (n)
    {
    case 1:
        cadastro(TL,LU,LL);
        break;
    case 2:
        consulta(TL,LU,LL);
        break;
    /*case 3:
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
        break;*/
    case 0:
        //sair();
        return;
    
    default:
        printf("Opção inválida, tente novamente\n");
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
        int ano;
        L->qtelem++;
        L->qtelemTotal++;
        printf("Cadastro de livro\nTítulo: ");
        GetMaieMin(titulo,50,1);//1 para maiusculo
        
        printf("Autor: ");
        GetMaieMin(autor,50,1);

        printf("Ano de publicação: ");
        scanf("%d",&ano);

        //ver esse negócio do ID(esperarresposta do denio)
        //ver se vai precisar adicionar a verificação do id
        nLivros *livro = setNodeL(setLivro(titulo,autor,ano,L));
        addNodeLL(L,livro);

        break;
    }   
    case 2:
    {
        char email[255];
        char nome [50];

        printf("Cadastro de Usuário\nEmail: ");
        GetMaieMin(email,255,0);
        
        if (findEmail(U->fisrt,email)!=NULL)
        {
            printf("Email já cadastrado\n");
            break;
        }

        printf("Nome: ");
        GetMaieMin(nome,50,1);

        nUser *user = setNodeU(setUser(email,nome));
        addNodeU(U,user);
        U->qtelem++;
        
        break;
    }
    case 0:
        return;
    
    default:
        printf("Opção inválida, tente novamente\n");
    }

}
void consulta(tLivros *TL,lUsers *LU,lLivros *LL)
{
    int n;
    char email [255];
    printf("1.Livros\n2.Usuários\n3.Empréstimos\n0.Voltar\n");
    scanf("%d",&n);
    getchar();

    switch (n)
    {
    case 1:
    {
        int d;
        printf("Buscar por:\n1.Código\n2.Autor\n: ");
        scanf("%d",&d);
        getchar();
        switch (d)
        {
        
        case 1:
        {
            nLivros *n = NULL;
            int id;
            printf("ID: ");
            scanf("%d",&id);
            getchar();
            n = findID(TL->root,id);

            if (n!=NULL)
            {
                printf("Título: %s\nAutor: %s\nAno de publicação: %d\nID: %d\nVezes emprestado: %d\nStatus: ",n->info.titulo,n->info.autor,n->info.ano,n->info.id,n->info.emp);
                if (n->info.status == 0) printf("DISPONÍVEL\n");
                else printf("EMPRESTADO\n");
            }
        break;    
        }
        case 2:
            {
                char autor [50];
                GetMaieMin(autor,50,1);

                findAutor(LL->first,autor);
                break;
            }
           
        default:
            printf("Opção inválida, tente novamente\n");
            break;
        }

        break;
    }
    case 2:
    {
        int d;
        printf("Buscar por:\n1.Email\n2.Nome\n: ");
        scanf("%d",&d);
        getchar();

        switch (d)
        {
            case 1:
            {
                printf("Email: ");
                GetMaieMin(email,255,0);

                nUser *e = findEmail(LU->fisrt,email);
                if (e!=NULL) printf("Nome: %s\nEmail: %s\n",e->info.nome,e->info.email);
                break;

            }
            case 2:
            {
                char nome [50];
                printf("Nome: ");
                GetMaieMin(nome,50,1);

                findNome(LU->fisrt,nome);
            }
            default:
            printf("Opção inválida, tente novamente\n");
            break;
        }
        break;
    }
    case 3:
    {
        printf("Email do usuário que deseja ver os empréstimos: ");
        GetMaieMin(email,255,0);
        findLporU(LL->first,email);
    }
        
        break;
    case 0:
        return;

    default:
        printf("Opção inválida, tente novamente\n");
    }
}

void atualiza(tLivros *TL,lUsers *LU,lLivros *LL)
{
    int n;
    char email[255];
    printf("1.Livros\n2.Usuários\n0.Voltar\n");
    scanf("%d",&n);
    getchar();

    switch (n)
    {
    case 1:
    {
        int titulo,ano,autor,id;
        printf("informe o ID do livro: ");
        scanf("%d",id);
        
        //IMPORTANTE!!!!!!!!!!!!!! pra eu terminar a atualização do livro preciso fazer a arvore de ID que facilita a busca, pq aí ele encontra ou não o id e termina de fazer as operações de acordo com o endereço que ele achar.
        printf("Digite 1 para os campos que deseja atualizar e 0 para os que não\nTítulo: ");
        scanf("%d",&titulo);
        printf("Ano: ");
        scanf("%d",&ano);
        printf("Autor: ");
        scanf("%d",&autor);

        if (titulo==1)
        {
            
        }
        if (ano==1)
        {

        }
        if (autor==1)
        {

        }
    }
        break;
    case 2:
    {
        printf("Email do usuário do qual deseja alterar o nome: ");
        GetMaieMin(email,255,0);
        nUser *U =findEmail(LU->fisrt,email);
        if(U!=NULL)
        {
            char nome[50];
            printf("Novo nome:");
            GetMaieMin(nome,50,1);
            strcpy(U->info.nome,nome);
        }
        else printf("Usuário não encontrado\n");
    }
        break;
    case 0:
        return;
    default:
        printf("Opção inválida, tente novamente\n");
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
        printf("Opção inválida, tente novamente\n");
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
        printf("Opção inválida, tente novamente\n");
    }

}

void estatisticas(tLivros *TL,lUsers *LU,lLivros *LL)
{
    int n;
    printf("1.livro mais emprestado\n2.Usuário com mais empréstimos ativos\n3.Total de livros cadastrados\n4.Total de usuários cadastrados\n0.Voltar\n");
    scanf("%d",&n);

    switch (n)
    {
    case 1: 
    {
        int maior = 0;
        nLivros *auxl = LL->first;
        for (;auxl!=NULL;auxl=auxl->next)
        {
            if (auxl->info.emp > maior) maior = auxl->info.emp;
        }
        if (maior==0)
        {
            printf("Nenhum livro foi emprestado\n");
            return;
        }
        auxl = LL->first;
        for (;auxl!=NULL;auxl=auxl->next)
        {
            if (auxl->info.emp == maior) printf("%s\n----------------\n",auxl->info.titulo);
        }
        //mostrar quantos por cento dos emrestimos isso representa

        break;
    }   
    case 2:
    {
        int maior = 0;
            nUser *auxu = LU->fisrt;
            for (;auxu!=NULL;auxu=auxu->next)
            {
                if (auxu->info.emp > maior) maior = auxu->info.emp;
            }
            if (maior==0)
            {
                printf("Nenhum livro emprestado no momento\n");
                return;
            }
            auxu = LU->fisrt;
            for (;auxu!=NULL;auxu=auxu->next)
            {
                if (auxu->info.emp == maior) printf("%s\n----------------\n",auxu->info.email);
            }

            break;
    }
    case 3:

        break;
    case 0:
       
        break;
    
    default:
        printf("Opção inválida, tente novamente\n");
    }

}

void sair(tLivros *TL, lUsers *LU, lLivros *LL)
{
    freeMemoryTL(TL->root);
    freeMemoryLL(LL->first);
    freeMemoryLU(LU->fisrt);
    free(TL);
    free(LL);
    free(LU);
}


//FIM DAS FUNÇÕES MENU

//FUNÇÕES PARA CONSTRUIR OS NÓS, LISTAS E A ÁRVORE
Usuario setUser(char email[30],char nome[50])
{
    Usuario u;
    strcpy(u.email,email);
    strcpy(u.nome,nome);
    return u;
}

Livro setLivro(char title[50], char autor[50],int ano, lLivros *L)
{
    Livro l;
    strcpy(l.titulo,title);
    strcpy(l.autor,autor);
    l.email[0]='\0';
    l.ano = ano;
    l.id = L->qtelemTotal;
    l.status = 0;
    l.emp=0;

    return l;
}

//cria um nó de livro para a arvore
TNLivros *setNodeTL(int id, nLivros *l)
{
    TNLivros *NL = (TNLivros *)malloc(sizeof(TNLivros));
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
    l->qtelemTotal=0;
}

//inicializa a lista de usuários
void initlUser (lUsers *u)
{
    u->fisrt=NULL;
    u->qtelem=0;
}
//inicializa a árvore de livros
void initTlivros (tLivros *t)
{
    t->root=NULL;
}

//adiciona o livro na lista ordnado por ID
//ver se o prof respondeu a dúvida e ajeitar isso aq conforme
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

//terminar de ajeitar esse usando strcmp
void addNodeU (lUsers *LU, nUser *User) 
{
    nUser *aux= LU->fisrt,*prev=LU->fisrt;
    if (LU->fisrt==NULL ) {
		LU->fisrt=User;
		LU->qtelem++;
		return;
	}

	while (aux != NULL)
	{
		if (strcmp(User->info.email,aux->info.email) < 0)
		{
		    LU->qtelem++;
			if(aux==LU->fisrt){
			    User->next=aux;
			    LU->fisrt=User;
			    return;
		    }
		    prev->next=User;
		    User->next=aux;
		    return;
		}
		prev=aux;
		aux=aux->next;
	}
	// o novo elemento vai ser incluído no fim
	prev->next=User;
	LU->qtelem++;
	return;	
	
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
    if(id < L->id) return findID(L->left, id);
    if(id > L->id) return findID(L->right, id);
   return NULL;//verificar isso aq depois
}

void findAutor(nLivros *L, char autor[50])
{   
    nLivros *aux = L;
    int flag = 0;
    printf("Livros cadastrados de %s: \n",autor);
      for (;aux!=NULL;aux=aux->next)
      {
          if (strcmp(aux->info.autor,autor)==0)
          {
            flag = 1;
            printf("Título: %s\nAno de publicação: %d\nID: %d\nStatus: ",aux->info.titulo,aux->info.ano,aux->info.id);
            if (aux->info.status == 0) printf("DISPONÍVEL\n");
            else printf("EMPRESTADO\n");
          }
      }
      if (flag==0) printf("Nenhum livro cadastrado\n ");
    
}

nUser *findEmail (nUser *U, char email[255])
{
    nUser *aux = U;
    for (;aux!=NULL;aux=aux->next)
    {
        if (strcmp(aux->info.email,email)==0) break;
    }
    return aux;
  
}
void findNome (nUser *U, char nome[50])
{
    nUser *aux = U;
    int flag=0;
    for (;aux!=NULL;aux=aux->next)
    {
        if (strcmp(aux->info.nome,nome)==0)
        {
            flag = 1;
            printf("Nome: %s\nEmail: %s\n",aux->info.nome,aux->info.email);
        }
    }
    if (flag==0) printf("Usuário não cadastrado\n");
}

void findLporU(nLivros *L, char email[255])
{
    nLivros *aux = L;
    int flag = 0;
    for (;aux!=NULL;aux=aux->next)
    {
        if (strcmp(email,aux->info.email)==0)
        {
            printf("%s\n-----------------\n",aux->info.titulo);
            flag =1;
        }
    }
    if (flag==0) printf("Nenhum livro encontrado\n");
    
}

//FIM DAS FUNÇÕES DE BUSCA

void GetMaieMin (char *c,int tam, int flag)
{
    fgets(c,tam,stdin);
    c[strcspn(c, "\n")] = '\0';
    if (flag==1) paraMaiusculo(c);
    else paraMinusculo(c);
}

//FUNÇÕES DE FREE MEMORY
void freeMemoryLL(nLivros *l)// no sair tem q passar o LL->first
{
	if (l==NULL) return;
	freeMemoryLL(l->next);
	free(l);
}
void freeMemoryLU(nUser *u)// no sair tem q passar o LU->first
{
	if (u==NULL) return;
	freeMemoryLU(u->next);
	free(u);
}
void freeMemoryTL(TNLivros *l)// no sair tem q passar o TN->root
{
    if (l==NULL) return;
	freeMemoryTL(l->left);
	freeMemoryTL(l->right);
    free(l);
}
// FIM DAS FUNÇÕES DE FREE MEMORY