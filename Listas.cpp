#include <iostream>

typedef struct no {
    int valor;
    struct no *proximo;

} no;

void inserir(no **lista, int num) {
    no *novo = new no();

    if (novo){
        novo->valor = num;
        novo->proximo = *lista;
        *lista = novo;
    }
    else {

    printf("Erro ao alocar memória\n");
    }
}

void inserir_final(no **lista, int num) {
    no *aux, *novo = new no();

    if (novo) {
        novo->valor = num;
        novo-> proximo = NULL;

            if (*lista == NULL) 
                *lista = novo;
            else {
                aux = *lista;
                while(aux->proximo)
                    aux = aux->proximo;
                aux->proximo = novo;
            }

    }
    else
        std:: cout << "Erro ao alocar memória"<< std:: endl;
}

void inserir_qlqr (no **lista, int num, int ant) {
    no *aux,*novo = new no();

    if (novo){
        novo->valor = num;
        if (*lista == NULL){ 
                novo->proximo= NULL;
                *lista = novo;
        }
        else {
            aux = *lista;
            while(aux->valor != ant && aux->proximo)
                aux = aux->proximo;
            novo->proximo = aux->proximo;
            aux->proximo = novo;
                
            }
        
    }
    else 
        std:: cout << "Erro ao alocar memória" << std:: endl;


}

void deletarlista (no *lista){
    no *atual = lista;
    while (atual != NULL) {
        no * proximo2 = atual;
        atual = atual->proximo;
        delete proximo2;
    }
}

void printarlista(no*lista) {

    while(lista) {
        std:: cout << lista->valor << std:: endl;
        lista = lista->proximo;
    }
     
}
void trocar(no*a, no*b) {
    int temp = a->valor;
    a->valor = b->valor;
    b->valor = temp;
}
void Bubblesort (no *lista1) {
  int temp, troca;
  do{
    troca = 0;
    no*lista= lista1;
    while (lista != NULL && lista->proximo!= NULL){
        
        no *depois =lista ->proximo;
        if(lista->valor >= depois->valor) {
            temp = lista->valor;
            lista->valor = depois->valor;
            depois->valor = temp;
            troca = 1;
        }
        lista = lista->proximo;
  }
  }while(troca);
}

no *ordenar_insertion (no*lista, no*novo) {
    if(lista == NULL || lista->valor >= novo->valor) {
      novo->proximo = lista;
      return novo;
    }
    no *atual = lista;

    while(atual->proximo != NULL && atual->proximo->valor < novo->valor) {
        atual = atual->proximo;
    }

    novo->proximo = atual->proximo;
    atual->proximo = novo;
    
    return lista;

}

void insertion_sort(no*lista){
    no*novo = NULL;

    while(lista != NULL){
        no*depois = lista->proximo;
        lista->proximo= NULL;
        novo = ordenar_insertion(novo,lista);
        lista= depois;
    }
    lista = novo;
}

no *meiodalista(no*lista) {
    no* pular2casas =lista->proximo;
    no* pular = lista;

    while(pular2casas != NULL && pular2casas->proximo !=NULL) {
        pular = pular->proximo;
        pular2casas = pular2casas->proximo->proximo;
    }
    return pular;
} 

no* juntarlistas(no * a, no *b) {
    if (a == NULL)
        return b;
    else if (b == NULL)
        return a;
    no *resultado = NULL;
    if (a->proximo <= b->proximo) {
        resultado = a;
        resultado->proximo = juntarlistas(a->proximo, b);
    } else {
        resultado = b;
        resultado->proximo = juntarlistas(a, b->proximo);
    }
    return resultado;
}


no *merge_sort(no*lista) {
    
    if ((lista == NULL) || (lista->proximo == NULL)) {
        return lista;
    }

    no* meio = meiodalista(lista);
    no* lista1 = lista;
    no* lista2 = meio->proximo;
    meio->proximo = NULL;

    lista1 = merge_sort(lista1);
    lista2 = merge_sort(lista2);

    return juntarlistas(lista1,lista2);

}

no *particao(no*lista,no*final,no**novalista,no**novofinal) {
    no* pivo = final;
    no* previo = NULL, *a = lista, *b = pivo;

     while (a != pivo) {
        if (a->valor < pivo->valor) {
           
            if ((*novalista) == NULL)
                (*novalista) = a;
            previo = a;
            a = a->proximo;
        } else {
           
            if (previo)
                previo->proximo = a->proximo;
            no * temp = a->proximo;
            a->proximo = NULL;
            b->proximo = a;
            b = a;
            a = temp;
        }

    }
    if ((*novalista) == NULL){
        (*novalista) = pivo;
    }

    
    (*novofinal) = b;

    
    return pivo;
}

no* acharfinal(no* a) {

    while (a != NULL && a->proximo != NULL)
        a = a->proximo;

    return a;
}

no * coisodoquick(no*lista,no*final) {
    if (!lista || lista == final)
        return lista;

    no* novalista = NULL, *novofinal = NULL;

    
    no* pivo = particao(lista, final, &novalista, &novofinal);

    
    if (novalista != pivo) {
        no * temp = novalista;
        while (temp->proximo != pivo)
            temp = temp->proximo;
        temp->proximo = NULL;

        novalista = coisodoquick(novalista, temp);

        temp = acharfinal(novalista);
        temp->proximo = pivo;
    }

    
    pivo->proximo = coisodoquick(pivo->proximo, novofinal);

    return novalista;
}
void quick_sort(no **lista) {
    (*lista) = coisodoquick(*lista, acharfinal(*lista));
}




int main () {
    no *lista = new no{-1, new no{0, new no{8 , new no{1,NULL}}}};
    
    quick_sort(&lista);
    printarlista(lista);
    deletarlista(lista);
    return 0;
}