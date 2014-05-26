
#include "TreeMaker.h"

using namespace std;

//---------------------------------------------------//
// Constructor
//---------------------------------------------------//
TreeMaker::TreeMaker(string outname, string inname) :
  m_outfile(NULL),
  m_tree(NULL),
  m_fRead(NULL)
{
  
  // Open up a file reader object
  m_fRead = new FileReader(inname);

  // Create a track tree
  m_event = new Event();

  // Open output root file
  m_outfile = new TFile(outname.c_str(),"recreate");

  // Create TTree object and assign this
  // trkTree to that tree
  m_tree = new TTree("trkTree","trkTree");
  m_tree->SetAutoSave(1000000);
  m_tree->SetMaxTreeSize(3000000000u);
  m_tree->Branch("event", &m_event,32000,1);
  
}

//---------------------------------------------------//
// Destructor
//---------------------------------------------------//
TreeMaker::~TreeMaker()
{

  m_outfile->Write("",TObject::kOverwrite);
  m_outfile->Close();
  delete m_outfile;
  delete m_event;
  delete m_fRead;

}

//---------------------------------------------------//
// Loop over events
//---------------------------------------------------//
void TreeMaker::loop(int nEvent)
{
  
  vector<Particle*> particles;

  // nEvent = the number of events to process. It is
  // the users job to make sure there are enough
  // events in the input file!
  for(int evt=0; evt<nEvent; ++evt){

    // Some print out so user doesn't get bored
    if(evt % 100000 == 0) 
      cout<<"Processing Event "<<evt<<endl;


    m_event->clear();                 // Make sure event empty
    m_fRead->setParticles(particles); // load particles
    m_event->addParticles(particles); // put them in the tree
    fill();                           // fill this event
  }

  // Clean up left over particles from last event
  for(unsigned int i=0; i<particles.size(); ++i)
    delete particles.at(i);
  particles.clear();

}

//---------------------------------------------------//
//                   HELP MENU                       //
//---------------------------------------------------//
void help()
{
  
  cout<<endl;
  cout<<"***************************************************"<<endl;
  cout<<"Options: "<<endl;
  cout<<"\t-n <int>"<<endl;
  cout<<"\t\tSpecify number of events to put in tree"<<endl;
  cout<<"\t-i <filepath>"<<endl;
  cout<<"\t\tSpecify input file path to G4 data"<<endl;
  cout<<"\t-o <outname>"<<endl;
  cout<<"\t\tSpecify the output file name"<<endl;
  cout<<"***************************************************"<<endl;
  cout<<endl;
}

//---------------------------------------------------//
//                     MAIN                          //
//---------------------------------------------------//
int main(int argc, char** argv)
{


  // TODO: Add options
  int nEvent = 0;
  //int nEvent = 1e6;
  string outname = "eBeam_40MeV_1000000_ice";
  //string inname  = "../../IceBlock/tracks/output_1000000000_40_ice_eBeam_np1.dat";
  string inname  = "../../IceBlock/tracks/output_1000000_40_ice_eBeam_np1.dat";

  //
  // Options
  //
  for(int i=1; i<argc; ++i){
    if(strcmp(argv[i],"-n") == 0)
      nEvent = atoi(argv[++i]);
    else if(strcmp(argv[i],"-o") == 0)
      outname = argv[++i];
    else if(strcmp(argv[i],"-i") == 0)
      inname = argv[++i];
    else{
      help();
      return 0;
    }
  }// end loop over options

  // redirect outname to trees directory
  outname = "../trees/" + outname + ".root";

  // Create TreeMaker Object
  TreeMaker* maker = new TreeMaker(outname,inname);

  // Now loop
  maker->loop(nEvent);

  // Delete object, we're done
  delete maker;

  // return 
  return 0.;
}
