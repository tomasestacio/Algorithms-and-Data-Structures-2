void grafo_apaga(grafo* g)
{
    
    if(g == NULL){
        return;
    }
    //liberta vetor e estrutura
    if(g->tamanho != 0)
    {
        for(int i=0; i<g->tamanho; i++)
        {
            if(g->nos[i]->tamanho != 0)
            {
                for(int j=0; j<g->nos[i]->tamanho; j++)
                {
                    free(g->nos[i]->ligacoes[j]);
                }
                free(g->nos[i]->ligacoes);
            }
            free(g->nos[i]->nome_user);
            free(g->nos[i]);
        }
        free(g->nos);
    }

    free(g);
        
    return;
}