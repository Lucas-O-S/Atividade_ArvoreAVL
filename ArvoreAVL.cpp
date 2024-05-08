#include "Node.cpp"

using namespace std;

class Arvore{

    private:

        Node* raiz; 
        int quantidadeNodes;

        //
        int alturaNode(Node* node){
            if(node == NULL){
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
            if(node){
                return alturaNode(node->left) - alturaNode(node->right);
            }
        }

        //Devolve a altura da arvore atravez de chamada
        
        
        
        
        
        
        
        // recursivas
        int AlturaArvore(Node* raiz){
            
            //Se não ouver um nó devolve -1
            if(raiz == nullptr){
                return -1;
            }

            else{
                //Se não usamos recursão para buscar mais nós a direita e a esqueda que receberão a altura de seus nós
                int direita = AlturaArvore(raiz->right);
                int  esquerda = AlturaArvore(raiz->left);

                //Ao fim de cada recursão recebemos a altura do maior nó mais 1
                if(direita > esquerda){
                    return direita + 1;
                }
                else{
                    return esquerda + 1;
                }
            }   
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

        //Busca Node pai do deletado
        Node* BuscarNodePai(Node* pai, string nome){

            
            Node* objetivo = pai;
             //Se objetivo for um nó nulo;
            if(objetivo == nullptr){
                
                cout << "\nvalor invalido" << endl;
                return nullptr;
            }

            else{
                
                //Se for encontrado o nó pai do objetivo acaba
                if((objetivo->left != nullptr && objetivo->left->contato->GetNome() == nome) || (objetivo->right != nullptr && objetivo->right->contato->GetNome() == nome)){
                    return objetivo;
                }

                else{
                    //Se não for encontrado o valor buscado entra-se em uma serie recursiva até achar o objetivo e devolver a função principal
                    if(objetivo->contato->GetNome() > nome){
                        objetivo = BuscarNodePai(objetivo->left,nome);
                    }
                    else if(objetivo->contato->GetNome() < nome){
                        objetivo = BuscarNodePai(objetivo->right,nome);

                    }
                    return objetivo;
                }
            }



        }

 

        //Deleta nó folha com base em seu pai e filho
        void DeletarFolha(Node* pai, Node* filho){

            //Para deletar o filho é cortado a conexão com o pai e depois deletado
            //Se for o nó da direita
            if(pai->right == filho){

                pai->right = nullptr;
            }

            //Se for o da esquerda
            else{

                pai->left =nullptr;
            }

            delete filho ;    
        }

        //Busca o nó mais a direita da esqueda do filho
        Node* MaisDireita(Node* filho){
             //Salva o valor do filho a esquerda
             Node* temp = filho->left;

            while(temp->right != nullptr){
                temp = temp->right;
            }

            return temp;
            

        }

        //Deleta Nós com dois filhos
        void DeletarNodeGrau2(Node* pai, Node* filho){

            //Salva o valor do nome procurado
            string SalvarContato = filho->contato->GetNome();
            
            //Cria o node mais adireita da esquerda do filho
            Node* maisDireita = MaisDireita(filho);

            //Troca o dado de ambos os nós, só o contato não do ponteiro
            Contato* DadoTemporario = maisDireita->contato;
            maisDireita->contato = filho->contato;
            filho->contato = DadoTemporario;
            
            //Se o filho não for iguai a raiz
            if(filho->left->contato->GetNome() != SalvarContato){
                //Joga o pai para ser o filho a esquerda de seu filho
                pai = filho->left;

            } 
            //Se for a raiz pai = filho
            else{

                pai  = filho;

            }


            
            while(pai != nullptr){
                //Descobrimos a onde está o nó que teve seu valor trocado em relação ao pai
                //enquanto não acharmos buscamos a posição de seu pai
                //Quando acharmos iremos verificar se o node deletado tinha filho ou não
                //Se tiver filho ele será conectado ao pai, se não sera cortada a conexão
                //Ao fim o node é deletado
                if(pai->left == maisDireita){
                    
                    if(maisDireita->left != nullptr){
                        pai->left = maisDireita->left;

                    }
                    else{
                        pai->left = nullptr;

                    }
                    delete maisDireita;

                    break;
                }
                else if(pai->right == maisDireita){
                    if(maisDireita->left != nullptr){
                        pai->right = maisDireita->left;

                    }
                    else{
                        pai->right =  nullptr;
                    }
                    delete maisDireita;
                    break;
                }
        
                if(filho->contato->GetNome() > pai->contato->GetNome()){
                    pai = pai->left;
                    
                }
                else{
                    pai = pai->right;
                }
            }


        }

        //Deleta um nó que só tenha um filho
        void DeletarNode1Filho(Node* pai, Node* filho){

           //Cria um nó temporario na posição do filho que será deletado 
          //Troca o ponteiro do filho para o seu filho

            Node* temporario = filho;

            if(filho->left != nullptr){
                temporario = filho->left;
            } 
            else{                        
                temporario = filho->right;

           }       

        // Se o deletado não for raiz
           if(pai != filho){

                //Conecta o pai a nova posição do filho
                if(pai->left == temporario){
                    pai->left = temporario;
                }

                else{
                    pai->right = temporario;
                }
                
                //deleta temporario
                delete filho;

           }

            //Se o deletado for raiz
           else{
                //filho será raiz
                raiz = temporario;
                //deleta pai
                delete pai;
           }

      
          
     


           //Deleta o temporario
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

        
        //Inseri um nó a arvore
        void inserir(Contato* contato){

            //Novo nó de contato
            Node* novoNode = new Node(contato);

            //Se raiz for nula adiciona o nó novo a raiz
            if(raiz == nullptr){
                raiz = novoNode;
            }
            else{

                //Se não pegamos criamos um nó temporario que começa da raiz
                Node* nodeTemp = raiz;
                Node* nodePai = nullptr;

                //enquanto não for nulo o nó folha verificamos em order alfabetica
                while (nodeTemp != nullptr)
                {
                    nodePai = nodeTemp;
                    //Se o nome vem depois(maior) então iremos a direita
                    if(nodeTemp->contato->GetNome() < contato->GetNome()){
                        nodeTemp = nodeTemp->right;
                    }

                    //Se o nome vem antes(menor) então iremos a esquerda
                    else if(nodeTemp->contato->GetNome() > contato->GetNome()){
                        nodeTemp = nodeTemp->left; 

                    }
                    //Ou se já existe, fazemos isso para evitar nomes iguais na arvore que daria problema já que em ordem alfabetica existe a possibilidade de nomes iguais
                    else{
                        cout << "\nContato já existe" << endl;
                        return;
                    }

                }

                // A posição do node temporario será igual ao novo node
                if(contato->GetNome() < nodePai->contato->GetNome()){
                    nodePai->left = novoNode;

                }
                else{
                    nodePai->right = novoNode;

                }

            }
            //Soma-se mais um ao contador de nós
            quantidadeNodes++;

        }

             //Faz a busca binaria da arvore com base no nome 
        Node* BuscarBinaria(Node* raiz, string nome){
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

        //Remove um nó da arvore
        void Remover(string nome){

            //Cria nó para o pai    
            Node* pai;

            //Busca a posição do pai do valor buscado a partir da raiz
            pai = BuscarNodePai(raiz,nome);
            
            //Verifica se o valor buscado existe antes de começar a deletar algo
            if(pai!=nullptr){

            
                //Node pai do node buscado
                Node* filho;

                //Verifica se o nó buscado não é a propria raiz então ele não terá filho e sera o proprio pai

                //Se não for raiz 
                if(pai->contato->GetNome() != nome){
                    
                    filho = BuscarBinaria(pai, nome);
                }

                //se for raiz filho será o proprio pai
                else{

                    filho = pai;
                }


                //Se for nó folha
                if(filho->left == nullptr && filho->right == nullptr){
                    
                    DeletarFolha(pai,filho);

                }
                else{
                    //Se for nó com dois filhos
                    
                    if(filho->left != nullptr && filho->right != nullptr){
                        DeletarNodeGrau2(pai, filho);
                    

                    }

                    //Node com um filho
                    else{
                        DeletarNode1Filho(pai,filho);
                    }
                }

                //Mensagem de sucesso
                cout << "\nDeletado com sucesso" << endl;
                quantidadeNodes--;
            }
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
            inserir(contato);

            
        }

        //Sobrecarga que já recebe dados direto
        void CriarContato(string nome,string numero, string  email){
            Contato* contato = new Contato(nome, email, numero);
            inserir(contato);
        }
        
        //Deleta o contato pedio;
        void Deletar(){
            string nome;
            cout << "Quem você deseja deletar: ";
            cin >> nome;

            Remover(nome);

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
            
            Node* nodeBuscado = BuscarBinaria(raiz, nome);
            
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
            
            Node* nodeBuscado = BuscarBinaria(raiz, nome);
            
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
            
            Node* nodeBuscado = BuscarBinaria(raiz, nome);
            
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
            return AlturaArvore(raiz);
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
    ;


};