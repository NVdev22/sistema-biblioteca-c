# 📚 Sistema de Gerenciamento de Biblioteca

Este projeto consiste em um sistema de linha de comando (CLI) desenvolvido em linguagem C para o gerenciamento eficiente de um acervo de biblioteca, controle de filas de reserva e histórico de empréstimos. O sistema utiliza estruturas de dados dinâmicas avançadas para otimizar as operações de busca, inserção e controle de fluxo.

## 👥 Equipe e Integrantes
* **Nome da Equipe:** Tiko Teko
* **Integrantes:**
  * Adriel Angelino Pessoa
  * Nicolas Vieira Lourenço

## 📃 Descrição do Sistema
O sistema organiza os livros da biblioteca utilizando uma **Árvore de Busca Binária (ABB) devidamente balanceada**, onde a chave de ordenação é o código numérico do livro. Isso garante que as operações de busca, inserção e listagem ordenada ocorram com excelente eficiência temporal.

Cada livro cadastrado no acervo possui, acoplada a ele, uma **Fila de Reserva (FIFO - First-In, First-Out)** implementada de forma dinâmica. Quando um usuário tenta retirar um livro que está com o estoque zerado (indisponível), o sistema permite que ele entre em uma fila de espera ordenada estritamente por ordem de chegada.

Além disso, o sistema conta com uma **Lista Encadeada** dedicada para armazenar o **histórico de empréstimos**. Essa estrutura funciona de forma que os empréstimos mais recentes sejam inseridos no início da lista, mantendo os registros antigos no fim, facilitando a auditoria das movimentações recentes.

## 🔧 Instruções para Compilação

Certifique-se de que todos os arquivos `.c` e `.h` estão presentes no mesmo diretório. Abra o terminal (Prompt de Comando, PowerShell ou Git Bash) na pasta do projeto e execute:

**Windows:**
```bash
gcc main.c livro.c arvore.c fila.c lista.c -o biblioteca.exe
```

**Linux/macOS:**
```bash
gcc main.c livro.c arvore.c fila.c lista.c -o biblioteca
```

> Requisito: compilador GCC instalado. No Windows, recomenda-se o [MinGW-w64](https://www.mingw-w64.org/) ou o GCC disponível via MSYS2.

## 🚀 Instruções para Execução

Após a compilação, execute o sistema a partir do mesmo diretório:

**Windows:**
```bash
./biblioteca.exe
```

**Linux/macOS:**
```bash
./biblioteca
```

O sistema abrirá um menu interativo no terminal. Navegue pelas opções digitando o número correspondente e pressionando Enter.

## 👨🏻‍💻 Exemplos de Uso
Ao iniciar o sistema, um menu interativo é exibido no terminal. Abaixo estão descritos os fluxos principais de utilização:

* **Cadastro e Remoção de Livro:** O usuário escolhe a opção de cadastrar um novo livro e fornece o código (ex: `30`), título, autor, ano de publicação e a quantidade em estoque. O sistema valida se o código já existe para impedir duplicidades. O livro é inserido na posição correta da árvore balanceada. Para remover, basta informar o código do livro.
* **Consulta e Listagem:** Permite verificar instantaneamente se a biblioteca possui o livro procurado (via código) e listar detalhadamente todos os livros disponíveis no acervo.
* **Empréstimo e Fila de Reservas:** O usuário pode realizar o empréstimo do livro caso haja exemplares em estoque. Se o estoque chegar a zero, o sistema oferece a opção de colocar o nome do usuário na fila de reserva daquele livro específico.
* **Devolução Automática:** No momento em que um livro com fila de espera é devolvido, o sistema atende automaticamente a primeira pessoa da fila de reserva, realizando o novo empréstimo de forma imediata.
* **Relatórios e Histórico:** O administrador pode extrair relatórios do acervo em ordem crescente de códigos e consultar a lista encadeada de histórico para checar os empréstimos realizados do mais recente ao mais antigo.

## ⚙️ Observações sobre Funcionalidades Implementadas
O projeto cumpre com rigor todas as especificações obrigatórias de manipulação de estruturas dinâmicas e inclui os seguintes refinamentos além do pedido:
* **Remoção de livros na Árvore AVL** (funcionalidade extra): remove o nó, substitui pelo sucessor em-ordem e rebalanceia automaticamente a estrutura.
* **Atendimento automático da fila de reservas na devolução**: ao devolver um livro com usuários em espera, o sistema empresta imediatamente ao primeiro da fila.
* **Listagem de livros indisponíveis** (opção 9): percurso em-ordem filtrando apenas livros com estoque zerado.
* **Listagem de livros com fila de reserva ativa** (opção 10): exibe quais livros possuem usuários aguardando.
* **Visualização estrutural da Árvore AVL** (opção 15): exibe a árvore rotacionada 90° no terminal, com indentação proporcional à profundidade de cada nó — direita no topo, esquerda na base.
* **Percursos em árvore** limpos e puramente recursivos (em-ordem, pré-ordem, pós-ordem).
* **Gerenciamento completo de memória dinâmica**: toda memória alocada com `malloc` é devidamente liberada ao encerrar o programa, incluindo as filas internas de cada livro.

## ⚠️ Limitações Conhecidas
* Os dados do acervo não são persistidos em disco: ao encerrar o programa, todas as informações são perdidas. Uma versão futura poderia salvar e carregar o estado em arquivo.
