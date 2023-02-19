no_grafo * no_insere(grafo *g, char *user)
{
    if(!g || user == NULL){
        return NULL;
    }
    
    //Verifica se já existe o nó
    for(int i = 0; i< g->tamanho;i++){
        if(strcmp(g->nos[i]->nome_user,user)==0){
            return NULL;
        }
    }

    //Caso o grafo não tenha nós, então cria espaço de memória para uma posição no vetor de apontadores para nós
    if(g->tamanho == 0){
        g->nos = (no_grafo **)malloc(sizeof(no_grafo *));
        if(g->nos == NULL){
            return NULL;
        }

        g->tamanho++;
    }
    else{
        //Incrementa o tamanho do grafo onde vamos inserir o novo nó
        g->tamanho++;
        
        //Aloca memória dinâmica para mais uma posição do vetor de apontares para nós
        g->nos = (no_grafo **)realloc(g->nos,g->tamanho*sizeof(no_grafo*)); // ou  g->nos[g->tamanho-1] = (no_grafo *)malloc(sizeof(no_grafo));
        if(g->nos == NULL){
            return NULL;
        }
    }

    //Aloca memória para o novo nó
    no_grafo *novo_no = (no_grafo *)malloc(sizeof(no_grafo));
    if(novo_no == NULL){
        free(g->nos);
        return NULL;
    }

    //Aloca memória para a string que contém o nome do utilizador
    novo_no->nome_user = (char *)malloc(strlen(user)+1);
    if(novo_no->nome_user == NULL){
        free(g->nos);
        free(novo_no);
        return NULL;
    }

    //Coloca o Utilizador e o tamanho de ligações (0) no novo nó
    strcpy(novo_no->nome_user,user);
    novo_no->tamanho = 0;


    //Insere o apontador para o novo nó na ultima posição do vetor de apontadores para nós do grafo
    g->nos[g->tamanho-1] = novo_no;

    return novo_no;
}