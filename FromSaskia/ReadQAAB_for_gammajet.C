#include "TRandom.h"
#include "TNtuple.h"

void ReadQAAB_for_gammajet()
 {

   TFile *myFile= new TFile("pp200_run9_triggers.root","recreate");      

   mGammaTriggers=new TNtuple("GammaTrigs","GammaTrigs","EneT0:TSP:eh:etav1:z:ET");

   mTupleCAB=new TNtuple("CAB","CAB","didE:ENET0:XX:YY:adc11:didP:adcE1:adcP1:eT:phT:hSS:hpedSS:muRef:TSP");
   mTupleQAAB=new TNtuple("QAAB","QAAB","EneT0:MPos:MNeg:H:en4:enp4:eneT0:z:etav1:phiv1:didT:delta1:dphi1:Weta1");
   mTupleAngleAB=new TNtuple("AngleTAB","AngleTAB","moduleT:EtaE:sP:runId:evt:NOP:Wphi1:enp7:enp1:enp8:enp0:en01:en02:PTower");
   mTupleSMDE1B=new TNtuple("SMDE1B","SMDE1B","en3:en5:en2:en6:en1:en7:en0:en8:enp3:enp5:enp2:enp6:en03:en04");
   mTuplePiB=new TNtuple("PiB","PiB","en9:en10:en11:en12:enp01:enp02:enp03:enp04:enp9:enp10:enp11:enp12:pidTower:Enpq1");
   mTuplePhoB=new TNtuple("PhoB","PhoB","sT:THeta:Ennq1:Enpq20:Ennq20:Enpq19:Ennq19:Enpq21:NumOfTracks:muRef:nV:rank1:rank:noOfPiVer");
   mTuplePi1B=new TNtuple("Pi1B","Pi1B","en05:enp05:en06:enp06:en07:enp07:en08:enp08:en13:enp13:en14:enp14:en15:enp15");
   mTupleEighteenB=new TNtuple("EighteenB","EighteenB","Ehighest:eh");



   Int_t tot_counter=0;
   Int_t tot_JP = 0;   Int_t tot_JG = 0;

   int nevents_inRunRange[12]={0,0,0,0,0,0,0,0,0,0,0,0};
   int nTrigs[12] = {0,0,0,0,0,0,0,0,0,0,0,0};
   int nTrigsWithCuts[12] = {0,0,0,0,0,0,0,0,0,0,0,0};
   int nPi0[12] = {0,0,0,0,0,0,0,0,0,0,0,0};
   int nTrigs_TSPlt06[12] = {0,0,0,0,0,0,0,0,0,0,0,0};

   int RunRange[12] = {10000000, 10115070, 10122018, 10128011, 10134102, 10138096, 10143091, 10149032, 10158002, 10164020, 10169078, 10174002};

   char files_name[50000];
   char n;
   //   for(int i=1; i<=70;i++)
   for(int i=1; i<=9;i++)
     {

       //       if(!(i!=71 && i!=72 && i!=73 && i!=74 && i!=75 &&  i!=76 && i!=77 &&  i!=78 && i!=79 && i!=80))continue;

       n=sprintf (files_name, "/data/smgroup/sm1/nsahoo/GammaJet/pp200R9/pp2009_nihar/pp2009_%d.root",i);

       printf ("%s \n",files_name);


       TFile* f1=new TFile(files_name);

       TNtuple *QAAB=(TNtuple*)f1->Get("QAAB");
       TNtuple *CAB=(TNtuple*)f1->Get("CAB");
       TNtuple *AngleTAB=(TNtuple*)f1->Get("AngleTAB");
       TNtuple *SMDE1B=(TNtuple*)f1->Get("SMDE1B");
       TNtuple *PiB=(TNtuple*)f1->Get("PiB");
       TNtuple *Pi1B=(TNtuple*)f1->Get("Pi1B");
       TNtuple *PhoB=(TNtuple*)f1->Get("PhoB");
       TNtuple *New6=(TNtuple*)f1->Get("New6");
       TNtuple *New7=(TNtuple*)f1->Get("New7");
       TNtuple *New8=(TNtuple*)f1->Get("New8");
       TNtuple *FiveteenB=(TNtuple*)f1->Get("FiveteenB");
       TNtuple *SixteenB=(TNtuple*)f1->Get("SixteenB");
       TNtuple *SeventeenB=(TNtuple*)f1->Get("SeventeenB");
       TNtuple *EighteenB=(TNtuple*)f1->Get("EighteenB");
       TNtuple *FTPCQ=(TNtuple*)f1->Get("FTPCQ");
       TNtuple *FiveL=(TNtuple*)f1->Get("FiveL");

 

       //       TFile* f17=new TFile("Tower_Filter_All.root");
       //       TH1F *Tower=(TH1F*)f17->Get("IdT");
       //       TH1F *BSMDE=(TH1F*)f17->Get("IdE");TH1F *BSMDP=(TH1F*)f17->Get("IdP");
       //       TProfile *ET=(TProfile*)f17->Get("hprofTE");


       float didE,ENET0,XX,YY,adc11,didP,adcE1,adcP1,eT,phT,hSS,hpedSS,hRMSSS,TC7; //CAB
       float EneT0,MPos,MNeg,H,en4,enp4,eneT0,z,etav1,phiv1,didT,delta1,dphi1,Weta1; //QAAB
       float moduleT,EtaE,sP,runId,evt,NOP,Wphi1,enp7,enp1,enp8,enp0,en01,en02,PTower;//AngleTAB
       float en3,en5,en2,en6,en1,en7,en0,en8,enp3,enp5,enp2,enp6,en03,en04;//SMDE1               
       float en9,en10,en11,en12,enp01,enp02,enp03,enp04,enp9,enp10,enp11,enp12,pidTower,Enpq1;//Pi
       float sT,eff,energ,dphif,energSt,THeta,Ennq1,Enpq20,Ennq20,Enpq19,Ennq19,Enpq21,dphiin,dphiou;	//Pho
       
       float en05,enp05,en06,enp06,en07,enp07,en08,enp08,en13,enp13,en14,enp14,en15,enp15;//Pi1		
       float hiTower,Subh,Moduleh,Etah,Adch,T,evt,z,runId,Idh,eTh,phiTh,Thetah,PPTPC;//FiveLL
       float angleRe,angleReS1,angleReS2,angleRef,angleRefS1,angleRefS2,NumOfTracks,Q1,Q2,XR,YR,XRf,YRf;//FiveteenB
       float XRS1,XRS2,YRS1,YRS2,Q,Q3,Q4,Q1S1,Q1S2,Q2S1,Q2S2,Q3S1,Q3S2,Q4S1;//SixteenA
       float Q4S2,XRfS1,XRfS2,YRfS1,YRfS2,XRfW,YRfW,XRfE,YRfE,XRfSW1,YRfSW1,XRfSW2,YRfSW2,XRfSE1;//SeventeenA
       
       float angleRepe,angleReS1pe,angleReS2pe,angleRene,angleReS1ne,angleReS2ne,angleRenc,angleReS1nc,angleReS2nc,angleRepc,angleReS1pc,angleReS2pc;//New6A
       float angleRept,angleReS1pt,angleReS2pt,vpdz,BBCz,ZDCz;//New7A
       float psif0,psif1,psifn0,psifn1,Ppo,xg,yg,zg,px,py,pz;//New8A
       
       
       float YRfSE1,XRfSE2,YRfSE2,psie,psiw,psif,mBBCAdcCut,vf2,vf2F,psifn,v2B,Ehighest,mBBCAdcCut0;//EighteenA
       float angleRefW,angleRefE,angleRefW1,angleRefE1,angleRefW2,angleRefE2;//FTPCQA
       
       float angleu0v,angleu1v,angleu2v,angleu3v,angleu4v,angleu5v,angleu6v,angleu7v,NumOfTracks,muRef,nV,rank1,rank,noOfPiVer;//New9A
       float pTPC,ptTPC,dEdx,EtaTr,epsi,ch,dca,Fp,eE,phE,ETAP,PHIP,eT,phT;//Track
 //CAB  
       TLeaf *l_didE=CAB->GetLeaf("didE");TLeaf *l_ENET0=CAB->GetLeaf("ENET0");TLeaf *l_XX=CAB->GetLeaf("XX");
       TLeaf *l_YY=CAB->GetLeaf("YY");TLeaf *l_adc11=CAB->GetLeaf("adc11");TLeaf *l_didP=CAB->GetLeaf("didP");
       TLeaf *l_adcE1=CAB->GetLeaf("adcE1");TLeaf *l_adcP1=CAB->GetLeaf("adcP1");TLeaf *l_eT=CAB->GetLeaf("eT");
       TLeaf *l_phT=CAB->GetLeaf("phT");TLeaf *l_hSS=CAB->GetLeaf("hSS");TLeaf *l_hpedSS=CAB->GetLeaf("hpedSS");
       TLeaf *l_hRMSSS=CAB->GetLeaf("hRMSSS");TLeaf *l_TC7=CAB->GetLeaf("TC7");
 
       TLeaf *l_EneT0=QAAB->GetLeaf("EneT0");TLeaf *l_MPos=QAAB->GetLeaf("MPos");TLeaf *l_MNeg=QAAB->GetLeaf("MNeg");
       TLeaf *l_H=QAAB->GetLeaf("H");TLeaf *l_en4=QAAB->GetLeaf("en4");TLeaf *l_enp4=QAAB->GetLeaf("enp4");
       TLeaf *l_eneT0=QAAB->GetLeaf("eneT0");TLeaf *l_z=QAAB->GetLeaf("z");TLeaf *l_etav1=QAAB->GetLeaf("etav1");
       TLeaf *l_phiv1=QAAB->GetLeaf("phiv1");TLeaf *l_didT=QAAB->GetLeaf("didT");TLeaf *l_delta1=QAAB->GetLeaf("delta1");
       TLeaf *l_dphi1=QAAB->GetLeaf("dphi1");TLeaf *l_Weta1=QAAB->GetLeaf("Weta1");
       
       TLeaf *l_moduleT=AngleTAB->GetLeaf("moduleT");TLeaf *l_EtaE=AngleTAB->GetLeaf("EtaE");TLeaf *l_sP=AngleTAB->GetLeaf("sP");
       TLeaf *l_runId=AngleTAB->GetLeaf("runId");TLeaf *l_evt=AngleTAB->GetLeaf("evt");TLeaf *l_NOP=AngleTAB->GetLeaf("NOP");
       TLeaf *l_Wphi1=AngleTAB->GetLeaf("Wphi1");TLeaf *l_enp7=AngleTAB->GetLeaf("enp7");TLeaf *l_enp1=AngleTAB->GetLeaf("enp1");
       TLeaf *l_enp8=AngleTAB->GetLeaf("enp8");TLeaf *l_enp0=AngleTAB->GetLeaf("enp0");TLeaf *l_en01=AngleTAB->GetLeaf("en01");
       TLeaf *l_en02=AngleTAB->GetLeaf("en02");TLeaf *l_PTower=AngleTAB->GetLeaf("PTower");
       
       TLeaf *l_en3=SMDE1B->GetLeaf("en3");TLeaf *l_en5=SMDE1B->GetLeaf("en5");TLeaf *l_en2=SMDE1B->GetLeaf("en2");
       TLeaf *l_en6=SMDE1B->GetLeaf("en6");TLeaf *l_en1=SMDE1B->GetLeaf("en1");TLeaf *l_en7=SMDE1B->GetLeaf("en7");
       TLeaf *l_en0=SMDE1B->GetLeaf("en0");TLeaf *l_en8=SMDE1B->GetLeaf("en8");TLeaf *l_enp3=SMDE1B->GetLeaf("enp3");
       TLeaf *l_enp5=SMDE1B->GetLeaf("enp5");TLeaf *l_enp2=SMDE1B->GetLeaf("enp2");TLeaf *l_enp6=SMDE1B->GetLeaf("enp6");
       TLeaf *l_en03=SMDE1B->GetLeaf("en03");TLeaf *l_en04=SMDE1B->GetLeaf("en04");
       
       TLeaf *l_en9=PiB->GetLeaf("en9");TLeaf *l_en10=PiB->GetLeaf("en10");TLeaf *l_en11=PiB->GetLeaf("en11");
       TLeaf *l_en12=PiB->GetLeaf("en12");TLeaf *l_enp01=PiB->GetLeaf("enp01");TLeaf *l_enp02=PiB->GetLeaf("enp02");
       TLeaf *l_enp03=PiB->GetLeaf("enp03");TLeaf *l_enp04=PiB->GetLeaf("enp04");TLeaf *l_enp9=PiB->GetLeaf("enp9");
       TLeaf *l_enp10=PiB->GetLeaf("enp10");TLeaf *l_enp11=PiB->GetLeaf("enp11");TLeaf *l_enp12=PiB->GetLeaf("enp12");
       TLeaf *l_pidTower=PiB->GetLeaf("pidTower");TLeaf *l_Enpq1=PiB->GetLeaf("Enpq1");

       TLeaf *l_sT=PhoB->GetLeaf("sT");TLeaf *l_eff=PhoB->GetLeaf("eff"); //TLeaf *l_energ=PhoB->GetLeaf("energ");
       TLeaf *l_muRef=PhoB->GetLeaf("muRef");
       //TLeaf *l_energSt=PhoB->GetLeaf("energSt");
       TLeaf *l_THeta=PhoB->GetLeaf("THeta");TLeaf *l_Ennq1=PhoB->GetLeaf("Ennq1");
       TLeaf *l_Enpq20=PhoB->GetLeaf("Enpq20");TLeaf *l_Ennq20=PhoB->GetLeaf("Ennq20");TLeaf *l_Enpq19=PhoB->GetLeaf("Enpq19");
       TLeaf *l_Ennq19=PhoB->GetLeaf("Ennq19");TLeaf *l_Enpq21=PhoB->GetLeaf("Enpq21");
       //TLeaf *l_dphiin=PhoB->GetLeaf("dphiin");
       //       TLeaf *l_dphiou=PhoB->GetLeaf("dphiou");//PhoB


       TLeaf *l_en05=Pi1B->GetLeaf("en05");TLeaf *l_enp05=Pi1B->GetLeaf("enp05");TLeaf *l_en06=Pi1B->GetLeaf("en06");
       TLeaf *l_enp06=Pi1B->GetLeaf("enp06");TLeaf *l_en07=Pi1B->GetLeaf("en07");TLeaf *l_enp07=Pi1B->GetLeaf("enp07");
       TLeaf *l_en08=Pi1B->GetLeaf("en08");TLeaf *l_enp08=Pi1B->GetLeaf("enp08");TLeaf *l_en13=Pi1B->GetLeaf("en13");
       TLeaf *l_enp13=Pi1B->GetLeaf("enp13");TLeaf *l_en14=Pi1B->GetLeaf("en14");TLeaf *l_enp14=Pi1B->GetLeaf("enp14");
       TLeaf *l_en15=Pi1B->GetLeaf("en15");TLeaf *l_enp15=Pi1B->GetLeaf("enp15");
 
       TLeaf *l_hiTower=FiveL->GetLeaf("hiTower");TLeaf *l_Subh=FiveL->GetLeaf("Subh");TLeaf *l_Moduleh=FiveL->GetLeaf("Moduleh");
       TLeaf *l_Etah=FiveL->GetLeaf("Etah");TLeaf *l_Adch=FiveL->GetLeaf("Adch");TLeaf *l_T=FiveL->GetLeaf("T");
       //       TLeaf *l_evt=FiveL->GetLeaf("evt");TLeaf *l_z=FiveL->GetLeaf("z");TLeaf *l_runId=FiveL->GetLeaf("runId");
       TLeaf *l_Idh=FiveL->GetLeaf("Idh");TLeaf *l_eTh=FiveL->GetLeaf("eTh");TLeaf *l_phiTh=FiveL->GetLeaf("phiTh");
       TLeaf *l_Thetah=FiveL->GetLeaf("Thetah");TLeaf *l_PPTPC=FiveL->GetLeaf("PPTPC");
       


       TLeaf *l_Ehighest=EighteenB->GetLeaf("Ehighest");


       l_didE->SetAddress(&didE);l_ENET0->SetAddress(&ENET0);l_XX->SetAddress(&XX);l_YY->SetAddress(&YY);l_adc11->SetAddress(&adc11);
l_didP->SetAddress(&didP);l_adcE1->SetAddress(&adcE1);l_adcP1->SetAddress(&adcP1);l_eT->SetAddress(&eT);l_phT->SetAddress(&phT);
l_hSS->SetAddress(&hSS);l_hpedSS->SetAddress(&hpedSS);l_hRMSSS->SetAddress(&hRMSSS);l_TC7->SetAddress(&TC7); //CAB

l_EneT0->SetAddress(&EneT0);l_MPos->SetAddress(&MPos);l_MNeg->SetAddress(&MNeg);l_H->SetAddress(&H);l_en4->SetAddress(&en4);
l_enp4->SetAddress(&enp4);l_eneT0->SetAddress(&eneT0);l_z->SetAddress(&z);l_etav1->SetAddress(&etav1);l_phiv1->SetAddress(&phiv1);
l_didT->SetAddress(&didT);l_delta1->SetAddress(&delta1);l_dphi1->SetAddress(&dphi1);l_Weta1->SetAddress(&Weta1); //QAAB

l_moduleT->SetAddress(&moduleT);l_EtaE->SetAddress(&EtaE);l_sP->SetAddress(&sP);l_runId->SetAddress(&runId);l_evt->SetAddress(&evt);
l_NOP->SetAddress(&NOP);l_Wphi1->SetAddress(&Wphi1);l_enp7->SetAddress(&enp7);l_enp1->SetAddress(&enp1);l_enp8->SetAddress(&enp8);
l_enp0->SetAddress(&enp0);l_en01->SetAddress(&en01);l_en02->SetAddress(&en02);l_PTower->SetAddress(&PTower);//AngleTAB

l_en3->SetAddress(&en3);l_en5->SetAddress(&en5);l_en2->SetAddress(&en2);l_en6->SetAddress(&en6);l_en1->SetAddress(&en1);
l_en7->SetAddress(&en7);l_en0->SetAddress(&en0);l_en8->SetAddress(&en8);l_enp3->SetAddress(&enp3);l_enp5->SetAddress(&enp5);
l_enp2->SetAddress(&enp2);l_enp6->SetAddress(&enp6);l_en03->SetAddress(&en03);l_en04->SetAddress(&en04);//SMDE1B   
            
l_en9->SetAddress(&en9);l_en10->SetAddress(&en10);l_en11->SetAddress(&en11);l_en12->SetAddress(&en12);l_enp01->SetAddress(&enp01);
l_enp02->SetAddress(&enp02);l_enp03->SetAddress(&enp03);l_enp04->SetAddress(&enp04);l_enp9->SetAddress(&enp9);l_enp10->SetAddress(&enp10);
l_enp11->SetAddress(&enp11);l_enp12->SetAddress(&enp12);l_pidTower->SetAddress(&pidTower);l_Enpq1->SetAddress(&Enpq1);//Pi	

 l_sT->SetAddress(&sT);
 // l_energ->SetAddress(&energ);l_dphif->SetAddress(&dphif);
l_muRef->SetAddress(&muRef);
 l_THeta->SetAddress(&THeta);l_Ennq1->SetAddress(&Ennq1);
 l_Enpq20->SetAddress(&Enpq20);l_Ennq20->SetAddress(&Ennq20);
 l_Enpq19->SetAddress(&Enpq19);l_Ennq19->SetAddress(&Ennq19);l_Enpq21->SetAddress(&Enpq21);
 // l_dphiin->SetAddress(&dphiin);l_dphiou->SetAddress(&dphiou);//PhoB
		
l_en05->SetAddress(&en05);l_enp05->SetAddress(&enp05);l_en06->SetAddress(&en06);l_enp06->SetAddress(&enp06);l_en07->SetAddress(&en07);
l_enp07->SetAddress(&enp07);l_en08->SetAddress(&en08);l_enp08->SetAddress(&enp08);l_en13->SetAddress(&en13);l_enp13->SetAddress(&enp13);
l_en14->SetAddress(&en14);l_enp14->SetAddress(&enp14);l_en15->SetAddress(&en15);l_enp15->SetAddress(&enp15);//Pi1B	

l_hiTower->SetAddress(&hiTower);l_Subh->SetAddress(&Subh);l_Moduleh->SetAddress(&Moduleh);l_Etah->SetAddress(&Etah);
l_Adch->SetAddress(&Adch);l_T->SetAddress(&T);l_evt->SetAddress(&evt);l_z->SetAddress(&z);l_runId->SetAddress(&runId);
l_Idh->SetAddress(&Idh);l_eTh->SetAddress(&eTh);l_phiTh->SetAddress(&phiTh);l_Thetah->SetAddress(&Thetah);l_PPTPC->SetAddress(&PPTPC);//FiveL


 l_Ehighest->SetAddress(&Ehighest);

 //TString outputfile = "2010_QAAB_test_all_cm_" + num + ".root";
 //TFile *fileout = new TFile(outputfile.Data(),"RECREATE");

//TFile myFile("2010_QAAB_test_all_cm_T102.root","recreate");

//    TFile myFile("auau200run11_modfy_TrkTowCorr_nt.root","recreate");      


   int counter=0;
float W1(0),W2(0),W3(0),W4(0);		
 float  eb(0), TSP050(0),TSP100(0),TSP125(0),TSP150(0),TSP200(0);
Int_t nentries=(Int_t)QAAB->GetEntries();

 tot_counter += nentries;


 Int_t JP=0; Int_t JG=0;
 int runRangeIndex;
 int runIdOld = -1;

for(Int_t D1=0;D1<nentries;D1++) 
       { //cout<<"entry number:::"<<D1<<"::::"<<"::evt ::"<<evt<<"::didT is::"<<didT<<endl;
        QAAB->GetEntry(D1); CAB->GetEntry(D1); AngleTAB->GetEntry(D1);SMDE1B->GetEntry(D1);
	PiB->GetEntry(D1);PhoB->GetEntry(D1); Pi1B->GetEntry(D1); //New6A->GetEntry(D1);
        //New7->GetEntry(D1);New8A->GetEntry(D1);
	FiveL->GetEntry(D1);
	FiveteenB->GetEntry(D1);
        SixteenB->GetEntry(D1);
	SeventeenB->GetEntry(D1);
	EighteenB->GetEntry(D1);
	//       	cout << (int)runId << " " << runIdOld<< endl;

       	Bool_t flag_Tower = Check_hot_Tower(didT+1);
	if((flag_Tower))continue;

	Bool_t flag_EtaStrp =  Check_hot_EtaStrip(didE+1);
	if((flag_EtaStrp))continue;



counter++;
 if(counter%5000==0)cout<<"counting "<<counter<<endl;

 // if(!(fabs(z)<55 &&z!=0)) continue;

 // nevents_inRunRange[runRangeIndex]++;

 // if(!(en4>=0.5&&enp4>=0.5/*&&etav1<=1&&etav1>=-1&&z<100&&z>-100*/&&(eneT0*sin(THeta))>=9/*&&PTower<3*/&&eT>-0.9&&eT<0.9&&z!=0))continue;
 if (!(EneT0>=6/*&&PTower<3*/&&eT>-0.9&&eT<0.9))continue;
 // nTrigs[runRangeIndex]++;

 if(!(en4>=0.5&&enp4>=0.5/*&&fabs(z-vpdz)<3.*/&&adc11<=6004&&fabs(etav1)<1./*&&nV==1*/)) continue;

 float XE(0); XE=EneT0*sin(2*atan(exp(-1*etav1)));
 if (XE<9. || XE>30.) continue;
 float TSP = 0.;
   TSP=(eneT0/((en4+enp4)*0.783+(en3+enp3+en5+enp5)*2.21+(en2+enp2+en6+enp6)*6.26+(en1+enp1+en7+enp7)*11.51+(en0+enp0+en8+enp8)*17.73+(en01+enp01+en9+enp9)*24.78+(en02+enp02+en10+enp10)*32.57+(en03+enp03+en11+enp11)*41.05));

   //   if (runId==10145081 && evt==108848) cout << "EneT0 = " << EneT0 << " " << eneT0 << ", phiv1 = " << phiv1 <<", TSP = " << TSP << endl;

   mGammaTriggers->Fill(EneT0,TSP,Ehighest,etav1,z,XE);
       }
     }


	myFile->cd();
	mGammaTriggers->Write();
	/*
	mTupleQAAB->Write(); 
	mTupleCAB->Write();
	mTupleAngleAB->Write();
	mTupleSMDE1B->Write();
	mTuplePiB->Write();
	mTuplePhoB->Write(); 
	mTuplePi1B->Write(); 
	mTupleEighteenB->Write();
	*/
	//	mTupleNew8->Write();
	//        mTupleNew7->Write();

	//	mTupleNew8->Write();
	//	mTupleFiveL->Write();

	//	mTupleFiveteenB->Write();
	//        mTupleSixteenB->Write(); 
	//	mTupleSeventeenB->Write(); 

	//	mTupleFTPCQ->Write();
	//	mTupleEighteenB->Write();

	//	mTupleNew6->Write();

	myFile->Close(); 
 }





