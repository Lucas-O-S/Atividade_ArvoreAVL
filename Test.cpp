#include "ArvoreAVL.cpp"
#include <iostream>

using namespace std;

int main(){

    Arvore arvore;

    arvore.inserir(new Contato("50","",""));
    arvore.inserir(new Contato("25","",""));
    arvore.inserir(new Contato("75","",""));
    arvore.inserir(new Contato("12","",""));
    arvore.inserir(new Contato("342","",""));
    arvore.inserir(new Contato("11","",""));
    arvore.inserir(new Contato("3","",""));
    arvore.inserir(new Contato("85","",""));



    arvore.ConsultaAlfabetica();
    cout << "\n" << arvore.BuscarQuantidadeNodes();
    arvore.Buscar("3");

 
    arvore.Remover("71");
    arvore.Remover("85");


 


    arvore.ConsultaAlfabetica();


    

}