/*****************************************************************/
/*   Grafo direcionado | PROG2 | MIEEC | 2019/20        */      
/*****************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "grafo.h"

/**FUNÇÃO AUXILIAR
 * Verifica se existe a ligação entre os nós origem e destino no grafo g
 * Retorna 0 caso exista ou -1 em caso de erro ou inexistência
**/
int ligacao_existe(grafo* g,no_grafo *origem, no_grafo *destino);

grafo* grafo_novo()
{
   //Aloca memória para a estrutura grafo
   grafo *grafo_novo = (grafo*)malloc(sizeof(grafo));
   if(grafo_novo == NULL){                                      //Caso seja impossível criar memória
       return NULL;
    }

    grafo_novo->tamanho = 0;                                    //Inicializa o tamanho a 0

    return grafo_novo;
}


void grafo_apaga(grafo* g)
{
    //Casos de erro
    if(g == NULL){
        free(g);
        return;
    }

    //Caso o grafo tenha nós
    if(g->tamanho != 0)
    {
        //Percorre os nós todos do grafo
        for(int i=0; i<g->tamanho; i++)
        {
            //Caso o nó tenha ligações
            if(g->nos[i]->tamanho != 0)
            {
                //Percorre todas as ligações do nó
                for(int j=0; j<g->nos[i]->tamanho; j++)
                {
                    free(g->nos[i]->ligacoes[j]);
                }
                free(g->nos[i]->ligacoes);
            }
            free(g->nos[i]->nome_user);
            free(g->nos[i]);
        }
        free(g->nos);
    }

    free(g);
        
    return;
}


no_grafo * no_insere(grafo *g, char *user)
{
    //Casos de erro
    if(!g || user == NULL){
        return NULL;
    }
    
    //Verifica se já existe o nó
    if(encontra_no(g, user) != NULL){
        return NULL;
    }

    //Caso o grafo não tenha nós, então cria espaço de memória para uma posição no vetor de apontadores para nós
    if(g->tamanho == 0){
        g->nos = (no_grafo **)malloc(sizeof(no_grafo *));
        if(g->nos == NULL){
            free(g->nos);
            return NULL;
        }

        g->tamanho++;
    }
    else{
        //Incrementa o tamanho do grafo
        g->tamanho++;
        
        //Aloca memória dinâmica para mais uma posição do vetor de apontares para nós
        g->nos = (no_grafo **)realloc(g->nos,g->tamanho*sizeof(no_grafo*)); // ou  g->nos[g->tamanho-1] = (no_grafo *)malloc(sizeof(no_grafo));
        if(g->nos == NULL){
            free(g->nos);
            return NULL;
        }
    }

    //Aloca memória para o novo nó
    no_grafo *novo_no = (no_grafo *)malloc(sizeof(no_grafo));
    if(novo_no == NULL){
        free(g->nos);
        free(novo_no);
        return NULL;
    }

    //Aloca memória para a string que contém o nome do utilizador
    novo_no->nome_user = (char *)malloc(strlen(user)+1);
    if(novo_no->nome_user == NULL){
        free(g->nos);
        free(novo_no);
        free(novo_no->nome_user);
        return NULL;
    }

    //Coloca o Utilizador e o tamanho de ligações (0) no novo nó
    strcpy(novo_no->nome_user,user);
    novo_no->tamanho = 0;


    //Insere o apontador para o novo nó na ultima posição do vetor de apontadores para nós do grafo
    g->nos[g->tamanho-1] = novo_no;

    return novo_no;
}

