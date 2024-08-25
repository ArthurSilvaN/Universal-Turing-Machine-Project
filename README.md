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
