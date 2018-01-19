
void fitCorrelations()
{

  //  TString inputfile = "/home/smgroup/ahamed/Run_Normalization/" + cuts + "/Make_Histo_" + system + "_combtrig.root";
  TString inputfile = "DeltaPhi_hists_pttpc3_NOTSPgamma.root";
  cout << inputfile.Data() << endl;
  TFile *file0 = new TFile(inputfile.Data());
  TString outputfile = "fitCorrelations_ET_bins_pttpc3_NOTSPgamma.root";
  

  double max, ped;

  TH1 *hg[12];
  TH1 *hp[12];

  for (int i=0; i<12; i++)
    {
     
      TString gammahis = "gamma_";
      gammahis += i;
      TString pi0his = "pi0_";
      pi0his += i;

      file0->GetObject(gammahis.Data(),hg[i]);
      max = hg[i]->GetMaximum();
      int pedlo = hg[i]->FindBin(0.8);
      int pedhi = hg[i]->FindBin(2.0);
      ped = hg[i]->Integral(pedlo,pedhi)/(pedhi-pedlo+1);
      TF1 *f1 = new TF1("f1","gaus(0)+gaus(3)+pol0(6)",-1.55.,4.70);
      cout << "max = " << max << ", ped = " << ped << " " << pedlo << " " << pedhi << endl; 
      
      f1->SetParameters(max,0.,0.02,max,3.14,0.035,ped);
      f1->SetParLimits(0,0.,max);
      f1->SetParLimits(1,-0.1,0.1);
      f1->SetParLimits(2,0.,0.6);
      f1->SetParLimits(3,0.,max);
      f1->SetParLimits(4,3.,3.25);
      f1->SetParLimits(5,0.,0.6);
      f1->SetParLimits(6,0.2*ped,10*ped);
      hg[i]->Fit(f1,"RBM");
      
      file0->GetObject(pi0his.Data(),hp[i]);
      max = hp[i]->GetMaximum();
      ped = hp[i]->Integral(pedlo,pedhi)/(pedhi-pedlo+1);
      TF1 *f1 = new TF1("f1","gaus(0)+gaus(3)+pol0(6)",-1.55.,4.70);
      cout << "max = " << max << ", ped = " << ped << endl; 

      f1->SetParameters(max,0.,0.02,max,3.14,0.035,ped);
      f1->SetParLimits(0,0.,max);
      f1->SetParLimits(1,-0.1,0.1);
      f1->SetParLimits(2,0.,0.6);
      f1->SetParLimits(3,0.,max);
      f1->SetParLimits(4,3.,3.25);
      f1->SetParLimits(5,0.,0.6);
      f1->SetParLimits(6,0.2*ped,10*ped);
      hp[i]->Fit(f1,"RBM");
      
    }
     
  //  TString outputfile = cuts + "/fitCorrelations_" + system + "_combtrig.root";
 TFile *fileout = new TFile(outputfile.Data(),"RECREATE");
 for (int i=0; i<12; i++)
   {
     hg[i]->Write();
     hp[i]->Write();
   }
 fileout->Close();
 cout << "Input file: " << inputfile.Data() << endl;
 cout << "Output file: " << outputfile.Data() << endl;
}
