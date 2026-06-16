#include <stdio.h>
#include <stdlib.h>
#include "lista.h"

Lista *criarLista(){
    Lista *lista = (Lista*) malloc(sizeof(Lista));
    if(lista == NULL){
        return NULL;
    }

    lista->inicio = NULL;   // inicializa a lista vazia.
    return lista;
}

int listaVazia(Lista *lista){
    if(lista == NULL || lista->inicio == NULL){
        return 1;
    }

    return 0;
}

void inserirEmprestimo(Lista *lista, Emprestimo emprestimo){
    if(lista == NULL) return;

    NoLista *novoNo = (NoLista*) malloc(sizeof(NoLista));
    if(novoNo == NULL) return;

    novoNo->emprestimo = emprestimo;
    novoNo->proximo = lista->inicio;
    lista->inicio = novoNo;
}

void listarEmprestimos(Lista *lista){
    if(listaVazia(lista)){
        printf("Nenhum emprestimo foi registrado!\n");
        return;
    }

    printf("=== LISTA DE EMPRESTIMOS ===\n");
    NoLista *aux = lista->inicio;

    while (aux != NULL){
        printf("Usuario: %s\n" , aux->emprestimo.nomeUsuario);
        printf("Livro: %s  | Codigo: %d\n", aux->emprestimo.tituloLivro, aux->emprestimo.codigoLivro);
        printf("-------------------------------\n");
        
        aux = aux->proximo;
    }
}

void liberarLista(Lista *lista){
    if(lista == NULL) return;

    // liberação dos nós internos da lista
    NoLista *aux = lista->inicio;
    while (aux != NULL) {
        lista->inicio = aux->proximo;
        free(aux);
        aux = lista->inicio;
    }

    free(lista); // liberação da estrutura de controle da lista
}

