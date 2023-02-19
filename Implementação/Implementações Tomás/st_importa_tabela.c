int st_importa_tabela(estrutura *st, tabela_dispersao *td)
{
    if(st == NULL || td == NULL){
        return -1;
    }

    st->tamanho = td->tamanho;

    for(int i=0; i<st->tamanho; i++)
    {
        if(st_insere(st, td->elementos[i]) != -1){
            st_insere(st, td->elementos[i]);
        }
    }

    return 0;
}