/**
Definição da estrutura Livro e protótipos das funções de gerenciamento.

- Este módulo é responsável por encapsular os dados de um livro do acervo,
controlando suas quantidades de estoque e gerenciando sua respectiva
fila exclusiva de reservas.
*/

#ifndef LIVRO_H
#define LIVRO_H

#include "fila.h"


//Estrutura que representa um livro no sistema da biblioteca.
typedef struct Livro {
    int codigo;
    char titulo[100];
    char autor[100];
    int anoPublicacao;
    int quantidadeTotal;
    int quantidadeDisponivel;               //Quantidade de exemplares atualmente livres para empréstimo
    Fila *filaReserva;                      //Ponteiro para a fila de usuários que reservaram este livro
} Livro;

//Aloca e inicializa um novo livro na memória.
Livro *criarLivro(int codigo, char titulo[], char autor[], int anoPublicacao, int quantidadeTotal);

//Exibe na tela todas as informações detalhadas de um livro.
void exibirLivro(Livro *livro);

//Decrementa a quantidade disponível de exemplares (empréstimo).
void emprestarExemplar(Livro *livro);

//Incrementa a quantidade disponível de exemplares (devolução).
void devolverExemplar(Livro *livro);

//Libera toda a memória alocada para o livro, incluindo sua fila de reservas interna.
void liberarLivro(Livro *livro);

//Retorna o código identificador de um livro.
int obterCodigoLivro(Livro *livro);

// Retorna o ponteiro para a string do título do livro
char *obterTituloLivro(Livro *livro);

// Retorna o ponteiro para a fila de reservas exclusiva deste livro
Fila *obterFilaReserva(Livro *livro);

//Consulta quantos exemplares do livro estão disponíveis no estoque.
int obterQuantidadeDisponivel(Livro *livro);

// verifica se um livro está dentro da lista
int livroEstaEmprestado(Livro *livro);


#endif  // LIVRO_H