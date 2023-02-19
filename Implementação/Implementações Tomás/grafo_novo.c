grafo* grafo_novo()
{
   //Aloca memória para a estrutura grafo
   grafo *grafo_novo = (grafo*)malloc(sizeof(grafo));
   if(grafo_novo == NULL){                                      //Caso seja impossível criar memória
       return NULL;
   }

    grafo_novo->tamanho = 0;                                    //Inicializa o tamanho a 0

    return grafo_novo;
}