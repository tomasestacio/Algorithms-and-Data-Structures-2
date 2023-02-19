void ligacao2(tabela_dispersao *td, char *nomeU1, char *nomeU2, int totMsg[2])
{
    //Caso a tabela não exista, então o vetor fica com todas as posições a -1
    if(!td){                        
        totMsg[0]=-1;
        totMsg[1]=-1;
        return;
    }

    //Descrição das variáveis do tipo int:
    // * U1existe e U2existe avaliam a existência de utilizador (0 se existe, -1 se não existe)
    // * index1 e index2 são os indices correspondentes às chaves
    // * countU1 e countU2 são os contadores para o número de mensagens trocadas
    
    int U1existe = -1,U2existe = -1,index1,index2,countU1 = 0,countU2 = 0;          
    
    elemento *elemaux, *elemauxU1, *elemauxU2;
    
    //---------------------- Início da verificação da existência de Utilizadores ----------------------------------------------//
    for(int i = 0;i<td->tamanho;i++){           //Percorre todas as posições do vetor de listas
        elemaux = td->elementos[i];             //Percorre todos os elementos das listas

        if(U1existe == 0) break;

        while(elemaux!=NULL){
            if(strcmp(nomeU1,elemaux->msg->remetente)==0 || strcmp(nomeU1,elemaux->msg->destinatario)==0){
                U1existe = 0;                     //Caso U1 exista como remetente ou utilizador, U1existe passa a ser 0
                break;
            }

            elemaux = elemaux->proximo;
        }
    }

    for(int j = 0;j <td->tamanho;j++){          //Percorre todas as posições do vetor de listas
        elemaux = td->elementos[j];             //Percorre todos os elementos das listas

        if(U2existe == 0) break;

        while(elemaux!=NULL){
            if(strcmp(nomeU2,elemaux->msg->remetente)==0 || strcmp(nomeU2,elemaux->msg->destinatario)==0){
                U2existe = 0;                     //Caso U2 exista como rementente ou utilizador, U2existe passa a ser 0
                break;
            }
            
            elemaux = elemaux->proximo;
        }
    }
    //--------------------------------------- Fim da verificação da existência de Utilizadores ----------------------------------//

    //Caso U1 não exista como remetente ou destinatário
    if(U1existe == -1){                          
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
    if(U2existe == -1){                         
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
