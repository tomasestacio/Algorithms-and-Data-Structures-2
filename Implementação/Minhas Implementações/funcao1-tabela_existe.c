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