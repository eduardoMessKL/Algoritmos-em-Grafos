//Equipe Grêmio FBPA
//Eduardo Messias Kulka e Gabriel Caldas
//Turma B

#include <iostream>
#include <vector>
#include <queue>
#include <map>

using namespace std;

// Define as dimensões do tabuleiro de xadrez
const int tamanho_tabuleiro = 8;

// Movimentos possíveis do cavalo
const vector<pair<int, int>> movimentos_cavalo = {{2, 1}, {1, 2}, {-1, 2}, {-2, 1}, {-2, -1}, {-1, -2}, {1, -2}, {2, -1}};

// Converte coordenadas no estilo xadrez para coordenadas de matriz
pair<int, int> paraCoordenadasMatriz(string posicao) {
    int coluna = posicao[0] - 'a';
    int linha = tamanho_tabuleiro - (posicao[1] - '0');
    return {linha, coluna};
}

// Converte coordenadas de matriz para coordenadas no estilo xadrez
string paraCoordenadasEstiloXadrez(pair<int, int> posicao) {
    string coordenadasXadrez = "";
    coordenadasXadrez += ('a' + posicao.second);
    coordenadasXadrez += ('1' + (tamanho_tabuleiro - posicao.first));
    return coordenadasXadrez;
}

// Implementação do algoritmo Floyd-Warshall
int calcularMovimentosCavalo(pair<int, int> pontoA, pair<int, int> pontoB) {
    vector<vector<int>> distancia(tamanho_tabuleiro, vector<int>(tamanho_tabuleiro, -1));
    queue<pair<int, int>> fila;

    // Define a distância de pontoA para pontoA como 0 e enfileira
    distancia[pontoA.first][pontoA.second] = 0;
    fila.push(pontoA);

    // Realiza busca em largura
    while (!fila.empty()) {
        pair<int, int> atual = fila.front();
        fila.pop();

        // Verifica se chegamos ao ponto de destino pontoB
        if (atual == pontoB) {
            return distancia[atual.first][atual.second];
        }

        // Explora as posições vizinhas
        for (int i = 0; i < 8; ++i) {
            int novaLinha = atual.first + movimentos_cavalo[i].first;
            int novaColuna = atual.second + movimentos_cavalo[i].second;

            // Verifica se a nova posição está dentro do tabuleiro de xadrez e ainda não foi visitada
            if (novaLinha >= 0 && novaLinha < tamanho_tabuleiro && novaColuna >= 0 && novaColuna < tamanho_tabuleiro && distancia[novaLinha][novaColuna] == -1) {
                distancia[novaLinha][novaColuna] = distancia[atual.first][atual.second] + 1;
                fila.push({novaLinha, novaColuna});
            }
        }
    }

    // O ponto de destino pontoB não é alcançável a partir do pontoA
    return -1;
}

bool coordenadaValida(string &coordenada) {
    if (coordenada.size() != 2) {
        return false;
    }
    
    // A coluna deve ser de 'a' a 'h'
    if (coordenada[0] < 'a' || coordenada[0] > 'h'){
        return false;
    }

    // A linha deve ser de 1 a 8
    if (coordenada[1] < '1' || coordenada[1] > '8'){
        return false;
    }
    
    return true;
}

int main() {
     cout << endl;
    while (true) {
        string pontoA, pontoB;
     
        cout << "------| Movimento do Cavalo |------" << endl << endl;
        cout << "Escreva a coordenada A, se baseando no tabuleiro de xadrez: ";
        cin >> pontoA;
        cout << "Escreva a coordenada B, se baseando no tabuleiro de xadrez: ";
        cin >> pontoB;
        cout << endl;

        // Verifica a condição de saída ou valida as entradas
        if (pontoA == "sair" || pontoB == "sair" || 
            !coordenadaValida(pontoA) || !coordenadaValida(pontoB)) {
            break;
        }

        pair<int, int> matrizPontoA = paraCoordenadasMatriz(pontoA);
        pair<int, int> matrizPontoB = paraCoordenadasMatriz(pontoB);

        int num_movimentos = calcularMovimentosCavalo(matrizPontoA, matrizPontoB);
         if (num_movimentos != -1) {
            cout << "To get from " << pontoA << " to " << pontoB << " takes " << num_movimentos << " knight moves." << endl;
        } else {
            cout << "Point B is not reachable from point A!" << endl;
        }

    }
    return 0;
}

