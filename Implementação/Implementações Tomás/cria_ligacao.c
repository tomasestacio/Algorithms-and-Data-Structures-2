int  cria_ligacao(no_grafo *origem, no_grafo *destino, int peso)
{
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
            return -1;
        }
    }

    //Aloca memória para a nova ligação
    l_nova = (ligacao *) malloc(sizeof(ligacao));
    if(l_nova == NULL){
        return -1;
    }

    //Aloca memória para o destino
    l_nova->destino = (no_grafo *)malloc(sizeof(no_grafo));
    if(l_nova->destino == NULL){
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