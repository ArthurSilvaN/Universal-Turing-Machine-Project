#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>

using namespace std;

struct Transicao {
    string de_estado;
    char ler_simbolo{};
    string para_estado;
    char escrever_simbolo{};
    char direcao_movimento{};
};

struct MaquinaTuring {
    vector<string> estados;
    vector<string> alfabeto;
    vector<string> alfabeto_fita;
    vector<Transicao> transicoes;
    string estado_inicial;
    vector<string> estados_aceitacao;
};

// Função para dividir uma string em um vetor de strings, usando uma string delimitadora.
vector<string> dividir(const string &s, const string &delim) {
    vector<string> tokens;
    size_t prev = 0, pos = 0;
    do {
        pos = s.find(delim, prev);
        if (pos == string::npos) pos = s.length();
        string token = s.substr(prev, pos - prev);
        if (!token.empty()) tokens.push_back(token);
        prev = pos + delim.length();
    } while (pos < s.length() && prev < s.length());
    return tokens;
}

// Função para ler uma lista de strings de uma linha, removendo pontuação e dividindo por vírgulas.
vector<string> ler_lista_da_linha(string linha) {
    // Remove as chaves da linha.
    linha.erase(remove(linha.begin(), linha.end(), '{'), linha.end());
    linha.erase(remove(linha.begin(), linha.end(), '}'), linha.end());
    // Divide a linha em um vetor de strings, usando vírgula como delimitador.
    return dividir(linha, ",");
}

// Função para ler uma transição de uma linha.
Transicao ler_transicao_da_linha(const string &linha) {
    // Remove os parênteses e espaços em branco da linha.
    string linha_formatada = linha;
    linha_formatada.erase(remove(linha_formatada.begin(), linha_formatada.end(), '('), linha_formatada.end());
    linha_formatada.erase(remove(linha_formatada.begin(), linha_formatada.end(), ')'), linha_formatada.end());
    linha_formatada.erase(remove(linha_formatada.begin(), linha_formatada.end(), ' '), linha_formatada.end());

    // Divide a linha em duas partes, usando '->' como delimitador.
    vector<string> partes = dividir(linha_formatada, "->");

    // Lê a lista de strings da primeira parte da linha.
    vector<string> de_estado_simbolo = dividir(partes[0], ",");
    // Lê a lista de strings da segunda parte da linha.
    vector<string> para_tripla = dividir(partes[1], ",");

    // Extrai os valores necessários das listas de strings.
    string de_estado = de_estado_simbolo[0];
    char ler_simbolo = de_estado_simbolo[1][0];
    string para_estado = para_tripla[0];
    char escrever_simbolo = para_tripla[1][0];
    char direcao_movimento = para_tripla[2][0];

    // Retorna uma nova Transicao com os valores extraídos.
    return {de_estado, ler_simbolo, para_estado, escrever_simbolo, direcao_movimento};
}

// Função para construir uma Máquina de Turing a partir de um arquivo de configuração.
MaquinaTuring construir_maquina_turing(const string &arquivo_config) {
    // Abre o arquivo de configuração.
    ifstream arquivo(arquivo_config);

    // Se não foi possível abrir o arquivo, lança uma exceção.
    if (!arquivo.is_open()) {
        throw runtime_error("Incapaz de abrir o arquivo");
    }

    // Inicializa o contador de linhas.
    int contador_linha = 1;

    // Cria uma nova Máquina de Turing.
    MaquinaTuring mt;

    // Variável para armazenar cada linha do arquivo.
    string linha;

    // Lê o arquivo linha por linha.
    while (getline(arquivo, linha)) {
        // Verifica se a linha atual está nas transições.
        bool nas_transicoes = linha[0] == '(' && contador_linha != 1;

        // Dependendo do número da linha, faz diferentes coisas.
        if (contador_linha == 2) {
            // Lê a lista de estados da linha.
            mt.estados = ler_lista_da_linha(linha);
        } else if (contador_linha == 3) {
            // Lê o alfabeto da linha.
            mt.alfabeto = ler_lista_da_linha(linha);
        } else if (contador_linha == 4) {
            // Lê o alfabeto da fita da linha.
            mt.alfabeto_fita = ler_lista_da_linha(linha);
        } else if (nas_transicoes) {
            // Lê uma transição da linha.
            mt.transicoes.push_back(ler_transicao_da_linha(linha));
        }

        // Se a linha começa com 'q', lê o estado inicial.
        if (linha[0] == 'q') {
            mt.estado_inicial = linha;
            mt.estado_inicial.erase(remove(mt.estado_inicial.begin(), mt.estado_inicial.end(), ','),
                                    mt.estado_inicial.end());
        }
        // Se a linha começa com '{' e o contador de linhas é maior que 4, lê os estados de aceitação.
        else if (linha[0] == '{' && contador_linha > 4) {
            mt.estados_aceitacao = ler_lista_da_linha(linha);
        }

        // Incrementa o contador de linhas.
        contador_linha++;
    }

    // Retorna a Máquina de Turing construída.
    return mt;
}

