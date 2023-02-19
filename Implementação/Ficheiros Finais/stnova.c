/*****************************************************************/
/*   Estrutura nova a implementar | PROG2 | MIEEC | 2019/20   */      
/*****************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stnova.h"

#define RAIZ 		(1)
#define PAI(x) 		(x/2)
#define FILHO_ESQ(x) 	(x*2)
#define FILHO_DIR(x) 	(x*2+1)

int adiciona_remetente(estrutura* st, char *user1){
    //Casos de erro
    if(!st || user1 == NULL){
        return 0;
    }
    
    //Aloca espaço de memória para o novo remetente
    remetente *novo_remetente = (remetente *)malloc(sizeof(remetente));
    if(novo_remetente == NULL){
        free(novo_remetente);
        return 0;
    }
    
    //Atualiza os campos do novo remetente
    strcpy(novo_remetente->remetente,user1);
    novo_remetente->totalinteracoes = 0;

    //Aloca espaço de memória para (mais) um remetente na estrutura
    if(st->totalremetentes == 0){
        st->remetentes = (remetente **)malloc(sizeof(remetente *));
        if(st->remetentes == NULL){
            free(novo_remetente);
            free(st->remetentes);
            return 0;
        }

        st->totalremetentes++;
    }
    else{
        st->totalremetentes ++;

        st->remetentes = (remetente **)realloc(st->remetentes,st->totalremetentes*sizeof(remetente *));
        if(st->remetentes == NULL){
            free(novo_remetente);
            free(st->remetentes);
            return 0;
        }
    }

    //Coloca o apontador para o remetente na última posição do vetor
    st->remetentes[st->totalremetentes-1] = novo_remetente;

    return 1;
}


interacao* nova_interacao(remetente* remet1,char *user2){
    //Casos de erro
    if(remet1 == NULL || user2 == NULL){
        return NULL;
    }

    //Aloca espaço para a nova interação
    interacao *nova_interacao = (interacao *)malloc(sizeof(interacao));
    if(nova_interacao == NULL){
        free(nova_interacao);
        return NULL;
    }

    int pos;

    //Inicializa os contadores de mensagens a 0
    nova_interacao->prioridade = 0;
    nova_interacao->totMsgs[0] = 0;
    nova_interacao->totMsgs[1] = 0;

    //Copia o nome do destinatário para a string correspondente
    strcpy(nova_interacao->destinatario,user2);

    //Aloca espaço de memória para (mais) uma interação no vetor de interações do remetente
    if(remet1->totalinteracoes == 0){
        remet1->interacoes = (interacao **)malloc(2*sizeof(interacao *));
        if(remet1->interacoes == NULL){
            free(remet1->interacoes);
            free(remet1);
            free(nova_interacao);
            return NULL;
        }

        remet1->totalinteracoes++;
    }
    else{
        remet1->totalinteracoes++;
        
        remet1->interacoes = (interacao **)realloc(remet1->interacoes,(remet1->totalinteracoes + 1)*sizeof(interacao *));
        if(remet1->interacoes == NULL){
            free(remet1->interacoes);
            free(remet1);
            free(nova_interacao);
            return NULL;
        }
    }

    //Coloca o apontador para a interação na última posição da heap
    int j = remet1->totalinteracoes;
    remet1->interacoes[j] = nova_interacao;


    return nova_interacao;
}

//Coloca o apontador para uma mensagem no vetor de apontadores para as mensagens, incrementa o número de mensagens e atualiza a prioridade
interacao* atualiza_interacoes(interacao *interacao1,interacao *interacao2, const char *remet,const char *dest, const char *texto){
    if(!interacao1 || !interacao2 || remet == NULL || dest == NULL || texto == NULL){
        return NULL;
    }

    //Aloca memória para a mensagem
    mensagem *msg = (mensagem *)malloc(sizeof(mensagem));
    if(msg == NULL){
        free(msg);
        return NULL;
    }

    //Aloca memória para o texto da mensagem
    msg->texto = (char *)malloc(strlen(texto)+1);
    if(msg->texto == NULL){
        free(msg->texto);
        free(msg);
        return NULL;
    }

    //Copia as strings
    strcpy(msg->texto,texto);
    strcpy(msg->remetente,remet);
    strcpy(msg->destinatario,dest);

    //Caso o número de mensagens enviadas pelo remetente esteja a 0
    if(interacao1->totMsgs[0] == 0){
        interacao1->MsgsRemetente = (mensagem **)malloc(sizeof(mensagem *));
        if(interacao1->MsgsRemetente == NULL){
            free(interacao1->destinatario);
            free(interacao1->MsgsRemetente);
            free(interacao1);
            free(msg->texto);
            free(msg);
            return NULL;
        }

        //Atualiza os campos com o número de mensagens em ambas as interações
        interacao1->totMsgs[0] ++;
        interacao2->totMsgs[1] ++;
        interacao1->prioridade ++;
        interacao2->prioridade ++;
    }
    else{
        interacao1->totMsgs[0]++;
        interacao2->totMsgs[1]++;
        interacao1->prioridade ++;
        interacao2->prioridade ++;

        interacao1->MsgsRemetente = (mensagem **)realloc(interacao1->MsgsRemetente,(interacao1->totMsgs[0])*sizeof(mensagem *));
        if(interacao1->MsgsRemetente == NULL){
            free(interacao1);
            free(msg->texto);
            free(msg);
            return NULL;
        }
    }

    //Coloca o apontador para a mensagem no vetor para apontadores de mensagens enviadas pelo remetente da interação
    int j = interacao1->totMsgs[0];
    interacao1->MsgsRemetente[j-1] = msg;

    return interacao1;
}

interacao* encontra_interacao(estrutura* st,char *remet, char *dest,int *pos){
    if(!st || remet == NULL || dest ==  NULL){
        return NULL;
    }

    *pos = -1;

    for(int i = 0; i < st->totalremetentes; i++){
        if(strcmp(st->remetentes[i]->remetente,remet) == 0){
            for(int k = 1; k <= st->remetentes[i]->totalinteracoes; k++){
                if(strcmp(st->remetentes[i]->interacoes[k]->destinatario,dest) == 0){
                    *pos = k;
                    return st->remetentes[i]->interacoes[k];
                }
            }
        }
    }

    return NULL;
}

remetente* encontra_remetente(estrutura* st, char *remet,int *pos){
    if(!st || remet == NULL){
        return NULL;
    }

    *pos = -1;

    for(int i = 0; i < st->totalremetentes; i++){
        if(strcmp(st->remetentes[i]->remetente,remet) == 0){
            *pos = i;
            return st->remetentes[i];
        }
    }

    return NULL;
}

estrutura* st_nova()
{
    //Aloca memória para a estrutura
    estrutura *st = (estrutura *)malloc(sizeof(estrutura));
    if(st == NULL){
        free(st);
        return NULL;
    }

    //Coloca a 0 o total de interações
    st->totalremetentes = 0;

    return st;
}

int st_insere(estrutura *st, elemento *elem)
{
    //Casos de erro
    if(!st || !elem){
        return -1;
    }

    int teste[2],pos;
    interacao *interacao1,*interacao2;
    
    //Inserir os dois remetentes caso não existam
    if(encontra_remetente(st,elem->msg->remetente,&pos) == NULL){
        teste[0] = adiciona_remetente(st,elem->msg->remetente);

        //Caso não dê para adicionar, termina o programa
        if(teste[0] == 0){
            return -1;
        }
    }
    if(encontra_remetente(st,elem->msg->destinatario,&pos) == NULL){
        teste[1] = adiciona_remetente(st,elem->msg->destinatario);

        //Caso não dê para adicionar, termina o programa
        if(teste[1] == 0){
            return -1;
        }
    }


    //Verificar se existem as interações e adicioná-las caso não existam
    if(encontra_interacao(st,elem->msg->remetente,elem->msg->destinatario,&pos) == NULL){
        interacao1 = nova_interacao(encontra_remetente(st,elem->msg->remetente,&pos),elem->msg->destinatario);

        if(interacao1 == NULL){
            return -1;
        }
    }
    if(encontra_interacao(st,elem->msg->destinatario,elem->msg->remetente,&pos) == NULL){
        interacao2 = nova_interacao(encontra_remetente(st,elem->msg->destinatario,&pos),elem->msg->remetente);

        if(interacao2 == NULL){
            return -1;
        }
    }

    int remet1,remet2,index1,index2;
    interacao *interacaoaux1, *interacaoaux2;

    //Insere a mensagem na interação 1, atualizando as prioridades e os totais de mensagens nas duas interações
    atualiza_interacoes(encontra_interacao(st,elem->msg->remetente,elem->msg->destinatario,&index1),encontra_interacao(st,elem->msg->destinatario,elem->msg->remetente,&index2),elem->msg->remetente,elem->msg->destinatario,elem->msg->texto);

    //Atualizar as heaps nas duas interações

    encontra_remetente(st,elem->msg->remetente,&remet1);
    encontra_remetente(st,elem->msg->destinatario,&remet2);

   
    //Organiza o vetor de apontadores para as interações de acordo com a prioridade, ou seja, o total de mensagens
    //Enquanto elemento for mais prioritario do que o respetivo pai, troca-os //
	while (index1 != RAIZ && maior_que(st->remetentes[remet1]->interacoes[index1], st->remetentes[remet1]->interacoes[PAI(index1)])){
		interacaoaux1 = st->remetentes[remet1]->interacoes[PAI(index1)];
		st->remetentes[remet1]->interacoes[PAI(index1)] = st->remetentes[remet1]->interacoes[index1];
		st->remetentes[remet1]->interacoes[index1] = interacaoaux1;
		index1 = PAI(index1);
	}

    while (index2 != RAIZ && maior_que(st->remetentes[remet2]->interacoes[index2], st->remetentes[remet2]->interacoes[PAI(index2)])){
		interacaoaux2 = st->remetentes[remet2]->interacoes[PAI(index2)];
		st->remetentes[remet2]->interacoes[PAI(index2)] = st->remetentes[remet2]->interacoes[index2];
		st->remetentes[remet2]->interacoes[index2] = interacaoaux2;
		index2 = PAI(index2);
	}

	return 0;
}

int maior_que(interacao * interacao1, interacao * interacao2)
{
	if (interacao1 == NULL || interacao2 == NULL)
	{
		return -1;
	}

	return interacao1->prioridade > interacao2->prioridade;
}

int st_importa_tabela(estrutura *st, tabela_dispersao *td)
{
    if(!st || !td){
        return -1;
    }
    
    elemento *elemaux;
    int insere;

    //Percorre a tabela e adiciona todos os elementos
    // Nota: Caso seja impossível inserir algum elemento, retorna -1
   
    for(int i = 0; i< td->tamanho ; i++){
        elemaux = td->elementos[i];

        while(elemaux!=NULL){
            
            insere = st_insere(st,elemaux);
            if(insere == -1){
                return -1;
            }
            
            elemaux = elemaux->proximo;
        }
    }

    return 0;
}

elemento *st_remove(estrutura *st,char *remetente)
{
    int pos;

    if(!st || remetente == NULL || encontra_remetente(st,remetente,&pos) == NULL){
        return NULL;
    }

    int j, filho_maior;
    interacao *interacaoaux;
    elemento *elem_inicio = NULL,*elemaux1,*elemaux2;

    //Percorre todos os remetentes da estrutura
    for(int i = 0; i < st->totalremetentes; i++){
        //Caso encontre o remetente
        if(strcmp(st->remetentes[i]->remetente,remetente) == 0){
            
            //Pega na interação com maior prioridade
            interacaoaux = st->remetentes[i]->interacoes[1];

            //Guarda todas as mensagens dessa interação na lista de elementos
            for(int k = 0; k < interacaoaux->totMsgs[0];k++){
                
                //Caso seja a primeira mensagem a guardar
                if(k == 0){
                    elem_inicio = (elemento *)malloc(sizeof(elemento));
                    if(elem_inicio == NULL){
                        free(elem_inicio);
                        return NULL;
                    }
                    
                    //Guarda o inicio da lista
                    elem_inicio->msg = interacaoaux->MsgsRemetente[k];
                    elem_inicio->proximo = NULL;
                    
                    st->remetentes[i]->interacoes[1]->MsgsRemetente[k] = NULL;
                }
                else{
                    elemaux2 = (elemento *)malloc(sizeof(elemento));
                    if(elemaux2 == NULL){
                        free(elemaux2);
                        free(elem_inicio);
                        return NULL;
                    }

                    elemaux2->msg = interacaoaux->MsgsRemetente[k];
                    elemaux2->proximo = NULL;

                    elemaux1 = elem_inicio;

                    while(elemaux1->proximo != NULL){
                        elemaux1 = elemaux1->proximo;
                    }

                    elemaux1->proximo = elemaux2;

                    st->remetentes[i]->interacoes[1]->MsgsRemetente[k] = NULL;
                }
            }

            int count = interacaoaux->totMsgs[0];
            
            //Atualiza o total de mensagens enviadas pelo remetente e a prioridade na interacao
            st->remetentes[i]->interacoes[1]->totMsgs[0] = 0;
            st->remetentes[i]->interacoes[1]->prioridade -= count;

            //Atualiza o vetor de interações do remetente, de acordo com a nova prioridade...

            //Coloca ultima interacao da heap na raiz
            st->remetentes[i]->interacoes[RAIZ] = st->remetentes[i]->interacoes[st->remetentes[i]->totalinteracoes];

            //Coloca a antiga interacao da raiz como última interacao
            st->remetentes[i]->interacoes[st->remetentes[i]->totalinteracoes] = interacaoaux;

            j = RAIZ;

            //enquanto nao chegar 'a base da heap
            while(FILHO_ESQ(j) <= st->remetentes[i]->totalinteracoes){
                filho_maior = FILHO_ESQ(j);

                //Verifica se existe filho 'a direita e se este e' mais prioritario do que 'a esquerda
                if (FILHO_DIR(j) <= st->remetentes[i]->totalinteracoes && maior_que(st->remetentes[i]->interacoes[FILHO_DIR(j)], st->remetentes[i]->interacoes[FILHO_ESQ(j)]))
                    filho_maior = FILHO_DIR(j);

                // Enquanto elemento for mais prioritario do que o respetivo pai, troca-os
                if (maior_que(st->remetentes[i]->interacoes[filho_maior], st->remetentes[i]->interacoes[j]))
                {
                    interacaoaux = st->remetentes[i]->interacoes[filho_maior];
                    st->remetentes[i]->interacoes[filho_maior] = st->remetentes[i]->interacoes[j];
                    st->remetentes[i]->interacoes[j] = interacaoaux;
                    j = filho_maior;
                }
                else
                    break;
            }
        }
    }

    return elem_inicio;
}


int st_apaga(estrutura *st)
{
    if(!st){
        return -1;
    }

    //Verifica se existem remetentes
    if(st->totalremetentes != 0){
        //Apaga cada 'remetente'
        for(int i = 0 ; i < st->totalremetentes; i++){
            //Dentro de cada remetente, verifica se existem interações
            if(st->remetentes[i]->totalinteracoes!=0){
                //Apaga cada interação
                for(int j = 1; j <= st->remetentes[i]->totalinteracoes; j++){
                    //Dentro de cada interação, verifica se existem mensagens enviadas pelo remetente
                    if(st->remetentes[i]->interacoes[j]->totMsgs[0] != 0){
                        //Apaga cada mensagem enviada
                        for(int k = 0; k < st->remetentes[i]->interacoes[j]->totMsgs[0]; k++){
                            free(st->remetentes[i]->interacoes[j]->MsgsRemetente[k]->texto);
                            free(st->remetentes[i]->interacoes[j]->MsgsRemetente[k]);
                        }
                        free(st->remetentes[i]->interacoes[j]->MsgsRemetente);
                    }

                    free(st->remetentes[i]->interacoes[j]);
                }

                free(st->remetentes[i]->interacoes);
            }

            free(st->remetentes[i]);
        }
        free(st->remetentes);
    }

    //Liberta a estrutura
    free(st);

    return 0;
}


