#ifndef AliGMFMixingManager_H
#define AliGMFMixingManager_H

#include <TObject.h>

#include "AliGMFEventContainer.h"

class TTree;
class AliGMFTTreeHeader;
class AliGMFTTreeTrack;
class TClonesArray;
class TFile;
class TArrayI;
class AliGMFEventReader;
class AliGMFEventContainer;

class AliGMFMixingManager : public TObject {


 public:
    AliGMFMixingManager();

    // core functions
    Bool_t      Initialize();
    Int_t       DoPerChunkMixing();

    // setters
    void SetMultiplicityRange(Int_t min, Int_t max) {
        fMultiplicityMin = min;
        fMultiplicityMax = max;
    }
    void SetVertexrange(Float_t min, Float_t max) {
        fVertexMin = min;
        fVertexMax = max;
                }
    void SetEventPlaneRange(Float_t min, Float_t max) {
        fEventPlaneMin = min;
        fEventPlaneMax = max;
    }
    void SetEventReader(AliGMFEventReader* r)   {fEventReader = r;}

 private:

    Bool_t      IsSelected(AliGMFEventContainer* event);
    void        InitializeMixingCache();
    Bool_t      FillMixingCache();
    void        FlushMixingCache();
    void        StageCachedEvent(Int_t i);
    AliGMFTTreeTrack*   GetNextCachedTrackFromEvent();


    Int_t       fMultiplicityMin;   // minimum multiplicity
    Int_t       fMultipicityMax;    // maximum multiplicity
    Float_t     fVertexMin;         // minimum vertexz
    Float_t     fVertexMax;         // maximum vertexz
    Float_t     fEventPlaneMin;     // minimum event plane angle
    Float_t     fEventPlaneMax;     // maximum event plane angle


    // data structures for mixed event output
    TTree*                      fTree;                  //! output data
    AliGMFTTreeHeader           fEvent;                 //! event header
    AliGMFEventContainer*       fBufferedEvent;         //! buffered real event 
    TClonesArray*               fTrackArray;            //! track container
    TFile*                      fOutputFile;            //! output file

    TArrayI*                    fEventCache;            //! event cache
    TArrayI*                    fTrackCache;            //! track cache

    // misc
    AliGMFEventReader*          fEventReader;           // event reader
    Int_t                       fGlobalBufferPosition;  //! global buffer position

    ClassDef(AliGMFMixingManager, 1);

};

#endif
