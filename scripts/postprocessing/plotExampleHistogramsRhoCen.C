void plotExampleHistogramsRhoCen() {

    thesis();

    TFile meJets("ME/0_5/ME_jets_0_5.root");
    TFile seJets("SE/0_5/SE_jets_0_5.root");

//    TFile meJets("ME/40_50/ME_jets_40_50.root");
//    TFile seJets("SE/40_50/SE_jets_40_50.root");
    for(Int_t r = 2; r < 7; r++) {
        if(r==3 || r ==5) continue;
        TH1D* meHistJets = (TH1D*)meJets.Get(Form("fHistRho__R%i", r));
        TH1D* seHistJets = (TH1D*)seJets.Get(Form("fHistRho__R%i", r));

        TH1D* meHistCent = (TH1D*)meJets.Get(Form("fHistCentrality__R%i", r));
        Int_t meEvents = meHistCent->GetEntries();

        TH1D* seHistCent = (TH1D*)seJets.Get(Form("fHistCentrality__R%i", r));
        Int_t seEvents = seHistCent->GetEntries();

        cout << "seEvents" << seEvents << endl;
        cout << "meEvents" << meEvents << endl;

        meHistJets->SetLineWidth(4);
        seHistJets->SetLineWidth(4);

        /*
           double meNorm = meHistJets->Integral(1,33,"width");
           cout << meNorm << endl;

           double seNorm = seHistJets->Integral(1,33,"width");
           cout << seNorm << endl;

           double scale = meNorm / seNorm;
           cout << " scale " << scale << endl;
           */
        meHistJets->SetTitle("ME #rho");
        meHistJets->SetLineColor(kRed);
        meHistJets->SetMarkerColor(kRed);
        cout << " > Mixed events (GeV/c) < " << endl;
        cout << "   RMS  = " << meHistJets->GetRMS() << endl;
        cout << "   Mean = " << meHistJets->GetMean() << endl;
        cout << " > Same events (GeV/c) < " << endl;
        cout << "   RMS  = " << seHistJets->GetRMS() << endl;
        cout << "   Mean = " << seHistJets->GetMean() << endl;


        meHistJets->GetYaxis()->SetTitle("'prob' (#frac{1}{N_{evt}})"); 
        seHistJets->GetYaxis()->SetTitle("'prob' (#frac{1}{N_{evt}})"); 

        meHistJets->GetXaxis()->SetTitle("#rho (GeV/#it{c})"); 
        seHistJets->GetXaxis()->SetTitle("#rho (GeV/#it{c})"); 

        seHistJets->SetTitle("SE #rho");

        seHistJets->Scale(1./double(seEvents), "width");
        meHistJets->Scale(1./double(meEvents), "width");


        TCanvas *c = new TCanvas(Form("illustration_R%i", r), Form("illustration_R%i", r), 800, 400);
        c->Divide(2);
        c->cd(1);

        meHistJets->DrawCopy();
        seHistJets->DrawCopy("same");


        c->cd(2);
        seHistJets->Divide(meHistJets);
        seHistJets->GetYaxis()->SetTitle("ratio (same events to mixed events)");
        seHistJets->DrawCopy();
        TF1* line = new TF1("line", "pol0", -30, 150);
        line->SetParameter(0, 1);
        line->DrawCopy("same");

        /*
           TFile fMQA("mixingQA.root");
           TH1D* unmixedPt = (TH1D*)fMQA.Get("fHistAcceptedMultiplicity");
           TH1D* mixedPt = (TH1D*)fMQA.Get("fHistMixedMultiplicity");

           unmixedPt->Divide(mixedPt);
           TCanvas *c2 = new TCanvas("QA", "QA", 400,400);
           unmixedPt->DrawCopy();
           */
    }
}
