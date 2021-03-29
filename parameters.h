#include <vector>
#include <queue>

using namespace std;

#define NORTH 0
#define EAST 1
#define SOUTH 2
#define WEST 3
#define LOCAL 4
#define LOCAL2 5

#define FREE 0
#define SENDING 1
#define WAITING 1

#define ERROR 5

#define BEGIN_PACKET 1
#define INSTRUCTION 2
#define END_PACKET 3
#define SIZE_FLIT_PACKET 5

struct trafegoRede {
	int origem;
	int destino;
	int pacotes;
	int deadline;
};

typedef vector <trafegoRede> trafego_rede; 

struct Conexoes{
	int primeiro;
	int segundo;
};

typedef vector <Conexoes> conexoes;
