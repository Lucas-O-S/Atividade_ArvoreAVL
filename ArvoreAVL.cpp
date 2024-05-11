#include "Node.cpp"

using namespace std;

class Arvore{

    private:

        Node* raiz; 
        int quantidadeNodes;

        //Devolve a alture de um nó
        int AlturaNode(Node* node){
            if(node == nullptr){
                return -1;
            }
            else{
                return node->altura;
            }
        }

        //Devolve a maior altura entre o nó a direita e a esqueda
        int MaiorAltura(int alturaA, int alturaB){
            return (alturaA>alturaB)? alturaA:alturaB;
        }

        //Retorna o fator de balanceamento do nó
        int FatorBalanceamento(Node* node){
            if(node != nullptr){
                return  AlturaNode(node->left) -  AlturaNode(node->right);
            }
            else{
                return 0;
            }
        }        
        
        
       
        //Faz uma rotação a esquerda e devolve uma nova raiz/pai
        Node* RotacaoEsquerda(Node* pai){

            //Cria um nó para o filho e para o possivel filho dele(Neto)
            Node *filho, *neto;

            //Filho recebe o valor do pai a direita
            filho = pai->right;

            //neto recebe o valor do filho a esquerda de filho
            if(filho->left != nullptr){
                neto = filho->left;
                
                //Raiz recebe o valor de um possivel neto como filho a direita
                pai->right = neto;


            }
            else{
                pai->right = nullptr;
            }


            
            //pai vira filho de filho(Ratação a esquerda)
            filho->left = pai;
            pai->altura = MaiorAltura(AlturaNode(pai->left),AlturaNode(pai->right)) + 1;
            filho->altura = MaiorAltura(AlturaNode(filho->left),AlturaNode(filho->right)) + 1;

            return filho;
        }

        //Faz uma rotação a direita e devolve uma nova raiz/pai
        Node* RotacaoDireita(Node* pai){

            //Cria um nó para o filho e para o possivel filho dele(Neto)
            Node *filho, *neto;

            //Filho recebe o valor do pai a esquerda
            filho = pai->left;

            //neto recebe o valor do filho a direita de filho
            if(filho->right != nullptr){
                neto = filho->right;
                
                //Raiz recebe o valor de um possivel neto como filho a esquerda
                pai->left = neto;


            }
            else{
                pai->left = nullptr;
            }


     
            //pai vira filho de filho(Ratação a direita)
            filho->right = pai;

            filho->altura = MaiorAltura(AlturaNode(filho->left),AlturaNode(filho->right)) + 1;

            //PAI tem sua altura atualizada e filho também
            pai->altura = MaiorAltura(AlturaNode(pai->left),AlturaNode(pai->right)) + 1;
            return filho;
        }

        //Rotação para a direita e depois a esquerda
        Node* RotacaoDireitaEsquerda(Node * pai){

            //Rotaciona a direita o filho a direita para o neto a esquerda
            pai->right = RotacaoDireita(pai->right);
            
            //Depois rotaciona o pai para a esquerda de seu filho que era o neto antes
            return RotacaoEsquerda(pai);
        }

        //Rotação para a direita e depois a esquerda
        Node* RotacaoEsquerdaDireita(Node * pai){

            //Rotaciona a esquerda o filho a esquerda para o neto a direita
            pai->left = RotacaoEsquerda(pai->left);

            //Depois rotaciona o pai para a direita de seu filho que era o noto antes       
            return RotacaoDireita(pai);
        }

        //Verifica o fator de balanceamento e devolve o arvore balanceada
        Node* Balancear(Node* pai){
            int fatorBalanceamento = FatorBalanceamento(pai);
        
            //Para ser balanceado o fator de balanceamento de pai deve ser 1 ,0 ou -1
            //fator de balanceamento de Pai = -2 ou menor e o do filho a direita for igual ou menor que 0 será rotacionado a esquerda
            if(fatorBalanceamento < -1 && FatorBalanceamento(pai->right) <= 0){
                pai = RotacaoEsquerda(pai);

            }

            //fator de balanceamento de Pai = 2 ou maior e o do filho a esquerda for igual ou maior que 0 será rotacionado a direita
            else if(fatorBalanceamento > 1 && FatorBalanceamento(pai->left) >= 0){
                pai = RotacaoDireita(pai);
            }

            //fator de balanceamento de Pai = 2 ou maior e o do filho a esquerda for menor que 0 será uma dupla rotação direita
            else if(fatorBalanceamento > 1 && FatorBalanceamento(pai->left) < 0){
                pai = RotacaoEsquerdaDireita(pai);
            }

            //fator de balanceamento de Pai = -2 ou menor e o do filho a direita for maior que 0 será uma dupla rotação esquerda
               else if(fatorBalanceamento < -1 && FatorBalanceamento(pai->right) > 0){
                pai = RotacaoDireitaEsquerda(pai);
            }


            //Devolve os nós
            return pai;
        }

    

