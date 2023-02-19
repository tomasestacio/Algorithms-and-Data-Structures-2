no_grafo * encontra_no(grafo *g, char *nomeU)
{
    //Casos de erro
    if(!g || nomeU == NULL){
        return NULL;
    }

    //Percorre o vetor de apontadores para nós do grafo
    for(int i = 0 ; i < g->tamanho ; i++){
        //Caso o utilizador do nó seja igual a nomeU, então retorna o apontador para o nó
        if(strcmp(g->nos[i]->nome_user,nomeU) == 0){
            return g->nos[i];
        }
    }

    //Caso não exista o nó, retorna NULL
    return NULL;
}