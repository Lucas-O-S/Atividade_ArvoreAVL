#include "Contatos.cpp"

using namespace std;




 class Node{


    public:
        Contato*  contato;
        Node* left;
        Node* right;
        int altura;

        //Construtor de nó 
        Node(Contato* contato)
        {
            this->contato = contato;
            altura = 0;
            left = nullptr;
            right = nullptr;
            
        };

        

      
    ;

    


};