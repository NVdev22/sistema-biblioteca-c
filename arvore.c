#include "arvore.h"
#include <stdio.h>
#include <stdlib.h>

// =================================================================
// FUNÇÕES AUXILIARES
// =================================================================

// aloca memória para um nó e associa o livro a ele
NoArvore *criarNo(Livro *livro){
    NoArvore *novoNo = (NoArvore*) malloc(sizeof(NoArvore));
    if(novoNo == NULL){
        return NULL;
    }

    novoNo->livro = livro;
    novoNo->altura = 0;             // Todo nó novo entra como folha, e folha tem altura 0
    novoNo->esquerda = NULL;        // começa sem filho
    novoNo->direita = NULL;         

    return novoNo;
}

// retorna o maior entre dois números (usado para definir qual sub-árvore é mais alta)
int maior(int a, int b){
    return (a > b) ? a : b;       // condição ? valor_se_verdadeiro : valor_se_falso
}

// retorna a altura guardada no nó, evita acessar ponteiro NULL
int alturaNo(NoArvore *n){
    if (n == NULL) {
        return -1;      // Se o nó não existe, sua altura é -1
    }

    return n->altura;
}

// calcula a diferença de altura entre a esquerda e a direita
int obterFatorBalanceamento(NoArvore *n) {
    if (n == NULL) {
        return 0;
    }

    // Fator positivo = árvore torta para a esquerda. Fator negativo = torta para a direita
    return alturaNo(n->esquerda) - alturaNo(n->direita);
}

// rotação Simples à Direita: Usada quando a subárvore esquerda está muito pesada
NoArvore *rotacaoDireita(NoArvore *y) {
    NoArvore *x = y->esquerda;          // filho da esquerda(x) vai virar a nova raiz do bloco
    NoArvore *T2 = x->direita;          // salva a sub-árvore direita de x, que mudará de pai

    // executa a rotação movendo os ponteiros
    x->direita = y;             // a antiga raiz(y) vira filho direito da nova raiz(x)
    y->esquerda = T2;           // T2 vira filho esquerdo de y

    // recalcula as alturas de baixo para cima (primeiro do y, depois do x)
    y->altura = 1 + maior(alturaNo(y->esquerda), alturaNo(y->direita));
    x->altura = 1 + maior(alturaNo(x->esquerda), alturaNo(x->direita));

    return x;           // retorna a nova raiz deste pedaço da árvore para atualizar quem estava acima
}

// rotação Simples à Esquerda: Usada quando a subárvore direita está muito pesada
NoArvore *rotacaoEsquerda(NoArvore *x) {
    NoArvore *y = x->direita;           // O filho da direita(y) vai virar a nova raiz do bloco
    NoArvore *T2 = y->esquerda;         // Salva a sub-árvore esquerda de y, que mudará de pai

    // executa a rotação movendo os ponteiros
    y->esquerda = x;            // a antiga raiz(x) vira filho esquerdo da nova raiz (y)
    x->direita = T2;            // T2 vira filho direito de x

    // recalcula as alturas (primeiro do x, depois do y)
    x->altura = 1 + maior(alturaNo(x->esquerda), alturaNo(x->direita));
    y->altura = 1 + maior(alturaNo(y->esquerda), alturaNo(y->direita));

    return y;           // Retorna a nova raiz deste pedaço da árvore
}

// insere o livro usando busca binária e rebalanceia a árvore no retorno da recursão
NoArvore *inserirNo(NoArvore *raiz, Livro *livro){
    
    // encontrou Null, cria o nó
    if(raiz == NULL){
        return criarNo(livro);
    }

    // obtém o código do livro a ser inserido e compara com os códigos dos livros da árvore
    int codigoNovo = obterCodigoLivro(livro);
    int codigoAtual = obterCodigoLivro(raiz->livro);

    // se o código for menor, vai para a esquerda; se for maior, vai para a direita
    if(codigoNovo < codigoAtual) {
        raiz->esquerda = inserirNo(raiz->esquerda, livro);
    } else if(codigoNovo > codigoAtual){
        raiz->direita = inserirNo(raiz->direita, livro);
    } else {
        return raiz;    // códigos iguais não são permitidos. Ignora a inserção e retorna
    }

    // na volta da recursão, atualiza a altura do nó pai atual
    raiz->altura = 1 + maior(alturaNo(raiz->esquerda), alturaNo(raiz->direita));
    // verifica se este nó atual ficou desregulado
    int fb = obterFatorBalanceamento(raiz);

    // para fazer o balanceamento
    // caso 1: esquerda-esquerda
    if (fb > 1 && codigoNovo < obterCodigoLivro(raiz->esquerda->livro)){
        return rotacaoDireita(raiz);
    }
    
    // caso 2: direita-direita
    if (fb < -1 && codigoNovo > obterCodigoLivro(raiz->direita->livro)){
        return rotacaoEsquerda(raiz);
    }

    // caso 3: esquerda-direita
    if (fb > 1 && codigoNovo > obterCodigoLivro(raiz->esquerda->livro)) {
        raiz->esquerda = rotacaoEsquerda(raiz->esquerda);
        return rotacaoDireita(raiz);
    }
    
    // caso 4: direita-esquerda 
    if (fb < -1 && codigoNovo < obterCodigoLivro(raiz->direita->livro)) {
        raiz->direita = rotacaoDireita(raiz->direita);
        return rotacaoEsquerda(raiz);
    }
    
    return raiz;        // Se o nó já estava balanceado, retorna ele mesmo
}

