
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=//
// This will be the 'main' in order to mix the  //
// events using the functions defined inside of //
// Mixer class.                                 //
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=//

#include "Mixer.h"

using namespace std;

//----------------------------------//
// Main
//----------------------------------//
int main()
{

  // TODO: Add arguments
  float Eprimary    = 40.;      // Primary energy in MeV
  float Edesired    = 40.*1e9;  // Desired energy in MeV
  int   nToBeMixed  = 1;      // Number of events to mix per event
  //int   totEvents   = 1e6;      // Number of generated showers
  int   totEvents   = 1;      // Number of generated showers
  int   finalEvents = 1;        // Number of final events
  string inname     = "";       // Input file path

  // Set input file
  inname = "../../IceBlock/tracks/output_1000000000_40_ice_eBeam_np1.dat";
  
  // Make mixer
  Mixer* mixer = new Mixer(Eprimary,Edesired,nToBeMixed,
			   totEvents,finalEvents,inname);

  // Execute and generate events
  mixer->generateEvents();

  // Delete
  delete mixer;

  return 0;

}