// Funcao para formatar a fita de saida
string formatar_fita(vector<char> fita, int posicao_cabeca, const string& estado_atual) {
    string resultado;
    for (int i = 0; i < fita.size(); i++) {
        if (i == posicao_cabeca) {
            resultado += "[" + estado_atual + "]" + string(1, fita[i]);
        } else if (posicao_cabeca == fita.size() && i == fita.size() - 1) {
            resultado += string(1, fita[i]) + "[" + estado_atual + "]";
        } else {
            resultado += string(1, fita[i]);
        }
    }
    return resultado;
}

// Funcao para inicializar a fita com um caracter 'branco'
vector<char> inicializar_fita(const string &palavra_entrada) {
    vector<char> fita = {'B'};
    for (char c: palavra_entrada) {
        fita.push_back(c);
    }
    fita.push_back('B');
    return fita;
}

void escrever_na_saida(ofstream &buffer_saida, vector<char> &fita, int posicao_cabeca, string &estado_atual) {
    buffer_saida << formatar_fita(fita, posicao_cabeca, estado_atual) << "\n";
}

// Funcao que executa o processamento, dada uma MT, uma palavra de entrada e o arquivo de saida
void executar_maquina_turing(MaquinaTuring mt, const string &palavra_entrada, const string &arquivo_saida) {
    vector<char> fita = inicializar_fita(palavra_entrada);
    string estado_atual = mt.estado_inicial;
    int posicao_cabeca = 0;

    ofstream buffer_saida(arquivo_saida);

    if (!buffer_saida.is_open()) {
        throw runtime_error("Falha ao criar arquivo de saída");
    }

    escrever_na_saida(buffer_saida, fita, posicao_cabeca, estado_atual);

    // Loop infinito para executar as transiçoes da maquina
    while (true) {
        char simbolo_atual = fita[posicao_cabeca];

        Transicao transicao;
        bool encontrado = false;

	// Percorrer as transicoes e verificar se a transicao se encaixa no cenario atual
        for (auto &t: mt.transicoes) {
            if (t.de_estado == estado_atual && t.ler_simbolo == simbolo_atual) {
                transicao = t;
                encontrado = true;
                break;
            }
        }

        if (!encontrado) {
            buffer_saida << "rejeita\n";
            break;
        }

        fita[posicao_cabeca] = transicao.escrever_simbolo;
        estado_atual = transicao.para_estado;

	// Atualizar a posicao da cabeca apos a transicao
        if (transicao.direcao_movimento == 'D') {
            posicao_cabeca++;
        } else if (transicao.direcao_movimento == 'E') {
            posicao_cabeca--;
        } else {
            throw runtime_error("Direção de movimento inválida");
        }

        escrever_na_saida(buffer_saida, fita, posicao_cabeca, estado_atual);

	// Verifica se a maquina para em estado final e aceita
        if (find(mt.estados_aceitacao.begin(), mt.estados_aceitacao.end(), estado_atual) != mt.estados_aceitacao.end()) {
            buffer_saida << "aceita\n";
            break;
        }
    }
}

// Funcao principal para ler os inputs do usuario
int main() {
    string arquivo_maquina;
    string palavra_entrada;
    string arquivo_saida;

    cout << "Insira o nome do arquivo de descricao: ";
    cin >> arquivo_maquina;

    cout << "Insira a palavra de entrada: ";
    cin >> palavra_entrada;

    cout << "Insira o nome do arquivo de saída: ";
    cin >> arquivo_saida;

    MaquinaTuring maquina_turing = construir_maquina_turing(arquivo_maquina);

    executar_maquina_turing(maquina_turing, palavra_entrada, arquivo_saida);

    return 0;
}
