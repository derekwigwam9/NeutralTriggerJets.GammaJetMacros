void R_TSP_Variation_Et()
{
  gROOT->Reset();  gStyle->SetCanvasColor(0);  gStyle->SetOptStat(0);
  

  TString filename1 = "fitCorrelations_ET_bins_pttpc3_NOTSPgamma.root";
  
 
 
  TFile *file0= new TFile(filename1.Data());
  
 
  double ped;
  int binlo1, binhi1;
  int binlo2, binhi2;


  TH1 *hg[12];
  TH1 *hp[12];
  TF1 *f1p[12];
  TF1 *f1g[12];
  double yieldNSg[12], errNSg[12];
  double yieldFSg[12], errFSg[12];
  double yieldNSp[12], errNSp[12];
  double yieldFSp[12], errFSp[12];
  double ex[12] = {0};

  double plotR[12], plot_errR[12], plot_pt[12];

  double R[12], errR[12];

  for (int i=0; i<12; i++)
    {
      double pt = 9.0;

      plot_pt[i] = pt + i*1.0 +0.5;


      TString gammahis = "gamma_";
      gammahis += i;
      TString pi0his = "pi0_";
      pi0his += i;

      file0->GetObject(gammahis.Data(),hg[i]);

      f1g[i] = hg[i]->GetFunction("f1");
      ped = f1g[i]->GetParameter(6);

      binlo1 = hg[i]->FindBin(-0.63);
      binhi1 = hg[i]->FindBin(0.63);
      binlo2 = hg[i]->FindBin(2.51);
      binhi2 = hg[i]->FindBin(3.77);
      
      yieldNSg[i] = 0.; 
      errNSg[i] = 0.;
      for (int j=binlo1; j<binhi1; j++)
	{
	  yieldNSg[i] += (double) hg[i]->GetBinContent(j);
	  errNSg[i] += (hg[i]->GetBinError(j))*(hg[i]->GetBinError(j));
	  if (hg[i]->GetBinContent(j) > 0.) yieldNSg[i] -= ped;
	}  
      yieldNSg[i] = yieldNSg[i]*0.1;
      errNSg[i] = sqrt(errNSg[i])*0.1;

      file0->GetObject(pi0his.Data(),hp[i]);

      f1p[i] = hp[i]->GetFunction("f1");
      ped = f1p[i]->GetParameter(6);

      binlo1 = hp[i]->FindBin(-0.63);
      binhi1 = hp[i]->FindBin(0.63);
      binlo2 = hp[i]->FindBin(2.51);
      binhi2 = hp[i]->FindBin(3.77);
      
      yieldNSp[i] = 0.; 
      errNSp[i] = 0.;
      for (int j=binlo1; j<binhi1; j++)
	{
	  yieldNSp[i] += (double) hp[i]->GetBinContent(j);
	  errNSp[i] += (hp[i]->GetBinError(j))*(hp[i]->GetBinError(j));
	  if (hp[i]->GetBinContent(j) > 0.) yieldNSp[i] -= ped;
	}  
      yieldNSp[i] = yieldNSp[i]*0.1;
      errNSp[i] = sqrt(errNSp[i])*0.1;


      if (yieldNSp[i]>0.)
	{
	  R[i] = yieldNSg[i]/yieldNSp[i];
	  cout  << i << " " << R[i] << endl;
	  if (yieldNSg[i]<0) R[i] = 0.;
	  cout  << i << " " << R[i] << endl;
	  errR[i] = R[i] * sqrt((errNSg[i]*errNSg[i])/(yieldNSg[i]*yieldNSg[i]) + (errNSp[i]*errNSp[i])/(yieldNSp[i]*yieldNSp[i]));

	  cout  << i << " " << R[i] << " +- " << errR[i] << endl;
	  plotR[i] = R[i];
	  plot_errR[i] = errR[i];

	  cout  << i << " " << plotR[i] << " +- " << plot_errR[i] << endl;
	}
    }



  c1 = new TCanvas("c1","R_dAu",200,10,600,500);
  c1->SetFillColor(0);
  c1->SetBorderMode(0);
  c1->SetBorderSize(2);
  c1->SetLeftMargin(0.14);
  c1->SetBottomMargin(0.14);
  //  c1->SetLogy();

  c1->Draw();
  TH2F *hr = new TH2F("hr","",20,9.,21.,20,0.01,1.5);
  hr->SetLabelSize(0.05);
  hr->SetStats(0);
  hr->GetXaxis()->SetLabelSize(0.05);
  hr->GetXaxis()->SetLabelOffset(0.01);
  hr->GetXaxis()->SetTitleSize(0.05);
  hr->GetXaxis()->SetTitleOffset(1.2);
  hr->GetYaxis()->SetLabelSize(0.05);
  hr->GetYaxis()->SetTitleSize(0.05);
  hr->GetYaxis()->SetLabelOffset(0.01);
  hr->GetYaxis()->SetTitleOffset(1.2);
  hr->SetXTitle("p_{T}^{trigger}");
  hr->SetYTitle("R = N_{#pi^{0}} / N_{#gamma_{rich}} = Y_{#gamma_{rich}+h}^{n} / Y_{#pi^{0}+h}^{n} ");
  hr->Draw("");
  
  TLegend *legend2 = new TLegend(0.35,0.72,0.7,0.9);
  legend2->SetFillColor(0);
  legend2->SetBorderSize(1);

  int syscolor;

  TGraphErrors* awaysideGammayields = new TGraphErrors(12,plot_pt,plotR,0,plot_errR);
  
  
  awaysideGammayields->SetMarkerStyle(20);
  awaysideGammayields->SetMarkerColor(1);
  awaysideGammayields->SetMarkerSize(1.6);
  awaysideGammayields->SetLineColor(1);

  
  awaysideGammayields->Draw("P");


}
 