int  cria_ligacao(no_grafo *origem, no_grafo *destino, int peso)
{
    //Casos de erro
    if(origem == NULL || destino == NULL || peso <= 0 ){
        return -1;
    }

    int i;
    ligacao *l_nova;

    //Se já existe a ligação, então retorna -1
    for(i=0; i < origem->tamanho; i++)
    {
        if(origem->ligacoes[i]->destino == destino){
            return -1;
        }
    }

    //Caso o nó de origem não tenha ligações, então cria espaço de memória para o vetor de apontadores para as ligações do nó
    if(origem->tamanho == 0){
        origem->ligacoes = (ligacao **)malloc(sizeof(ligacao *));
        if(origem->ligacoes == NULL){
            free(origem->ligacoes);
            return -1;
        }

        origem->tamanho++;
    }
    else{
        //Incrementa o número de ligações do nó
        origem->tamanho++;
        
        //Aloca um espaço de memória extra no vetor de apontadores para as ligações do nó
        origem->ligacoes = (ligacao **)realloc(origem->ligacoes,origem->tamanho*sizeof(ligacao *));
        if(origem->ligacoes == NULL){
            free(origem->ligacoes);
            return -1;
        }
    }

    //Aloca memória para a nova ligação
    l_nova = (ligacao *) malloc(sizeof(ligacao));
    if(l_nova == NULL){
        free(origem->ligacoes);
        free(l_nova);
        return -1;
    }

    //Coloca o peso da ligação
    l_nova->peso_ligacao = peso;

    //Coloca o nó de destino
    l_nova->destino = destino;
    
    //Coloca o apontador para a nova ligação no vetor de apontadores do nó origem
    origem->ligacoes[origem->tamanho-1] = l_nova;

    return 0;
}


no_grafo * encontra_no(grafo *g, char *nomeU)
{
    //Casos de erro
    if(!g || nomeU == NULL){
        return NULL;
    }

    //Percorre o vetor de apontadores para nós do grafo
    for(int i = 0 ; i < g->tamanho ; i++){
        //Caso o utilizador do nó seja igual a nomeU, então retorna o apontador para o nó
        if(strcmp(g->nos[i]->nome_user,nomeU) == 0){
            return g->nos[i];
        }
    }

    //Caso não exista o nó, retorna NULL
    return NULL;
}

int ligacao_existe(grafo* g,no_grafo *origem, no_grafo *destino){
    
    //Casos de erro
    if(!g || !origem || !destino){
        return -1;
    }

    //Percorre todos os nós do grafo
    for(int i = 0;i < g->tamanho;i++){
        //Caso o nó a testar seja igual ao nó origem, então vai procurar dentro das ligações do nó a testar
        if(g->nos[i] == origem){
            for(int j = 0; j < g->nos[i]->tamanho; j++){
                //Caso o nó de destino a testar seja igual ao nó destino, então encontrou a ligação
                if(g->nos[i]->ligacoes[j]->destino ==  destino){
                    return 0;
                }
            }
        }  
    }

    //Caso não tenha encontrado, retorna -1
    return -1;
}


grafo * criaGrafo(tabela_dispersao *td)
{
    if(!td){
        return NULL;
    }

    //Cria um novo grafo com tamanho 0
    grafo *g = grafo_novo();

    //Cria um elemento auxiliar para ser utilizado
    elemento *elemaux;

    //Percorre todos os elementos da tabela e insere nós para todos os remetentes e todos os destinatários
    for(int i = 0; i < td->tamanho ; i++){
        elemaux = td->elementos[i];
        
        while(elemaux != NULL){
            //Caso não existam os nós de remetente e destino, então vai inserir
            
            if(encontra_no(g,elemaux->msg->remetente) == NULL){
                no_insere(g,elemaux->msg->remetente);
            }
            
            if(encontra_no(g,elemaux->msg->destinatario) == NULL){
                no_insere(g,elemaux->msg->destinatario);
            }

            elemaux = elemaux->proximo;            
        }
    }

    //Cria o vetor de inteiros para guardar o número de mensagens trocadas entre dois utilizadores, dada pela função 'ligacao2'
    int totMsg[2];
    
    //Percorre todos os elementos da tabela e insere ligações para todas as mensagens
    for(int j = 0; j < td->tamanho; j++){
        elemaux = td->elementos[j];

        while(elemaux!= NULL){
            
            //Caso não exista a ligação, então vai criá-la com o peso presente em totMsg[0];
            if(ligacao_existe(g,encontra_no(g,elemaux->msg->remetente),encontra_no(g,elemaux->msg->destinatario)) !=0){
                
                //Coloca os valores correspondentes no vetor totMsg
                ligacao2(td,elemaux->msg->remetente,elemaux->msg->destinatario,totMsg);

                cria_ligacao(encontra_no(g,elemaux->msg->remetente),encontra_no(g,elemaux->msg->destinatario),totMsg[0]);
            }

            elemaux = elemaux->proximo;
        }
    }

    return g;
}