        //Função recursiva que devolve a quantidade de nós folhas da arvore
        int QuantidadeFolhas(Node* raiz){

            //Se nó for nulo devolve 0
            if(raiz == nullptr){
                return 0;
            }
            //Se não houver filhos a direita e a esquerda devolve 1
            else if(raiz->left != nullptr && raiz->right != nullptr){
                return 1;
            }
            //Se houver filhos é devolvido a soma deles
            else{
                return QuantidadeFolhas(raiz->left) + QuantidadeFolhas(raiz->right);
            }

            //Ao final será somada a quantidade total de folhas 
        }

 

        //Deleta nó folha
        void DeletarFolha(Node* pai){
            delete pai;    
        }

        //Busca o nó mais a direita da esqueda de pai
        Node* MaisDireita(Node* pai){
             //Salva o valor do filho a esquerda
             Node* temp = pai->left;

            while(temp->right != nullptr){
                temp = temp->right;
            }

            return temp;
            

        }

        //Deleta Nós com dois filhos
        void DeletarNodeGrau2(Node* pai, Contato *contato){

            //Cria um nó temporario na posição mais a direita da esquerda de pai(Maio valor em relação a pai)
            Node* temporario = MaisDireita(pai);

            //Troca seus contatos salvos
            pai ->contato = temporario->contato;
            temporario->contato = contato;

            //Manda para deletar novamente só que agora o valor procurado estará em uma folha
            pai->left = Remover(pai->left, temporario->contato->GetNome());

        }

        //Deleta um nó que só tenha um filho e devolve o filho no lugar 
        Node* DeletarNode1Filho(Node* pai){

            //Cria um nó temporario    
            Node* temporario;

            //Verifica qual lado possui um filho

            if(pai->left != nullptr){
                temporario = pai->left;
            }
            else{
                
                temporario = pai->right;
            }

            delete pai;
            return temporario;
        }

           //Imprime em ordem(mostra dados em ordem do menor para maior), indo do mais a esqueda -> raiz -> direita -> sobe e repete
        void ImprimirEmOrdem(Node* pai){
            if(pai){
                ImprimirEmOrdem(pai->left);
                cout << pai->contato->MostrarDados();
                ImprimirEmOrdem(pai->right);
            }
        }

        
        //Imprime em ordem(mostra dados em ordem do menor para maior), indo do mais a esqueda -> raiz -> direita -> sobe e repete considerando favoritos
        void ImprimirEmOrdemFavoritos(Node* pai){
            if(pai){
                
                ImprimirEmOrdemFavoritos(pai->left);
                if(pai->contato->GetFavorito()){
                    cout << pai->contato->MostrarDados();
  
                }
                ImprimirEmOrdemFavoritos(pai->right);
            }
        }


        //Imprime em pré ordem, raiz -> filho a esqueda -> filho a direita
        void ImprimirPreOrdem(Node* pai){
            if(pai){

                cout << pai->contato->MostrarDados();
                ImprimirPreOrdem(pai->left);
                ImprimirPreOrdem(pai->right);
            }
        }

        //Imprime e pós ordem, Mais a esqueda -> direita -> raiz -> repete até acabar
        void ImprimirPosOrdem(Node* pai){
            if(pai){

                ImprimirPosOrdem(pai->left);
                ImprimirPosOrdem(pai->right);
                cout << pai->contato->MostrarDados();

            }
        }

        
        //Inseri um nó a arvore de forma recursiva
        Node* inserir(Node* pai, Contato* contato){

            //Se pai for nulo adiciona o nó novo ao pai
            if(pai == nullptr){
                Node* novoNode = new Node(contato);
                quantidadeNodes++;
                return novoNode;

            }
            else{
                //Busca a nova posição do nó 
                if(contato->GetNome() < pai->contato->GetNome()){
                    pai->left = inserir(pai->left, contato);
                }

                else if(contato->GetNome() > pai->contato->GetNome()){
                    pai->right = inserir(pai->right, contato);

                }
                //Verifica se o contato já existe
                else{
                    cout << "\nContato já existe"<< endl;
                }
          

            }
            //Recaucula a autura dos nós
            pai->altura = MaiorAltura(AlturaNode(pai->left),AlturaNode(pai->right) ) +1; 
            
            //Verifica a partir da raiz o balanceamento
            pai = Balancear(pai);

            return pai;
        }

             //Faz a busca binaria da arvore com base no nome 
        Node* BuscaBinaria(Node* raiz, string nome){
            Node* nodeTemporario = raiz;
                while(nodeTemporario != nullptr){

                    //Se achar termina metodo
                    if(nodeTemporario->contato->GetNome() == nome){
                        return nodeTemporario;
                    }

                    //Se não continua buscando 
                    if(nodeTemporario->contato->GetNome() < nome){
                        nodeTemporario = nodeTemporario->right;
                    }
                    else{
                        nodeTemporario = nodeTemporario->left;
                    }
                }

            return nullptr;      
            
        }

