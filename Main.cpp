#include "ArvoreAVL.cpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>


using namespace std;

void AcessarDados(Arvore* arvore){
    
    fstream arquivo("Contatos.csv");

    if(arquivo.is_open()){
        cout << "\nDados antigos encontrados, eles serão adicionados a lista" << endl; 


        string linha;

        while(getline(arquivo, linha)){
            istringstream ss(linha);

            string nome, email, numero;
            getline(ss,nome,';');
            getline(ss,email,';');
            getline(ss,numero,';');


            arvore->CriarContato(nome,numero,email);

        }

        arquivo.close();
    }

}

int main(){

    Arvore* arvore = new Arvore;

    
    cout << "Acessando Lista de contatos:" << endl;

    //Colocar uma função que adiona contatos de um arquivo csv
    AcessarDados(arvore);

    int escolha;
    bool repetir = true;

    while(repetir){


        cout << "\n O que deseja fazer: " << endl;
        cout << "\n 1 - Adicionar novo contato\n 2 - Remover contato\n 3 - Buscar contato\n 4 - Listar Contatos\n 5 - Listar favoritos\n 6 - Favoritar contato\n 7 - Desfavoritar Contato\n 8 - Sair \n";

        cin >> escolha;

        switch (escolha)
        {
            case 1:

                arvore->CriarContato();


            break;

            case 2:
                arvore->Deletar();
            
            break;
            
            case 3:

                arvore->Buscar();

            break;

            case 4:
            
                arvore->ConsultaAlfabetica();

            break;

            case 5:

                arvore->MostrarFavoritos();
            
            break;

            case 6:

                arvore->Favoritar();

            break;

            case 7:

                arvore->Desfavoritar();

            break;

            case 8:

                repetir = false;

            break;

            default:
                cout << "\n Erro, valor invalido" << endl;
            
            break;

  
        }



    }

    cout << "\nSaindo do sistema...";

    return 0;

}