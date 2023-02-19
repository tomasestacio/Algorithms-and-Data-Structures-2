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