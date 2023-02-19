/*****************************************************************/
/*         Tabela de Dispersao | PROG2 | MIEEC | 2019/20         */
/*****************************************************************/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "tabdispersao.h"

/**FUNÇÃO AUXILIAR
 * Verifica se o utilzador 'user' existe na tabela 'td' como remetente ou como destinatário
 * Retorna 0 se existe ou -1 em caso de inexistência ou erro
**/ 
int utilizador_existe(tabela_dispersao *td,char *user);

tabela_dispersao* tabela_nova(int tamanho, hash_func *hfunc)
{
    /* aloca memoria para a estrutura tabela_dispersao */
    if (hfunc == NULL)
        return NULL;

    tabela_dispersao *t = (tabela_dispersao*) malloc(sizeof (tabela_dispersao));
    if (t == NULL){
        free(t);
        return NULL;
    }

    /* aloca memoria para os elementos */
    t->elementos = (elemento **) calloc(tamanho, sizeof (elemento*));
    if (t->elementos == NULL) {
        free(t->elementos);
        free(t);
        return NULL;
    }

    t->tamanho = tamanho;
    t->hfunc = hfunc;

    return t;
}

void tabela_apaga(tabela_dispersao *td)
{
    if (td == NULL) return;

    /* esvazia tabela*/
    tabela_esvazia(td);

    /* liberta vector e estrutura */
    free(td->elementos);
    free(td);
}

int tabela_adiciona(tabela_dispersao *td, const char *remet,const char *dest, const char *texto)  //valor = texto // dest //remet=chave
{
    int index;
    elemento * elem, *elemaux;

    if (!td || !texto|| !dest || !remet) return TABDISPERSAO_ERRO;

    /* aloca memoria para o elemento */
        elem = (elemento*) malloc(sizeof (elemento));
        if (elem == NULL){
            free(elem);
            return TABDISPERSAO_ERRO;
        }

        /* aloca memoria para o mensagem*/
        elem->msg = (mensagem*) malloc(sizeof (mensagem));
        if (elem->msg == NULL)
        {   
            free(elem->msg);
            free(elem);
            return TABDISPERSAO_ERRO;
        }
        /* aloca memoria para o texto da mensagem*/
         elem->msg->texto = malloc(strlen(texto)+1);
        if (elem->msg->texto == NULL)
        {   
            free(elem->msg->texto);
            free(elem->msg);
            free(elem);
            return TABDISPERSAO_ERRO;
        }
        /*copia chave e valor */
        
        strcpy(elem->msg->remetente, remet);
        strcpy(elem->msg->destinatario, dest);
        strcpy(elem->msg->texto,texto );


    /* calcula hash para a string a adicionar */
    index = td->hfunc(remet, td->tamanho);

    /* verifica se chave ja' existe na lista */
    elemaux = td->elementos[index];
   

    if (elemaux == NULL)
    {
        /* novo elemento, chave nao existe na lista */

        /* insere no inicio da lista */
        elem->proximo = NULL;
        td->elementos[index] = elem;
    } else {
      
        elem->proximo = elemaux;
        td->elementos[index] = elem;
       
    }

    return TABDISPERSAO_OK;
}


int tabela_existe(tabela_dispersao *td, const char *remetente)
{
    if(!td || remetente == NULL){
        return -1;
    }

    int index;                                      //Inteiro para guardar o indice do vetor correspondente à chave
    elemento *elemaux;                              //Elemento auxiliar 


    index = td->hfunc(remetente,td->tamanho);       //Atribui o valor à chave
    elemaux = td->elementos[index];                 //Elemaux passa a ser o elemento correspondente à chave

    int num_msg = 0;            //Inteiro que guardará o número de mensagens de um remetente

    //Ciclo que atualiza o nº de mensagens do remetente caso ele exista, enquanto não chega ao fim da lista
    while(elemaux!= NULL){
        if(strcmp(remetente,elemaux->msg->remetente)==0){       // Caso o remetente do elemento da lista seja o remetente a procurar, atualiza
            num_msg++;           
        }
        elemaux = elemaux->proximo;   
    }

    return num_msg;                                 //Note-se que, se o remetente não existir, não entra no ciclo while, logo retorna 0
}

mensagem **tabela_listagem(tabela_dispersao *td, const char *remetente)
{
    //Casos de erro
    if(td == NULL || remetente == NULL){
        return NULL;
    }
    
    mensagem **msg_aux;
    elemento *elemaux;
    int i, j=0, tbl, index;

    tbl = tabela_existe(td, remetente);
    
    //Se tbl = -1, então o utilizador não existe
    if(tbl == -1){
        return NULL;
    } 

    //Aloca memória para todos os elementos de mensagem
    msg_aux = (mensagem **) malloc((tbl+1)*sizeof(mensagem *));
    if(msg_aux == NULL){
        free(msg_aux);
        return NULL;
    }

    //Verifica a posicao do remetente no vetor de elementos
    index = td->hfunc(remetente, td->tamanho);
    elemaux = td->elementos[index];

    //Enquanto existem mensagens, verifica se são do remetente e insere-las na lista de apontadores de msg
    while(elemaux != NULL){

        if(strcmp(elemaux->msg->remetente, remetente)==0){
            msg_aux[j] = elemaux->msg;
            j++;
        }      
        elemaux = elemaux->proximo;
    }

    // Última posição do vetor de mensagens é NULL
    // * Note-se que se tbl = 0, então não entra no ciclo while anterior e o vetor apenas tem uma posição (NULL)
    msg_aux[j] = NULL;

    return msg_aux;
}