Bool_t Check_hot_Tower(Int_t TwrId)
{

  Int_t T_Id = TwrId;
  
  Int_t x_Id = 0;
  
  
  Int_t hotTower[146]={2,51,142,147,176,188,225,324,342,425,447,485,486,592,638,651,654,675,791,815,900,902,954,955,964,982,1022,1026,1027,1029,1046,1047,1064,1129,1133,1142,1164,1172,1199,1243,1245,1247,1250,1265,1270,1272,1273,1295,1304,1320,1322,1379,1383,1389,1406,1423,1428,1441,1575,1576,1706,1742,1763,1767,1774,1882,1908,1982,1986,2006,2026,2067,2071,2081,2106,2161,2165,2184,2193,2202,2206,2254,2262,2291,2302,2304,2307,2384,2392,2395,2410,2505,2522,2524,2584,2590,2591,2682,2843,2930,3107,3168,3254,3261,3680,3691,3710,3719,3728,3747,3770,3841,3949,3985,4014,4020,4042,4044,4048,4051,4054,4058,4066,4080,4122,4125,4168,4172,4327,4442,4443,4445,4446,4450,4462,4466,4468,4474,4507,4544,4565,4570,4608,4633,4640,4793};
   

  for(int i=0; i<146;i++)
    {
      {if(T_Id == hotTower[i]) //cout<<hotTower[i]<<endl;
	  { x_Id = 1;break;}}
    }

  if(x_Id == 1) 
    return kTRUE;
  else return kFALSE;
}