// busca recursiva pelo código do livro
Livro *buscarNo(NoArvore *raiz, int codigo){
    // se chegou em null, o livro não existe na árvore
    if(raiz == NULL){
        return NULL;
    }

    int codigoAtual = obterCodigoLivro(raiz->livro);

    // se encontrou, retorna o ponteiro do livro imediatamente
    if(codigo == codigoAtual){
        return raiz->livro;
    }

    // se o código buscado for menor, restringe a busca apenas ao lado esquerdo
    if(codigo < codigoAtual){
        return buscarNo(raiz->esquerda, codigo);
    }

    // se não, restringe a busca apenas ao lado direito
    return buscarNo(raiz->direita, codigo);
}

// percurso em-ordem: esquerda, raiz, direita.
void emOrdem(NoArvore *raiz){
    if(raiz == NULL){
        return;
    }

    emOrdem(raiz->esquerda);        // vai até o menor código disponível
    exibirLivro(raiz->livro);       // imprime o livro atual
    emOrdem(raiz->direita);         // vai para os códigos maiores
}

// percurso pré-ordem: raiz, esquerda, direita.
void preOrdem(NoArvore *raiz){
    if(raiz == NULL){
        return;
    }

    exibirLivro(raiz->livro);       // imprime logo o nó atual
    preOrdem(raiz->esquerda);       // vai para o filho esquerdo
    preOrdem(raiz->direita);        // vai para o filho direito
}

// percurso pós-ordem: esquerda, direita, raiz.
void posOrdem(NoArvore *raiz){
    if(raiz == NULL){
        return; 
    }

    posOrdem(raiz->esquerda);       // vai para toda a esquerda
    posOrdem(raiz->direita);        // vai para toda a direita
    exibirLivro(raiz->livro);       // imprime a raiz por último
}

// percorre emOrdem e verifica o estoque de forma recursiva
void listarNoIndisponivel(NoArvore *raiz){
    if (raiz == NULL) return;

    // visita a sub-árvore esquerda
    listarNoIndisponivel(raiz->esquerda);

    // checa se o livro atual está indisponível
    if (obterQuantidadeDisponivel(raiz->livro) == 0) {
        exibirLivro(raiz->livro);
        printf("-----------------------------------\n");
    }

    // visita a sub-árvore direita
    listarNoIndisponivel(raiz->direita);
}

// percorre emOrdem e verifica se a fila de reserva tem usuário
void listarNoComReserva(NoArvore *raiz){
    if (raiz == NULL) return;

    // visita a sub-árvore esquerda
    listarNoComReserva(raiz->esquerda);

    // Processa o nó atual: se a fila de reserva NÃO estiver vazia
    if (!filaVazia(obterFilaReserva(raiz->livro))) {
        printf("Codigo: %d | Livro: %s\n", obterCodigoLivro(raiz->livro), obterTituloLivro(raiz->livro));
        printf("Fila de Espera:\n");
        
        // Exibe a lista de pessoas esperando por este livro específico
        exibirReservas(obterFilaReserva(raiz->livro));
        printf("-----------------------------------\n");
    }

    // visita a sub-árvore direita
    listarNoComReserva(raiz->direita);
}

// conta os nós somando 1(o nó atual) + o total da esquerda + o total da direita
int contarNo(NoArvore *raiz){
    if(raiz == NULL){
        return 0;           // um nó inexistente soma 0 na contagem
    }
    return 1 + contarNo(raiz->esquerda) + contarNo(raiz->direita);
}

