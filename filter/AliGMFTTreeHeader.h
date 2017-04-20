#ifndef AliGMFTTreeEVENT_H
#define AliGMFTTreeEVENT_H

#include <TObject.h>

class AliGMFTTreeHeader : public TObject{

 public:

  AliGMFTTreeHeader();
  
  // manipulators - persistent
  void  SetRun(Int_t run)       {fRun   = run;}
  void  SetV0M(Float_t V0M)     {fV0M   = V0M;}
  void  SetTRK(Float_t TRK)     {fTRK   = TRK;}
  void  SetZvtx(Float_t Zvtx)   {fZvtx  = Zvtx;}

  Int_t         GetRun() const  {return fRun;}
  Float_t       GetV0M() const  {return fV0M;}
  Float_t       GetTRK() const  {return fTRK;}
  Float_t       GetZvtx() const {return fZvtx;}

  // manipulators - no persistent
  void SetEventID(Int_t id)     {fEventID = id;}
  void SetUsed(Bool_t used)     {fUsed = used;}

  Int_t         GetEventID() const      {return fEventID;}
  Bool_t        GetUsed() const         {return fUsed;}


 private:
  Int_t     fRun;        // run number
  Float_t   fV0M;        // centrality V0
  Float_t   fTRK;        // centrality TRK
  Float_t   fZvtx;       // rec vertex

  // transient members for bookkeeping
  Int_t    fEventID;    //! event identifier
  Bool_t   fUsed;       //! was event read from file

  virtual ~AliGMFTTreeHeader(); // default destructor

  ClassDef(AliGMFTTreeHeader, 1);    // Help class
};

#endif
	
