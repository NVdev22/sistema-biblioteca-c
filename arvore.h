/*
Definição da estrutura da Árvore e protótipos das funções.
- Este módulo é responsável por armazenar de forma indexada e eficiente
os livros do acervo da biblioteca, usando o código do livro como chave.
*/

#ifndef ARVORE_H
#define ARVORE_H
#include "livro.h"


// Nó da árvore que armazena os dados de um livro e as ramificações
typedef struct NoArvore {
    Livro *livro;                       // Ponteiro para as informações do livro
    int altura;                         // Altura do nó (fundamental para o balanceamento AVL)
    struct NoArvore* esquerda;          // Ponteiro para a sub-árvore esquerda(códigos menores)
    struct NoArvore* direita;           // Ponteiro para a sub-árvore direita(códigos maiores)
} NoArvore;


typedef struct Arvore {
    NoArvore* raiz; // Aponta para o topo da árvore (ou NULL se estiver vazia)
} Arvore;

// Aloca e inicializa uma nova árvore na memória
Arvore *criarArvore();

// Insere um novo livro na árvore organizando por código
void inserirLivroArvore(Arvore *arvore, Livro *livro);

// Busca um livro na árvore através do seu código identificador único
Livro *buscarLivroArvore(Arvore *arvore, int codigo);

// Remove um livro da árvore pelo código e reorganiza a árvore
void removerLivroArvore(Arvore *arvore, int codigo);

// Exibe todos os livros em ordem crescente de código (Esquerda - Raiz - Direita)
void listarLivrosEmOrdem(Arvore *arvore);

// Exibe os livros seguindo o percurso de Pré-Ordem (Raiz - Esquerda - Direita)
void listarLivrosPreOrdem(Arvore *arvore);

// Exibe os livros seguindo o percurso de Pós-Ordem (Esquerda - Direita - Raiz)
void listarLivrosPosOrdem(Arvore *arvore);

// percorre a árvore e printa apenas os livros cujo estoque disponível seja zero
void listarLivrosIndisponiveis(Arvore *arvore);

// Percorre a árvore e exibe os livros que têm pessoas aguardando na fila de reserva
void listarLivrosComReserva(Arvore *arvore);

// Conta e retorna a quantidade total de livros cadastrados na árvore
int contarLivros(Arvore *arvore);

// Calcula e retorna a altura máxima atual da árvore
int calcularAlturaArvore(Arvore *arvore);

// Exibe a estrutura visual da árvore no terminal (rotacionada 90°, direita em cima)
void imprimirArvore(Arvore *arvore);

// Libera toda a memória alocada para a árvore, seus nós e os livros internos
void liberarArvore(Arvore *arvore);

#endif   // ARVORE_H