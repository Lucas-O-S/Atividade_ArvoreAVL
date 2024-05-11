#include "ArvoreAVL.cpp"

#include <iostream>

using namespace std;

//Testa inserção
bool TesteInsercao(){
  Arvore arvore;

  arvore.CriarContato("50","","");
  arvore.CriarContato("25","","");
  arvore.CriarContato("10","","");
  arvore.CriarContato("3","","");

  cout <<"\n" << arvore.BuscarQuantidadeNodes() << " nodes foram adicionados e a quantidade esperada: 4";

  if(arvore.BuscarQuantidadeNodes() == 4){
    return true;
  } 
  else{
    return false;
  }
}

bool TesteExclusao(){
  Arvore arvore;

  arvore.CriarContato("50","","");
  arvore.CriarContato("25","","");
  arvore.CriarContato("10","","");
  arvore.CriarContato("3","","");

  arvore.Deletar("50");
  arvore.Deletar("25");
  arvore.Deletar("10");

  

  cout <<"\n" << arvore.BuscarQuantidadeNodes() << " nodes existente e a quantidade esperada: 1" << endl;
  cout <<"\n Node raiz = " << arvore.GetRaiz() << " - valor esperada: 3" << endl;

  if(arvore.BuscarQuantidadeNodes() == 1 && arvore.GetRaiz() == "3"){
    return true;
  } 
  else{
    return false;
  }
}

bool TesteBalanceamento(){
  Arvore arvore;
  arvore.CriarContato("50","","");
  arvore.CriarContato("25","","");
  arvore.CriarContato("30","","");

  cout << "\nForam adicionados os valores 50, 25 e 30, isso fara a arvore ficar desbalanceada" << endl;
  cout << "\nRaiz deve ser 30 e a raiz encontrada igual a " << arvore.GetRaiz() << endl;

  if(arvore.GetRaiz() == "30"){
    return true;
  }

  else{
    return false;
  }

}


int main(){

  cout << "\nTeste de Inserir: " << endl;

  if(TesteInsercao() == false){
    cout << "\nTeste de inserção falhou" << endl;
  }
  else{
    cout << "\nTeste de inserção foi um sucesso" << endl;

  }
  
  cout << "\nTeste de Excluir: " << endl;

 if(TesteExclusao() == false){
    cout << "\nTeste de exclusão falhou" << endl;
  }
  else{
    cout << "\nTeste de exclusão foi um sucesso" << endl;

  }


 if(TesteBalanceamento() == false){
    cout << "\nTeste de balanceamento falhou" << endl;
  }
  else{
    cout << "\nTeste de balanceamento foi um sucesso" << endl;

  }


    

}