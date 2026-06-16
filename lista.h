/*
Definição da estrutura da Lista Encadeada e protótipos das funções.
- Este módulo é responsável por gerenciar o histórico geral de empréstimos
da biblioteca, registrando quem pegou qual livro.
*/

#ifndef LISTA_H
#define LISTA_H

// Estrutura que armazena os dados de um empréstimo realizado
typedef struct Emprestimo {
    char nomeUsuario[100];          // Nome da pessoa que pegou o livro
    int codigoLivro;
    char tituloLivro[100];
} Emprestimo;

// Nó da lista encadeada que armazena um empréstimo
typedef struct NoLista {
    Emprestimo emprestimo;          // Os dados do empréstimo contidos neste nó
    struct NoLista *proximo;        // Ponteiro para o próximo nó da lista
} NoLista;


typedef struct Lista {
    NoLista *inicio;            // Ponteiro para o primeiro elemento da lista
} Lista;


// Aloca e inicializa uma nova lista de histórico na memória
Lista *criarLista();

// Verifica se a lista de histórico está vazia
int listaVazia(Lista *lista);

// Insere um novo registro de empréstimo no início da lista
void inserirEmprestimo(Lista *lista, Emprestimo emprestimo);

// Exibe na tela todo o histórico de empréstimos realizados
void listarEmprestimos(Lista *lista);

// Libera toda a memória alocada para a lista e para todos os seus nós
void liberarLista(Lista *lista);

#endif   // LISTA_H