Bool_t Check_hot_EtaStrip(Int_t EtaStpId)
{

  Int_t T_Id = EtaStpId;
  
  Int_t x_Id = 0;
  
  
  Int_t hotTower[320]={407,408,409,410,411,412,415,416,417,418,419,439,441,443,747,749,1143,1165,1167,1183,1185,1789,1790,1791,1792,1793,1794,2057,2058,2059,2060,2061,2062,2066,2075,2847,2848,2849,2850,2851,2965,2966,2967,2968,2969,2970,3132,3134,3136,3142,3144,3422,3423,3424,3425,3426,3427,3428,3598,3687,4271,4272,4273,4274,4275,4276,4277,4325,4327,4745,4759,4761,4765,4767,4769,4773,4775,4947,4948,4949,4950,5005,5006,5007,5008,5009,5010,5011,5073,5074,5075,5076,5077,5090,5359,5361,5699,5822,5823,5824,5825,5826,5827,5828,5847,5848,5849,5850,5990,5992,5994,6275,6363,6364,6365,6366,6367,6368,6369,6701,6890,6891,6892,6893,6894,7332,7334,7342,7444,7447,7481,7499,7625,7631,7633,7641,7668,7669,7792,7949,7950,8075,8077,8083,8085,8089,8093,8310,8693,8699,8960,9087,9089,9094,9267,9269,9273,9275,9281,9440,9441,9443,9447,9448,9449,9450,9451,9592,9598,9739,9741,9743,9889,9891,10024,10040,10042,10043,10189,10191,10193,10199,10201,10348,10349,10350,10773,10775,10777,10781,10783,10785,10797,10798,10799,10800,10801,10910,10948,10949,11099,11305,11306,11307,11308,11309,11310,11389,11391,11393,11397,11398,11399,11400,11401,11645,11691,11693,11699,11839,11841,12440,12442,12444,12448,12450,12565,12567,12569,12583,12589,12591,12597,12598,12599,12600,12601,12707,12708,12709,12710,12711,12712,12725,12733,12739,12740,12741,12742,12743,12744,12747,12748,12749,13039,13040,13041,13043,13048,13049,13167,13173,13175,13341,13347,13349,13489,13490,13491,13492,13493,13495,13886,13887,13888,13889,13890,13891,13940,13946,13947,13948,13949,13950,13951,14224,14230,14236,14248,14250,14380,14381,14382,14383,14384,14385,14386,14525,14533,14539,14541,14547,14548,14549,14550,14689,14691,14693,14847,14849,14850,16294,16489,16491,16631,16633,16639,17085,17091,17982};
  

   

  for(int i=0; i<320;i++)
    {
      {if(T_Id == hotTower[i]) //cout<<hotTower[i]<<endl;
	  { x_Id = 1;break;}}
    }

  if(x_Id == 1) 
    return kTRUE;
  else return kFALSE;
}


