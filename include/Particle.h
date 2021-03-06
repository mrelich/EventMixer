#ifndef Particle_h
#define Particle_h

//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-//
// Basic particle class to store some information that //
// makes the code cleaner.                             //
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-//

#include "TObject.h"
#include <iostream>

class Particle : public TObject
{
  
 public:
  
  // Constructor
  Particle(){};
  Particle(float xi, float yi, float zi, float ti,
	   float xf, float yf, float zf, float tf,
	   float E, int trkID, int pdg){
    // Set Variables                                                                                
    m_xi    = xi;
    m_yi    = yi;
    m_zi    = zi;
    m_ti    = ti;
    m_xf    = xf;
    m_yf    = yf;
    m_zf    = zf;
    m_tf    = tf;
    m_E     = E;
    m_trkID = trkID;
    m_pdg   = pdg;
  };
  
  // Destructor
  virtual ~Particle(){};

  // Clear method
  void clear(){
    m_xi    = 0;
    m_yi    = 0;
    m_zi    = 0;
    m_ti    = 0;
    m_xf    = 0;
    m_yf    = 0;
    m_zf    = 0;
    m_tf    = 0;
    m_E     = 0;
    m_trkID = 0;
    m_pdg   = 0;
  };

  // Print properties
  void print(){
    std::cout<<"--------------"<<std::endl;
    std::cout<<"(xi,yi,zi,ti) = ("<<m_xi<<","<<m_yi<<","<<m_zi<<","<<m_ti<<")"<<std::endl;
    std::cout<<"(xf,yf,zf,tf) = ("<<m_xf<<","<<m_yf<<","<<m_zf<<","<<m_tf<<")"<<std::endl;
    std::cout<<"E          =  "<<m_E<<std::endl;
    std::cout<<"trkID      =  "<<m_trkID<<std::endl;
    std::cout<<"pdg        =  "<<m_pdg<<std::endl;
  }

  // Accessor methods
  float XI()   { return m_xi;    };
  float YI()   { return m_yi;    };
  float ZI()   { return m_zi;    };
  float TI()   { return m_ti;    };
  float XF()   { return m_xf;    };
  float YF()   { return m_yf;    };
  float ZF()   { return m_zf;    };
  float TF()   { return m_tf;    };
  float E()    { return m_E;     };
  float trkID(){ return m_trkID; };
  float pdg()  { return m_pdg;   };

  ClassDef(Particle, 2);

 private:

  float m_xi;           // initial x position
  float m_yi;           // initial y position
  float m_zi;           // initial z position
  float m_ti;           // initial time
  float m_xf;           // final x position
  float m_yf;           // final y position
  float m_zf;           // final z position
  float m_tf;           // final time

  float m_E;            // total energy of particle
  float m_trkID;        // ID for the track
  float m_pdg;          // particles PDG

};

#endif
