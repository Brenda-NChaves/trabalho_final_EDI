#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include <ctype.h>
#include "trabalho.h"

//funções implementadas aq
//essa primeira foi gerada com IA porque queria deixar as informações digitadas pelo usuário todos com letra maiúscula para facilitar a busca, mas o toupper é meio chatinho de usar, já que ele faz isso byte por byte, mas letras com acento e ç ocupam dois bytes, então pedi para o gpt fazer essa parte, mas só foi isso que ela fez

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
    case 3:
        atualiza(TL,LU);
        break;
    case 4:
        excluir(TL,LU,LL);
        break;
    case 5:
        emprestar(TL,LU);
        break;
    case 6:
        devolver(TL);
        break;
    case 7:
        estatisticas(LU,LL);
        break;
    case 0:
        sair(TL,LU,LL);
        return;
    
    default:
        printf("Opção inválida, tente novamente\n\n");
    }
}

void cadastro(tLivros *TL, lUsers *U, lLivros *L)
{
    int n;
    printf("1.Livros\n2.Usuários\n0.Voltar\n");
    scanf("%d",&n);
    getchar();
    printf("\n");
    switch (n)
    {
    case 1:
    {
        char titulo[50];
        char autor[50];
        int ano;
        printf("Cadastro de livro\nTítulo: ");
        GetM(titulo,50);
        
        printf("Autor: ");
        GetM(autor,50);

        printf("Ano de publicação: ");
        scanf("%d",&ano);
        printf("\n");

        nLivros *livro = setNodeL(setLivro(titulo,autor,ano,L));
        addNodeLL(L,livro);
        TNLivros *TN =setNodeTL(livro->info.id, livro);
        TL->root = insertNodeR(TL->root,TN);
        
        break;
    }   
    case 2:
    {
        char email[255];
        char nome [50];

        printf("Cadastro de Usuário\nEmail: ");
        GetM(email,255);
        
        if (findEmail(U->fisrt,email)!=NULL)
        {
            printf("Email já cadastrado\n");
            break;
        }

        printf("Nome: ");
        GetM(nome,50);
        printf("\n");

        nUser *user = setNodeU(setUser(email,nome));
        addNodeU(U,user);
        break;
    }
    case 0:
        return;
    
    default:
        printf("Opção inválida, tente novamente\n\n");
    }

}
void consulta(tLivros *TL,lUsers *LU,lLivros *LL)
{
    int n;
    char email [255];
    printf("1.Livros\n2.Usuários\n3.Empréstimos\n0.Voltar\n");
    scanf("%d",&n);
    getchar();
    printf("\n");

    switch (n)
    {
    case 1:
    {
        int d;
        printf("Buscar por:\n1.Código\n2.Autor\n");
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
            if (n==NULL) return;
            
            printf("Título: %s\nAutor(a): %s\nAno de publicação: %d\nVezes emprestado: %d\nStatus: ",n->info.titulo,n->info.autor,n->info.ano,n->info.emp);
            if (n->info.status == 0) printf("DISPONÍVEL\n\n");
            else printf("EMPRESTADO\n\n");

            break;    
        }
        case 2:
            {
                char autor [50];
                GetM(autor,50);

                findAutor(LL->first,autor);
                break;
            }
           
        default:
            printf("Opção inválida, tente novamente\n\n");
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
                GetM(email,255);

                nUser *e = findEmail(LU->fisrt,email);
                if (e!=NULL) printf("Nome: %s\nEmail: %s\n\n",e->info.nome,e->info.email);
                else
                {
                    printf("Usuário não cadastrado\n\n");
                    return;
                }
                break;

            }
            case 2:
            {
                char nome [50];
                printf("Nome: ");
                GetM(nome,50);

                findNome(LU->fisrt,nome);
                break;
            }
            default:
            printf("Opção inválida, tente novamente\n\n");
            break;
        }
        break;
    }
    case 3:
    {
        printf("Email do usuário que deseja ver os empréstimos: ");
        GetM(email,255);
        findLporU(LL->first,email);
        break;
    }
    case 0:
        return;

    default:
        printf("Opção inválida, tente novamente\n\n");
    }
}

