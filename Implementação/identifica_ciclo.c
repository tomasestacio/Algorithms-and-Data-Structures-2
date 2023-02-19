no_grafo ** identifica_ciclo(grafo *g, char *nomeU, int M, int *n)
{
    if(g == NULL || nomeU == NULL || M < 3){
        return NULL;
    }
    
    no_grafo *amigo;
    int i;
    static int count = 1;
    static no_grafo **ciclo;

    static char name[100];
    //guardar o primeiro nome do primeiro nó
    if(count == 1){
        strcpy(name, nomeU);
    }

    amigo = encontra_no(g, nomeU);

    for(i=0; i<amigo->tamanho; i++)
    {
        if(count > 2 && count <= M && strcmp(name, amigo->ligacoes[i]->destino->nome_user)==0){
            *n = count;
            ciclo = (no_grafo **)malloc((*n)*sizeof(no_grafo *));
            if(ciclo == NULL){
                return NULL;
            }
            ciclo[count-1] = amigo;
            return ciclo;
        }
        else if(count < M){
            count++;
            ciclo = identifica_ciclo(g, amigo->ligacoes[i]->destino->nome_user, M, n);
            if(ciclo != NULL){
                count--;
                ciclo[count-1] = amigo;
                return ciclo;
            }
        }
        else if(i == amigo->tamanho-1){
            count--;
        }
    }   
    return NULL;
}