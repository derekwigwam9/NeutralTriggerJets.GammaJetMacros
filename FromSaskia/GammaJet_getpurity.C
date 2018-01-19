void GammaJet_getpurity()
{
  TFile *file0 = new TFile("GammaJet_analysis_Ntuple_9GeV_withRunId.root");
  TH1 *pi0[12];
  TH1 *gamma[12];

  float Npi0[12] = {12324.,6430.,3453.,1999.,1053.,694.,413.,266.,198.,122.,110.,444.};

  // with TSP cut
  //  float Ngamma[12] = {13934.,7854.,4502.,2827.,1867.,1219.,787.,554.,379.,305.,224.,715.};

  // NO TSP cut
  float Ngamma[12] = {45287.,25295.,14536.,9006.,5535.,3733.,2350.,1662.,1167.,822.,659.,2133.};


  for (int i=0; i<12; i++)
    {
      TString h1_name = "pi0_";
      TString h2_name = "gamma_";

      TString P_cutSelection = "ptTPC>3. && TSP<0.08 && abs(z)<55 && ";
      TString G_cutSelection = "ptTPC>3. && abs(z)<55 && ";

      h1_name +=  i;
      h2_name +=  i;

      if (i==0) 
	{
	  P_cutSelection += "EneT0*sin(2*atan(exp(-1*etav1)))>9. && EneT0*sin(2*atan(exp(-1*etav1)))<10.";	  
	  G_cutSelection += "EneT0*sin(2*atan(exp(-1*etav1)))>9. && EneT0*sin(2*atan(exp(-1*etav1)))<10.";
	}

      if (i==1) 
	{
	  P_cutSelection += "EneT0*sin(2*atan(exp(-1*etav1)))>10. && EneT0*sin(2*atan(exp(-1*etav1)))<11.";	  
	  G_cutSelection += "EneT0*sin(2*atan(exp(-1*etav1)))>10. && EneT0*sin(2*atan(exp(-1*etav1)))<11.";
	}

      if (i==2) 
	{
	  P_cutSelection += "EneT0*sin(2*atan(exp(-1*etav1)))>11. && EneT0*sin(2*atan(exp(-1*etav1)))<12.";	  
	  G_cutSelection += "EneT0*sin(2*atan(exp(-1*etav1)))>11. && EneT0*sin(2*atan(exp(-1*etav1)))<12.";
	}

      if (i==3) 
	{
	  P_cutSelection += "EneT0*sin(2*atan(exp(-1*etav1)))>12. && EneT0*sin(2*atan(exp(-1*etav1)))<13.";	  
	  G_cutSelection += "EneT0*sin(2*atan(exp(-1*etav1)))>12. && EneT0*sin(2*atan(exp(-1*etav1)))<13.";
	}

      if (i==4) 
	{
	  P_cutSelection += "EneT0*sin(2*atan(exp(-1*etav1)))>13. && EneT0*sin(2*atan(exp(-1*etav1)))<14.";	  
	  G_cutSelection += "EneT0*sin(2*atan(exp(-1*etav1)))>13. && EneT0*sin(2*atan(exp(-1*etav1)))<14.";
	}

      if (i==5) 
	{
	  P_cutSelection += "EneT0*sin(2*atan(exp(-1*etav1)))>14. && EneT0*sin(2*atan(exp(-1*etav1)))<15.";	  
	  G_cutSelection += "EneT0*sin(2*atan(exp(-1*etav1)))>14. && EneT0*sin(2*atan(exp(-1*etav1)))<15.";
	}

      if (i==6) 
	{
	  P_cutSelection += "EneT0*sin(2*atan(exp(-1*etav1)))>15. && EneT0*sin(2*atan(exp(-1*etav1)))<16.";	  
	  G_cutSelection += "EneT0*sin(2*atan(exp(-1*etav1)))>15. && EneT0*sin(2*atan(exp(-1*etav1)))<16.";
	}

      if (i==7) 
	{
	  P_cutSelection += "EneT0*sin(2*atan(exp(-1*etav1)))>16. && EneT0*sin(2*atan(exp(-1*etav1)))<17.";	  
	  G_cutSelection += "EneT0*sin(2*atan(exp(-1*etav1)))>16. && EneT0*sin(2*atan(exp(-1*etav1)))<17.";
	}

      if (i==8) 
	{
	  P_cutSelection += "EneT0*sin(2*atan(exp(-1*etav1)))>17. && EneT0*sin(2*atan(exp(-1*etav1)))<18.";	  
	  G_cutSelection += "EneT0*sin(2*atan(exp(-1*etav1)))>17. && EneT0*sin(2*atan(exp(-1*etav1)))<18.";
	}

      if (i==9) 
	{
	  P_cutSelection += "EneT0*sin(2*atan(exp(-1*etav1)))>18. && EneT0*sin(2*atan(exp(-1*etav1)))<19.";	  
	  G_cutSelection += "EneT0*sin(2*atan(exp(-1*etav1)))>18. && EneT0*sin(2*atan(exp(-1*etav1)))<19.";
	}

      if (i==10) 
	{
	  P_cutSelection += "EneT0*sin(2*atan(exp(-1*etav1)))>19. && EneT0*sin(2*atan(exp(-1*etav1)))<20.";	  
	  G_cutSelection += "EneT0*sin(2*atan(exp(-1*etav1)))>19. && EneT0*sin(2*atan(exp(-1*etav1)))<20.";
	}

      if (i==11) 
	{
	  P_cutSelection += "EneT0*sin(2*atan(exp(-1*etav1)))>20.";
	  G_cutSelection += "EneT0*sin(2*atan(exp(-1*etav1)))>20.";
	}

      pi0[i] = new TH1D(h1_name.Data(),"",70,-2.,5.);
      pi0[i]->Sumw2();

      gamma[i] = new TH1D(h2_name.Data(),"",70,-2.,5.);
      gamma[i]->Sumw2();

      cout << i << " " << h1_name.Data()<< endl;
      cout << P_cutSelection.Data()<< endl;

      cout << i << " " << h2_name.Data()<< endl;
      cout << G_cutSelection.Data()<< endl;

      Gammajet->Project(h1_name.Data(),"dphif",P_cutSelection.Data());
      Gammajet->Project(h2_name.Data(),"dphif",G_cutSelection.Data());


      pi0[i]->Scale(1./Npi0[i]);
      pi0[i]->Scale(1./0.1);
      gamma[i]->Scale(1./Ngamma[i]);
      gamma[i]->Scale(1./0.1);

    }

  TFile *file1 = new TFile("DeltaPhi_hists_pttpc3_NOTSPgamma.root","RECREATE");

  for (int i=0; i<12; i++) {
    pi0[i]->Write();
    gamma[i]->Write();

  }
  file1->Close();
    
}