void atualiza(tLivros *TL,lUsers *LU)
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
        nLivros *n = NULL;
        int titulo,ano,autor,id;
        char Ntitulo[50];
        char Nautor[50];
        printf("informe o ID do livro: ");
        scanf("%d",&id);
        n = findID(TL->root,id);
        if (n==NULL) return;
            
        printf("Digite 1 para os campos que deseja atualizar e 0 para os que não\nTítulo: ");
        scanf("%d",&titulo);
        printf("Ano: ");
        scanf("%d",&ano);
        printf("Autor: ");
        scanf("%d",&autor);
        getchar();

        if (titulo==1)
        {
            printf("Novo título: ");
            GetM(Ntitulo,50);
            strcpy(n->info.titulo,Ntitulo);
        }
        if (ano==1)
        {
            printf("Novo ano: ");
            scanf("%d",&n->info.ano);
            getchar();
        }
        if (autor==1)
        {
            printf("Novo autor: ");
            GetM(Nautor,50);
            strcpy(n->info.autor,Nautor);
        }
        printf("\n");
        break;
    }
    case 2:
    {
        printf("Email do usuário do qual deseja alterar o nome: ");
        GetM(email,255);
        nUser *U =findEmail(LU->fisrt,email);
        if(U==NULL)
        {
            printf("Usuário não cadastrado\n\n");
            return;
        }
            char nome[50];
            printf("Novo nome:");
            GetM(nome,50);
            strcpy(U->info.nome,nome);
        break;
    }
    case 0:
        return;
    default:
        printf("Opção inválida, tente novamente\n\n");
}
}

void excluir(tLivros *TL,lUsers *LU,lLivros *LL)
{
    int n;
    printf("1.Livros\n2.Usuários\n0.Voltar\n");
    scanf("%d",&n);
    getchar();

    switch (n)
    {
    case 1:
    {
        int id;
        printf("ID do livro que deseja excluir: ");
        scanf("%d",&id);
        getchar();
        nLivros *L = findID(TL->root,id);
        if (L==NULL) return;
        
        delNodeTL(TL,id);
        delNodeLL(LL,id);
        printf("Exclusão realizada com sucesso\n\n");
    }
        
        break;
    case 2:
    {
        char email[255];
        printf("Email do usuário que deseja excluir: ");
        GetM(email,255);
        nUser *U =findEmail(LU->fisrt,email);
        if(U==NULL)
        {
            printf("Usuário não cadastrado\n\n");
            return;
        }
            
        
        nLivros *aux = LL->first;
        for(;aux!=NULL;aux=aux->next)
        {
            if (strcmp(aux->info.email, U->info.email)==0)
            {
                aux->info.email[0]='\0';
                aux->info.status = 0;
            }
        }
        delNodeLU(LU,U);
        printf("Exclusão concluída com sucesso\n\n");
        break;
        
    }
    case 0:
      return;
    default:
        printf("Opção inválida, tente novamente\n\n");
    }
}

void emprestar( tLivros *TL,lUsers *LU)
{
    int id;
    char email[255];
    nUser *user;
    printf("ID do livro: ");
    scanf("%d",&id);
    getchar();

    nLivros *L = findID(TL->root,id);
    if (L==NULL) return;
    
    if (L->info.status==1)
    {
        printf("Esse livro já está emprestado\n\n");
        return;
    }
        printf("Informe o email do usuário: ");
        GetM(email,255);
        user = findEmail(LU->fisrt,email);
        if(user==NULL)
        {
            printf("Usuário não cadastrado\n\n");
            return;
        }

        L->info.status=1;
        L->info.emp++;
        user->info.emp++;
        strcpy(L->info.email,email);
        printf("Empréstimo realizado com sucesso\n\n");
    
}

void devolver(tLivros *TL)
{
    int id;
    printf("ID do livro para devolver: ");
    scanf("%d",&id);
    getchar();

    nLivros *L = findID(TL->root,id);
    if (L==NULL) return;
    
    if (L->info.status==0)
    {
        printf("Esse livro não está emprestado\n\n");
        return;
    }
        L->info.status=0;
        L->info.email[0] = '\0';
        printf("Livro devolvido com sucesso\n\n");
}

