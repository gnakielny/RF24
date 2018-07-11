#include <cstdlib>
#include <iostream>
#include <sstream>
#include <string>
#include <unistd.h>
#include <RF24/RF24.h>

using namespace std;

RF24 radio(22,0);

const uint8_t pipes[][6] = {"Dupa1","Dupa2"};

int main(int argc, char** argv)
{
	//konfiguracja transmisji xD
	radio.begin();
	radio.setChannel(0x6B);
  	radio.setDataRate(RF24_250KBPS);
	radio.setAutoAck(false);
	radio.setRetries(15,15);
	radio.setCRCLength(RF24_CRC_8);
  	radio.openWritingPipe(pipes[0]);
	//rury
	//radio.openReadingPipe(1,pipes[1]);
	//wykonuj argumenty po kolei
	unsigned int proby = 50;
	for(int i = 1; i < argc ; i++)
	{
		cout << endl << argv[i] << endl;
		unsigned short funkcja = strtol(argv[i],NULL,10);
		for(unsigned int j = 1; j <= proby; j++)
		{
//			bool ok = 
			radio.write( &funkcja, sizeof(unsigned short));
/*			if(ok)
			{
        			printf("%d proba  ok\n",j);
        		}
        		if (!ok)
			{
        			printf("%d proba  failed\n",j);
			}
*/
			usleep(1);
		}
		if (argc>2 && i<argc-1)
			usleep(500000);
	}
	return 0;
}
