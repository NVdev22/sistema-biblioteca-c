#include "fila.h"
#include <stdio.h>
#include <stdlib.h>

Fila *criarFila(){
    Fila *fila = (Fila*) malloc(sizeof(Fila));
    if(fila == NULL){
        return NULL;
    }

    // inicializa a fila vazia
    fila->inicio = NULL;
    fila->fim = NULL;
    return fila;
}

int filaVazia(Fila *fila){
    if (fila == NULL || fila->inicio == NULL) {
        return 1;
    }

    return 0;
}

void enfileirarReserva(Fila *fila, Reserva reserva){
    if(fila == NULL) return;

    NoFila *novoNo = (NoFila*) malloc(sizeof(NoFila));
    if(novoNo == NULL){
        return;
    }

    novoNo->reserva = reserva;
    novoNo->proximo = NULL;
    
    // se a fila estiver vazia, o novo nó será o início e o fim
    if(filaVazia(fila)){
       fila->inicio = novoNo;
       fila->fim = novoNo;
    } else {
        fila->fim->proximo = novoNo;
        fila->fim = novoNo;
    }
}

Reserva desenfileirarReserva(Fila *fila){
    
    // retorna uma reserva inválida caso a fila esteja vazia
    if(filaVazia(fila)){
        Reserva reservaVazia = {"", -1};
        return reservaVazia;
    }

    NoFila *removido = fila->inicio;
    Reserva reserva = removido->reserva;
    fila->inicio = removido->proximo;

    // se a fila ficou vazia após a remoção, ajusta o ponteiro do fim
    if(fila->inicio == NULL){
        fila->fim = NULL;
    }

    free(removido);
    return reserva;
}

void exibirReservas(Fila *fila){
    if(filaVazia(fila)){
        printf("Nao ha nenhuma reserva!\n");
        return;
    }

    NoFila *aux = fila->inicio; 
    
    printf("============ Reservas ============\n");
    while(aux != NULL){
        printf("Usuario: %s\n", aux->reserva.nomeUsuario);
        printf("Codigo do livro: %d\n", aux->reserva.codigoLivro);
        printf("----------------------------------------------------\n");
        aux = aux->proximo;
    }
}

void liberarFila(Fila *fila){
    if (fila == NULL) return;

    // Liberação dos nós internos da fila
    NoFila *aux = fila->inicio;
    while (aux != NULL){
        fila->inicio = aux->proximo;
        free(aux);
        aux = fila->inicio;
    }

    free(fila);     // Liberação da estrutura de controle da fila
}
