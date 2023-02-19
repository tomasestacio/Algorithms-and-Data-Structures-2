ligacao * encontra_ligacao(grafo* g,no_grafo *origem, no_grafo *destino){
    
    //Casos de erro
    if(!g || !origem || !destino){
        return NULL;
    }

    //Percorre todos os nós do grafo
    for(int i = 0;i < g->tamanho;i++){
        //Caso o nó a testar seja igual ao nó origem, então vai procurar dentro das ligações do nó a testar
        if(g->nos[i] == origem){
            for(int j = 0; j < g->nos[i]->tamanho; j++){
                //Caso o nó de destino a testar seja igual ao nó destino, então encontrou a ligação
                if(g->nos[i]->ligacoes[j]->destino ==  destino){
                    return g->nos[i]->ligacoes[j];
                }
            }
        }  
    }

    //Caso não tenha encontrado, retorna NULL
    return NULL;
}