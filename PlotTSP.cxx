// 'PlotTSP.cxx'
// Derek Anderson
// 07.08.2015
//
// This macro takes the output from ReadQAA.cxx and plots the TSP after 
// various cuts. (And is to be run in ROOT.)
//
// Last Updated: 08.01.2015

#include "TH1.h"
#include "TFile.h"
#include "TNtuple.h"


void PlotTSP() {

   // Open output file
   TFile *f = new TFile("/data/smgroup/sm0/DerekAnderson/GammaJet/Output/PlotTSP4.root", "update");


   // Grab the tuples [ {a / A} denotes Associated Level, {b / B} denotes Trigger Level ]
   TNtuple *aTuple = (TNtuple*) f->Get("aTuple");
   TNtuple *bTuple = (TNtuple*) f->Get("bTuple");

   // Associated and Trigger leaf names [ET = transverse cluster energy]
   float gID, gPT, nTowTrak, adc11, ET, Mpn, TSP;

   // Get Associated leaves
   TLeaf *l_gIDa   = aTuple->GetLeaf("gID");
   TLeaf *l_gPTa   = aTuple->GetLeaf("gPT");
   TLeaf *l_nTTa   = aTuple->GetLeaf("nTowTrak");
   TLeaf *l_adc11a = aTuple->GetLeaf("adc11");
   TLeaf *l_ETa    = aTuple->GetLeaf("ET");
   TLeaf *l_MpnA   = aTuple->GetLeaf("Mpn");
   TLeaf *l_TSPa   = aTuple->GetLeaf("TSP"); 
   // Get Trigger leaves
   TLeaf *l_gIDb   = bTuple->GetLeaf("gID");
   TLeaf *l_gPTb   = bTuple->GetLeaf("gPT");
   TLeaf *l_nTTb   = bTuple->GetLeaf("nTowTrak");
   TLeaf *l_adc11b = bTuple->GetLeaf("adc11");
   TLeaf *l_ETb    = bTuple->GetLeaf("ET");
   TLeaf *l_MpnB   = bTuple->GetLeaf("Mpn");
   TLeaf *l_TSPb   = bTuple->GetLeaf("TSP");

   // Set Associated addresses
   l_gIDa   -> SetAddress(&gID);
   l_gPTa   -> SetAddress(&gPT);
   l_nTTa   -> SetAddress(&nTowTrak);
   l_adc11a -> SetAddress(&adc11);
   l_ETa    -> SetAddress(&ET);
   l_MpnA   -> SetAddress(&Mpn);
   l_TSPa   -> SetAddress(&TSP);
   // Set Triiger addresses
   l_gIDb   -> SetAddress(&gID);
   l_gPTb   -> SetAddress(&gPT);
   l_nTTb   -> SetAddress(&nTowTrak);
   l_adc11b -> SetAddress(&adc11);
   l_ETb    -> SetAddress(&ET);
   l_MpnB   -> SetAddress(&Mpn);
   l_TSPb   -> SetAddress(&TSP);


   // Associated histograms
   TH1F *hAP  = new TH1F("hAP", "TSP -- Pure Photon Sample [Assc.]", 100, 0., 1.);
   TH1F *hAPe = new TH1F("hAPe", "TSP -- Pure Photon Sample, eT > 16 [Assc.]", 100, 0., 1.);
   TH1F *hAPl = new TH1F("hAPl", "TSP -- Pure Sample, Low Mult. [Assc.]", 100, 0., 1.);
   TH1F *hAPh = new TH1F("hAPh", "TSP -- Pure Sample, High Mult. [Assc.]", 100, 0., 1.);
   TH1F *hAD  = new TH1F("hAD", "TSP -- Dirty Photon Sample [Assc.]", 100, 0., 1.);
   TH1F *hADe = new TH1F("hADe", "TSP -- Dirty Photon Sample, eT > 16 [Assc.]", 100, 0., 1.);
   TH1F *hADl = new TH1F("hADl", "TSP -- Dirty Sample, Low Mult. [Assc.]", 100, 0., 1.);
   TH1F *hADh = new TH1F("hADh", "TSP -- Dirty Sample, High Mult. [Assc.]", 100, 0., 1.);
   // Trigger histograms
   TH1F *hBP  = new TH1F("hBP", "TSP -- Pure Photon Sample [Trig.]", 100, 0., 1.);
   TH1F *hBPe = new TH1F("hBPe", "TSP -- Pure Photon Sample, eT > 16 [Trig.]", 100, 0., 1.);
   TH1F *hBPl = new TH1F("hBPl", "TSP -- Pure Sample, Low Mult. [Trig.]", 100, 0., 1.);
   TH1F *hBPh = new TH1F("hBPh", "TSP -- Pure Sample, High Mult. [Trig.]", 100, 0., 1.);
   TH1F *hBD  = new TH1F("hBD", "TSP -- Dirty Photon Sample [Trig.]", 100, 0., 1.);
   TH1F *hBDe = new TH1F("hBDe", "TSP -- Dirty Photon Sample, eT > 16 [Trig.]", 100, 0., 1.);
   TH1F *hBDl = new TH1F("hBDl", "TSP -- Dirty Sample, Low Mult. [Trig.]", 100, 0., 1.);
   TH1F *hBDh = new TH1F("hBDh", "TSP -- Dirty Sample, High Mult. [Trig.]", 100, 0., 1.);

   // Fill Associated histograms
   int N = aTuple->GetEntries();
   for (int a = 0; a < N; ++a) {

      aTuple->GetEntry(a);

      if (gID == 1 && gPT < 20 && nTowTrak == 1 && adc11 < 6003 && TSP < 1) {
         hAP  -> Fill(TSP);
         if (ET > 16)   hAPe->Fill(TSP);
         if (Mpn < 200) hAPl->Fill(TSP);
         if (Mpn > 200) hAPh->Fill(TSP);
      }

      if (nTowTrak > 1 && TSP < 1) {
         hAD->Fill(TSP);
         if (ET > 16)   hADe->Fill(TSP);
         if (Mpn < 200) hADl->Fill(TSP);
         if (Mpn > 200) hADh->Fill(TSP);
      }

   }

   // Fill Trigger histograms
   N = bTuple->GetEntries();
   for (int b = 0; b < N; ++b) {

      bTuple->GetEntry(b);

      if (gID == 1 && gPT < 20 && nTowTrak == 1 && adc11 < 6003 && TSP < 1) {
         hBP->Fill(TSP);
         if (ET > 16)   hBPe->Fill(TSP);
         if (Mpn < 200) hBPl->Fill(TSP);
         if (Mpn > 200) hBPh->Fill(TSP);
      }

      if (nTowTrak > 1 && TSP < 1) {
         hBD->Fill(TSP);
         if (ET > 16)   hBDe->Fill(TSP);
         if (Mpn < 200) hBDl->Fill(TSP);
         if (Mpn > 200) hBDh->Fill(TSP);
      }

   }


   // Scale Associated histograms
   double scale;
   scale = hAP  -> GetEntries();
      hAP  -> Scale(1. / scale);
   scale = hAPe -> GetEntries();
      hAPe -> Scale(1. / scale);
   scale = hAPl -> GetEntries();
      hAPl -> Scale(1. / scale); 
   scale = hAPh -> GetEntries();
      hAPh -> Scale(1. / scale);
   scale = hAD  -> GetEntries();
      hAD  -> Scale(1. / scale);
   scale = hADe -> GetEntries();
      hADe -> Scale(1. / scale);
   scale = hADl -> GetEntries();
      hADl -> Scale(1. / scale);
   scale = hADh -> GetEntries();
      hADh -> Scale(1. / scale);
   // Scale Trigger histograms
   scale = hBP  -> GetEntries();
      hBP  -> Scale(1. / scale);
   scale = hBPe -> GetEntries();
      hBPe -> Scale(1. / scale);
   scale = hBPl -> GetEntries();
      hBPl -> Scale(1. / scale); 
   scale = hBPh -> GetEntries();
      hBPh -> Scale(1. / scale);
   scale = hBD  -> GetEntries();
      hBD  -> Scale(1. / scale);
   scale = hBDe -> GetEntries();
      hBDe -> Scale(1. / scale);
   scale = hBDl -> GetEntries();
      hBDl -> Scale(1. / scale);
   scale = hBDh -> GetEntries();
      hBDh -> Scale(1. / scale);

   // Set Pure histograms' line colors
   hAP  -> SetLineColor(kBlue);
   hAPe -> SetLineColor(kViolet);
   hAPl -> SetLineColor(kBlue + 2);
   hAPh -> SetLineColor(kViolet + 10);
   hBP  -> SetLineColor(kBlue);
   hBPe -> SetLineColor(kViolet);
   hBPl -> SetLineColor(kBlue + 2);
   hBPh -> SetLineColor(kViolet + 10);
   // Set Dirty histograms' line colors
   hAD  -> SetLineColor(kRed);
   hADe -> SetLineColor(kOrange);
   hADl -> SetLineColor(kRed + 2);
   hADh -> SetLineColor(kOrange + 10);
   hBD  -> SetLineColor(kRed);
   hBDe -> SetLineColor(kOrange);
   hBDl -> SetLineColor(kRed + 2);
   hBDh -> SetLineColor(kOrange + 10);


   // Write Associated histograms
   hAP  -> Write();
   hAPe -> Write();
   hAPl -> Write();
   hAPh -> Write();
   hAD  -> Write();
   hADe -> Write();
   hADl -> Write();
   hADh -> Write();
   // Write Trigger histograms
   hBP  -> Write();
   hBPe -> Write();
   hBPl -> Write();
   hBPh -> Write();
   hBD  -> Write();
   hBDe -> Write();
   hBDl -> Write();
   hBDh -> Write();

   // All done!
   f->Close();

}

// End ------------------------------------------------------------------------
