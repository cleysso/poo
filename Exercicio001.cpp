#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include <vector>
#include <algorithm>

using namespace std;

class Filme {
private:
  int numero;
  string titulo;
  int faixaEtaria;
  string estilo;
public:
  Filme(int n=-1, string t="", int f=-1, string e=""){
    numero = n; 
    titulo = t; 
    faixaEtaria = f; 
    estilo = e; 
    }

  ~Filme(){}

  int obtemNumero() const { return numero; }
  string obtemTitulo() const { return titulo; }
  int obtemFaixaEtaria() const { return faixaEtaria; }
  string obtemEstilo() const { return estilo; }
  string str() const {
    string numerostr = to_string(numero);
    string output = "";
    if (faixaEtaria == 0) {
        output += titulo + " [" + numerostr + "] - " + "LIVRE" + " - " + estilo;
    }
    else {
        string faixaEtariastr = to_string(faixaEtaria);
        output += titulo + " [" + numerostr + "] - " + faixaEtariastr + " anos" + " - " + estilo;
    }
    return output;
  }
  void defineNumero(int n) { numero = n; }
  void defineTitulo(string t) { titulo = t; }
  void defineFaixaEtaria(int f) { faixaEtaria = f; }
  void defineEstilo(string e) { estilo = e; }
  bool operator<(const Filme &f) const { return titulo < f.obtemTitulo(); }
};

vector<string> splitCSV(string linha, char separador=';') {
    vector<string> res;
    string campo = "";
    for (int i=0; i<linha.size(); ++i) {
        char c = linha.at(i);
        if (c == separador) {
            res.push_back(campo);
            campo = "";
        } 
        else campo.append(1,c);
    }
    res.push_back(campo);
    return res;
}

int main(){
    string linha;
    vector<Filme> filmes;
    while(getline(cin, linha)){
        vector<string> campos = splitCSV(linha, ';');
        int id = stoi(campos[0]);
        string titulo = campos[1];
        int faixaEtaria = stoi(campos[2]);
        string estilo = campos[3];
        Filme f(id, titulo, faixaEtaria, estilo);
        filmes.push_back(f);
    }

    sort(filmes.begin(), filmes.end(), [](Filme f1, Filme f2) { return f1 < f2; });

    for (const Filme& f : filmes) {
        cout << f.str() << endl;
    }
}