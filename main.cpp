#include <iostream>
#include <fstream>
#include <signal.h>
#include <cstdlib>

#include <map>

//network
#include "network_module.h"
#include "createXml.h"

using namespace rapidxml;
using namespace std;

SOCKET sock;

bool isRec = false;
bool sendInfo = false;

void connect_signals();
void launch_mic();
void stop_mic_on_signal(int);
void change_mic_state(int);

void connect_signals()
{
    signal ( 30, change_mic_state );
}

void change_mic_state(int signal)
{
  if ( isRec ) // if we already record
  {
    isRec = false;
    cout << "isRec : " << isRec << " stop mic "<< endl;
    stop_mic_on_signal(signal); // we cease the recording and launch the computing and scenarios
    sendInfo = true;
  }
  else // if we havent been recording, we launch the mic
  {
    isRec = true;
    cout << "isRec : " << isRec << " launch mic " << endl;
    launch_mic(); // we record while we receive a stop signal
  }
}

void launch_mic()
{
    // Send sound
    cout << "Recording launched" << endl;
    system("rec -r 16000 -b 16 -c 1 record.wav");
	// when we killall rec, we set isRec to false to continue the processing of the voice
}

void stop_mic_on_signal(int signal)
{
    // Stop rec
    cout << "Recording ended" << endl;
    system("killall rec");
}


int main(int argc, char **argv)
{
  
  isRec = false;
  sendInfo = false;

	if(argc < 3)
	{
		printf("Usage : %s [address] [name] [port]\n", argv[0]);
		return EXIT_FAILURE;
 	}
	//first send the application name
	sock = init_connection_module(argv[1],atoi(argv[3]));
	
	//use of a descriptor in order to use non-blocking sockets
	if(fcntl(sock, F_SETFL, O_NONBLOCK) < 0)
		printf("Error setting socket in non blocking mode\n");
	else
		printf("Socket is in non blocking mode\n");

	// send the Applcation's name
	write_server(sock, argv[2]);
	
	// hello packet
	write_server(sock, createInitGestureXml().c_str());

 	connect_signals();

  while (1)
  {
    sleep(1);
    if (!isRec)
    {
      // Convert sound to flac
      system("sox record.wav record.flac gain -n -5 silence 1 5 2%");
      isRec = false;
    
      if ( sendInfo )
      {
				// Call Google server and get file of trad
				system("curl -H \"Content-Type: audio/x-flac; rate=16000\" \"https://www.google.com/speech-api/v1/recognize?xjerr=1&client=chromium&lang=fr-FR&maxresults=1\" -F myfile=\"@record.flac\" -k -o \"result.txt\"");

				cout << "delete record" ;
				system("rm record.flac");
				cout << " done" << endl;
				
				
				ifstream infile("result.txt");

				cout << infile.rdbuf() << endl;


				infile.seekg(0, ios::end);
				size_t size = infile.tellg();
				string bufferdan(size, ' ');

				infile.seekg(0);
				infile.read(&bufferdan[0], size);
				cout << bufferdan << endl;

				bufferdan = "";

				infile.seekg(82);
				infile.read(&bufferdan[0], size);
				cout << bufferdan << endl;

				string command = "";
				int i = 0;

				do
				{
						command = command + bufferdan[i];
						i++;
				} while ( bufferdan[i] != '"' );

				cout << command << endl;


						char buffer2[500];
						string xml = "" ;
						string s;
						s="2";

				if ( command == "action 1" )
				{

						xml = acreateGestureXml(s, s, "2", s, "1");
						cout << xml << endl;
						strcpy(buffer2, xml.c_str());
						cout << buffer2 << endl;
						write_server(sock,buffer2);
				}

				if ( command == "action 2" )
				{
						// Send 2 with XML Socket
						xml = acreateGestureXml(s, s, "2", s, "2");
						strcpy(buffer2, xml.c_str());
						write_server(sock,buffer2);
				}

				if ( command == "action 3" )
				{
						// Send 3 with XML Socket
						xml = acreateGestureXml(s, s, "2", s, "3");
						strcpy(buffer2, xml.c_str());
						write_server(sock,buffer2);
				}

				if ( command == "action 4" )
				{
						// Send 4 with XML Socket
						xml = acreateGestureXml(s, s, "2", s, "4");
						strcpy(buffer2, xml.c_str());
						write_server(sock,buffer2);
				}
				buffer2[0] = '\0';
				bufferdan = "";
				infile.close();
				sendInfo = false;
      }
	  
    }
     
  }
  end_connection_module(sock); 
  return 0;
}
