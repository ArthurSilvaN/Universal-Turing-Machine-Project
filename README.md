# Universal-Turing-Machine-Project
## __Autores: Arthur Nunes & Nicolas Lopes__

Este simulador de Máquina de Turing foi implementado em C++ e permite a execução de uma Máquina de Turing a partir de um arquivo de configuração que define os estados, alfabetos, transições, estado inicial e estados de aceitação. A seguir, vamos detalhar o funcionamento do simulador, os desafios encontrados e as soluções adotadas.

1. Estruturas de Dados

__Transicao__: Representa uma transição da Máquina de Turing. Contém as seguintes informações:</br>
</br>
de_estado: Estado atual.</br>
ler_simbolo: Símbolo lido na fita.</br>
para_estado: Estado de destino.</br>
escrever_simbolo: Símbolo a ser escrito na fita.</br>
direcao_movimento: Direção do movimento da cabeça de leitura/escrita.</br>

__MaquinaTuring__: Contém todas as informações sobre a Máquina de Turing, incluindo:</br>
</br>
estados: Lista de estados da máquina.</br>
alfabeto: Alfabeto de entrada.</br>
alfabeto_fita: Alfabeto da fita.</br>
transicoes: Lista de transições possíveis.</br>
estado_inicial: Estado inicial da máquina.</br>
estados_aceitacao: Lista de estados de aceitação.</br>

2. Funções Auxiliares

__dividir__: Divide uma string usando um delimitador especificado e retorna um vetor de strings.</br>
__ler_lista_da_linha__: Lê uma linha de texto que contém uma lista de elementos, remove pontuações indesejadas e retorna um vetor de strings.</br>
__ler_transicao_da_linha__: Constrói uma estrutura Transicao a partir de uma linha de texto que define uma transição.</br>
__construir_maquina_turing__: Lê um arquivo de configuração e constrói uma estrutura MaquinaTuring com base no conteúdo do arquivo.</br>
__inicializar_fita__: Inicializa a fita de entrada da Máquina de Turing com a palavra de entrada fornecida, adicionando símbolos brancos (B) __nas extremidades__.</br>
__formatar_fita__: Formata a fita de saída para exibir o estado atual e a posição da cabeça de leitura/escrita.</br>
__escrever_na_saida__: Escreve a fita formatada no arquivo de saída.</br>

1. Função Principal

__executar_maquina_turing__: Executa a Máquina de Turing simulando o processamento da palavra de entrada. A função percorre as transições com base no estado atual e no símbolo lido na fita, realizando as operações de leitura, escrita, e movimentação da cabeça, até que a máquina aceite ou rejeite a palavra.

## Funcionamento do Simulador
1. Entrada do Usuário:

O usuário fornece o nome do arquivo de configuração da Máquina de Turing, a palavra de entrada a ser processada e o nome do arquivo de saída onde os resultados serão salvos.

2. Construção da Máquina de Turing:

O simulador lê o arquivo de configuração, que contém as definições da máquina (estados, alfabetos, transições, etc.), e constrói a estrutura MaquinaTuring.

3. Execução da Máquina de Turing:

A palavra de entrada é carregada na fita da Máquina de Turing.
O simulador executa a máquina, processando a palavra de entrada conforme as transições definidas, até atingir um estado de aceitação ou uma condição de rejeição.
O estado atual e a fita são continuamente atualizados e escritos no arquivo de saída.

4. Finalização:

O simulador salva os resultados (fita final e decisão de aceitar ou rejeitar a palavra) no arquivo de saída.

## Desafios Enfrentados e Soluções
__Leitura e Formatação de Linhas:__

Desafio: Interpretar corretamente as linhas do arquivo de configuração que possuem diferentes formatos (listas, transições, etc.).</br>
Solução: Foram criadas funções específicas para manipular e formatar as strings lidas, removendo caracteres indesejados e dividindo as linhas conforme necessário.

__Execução das Transições:__

Desafio: Garantir que a máquina executasse corretamente as transições, especialmente em casos onde a direção da cabeça de leitura deveria ser alterada.</br>
Solução: Implementação de um loop para percorrer todas as transições e selecionar aquela que corresponde ao estado atual e ao símbolo lido na fita.

__Verificação de Aceitação ou Rejeição:__

Desafio: Determinar se a palavra de entrada deveria ser aceita ou rejeitada com base no estado final atingido pela máquina.</br>
Solução: Após cada transição, o simulador verifica se o estado atual está na lista de estados de aceitação. Se estiver, a palavra é aceita; caso contrário, o simulador continua até que uma condição de rejeição seja atingida.

# Manual de Usuário

1. __Pré-requisitos__

Compilador C++: Certifique-se de ter um compilador C++ instalado, como g++.

Arquivos necessários:</br>
O código fonte (main.cpp).</br>
Um arquivo de configuração da Máquina de Turing (maquina_turing.txt).

2. __Compilando o Programa__

Para compilar o programa, use o seguinte comando no terminal:

`g++ -o simulador main.cpp`

Isso irá gerar um executável chamado simulador.

3. __Estrutura do Arquivo de Configuração__

