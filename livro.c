#include "livro.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


Livro *criarLivro(int codigo, char titulo[], char autor[], int anoPublicacao, int quantidadeTotal){
    Livro *livro = (Livro*) malloc(sizeof(Livro));
    
    if(livro == NULL){
        return NULL;
    }
    
    livro->codigo = codigo;
    strcpy(livro->titulo, titulo);
    strcpy(livro->autor, autor);
    livro->anoPublicacao = anoPublicacao;
    livro->quantidadeTotal = quantidadeTotal;
    livro->quantidadeDisponivel = quantidadeTotal;

    // Alocação da fila exclusiva de reservas do livro
    livro->filaReserva = criarFila();
    if(livro->filaReserva == NULL){
        free(livro); // Se a fila falhar, desfaz a alocação do livro para não vazar memória
        return NULL;
    }

    return livro;
}

void exibirLivro(Livro *livro){
    if(livro == NULL){
        printf("Livro nao encontrado!\n");
        return;
    }

    printf("===================================================\n");
    printf("CODIGO: %d\n", livro->codigo);
    printf("TITULO: %s\n", livro->titulo);
    printf("AUTOR: %s\n", livro->autor);
    printf("ANO de Publicacao: %d\n", livro->anoPublicacao);
    printf("---------------------------------------------------\n");
    printf("TOTAL de Exemplares: %d\n", livro->quantidadeTotal);
    printf("Disponiveis para Emprestimos: %d\n", livro->quantidadeDisponivel);
    printf("===================================================\n");
}

void emprestarExemplar(Livro *livro){
    if (livro == NULL) return;

    // se tiver exemplar disponível, decrementa 
    if(livro->quantidadeDisponivel > 0) {
        livro->quantidadeDisponivel--;
    } else {
        printf("Nao ha exemplares disponiveis deste livro no momento!\n");
    }
}

void devolverExemplar(Livro *livro){
    if (livro == NULL) return;

    if(livro->quantidadeDisponivel < livro->quantidadeTotal) {
        livro->quantidadeDisponivel++;
    } else {
        printf("Todos os exemplares deste livro ja estao no estoque!\n");
    }
}

void liberarLivro(Livro *livro) {
    if (livro == NULL) return;
    
    // Libera a fila interna primeiro
    if (livro->filaReserva != NULL) {
        liberarFila(livro->filaReserva);
    }
    
    // Depois libera a estrutura do livro
    free(livro);
}

int obterCodigoLivro(Livro *livro){
    if (livro == NULL) return -1;
    return livro->codigo;
}

char *obterTituloLivro(Livro *livro){
    if (livro == NULL) {
        return NULL;
    }

    return livro->titulo;
}

Fila *obterFilaReserva(Livro *livro){
    if (livro == NULL) {
        return NULL;
    }

    return livro->filaReserva;
}

int obterQuantidadeDisponivel(Livro *livro){
    if (livro == NULL) return 0;
    return livro->quantidadeDisponivel;
}

int livroEstaEmprestado(Livro *livro){
    if(livro == NULL) return 0;
    return obterQuantidadeDisponivel(livro) < livro->quantidadeTotal;
}