void estatisticas(lUsers *LU,lLivros *LL)
{
    int n;
    printf("1.livro mais emprestado\n2.Usuário que realizou mais empréstimos\n3.Total de livros cadastrados\n4.Total de usuários cadastrados\n5.Total de livros atualmente emprestados\n0.Voltar\n");
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
        printf("\n");
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
            printf("\n");
            break;
    }
    case 3:
    {
        printf("%d livros cadastrados\n\n",LL->qtelem);
        break;
    }
    case 4:
    {
        printf("%d usuários cadastrados\n\n",LU->qtelem);
        break;
    }
    case 5:
    {
        int total = 0;
        nLivros *auxl = LL->first;
        for (;auxl!=NULL;auxl=auxl->next)
        {
            if(auxl->info.status==1) total++;
        }
        if (total==0)
        {
            printf("Nenhum livro emprestado no momento\n\n");
            return;
        }

        printf("%d livro(s) emprestado(s) no momento\n\n",total);
        break;
    }
    case 0:
        return;
    default:
        printf("Opção inválida, tente novamente\n\n");
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

//FUNÇÕES PARA CONSTRUIR OS NÓS E LISTAS
Usuario setUser(char email[30],char nome[50])
{
    Usuario u;
    strcpy(u.email,email);
    strcpy(u.nome,nome);
    u.emp=0;
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

//cria um nó pra ABB
TNLivros *setNodeTL(int id, nLivros *endereco)
{
    TNLivros *TN = (TNLivros *)malloc(sizeof(TNLivros));
    TN->id = id;
    TN->endereco = endereco;
    TN->left=NULL;
    TN->right=NULL;
    return TN;
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
void addNodeLL(lLivros *LL, nLivros *l)
{
    nLivros *aux= LL->first,*prev=LL->first;
    if (LL->first==NULL ) {
		LL->first=l;
		LL->qtelem++;
        LL->qtelemTotal++;
		return;
	}

	while (aux != NULL)
	{
		if (l->info.id < aux->info.id)
		{
		    LL->qtelem++;
            LL->qtelemTotal++;
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
    LL->qtelemTotal++;
	return;	
}
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
// FIM DAS FUNÇÕES PARA CONSTRUIR OS NÓS E LISTAS

//AVL

int depthSubTree(TNLivros *root){
	int depthLeft, depthRight;

	if (root==NULL)
	   return 0;

	depthLeft = depthSubTree(root->left); //calculate the depth of the left subtree
	depthRight = depthSubTree(root->right);//calculate the depth of the right subtree

	return 1 + (depthLeft > depthRight? depthLeft: depthRight); //verify the deepest sub-tree and add + 1.
}
TNLivros *ll(TNLivros *root){
	TNLivros *newRoot = root->left;
	root->left = newRoot->right;
	newRoot->right = root;

	return newRoot;
}
TNLivros *rr(TNLivros *root){
	TNLivros *newRoot = root->right;
	root->right = newRoot->left;
	newRoot->left = root;

	return newRoot;
}
TNLivros *lr(TNLivros *root){
	root->left = rr(root->left);
	return ll(root);
}
TNLivros *rl(TNLivros *root){
	root->right = ll(root->right);
	return rr(root);
}
TNLivros *balanceCheck(TNLivros *root){
	int rootBalance, childBalance;

	rootBalance = depthSubTree(root->left) - depthSubTree(root->right);
	
	if (rootBalance > 1){
		//calculates the balance value of the left child
		childBalance = depthSubTree(root->left->left) - depthSubTree(root->left->right);
		root = (childBalance > 0)? ll(root): lr(root);

	}else if (rootBalance < -1){
		//calculates the balance value of the right child
		childBalance = depthSubTree(root->right->left) - depthSubTree(root->right->right);
		root = (childBalance < 0)? rr(root): rl(root);
	}
	return root;
}
TNLivros *insertNodeR (TNLivros *root, TNLivros *n) //  recursive
{
	if (root==NULL)
	   return n;

	if (n->id < root->id) // go to left
	   root->left=insertNodeR(root->left,n);
	else
	   root->right=insertNodeR(root->right,n);

	root = balanceCheck(root);
	
	return root;
}
//FIM DA AVL

//FUNÇÕES DE BUSCA

//busca se tem o id na arvore
nLivros *findID(TNLivros *L, int id)
{
    if(L==NULL){
        printf("Livro não encontrado\n\n");
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
            printf("-------------------\n");
          }
      }
      if (flag==0) printf("Nenhum livro cadastrado\n\n");
    
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
    if (flag==0) printf("Usuário não cadastrado\n\n");
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
    if (flag==0) printf("Nenhum livro encontrado\n\n");
    
}
//FIM DAS FUNÇÕES DE BUSCA

void GetM (char *c,int tam)
{
    fgets(c,tam,stdin);
    c[strcspn(c, "\n")] = '\0';
    paraMaiusculo(c);
    
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

//FUNÇÔES DE EXCLUSÂO:
////exclui da lista de:
//usuários
void delNodeLU (lUsers *s, nUser *U)
{
	nUser *aux=s->fisrt,*auxprev=s->fisrt;

	for (;aux!=NULL;aux=aux->next)
	{
		if (aux==U)
		{
			s->qtelem--;
			if (aux == s->fisrt)
			{
				s->fisrt = aux->next;
				free(aux);
				break;
			}
			if (aux->next == NULL)
			{
				auxprev->next = NULL;
				free(aux);
				break;
			}
			auxprev->next = aux->next;
			free(aux);
			break;
				
		}
		auxprev=aux;
	}
}
//livros
void delNodeLL (lLivros *s, int id )
{
	if (s->first == NULL)
	{
		printf("Lista vazia\n");
		return;
	}
	nLivros *aux=s->first,*auxprev=s->first;

	for (;aux!=NULL;aux=aux->next)
	{
		if (aux->info.id == id)
		{
			s->qtelem--;
			if (aux == s->first)
			{
				s->first = aux->next;
				free(aux);
				break;
			}
			if (aux->next == NULL)
			{
				auxprev->next = NULL;
				free(aux);
				break;
			}
			auxprev->next = aux->next;
			free(aux);
			break;	
		}
		auxprev=aux;
	}
}
//excluiu da arvore:
void delNodeTL (tLivros *n, int v)
{
	if(n->root==NULL) return;
	TNLivros *aux=n->root, *parent=n->root, *aux2;
	while(aux!=NULL)
		if (v<aux->id)
		{ 	
			parent=aux;
			aux= aux->left;
		}
		else if (v>aux->id) 
		{
			parent=aux;
			aux=aux->right;
		}
			else break;
		
	if (aux==NULL) return; //não encontrou o dado

	//Caso 1
	if (aux->left==NULL && aux->right==NULL)
	{
        if(aux==parent) n->root=NULL;
		else if (aux->id<=parent->id) parent->left=NULL;
		else				   parent->right=NULL;
		free(aux);
		return;
	
	}
	//Caso 2
	if ((aux->left==NULL && aux->right !=NULL) || (aux->left!=NULL && aux->right ==NULL ))
	{
		if (aux->left==NULL)
		{	
			if(aux==n->root) {n->root=aux->right; free(aux);return;}
			if (aux->id<=parent->id) parent->left=aux->right;
			else parent->right=aux->right;	
					  
		}
		else {
			if(aux==n->root) {n->root=aux->left; free(aux); return;}
			if (aux->id<=parent->id) parent->left=aux->left;
			else parent->right=aux->left;
		}
		free(aux);
		return;	
	}
	//caso 3 
	if (aux->left!=NULL && aux->right !=NULL)
	{
		aux2=aux->right;
		
		TNLivros *parent2=aux;
		for (;aux2->left!=NULL;aux2=aux2->left){parent2=aux2;}//acha o aux2 e o parent dele

		
		//caso se for folha
		if(aux2->left==NULL&&aux2->right==NULL)
		{
			if (aux2->id<=parent2->id) parent2->left=NULL;
			else					parent2->right=NULL;
			aux->id=aux2->id;
			free(aux2);
			return;
		}
		//caso n for folha e for filho do aux
		if (parent2==aux)
		{
			aux->id=aux2->id;
			aux->right=aux2->right;
			free(aux2);
			return;
		}
		//caso n for folha e não for filho do aux
		else
		{
			aux->id=aux2->id;
			parent2->left=aux2->right;
			free(aux2);
			return;
		}
	}
}