#include <iostream>
#include "CaixaRegistradora.hpp"

using namespace std ;

int main () {
    CaixaRegistradora* caixa = new CaixaRegistradora();
    caixa -> adicionaItem(1.99); // Adiciona primeiro item
    caixa -> adicionaItem(2.99); // Adiciona segundo item
    caixa -> adicionaItem(1.50); // Adiciona terceiro item
    cout << caixa -> obtemTotal() << endl; // Saida : 6.48
    cout << caixa -> obtemNumItens() << endl; // Saida : 3
    caixa -> limpa(); 
    cout << caixa -> obtemTotal() << endl; // Saida : 0
    cout << caixa -> obtemNumItens() << endl; // Saida : 0
    delete caixa;
    CaixaRegistradora caixa2;
    caixa2.adicionaItem(123.456);
    cout << caixa2.obtemTotal() << endl ;
    cout << caixa2.obtemNumItens() << endl ;
    return 0;
}