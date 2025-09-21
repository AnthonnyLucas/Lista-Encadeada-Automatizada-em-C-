# Lista Encadeada Automatizada em C++

Este projeto consiste em uma implementação da estrutura de dados de lista encadeada simples em C++. O diferencial deste programa é sua capacidade de operar de forma totalmente automatizada, lendo o estado inicial da lista e uma sequência de comandos de manipulação a partir de arquivos de texto, sem a necessidade de interação do usuário durante a execução.

O código também foi instrumentado para medir o tempo total de execução, fornecendo métricas de desempenho como tempo real (`real`), tempo de usuário (`user`) e tempo de sistema (`sys`), utilizando APIs específicas do Windows.

## Funcionalidades Principais

* **Implementação em C++:** Código orientado a objetos utilizando classes e ponteiros para gerenciamento de memória.
* **Operações da Lista:** Suporta as operações essenciais de `adicionar` em uma posição específica, `remover` a primeira ocorrência de um valor e `imprimir` o estado atual da lista.
* **Execução Automatizada:** Carrega uma lista inicial a partir do arquivo `lista_inicial.txt` e executa comandos sequenciais do arquivo `comandos.txt`.
* **Tratamento de Erros:** Lida de forma robusta com operações inválidas (ex: adicionar em posição inexistente, remover valor não encontrado), reportando o erro sem interromper a execução.
* **Medição de Desempenho:** Calcula e exibe o tempo de execução ao final do processo, detalhando o tempo total, de usuário e de sistema.

## Estrutura dos Arquivos

* `main.cpp`: Contém todo o código-fonte em C++, incluindo a definição das classes `Node` e `LinkedList`, a lógica das operações e a função principal que orquestra a leitura dos arquivos e a medição de tempo.
* `lista_inicial.txt`: Arquivo de entrada que define os valores iniciais da lista. Os números devem ser separados por espaços ou quebras de linha.
* `comandos.txt`: Arquivo de entrada que contém a sequência de comandos a serem executados. Cada linha representa uma ação.

## Pré-requisitos

Para compilar e executar este projeto, você precisará de:

1.  **Um Compilador C++:** Recomenda-se o **g++ (MinGW-w64)**, que é o ambiente para o qual o código foi ajustado.
2.  **Sistema Operacional:** Windows (devido à API `GetProcessTimes` usada para medição de tempo `user` e `sys`).
3.  **Editor de Código (Opcional):** Visual Studio Code com a extensão C/C++ da Microsoft.

## Como Executar

Siga os passos abaixo para baixar, configurar e rodar o projeto.

### 1. Clone o Repositório

Abra um terminal (como o Git Bash) e use o seguinte comando para clonar o repositório para sua máquina local:

```bash
git clone [URL_DO_SEU_REPOSITORIO_AQUI]
cd [NOME_DA_PASTA_DO_REPOSITORIO]
```

### 2. Instalação das Dependências (Compilador MinGW-w64)

Se você ainda não tem o compilador g++ instalado no Windows, a maneira mais fácil é através do **MSYS2**.

1.  **Baixe e instale o MSYS2:** Acesse o [site oficial do MSYS2](https://www.msys2.org/) e siga as instruções de instalação.
2.  **Instale a toolchain do MinGW-w64:** Após instalar o MSYS2, abra o terminal do MSYS2 e execute o seguinte comando para instalar o compilador e ferramentas necessárias:
    ```bash
    pacman -S --needed base-devel mingw-w64-ucrt-x86_64-toolchain
    ```
3.  **Adicione o compilador ao PATH:** Adicione a pasta `bin` da sua instalação do MinGW-w64 (ex: `C:\msys64\ucrt64\bin`) às variáveis de ambiente do Windows para poder usar o `g++` em qualquer terminal.

### 3. Configure os Arquivos de Entrada

Antes de compilar, você pode editar os arquivos `lista_inicial.txt` e `comandos.txt` para testar diferentes cenários.

* **`lista_inicial.txt` (Exemplo):**
    ```
    10.5 25 -3.14 99
    ```
* **`comandos.txt` (Exemplo):**
    ```
    # Imprime a lista inicial
    P
    # Adiciona 500 na posição 2
    A 500 2
    # Remove o valor 10.5
    R 10.5
    # Tenta remover um valor que não existe
    R 123
    # Imprime o estado final
    P
    ```

### 4. Compile o Código

Navegue até a pasta do projeto pelo terminal e execute o seguinte comando para compilar o `main.cpp`:

```bash
g++ main.cpp -o programa -std=c++17 -Wall
```
Isso criará um arquivo executável chamado `programa.exe`.

### 5. Execute o Programa

Para rodar o programa, basta executar o arquivo gerado:

```bash
./programa.exe
```

## Exemplo de Saída

A saída no terminal será parecida com esta, mostrando cada passo da execução:

```
Lista inicial carregada do arquivo 'lista_inicial.txt':
Lista atual: 10.5 25 -3.14 99

--- Executando Comandos do Arquivo ---
> P
Lista atual: 10.5 25 -3.14 99
> A 500 2
INFO: Valor 500 adicionado na posicao 2.
> R 10.5
INFO: Valor 10.5 removido da lista.
> R 123
ERRO: Valor 123 nao encontrado na lista.
> P
Lista atual: 25 500 -3.14 99
--------------------------------------

Programa encerrado. Calculando tempos...

--- Tempos de Execucao ---
real    0.005s
user    0.000s
sys     0.000s
```
