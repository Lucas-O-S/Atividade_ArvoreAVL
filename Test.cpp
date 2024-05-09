#include "ArvoreAVL.cpp"

#include <iostream>

using namespace std;

int main(){

    Arvore arvore;

    arvore.CriarContato("5","","");
    cout << arvore.GetRaiz();

    arvore.CriarContato("3","","");
    cout << arvore.GetRaiz();

    arvore.CriarContato("4","","");
    cout << arvore.GetRaiz();


    arvore.CriarContato("7","","");
    cout << arvore.GetRaiz();

    arvore.CriarContato("8","","");
    cout << arvore.GetRaiz();

    arvore.CriarContato("9","","");
    cout << arvore.GetRaiz();

    arvore.Deletar("8");

      arvore.Deletar("9");

      cout << arvore.GetRaiz();




 




    

}