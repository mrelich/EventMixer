
#include "Particle.h"

using namespace std;

//----------------------------------------------------//
// Constructor
//----------------------------------------------------//
Particle::Particle(float xi, float yi, float zi,
		   float xf, float yf, float zf,
		   float E, int trkID, int pdg)
{

  // Set Variables
  m_xi    = xi;
  m_yi    = yi;
  m_zi    = zi;
  m_xf    = xf;
  m_yf    = yf;
  m_zf    = zf;
  m_E     = E;
  m_trkID = trkID;
  m_pdg   = pdg;

}

//----------------------------------------------------//
// Clear variables
//----------------------------------------------------//
void Particle::clear()
{

  m_xi    = 0;
  m_yi    = 0;
  m_zi    = 0;
  m_xf    = 0;
  m_yf    = 0;
  m_zf    = 0;
  m_E     = 0;
  m_trkID = 0;
  m_pdg   = 0;

}

//----------------------------------------------------//
// Print particle information
//----------------------------------------------------//
void Particle::print()
{

  cout<<"--------------"<<endl;
  cout<<"(xi,yi,zi) = ("<<m_xi<<","<<m_yi<<","<<m_zi<<")"<<endl;
  cout<<"(xf,yf,zf) = ("<<m_xf<<","<<m_yf<<","<<m_zf<<")"<<endl;
  cout<<"E          =  "<<m_E<<endl;
  cout<<"trkID      =  "<<m_trkID<<endl;
  cout<<"pdg        =  "<<m_pdg<<endl;
  
}