// encontra o nó com o menor código a partir de um ponto
NoArvore *encontrarMenorNo(NoArvore *raiz) {
    if (raiz == NULL){
        return NULL;
    }

    NoArvore *atual = raiz;
    while (atual->esquerda != NULL) {
        atual = atual->esquerda;
    }
    return atual;
}

// remove recursivamente o nó e rebalanceia a estrutura
NoArvore *removerNo(NoArvore *raiz, int codigo) {
    
    // livro não foi encontrado na árvore
    if (raiz == NULL) {
        printf("Erro: Livro com o codigo %d nao foi encontrado.\n", codigo);
        return NULL;
    }

    int codigoAtual = obterCodigoLivro(raiz->livro);

    // busca o código que queira remover
    if (codigo < codigoAtual) {
        raiz->esquerda = removerNo(raiz->esquerda, codigo);

    } else if (codigo > codigoAtual) {
        raiz->direita = removerNo(raiz->direita, codigo);

    } else { // encontrou o nó que vai ser removido
        
        // caso 1: nó com nenhum filho(nó folha) e caso 2: nó com um filho
        if (raiz->esquerda == NULL || raiz->direita == NULL) {
            
            // Se tiver o filho esquerdo, temp assume ele. Se tiver o direito, assume ele.
            NoArvore *temp = raiz->esquerda ? raiz->esquerda : raiz->direita;

            if (temp == NULL) {
                // caso 1: nó folha(não tem filhos), é só isolar a raiz atual
                temp = raiz;
                raiz = NULL; 
            } else {    // caso 2: nó com um filho

                // Criamos um ponteiro auxiliar para segurar o nó que vai morrer (o pai atual)
                NoArvore *noParaDeletar = raiz;
                // A raiz deste pedaço da árvore passa a ser, oficialmente, o próprio filho!
                raiz = temp; 
                // Agora apontamos o temp para o nó antigo para que ele seja desalocado corretamente
                temp = noParaDeletar;
            }

            // libera o livro alocado e o nó temp que sobrou
            liberarLivro(temp->livro);
            free(temp);
            printf("Livro removido com sucesso!\n");

        } else {    // caso 3: nó com dois filhos
   
            // busca o menor nó do lado direito(sucessor emOrdem)
            NoArvore *temp = encontrarMenorNo(raiz->direita);

            // trocamos: o livro que queremos apagar vai lá para baixo, e o do sucessor assume a raiz.
            Livro *aux = raiz->livro;
            raiz->livro = temp->livro;
            temp->livro = aux;

            // assim, chamamos a remoção na sub-árvore direita, para eliminar o livro 
            raiz->direita = removerNo(raiz->direita, codigo);
        }
    }

    // se a árvore só tinha 1 nó e ele foi removido, a raiz agora é null.
    if (raiz == NULL) return NULL;

    // atualiza a altura
    raiz->altura = 1 + maior(alturaNo(raiz->esquerda), alturaNo(raiz->direita));

    // rebalanceamento da árvore
    int fb = obterFatorBalanceamento(raiz);

    // caso esquerda-esquerda
    if (fb > 1 && obterFatorBalanceamento(raiz->esquerda) >= 0) {
        return  rotacaoDireita(raiz);
    }
    // caso esquerda-direita
    if (fb > 1 && obterFatorBalanceamento(raiz->esquerda) < 0) {
        raiz->esquerda = rotacaoEsquerda(raiz->esquerda);
        return  rotacaoDireita(raiz);
    }
    // caso direita-direita
    if (fb < -1 && obterFatorBalanceamento(raiz->direita) <= 0) {
        return  rotacaoEsquerda(raiz);
    }
    // caso direita-esquerda
    if (fb < -1 && obterFatorBalanceamento(raiz->direita) > 0) {
        raiz->direita =  rotacaoDireita(raiz->direita);
        return  rotacaoEsquerda(raiz);
    }

    return raiz; // retorna a raiz atualizada e balanceada

}

// liberação em pós-ordem, deleta os filhos primeiro para não perder as referências
void liberarNoArvore(NoArvore *raiz) {
    if (raiz == NULL) return;

    liberarNoArvore(raiz->esquerda); // Limpa recursivamente a subárvore esquerda
    liberarNoArvore(raiz->direita);  // Limpa recursivamente a subárvore direita
    
    // quando já tiver liberado os filhos, libera o nó atual
    liberarLivro(raiz->livro);             // primeiro, apaga o livro alocado dinamicamente
    free(raiz);                            // segundo, apaga o nó que guardava o livro
}










