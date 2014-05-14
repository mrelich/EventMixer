
#include "Mixer.h"

using namespace std;

//------------------------------------------------//
// Constructor
//------------------------------------------------//
Mixer::Mixer(float Eprimary, float Edesired,
	     int nToBeMixed, 
	     int totEvents, int finalEvents,
	     string inname) :
  m_output(NULL),
  m_fRead(NULL),
  m_rand(NULL),
  m_tobemixed(nToBeMixed),
  m_totEvents(totEvents),
  m_finalEvents(finalEvents),
  m_scale(0.),
  m_nbins(40),
  m_xmin(0.),
  m_xmax(20.),
  m_X0(38.9)
{

  // Build output file name
  stringstream ss;
  ss << getenv("PWD");
  ss << "/../output/mixedShower_Eprim" 
     << Eprimary
     << "_ToBeMixed" << m_tobemixed
     << "_nEvents" << finalEvents
     << ".root";
  
  // Open root file
  m_output = new TFile(ss.str().c_str(),"recreate");

  // Build file reader
  m_fRead  = new FileReader(inname);

  // Create the random object
  m_rand   = new TRandom3();

  // Set the scale factor to use for each event.
  // scale = (Edesired) / (Eprimary * nToBeMixed)
  //m_scale = Edesired/(Eprimary * nToBeMixed);
  m_scale = 1; 

  // Print some beginning info
  cout<<endl;
  cout<<"************************************************"<<endl;
  cout<<" Eprimary     = "<<Eprimary<<endl;
  cout<<" Edesired     = "<<Edesired<<endl;
  cout<<" nToBeMixed   = "<<nToBeMixed<<endl;
  cout<<" totEvents    = "<<totEvents<<endl;
  cout<<" nFinalEvents = "<<finalEvents<<endl;
  cout<<"************************************************"<<endl;
  cout<<endl;

}

//------------------------------------------------//
// Destructor
//------------------------------------------------//
Mixer::~Mixer()
{

  // Close output file
  m_output->Write();
  m_output->Close();
  delete m_output;

  // Delete objects
  delete m_fRead;
  delete m_rand;

  // Loop over and kill any remaining particles
  for(uint i=0; i<m_parts.size(); ++i)
    delete m_parts.at(i);
  m_parts.clear();

}

//------------------------------------------------//
// Generate events
//------------------------------------------------//
void Mixer::generateEvents()
{
  
  // Make sure root directory is in root file
  m_output->cd();

  // Name for output histogram
  stringstream pname;

  // Loop over the number of events to be generated
  for(int iEvt=0; iEvt<m_finalEvents; ++iEvt){

    // Specify output name
    pname.str("");
    pname << "h_evt" << iEvt;

    // Make histogram
    TH1D* h_evt = new TH1D(pname.str().c_str(),"",
			   m_nbins, m_xmin, m_xmax);
    
    // Now loop over total times to reuse
    for(int iMix=0; iMix<m_tobemixed; ++iMix){
      int rndEvent = getEventNum();
      TH1D* h_temp = generateEvent(rndEvent);
      h_evt->Add( h_temp );
      delete h_temp;
    }// end loop over mixed events

    // Write histogram
    h_evt->Write();
    delete h_evt;

  }// end loop over tot events to be generated

}

//------------------------------------------------//
// Generate a single event
//------------------------------------------------//
TH1D* Mixer::generateEvent(int evtNum)
{

  // Load the particles for a given event
  m_fRead->setRandom(evtNum);
  m_fRead->setParticles(m_parts);
  
  // Create temporary histogram
  TH1D* h_temp = new TH1D("h_temp","",m_nbins,m_xmin,m_xmax);
  
  // Loop over particles
  //cout<<"Number of Particles: "<<m_parts.size()<<" Event: "<<evtNum<<endl;
  for(uint i=0; i<m_parts.size(); ++i){
    Particle* p = m_parts.at(i);
  
    // TODO: Make the bin width variable
    // this should be easy to do!!
    //cout<<"\tStart: "<<p->ZI()<<" last: "<<p->ZF()<<endl;
    int lowbin  = (int) (p->ZI()/0.5);
    int highbin = (int) (p->ZF()/0.5);
    
    // If in same bin, do nothing
    if(lowbin == highbin) continue;
    p->print();
    // Loop from low to high
    for(int bin=lowbin; bin<highbin; ++bin)
      h_temp->Fill(bin*0.5, m_scale);
    
  }// end loop over particles
  
  return h_temp;

}

//------------------------------------------------//
// Get a random event number
//------------------------------------------------//
int Mixer::getEventNum()
{
  
  return (int) (m_rand->Rndm() * (m_totEvents-1));
  
}
