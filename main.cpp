#include "systemc.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include "router_2.h"
#include "caminho_min.h"


SC_MODULE(NoC){

	sc_in<bool> clk;

	int coreNumbers;
	int prioridade;
	int router_num;
	int r1, r2;
	int real_time;

	trafego_rede trafego;

	conexoes conexoes_rede;

	router_2 *rt[25];;
	routing_table table[25];
	int router_count[25];

	void chaveamento_externo(){
		for(int i = 0; i < (router_num + (router_num / 4)); i++){
			router_count[i] =  0;
		}

		for(int i = 0; i < (router_num + (router_num / 4)); i++){
			if((router_count[(conexoes_rede[i].primeiro)-1] == 0) && (router_count[(conexoes_rede[i].segundo)-1] == 0)){
				rt[(conexoes_rede[i].primeiro)-1]->in_port[0] = rt[(conexoes_rede[i].segundo)-1]->out_port[0];
				rt[(conexoes_rede[i].primeiro)-1]->in_val[0].write(rt[(conexoes_rede[i].segundo)-1]->out_val[0]);
				rt[(conexoes_rede[i].segundo)-1]->in_port[0] = rt[(conexoes_rede[i].primeiro)-1]->out_port[0];
				rt[(conexoes_rede[i].segundo)-1]->in_val[0].write(rt[(conexoes_rede[i].primeiro)-1]->out_val[0]);
				router_count[(conexoes_rede[i].primeiro)-1]++;
				router_count[(conexoes_rede[i].segundo)-1]++;
			}else if((router_count[(conexoes_rede[i].primeiro)-1] == 0) && (router_count[(conexoes_rede[i].segundo)-1] == 1)){
				rt[(conexoes_rede[i].primeiro)-1]->in_port[0] = rt[(conexoes_rede[i].segundo)-1]->out_port[1];
				rt[(conexoes_rede[i].primeiro)-1]->in_val[0].write(rt[(conexoes_rede[i].segundo)-1]->out_val[1]);
				rt[(conexoes_rede[i].segundo)-1]->in_port[1] = rt[(conexoes_rede[i].primeiro)-1]->out_port[0];
				rt[(conexoes_rede[i].segundo)-1]->in_val[1].write(rt[(conexoes_rede[i].primeiro)-1]->out_val[0]);
				router_count[(conexoes_rede[i].primeiro)-1]++;
				router_count[(conexoes_rede[i].segundo)-1]++;
			}else if((router_count[(conexoes_rede[i].primeiro)-1] == 0) && (router_count[(conexoes_rede[i].segundo)-1] == 2)){
				rt[(conexoes_rede[i].primeiro)-1]->in_port[0] = rt[(conexoes_rede[i].segundo)-1]->out_port[2];
				rt[(conexoes_rede[i].primeiro)-1]->in_val[0].write(rt[(conexoes_rede[i].segundo)-1]->out_val[2]);
				rt[(conexoes_rede[i].segundo)-1]->in_port[2] = rt[(conexoes_rede[i].primeiro)-1]->out_port[0];
				rt[(conexoes_rede[i].segundo)-1]->in_val[2].write(rt[(conexoes_rede[i].primeiro)-1]->out_val[0]);
				router_count[(conexoes_rede[i].primeiro)-1]++;
				router_count[(conexoes_rede[i].segundo)-1]++;
			}else if((router_count[(conexoes_rede[i].primeiro)-1] == 1) && (router_count[(conexoes_rede[i].segundo)-1] == 0)){
				rt[(conexoes_rede[i].primeiro)-1]->in_port[1] = rt[(conexoes_rede[i].segundo)-1]->out_port[0];
				rt[(conexoes_rede[i].primeiro)-1]->in_val[1].write(rt[(conexoes_rede[i].segundo)-1]->out_val[0]);
				rt[(conexoes_rede[i].segundo)-1]->in_port[0] = rt[(conexoes_rede[i].primeiro)-1]->out_port[1];
				rt[(conexoes_rede[i].segundo)-1]->in_val[0].write(rt[(conexoes_rede[i].primeiro)-1]->out_val[1]);
				router_count[(conexoes_rede[i].primeiro)-1]++;
				router_count[(conexoes_rede[i].segundo)-1]++;
			}else if((router_count[(conexoes_rede[i].primeiro)-1] == 1) && (router_count[(conexoes_rede[i].segundo)-1] == 1)){
				rt[(conexoes_rede[i].primeiro)-1]->in_port[1] = rt[(conexoes_rede[i].segundo)-1]->out_port[1];
				rt[(conexoes_rede[i].primeiro)-1]->in_val[1].write(rt[(conexoes_rede[i].segundo)-1]->out_val[1]);
				rt[(conexoes_rede[i].segundo)-1]->in_port[1] = rt[(conexoes_rede[i].primeiro)-1]->out_port[1];
				rt[(conexoes_rede[i].segundo)-1]->in_val[1].write(rt[(conexoes_rede[i].primeiro)-1]->out_val[1]);
				router_count[(conexoes_rede[i].primeiro)-1]++;
				router_count[(conexoes_rede[i].segundo)-1]++;
			}else if((router_count[(conexoes_rede[i].primeiro)-1] == 1) && (router_count[(conexoes_rede[i].segundo)-1] == 2)){
				rt[(conexoes_rede[i].primeiro)-1]->in_port[1] = rt[(conexoes_rede[i].segundo)-1]->out_port[2];
				rt[(conexoes_rede[i].primeiro)-1]->in_val[1].write(rt[(conexoes_rede[i].segundo)-1]->out_val[2]);
				rt[(conexoes_rede[i].segundo)-1]->in_port[2] = rt[(conexoes_rede[i].primeiro)-1]->out_port[1];
				rt[(conexoes_rede[i].segundo)-1]->in_val[2].write(rt[(conexoes_rede[i].primeiro)-1]->out_val[1]);
				router_count[(conexoes_rede[i].primeiro)-1]++;
				router_count[(conexoes_rede[i].segundo)-1]++;
			}else if((router_count[(conexoes_rede[i].primeiro)-1] == 2) && (router_count[(conexoes_rede[i].segundo)-1] == 0)){
				rt[(conexoes_rede[i].primeiro)-1]->in_port[2] = rt[(conexoes_rede[i].segundo)-1]->out_port[0];
				rt[(conexoes_rede[i].primeiro)-1]->in_val[2].write(rt[(conexoes_rede[i].segundo)-1]->out_val[0]);
				rt[(conexoes_rede[i].segundo)-1]->in_port[0] = rt[(conexoes_rede[i].primeiro)-1]->out_port[2];
				rt[(conexoes_rede[i].segundo)-1]->in_val[0].write(rt[(conexoes_rede[i].primeiro)-1]->out_val[2]);
				router_count[(conexoes_rede[i].primeiro)-1]++;
				router_count[(conexoes_rede[i].segundo)-1]++;
			}else if((router_count[(conexoes_rede[i].primeiro)-1] == 2) && (router_count[(conexoes_rede[i].segundo)-1] == 1)){
				rt[(conexoes_rede[i].primeiro)-1]->in_port[2] = rt[(conexoes_rede[i].segundo)-1]->out_port[1];
				rt[(conexoes_rede[i].primeiro)-1]->in_val[2].write(rt[(conexoes_rede[i].segundo)-1]->out_val[1]);
				rt[(conexoes_rede[i].segundo)-1]->in_port[1] = rt[(conexoes_rede[i].primeiro)-1]->out_port[2];
				rt[(conexoes_rede[i].segundo)-1]->in_val[1].write(rt[(conexoes_rede[i].primeiro)-1]->out_val[2]);
				router_count[(conexoes_rede[i].primeiro)-1]++;
				router_count[(conexoes_rede[i].segundo)-1]++;
			}else if((router_count[(conexoes_rede[i].primeiro)-1] == 2) && (router_count[(conexoes_rede[i].segundo)-1] == 2)){
				rt[(conexoes_rede[i].primeiro)-1]->in_port[2] = rt[(conexoes_rede[i].segundo)-1]->out_port[2];
				rt[(conexoes_rede[i].primeiro)-1]->in_val[2].write(rt[(conexoes_rede[i].segundo)-1]->out_val[2]);
				rt[(conexoes_rede[i].segundo)-1]->in_port[2] = rt[(conexoes_rede[i].primeiro)-1]->out_port[2];
				rt[(conexoes_rede[i].segundo)-1]->in_val[2].write(rt[(conexoes_rede[i].primeiro)-1]->out_val[2]);
				router_count[(conexoes_rede[i].primeiro)-1]++;
				router_count[(conexoes_rede[i].segundo)-1]++;
			}
		}
	}



	void map_rede(){
		for (int i = 0; i < coreNumbers; i++){
			rt[i]->tabela = table[i];
		}
	}

	void set_packets(){
		//srand((unsigned)time(NULL));
		for(int i = 0; i < coreNumbers; i++){
			for(int j = 0; j < trafego.size(); j++){
				if(rt[i]->position == trafego[j].origem){
					rt[i]->in_val[4].write(1);
					for(int k = 0; k < trafego[j].pacotes; k++){
						prioridade = 1 + (rand() % 2);
						for(int l = 0; l < 5; l++){
							if(l == 0){
								rt[i]->in_port[4].type = BEGIN_PACKET;
								rt[i]->in_port[4].payload = (8 + i);
								rt[i]->in_port[4].destiny = trafego[j].destino;
								rt[i]->in_port[4].priority = prioridade;
								wait(3);
								rt[i]->in_port[4].type = 0;
							}else if(l == 4){
								rt[i]->in_port[4].type = END_PACKET;
								rt[i]->in_port[4].payload = (8 + i);
								rt[i]->in_port[4].destiny = trafego[j].destino;
								wait(3);
								rt[i]->in_port[4].type = 0;
							}else{
								rt[i]->in_port[4].type = INSTRUCTION;
								rt[i]->in_port[4].payload = (8 + i);
								rt[i]->in_port[4].destiny = trafego[j].destino;
								wait(3);
								rt[i]->in_port[4].type = 0;
							}
						}
					}
				}
			}
		}
	}


	SC_CTOR(NoC){
		for(int i = 0; i < 25; i++){
			rt[i] = new router_2("rt");
			rt[i]->clk(clk);
		}

		SC_METHOD(chaveamento_externo);
		sensitive << clk.pos();
		SC_METHOD(map_rede);
		sensitive << clk.pos();
		SC_CTHREAD(set_packets, clk.pos());
	}
};

