// root includes
#include "TClonesArray.h"

// custom includes
#include "AliGMFEventContainer.h"
#include "../filter/AliGMFTTreeHeader.h"
#include "../filter/AliGMFTTreeTrack.h"

ClassImp(AliGMFEventContainer)

//------------------------------------------------------------------------
AliGMFEventContainer::AliGMFEventContainer( 
        AliGMFTTreeHeader* event,
        TClonesArray* array) : TObject()
{

    // link the event
    fHeader = event;
    fTracks = array;
}
//------------------------------------------------------------------------
