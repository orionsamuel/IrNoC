#include <vector>

using namespace std;

struct table {
	int destiny;
	int port;
	int hops;
};

typedef vector <table> routing_table;

class routing{
public:
	

	routing_table tabela;
	int destiny; //Entra o endereço do roteador destino
	int portDestiny; //Retorna a porta por onde o pacote deve passar



	int tableAcess(){
		for(int i = 0; i < tabela.size(); i++){
			if(tabela[i].destiny == destiny){
				portDestiny = tabela[i].port;
			}
		}
		return portDestiny;
	}


	routing(){

    }
};