int tabela_esvazia(tabela_dispersao *td)
{
     int i;
    elemento * elem, * aux;

    if (!td) return TABDISPERSAO_ERRO;

    /* para cada entrada na tabela */
    for (i = 0; i < td->tamanho; i++)
    {
        /* apaga todos os elementos da entrada */
        elem = td->elementos[i];
        while(elem != NULL)
        {
            aux = elem->proximo;
            free(elem->msg->texto);
            free(elem->msg);
            free(elem);
            elem = aux;
        }
        td->elementos[i] = NULL;
    }
    return TABDISPERSAO_OK;
}




unsigned long hash_krm(const char* chave, int tamanho)
{
	int c, t = strlen(chave);
    unsigned long hash = 7;
    
    for(c = 0; c < t; c++)
    {
        hash += (int) chave[c];
    
    }

    return hash % tamanho;

    return 0;
}



tabela_dispersao* tabela_carrega(char *ficheiro,int tamanho)
{
    FILE *f = fopen(ficheiro, "r");
    if(f == NULL) 
        return NULL;
    
    tabela_dispersao *td = tabela_nova(tamanho,hash_krm);
    if(td == NULL)
    {
        fclose(f);
        return NULL;
    }

    int count=0;
    char str_aux[1024] = {};
    char remetente[TAMANHO_CHAVE] = {0};
    char destinatario[TAMANHO_CHAVE] = {0};
    char *token;
   
    

    while((fgets(str_aux, 1024, f)) != NULL)
    {
        
        str_aux[strlen(str_aux)-1] = '\0';

        count++;  
        token = strtok(str_aux, "\\");
        
        strcpy(remetente,token);
        token = strtok(NULL, "\\");
    
        strcpy(destinatario,token);
    
        token = strtok(NULL, "");
    
        if (token==NULL) 
            token=" ";
        
        if (tabela_adiciona(td, remetente,destinatario,token)==-1)
        {
            tabela_apaga(td);
            fclose(f);
            return NULL;
        }
           
  
    }
    
    fclose(f);
    return td; 
}

int utilizador_existe(tabela_dispersao *td,char *user){
    if(!td || user == NULL){
        return -1;
    }

    elemento *elemaux;
    int U1existe = -1;

    for(int i = 0;i < td->tamanho;i++){           //Percorre todas as posições do vetor de listas
        elemaux = td->elementos[i];               //Percorre todos os elementos das listas

        if(U1existe == 0) break;

        while(elemaux!=NULL){
            if(strcmp(user,elemaux->msg->remetente)==0 || strcmp(user,elemaux->msg->destinatario)==0){
                U1existe = 0;                     //Caso U1 exista como remetente ou utilizador, U1existe passa a ser 0
                break;
            }

            elemaux = elemaux->proximo;
        }
    }

    return U1existe;
}

void ligacao2(tabela_dispersao *td, char *nomeU1, char *nomeU2, int totMsg[2])
{
    //Caso a tabela não exista, então o vetor fica com todas as posições a -1
    if(!td){                        
        totMsg[0]=-1;
        totMsg[1]=-1;
        return;
    }

    //Descrição das variáveis do tipo int:
    // * index1 e index2 são os indices correspondentes às chaves
    // * countU1 e countU2 são os contadores para o número de mensagens trocadas
    
    int index1,index2,countU1 = 0,countU2 = 0;          
    
    elemento *elemaux, *elemauxU1, *elemauxU2;
    
    //Caso U1 não exista como remetente ou destinatário
    if(utilizador_existe(td,nomeU1) == -1){                          
        totMsg[0] = -1;
    }
    else{
        index1 = td->hfunc(nomeU1,td->tamanho);
        elemauxU1 = td->elementos[index1];

        while(elemauxU1 != NULL){
            if(strcmp(nomeU1,elemauxU1->msg->remetente)==0 && strcmp(nomeU2,elemauxU1->msg->destinatario)==0){
                countU1++;
            }
            
            elemauxU1=elemauxU1->proximo;
        }

        totMsg[0] = countU1;
    }

    //Caso U2 não exista como remetente ou destinatário
    if(utilizador_existe(td,nomeU2) == -1){                         
        totMsg[1] = -1;
    }
    else{
        index2 = td->hfunc(nomeU2,td->tamanho);
        elemauxU2 = td->elementos[index2];

        while(elemauxU2 != NULL){
            if(strcmp(nomeU2,elemauxU2->msg->remetente)==0 && strcmp(nomeU1,elemauxU2->msg->destinatario)==0){
                countU2++;
            }
            
            elemauxU2=elemauxU2->proximo;
        }
        totMsg[1] = countU2;
    }
    return;
}
