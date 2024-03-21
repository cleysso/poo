#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <map>
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
    vector<Aposta> vencedores;
    int id_atual = 1001;

public:
    void iniciar() {
        apostas.clear();
        sorteados.clear();
        vencedores.clear();
        id_atual = 1001;
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

    void executa_sorteio() {
        bool vencedor = false;
        int rodadas = 0;

        while (getvencedores().size() == 0 && rodadas < 25) {
            sortear_numeros();
            for (auto & aposta : getApostas()) {
                vector<int> intersecao;
                vector<int> numeros = aposta.getNumeros();
                sort(numeros.begin(), numeros.end());
                sort(sorteados.begin(), sorteados.end());
                set_intersection(numeros.begin(), numeros.end(), sorteados.begin(), sorteados.end(), back_inserter(intersecao));
    
                if (intersecao.size() == 5) {
                    getvencedores().push_back(aposta);
                }
            }
            rodadas++;
        }

        if (getvencedores().size() == 0) {
            cout << "Não houve vencedores." << endl;
        } else {
            for (auto & vencedor : getvencedores()) {
            cout << "Aposta vencedora: " << vencedor.getId() << ", Nome: " << vencedor.getNome() << endl;
            }
        }

        cout << "Números sorteados: ";
        for (int num : sorteados) {
            cout << num << " ";
        }
        cout << endl;

        cout << "Rodadas de sorteio realizadas: " << rodadas << endl;
    }

    void exibir_resultados() {
        // a. Lista de números sorteados
        cout << "Números sorteados: ";
        for (int num : sorteados) {
            cout << num << " ";
        }
        cout << endl;

        // b. Quantas rodadas de sorteio foram realizadas
        cout << "Rodadas de sorteio realizadas: " << sorteados.size()/5 << endl;

        // c. Quantidade de apostas vencedoras
        cout << "Quantidade de apostas vencedoras: " << getvencedores().size() << endl;

        // d. Lista de apostas vencedoras
        if (getvencedores().size() > 0) {
            cout << "Apostas vencedoras: " << endl;
            for (auto & vencedor : getvencedores()) {
                    cout << "ID: " << vencedor.getId() << ", Nome: " << vencedor.getNome() << endl;
            }
        } else {
            cout << "Não houve vencedores." << endl;
        }

        // e. Lista de todos os números apostados
        map<int, int> frequencia;
        for (auto & aposta : getApostas()) {
            for (int num : aposta.getNumeros()) {
                frequencia[num]++;
            }
        }

        vector<pair<int, int>> freq(frequencia.begin(), frequencia.end());
        sort(freq.begin(), freq.end(), [](const pair<int, int>& a, const pair<int, int>& b) {
            return a.second > b.second;
        });

        cout << "Nro apostado | Qtd de apostas" << endl;
        for (auto & p : freq) {
            cout << "     " << setw(2) << setfill('0') << p.first << "             " << setw(2) << setfill('0') << p.second << endl;
        }
    }

    void exibir_premiacao() {
        if (vencedores.empty()) {
            cout << "Não houve vencedores." << endl;
        } else {
            double premiacao_por_vencedor = 10.0 / vencedores.size();
            cout << "Vencedores:" << endl;
            for (auto & vencedor : vencedores) {
                cout << "ID da aposta: " << vencedor.getId() << ", Nome: " << vencedor.getNome() << ", Prêmio: " << premiacao_por_vencedor << "ml de Felix Felicis" << endl;
            }
        }
    }
   

    vector<Aposta>& getApostas() { return apostas; }
    vector<Aposta>& getvencedores() { return vencedores; }
};

