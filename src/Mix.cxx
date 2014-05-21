
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=//
// This will be the 'main' in order to mix the  //
// events using the functions defined inside of //
// Mixer class.                                 //
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=//

#include "Mixer.h"

using namespace std;

//----------------------------------//
// Help
//----------------------------------//
void help()
{

  // Block
  cout<<endl;
  cout<<"--------------------------";
  cout<<"--------------------"<<endl;

  // Options
  cout<<"-e <float> : Primary E"<<endl;
  cout<<"-p <int>   : Scale factor"<<endl;
  cout<<"-nm <int>  : N Showers to mix"<<endl;
  cout<<"-t <int>   : Total available events"<<endl;
  cout<<"-f <int>   : Final Number events"<<endl;
  cout<<"-i <f.root>: Input root file"<<endl;

  // Block
  cout<<"--------------------------";
  cout<<"--------------------"<<endl;
  cout<<endl;

}

//----------------------------------//
// Main
//----------------------------------//
int main(int argc, char** argv)
{

  // Options
  float Eprimary      = 40.;      // Primary energy in MeV
  int   nPartPerEvent = 1;        // Scale factor per event
  int   nToBeMixed    = 100;      // Number of events to mix per event
  int   totEvents     = 1e6;      // Number of generated showers
  int   finalEvents   = 100;      // Number of final events
  string inname       = "";       // Input file path

  // Loop over inputs
  for(int i=1; i<argc; ++i){
    if(strcmp("-e",argv[i])==0)
      Eprimary = atof(argv[++i]);
    else if(strcmp("-p",argv[i])==0)
      nPartPerEvent = (int) atof(argv[++i]);
    else if(strcmp("-nm",argv[i])==0)
      nToBeMixed = (int) atof(argv[++i]);
    else if(strcmp("-t",argv[i])==0)
      totEvents = (int) atof(argv[++i]);
    else if(strcmp("-f",argv[i])==0)
      finalEvents = atoi(argv[++i]);
    else if(strcmp("-i",argv[i])==0)
      inname = argv[++i];
    else{
      help();
      return 0;
    }
  }// end loop over input args

  // Make mixer
  Mixer* mixer = new Mixer(Eprimary,nPartPerEvent,nToBeMixed,
			   totEvents,finalEvents,inname);

  // Execute and generate events
  mixer->generateEvents();

  // Delete
  delete mixer;

  return 0;

}
