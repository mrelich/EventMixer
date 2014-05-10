
#include "FileReader.h"

using namespace std;

//------------------------------------------//
// Constructor
//------------------------------------------//
FileReader::FileReader(string filename)
{

  // Open file
  m_input.open(filename.c_str(), ifstream::in);

}

//------------------------------------------//
// Destructor
//------------------------------------------//
FileReader::~FileReader()
{

  // Close file
  m_input.close();

}

//------------------------------------------//
// Set Particles
//------------------------------------------//
void FileReader::setParticles(vector<Particle*> &parts)
{

  // Delete old particles
  for(uint i=0; i<parts.size(); ++i)
    delete parts.at(i);
  parts.clear();

  // Set the kill switches
  string event = "Event:";
  string end   = "End:";

  // Variables to be read in
  // [0,1,2]  == xi, yi, zi
  // [3,4]    == E, Etot
  // [5,6,7]  == xf, yf, zf
  // [8,9,10] == trkID, momID, pdg
  const int nPars = 11;
  float vars[nPars];
  
  // Loop over and load input
  int prevPos = 0;
  while( !m_input.eof() ){
    
    // Specify some generic char vector
    char buf[512];

    // Get the line and save previous position
    prevPos = m_input.tellg();
    m_input.getline(buf, 512);

    // Now parse the buffer
    const char* tokens[nPars] = {};
    tokens[0] = strtok(buf, " ");

    if( event.compare(tokens[0]) == 0 ) continue;
    if( end.compare(tokens[0]) == 0)    break;

    // Now save the variables
    vars[0] = atof(tokens[0]);
    for(int i=1; i<nPars; ++i){
      vars[i] = atof(strtok(0," "));
    }

    // Skip photons
    if( ((int) vars[10]) == 22 ) continue;

    // Now construct the particle
    Particle* p = new Particle(vars[0],     // xi
			       vars[1],     // yi
			       vars[2],     // zi
			       vars[5],     // xf
			       vars[6],     // yf
			       vars[7],     // af
			       vars[4],     // Etot
			       vars[8],     // trkID
			       vars[10]);   // pdg
    parts.push_back(p);

  }// end while loop

}

//------------------------------------------//
// Main
//------------------------------------------//
int main()
{

  // This is a test function in order to see if
  // the file reader is working properly
  string fname = "../../IceBlock/tracks/output_1000000000_40_ice_eBeam_np1.dat";

  // Create FileReader Object
  FileReader* fRead = new FileReader(fname);

  // Now loop and load some particles
  vector<Particle*> particles;
  int nEvt = 2;
  for(int i=0; i<nEvt; ++i){
    fRead->setParticles(particles);
    cout<<"Loaded: "<<particles.size()<<endl;
    for(uint j=0; j<particles.size(); ++j)
      particles.at(j)->print();
  }

  // CLean up left over particles
  for(uint j=0; j<particles.size(); ++j)
    delete particles.at(j);
  particles.clear();
  
  // Delete
  delete fRead;
  
  return 0;


}
