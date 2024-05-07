#include <iostream>

using namespace std;

class Contato{

    private:

        string nome, numero, email;
        bool favorito;

        string CaixaAlta(const string& texto) const{
            string mensagem;
            for(char c: texto){
                mensagem+=toupper(c);
            }
            return mensagem;
        }

    ;

    public:

 

        Contato(string nome, string numero, string email){
            this->nome = nome;
            this->numero = numero;
            this->email = email;
            favorito = false;
        }

        string  MostrarDados(){
            
            return "+ " + nome + " - " + numero + " - " + email + "\n";  
        }

        void Favoritar(){
            favorito=true;
        }

         void Desfavoritar(){
            favorito=false;
        } 

        string GetNome(){
            return nome;
        }

        void SetNome(string nome){
            this->nome = nome;    
        }
  
    ;
};