// 'ReadQAA.cxx'
// Derek Anderson
// 06.25.2015
//
// This macro collects information and calculates the TSP and Charge Multiplicity from data, and is to
// be run with ROOT. A stripped down, "prototype" version can be found in the 'Embedding_ntuples_pi0'
// directory as 'ReadQAA_st_gamma_2011.C'.
//
// Last Updated: 08.03.2015
//
// Courtesy of:
//    Nihar Sahoo, ca. 2014

#include "TFile.h"
#include "TNtuple.h"


void ReadQAA() {

   TFile *myFile = new TFile("/data/smgroup/sm0/DerekAnderson/GammaJet/Output/PlotTSP4.root", "recreate");

   // new tuples [ {-, a, A} denotes associated level; {b, B} denotes trigger level ]
   aTuple = new TNtuple("aTuple", "Photon Info [associated]", "gID:gPT:nTowTrak:adc11:theta:eTot:ETot:ET:Mref:Mpn:TSP:Dphi:pTtpc");
   bTuple = new TNtuple("bTuple", "Photon Info [trigger]", "gID:gPT:nTowTrak:adc11:theta:eTot:ETot:ET:Mref:Mpn:TSP");

   // loop over files
   char FileName[500];
   char PathName[500];
   char num[500];
   for (int f = 0; f <= 49; ++f) {

      // get file name and open it
      sprintf(num, "%d", f);
      strcpy(PathName, "/data/smgroup/sm0/DerekAnderson/GammaJet/Embedding_ntuples_pi0/");
      strcpy(FileName, "pi0_");
      strcat(FileName, num);
      strcat(FileName, ".root");
      strcat(PathName, FileName);
      TFile *urFile = new TFile(PathName);

      // grab their tuples
      TNtuple *Pi       = (TNtuple*) urFile->Get("Pi");
      TNtuple *PiB      = (TNtuple*) urFile->Get("PiB");
      TNtuple *CA       = (TNtuple*) urFile->Get("CA");
      TNtuple *CAB      = (TNtuple*) urFile->Get("CAB");
      TNtuple *Pho      = (TNtuple*) urFile->Get("Pho");
      TNtuple *PhoB     = (TNtuple*) urFile->Get("PhoB");
      TNtuple *QAA      = (TNtuple*) urFile->Get("QAA");
      TNtuple *QAAB     = (TNtuple*) urFile->Get("QAAB");
      TNtuple *Four     = (TNtuple*) urFile->Get("Four");
      TNtuple *Track    = (TNtuple*) urFile->Get("Track");
      TNtuple *TrackS   = (TNtuple*) urFile->Get("TrackS");
      TNtuple *SMDE1    = (TNtuple*) urFile->Get("SMDE1");
      TNtuple *SMDE1B   = (TNtuple*) urFile->Get("SMDE1B");
      TNtuple *AngleTA  = (TNtuple*) urFile->Get("AngleTA");
      TNtuple *AngleTAB = (TNtuple*) urFile->Get("AngleTAB");


      // Pi, PiB leaf names
      float en9, en10, en11;
      float enp03, enp02, enp01, enp9, enp10, enp11;
      // CA, CAB leaf names
      float adc11, dphi1;
      // Pho, leaf names
      float dphif, THeta;
      // QAA, QAAB leaf names
      float geantID, geantPT, etav1, phiv1, nTowerTracks;
      float EneT0, eneT0;
      float en4, enp4;
      // Four leaf names
      float MNeg, MPos;
      // Track names
      float EtaTr;
      // TrackS names
      float ptTPC, RefM;
      // SMDE1, SMDE1B names
      float en03, en0, en1, en2, en3, en5, en6, en7, en8;
      float enp2, enp3, enp5, enp6;
      // AngleTA, AngleTAB names
      float en02, en01;
      float enp0, enp1, enp7, enp8;

      // get Pi leaves
      TLeaf *l_en9a   = Pi->GetLeaf("en9");
      TLeaf *l_en10a  = Pi->GetLeaf("en10");
      TLeaf *l_en11a  = Pi->GetLeaf("en11");
      TLeaf *l_enp03a = Pi->GetLeaf("enp03");
      TLeaf *l_enp02a = Pi->GetLeaf("enp02");
      TLeaf *l_enp01a = Pi->GetLeaf("enp01");
      TLeaf *l_enp9a  = Pi->GetLeaf("enp9");
      TLeaf *l_enp10a = Pi->GetLeaf("enp10");
      TLeaf *l_enp11a = Pi->GetLeaf("enp11");
      // get PiB leaves
      TLeaf *l_en9b   = PiB->GetLeaf("en9");
      TLeaf *l_en10b  = PiB->GetLeaf("en10");
      TLeaf *l_en11b  = PiB->GetLeaf("en11");
      TLeaf *l_enp03b = PiB->GetLeaf("enp03");
      TLeaf *l_enp02b = PiB->GetLeaf("enp02");
      TLeaf *l_enp01b = PiB->GetLeaf("enp01");
      TLeaf *l_enp9b  = PiB->GetLeaf("enp9");
      TLeaf *l_enp10b = PiB->GetLeaf("enp10");
      TLeaf *l_enp11b = PiB->GetLeaf("enp11");
      // get CA leaves
      TLeaf *l_adc11a = CA->GetLeaf("adc11");
      TLeaf *l_dphi1a = CA->GetLeaf("dphi1");
      // get CAB leaves
      TLeaf *l_adc11b = CAB->GetLeaf("adc11");
      TLeaf *l_dphi1b = CAB->GetLeaf("dphi1");
      // get Pho leaves
      TLeaf *l_dphifa = Pho->GetLeaf("dphif");
      TLeaf *l_THetaa = Pho->GetLeaf("THeta");
      // get PhoB leaves
      TLeaf *l_THetab = PhoB->GetLeaf("THeta");
      // get QAA leaves
      TLeaf *l_gIDa   = QAA->GetLeaf("geantID");
      TLeaf *l_gPTa   = QAA->GetLeaf("geantPT");
      TLeaf *l_etaV1a = QAA->GetLeaf("etav1");
      TLeaf *l_phiV1a = QAA->GetLeaf("phiv1");
      TLeaf *l_nTTa   = QAA->GetLeaf("nTowerTracks");
      TLeaf *l_Etota  = QAA->GetLeaf("EneT0");
      TLeaf *l_etota  = QAA->GetLeaf("eneT0");
      TLeaf *l_en4a   = QAA->GetLeaf("en4");
      TLeaf *l_enp4a  = QAA->GetLeaf("enp4");
      // get QAAB leaves
      TLeaf *l_gIDb   = QAAB->GetLeaf("geantID");
      TLeaf *l_gPTb   = QAAB->GetLeaf("geantPT");
      TLeaf *l_etaV1b = QAAB->GetLeaf("etav1");
      TLeaf *l_phiV1b = QAAB->GetLeaf("phiv1");
      TLeaf *l_nTTb   = QAAB->GetLeaf("nTowerTracks");
      TLeaf *l_Etotb  = QAAB->GetLeaf("EneT0");
      TLeaf *l_etotb  = QAAB->GetLeaf("eneT0");
      TLeaf *l_en4b   = QAAB->GetLeaf("en4");
      TLeaf *l_enp4b  = QAAB->GetLeaf("enp4");
      // get Four leaves
      TLeaf *l_Mn     = Four->GetLeaf("MNeg");
      TLeaf *l_Mp     = Four->GetLeaf("MPos");
      // get Track leaves
      TLeaf *l_EtaTr  = Track->GetLeaf("EtaTr");
      // get TrackS leaves
      TLeaf *l_pTtpc  = TrackS->GetLeaf("ptTPC");
      TLeaf *l_Mr     = TrackS->GetLeaf("RefM");
      // get SMDE1 leaves
      TLeaf *l_en03a  = SMDE1->GetLeaf("en03");
      TLeaf *l_en0a   = SMDE1->GetLeaf("en0");
      TLeaf *l_en1a   = SMDE1->GetLeaf("en1");
      TLeaf *l_en2a   = SMDE1->GetLeaf("en2");
      TLeaf *l_en3a   = SMDE1->GetLeaf("en3");
      TLeaf *l_en5a   = SMDE1->GetLeaf("en5");
      TLeaf *l_en6a   = SMDE1->GetLeaf("en6");
      TLeaf *l_en7a   = SMDE1->GetLeaf("en7");
      TLeaf *l_en8a   = SMDE1->GetLeaf("en8");
      TLeaf *l_enp2a  = SMDE1->GetLeaf("enp2");
      TLeaf *l_enp3a  = SMDE1->GetLeaf("enp3");
      TLeaf *l_enp5a  = SMDE1->GetLeaf("enp5");
      TLeaf *l_enp6a  = SMDE1->GetLeaf("enp6");
      // get SMDE1B leaves
      TLeaf *l_en03b  = SMDE1B->GetLeaf("en03");
      TLeaf *l_en0b   = SMDE1B->GetLeaf("en0");
      TLeaf *l_en1b   = SMDE1B->GetLeaf("en1");
      TLeaf *l_en2b   = SMDE1B->GetLeaf("en2");
      TLeaf *l_en3b   = SMDE1B->GetLeaf("en3");
      TLeaf *l_en5b   = SMDE1B->GetLeaf("en5");
      TLeaf *l_en6b   = SMDE1B->GetLeaf("en6");
      TLeaf *l_en7b   = SMDE1B->GetLeaf("en7");
      TLeaf *l_en8b   = SMDE1B->GetLeaf("en8");
      TLeaf *l_enp2b  = SMDE1B->GetLeaf("enp2");
      TLeaf *l_enp3b  = SMDE1B->GetLeaf("enp3");
      TLeaf *l_enp5b  = SMDE1B->GetLeaf("enp5");
      TLeaf *l_enp6b  = SMDE1B->GetLeaf("enp6");
      // get AngleTA leaves
      TLeaf *l_en02a  = AngleTA->GetLeaf("en02");
      TLeaf *l_en01a  = AngleTA->GetLeaf("en01");
      TLeaf *l_enp0a  = AngleTA->GetLeaf("enp0");
      TLeaf *l_enp1a  = AngleTA->GetLeaf("enp1");
      TLeaf *l_enp7a  = AngleTA->GetLeaf("enp7");
      TLeaf *l_enp8a  = AngleTA->GetLeaf("enp8");
      // get AngleTAB leaves
      TLeaf *l_en02b  = AngleTAB->GetLeaf("en02");
      TLeaf *l_en01b  = AngleTAB->GetLeaf("en01");
      TLeaf *l_enp0b  = AngleTAB->GetLeaf("enp0");
      TLeaf *l_enp1b  = AngleTAB->GetLeaf("enp1");
      TLeaf *l_enp7b  = AngleTAB->GetLeaf("enp7");
      TLeaf *l_enp8b  = AngleTAB->GetLeaf("enp8");

      // set Pi addresses
      l_en9a   -> SetAddress(&en9);
      l_en10a  -> SetAddress(&en10);
      l_en11a  -> SetAddress(&en11);
      l_enp03a -> SetAddress(&enp03);
      l_enp02a -> SetAddress(&enp02);
      l_enp01a -> SetAddress(&enp01);
      l_enp9a  -> SetAddress(&enp9);
      l_enp10a -> SetAddress(&enp10);
      l_enp11a -> SetAddress(&enp11);
      // set PiB addresses
      l_en9b   -> SetAddress(&en9);
      l_en10b  -> SetAddress(&en10);
      l_en11b  -> SetAddress(&en11);
      l_enp03b -> SetAddress(&enp03);
      l_enp02b -> SetAddress(&enp02);
      l_enp01b -> SetAddress(&enp01);
      l_enp9b  -> SetAddress(&enp9);
      l_enp10b -> SetAddress(&enp10);
      l_enp11b -> SetAddress(&enp11);
      // set CA addresses
      l_adc11a -> SetAddress(&adc11);
      l_dphi1a -> SetAddress(&dphi1);
      // set CAB addresses
      l_adc11b -> SetAddress(&adc11);
      l_dphi1b -> SetAddress(&dphi1);
      // set Pho addresses
      l_dphifa -> SetAddress(&dphif);
      l_THetaa -> SetAddress(&THeta);
      // set PhoB addresses
      l_THetab -> SetAddress(&THeta);
      // set QAA addresses
      l_gIDa   -> SetAddress(&geantID);
      l_gPTa   -> SetAddress(&geantPT);
      l_etaV1a -> SetAddress(&etav1);
      l_phiV1a -> SetAddress(&phiv1);
      l_nTTa   -> SetAddress(&nTowerTracks);
      l_Etota  -> SetAddress(&EneT0);
      l_etota  -> SetAddress(&eneT0);
      l_en4a   -> SetAddress(&en4);
      l_enp4a  -> SetAddress(&enp4);
      // set QAAB addresses
      l_gIDb   -> SetAddress(&geantID);
      l_gPTb   -> SetAddress(&geantPT);
      l_etaV1b -> SetAddress(&etav1);
      l_phiV1b -> SetAddress(&phiv1);
      l_nTTb   -> SetAddress(&nTowerTracks);
      l_Etotb  -> SetAddress(&EneT0);
      l_etotb  -> SetAddress(&eneT0);
      l_en4b   -> SetAddress(&en4);
      l_enp4b  -> SetAddress(&enp4);
      // set Four addresses
      l_Mn     -> SetAddress(&MNeg);
      l_Mp     -> SetAddress(&MPos);
      // set Track addresses
      l_EtaTr  -> SetAddress(&EtaTr);
      // set TrackS addresses
      l_pTtpc  -> SetAddress(&ptTPC);
      l_Mr     -> SetAddress(&RefM);
      // set SMDE1 addresses
      l_en03a  -> SetAddress(&en03);
      l_en0a   -> SetAddress(&en0);
      l_en1a   -> SetAddress(&en1);
      l_en2a   -> SetAddress(&en2);
      l_en3a   -> SetAddress(&en3);
      l_en5a   -> SetAddress(&en5);
      l_en6a   -> SetAddress(&en6);
      l_en7a   -> SetAddress(&en7);
      l_en8a   -> SetAddress(&en8);
      l_enp2a  -> SetAddress(&enp2);
      l_enp3a  -> SetAddress(&enp3);
      l_enp5a  -> SetAddress(&enp5);
      l_enp6a  -> SetAddress(&enp6);
      // set SMDE1B addresses
      l_en03b  -> SetAddress(&en03);
      l_en0b   -> SetAddress(&en0);
      l_en1b   -> SetAddress(&en1);
      l_en2b   -> SetAddress(&en2);
      l_en3b   -> SetAddress(&en3);
      l_en5b   -> SetAddress(&en5);
      l_en6b   -> SetAddress(&en6);
      l_en7b   -> SetAddress(&en7);
      l_en8b   -> SetAddress(&en8);
      l_enp2b  -> SetAddress(&enp2);
      l_enp3b  -> SetAddress(&enp3);
      l_enp5b  -> SetAddress(&enp5);
      l_enp6b  -> SetAddress(&enp6);
      // set AngleTA addresses
      l_en02a  -> SetAddress(&en02);
      l_en01a  -> SetAddress(&en01);
      l_enp0a  -> SetAddress(&enp0);
      l_enp1a  -> SetAddress(&enp1);
      l_enp7a  -> SetAddress(&enp7);
      l_enp8a  -> SetAddress(&enp8);
      // set AngleTAB addresses
      l_en02b  -> SetAddress(&en02);
      l_en01b  -> SetAddress(&en01);
      l_enp0b  -> SetAddress(&enp0);
      l_enp1b  -> SetAddress(&enp1);
      l_enp7b  -> SetAddress(&enp7);
      l_enp8b  -> SetAddress(&enp8);


      // Associated-Level Loop
      cout << FileName << ": Associated Level, " << endl;
 
      // calculate ET [perp. component of EneT0], Mpn, and TSP, and fill aTuple
      float ET  = 0;
      float Mpn = 0;
      float TSP = 0;
      int Ntry  = (int) QAA->GetEntries();
      for (int a = 0; a < Ntry; ++a) {

         Pi      -> GetEntry(a);
         CA      -> GetEntry(a);
         Pho     -> GetEntry(a);
         QAA     -> GetEntry(a);
         Four    -> GetEntry(a);
         Track   -> GetEntry(a);
         TrackS  -> GetEntry(a);
         SMDE1   -> GetEntry(a);
         AngleTA -> GetEntry(a);

         if ( (eneT0 > 8 && eneT0 < 20) && (abs(etav1) < 0.9 && abs(EtaTr) < 1) ) {

            // TSP numerator and denominator
            float TSPn = eneT0;
            float TSPd = (en4 + enp4) * 0.783 + (en3 + enp3 + en5 + enp5) * 2.21 + (en2 + enp2 + en6 + enp6) * 6.26
                         + (en1 + enp1 + en7 + enp7) * 11.51 + (en0 + enp0 + en8 + enp8) * 17.73 + (en01 + enp01 + en9 + enp9) * 24.78
                         + (en02 + enp02 + en10 + enp10) * 32.57 + (en03 + enp03 + en11 + enp11) * 41.05;
            if (TSPd == 0) continue;

            Mpn = MPos + MNeg;
            ET  = EneT0 * sin(THeta);
            TSP = TSPn / TSPd;

            aTuple->Fill(geantID, geantPT, nTowerTracks, adc11, THeta, eneT0, EneT0, ET, RefM, Mpn, TSP, dphif, ptTPC);

         }

         if (a % 50000 == 0) cout << " counting " << a << endl;

      }

      // Trigger-Level Loop
      cout << FileName << ": Trigger Level, " << endl;

      // calculate ET, Mpn, and TSP, and fill bTuple
      ET  = 0;
      Mpn = 0;
      TSP = 0;  
      Ntry = (int) QAAB->GetEntries();
      for (int b = 0; b < Ntry; ++b) {

         PiB      -> GetEntry(b);
         CAB      -> GetEntry(b);
         PhoB     -> GetEntry(b);
         QAAB     -> GetEntry(b);
         Four     -> GetEntry(b);
         Track    -> GetEntry(b);
         TrackS   -> GetEntry(b);
         SMDE1B   -> GetEntry(b);
         AngleTAB -> GetEntry(b);

         if ( (eneT0 > 8 && eneT0 < 20) && (abs(etav1) < 0.9 && abs(EtaTr) < 1) ) {

            float TSPn = eneT0;
            float TSPd = (en4 + enp4) * 0.783 + (en3 + enp3 + en5 + enp5) * 2.21 + (en2 + enp2 + en6 + enp6) * 6.26
                         + (en1 + enp1 + en7 + enp7) * 11.51 + (en0 + enp0 + en8 + enp8) * 17.73 + (en01 + enp01 + en9 + enp9) * 24.78
                         + (en02 + enp02 + en10 + enp10) * 32.57 + (en03 + enp03 + en11 + enp11) * 41.05;
            if (TSPd == 0) continue;

            Mpn = MPos + MNeg;
            ET  = EneT0 * sin(THeta);
            TSP = TSPn / TSPd;

            bTuple->Fill(geantID, geantPT, nTowerTracks, adc11, THeta, eneT0, EneT0, ET, RefM, Mpn, TSP);

         }

         if (b % 5000 == 0) cout << " counting " << b << endl;

      }

      cout << "\n";

   }   // end of File-Loop


   myFile -> cd();
   aTuple -> Write();
   bTuple -> Write();
   myFile -> Close();

}

// End ------------------------------------------------------------------------

