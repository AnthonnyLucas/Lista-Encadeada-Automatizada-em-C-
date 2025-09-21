#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <limits>
#include <chrono>

// Para medição de tempo no Windows
#ifdef _WIN32
#include <windows.h>
#endif

// Estrutura do Nó da lista
struct Node {
    double data;
    Node* next;

    Node(double val) : data(val), next(nullptr) {}
};

// Classe da Lista Encadeada
class LinkedList {
private:
    Node* head;

public:
    LinkedList() : head(nullptr) {}

    // Destrutor para liberar a memória alocada
    ~LinkedList() {
        Node* current = head;
        while (current != nullptr) {
            Node* next = current->next;
            delete current;
            current = next;
        }
    }

    void adicionar(double data, int position);
    void remover(double data);
    void imprimir_lista();
};

void LinkedList::adicionar(double data, int position) {
    Node* newNode = new Node(data);

    if (position < 0) {
        std::cout << "ERRO: Posicao " << position << " e invalida." << std::endl;
        delete newNode;
        return;
    }

    if (position == 0) {
        newNode->next = head;
        head = newNode;
        std::cout << "INFO: Valor " << data << " adicionado na posicao " << position << "." << std::endl;
        return;
    }

    Node* current_node = head;
    int current_position = 0;

    while (current_node != nullptr && current_position < position - 1) {
        current_node = current_node->next;
        current_position++;
    }

    if (current_node == nullptr) {
        std::cout << "ERRO: Posicao " << position << " e invalida ou fora do alcance da lista." << std::endl;
        delete newNode; // Libera a memória se a posição for inválida
    } else {
        newNode->next = current_node->next;
        current_node->next = newNode;
        std::cout << "INFO: Valor " << data << " adicionado na posicao " << position << "." << std::endl;
    }
}

void LinkedList::remover(double data) {
    Node* current_node = head;
    Node* previous_node = nullptr;

    if (current_node == nullptr) {
        std::cout << "ERRO: Nao e possivel remover o valor " << data << ", pois a lista esta vazia." << std::endl;
        return;
    }

    if (current_node->data == data) {
        head = current_node->next;
        delete current_node;
        std::cout << "INFO: Valor " << data << " removido da lista." << std::endl;
        return;
    }

    while (current_node != nullptr && current_node->data != data) {
        previous_node = current_node;
        current_node = current_node->next;
    }

    if (current_node == nullptr) {
        std::cout << "ERRO: Valor " << data << " nao encontrado na lista." << std::endl;
    } else {
        previous_node->next = current_node->next;
        delete current_node;
        std::cout << "INFO: Valor " << data << " removido da lista." << std::endl;
    }
}

void LinkedList::imprimir_lista() {
    Node* current_node = head;
    std::cout << "Lista atual: ";
    if (current_node == nullptr) {
        std::cout << "(vazia)";
    } else {
        while (current_node != nullptr) {
            std::cout << current_node->data << " ";
            current_node = current_node->next;
        }
    }
    std::cout << std::endl;
}

// Função para converter FILETIME para um valor numérico (em segundos)
double fileTimeToSeconds(const FILETIME& ft) {
    ULARGE_INTEGER uli;
    uli.LowPart = ft.dwLowDateTime;
    uli.HighPart = ft.dwHighDateTime;
    return uli.QuadPart / 10000000.0;
}

void executarComandos(const std::string& nome_arquivo_comandos, LinkedList& lista) {
    std::ifstream arquivo_comandos(nome_arquivo_comandos);
    if (!arquivo_comandos.is_open()) {
        std::cout << "ERRO: Nao foi possivel abrir o arquivo de comandos '" << nome_arquivo_comandos << "'." << std::endl;
        return;
    }

    std::cout << "\n--- Executando Comandos do Arquivo ---" << std::endl;

    std::string linha;
    while (std::getline(arquivo_comandos, linha)) {
        if (linha.empty() || linha[0] == '#') { // Ignora linhas vazias ou comentários
            continue;
        }

        std::cout << "> " << linha << std::endl; // Mostra o comando que está sendo executado

        std::stringstream ss(linha);
        char acao_char;
        ss >> acao_char;
        char acao = toupper(acao_char);

        if (acao == 'A') {
            double numero;
            int posicao;
            if (ss >> numero >> posicao) {
                lista.adicionar(numero, posicao);
            } else {
                std::cout << "ERRO DE SINTAXE: Para adicionar, use o formato: A [numero] [posicao]" << std::endl;
            }
        } else if (acao == 'R') {
            double numero;
            if (ss >> numero) {
                lista.remover(numero);
            } else {
                std::cout << "ERRO DE SINTAXE: Para remover, use o formato: R [numero]" << std::endl;
            }
        } else if (acao == 'P') {
            lista.imprimir_lista();
        } else {
            std::cout << "ERRO: Acao invalida '" << acao_char << "' encontrada no arquivo." << std::endl;
        }
    }
    std::cout << "--------------------------------------\n" << std::endl;
}


int main() {
    // Inicia a medição de tempo
    auto start_time = std::chrono::high_resolution_clock::now();
    
    #ifdef _WIN32
    FILETIME creationTime, exitTime, kernelTimeStart, userTimeStart;
    GetProcessTimes(GetCurrentProcess(), &creationTime, &exitTime, &kernelTimeStart, &userTimeStart);
    #endif

    // 1. Carregar a lista inicial
    LinkedList lista;
    std::string nome_arquivo_lista = "lista_inicial.txt";
    std::ifstream arquivo_lista(nome_arquivo_lista);

    if (arquivo_lista.is_open()) {
        double valor;
        int i = 0;
        while (arquivo_lista >> valor) {
            lista.adicionar(valor, i++);
        }
        arquivo_lista.close();
        
        std::cout << "\nLista inicial carregada do arquivo '" << nome_arquivo_lista << "':" << std::endl;
        lista.imprimir_lista();

    } else {
        std::cout << "AVISO: Arquivo '" << nome_arquivo_lista << "' nao encontrado. A lista comecara vazia." << std::endl;
    }

    // 2. Executar comandos do arquivo
    executarComandos("comandos.txt", lista);

    std::cout << "Programa encerrado. Calculando tempos..." << std::endl;

    // Finaliza a medição de tempo
    auto end_time = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> real_duration = end_time - start_time;
    
    double user_sec = 0.0;
    double sys_sec = 0.0;

    #ifdef _WIN32
    FILETIME kernelTimeEnd, userTimeEnd;
    GetProcessTimes(GetCurrentProcess(), &creationTime, &exitTime, &kernelTimeEnd, &userTimeEnd);
    
    user_sec = fileTimeToSeconds(userTimeEnd) - fileTimeToSeconds(userTimeStart);
    sys_sec = fileTimeToSeconds(kernelTimeEnd) - fileTimeToSeconds(kernelTimeStart);
    #endif

    std::cout.precision(3); // Configura a precisão da saída
    std::cout << "\n--- Tempos de Execucao ---" << std::endl;
    std::cout << "real\t" << std::fixed << real_duration.count() << "s" << std::endl;
    std::cout << "user\t" << std::fixed << user_sec << "s" << std::endl;
    std::cout << "sys\t" << std::fixed << sys_sec << "s" << std::endl;


    return 0;
}