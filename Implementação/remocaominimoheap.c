/******************************************************************************/
/** Este ficheiro representa uma tentativa minha de implementação do código ***/
/* ******************** de remoção do mínimo de uma min-heap ******************/

element removeminimoheap(heap H){
    
    if(H is empty){
        printf(A fila está vazia);
        return NULL;
    }

    H->size--;

    element removido = H->Elements[1];

    int i=1;

    while(H->Elements[2*i] != NULL && H->Elements[2*i +1 ] != NULL){       

        if(min(H->Elements [2*i],H->Elements [2*i+1]) < H->Elements[H->size]){
            
            H->Elements[i]= min(H->Elements [2*i],H->Elements [2*i+1]);
            i = indice_min(H->Elements [2*i],H->Elements [2*i+1]);

        }
        else{
            break;
        }
    }

    H->elements[i] = H->elements[H->size];

    return removido;
}