{
  #include <iostream>
  using namespace std;

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

  float vtx[3];
  float hadCollar_side[4];
  float lepCollar_side[4];
  int lepPdg;
  float p3lep[3];
  float lepKE;
  float muExitPt[3];
  float muExitMom[3];

  TH2D* h1 = new TH2D("","",50,-120,120,50,-100,100);
  TH2D* h2 = new TH2D("","",50,-120,120,50,-100,100);
  TH2D* h3 = new TH2D("","",50,-120,120,50,-100,100);
  TH2D* h4 = new TH2D("","",50,-120,120,50,-100,100);

  TH2D* hh1 = new TH2D("","",50,-120,120,50,-100,100);
  TH2D* hh2 = new TH2D("","",50,-120,120,50,-100,100);
  TH2D* hh3 = new TH2D("","",50,-120,120,50,-100,100);
  TH2D* hh4 = new TH2D("","",50,-120,120,50,-100,100);

  TH2D* hhh1 = new TH2D("","",50,0,3000,50,-1,1);
  TH2D* hhh2 = new TH2D("","",50,0,3000,50,-1,1);
  TH2D* hhh3 = new TH2D("","",50,0,3000,50,-1,1);
  TH2D* hhh4 = new TH2D("","",50,0,3000,50,-1,1);

  TH2D* hhhh1 = new TH2D("","",50,-100,100,50,-1,1);
  TH2D* hhhh2 = new TH2D("","",50,-100,100,50,-1,1);
  TH2D* hhhh3 = new TH2D("","",50,-100,100,50,-1,1);
  TH2D* hhhh4 = new TH2D("","",50,-100,100,50,-1,1);

  TH2D* sh1 = new TH2D("","",50,-120,120,50,-100,100);
  TH2D* sh2 = new TH2D("","",50,-120,120,50,-100,100);
  TH2D* sh3 = new TH2D("","",50,-120,120,50,-100,100);
  TH2D* sh4 = new TH2D("","",50,-120,120,50,-100,100);

  TH2D* shh1 = new TH2D("","",50,-120,120,50,-100,100);
  TH2D* shh2 = new TH2D("","",50,-120,120,50,-100,100);
  TH2D* shh3 = new TH2D("","",50,-120,120,50,-100,100);
  TH2D* shh4 = new TH2D("","",50,-120,120,50,-100,100);

  TH2D* shhh1 = new TH2D("","",50,0,3000,50,-1,1);
  TH2D* shhh2 = new TH2D("","",50,0,3000,50,-1,1);
  TH2D* shhh3 = new TH2D("","",50,0,3000,50,-1,1);
  TH2D* shhh4 = new TH2D("","",50,0,3000,50,-1,1);

  TH2D* shhhh1 = new TH2D("","",50,-100,100,50,-1,1);
  TH2D* shhhh2 = new TH2D("","",50,-100,100,50,-1,1);
  TH2D* shhhh3 = new TH2D("","",50,-100,100,50,-1,1);
  TH2D* shhhh4 = new TH2D("","",50,-100,100,50,-1,1);

  TH2D* ex1 = new TH2D("","",50,-120,120,50,-120,120);
  TH2D* ex11 = new TH2D("","",50,-120,120,50,-100,100);
  TH2D* ex12 = new TH2D("","",50,-120,120,50,-100,100);
  TH2D* ex2 = new TH2D("","",50,-120,120,50,0,3000);
  TH2D* ex3 = new TH2D("","",50,-120,120,50,0,3000);
  TH2D* ex4 = new TH2D("","",50,-120,120,50,0,3000);

  TH2D* exx1 = new TH2D("","",50,-1,1,50,-120,120);
  TH2D* exx2 = new TH2D("","",50,-1,1,50,-120,120);
  TH2D* exx3 = new TH2D("","",50,-1,1,50,-120,120);
  TH2D* exx4 = new TH2D("","",50,-1,1,50,0,3000);

  TH2D* muon1 = new TH2D("","",50,0,10000,50,-1,1);
  TH1D* muon2 = new TH1D("","",100,0,10000);
  TH1D* muon3 = new TH1D("","",100,0,10000);

  TChain t("tree");
  t.Add("/home/guang/work/DUNE3dstTools/data/PROD101/FHC_*.root");
  t.SetBranchAddress("vtx",&vtx);
  t.SetBranchAddress("hadCollar_side",&hadCollar_side);
  t.SetBranchAddress("lepCollar_side",&lepCollar_side);
  t.SetBranchAddress("p3lep",&p3lep);
  t.SetBranchAddress("lepPdg",&lepPdg);
  t.SetBranchAddress("lepKE",&lepKE);
  t.SetBranchAddress("muonExitPt",&muExitPt);
  t.SetBranchAddress("muonExitMom",&muExitMom);

  double scale = 0;
  double sscale = 0;

  for(Int_t i=0;i<t.GetEntries();i++){

    t.GetEntry(i);

    std::cout<<"event number "<<i<<std::endl; 

    cout<<vtx[0]<<" "<<vtx[1]<<" "<<vtx[2]<<endl;

    if(abs(lepPdg) == 13 && abs(vtx[0])<110 && abs(vtx[1])<110 && abs(vtx[2])<90){

      double ang = 0;
      double mom = 0;
      h1->Fill(vtx[0],vtx[2]);

      ang = p3lep[2]/sqrt(p3lep[0]*p3lep[0] + p3lep[1]*p3lep[1] + p3lep[2]*p3lep[2]);
      mom = lepKE; //sqrt(p3lep[0]*p3lep[0] + p3lep[1]*p3lep[1] + p3lep[2]*p3lep[2]);
      hhh1->Fill(mom, ang);
      hhhh1->Fill(vtx[2], ang);

      //muon1->Fill(sqrt(p3lep[0]*p3lep[0] + p3lep[1]*p3lep[1] + p3lep[2]*p3lep[2]),ang);
      muon1->Fill(mom, ang);
      muon2->Fill(sqrt(p3lep[0]*p3lep[0] + p3lep[1]*p3lep[1] + p3lep[2]*p3lep[2]));
      if(sqrt(muExitMom[0]*muExitMom[0]+muExitMom[1]*muExitMom[1]+muExitMom[2]*muExitMom[2])>0)
      muon3->Fill(sqrt(muExitMom[0]*muExitMom[0]+muExitMom[1]*muExitMom[1]+muExitMom[2]*muExitMom[2]));

      if(hadCollar_side[0] < 20 && hadCollar_side[1] < 20 && hadCollar_side[2] < 20 ){
	h2->Fill(vtx[0],vtx[2]);
        hh2->Fill(vtx[0],vtx[2]);
	//ang = p3lep[2]/sqrt(p3lep[0]*p3lep[0] + p3lep[1]*p3lep[1] + p3lep[2]*p3lep[2]);
	//mom = sqrt(p3lep[0]*p3lep[0] + p3lep[1]*p3lep[1] + p3lep[2]*p3lep[2]);
	hhh2->Fill(mom,ang);
        hhhh2->Fill(vtx[2],ang);
      }
      if(lepCollar_side[0] < 1 && lepCollar_side[1] <1 && lepCollar_side[2] < 1 ){
        h3->Fill(vtx[0],vtx[2]);
        hh3->Fill(vtx[0],vtx[2]);
        //ang = p3lep[2]/sqrt(p3lep[0]*p3lep[0] + p3lep[1]*p3lep[1] + p3lep[2]*p3lep[2]);
        //mom = sqrt(p3lep[0]*p3lep[0] + p3lep[1]*p3lep[1] + p3lep[2]*p3lep[2]);
        hhh3->Fill(mom,ang);
	hhhh3->Fill(vtx[2],ang);
      }
      if(hadCollar_side[0] < 20 && hadCollar_side[1] < 20 && hadCollar_side[2] < 20 && lepCollar_side[0] < 1 && lepCollar_side[1] < 1 && lepCollar_side[2] < 1 ){
        h4->Fill(vtx[0],vtx[2]);
        hh4->Fill(vtx[0],vtx[2]);
        //ang = p3lep[2]/sqrt(p3lep[0]*p3lep[0] + p3lep[1]*p3lep[1] + p3lep[2]*p3lep[2]);
        //mom = sqrt(p3lep[0]*p3lep[0] + p3lep[1]*p3lep[1] + p3lep[2]*p3lep[2]);
        hhh4->Fill(mom,ang);
	hhhh4->Fill(vtx[2],ang);
      }
      scale ++;
    }

    if(abs(lepPdg) == 13 && abs(vtx[0])<50 && abs(vtx[1])<50 && abs(vtx[2])<50 ){

      double ang = 0;
      double mom = 0;
      sh1->Fill(vtx[0],vtx[2]);

      ang = p3lep[2]/sqrt(p3lep[0]*p3lep[0] + p3lep[1]*p3lep[1] + p3lep[2]*p3lep[2]);
      mom = lepKE; 
      shhh1->Fill(mom, ang);
      shhhh1->Fill(vtx[2], ang);

      if(hadCollar_side[0] < 20 && hadCollar_side[1] < 20 && hadCollar_side[2] < 20 ){
        sh2->Fill(vtx[0],vtx[2]);
        shh2->Fill(vtx[0],vtx[2]);
        shhh2->Fill(mom,ang);
        shhhh2->Fill(vtx[2],ang);
      }
      if(lepCollar_side[1] < 1 ){ //&& lepCollar_side[1] < 1 && lepCollar_side[2] < 10 ){
        sh3->Fill(vtx[0],vtx[2]);
        shh3->Fill(vtx[0],vtx[2]);
        shhh3->Fill(mom,ang);
        shhhh3->Fill(vtx[2],ang);
      }
      if(hadCollar_side[0] < 20 && hadCollar_side[1] < 20 && hadCollar_side[2] < 20 && lepCollar_side[0] < 1 && lepCollar_side[1] < 1 && lepCollar_side[2] < 1 ){
        sh4->Fill(vtx[0],vtx[2]);
        shh4->Fill(vtx[0],vtx[2]);
        shhh4->Fill(mom,ang);
        shhhh4->Fill(vtx[2],ang);
      }
      double tMom = sqrt(muExitMom[0]*muExitMom[0]+muExitMom[1]*muExitMom[1]+muExitMom[2]*muExitMom[2]);
      if(lepCollar_side[1] > 1 && ang>0.9 ){
        ex1->Fill(muExitPt[0],muExitPt[1]);
	ex11->Fill(muExitPt[0],muExitPt[2]);
	ex12->Fill(muExitPt[1],muExitPt[2]);
        ex2->Fill(muExitPt[0],tMom); 
        ex3->Fill(muExitPt[1],tMom);
        ex4->Fill(muExitPt[2],tMom);
      }
      if(lepCollar_side[1] > 1  ){
        exx1->Fill(ang,muExitPt[0]);
        exx2->Fill(ang,muExitPt[1]);
        exx3->Fill(ang,muExitPt[2]);
        exx4->Fill(ang,tMom);
      }

      sscale ++;
    }  
  }

  scale = 13600000./ scale;
  sscale = 13600000./ (8.7 * sscale);

  for(Int_t i=0;i<h1->GetNbinsX();i++){
    for(Int_t j=0;j<h1->GetNbinsY();j++){
      if(h1->GetBinContent(i+1,j+1)>0){
        h2->SetBinContent(i+1,j+1,h2->GetBinContent(i+1,j+1)/h1->GetBinContent(i+1,j+1));
        h3->SetBinContent(i+1,j+1,h3->GetBinContent(i+1,j+1)/h1->GetBinContent(i+1,j+1));
        h4->SetBinContent(i+1,j+1,h4->GetBinContent(i+1,j+1)/h1->GetBinContent(i+1,j+1));
      }
    }
  }

  for(Int_t i=0;i<hh1->GetNbinsX();i++){
    for(Int_t j=0;j<hh1->GetNbinsY();j++){
      hh2->SetBinContent(i+1,j+1,hh2->GetBinContent(i+1,j+1)*scale*(1-h2->GetBinContent(i+1,j+1)));
      hh3->SetBinContent(i+1,j+1,hh3->GetBinContent(i+1,j+1)*scale*(1-h3->GetBinContent(i+1,j+1)));
      hh4->SetBinContent(i+1,j+1,hh4->GetBinContent(i+1,j+1)*scale*(1-h4->GetBinContent(i+1,j+1)));
    }
  }

  for(Int_t i=0;i<hhh1->GetNbinsX();i++){
    for(Int_t j=0;j<hhh1->GetNbinsY();j++){
      if(hhh1->GetBinContent(i+1,j+1)>0){
        hhh2->SetBinContent(i+1,j+1,hhh2->GetBinContent(i+1,j+1)/hhh1->GetBinContent(i+1,j+1));
        hhh3->SetBinContent(i+1,j+1,hhh3->GetBinContent(i+1,j+1)/hhh1->GetBinContent(i+1,j+1));
        hhh4->SetBinContent(i+1,j+1,hhh4->GetBinContent(i+1,j+1)/hhh1->GetBinContent(i+1,j+1));
      }
    }
  }

  for(Int_t i=0;i<hhhh1->GetNbinsX();i++){
    for(Int_t j=0;j<hhhh1->GetNbinsY();j++){
      if(hhhh1->GetBinContent(i+1,j+1)>0){
        hhhh2->SetBinContent(i+1,j+1,hhhh2->GetBinContent(i+1,j+1)/hhhh1->GetBinContent(i+1,j+1));
        hhhh3->SetBinContent(i+1,j+1,hhhh3->GetBinContent(i+1,j+1)/hhhh1->GetBinContent(i+1,j+1));
        hhhh4->SetBinContent(i+1,j+1,hhhh4->GetBinContent(i+1,j+1)/hhhh1->GetBinContent(i+1,j+1));
      }
    }
  }

  for(Int_t i=0;i<sh1->GetNbinsX();i++){
    for(Int_t j=0;j<sh1->GetNbinsY();j++){
      if(sh1->GetBinContent(i+1,j+1)>0){
        sh2->SetBinContent(i+1,j+1,sh2->GetBinContent(i+1,j+1)/sh1->GetBinContent(i+1,j+1));
        sh3->SetBinContent(i+1,j+1,sh3->GetBinContent(i+1,j+1)/sh1->GetBinContent(i+1,j+1));
        sh4->SetBinContent(i+1,j+1,sh4->GetBinContent(i+1,j+1)/sh1->GetBinContent(i+1,j+1));
      }
    }
  }

  for(Int_t i=0;i<shh1->GetNbinsX();i++){
    for(Int_t j=0;j<shh1->GetNbinsY();j++){
      shh2->SetBinContent(i+1,j+1,shh2->GetBinContent(i+1,j+1)*sscale*(1-sh2->GetBinContent(i+1,j+1)));
      shh3->SetBinContent(i+1,j+1,shh3->GetBinContent(i+1,j+1)*sscale*(1-sh3->GetBinContent(i+1,j+1)));
      shh4->SetBinContent(i+1,j+1,shh4->GetBinContent(i+1,j+1)*sscale*(1-sh4->GetBinContent(i+1,j+1)));
    }
  }

  for(Int_t i=0;i<shhh1->GetNbinsX();i++){
    for(Int_t j=0;j<shhh1->GetNbinsY();j++){
      if(shhh1->GetBinContent(i+1,j+1)>0){
        shhh2->SetBinContent(i+1,j+1,shhh2->GetBinContent(i+1,j+1)/shhh1->GetBinContent(i+1,j+1));
        shhh3->SetBinContent(i+1,j+1,shhh3->GetBinContent(i+1,j+1)/shhh1->GetBinContent(i+1,j+1));
        shhh4->SetBinContent(i+1,j+1,shhh4->GetBinContent(i+1,j+1)/shhh1->GetBinContent(i+1,j+1));
      }
    }
  }

  for(Int_t i=0;i<shhhh1->GetNbinsX();i++){
    for(Int_t j=0;j<shhhh1->GetNbinsY();j++){
      if(shhhh1->GetBinContent(i+1,j+1)>0){
        shhhh2->SetBinContent(i+1,j+1,shhhh2->GetBinContent(i+1,j+1)/shhhh1->GetBinContent(i+1,j+1));
        shhhh3->SetBinContent(i+1,j+1,shhhh3->GetBinContent(i+1,j+1)/shhhh1->GetBinContent(i+1,j+1));
        shhhh4->SetBinContent(i+1,j+1,shhhh4->GetBinContent(i+1,j+1)/shhhh1->GetBinContent(i+1,j+1));
      }
    }
  }

  new TCanvas();
  muon1->GetXaxis()->SetTitle("muon KE (MeV)");
  muon1->GetYaxis()->SetTitle("cos#theta");
  muon1->Draw("colz");


  std::cout<<muon2->GetMean()<<" "<<muon3->GetMean()<<std::endl;
  new TCanvas();
  muon2->SetLineColor(2);
  muon2->Draw("hist");
  muon2->GetXaxis()->SetTitle("muon momentum (MeV)");
  muon2->GetYaxis()->SetTitle("Events");  
  muon3->SetLineColor(4);
  muon3->Draw("same");
  TLegend* leg = new TLegend(0.6,0.68,0.9,0.9,NULL,"brNDC");
  leg->AddEntry(muon2 ,"inital muon momentum","l");
  leg->AddEntry(muon3 ,"exiting muon momentum","l");
  leg->SetBorderSize(2);
  leg->SetTextFont(62);
  leg->SetFillColor(1);
  leg->SetLineColor(1);
  leg->SetShadowColor(0);
  leg->SetLineStyle(1);
  leg->SetLineWidth(2);
  leg->SetFillColor(0);
  leg->SetFillStyle(1001);
  leg->Draw();

/*
  TCanvas* c1 = new TCanvas();
  c1->Divide(2,2);
  c1->cd(1);
  h2->SetTitle("had. contained fraction");
  h2->GetXaxis()->SetTitle("x [cm]");
  h2->GetYaxis()->SetTitle("z [cm]");
  h2->Draw("colz");

  c1->cd(2);
  h3->SetTitle("lep. contained fraction");
  h3->GetXaxis()->SetTitle("x [cm]");
  h3->GetYaxis()->SetTitle("z [cm]");
  h3->Draw("colz");

  c1->cd(3);
  h4->SetTitle("had. or lep. cont. frac.");
  h4->GetXaxis()->SetTitle("x [cm]");
  h4->GetYaxis()->SetTitle("z [cm]");
  h4->Draw("colz");

  TCanvas* c2 = new TCanvas();
  c2->Divide(2,2);
  c2->cd(1);
  hh2->SetTitle("had. cont. yearly loss");
  hh2->GetXaxis()->SetTitle("x [cm]");
  hh2->GetYaxis()->SetTitle("z [cm]");
  hh2->Draw("colz");

  c2->cd(2);
  hh3->SetTitle("lep. cont. yearly loss");
  hh3->GetXaxis()->SetTitle("x [cm]");
  hh3->GetYaxis()->SetTitle("z [cm]");
  hh3->Draw("colz");

  c2->cd(3);
  hh4->SetTitle("had. or lep. cont. yearly loss");
  hh4->GetXaxis()->SetTitle("x [cm]");
  hh4->GetYaxis()->SetTitle("z [cm]");
  hh4->Draw("colz");

  TCanvas* c3 = new TCanvas();
  c3->Divide(2,2);
  c3->cd(1);
  hhh2->SetTitle("had. cont. phase space cov.");
  hhh2->GetXaxis()->SetTitle("kineticEnergy [MeV]");
  hhh2->GetYaxis()->SetTitle("cos#theta");
  hhh2->Draw("colz");

  c3->cd(2);
  hhh3->SetTitle("lep. cont. phase space cov.");
  hhh3->GetXaxis()->SetTitle("kineticEnergy [MeV]");
  hhh3->GetYaxis()->SetTitle("cos#theta");
  hhh3->Draw("colz");

  c3->cd(3);
  hhh4->SetTitle("had. or lep. phase space cov.");
  hhh4->GetXaxis()->SetTitle("kineticEnergy [MeV]");
  hhh4->GetYaxis()->SetTitle("cos#theta");
  hhh4->Draw("colz");

  TCanvas* c4 = new TCanvas();
  c4->Divide(2,2);
  c4->cd(1);
  hhhh2->SetTitle("had. cont. phase space cov.");
  hhhh2->GetXaxis()->SetTitle("z [cm]");
  hhhh2->GetYaxis()->SetTitle("cos#theta");
  hhhh2->Draw("colz");

  c4->cd(2);
  hhhh3->SetTitle("lep. cont. phase space cov.");
  hhhh3->GetXaxis()->SetTitle("z [cm]");
  hhhh3->GetYaxis()->SetTitle("cos#theta");
  hhhh3->Draw("colz");

  c4->cd(3);
  hhhh4->SetTitle("had. or lep. phase space cov.");
  hhhh4->GetXaxis()->SetTitle("z [cm]");
  hhhh4->GetYaxis()->SetTitle("cos#theta");
  hhhh4->Draw("colz");

  TCanvas* c11 = new TCanvas();
  c11->Divide(2,2);
  c11->cd(1);
  sh2->SetTitle("had. contained fraction");
  sh2->GetXaxis()->SetTitle("x [cm]");
  sh2->GetYaxis()->SetTitle("z [cm]");
  sh2->Draw("colz");

  c11->cd(2);
  sh3->SetTitle("lep. contained fraction");
  sh3->GetXaxis()->SetTitle("x [cm]");
  sh3->GetYaxis()->SetTitle("z [cm]");
  sh3->Draw("colz");

  c11->cd(3);
  sh4->SetTitle("had. or lep. cont. frac.");
  sh4->GetXaxis()->SetTitle("x [cm]");
  sh4->GetYaxis()->SetTitle("z [cm]");
  sh4->Draw("colz");

  TCanvas* c12 = new TCanvas();
  c12->Divide(2,2);
  c12->cd(1);
  shh2->SetTitle("had. cont. yearly loss");
  shh2->GetXaxis()->SetTitle("x [cm]");
  shh2->GetYaxis()->SetTitle("z [cm]");
  shh2->Draw("colz");

  c12->cd(2);
  shh3->SetTitle("lep. cont. yearly loss");
  shh3->GetXaxis()->SetTitle("x [cm]");
  shh3->GetYaxis()->SetTitle("z [cm]");
  shh3->Draw("colz");

  c12->cd(3);
  shh4->SetTitle("had. or lep. cont. yearly loss");
  shh4->GetXaxis()->SetTitle("x [cm]");
  shh4->GetYaxis()->SetTitle("z [cm]");
  shh4->Draw("colz");

  TCanvas* c13 = new TCanvas();
  c13->Divide(2,2);
  c13->cd(1);
  shhh2->SetTitle("1x1x1 had. cont. phase space cov.");
  shhh2->GetXaxis()->SetTitle("kineticEnergy [MeV]");
  shhh2->GetYaxis()->SetTitle("cos#theta");
  shhh2->Draw("colz");

  c13->cd(2);
  shhh3->SetTitle("1x1x1 lep. cont. phase space cov.");
  shhh3->GetXaxis()->SetTitle("kineticEnergy [MeV]");
  shhh3->GetYaxis()->SetTitle("cos#theta");
  shhh3->Draw("colz");

  c13->cd(3);
  shhh4->SetTitle("1x1x1 had. or lep. phase space cov.");
  shhh4->GetXaxis()->SetTitle("kineticEnergy [MeV]");
  shhh4->GetYaxis()->SetTitle("cos#theta");
  shhh4->Draw("colz");

  TCanvas* c14 = new TCanvas();
  c14->Divide(2,2);
  c14->cd(1);
  shhhh2->SetTitle("had. cont. phase space cov.");
  shhhh2->GetXaxis()->SetTitle("z [cm]");
  shhhh2->GetYaxis()->SetTitle("cos#theta");
  shhhh2->Draw("colz");

  c14->cd(2);
  shhhh3->SetTitle("lep. cont. phase space cov.");
  shhhh3->GetXaxis()->SetTitle("z [cm]");
  shhhh3->GetYaxis()->SetTitle("cos#theta");
  shhhh3->Draw("colz");

  c14->cd(3);
  shhhh4->SetTitle("had. or lep. phase space cov.");
  shhhh4->GetXaxis()->SetTitle("z [cm]");
  shhhh4->GetYaxis()->SetTitle("cos#theta");
  shhhh4->Draw("colz");

  TCanvas* c15 = new TCanvas();
  c15->Divide(3,2);
  c15->cd(1);
  ex1->Draw("colz");
  c15->cd(2);
  ex11->Draw("colz");
  c15->cd(3);
  ex12->Draw("colz");
  c15->cd(4);
  ex2->Draw("colz");
  c15->cd(5);
  ex3->Draw("colz");
  c15->cd(6);
  ex4->Draw("colz");

  TCanvas* c16 = new TCanvas();
  c16->Divide(3,2);
  c16->cd(1);
  exx1->Draw("colz");
  c16->cd(2);
  exx2->Draw("colz");
  c16->cd(3);
  exx3->Draw("colz");
  c16->cd(4);
  exx4->Draw("colz");
*/
}

