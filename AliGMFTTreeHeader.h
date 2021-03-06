#ifndef COMPRESSION_LEVEL
#define COMPRESSION_LEVEL 1
#endif

#ifndef AliGMFTTreeHeader_H
#define AliGMFTTreeHeader_H

#include <TObject.h>

class AliGMFTTreeHeader : public TObject{

 public:

  AliGMFTTreeHeader();
  void  Fill(AliGMFTTreeHeader* event);
  
  // manipulators - persistent
  void  SetZvtx(Float_t Zvtx)           {fZvtx  = Zvtx;}
  void  SetEventPlane(Float_t ep)       {fEventPlane = ep;}
  void  SetEventPlane3(Float_t ep)      {fEventPlane3 = ep;}
  void  SetRunNumber(ULong_t rn)        {fRunNumber = rn;}

  // manipulators - no persistent
  void SetEventID(Int_t id)             {fEventID = id;}
  void SetUsed(Bool_t used)             {fUsed = used;}
  void SetMultiplicity(Short_t m)       {fMultiplicity = m;}
  void SetCentrality(Double_t c)        {fCentrality = c;}


  // getters
  Float_t       GetZvtx() const         {return fZvtx;}
  Float_t       GetEventPlane() const   {return fEventPlane;}
  Float_t       GetEventPlane3() const  {return fEventPlane3;}

  Int_t         GetEventID() const      {return fEventID;}
  Bool_t        GetUsed() const         {return fUsed;}
  Short_t       GetMultiplicity() const {return fMultiplicity;}
  Float_t       GetCentrality() const   {return fCentrality;}
  ULong_t       GetRunNumber() const    {return fRunNumber;}

  void          Reset();
 private:
  // first the persistent members are listed. these are written to disk
  // so extra care is taken to minimize the space they take
#if COMPRESSION_LEVEL > 1
  // maximum compression, some loss of precision may occur
  Double32_t    fZvtx;          //[-10,10,8] rec vertex
  Double32_t    fEventPlane;    //[-1.6, 1.6,8] event plane orientation
  Double32_t    fEventPlane3;   //[-1.05, 1.05,8] event plane 3 orientation
  Double32_t    fCentrality;    //[0,100,8] collision centrality
#elif COMPRESSION_LEVEL > 0
  //medium compression, no precision loss expected
  Double32_t    fZvtx;          //[-10,10,12] rec vertex
  Double32_t    fEventPlane;    //[-1.6,1.6,12] event plane orientation
  Double32_t    fEventPlane3;   //[-1.05, 1.05,12] event plane 3 orientation
  Double32_t    fCentrality;    //[0,100,12] collision centrality
#else  
  // no compression
  Float_t       fZvtx;          // rec vertex
  Float_t       fEventPlane;    // event plane orientation
  Float_t       fEventPlane3;   // event plane 3 orientation
  Float_t       fCentrality;    // collision centrality
#endif

  // non-transient non compressable numbers
  ULong_t       fRunNumber;     // run number
  // transient members are not written to disk, they
  // can be optimized for speed
  Int_t         fEventID;       //! event identifier
  Bool_t        fUsed;          //! was event read from file
  Short_t       fMultiplicity;  //! event multiplicity

  virtual ~AliGMFTTreeHeader(); // default destructor

  ClassDef(AliGMFTTreeHeader, 3);    // Help class
};

#endif	