        //Remove um nó da arvore de forma recursiva
        Node* Remover(Node* pai, string nome){

            //Verifica se achou o nome
            if(pai == nullptr){
                cout << "\nNão foi possivel achar o contato" << endl;
                return nullptr;
            }

            if(pai->contato->GetNome() == nome){
                if(pai->left == nullptr && pai->right == nullptr){
                    DeletarFolha(pai);
                    quantidadeNodes--;

                    return nullptr;
                }
                else{
                    //Nó de segundo grau
                    if(pai->left != nullptr && pai->right != nullptr){
                        DeletarNodeGrau2(pai, pai->contato);

                        return pai;

                    }

                    //Apenas um filho
                    else{
                        quantidadeNodes--;
                        return DeletarNode1Filho(pai);

                    }
                }
            }
            //Busca o nó correto
            else{
                if(nome < pai->contato->GetNome()){
                    pai->left = Remover(pai->left,nome);

                }
                else{
                    pai->right = Remover(pai->right,nome);

                }
            }
            
            //Verifica se está balanceado e faz se nescessario
            pai = Balancear(pai);

            return pai;

        }
    
    ;

    public:

        //Construtor de arvore
        Arvore(){
            raiz = nullptr;
            quantidadeNodes = 0;
        }

        //função para criar contato do 0
        void CriarContato(){
            string nome, numero, email;

            cout << "\nNome do contato: ";
            cin >> nome;

            cout << "\nNumero do contato: ";
            cin >> numero;

            cout << "\nEmail do contato: ";
            cin >> email;

            cout << "\n";

            Contato* contato = new Contato(nome, email, numero);
            raiz = inserir(raiz, contato);

            
        }

        //Sobrecarga que já recebe dados direto
        void CriarContato(string nome,string numero, string  email){
            Contato* contato = new Contato(nome, numero, email);
            raiz = inserir(raiz, contato);
        }
        
        //Deleta o contato pedio;
        void Deletar(){
            string nome;
            cout << "Quem você deseja deletar: ";
            cin >> nome;

            raiz = Remover(raiz, nome);


        }

        //Sobrecarga de Deleta o contato pedio;
        void Deletar( string nome){

            raiz = Remover(raiz, nome);


        }

        //Mostra todos os favoritos;
        void MostrarFavoritos(){

            cout << "\nLista de favoritos:" << endl;

            ImprimirEmOrdemFavoritos(raiz);
        }

        //Busca contato que será favoritado;
        void Favoritar(){
            
            string nome;
            cout << "Quem você deseja favoritar: ";
            cin >> nome;
            
            Node* nodeBuscado = BuscaBinaria(raiz, nome);
            
            if(nodeBuscado != nullptr){
                nodeBuscado->contato->Favoritar();
                cout << "\nFavoritado com sucesso";
            }
            else{
                
                cout << "\n Contato não encontrado" << endl;            

            }
      
            
        }

      //Busca contato que será desfavoritar;
        void Desfavoritar(){
            
            string nome;
            cout << "Quem você deseja desfavoritar: ";
            cin >> nome;
            
            Node* nodeBuscado = BuscaBinaria(raiz, nome);
            
            if(nodeBuscado != nullptr){
                nodeBuscado->contato->Desfavoritar();
                cout << "\nDesfavoritado com sucesso";
            }
            else{
                
                cout << "\n Contato não encontrado" << endl;            

            }
      
            
        }
      
 
        //Faz a busca binaria da arvore com base no nome 
        void Buscar(){
            
            string nome;
            cout << "Quem você deseja buscar: ";
            cin >> nome;
            
            Node* nodeBuscado = BuscaBinaria(raiz, nome);
            
            if(nodeBuscado != nullptr){
                cout << nodeBuscado->contato->MostrarDados();
            }
            else{
                
                cout << "\n Contato não encontrado" << endl;            

            }
      
            
        }

        //Devolve a altura da arvore
        int BuscarAltura(){

            //Usa uma função recursiva para calcular a altura da arvore
            return AlturaNode(raiz);
        }

        //Devolve a quantidade de Nós da arvore
        int BuscarQuantidadeNodes(){
            //Usa a variavel de contador de nós
            return quantidadeNodes;
        }

        //Devolve a quantidade de nós folhas da arvore
        int BuscarFolhas(){

            //Usa uma função recursiva para pegar a quantidade de nós folhas(Sem filhos)
            return QuantidadeFolhas(raiz);
        }

        //Mostra dados da arvore em ordem alfabetica
        void ConsultaAlfabetica(){
            ImprimirEmOrdem(raiz);
        }

        //Devolve o valor da raiz
        string GetRaiz(){
            return raiz->contato->GetNome();
        }
    ;




};