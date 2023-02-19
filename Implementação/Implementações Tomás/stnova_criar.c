estrutura* st_nova()
{
    estrutura *st = (estrutura *)malloc(sizeof(estrutura));
    if(st == NULL){
        return NULL;
    }

    st->tamanho = 0;

    return st;
}