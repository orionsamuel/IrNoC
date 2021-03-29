#include "systemc.h"

using namespace std;

SC_MODULE(arbiter){
	sc_in<bool> clk;
	sc_signal<sc_int<32> > rd[5];
	sc_int<32> priority;
	sc_int<32> bufferCircular[5];
	sc_int<32> pointer;

	//Verifica em qual buffer se encontra a prioridade no momento
	void checkPriority(){			
		if(this->pointer < 5){
			this->pointer++;
		}else{
			this->pointer = 1;
		}
		if ((bufferCircular[0] == 1)  && (this->pointer == 0)){
			priority = 0;
			rd[0].write(1);
		}
		if ((bufferCircular[1] == 1)  && (this->pointer == 1)){
			priority = 1;
			rd[1].write(1);
		}
		if ((bufferCircular[2] == 1)  && (this->pointer == 2)){
			priority = 2;
			rd[2].write(1);
		}
		if ((bufferCircular[3] == 1)  && (this->pointer == 3)){
			priority = 3;
			rd[3].write(1);
		}
		if ((bufferCircular[4] == 1)  && (this->pointer == 4)){
			priority = 4;
			rd[4].write(1);
		}
		//cout << this->pointer << endl;
	}


	SC_CTOR(arbiter){
		pointer = 0;
		SC_METHOD(checkPriority);
		sensitive << clk.pos();
	}
};
