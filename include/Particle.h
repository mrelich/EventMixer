#ifndef Particle_h
#define Particle_h

//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-//
// Basic particle class to store some information that //
// makes the code cleaner.                             //
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-//

#include <iostream>

class Particle
{
  
 public:
  
  // Constructor
  Particle(float xi, float yi, float zi,
	   float xf, float yf, float zf,
	   float E, int trkID, int pdg);
  
  // Destructor
  virtual ~Particle(){};

  // Clear method
  void clear();

  // Print properties
  void print();

  // Accessor methods
  float XI()   { return m_xi;    };
  float YI()   { return m_yi;    };
  float ZI()   { return m_zi;    };
  float XF()   { return m_xf;    };
  float YF()   { return m_yf;    };
  float ZF()   { return m_zf;    };
  float E()    { return m_E;     };
  float trkID(){ return m_trkID; };
  float pdg()  { return m_pdg;   };

 private:

  float m_xi;           // initial x position
  float m_yi;           // initial y position
  float m_zi;           // initial z position
  float m_xf;           // final x position
  float m_yf;           // final y position
  float m_zf;           // final z position

  float m_E;            // total energy of particle
  float m_trkID;        // ID for the track
  float m_pdg;          // particles PDG

};

#endif
