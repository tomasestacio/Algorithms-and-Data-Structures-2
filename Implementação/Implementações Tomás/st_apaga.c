int st_apaga(estrutura *st)
{
    if(st == NULL){
        return -1;
    }

    element *elem, *aux;
    if(st->tamanho != 0)
    {
        for(int i=0; i<st->tamanho; i++)
        {
            elem = st->elementos[i];
            while(elem != NULL)
            {
                aux = elem->proximo;
                free(elem->msg->texto);
                free(elem->msg);
                free(elem);
                elem = aux;
            }
            st->elementos[i] = NULL;
        }
    ]
    free(st->elementos);
    free(st);

    return 0;
}