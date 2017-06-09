// simple jet finder on generic input vector
//
// Redmer Alexander Bertens, 2017 (UTK, CERN)

#include "fastjet/Selector.hh"
//#include "fastjet/tools/JetMedianBackgroundEstimator.hh"
#include "fastjet/PseudoJet.hh"
#include "fastjet/ClusterSequence.hh"
#include "fastjet/ClusterSequenceArea.hh"
#include "fastjet/ClusterSequenceAreaBase.hh"


#include <iostream>
#include <vector>

#include "TH1F.h"
#include "TFile.h"
#include "TMath.h"

#include "reader/AliGMFEventContainer.h"
#include "filter/AliGMFTTreeTrack.h"
#include "jetfinder/AliGMFDummyJetFinder.h"
#include "tools/AliGMFHistogramManager.h"

ClassImp(AliGMFDummyJetFinder)

using namespace std;

//_____________________________________________________________________________
AliGMFDummyJetFinder::AliGMFDummyJetFinder() : TObject(),
    fDoBackgroundSubtraction(kFALSE),
    fJetResolution(.3),
    fLeadingHadronPt(.1),
    fHistogramManager(0x0)
{
    // default constructor
}
    
//_____________________________________________________________________________
Bool_t AliGMFDummyJetFinder::Initialize() {
    // initialize
   fHistogramManager = new AliGMFHistogramManager();
   
   // create the histograms (for now here)
   fHistogramManager->BookTH1F("fHistJetPt", "p_{T}^{jet}", 100, 0, 100);
   fHistogramManager->BookTH2F("fHistJetPtArea", "p_{T}^{jet}", "area", 100, 0, 100, 100, 0, 1);
   fHistogramManager->BookTH2F("fHistJetEtaPhi", "#eta^{jet}", "#phi^{jet}", 100, -1, 1, 100, 0, TMath::TwoPi());

   return kTRUE;

}
//_____________________________________________________________________________

Bool_t AliGMFDummyJetFinder::AnalyzeEvent(AliGMFEventContainer* event) {
    // called for each event
    
    // define the fastjet input vector and create a pointer to a track
    std::vector <fastjet::PseudoJet> fjInputVector;
    AliGMFTTreeTrack* track(0x0);
    Double_t totalE;

    for(Int_t i(0); i < event->GetNumberOfTracks(); i++) {
        track = event->GetTrack(i);
        if(track) {
            totalE = track->GetPt()*TMath::CosH(track->GetEta());
            if (totalE <= 0) continue;
            totalE = totalE*totalE + .14*.14;   // assume pion mass for each track
            fastjet::PseudoJet fjInputProtoJet(
                    track->GetPt()*TMath::Cos(track->GetPhi()), 
                    track->GetPt()*TMath::Sin(track->GetPhi()), 
                    track->GetPt()*TMath::SinH(track->GetEta()), 
                    TMath::Sqrt(totalE));
            fjInputProtoJet.set_user_index(i);
            fjInputVector.push_back(fjInputProtoJet);
        }
    }

    // setup the jet finder
    fastjet::GhostedAreaSpec     ghostSpec(.9, 1, 0.001);
    fastjet::Strategy            strategy = fastjet::Best;
    fastjet::RecombinationScheme recombScheme = fastjet::BIpt_scheme;
    fastjet::AreaType            areaType = fastjet::active_area;
    fastjet::AreaDefinition      areaDef = fastjet::AreaDefinition(areaType, ghostSpec);

    // some bookkeeping
    fastjet::RangeDefinition range(fJetResolution-.9, .9-fJetResolution, 0, 2.*fastjet::pi);
    fastjet::JetDefinition jetDef(fastjet::antikt_algorithm, fJetResolution, recombScheme, strategy);

    // feed the protojets to fastjet
    fastjet::ClusterSequenceArea clusterSeq(fjInputVector, jetDef, areaDef);

    // get the jets
    std::vector <fastjet::PseudoJet> inclusiveJets = clusterSeq.inclusive_jets();

    for (UInt_t iJet = 0; iJet < inclusiveJets.size(); iJet++) {
        if (!range.is_in_range(inclusiveJets[iJet])) continue;
        // loop over constituents to apply leading hadron cut
        std::vector<fastjet::PseudoJet> constituents = clusterSeq.constituents(inclusiveJets[iJet]);
        Double_t maxpt(0);
        for(UInt_t i(0); i < constituents.size(); i++) {
            if(constituents[i].perp() > maxpt) maxpt = constituents[i].perp();
        }
        if(maxpt < fLeadingHadronPt) continue;

        fHistogramManager->Fill(
                "fHistJetPt", 
                inclusiveJets[iJet].perp()
                );
        fHistogramManager->Fill(
                "fHistJetPtArea", 
                inclusiveJets[iJet].perp(),
                inclusiveJets[iJet].area()
                );
        fHistogramManager->Fill(
                "fHistJetEtaPhi",
                inclusiveJets[iJet].eta(),
                inclusiveJets[iJet].phi()
                );
    }

    return kTRUE;
}
//_____________________________________________________________________________

Bool_t AliGMFDummyJetFinder::Finalize() {

    fHistogramManager->StoreManager("jetFinderOutput.root");
    return kTRUE;

}