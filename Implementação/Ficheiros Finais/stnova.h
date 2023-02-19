/*****************************************************************/
/*   Estrutura nova a implementar | PROG2 | MIEEC | 2019/20   */      
/*****************************************************************/

#ifndef _STNOVA_H_
#define _STNOVA_H_

#include "tabdispersao.h"

/** DESCRIÇÃO DAS ESTRUTURAS
 * "interacao" - Representa uma interação entre um remetente e um destinatário
 * "remetente" - Representa o conjunto de interações cujo remetente é "remetente", ordenadas numa max-heap
 * "estrutura" - Representa o conjunto de remetentes guardados
 * NOTAS : 
     -> Em "estrutura" existem tantos "remetentes" quantos utilizadores existem na tabela de dispersão      
**/

typedef struct struct_elem{
    char destinatario [TAMANHO_CHAVE];  //String com o nome do destinatário da interação
    
    int totMsgs[2];                     //Na posição 0 tem o total de mensagens enviadas do remetente para destinatário // Na posição 1 tem o total de mensagens enviadas pelo destinatário para o remetente

    int prioridade;                     //Contém o número total de mensagens trocadas entre o remetente e o destinatário da interação - definição de prioridade
    
    mensagem **MsgsRemetente;           //Vetor de apontadores para todas as mensagens de remetente para destinatário
} interacao;

typedef struct{
    char remetente [TAMANHO_CHAVE];     //String que contém o nome do remetente

    int totalinteracoes;                //Representa o número de destinatários do "remetente", ou seja, o número de interações de um determinado remetente

    interacao ** interacoes;            //Vetor de apontadores para as interacoes do remetente, organizadas sob a forma de uma max-heap
} remetente;

typedef struct
{
    int totalremetentes;                //Contém o número de remetentes, ou seja, o nº de posições do vetor de apontadores para remetentes
    
    remetente ** remetentes;            //Vetor de apontadores para remetentes
} estrutura;


/**
 * Adiciona um remetente à estrutura
 * Retorna 1 em caso de sucesso ou 0 em caso de erro
 **/
int adiciona_remetente(estrutura* st, char *user1);

/**
 * Cria uma nova interação entre o 'remetente' e um destinatário de nome 'user2'
 * Retorna o remetente atualizado ou NULL em caso de erro
**/
interacao* nova_interacao(remetente* remet1,char *user2);

/**
 * Adiciona uma mensagem à interação entre um utilizador que é 'remetente' e um 'destinatário'
 * PARAMETROS : Interação em que o utilizador é remetente, Interação em que o utilizador é destinatário, Remetente, Destinatário e Texto da mensagem a inserir
 * Retorna a interação atualizada ou NULL em caso de erro
**/
interacao* atualiza_interacoes(interacao *interacao1,interacao * interacao2,const char *remet,const char *dest, const char *texto);

/**
 * Retorna o apontador para a interação cujo remetente é 'remet' e destinatário é 'dest' ou  NULL em caso de erro ou inexistência
 * Retorna por referência a posição da interação no vetor de apontadores para interações de 'remet'
**/
interacao* encontra_interacao(estrutura* st,char *remet, char *dest,int *pos);

/**
 * Retorna o apontador para o remetente cujo nome é 'remet' ou  NULL em caso de erro ou inexistência
 * Retorna por referência a posição do remetente no vetor de apontadores para remetentes de st
**/
remetente* encontra_remetente(estrutura* st, char *remet,int *pos);


/**
 * Retorna um valor boolenano, correspondente à condição "Prioridade de 1 > Prioridade de 2" ou NULL em caso de erro
 */ 
int maior_que(interacao * interacao1, interacao * interacao2);

/**
 * cria e inicializa a estrutura criada
 */
estrutura* st_nova();


/**
 * Tenta inserir o elemento elem na estrutura st, garantindo acesso mais rápido aos elementos 
 * com maior número total de mensagens trocadas.
 * parametro st - apontador para a estrutura criada 
 * parametro elem - elemento que se pretende inserir na estrutura
 * Retorna 0 se bem-sucedida ou -1 em contrário.
 * */
int st_insere(estrutura *st, elemento *elem);


/*
* Importa todo o conteúdo da tabela td para o novo formato de acesso. 
* parametro st - apontador para a estrutura criada 
* parametro td - apontador para a tabela de dispersao
* Retorna 0 se bem-sucedido ou -1 em contrário.
*/
int st_importa_tabela(estrutura *st, tabela_dispersao *td);


/*
* Extrai a instância do par remetente-destinatário com maior soma de mensagens enviadas e recebidas entre eles, 
* levando juntamente todas as mensagens enviadas pelo remetente. 
* parametro st - apontador para a estrutura criada 
* parametro remetente - apontador para o utilizador em que vai procurar o que tem mais ligacoes 
* Retorna apontador para o primeiro elemento de uma lista ligada de ‘elemento’,
* terminada com o campo ‘proximo’ do  último elemento apontando para NULL. Retorna NULL se não for encontrado ou em caso de erro.
* Obs : A instância retornada deverá ser consumida, i.e. não deverá ficar uma cópia dela em ‘st’. 
*/
elemento *st_remove(estrutura *st,char *remetente);

/*
*  Elimina todas as instâncias presentes na estrutura st e desaloca toda a memória da estrutura.
*  parametro st - apontador para a estrutura criada 
*  Retorna 0 se bem-sucedido e -1 se ocorrer algum erro.  
*/
int st_apaga(estrutura *st);


#endif