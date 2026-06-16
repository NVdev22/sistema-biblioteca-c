#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// módulos do projeto
#include "livro.h"
#include "arvore.h"
#include "lista.h"
#include "fila.h"


// =================================================================
// FUNÇÕES AUXILIARES PARA TRATAMENTO DE ENTRADA
// =================================================================

// Limpa o buffer do teclado para evitar que o fgets seja pulado
void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Remove o caractere '\n' que o fgets captura automaticamente no fim da string
void removerNewline(char *texto) {
    size_t tamanho = strlen(texto);
    if (tamanho > 0 && texto[tamanho - 1] == '\n') {
        texto[tamanho - 1] = '\0';
    }
}



// =================================================================
// PROGRAMA PRINCIPAL
// =================================================================
int main() {

    //inicialização das estruturas
    Arvore *acervo = criarArvore();
    Lista *historicoEmprestimos = criarLista();

    // VERIFICAÇÃO DE SEGURANÇA:
    if (acervo == NULL || historicoEmprestimos == NULL) {
        printf("ERRO CRITICO: Falha de memoria ao inicializar o sistema!\n");

        // Libera o que quer que tenha dado certo antes de fechar
        if (acervo) liberarArvore(acervo);
        if (historicoEmprestimos) liberarLista(historicoEmprestimos);
    
        return 1; // Encerra o programa indicando erro ao sistema operacional
    }



    int opcao;
    
    do{
        printf("\n===================================================\n");
        printf("          SISTEMA DE GESTAO DE BIBLIOTECA          \n");
        printf("===================================================\n");
        printf(" 1 - Cadastrar novo livro\n");
        printf(" 2 - Buscar livro por codigo\n");
        printf(" 3 - Remover livro\n");
        printf(" 4 - Realizar emprestimo de livro\n");
        printf(" 5 - Devolver livro\n");
        printf(" 6 - Exibir fila de reservas\n");
        printf(" 7 - Exibir historico de emprestimos\n");
        printf(" 8 - Listar livros em ordem crescente de codigo\n");
        printf(" 9 - Listar livros indisponiveis\n");
        printf(" 10 - Listar livros com fila de reserva\n");
        printf(" 11 - Listar livros em pre-ordem\n");
        printf(" 12 - Listar livros em pos-ordem\n");
        printf(" 13 - Exibir quantidade de livros cadastrados\n");
        printf(" 14 - Exibir altura da arvore\n");
        printf(" 15 - Visualizar estrutura da arvore\n");
        printf(" 0 - sair\n");
        printf("---------------------------------------------------\n");
        printf("Digite uma opcao:");

        // verifica se o usuário por engano digitou uma letra ou caractere inválido
        // o scanf retorna o número de itens que ele conseguiu ler.
        // se o usuário digitar uma letra, nesse caso ele não vai conseguir ler, pois é para ler um inteiro, assim retorna 0
        if (scanf("%d", &opcao) != 1) {
            printf("Opcao invalida! Digite um numero.\n");
            limparBuffer(); // limpa o buffer, para que ele não verifique de novo o mesmo caractere.
            continue;
        }

        limparBuffer(); // Limpa o '\n' do scanf para não quebrar o fgets

        switch (opcao) {
            case 1: {
                int cod, ano, total;
                char titulo[100], autor[100];    

                printf("\n--- CADASTRANDO NOVO LIVRO ---\n");
                
                //peço o código do livro
                printf("Codigo do livro: ");
                scanf("%d", &cod);
                limparBuffer();

                //verifica se já existe um livro com esse código
                if(buscarLivroArvore(acervo, cod) != NULL){
                    printf("Erro: Ja existe um livro com o codigo %d!\n", cod);
                    break;
                }

                //peço o título do livro
                printf("Titulo: ");
                fgets(titulo, sizeof(titulo), stdin);
                removerNewline(titulo);

                //peço o autor do livro
                printf("Autor: ");
                fgets(autor, sizeof(autor), stdin);
                removerNewline(autor);

                //peço o ano de publicação do livro
                printf("Ano de Publicacao: ");
                scanf("%d", &ano);

                //peço a qunatidade total de livros
                printf("Quantidade de Exemplares: ");
                scanf("%d", &total);
                limparBuffer();

                // cria o livro e inseri na árvore(acervo)
                Livro *livro = criarLivro(cod, titulo, autor, ano, total);
                if(livro != NULL){
                    inserirLivroArvore(acervo, livro);
                    printf("Livro '%s' cadastrado com sucesso!\n", titulo);
                } else{
                    printf("Erro: Falha ao alocar memoria para o livro.\n");
                }
                break;
            }

            case 2: {
                int cod;
                printf("\nDigite o codigo do livro: ");
                scanf("%d", &cod);
                limparBuffer();

                Livro *encontrado = buscarLivroArvore(acervo, cod);
                exibirLivro(encontrado); // a própria função trata se for NULL
                break;
            }

            case 3: {
                int cod;
                printf("\n--- REMOVENDO LIVRO ---\n");
                printf("Digite o codigo do livro que deseja excluir: ");
                scanf("%d", &cod);
                limparBuffer();

                Livro *livroRemover = buscarLivroArvore(acervo, cod);
                if(livroRemover == NULL){
                    printf("Livro nao encontrado.\n");
                    break;
                }
                if(livroEstaEmprestado(livroRemover)){
                    printf("Livro nao pode ser removido, esta emprestado.\n");
                    break;
                }

                // faz a remoção e o rebalanceamento
                removerLivroArvore(acervo, cod);
                break;
            }

            case 4: {
                int cod;
                char nomeUsuario[100];

                printf("\n--- REALIZANDO EMPRESTIMO ---\n");
                
                //peço o nome do usuário
                printf("Nome do Usuario: ");
                fgets(nomeUsuario, sizeof(nomeUsuario), stdin);
                removerNewline(nomeUsuario);
            
                //peço o código do livro
                printf("Digite o codigo do livro: ");
                scanf("%d", &cod);
                limparBuffer();

                Livro *livro = buscarLivroArvore(acervo, cod);
                if (livro == NULL) {
                    printf("Livro nao encontrado no acervo.\n");
                    break;
                }

                // se o livro estiver no estoque, registra o empréstimo imediatamente
                if(obterQuantidadeDisponivel(livro) > 0){
                    emprestarExemplar(livro);

                    Emprestimo emp;
                    strcpy(emp.nomeUsuario, nomeUsuario);
                    emp.codigoLivro = cod;
                    strcpy(emp.tituloLivro, obterTituloLivro(livro));

                    inserirEmprestimo(historicoEmprestimos, emp);
                    printf("Emprestimo de '%s' realizado para %s!\n", emp.tituloLivro, nomeUsuario);

                } else { // se não estiver no estoque, oferece a fila de reserva
                    char resposta;
                    printf("Nao ha exemplares disponiveis. Deseja entrar na fila de reservas? (S/N): ");
                    scanf("%c", &resposta);
                    limparBuffer();

                    if (resposta == 'S' || resposta == 's') {
                        Reserva res;
                        strcpy(res.nomeUsuario, nomeUsuario);
                        res.codigoLivro = cod;

                        // enfileira na fila de reserva que tem dentro da entidade livro
                        enfileirarReserva(obterFilaReserva(livro), res);
                        printf("Usuario '%s' adicionado a fila de espera do livro %d.\n", nomeUsuario, cod);

                    }
                }
                break;
            }

            case 5: {
                int cod;
                printf("\n--- DEVOLVENDO LIVRO ---\n");
                printf("Informe o codigo do livro devolvido: \n");
                scanf("%d", &cod);
                limparBuffer();

                Livro *livro = buscarLivroArvore(acervo, cod);
                if(livro == NULL){
                    printf("Erro: Este livro nao pertence a esta biblioteca.\n");
                    break;
                }

                devolverExemplar(livro);
                printf("Exemplar devolvido com sucesso! Estoque atualizado.\n");

                // verifica se existem pessoas aguardando na fila de reserva daquele exemplar
                if(!filaVazia(obterFilaReserva(livro))) {
                    printf("Aviso: Ha usuarios aguardando por este livro!\n");
                    
                    // atendimento automático do primeiro na fila de reserva
                    Reserva atendido = desenfileirarReserva(obterFilaReserva(livro));
                    printf("Primeiro da fila: %s\n", atendido.nomeUsuario);
                    
                    // empresta o livro 
                    emprestarExemplar(livro);
                    
                    // registra o empréstimo no histórico
                    Emprestimo emp;
                    strcpy(emp.nomeUsuario, atendido.nomeUsuario);
                    emp.codigoLivro = cod;
                    strcpy(emp.tituloLivro, obterTituloLivro(livro));
                    inserirEmprestimo(historicoEmprestimos, emp);

                    printf("Livro emprestado automaticamente para '%s'\n", atendido.nomeUsuario);
                }

                break;
            }

            case 6: {
                int cod;
                printf("\nDigite o codigo do livro para ver as reservas: ");
                scanf("%d", &cod);
                limparBuffer();

                Livro *livro = buscarLivroArvore(acervo, cod);
                if (livro == NULL) {
                    printf("Erro: Livro nao encontrado.\n");
                } else {
                    printf("\n--- FILA DE RESERVAS DE: %s ---\n", obterTituloLivro(livro));
                    exibirReservas(obterFilaReserva(livro)); // Exibe a fila daquele livro
                }
                break;
            }

            case 7: {
                listarEmprestimos(historicoEmprestimos);
                break;
            }

            case 8: {
                printf("\n--- LIVROS EM ORDEM CRESCENTE DE CODIGO ---\n");
                listarLivrosEmOrdem(acervo);
                break;
            }
        
            case 9: {
                listarLivrosIndisponiveis(acervo);
                break;
            }
            
            case 10: {
                listarLivrosComReserva(acervo);
                break;
            }

            case 11: {
                printf("\n--- LIVROS EM PRE-ORDEM ---\n");
                listarLivrosPreOrdem(acervo);
                break;
            }

            case 12: {
                printf("\n--- LIVROS EM POS-ORDEM ---\n");
                listarLivrosPosOrdem(acervo);
                break;
            }

            case 13: {
                printf("\nQuantidade total de livros cadastrados: %d\n", contarLivros(acervo));
                break;
            }

            case 14: {
                printf("\nAltura atual da Arvore AVL: %d\n", calcularAlturaArvore(acervo));
                break;
            }

            case 15: {
                imprimirArvore(acervo);
                break;
            }

            case 0: {
                printf("\nEncerrando o sistema...\n");
                break;
            }

            default: {
                printf("Opcao invalida! Por favor, escolha uma opcao listada no menu.\n");
                break;
            }
        }

    } while (opcao != 0); 

    // liberação de memória
    printf("\nLiberando memoria...\n");    
    liberarArvore(acervo);
    liberarLista(historicoEmprestimos);

    printf("Memoria totalmente liberada. Programa finalizado com sucesso!\n");

    return 0;
}