no_grafo **lista_amigos(grafo *g, char *nomeU, int *n)
{
    //Casos de Erro
    if(g == NULL || nomeU == NULL){
        return NULL;
    }
    
    int i, j, k;
    no_grafo *no_aux, *amigo;

    ligacao *laux;

    //Aloca memória para o vetor de apontadores para nós amigos
    no_grafo **amigos = (no_grafo **)malloc(sizeof(no_grafo *));
    if(amigos == NULL){
        free(amigos);
        return NULL;
    }


    //Inicializa o apontador para o número de amigos a 0
    *n = 0;

    //Coloca em no_aux o apontador para o nó que contem a string 'nomeU'
    no_aux = encontra_no(g, nomeU);

    for(i=0; i<no_aux->tamanho; i++)
    {
        laux = no_aux->ligacoes[i];

        //Procura em cada ligação de no_aux os possíveis amigos
        if(laux->peso_ligacao >= 4)
        {
            //Possível amigo
            amigo = laux->destino;
            
            //Verifica entre as ligações do amigo se também tem pelo menos 4 mensagens enviadas para 'nomeU'
            for(j=0; j<amigo->tamanho; j++)
            {
                if(strcmp(amigo->ligacoes[j]->destino->nome_user, nomeU) == 0 && amigo->ligacoes[j]->peso_ligacao >= 4){
                    (*n)++;

                    //Adiciona espaço para mais uma posição no vetor de apontadores para amigos
                    amigos = (no_grafo **)realloc(amigos, (*n)*sizeof(no_grafo *));
                    if(amigos == NULL){
                        free(amigos);
                        return NULL;
                    }

                    amigos[(*n)-1] = amigo;
                }
            }
        }
    }

    //Caso a lista de amigos não tenha posições, então retorna NULL
    if(*n == 0){
        free(amigos);
        return NULL;
    }

    return amigos;
}


no_grafo ** identifica_ciclo(grafo *g, char *nomeU, int M, int *n)
{
    //Casos de erro
    if(g == NULL || nomeU == NULL || M < 3){
        return NULL;
    }
    
    no_grafo *amigo;
    int i;
    static int count = 1;
    static no_grafo **ciclo;

    static char name[100];
    
    //Guarda o nome do primeiro nó do ciclo
    if(count == 1){
        strcpy(name, nomeU);
    }

    //Coloca o nó a avaliar em 'amigo'
    amigo = encontra_no(g, nomeU);

    for(i=0; i<amigo->tamanho; i++)
    {
        //Caso o contador esteja entre os valores 2 e M e caso o nó inicial tenha o mesmo nome que o destino do nó a avaliar
        if(count > 2 && count <= M && strcmp(name, amigo->ligacoes[i]->destino->nome_user)==0){
            //Atualiza o tamanho do ciclo
            *n = count;

            //Aloca memória para mais um nó no ciclo
            ciclo = (no_grafo **)malloc((*n)*sizeof(no_grafo *));
            if(ciclo == NULL){
                free(ciclo);
                return NULL;
            }

            //Insere na última posição do vetor de apontadores para nós
            ciclo[count-1] = amigo;

            return ciclo;
        }
        else if(count < M){
            //Avança para outro nó
            count++;
            ciclo = identifica_ciclo(g, amigo->ligacoes[i]->destino->nome_user, M, n);

            //Caso o ciclo não esteja vazio, vai para o nó anterior e insere o destino desse nó no ciclo
            if(ciclo != NULL){
                count--;
                ciclo[count-1] = amigo;

                return ciclo;
            }
        }
        else if(i == amigo->tamanho-1){
            //Volta para o nó anterior depois de verificar todas as ligações do nó atual
            count--;
        }
    }   
    return NULL;
}