/*
Definição da estrutura da Fila e protótipos das funções.
- Este módulo gerencia as filas de reservas. Cada livro do acervo possui
sua própria fila para controlar a ordem de espera dos usuários.
*/

#ifndef FILA_H
#define FILA_H

// Estrutura que armazena os dados de uma reserva realizada
typedef struct Reserva {
    char nomeUsuario[100];          // Nome do usuário que entrou na fila de reserva
    int codigoLivro;                // Código do livro que foi reservado
} Reserva;

// Nó da fila que armazena uma reserva
typedef struct NoFila {
    Reserva reserva;                // Os dados da reserva contidos neste nó
    struct NoFila *proximo;         // Ponteiro para o próximo usuário na fila
} NoFila;


typedef struct Fila {
    NoFila *inicio;                 // Ponteiro para quem está no começo (próximo a ser atendido)
    NoFila *fim;                    // Ponteiro para quem está no final (último que chegou)
} Fila;


// Aloca e inicializa uma nova fila de reservas na memória
Fila *criarFila();

// Verifica se a fila está vazia
int filaVazia(Fila *fila);

// Insere uma nova reserva no fim da fila (quem chega vai para o final)
void enfileirarReserva(Fila *fila, Reserva reserva);

// Remove e retorna a reserva do início da fila (atende o primeiro da espera)
Reserva desenfileirarReserva(Fila *fila);

// Exibe na tela todos os usuários que estão na fila de reserva deste livro
void exibirReservas(Fila *fila);

// Libera toda a memória alocada para a fila e para todos os seus nós
void liberarFila(Fila *fila);

#endif   // FILA_H