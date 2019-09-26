{

  gROOT->SetStyle("Plain");
  gStyle->SetTitleBorderSize(0);
  gStyle->SetOptStat("");

  gStyle->SetLabelFont(102,"");
  gStyle->SetLabelSize(0.06,"");
  gStyle->SetLabelFont(102,"xyz");
  gStyle->SetLabelSize(0.04,"xyz");
  gStyle->SetLabelOffset(0.001,"x");
  gStyle->SetLabelOffset(0.01,"y");

  gStyle->SetTitleFont(42,"xyz");
  gStyle->SetTitleFontSize(0.06);
  gStyle->SetTitleFont(42);
  gStyle->SetTitleSize(0.06,"xyz");
  gStyle->SetTitleOffset(0.9,"x");
  gStyle->SetTitleOffset(0.9,"y");

  gStyle->SetStripDecimals(kFALSE);

  gStyle->SetPadLeftMargin(0.15);
  gStyle->SetPadBottomMargin(0.15);

  gStyle->SetStatW(0.35);
  gStyle->SetStatH(0.25);

  gStyle->SetPadTickX(kTRUE);
  gStyle->SetPadTickY(kTRUE);

  gStyle->SetPalette(1);
  gStyle->SetNumberContours(99);

  gStyle->SetHistLineWidth(2);
  gStyle->SetFrameLineWidth(2);
  gStyle->SetFuncWidth(2);

  gStyle->SetStatFont(42);
  gStyle->SetOptFit(1111);
  gStyle->SetOptStat(0000);

  bool doStableCheck = false;
  int nDay = 1;
  int thisCase = atoi(gApplication->Argv(6));
  double upperlimit = atoi(gApplication->Argv(7));

  TFile f(Form("%s",gApplication->Argv(4)));
  TH1D* mean1 = (TH1D*)f.Get("Mean_E_reco_Energy_Spectrum_per_Day");

  cout<<"point 1"<<endl;
  TH1D* shift1;
  TH1D* shift2;
  TH1D* shift3;
  TH1D* shift4;
  shift1 = (TH1D*)f.Get("Mean_E_reco_shift1_Energy_Spectrum_per_Day(M)");
  shift2 = (TH1D*)f.Get("Mean_E_reco_shift2_Energy_Spectrum_per_Day(M)");
  shift3 = (TH1D*)f.Get("Mean_E_reco_shift3_Energy_Spectrum_per_Day(M)");
  shift4 = (TH1D*)f.Get("Mean_E_reco_shift4_Energy_Spectrum_per_Day(M)");

  TH1D* everyOne1[100];
  TH1D* everySeven1[10];
  TH1D* everyOne2[100];
  TH1D* everySeven2[10];
  TH1D* everyOne3[100];
  TH1D* everySeven3[10];
  TH1D* everyOne4[100];
  TH1D* everySeven4[10];  
  TGraph* g1 = new TGraph(10);
  TGraph* g2 = new TGraph(10);
  TGraph* g3 = new TGraph(10);
  TGraph* g4 = new TGraph(10);

  if(doStableCheck == true){
    for(int i=0;i<70;i++){
      everyOne1[i] = (TH1D*)f.Get(Form("shift1_day%d",i));
      everyOne2[i] = (TH1D*)f.Get(Form("shift2_day%d",i));
      everyOne3[i] = (TH1D*)f.Get(Form("shift3_day%d",i));
      everyOne4[i] = (TH1D*)f.Get(Form("shift4_day%d",i));      
      if(i<10){
        everySeven1[i] = (TH1D*)f.Get(Form("shift1_day%d",i));
        everySeven2[i] = (TH1D*)f.Get(Form("shift2_day%d",i));
        everySeven3[i] = (TH1D*)f.Get(Form("shift3_day%d",i));
        everySeven4[i] = (TH1D*)f.Get(Form("shift4_day%d",i));
      }
    }
    for(int i=0;i<10;i++){
      double tempContent1[1000] = {};
      double tempContent2[1000] = {};
      double tempContent3[1000] = {};
      double tempContent4[1000] = {};
	    
      for(int j=0;j<7;j++){
	for(int k=0;k<everyOne1[0]->GetNbinsX();k++){
	  tempContent1[k] += everyOne1[i*7+j]->GetBinContent(k+1);
	  tempContent2[k] += everyOne2[i*7+j]->GetBinContent(k+1);
	  tempContent3[k] += everyOne3[i*7+j]->GetBinContent(k+1);
	  tempContent4[k] += everyOne4[i*7+j]->GetBinContent(k+1);
	} 
      }	      
      for(int k=0;k<everyOne1[0]->GetNbinsX();k++){
        everySeven1[i]->SetBinContent(k+1,tempContent1[k]/7.);
	everySeven2[i]->SetBinContent(k+1,tempContent2[k]/7.);
	everySeven3[i]->SetBinContent(k+1,tempContent3[k]/7.);
	everySeven4[i]->SetBinContent(k+1,tempContent4[k]/7.);
      }
    }
  }


  //mean1->Scale(35000*nDay*0.9/mean1->Integral());
  //shift1->Scale(35000*nDay*0.9/shift1->Integral());
  //shift2->Scale(35000*nDay*0.9/shift2->Integral());
  //shift3->Scale(35000*nDay*0.9/shift3->Integral());
  //shift4->Scale(35000*nDay*0.9/shift4->Integral());

  for(Int_t i=0;i<mean1->GetNbinsX(); i++){
    //mean1->SetBinError(i+1, mean1->GetBinError(i+1)* (1./TMath::Sqrt(nDay)) );
    //shift1->SetBinError(i+1, shift1->GetBinError(i+1)* (1./TMath::Sqrt(nDay)) );
    //shift2->SetBinError(i+1, shift2->GetBinError(i+1)* (1./TMath::Sqrt(nDay)) );  
    //shift3->SetBinError(i+1, shift3->GetBinError(i+1)* (1./TMath::Sqrt(nDay)) );
    //shift4->SetBinError(i+1, shift4->GetBinError(i+1)* (1./TMath::Sqrt(nDay)) );

    mean1->SetBinError(i+1, sqrt(mean1->GetBinContent(i+1))* (1./TMath::Sqrt(nDay)) );
    shift1->SetBinError(i+1, sqrt(shift1->GetBinContent(i+1))* (1./TMath::Sqrt(nDay)) );
    shift2->SetBinError(i+1, sqrt(shift2->GetBinContent(i+1))* (1./TMath::Sqrt(nDay)) );
    shift3->SetBinError(i+1, sqrt(shift3->GetBinContent(i+1))* (1./TMath::Sqrt(nDay)) );
    shift4->SetBinError(i+1, sqrt(shift4->GetBinContent(i+1))* (1./TMath::Sqrt(nDay)) );

    if(doStableCheck){
      for(int k=0;k<10;k++){
        everySeven1[k]->SetBinError(i+1, sqrt(everySeven1[k]->GetBinContent(i+1))* (1./TMath::Sqrt(nDay))); 
        everySeven2[k]->SetBinError(i+1, sqrt(everySeven2[k]->GetBinContent(i+1))* (1./TMath::Sqrt(nDay)));
        everySeven3[k]->SetBinError(i+1, sqrt(everySeven3[k]->GetBinContent(i+1))* (1./TMath::Sqrt(nDay)));
        everySeven4[k]->SetBinError(i+1, sqrt(everySeven4[k]->GetBinContent(i+1))* (1./TMath::Sqrt(nDay)));
      }
    }
    
  }

  cout<<"point 2"<<endl;
  new TCanvas();
  mean1->SetTitle(Form("per %d day(s) spetrum comparison",nDay));
  mean1->SetLineColor(1);
  mean1->SetLineWidth(3);
  mean1->GetXaxis()->SetTitle("Energy (GeV)");
  mean1->GetYaxis()->SetTitle("Events per day per 0.25 GeV");
  mean1->Draw("hist e");
  cout<<"point 3"<<endl;

  shift1->SetLineColor(2);
  shift1->SetLineWidth(3);
  shift1->SetLineStyle(2);
  //shift1->Draw("hist same");
  shift2->SetLineColor(3);
  shift2->SetLineWidth(3);
  shift2->SetLineStyle(2);
  shift2->Draw("hist same");
  shift3->SetLineColor(4);
  shift3->SetLineWidth(3);
  shift3->SetLineStyle(2);
  //shift3->Draw("hist same");
  shift4->SetLineColor(6);
  shift4->SetLineWidth(3);
  shift4->SetLineStyle(2);
  shift4->Draw("hist same");

  cout<<"point 4"<<endl;
  //TText *t1 = new TText(3.8, 700 , Form("smeared 4%% mu at 1 GeV, 10%% pi+-, 10%% p, 10%% pi0, no n") );
  TText* t1;
  TText* t2;
  if(nDay == 1){
    t1 = new TText(4.8, 500 , Form("smeared 4%% mu at 1 GeV") );
    t1->SetTextSize(0.035);
    t1->Draw();
    t2 = new TText(4.8, 700 , Form("Stat. Error with smearing") );
    t2->SetTextSize(0.035);
    t2->Draw();
  }
  else{
    t1 = new TText(4.8, 500*nDay , Form("smeared 4%% mu at 1 GeV") );
    t1->SetTextSize(0.035);
    t1->Draw();
    t2 = new TText(4.8, 700*nDay , Form("Stat. Error with smearing") );
    t2->SetTextSize(0.035);
    t2->Draw();  
  }

  TLegend* legend; 
  if(thisCase ==1){
  legend = new TLegend(0.58, 0.62, 0.9, 0.9);
  legend->AddEntry(mean1,"nominal","l");
  legend->AddEntry(shift1,"target density","l");
  legend->AddEntry(shift2,"beam width","l");
  legend->AddEntry(shift3,"beam offset x","l");
  legend->AddEntry(shift4,"beam theta","l");
  legend->Draw();
  }
  if(thisCase ==2){
  legend = new TLegend(0.58, 0.62, 0.9, 0.9);
  legend->AddEntry(mean1,"nominal","l");
  legend->AddEntry(shift1,"beam theta phi","l");
  legend->AddEntry(shift2,"horn current","l");
  legend->AddEntry(shift3,"water layer thickness","l");
  legend->AddEntry(shift4,"decay pipe radius","l");
  legend->Draw();
  }  
  if(thisCase ==3){
  legend = new TLegend(0.58, 0.62, 0.9, 0.9);
  legend->AddEntry(mean1,"nominal","l");
  //legend->AddEntry(shift1,"horn 1 x shift 0.5 mm","l");
  legend->AddEntry(shift2,"horn 1 y shift 0.5 mm","l");
  //legend->AddEntry(shift3,"horn 2 x shift 0.5 mm","l");
  legend->AddEntry(shift4,"horn 2 y shift 0.5 mm","l");
  legend->Draw();
  }
  if(thisCase ==4){
  legend = new TLegend(0.58, 0.62, 0.9, 0.9);
  legend->AddEntry(mean1,"nominal","l");
  legend->AddEntry(shift1,"Horn 1 and 2 shift 1mm x and y","l");
  legend->AddEntry(shift2,"Horn 1 and 2 tilt 1mm x and y","l");
  legend->AddEntry(shift3,"horn 1 and 2 tilt 2.5 mm x and y","l");
  legend->Draw();
  }
  if(thisCase ==5){
  legend = new TLegend(0.58, 0.62, 0.9, 0.9);
  legend->AddEntry(mean1,"nominal","l");
  legend->AddEntry(shift1,"Horn 1 only x","l");
  legend->AddEntry(shift2,"Horn 1 only y","l");
  legend->AddEntry(shift3,"Horn 3 x","l");
  legend->AddEntry(shift4,"Horn 3 y","l");
  legend->Draw();
  }  

  TH1D* rshift1 = new TH1D("","",shift1->GetNbinsX(), 0, upperlimit);
  TH1D* rshift2 = new TH1D("","",shift2->GetNbinsX(), 0, upperlimit);
  TH1D* rshift3 = new TH1D("","",shift3->GetNbinsX(), 0, upperlimit);
  TH1D* rshift4 = new TH1D("","",shift4->GetNbinsX(), 0, upperlimit);

  double summ1 = 0;
  double summ2 = 0;
  double summ3 = 0;
  double summ4 = 0;
  double sumpp1[10] = {};
  double sumpp2[10] = {};
  double sumpp3[10] = {};
  double sumpp4[10] = {};
  for(Int_t i=0;i<mean1->GetNbinsX(); i++){
    rshift1->SetBinContent(i+1, (mean1->GetBinContent(i+1) - shift1->GetBinContent(i+1)) / mean1->GetBinError(i+1));
    rshift2->SetBinContent(i+1, (mean1->GetBinContent(i+1) - shift2->GetBinContent(i+1)) / mean1->GetBinError(i+1));
    rshift3->SetBinContent(i+1, (mean1->GetBinContent(i+1) - shift3->GetBinContent(i+1)) / mean1->GetBinError(i+1));
    rshift4->SetBinContent(i+1, (mean1->GetBinContent(i+1) - shift4->GetBinContent(i+1)) / mean1->GetBinError(i+1));

    if(sqrt(mean1->GetBinContent(i+1))>0)
      rshift1->SetBinContent(i+1, (mean1->GetBinContent(i+1) - shift1->GetBinContent(i+1)) / sqrt(mean1->GetBinContent(i+1)));
    if(sqrt(mean1->GetBinContent(i+1))>0)
      rshift2->SetBinContent(i+1, (mean1->GetBinContent(i+1) - shift2->GetBinContent(i+1)) / sqrt(mean1->GetBinContent(i+1)));
    if(sqrt(mean1->GetBinContent(i+1))>0)
      rshift3->SetBinContent(i+1, (mean1->GetBinContent(i+1) - shift3->GetBinContent(i+1)) / sqrt(mean1->GetBinContent(i+1)));
    if(sqrt(mean1->GetBinContent(i+1))>0)
      rshift4->SetBinContent(i+1, (mean1->GetBinContent(i+1) - shift4->GetBinContent(i+1)) / sqrt(mean1->GetBinContent(i+1)));

    summ1 += TMath::Power((mean1->GetBinContent(i+1) - shift1->GetBinContent(i+1)) / mean1->GetBinError(i+1),2);
    summ2 += TMath::Power((mean1->GetBinContent(i+1) - shift2->GetBinContent(i+1)) / mean1->GetBinError(i+1),2);
    summ3 += TMath::Power((mean1->GetBinContent(i+1) - shift3->GetBinContent(i+1)) / mean1->GetBinError(i+1),2);
    summ4 += TMath::Power((mean1->GetBinContent(i+1) - shift4->GetBinContent(i+1)) / mean1->GetBinError(i+1),2);

    if(doStableCheck){
      for(int k=0;k<10;k++){
        sumpp1[k] += TMath::Power((mean1->GetBinContent(i+1) - everySeven1[k]->GetBinContent(i+1)) / mean1->GetBinError(i+1),2);
        sumpp2[k] += TMath::Power((mean1->GetBinContent(i+1) - everySeven2[k]->GetBinContent(i+1)) / mean1->GetBinError(i+1),2);
        sumpp3[k] += TMath::Power((mean1->GetBinContent(i+1) - everySeven3[k]->GetBinContent(i+1)) / mean1->GetBinError(i+1),2);
        sumpp4[k] += TMath::Power((mean1->GetBinContent(i+1) - everySeven4[k]->GetBinContent(i+1)) / mean1->GetBinError(i+1),2);
      } 	      
    }
    
  }

  if(doStableCheck){
    for(int k=0;k<10;k++){
      g1->SetPoint(k,k+1, sqrt(sumpp1[k]));
      g2->SetPoint(k,k+1, sqrt(sumpp2[k]));
      g3->SetPoint(k,k+1, sqrt(sumpp3[k]));
      g4->SetPoint(k,k+1, sqrt(sumpp4[k]));
    }
  }

  std::cout<<"significance of the shifts : "<<sqrt(summ1)<<" "<<sqrt(summ2)<<" "<<sqrt(summ3)<<" "<<sqrt(summ4)<<std::endl;
 
  if(doStableCheck){
    new TCanvas();
    g1->SetLineColor(1);
    g2->SetLineColor(2);
    g3->SetLineColor(3);
    g4->SetLineColor(4);
    g1->SetLineWidth(3);
    g2->SetLineWidth(3);
    g3->SetLineWidth(3);
    g4->SetLineWidth(3);

    g1->GetXaxis()->SetTitle("Test time");
    g1->GetYaxis()->SetTitle("#sqrt{#chi^{2}}");
    g1->SetTitle("Horn 1 along x 0.5 mm");
    g1->Draw("AL");
    //g2->Draw("same");
    //g3->Draw("same");
    //g4->Draw("same");
  }

  new TCanvas();
  rshift1->SetTitle("shifted significance");
  rshift1->SetLineColor(1);
  rshift1->SetLineWidth(3);
  rshift1->SetLineStyle(2);
  //rshift1->Draw("hist");
  rshift2->SetLineColor(2);
  rshift2->SetLineWidth(3);
  rshift2->SetLineStyle(2);
  rshift2->Draw("hist ");
  rshift3->SetLineColor(3);
  rshift3->SetLineWidth(3);
  rshift3->SetLineStyle(2);
  //rshift3->Draw("hist same");
  rshift4->SetLineColor(4);
  rshift4->SetLineWidth(3);
  rshift4->SetLineStyle(2);
  rshift4->Draw("hist same");
  rshift1->GetXaxis()->SetTitle("Energy (GeV)");
  rshift1->GetYaxis()->SetTitle("Significance #sqrt{#chi^{2}}");
  rshift2->GetXaxis()->SetTitle("Energy (GeV)");
  rshift2->GetYaxis()->SetTitle("Significance #sqrt{#chi^{2}}");

  if(thisCase ==1){
  legend = new TLegend(0.58, 0.62, 0.9, 0.9);
  legend->AddEntry(rshift1,"target density","l");
  legend->AddEntry(rshift2,"beam width","l");
  legend->AddEntry(rshift3,"beam offset x","l");
  legend->AddEntry(rshift4,"beam theta","l");
  legend->Draw();
  }
  if(thisCase ==2){
  legend = new TLegend(0.58, 0.62, 0.9, 0.9);
  legend->AddEntry(rshift1,"beam theta phi","l");
  legend->AddEntry(rshift2,"horn current","l");
  legend->AddEntry(rshift3,"water layer","l");
  legend->AddEntry(rshift4,"decay pipe radius","l");
  legend->Draw();
  }
  if(thisCase ==3){
  legend = new TLegend(0.58, 0.62, 0.9, 0.9);
  //legend->AddEntry(rshift1,"horn 1 x shift 0.5 mm","l");
  legend->AddEntry(rshift2,"horn 1 y shift 0.5 mm","l");
  //legend->AddEntry(rshift3,"horn 2 x shift 0.5 mm","l");
  legend->AddEntry(rshift4,"horn 2 y shift 0.5 mm","l");
  legend->Draw();
  }
  if(thisCase ==4){
  legend = new TLegend(0.58, 0.62, 0.9, 0.9);
  legend->AddEntry(rshift1,"Horn 1 and 2 shift 1mm x and y","l");
  legend->AddEntry(rshift2,"Horn 1 and 2 tilt 1mm x and y","l");
  legend->AddEntry(rshift3,"horn 1 and 2 tilt 2.5 mm x and y","l");
  legend->Draw();
  }
  if(thisCase ==5){
  legend = new TLegend(0.58, 0.62, 0.9, 0.9);
  legend->AddEntry(rshift1,"Horn 1 only x","l");
  legend->AddEntry(rshift2,"Horn 1 only y","l");
  legend->AddEntry(rshift3,"Horn 3 x","l");
  legend->AddEntry(rshift4,"Horn 3 y","l");
  legend->Draw();
  }

/* 
  //int compare = 1;
  //if(compare == 1){
    TFile ff(Form("%s",gApplication->Argv(5)));
    TH1D* mean11 = (TH1D*)ff.Get("Mean_E_reco_Energy_Spectrum_per_Day");

    cout<<"point 3"<<endl;
    TH1D* shift11;
    TH1D* shift12;
    shift11 = (TH1D*)ff.Get("Mean_E_reco_shift1_Energy_Spectrum_per_Day(M)");
    shift12 = (TH1D*)ff.Get("Mean_E_reco_shift2_Energy_Spectrum_per_Day(M)");

    for(Int_t i=0;i<mean11->GetNbinsX(); i++){
      mean11->SetBinError(i+1, mean11->GetBinError(i+1)* (1./TMath::Sqrt(nDay)) );
      shift11->SetBinError(i+1, shift11->GetBinError(i+1)* (1./TMath::Sqrt(nDay)) );
      shift12->SetBinError(i+1, shift12->GetBinError(i+1)* (1./TMath::Sqrt(nDay)) );
    }
  
    TH1D* rshift11 = new TH1D("","",shift11->GetNbinsX(), 0, 10);
    TH1D* rshift12 = new TH1D("","",shift12->GetNbinsX(), 0, 10);

    for(Int_t i=0;i<mean11->GetNbinsX(); i++){
      rshift11->SetBinContent(i+1, (mean11->GetBinContent(i+1) - shift11->GetBinContent(i+1)) / mean11->GetBinError(i+1));
      rshift12->SetBinContent(i+1, (mean11->GetBinContent(i+1) - shift12->GetBinContent(i+1)) / mean11->GetBinError(i+1));
    }

    new TCanvas();
    rshift11->SetTitle("Stat. Error and detector effect (smearing + efficiency applied)");
    rshift11->SetLineColor(2);
    rshift11->SetLineWidth(3);
    rshift11->SetLineStyle(1);
    rshift11->Draw("hist");
    rshift12->SetLineColor(3);
    rshift12->SetLineWidth(3);
    rshift12->SetLineStyle(1);
    rshift12->Draw("hist same");
    rshift1->Draw("hist same");
    rshift2->Draw("hist same");
    rshift11->GetXaxis()->SetTitle("Energy (GeV)");
    rshift11->GetYaxis()->SetTitle("Pull (Significance)");

    TF1* line1 = new TF1("","0",0,10);
    line1->SetLineWidth(3);
    line1->Draw("same");

    legend = new TLegend(0.58, 0.62, 0.9, 0.9);
    legend->AddEntry(rshift1,"target density 1 #sigma neutrino reconstructed","l");
    legend->AddEntry(rshift1,"Horn Y 1 #sigma neutrino reconstructed","l");
    legend->AddEntry(rshift11,"target density 1 #sigma neutrino reconstructed 30% muon p res.","l");
    legend->AddEntry(rshift12,"Horn Y 1 #sigma neutrino reconstructed 30% muon p res.","l");
    legend->Draw();

    //}
*/
}
