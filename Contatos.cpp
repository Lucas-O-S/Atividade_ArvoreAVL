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

 
        //Construtor de contatos
        Contato(string nome, string numero, string email){
            this->nome = nome;
            this->numero = numero;
            this->email = email;
            favorito = false;
        }

        //Sobrecarga que considera o favorito
        Contato(string nome, string numero, string email, bool favorito){
            this->nome = nome;
            this->numero = numero;
            this->email = email;
            favorito = favorito;
        }

        //Mostra todos os dados
        string  MostrarDados(){
            
            return "+ " + nome + " - " + numero + " - " + email + "\n";  
        }

        //Muda o estado de favorito para true
        void Favoritar(){
            favorito=true;
        }

        //Muda o estado de favorito para false
         void Desfavoritar(){
            favorito=false;
        } 

        //Devolve o estado de favorito
        bool GetFavorito(){
            return favorito;
        }

        //Devolve o nome
        string GetNome(){
            return nome;
        }

        //Muda o nome;
        void SetNome(string nome){
            this->nome = nome;    
        }
  
    ;
};