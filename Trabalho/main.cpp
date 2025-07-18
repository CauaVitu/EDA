#include <iostream>
#include "AVL.hpp"
#include "RBTree.hpp"
#include "ChainedHash.hpp"
#include "OpenHash.hpp"
#include "Dictionary.hpp"
#include <unicode/unistr.h>
#include <unicode/brkiter.h>
#include <unicode/ustream.h> // para cout << UnicodeString
#include <unicode/locid.h>
#include <fstream>
#include <sstream>
#include <memory>
#include <algorithm>
#include <cctype>
#include <chrono>

using namespace std;
using namespace icu;

// Quicksort implementation for sorting word frequencies
int partition(vector<pair<string,int>>& arr, int low, int high) {
    int pivot = arr[high].second;  // Use frequency as pivot
    int i = low - 1;
    
    for (int j = low; j < high; j++) {
        // Sort in descending order (highest frequency first)
        if (arr[j].second >= pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return i + 1;
}

void quicksort(vector<pair<string,int>>& arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quicksort(arr, low, pi - 1);
        quicksort(arr, pi + 1, high);
    }
}

// Wrapper function for easier usage
void sortWordFrequencies(vector<pair<string,int>>& wordFreqs) {
    if (!wordFreqs.empty()) {
        quicksort(wordFreqs, 0, wordFreqs.size() - 1);
    }
}

string readUTF8File(const string& filename) {
    ifstream file(filename);
    stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

// O programa abaixo tem alguns requisitos para ser executado corretamente:
// Você precisa ter o ICU instalado no seu sistema, pois ele é usado para manipulação de strings Unicode.
// O bat só existe por necessidade do windows, no linux você pode compilar e executar diretamente o main.cpp
// No Linux: g++ -std=c++11 -o main main.cpp -licuuc && ./main <StructureType> <filename>.txt 
// No Windows: build_and_run.bat <StructureType> <filename>.txt 
// OBS: um .bat é suspeito pra caramba, então caso queira apenas compilar sem a interface bonitinha.
// Esse .bat não é completamente de minha autoria, ele foi criado com a ajuda do copilot
// para lidar com o problema do meu
// VSCode não conseguir achar a biblioteca ICU, ele abre a powershell
// do MSY64 e executa o comando de compilação.
// Também faz algumas checagens extras e tem uma interface bonitinha.
// Comando:
// g++.exe -std=c++17 main.cpp -o main.exe -IC:\msys64\mingw64\include -LC:\msys64\mingw64\lib -licuuc

// Na execução da nossa main iremos receber 2 argumentos: o nome do arquivo e o tipo de estrutura
// Na linha de comando deve ser passado o tipo de estrutura e o nome do arquivo a ser lido
// O tipo de estrutura pode ser:
// 1. AVLTREE
// 2. RBTREE
// 3. OPENHASH
// 4. CHAINEDHASH
// O comando não é case sensitive, e você também pode usar os números 1-4 pra estrutura.
// O nome do arquivo deve ser passado como segundo argumento com a extensão .txt
// Exemplo de uso:
// build_and_run.bat AVLTREE test.txt
// Ou
// build_and_run.bat 1 test.txt
// Ou
// build_and_run.bat AvLtReE test.txt

int main(int argc, char* argv[]) {
    enum structureTypes {
        AVLTREE,
        RBTREE,
        OPENHASH,
        CHAINEDHASH
    };
    
    // Checagem pra garantir que temos todos os argumentos necessários
    // argc deve ser 3: o nome do programa, o tipo de estrutura e o nome do arquivo
    if (argc != 3) {
        cout << "O uso correto é: " << argv[0] << " <tipo_de_estrutura> <nome_do_arquivo>" << endl;
        cout << "Tipos de estrutura disponíveis: " << endl;
        cout << "1. AVLTREE" << endl;
        cout << "2. RBTREE" << endl;
        cout << "3. OPENHASH" << endl;
        cout << "4. CHAINEDHASH" << endl;
        cout << "Exemplo: " << argv[0] << " AVLTREE test.txt" << endl;
        return 1;
    }
    
    //  Pegamos o tipo de estrutura e o nome do arquivo a partir dos argumentos da linha de comando
    string structureArg = argv[1];
    // Para garantir que o tipo de estrutura é case insensitive, convertemos para maiúsculas
    for (char& c : structureArg) {
        c = toupper(c);
    }
    structureTypes selectedType;
    
    // Verificamos o tipo de estrutura e atribuímos o valor correto ao selectedType
    // Interface bonitinha para o usuário. Você merece!
    if (structureArg == "AVLTREE" || structureArg == "1") {
        selectedType = structureTypes::AVLTREE;
        cout << "Usando estrutura: AVL Tree" << endl;
    } else if (structureArg == "RBTREE" || structureArg == "2") {
        selectedType = structureTypes::RBTREE;
        cout << "Usando estrutura: Red-Black Tree" << endl;
    } else if (structureArg == "OPENHASH" || structureArg == "3") {
        selectedType = structureTypes::OPENHASH;
        cout << "Usando estrutura: Open Hash" << endl;
    } else if (structureArg == "CHAINEDHASH" || structureArg == "4") {
        selectedType = structureTypes::CHAINEDHASH;
        cout << "Usando estrutura: Chained Hash" << endl;
    } else {
        cout << "Tipo de estrutura inválido: " << structureArg << endl;
        cout << "Use: AVLTREE, RBTREE, OPENHASH, CHAINEDHASH ou os números 1-4" << endl;
        return 1;
    }
    
    // Instanciamos o dicionário com o tipo de estrutura selecionado
    Dictionary<string,int> dicionario(selectedType);

    // Recebemos o nome do arquivo a ser lido
    string filename = argv[2];
    cout << "Lendo arquivo: " << filename << endl;
    
    // Criamos o arquivo de saída com o mesmo nome do arquivo de entrada, mas com _frequency_output.txt no final
    string outputFilename = filename.substr(0, filename.find_last_of('.')) + "_frequency_output.txt";
    ofstream outputFile(outputFilename);
    
    // Verificamos se o arquivo de saída foi aberto corretamente
    // Se não, exibimos uma mensagem de erro e encerramos o programa
    if (!outputFile.is_open()) {
        cout << "Erro: Não foi possível criar o arquivo de saída: " << outputFilename << endl;
        return 1;
    }
    
    // Exibimos o nome do arquivo de saída
    cout << "Arquivo de saída será: " << outputFilename << endl;
    
    // Lemos o arquivo de entrada como uma string UTF-8
    string utf8text = readUTF8File(filename);
    
    // Checamos se o arquivo foi lido corretamente, existe e não está vazio
    if (utf8text.empty()) {
        cout << "Erro: Arquivo '" << filename << "' não encontrado ou vazio!" << endl;
        return 1;
    }
    
//debugging    cout << "Texto lido: " << utf8text << endl;  
    UnicodeString text = UnicodeString::fromUTF8(utf8text);

    UErrorCode status = U_ZERO_ERROR;
    // Criamos nosso iterador de palavras (magia negra da ICU)
    unique_ptr<BreakIterator> wordIterator(BreakIterator::createWordInstance(Locale("pt_BR"), status));

    // Verificamos se o iterador foi criado corretamente
    if (U_FAILURE(status)) {
        cerr << "Erro ao criar BreakIterator: " << u_errorName(status) << endl;
        return 1;
    }

    // Marcamos o texto no iterador
    wordIterator->setText(text);

    // Percorre as palavras
    int32_t start = wordIterator->first();
    // Aqui considero que o algoritmo começou a execução de fato, já que antes disso estamos preparando terreno.
    auto start_time = std::chrono::high_resolution_clock::now();
    // Itera sobre as palavras e conta a frequência de cada uma
    // Funciona da seguinte forma:
    // O iterador aponta para bordas de palavras, portanto se pegamos o que está entre uma borda e outra, temos uma palavra.
    // O iterador retorna o índice da próxima borda, então usamos isso para pegar a palavra entre as bordas.
    
for (int32_t end = wordIterator->next(); end != BreakIterator::DONE; start = end, end = wordIterator->next()) {
    UnicodeString word = text.tempSubStringBetween(start, end);
    if (wordIterator->getRuleStatus() != UBRK_WORD_NONE) {
        word.toLower();
        word.trim();
        string utf8word;
        word.toUTF8String(utf8word);
        // Adiciona a palavra se ela não estiver no dicionário
        // Se já estiver, incrementa a frequência
        try {
            int aux = dicionario.access(utf8word) + 1;
            dicionario.update(utf8word, aux);
        } catch (const std::out_of_range& e) {
            dicionario.insert(utf8word, 1);
        }    }
}
    // Aqui considero que o algoritmo terminou de executar, já que percorremos todas as palavras
    // Agora só falta ordenar e escrever os resultados no arquivo de saída
    auto end_time = std::chrono::high_resolution_clock::now();
    cout << "Análise concluída! Total de palavras únicas: " << dicionario.size() << endl;
    vector<pair<string,int>>vetor =  dicionario.iterate();
    
    cout << "Ordenando palavras por frequência..." << endl;
    sortWordFrequencies(vetor);
    
    // Criamos o cabeçalho do arquivo de saída
    outputFile << "           ANÁLISE DE FREQUÊNCIA DE PALAVRAS           " << endl;
    outputFile << "Arquivo analisado: " << filename << endl;
    
    
    if (selectedType == structureTypes::AVLTREE) {
        outputFile << "Estrutura utilizada: AVL Tree" << endl;
    } else if (selectedType == structureTypes::RBTREE) {
        outputFile << "Estrutura utilizada: Red-Black Tree" << endl;
    } else if (selectedType == structureTypes::OPENHASH) {
        outputFile << "Estrutura utilizada: Open Hash" << endl;
    } else if (selectedType == structureTypes::CHAINEDHASH) {
        outputFile << "Estrutura utilizada: Chained Hash" << endl;
    }

    // Escrevemos os meta-dados da análise no arquivo de saída
    outputFile << "Total de palavras únicas: " << dicionario.size() << endl;
    outputFile << "Tempo total de execução: " 
              << std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count() 
              << " ms" << endl;
    if (dicionario.structureType == structureTypes::AVLTREE || dicionario.structureType == structureTypes::RBTREE){
        outputFile << "Número de comparações: " << dicionario.get_comparison_counter() << endl;
        outputFile << "Número de rotações: " << dicionario.get_rotations_counter() << endl;
    } else {
        outputFile << "Numero de comparações: " << dicionario.get_comparison_counter() << endl;
        outputFile << "Número de colisões: " << dicionario.get_colision_counter() << endl;
    }
    outputFile << "═══════════════════════════════════════════════════════" << endl;

    // Escrevemos as palavras e suas frequências no arquivo de saída em ordem
    for (const auto& pair : vetor) {
        outputFile << "Palavra: " << pair.first << ", Frequência: " << pair.second << endl;
    }
    outputFile << "═══════════════════════════════════════════════════════" << endl;

    outputFile.close();
    cout << "Análise concluída! Resultados salvos em: " << outputFilename << endl;
    // Acabou!!!!!!!!
}