int main() {
    Sistema sistema;
    string nome, cpf;
    vector<int> numeros;
    int opcao, numero, id = 1001;
    bool apostas_finalizadas = 0;

    sistema.iniciar();

    while (true) {
        cout << "\n0. Encerrar programa\n1. Iniciar nova edição\n2. Registrar nova aposta\n3. Lista de apostas\n4. Finalizar apostas e executar o sorteio\n5. Apuração\n6. Premiação\n";
        cout << "\nSelecione uma opção: ";
        while(!(cin >> opcao)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Entrada inválida. Por favor, insira um número: ";
        }
        cout << endl;

        switch (opcao) {
            case 0:
                cout << "Programa encerrado!" << endl;
                return 0;
            case 1:
                cout << "\nVocê tem certeza que deseja iniciar uma nova edição? (Isso apagará os dados armazenados da edição atual)" << endl;
                cout << "(1) Sim" << endl;
                cout << "(2) Não" << endl;
                int escolha;
                while(!(cin >> escolha) || (escolha != 1 && escolha != 2)) {
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cout << "Entrada inválida. Por favor, insira 1 para iniciar uma nova edição ou 2 para voltar ao menu inicial: ";
                    }
                if (escolha == 1){
                    sistema.iniciar();
                    apostas_finalizadas = false;
                    cout << "\nNova edição iniciada" << endl;
                }
                break;
            case 2:
                if (apostas_finalizadas == false){
                    cout << "Digite o nome: ";
                    cin.ignore();
                    getline(cin, nome);
                    for (char c : nome){
                        if (!isalpha(c) && c != ' ') {
                            cout << "\nNome inválido. Tente novamente.\n";
                            continue;
                        }
                    }
                    cout << "Digite o CPF (apenas números): ";
                    cin >> cpf;
                    if (cpf.length() != 11) { // Verifica se o CPF tem 11 dígitos
                        cout << "\nCPF inválido. Tente novamente.\n";
                        continue;
                    }
                    int soma = 0;
                    for (char c : cpf) {
                        if (!isdigit(c)) { // Verifica se todos os caracteres são dígitos
                            cout << "\nCPF inválido. Tente novamente.\n";
                            continue;
                        }
                        soma += c - '0'; // Converte o caractere para um número e adiciona à soma
                    }
                    if (soma % 11 != 0) { // Verifica se a soma dos dígitos é múltipla de 11, que é o caso de um cpf válido
                        cout << "\nCPF inválido. Tente novamente.\n";
                        continue;
                    }
                    cout << "Deseja escolher os números (1) ou usar a surpresinha (2)? ";
                    int escolha;
                    while(!(cin >> escolha) || (escolha != 1 && escolha != 2)) {
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cout << "Entrada inválida. Por favor, insira 1 para escolher os números ou 2 para usar a surpresinha: ";
                    }
                    if (escolha == 1) {
                        cout << "Digite 5 números entre 1 e 50 para a aposta: ";
                        for (int i = 0; i < 5; i++) {
                            cin >> numero;
                            while(!(cin >> numero) || (numero < 1 || numero > 50)) {
                                cin.clear();
                                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                                cout << "Entrada inválida. Por favor, insira um número entre 1 e 50: ";
                            }
                            if (find(numeros.begin(), numeros.end(), numero) != numeros.end()) {
                                cout << "Número já escolhido! Por favor, escolha outro número." << endl;
                                i--;
                            }
                            else{
                                numeros.push_back(numero);
                            }
                        }
                    } else if (escolha == 2) {
                        random_device rd;
                        mt19937 gen(rd());
                        uniform_int_distribution<> dis(1, 50);
                        for (int i = 0; i < 5; i++) {
                            do {
                                numero = dis(gen);
                            } while (find(numeros.begin(), numeros.end(), numero) != numeros.end());
                            numeros.push_back(numero);
                        }
                    }
                    sistema.registrar_aposta(nome, cpf, numeros);
                    cout << endl;
                    cout << "Aposta registrada com sucesso! Os números apostados são: ";
                    for (int num : numeros) {
                        cout << num << " ";
                    }
                    cout << endl;
                    numeros.clear();
                } else{
                    cout << "Aposta já finalizada, veja a apuração e premiação ou inicie uma nova edição" << endl;
                }
                break;
            case 3:
                for (auto & aposta : sistema.getApostas()) {
                    cout << "ID: " << aposta.getId() << ", Nome: " << aposta.getNome() << ", CPF: " << aposta.getCpf() << ", Números: ";
                    for (int num : aposta.getNumeros()) {
                        cout << num << " ";
                }
                    cout << endl;
                }
                break;
            case 4:
                if (apostas_finalizadas == false){
                    sistema.executa_sorteio();
                    apostas_finalizadas = true;
                }
                else{
                    cout << "Aposta já finalizada, veja a apuração e premiação ou inicie uma nova edição" << endl;
                }
                break;
            case 5:
                if (apostas_finalizadas == true){
                    sistema.exibir_resultados();
                } else{
                    cout << "Fase de apostas ainda não finalizada, finalize-a executando o sorteio para poder ver a apuração" << endl;
                }
                break;
            case 6:
                if (apostas_finalizadas == true){
                    sistema.exibir_premiacao();
                } else{
                    cout << "Sorteio não realizado, finalize a fase de apostas e realize o sorteio para poder verificar a premiação" << endl;
                }
                break;
            default:
                cout << "Opção inválida\n";
        }
    }
    return 0;
}