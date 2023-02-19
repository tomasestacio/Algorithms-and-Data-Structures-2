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