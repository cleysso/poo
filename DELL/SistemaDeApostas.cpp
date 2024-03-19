#include <iostream>
#include <vector>
#include <algorithm>
#include <random>

using namespace std;

class Aposta {
private:
    string nome;
    string cpf;
    vector<int> numeros;
    int id;

public:
    Aposta(string nome, string cpf, vector<int> numeros, int id) : nome(nome), cpf(cpf), numeros(numeros), id(id) {}

    string getNome() { return nome; }
    string getCpf() { return cpf; }
    vector<int> getNumeros() { return numeros; }
    int getId() { return id; }

    void setNome(string nome) { this->nome = nome; }
    void setCpf(string cpf) { this->cpf = cpf; }
    void setNumeros(vector<int> numeros) { this->numeros = numeros; }
    void setId(int id) { this->id = id; }
};

class Sistema {
private:
    vector<Aposta> apostas;
    vector<int> sorteados;
    int id_atual = 1000;

public:
    void iniciar() {
        apostas.clear();
        sorteados.clear();
        id_atual = 1000;
    }

    void registrar_aposta(string nome, string cpf, vector<int> numeros) {
        getApostas().push_back(Aposta(nome, cpf, numeros, id_atual++));
    }

    void sortear_numeros() {
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> dis(1, 50);

        for (int n=0; n<5; ++n)
            sorteados.push_back(dis(gen));
    }

    void sorteio_adicional() {
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> dis(1, 50);

        for (int i=0; i<25; ++i) {
            sorteados.push_back(dis(gen));
            bool vencedor = false;

            for (auto & aposta : getApostas()) {
                vector<int> intersecao;
                vector<int> numeros = aposta.getNumeros();
                sort(numeros.begin(), numeros.end());
                set_intersection(numeros.begin(), numeros.end(), sorteados.begin(), sorteados.end(), back_inserter(intersecao));

                if (intersecao.size() == 5) {
                    cout << "Aposta vencedora: " << aposta.getId() << endl;
                    vencedor = true;
                    break;
                }
            }

            if (vencedor) {
                break;
            }
        }
    }


    void apuracao() {
        bool vencedor = false;
        int rodadas = 0;

        while (!vencedor && rodadas < 25) {
            for (auto & aposta : getApostas()) {
                vector<int> intersecao;
                vector<int> numeros = aposta.getNumeros();
                sort(numeros.begin(), numeros.end());
                set_intersection(numeros.begin(), numeros.end(), sorteados.begin(), sorteados.end(), back_inserter(intersecao));

                if (intersecao.size() == 5) {
                    cout << "Aposta vencedora: " << aposta.getId() << endl;
                    vencedor = true;
                    break;
                }
            }

            if (!vencedor) {
                sortear_numeros();
                rodadas++;
            }
        }

        if (!vencedor) {
            cout << "Não houve vencedores." << endl;
        }

        cout << "Números sorteados: ";
        for (int num : sorteados) {
            cout << num << " ";
        }
        cout << endl;

        cout << "Rodadas de sorteio realizadas: " << rodadas << endl;
    }

    vector<Aposta>& getApostas() { return apostas; }
};

int main(){
    cout << "ok" << endl;
}