// imprime a árvore rotacionada 90 graus: direita(cima) → raiz(centro) → esquerda(baixo)
void imprimirArvoreNo(NoArvore *raiz, int nivel) {
    int i;
    if (raiz != NULL) {
        imprimirArvoreNo(raiz->direita, nivel + 1);
        printf("\n");
        for (i = 0; i < nivel; i++) {
            printf("\t");
        }
        printf("[ %d ]", obterCodigoLivro(raiz->livro));
        imprimirArvoreNo(raiz->esquerda, nivel + 1);
    }
}

// =================================================================
// FUNÇÕES PRINCIPAIS
// =================================================================

Arvore *criarArvore(){
    Arvore *arvore = (Arvore*) malloc(sizeof(Arvore));
    if(arvore == NULL){
        return NULL;
    }

    arvore->raiz = NULL;    // a árvore inicia vazia
    return arvore;
}

void inserirLivroArvore(Arvore *arvore, Livro *livro){
    if (arvore == NULL || livro == NULL) {
        return;
    }
    
    // A raiz recebe o resultado da inserção, que pode mudar caso precise de balanceamento
    arvore->raiz = inserirNo(arvore->raiz, livro);
}

Livro *buscarLivroArvore(Arvore *arvore, int codigo){
   if(arvore == NULL){
    return NULL;
   }
   return buscarNo(arvore->raiz, codigo);
}

void removerLivroArvore(Arvore *arvore, int codigo) {
    if (arvore == NULL || arvore->raiz == NULL) {
        printf("Árvore esta vazia\n");
        return;
    }
    
    arvore->raiz = removerNo(arvore->raiz, codigo); // O ponteiro da raiz recebe o resultado final do processamento
}

void listarLivrosEmOrdem(Arvore *arvore){
    if(arvore == NULL || arvore->raiz == NULL){
        printf("Nenhum livro cadastrado.\n");
        return;
    }

    emOrdem(arvore->raiz);
    printf("\n");
}

void listarLivrosPreOrdem(Arvore *arvore){
    if(arvore == NULL || arvore->raiz == NULL){
        printf("Nenhum livro cadastrado.\n");
        return;
    }

    preOrdem(arvore->raiz);
    printf("\n");
}

void listarLivrosPosOrdem(Arvore *arvore){
    if(arvore == NULL || arvore->raiz == NULL){
        printf("Nenhum livro cadastrado.\n");
        return;
    }

    posOrdem(arvore->raiz);
    printf("\n");
}

void listarLivrosIndisponiveis(Arvore *arvore){
    if (arvore == NULL || arvore->raiz == NULL) {
        printf("Nenhum livro cadastrado no acervo.\n");
        return;
    }

    printf("\n--- LIVROS INDISPONIVEIS (ESTOQUE ZERADO) ---\n");
    listarNoIndisponivel(arvore->raiz);
}

void listarLivrosComReserva(Arvore *arvore){
    if (arvore == NULL || arvore->raiz == NULL) {
        printf("Nenhum livro cadastrado no acervo.\n");
        return;
    }

    printf("\n--- LIVROS COM FILA DE RESERVA ATIVA ---\n");
    listarNoComReserva(arvore->raiz);
}

int contarLivros(Arvore *arvore){
    if(arvore == NULL || arvore->raiz == NULL){
        return 0;
    }

    return contarNo(arvore->raiz);
}

int calcularAlturaArvore(Arvore *arvore){
    if(arvore == NULL || arvore->raiz == NULL){
        return -1;  // árvore sem nós tem altura -1 por convenção
    }

    return arvore->raiz->altura;
}

void liberarArvore(Arvore *arvore) {
    if (arvore == NULL) return;

    liberarNoArvore(arvore->raiz);   // Limpa todos os nós
    free(arvore);                    // libera a árvore
}

void imprimirArvore(Arvore *arvore) {
    if (arvore == NULL || arvore->raiz == NULL) {
        printf("Arvore vazia.\n");
        return;
    }
    printf("\n--- ESTRUTURA VISUAL DA ARVORE AVL ---\n");
    printf("(leitura: direita em cima, esquerda embaixo)\n");
    imprimirArvoreNo(arvore->raiz, 0);
    printf("\n\n");
}