using namespace std;

int sc_main (int argc, char* argv[]){

	sc_clock clock("Clock", 10, SC_NS);

	NoC rede("NoC");
	rede.clk(clock);

	int coreNumbers;
	char linha[100];
	string temp0;
	string temp1;
	string temp2;
	string temp3;
	int temp00;
	int temp01;
	int temp02;
	int temp03;
	int count;
	int dist[10][10];
	int caminho[10][10];
	caminho_min cam;


	trafego_rede trafego;

	float deadline_parcial, deadline;
	int total_packets;
	sc_time latencia_parcial, latencia_media, zera_latencia;
	sc_time conste(0, SC_NS);

	ifstream arquivoTrafego;
	ofstream saidaDados;


	//Instanciamento do arquivo de trafego
	arquivoTrafego.open("01.txt", ios_base::in);
	if (arquivoTrafego.is_open()){
		arquivoTrafego.getline(linha, 100);
		coreNumbers = atoi(linha);
		while(arquivoTrafego.getline(linha, 100)){
			temp0 = "";
			temp1 = "";
			temp2 = "";
			temp3 = "";
			for(count = 0; count < 100; count++){
				if(linha[count] != ' '){
					temp0 = temp0 + linha[count];
				}else{
					break;
				}
			}
			temp00 = atoi(temp0.c_str());
			count = count + 1;

			for(; count < 100; count ++){
				if(linha[count] != ' '){
					temp1 = temp1 + linha[count];
				}else{
					break;
				}
			}
			temp01 = atoi(temp1.c_str());
			count = count + 1;

			for(; count < 100; count ++){
				if(linha[count] != ' '){
					temp2 = temp2 + linha[count];
				}else{
					break;
				}
			}
			temp02 = atoi(temp2.c_str());
			count = count + 1;

			for(; count < 100; count ++){
				if(linha[count] != ' '){
					temp3 = temp3 + linha[count];
				}else{
					break;
				}
			}
			temp03 = atoi(temp3.c_str());

			trafego.push_back({temp00, temp01, temp02, temp03});
		}
	}

	arquivoTrafego.close();

	int router_num = coreNumbers;

	rede.coreNumbers = coreNumbers;
	rede.trafego = trafego;


	for(int i = 0; i < coreNumbers; i++){
		rede.rt[i]->position = i + 1;
	}

	conexoes mapeamento;
	srand (time(0));
	for(int i = 0; i < 10; i++){
		Conexoes temp;
		temp.primeiro = 1 + rand() % 10;
		temp.segundo = 1 + rand() % 10;
		mapeamento.push_back(temp);
	}

	rede.conexoes_rede = mapeamento;

			
	//Preenchimento da matriz de adjacência
	for(int i = 0; i < router_num; i++){
		for(int j = 0; j < router_num; j++){
			if (i == j){
				dist[i][j] = 0;
			}else{
				for(int k = 0; k < (router_num + (router_num / 4)); k++){
					if((rede.conexoes_rede[k].primeiro - 1) == i){
						if((rede.conexoes_rede[k].segundo - 1) == j){
							dist[i][j] = 1;
							dist[j][i] = 1;
						}
					}
				}
			}						
		}
	}


			

	for(int i = 0; i < router_num; i++){
		for(int j = 0; j < router_num; j++){
			if((i != j) && (dist[i][j] != 1)){
				dist[i][j] = 100;
			}
		}
	}


	//Passagem dos valores das matrizes pro caminho mínimo	
	cam.floyd(dist, caminho);

	//Preenchimento das tabelas de roteamento
	int router_count[(router_num + (router_num / 4))];
	int tab_aux[router_num][router_num];


	for(int i = 0; i < (router_num + (router_num / 4)); i++){
		router_count[i] =  0;
	}

	for(int i = 0; i < router_num; i++){
		for(int j = 0; j < router_num; j++){
			tab_aux[i][j] = 100;
		}
	}

	for(int i = 0; i < router_num; i++){
		for(int j = 0; j < router_num; j++){
			if(i == j){
				tab_aux[i][j] = 4;
			}
		}
	}



	for(int i = 0; i < (router_num + (router_num / 4)); i++){
		if((router_count[(rede.conexoes_rede[i].primeiro)-1] == 0) && (router_count[(rede.conexoes_rede[i].segundo)-1] == 0)){
			tab_aux[(rede.conexoes_rede[i].primeiro)-1][(rede.conexoes_rede[i].segundo)-1] = 0;
			tab_aux[(rede.conexoes_rede[i].segundo)-1][(rede.conexoes_rede[i].primeiro)-1] = 0;
			router_count[(rede.conexoes_rede[i].primeiro)-1]++;
			router_count[(rede.conexoes_rede[i].segundo)-1]++;
		}else if((router_count[(rede.conexoes_rede[i].primeiro)-1] == 0) && (router_count[(rede.conexoes_rede[i].segundo)-1] == 1)){
			tab_aux[(rede.conexoes_rede[i].primeiro)-1][(rede.conexoes_rede[i].segundo)-1] = 0;
			tab_aux[(rede.conexoes_rede[i].segundo)-1][(rede.conexoes_rede[i].primeiro)-1] = 1;
			router_count[(rede.conexoes_rede[i].primeiro)-1]++;
			router_count[(rede.conexoes_rede[i].segundo)-1]++;
		}else if((router_count[(rede.conexoes_rede[i].primeiro)-1] == 0) && (router_count[(rede.conexoes_rede[i].segundo)-1] == 2)){
			tab_aux[(rede.conexoes_rede[i].primeiro)-1][(rede.conexoes_rede[i].segundo)-1] = 0;
			tab_aux[(rede.conexoes_rede[i].segundo)-1][(rede.conexoes_rede[i].primeiro)-1] = 2;
			router_count[(rede.conexoes_rede[i].primeiro)-1]++;
			router_count[(rede.conexoes_rede[i].segundo)-1]++;
		}else if((router_count[(rede.conexoes_rede[i].primeiro)-1] == 1) && (router_count[(rede.conexoes_rede[i].segundo)-1] == 0)){
			tab_aux[(rede.conexoes_rede[i].primeiro)-1][(rede.conexoes_rede[i].segundo)-1] = 1;
			tab_aux[(rede.conexoes_rede[i].segundo)-1][(rede.conexoes_rede[i].primeiro)-1] = 0;
			router_count[(rede.conexoes_rede[i].primeiro)-1]++;
			router_count[(rede.conexoes_rede[i].segundo)-1]++;
		}else if((router_count[(rede.conexoes_rede[i].primeiro)-1] == 1) && (router_count[(rede.conexoes_rede[i].segundo)-1] == 1)){
			tab_aux[(rede.conexoes_rede[i].primeiro)-1][(rede.conexoes_rede[i].segundo)-1] = 1;
			tab_aux[(rede.conexoes_rede[i].segundo)-1][(rede.conexoes_rede[i].primeiro)-1] = 1;
			router_count[(rede.conexoes_rede[i].primeiro)-1]++;
			router_count[(rede.conexoes_rede[i].segundo)-1]++;
		}else if((router_count[(rede.conexoes_rede[i].primeiro)-1] == 1) && (router_count[(rede.conexoes_rede[i].segundo)-1] == 2)){
			tab_aux[(rede.conexoes_rede[i].primeiro)-1][(rede.conexoes_rede[i].segundo)-1] = 1;
			tab_aux[(rede.conexoes_rede[i].segundo)-1][(rede.conexoes_rede[i].primeiro)-1] = 2;
			router_count[(rede.conexoes_rede[i].primeiro)-1]++;
			router_count[(rede.conexoes_rede[i].segundo)-1]++;
		}else if((router_count[(rede.conexoes_rede[i].primeiro)-1] == 2) && (router_count[(rede.conexoes_rede[i].segundo)-1] == 0)){
			tab_aux[(rede.conexoes_rede[i].primeiro)-1][(rede.conexoes_rede[i].segundo)-1] = 2;
			tab_aux[(rede.conexoes_rede[i].segundo)-1][(rede.conexoes_rede[i].primeiro)-1] = 0;
			router_count[(rede.conexoes_rede[i].primeiro)-1]++;
			router_count[(rede.conexoes_rede[i].segundo)-1]++;
		}else if((router_count[(rede.conexoes_rede[i].primeiro)-1] == 2) && (router_count[(rede.conexoes_rede[i].segundo)-1] == 1)){
			tab_aux[(rede.conexoes_rede[i].primeiro)-1][(rede.conexoes_rede[i].segundo)-1] = 2;
			tab_aux[(rede.conexoes_rede[i].segundo)-1][(rede.conexoes_rede[i].primeiro)-1] = 1;
			router_count[(rede.conexoes_rede[i].primeiro)-1]++;
			router_count[(rede.conexoes_rede[i].segundo)-1]++;
		}else if((router_count[(rede.conexoes_rede[i].primeiro)-1] == 2) && (router_count[(rede.conexoes_rede[i].segundo)-1] == 2)){
			tab_aux[(rede.conexoes_rede[i].primeiro)-1][(rede.conexoes_rede[i].segundo)-1] = 2;
			tab_aux[(rede.conexoes_rede[i].segundo)-1][(rede.conexoes_rede[i].primeiro)-1] = 2;
			router_count[(rede.conexoes_rede[i].primeiro)-1]++;
			router_count[(rede.conexoes_rede[i].segundo)-1]++;
		}
	}

			
	//Tabelas de roteamento
	for(int i = 0; i < router_num; i++){	
		for(int j = 0; j < coreNumbers; j++){
			rede.table[i].push_back({j, tab_aux[i][caminho[i][j]], dist[i][j]});
		}
	}


	//Execução da simulação
	sc_start(trafego[0].deadline, SC_NS);

	zera_latencia = sc_time_stamp();

	//Calculo dos pacotes que chegaram ao destino
	for(int i = 0; i < trafego.size(); i++){
		total_packets = total_packets + trafego[i].pacotes;
	}

	for(int i = 0; i < coreNumbers; i++){
		deadline_parcial = deadline_parcial + rede.rt[i]-> count;
	}
	
	for(int i = 0; i < coreNumbers; i++){
		latencia_parcial = latencia_parcial + rede.rt[i]->latencia_rt;
	}

	string simulacao = "_saida_simulacao.txt";

	deadline = (deadline_parcial * 100) / total_packets;
	latencia_media = ((latencia_parcial) - (zera_latencia * 4 * router_num) / total_packets);

	if(deadline > 100){
		deadline = 100;
	}

	for(int w = 0; w < router_num; w++){
		rede.rt[w]->count = 0;
	}

	deadline_parcial = 0;
	latencia_parcial = conste;

	saidaDados.open(simulacao);
	saidaDados << deadline << endl;
	saidaDados << latencia_media;
	
	saidaDados.close();
			
	string conex = "conexoes.txt";

	saidaDados.open(conex);

	for(int i = 0; i < 10; i++){
		saidaDados << mapeamento[i].primeiro << " " << mapeamento[i].segundo << endl;
	}

	saidaDados.close();

	return 0;

}