O arquivo de configuração da Máquina de Turing (maquina_turing.txt) deve seguir o seguinte formato:

Linha 1: Lista de estados da máquina, entre chaves {} e separados por vírgulas.</br>
Linha 2: Alfabeto de entrada, entre chaves {} e separados por vírgulas.</br>
Linha 3: Alfabeto da fita, entre chaves {} e separados por vírgulas.</br>
Linhas 4 em diante: Transições, no formato (estado_atual,símbolo_lido) -> (estado_seguinte,símbolo_escrito,direção).</br>
Penultima linha: Estado inicial.</br>
Ultima linha: Estados de aceitação, entre chaves {} e separados por vírgulas.</br>

4. __Executando o Programa__

Após a compilação, execute o programa usando o comando:

`./simulador`

O programa solicitará três informações:

Nome do arquivo de descrição: O nome do arquivo de configuração da Máquina de Turing. Exemplo: maquina_turing.txt.</br>
Palavra de entrada: A palavra que você deseja processar. Exemplo: 010.</br>
Nome do arquivo de saída: O nome do arquivo onde o resultado será gravado. Exemplo: resultado.txt.

# Documentação dos Testes

### Exemplo 1: Maquina de Turing para inverter os Binários

Resultados esperados: Este teste é projetado para verificar se a máquina de Turing pode inverter corretamente uma sequência binária. A saída esperada é a sequência binária invertida, e a máquina deve aceitar a entrada. Podemos Observar que ele faz a reversão 10110 -> 01001

Exemplo de input:
```
Insira o nome do arquivo de descricao: MT-Inverte-Binario.txt
Insira a palavra de entrada: 10110
Insira o nome do arquivo de saída: saida.txt 
```

output (arquivo):

```
[q0]B10110B
B[q1]10110B
B0[q1]0110B
B01[q1]110B
B010[q1]10B
B0100[q1]0B
B01001[q1]B
B01001B[q2]
aceita
```

### Exemplo 2: Maquina de Turing para aceitar mesmo numeros de a's e b's

Resultados esperados: Este teste é projetado para verificar se a máquina de Turing pode aceitar corretamente uma entrada que contém o mesmo número de 'a's e 'b's. A saída esperada é a sequência de transições que a máquina faz ao processar a entrada, a máquina deve aceitar a entrada quando a palavratem o mesmo numero e reijar caso contrário.

Exemplo de input:
```
Insira o nome do arquivo de descricao: MT-Mesmo-Numero-AB.txt
Insira a palavra de entrada: aaabbb
Insira o nome do arquivo de saída: saida.txt
```

output (arquivo):

exemplo que aceita:

```
[q0]BaaabbbB
B[q1]aaabbbB
BX[q2]aabbbB
BXa[q2]abbbB
BXaa[q2]bbbB
BXa[q3]aYbbB
BX[q3]aaYbbB
B[q3]XaaYbbB
BX[q1]aaYbbB
BXX[q2]aYbbB
BXXa[q2]YbbB
BXXaY[q2]bbB
BXXa[q3]YYbB
BXX[q3]aYYbB
BX[q3]XaYYbB
BXX[q1]aYYbB
BXXX[q2]YYbB
BXXXY[q2]YbB
BXXXYY[q2]bB
BXXXY[q3]YYB
BXXX[q3]YYYB
BXX[q3]XYYYB
BXXX[q1]YYYB
BXXXY[q1]YYB
BXXXYY[q1]YB
BXXXYYY[q1]B
BXXXYYYB[q4]
aceita
```
exemplo que rejeita:

```
[q0]BaaabB
B[q1]aaabB
BX[q2]aabB
BXa[q2]abB
BXaa[q2]bB
BXa[q3]aYB
BX[q3]aaYB
B[q3]XaaYB
BX[q1]aaYB
BXX[q2]aYB
BXXa[q2]YB
BXXaY[q2]B
rejeita
```

### Exemplo 3: Maquina de Turing que entra em Loop

Exemplo de input:
```
Insira o nome do arquivo de descricao: MT-Loop.txt
Insira a palavra de entrada: a
Insira o nome do arquivo de saída: saida.txt
```

Resultados esperados: Este teste é projetado para verificar se a máquina de Turing pode lidar corretamente com um loop infinito. A saída esperada é uma sequência infinita de transições que a máquina faz ao processar a entrada. Neste caso, a máquina não deve aceitar nem rejeitar a entrada, pois ela entra em um loop infinito.

output (arquivo):

```
[q0]BaB
B[q1]aB
Ba[q1]B
B[q1]aB
Ba[q1]B
B[q1]aB
Ba[q1]B
B[q1]aB
Ba[q1]B
B[q1]aB
Ba[q1]B
B[q1]aB
Ba[q1]B
B[q1]aB
Ba[q1]B
B[q1]aB
Ba[q1]B
B[q1]aB
Ba[q1]B
B[q1]aB
Ba[q1]B
B[q1]aB
Ba[q1]B
B[q1]aB
Ba[q1]B
B[q1]aB
Ba[q1]B
[...]
```
