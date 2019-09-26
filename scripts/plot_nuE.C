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


  TChain t("tree");
  //t.Add("/pnfs/dune/persistent/users/gyang/3DST/dump/standardGeo10/PROD101/FHC_*.root");
  t.Add("/home/guang/work/DUNE3dstTools/data/PROD101/FHC_*.root");

  Float_t vtx[3]; 
  Int_t lepPdg;
  Float_t lepKE, hadTot_TPC, hadTot_3DST, hadTot_ECAL, hadTot_allECAL, hadTot_leak;

  TH2D* h2_1 = new TH2D("lepKEvsLeak","lepKEvsLeak",40,0,6000,50,0,200);
  TH2D* h2_2 = new TH2D("lepKEvs3DST","lepKEvs3DST",40,0,6000,50,0,5000);
  TH2D* h2_3 = new TH2D("lepKEvsAllECAL","lepKEvsAllECAL",40,0,6000,50,0,6000);

  TH2D* h2_11 = new TH2D("lepKEvsLeak_descoped","lepKEvsLeak_descoped",40,0,6000,50,0,200);
  TH2D* h2_12 = new TH2D("lepKEvs3DST_descoped","lepKEvs3DST_descoped",40,0,6000,50,0,5000);
  TH2D* h2_13 = new TH2D("lepKEvsAllECAL_descoped","lepKEvsAllECAL_descoped",40,0,6000,50,0,6000);

  TH1D* h1_1 = new TH1D("lepKE_descoped","lepKE_5percent_descoped",20,0,6000);
  TH1D* h1_2 = new TH1D("lepKE","lepKE_5percent",20,0,6000);

  TH1D* h1_3 = new TH1D("lepKE_descoped","lepKE_5percent_descoped",20,0,6000);
  TH1D* h1_4 = new TH1D("lepKE","lepKE_5percent",20,0,6000);

  t.SetBranchAddress("vtx", &vtx);
  t.SetBranchAddress("lepPdg", &lepPdg);
  t.SetBranchAddress("lepKE", &lepKE);
  t.SetBranchAddress("hadTot_TPC", &hadTot_TPC);
  t.SetBranchAddress("hadTot_3DST", &hadTot_3DST);
  t.SetBranchAddress("hadTot_ECAL", &hadTot_ECAL);
  t.SetBranchAddress("hadTot_allECAL", &hadTot_allECAL);
  t.SetBranchAddress("hadTot_leak", &hadTot_leak);

  for(Int_t i =0;i<t.GetEntries();i++){

    t.GetEntry(i);

    //cout<<"vtx "<<vtx[0]<<" "<<vtx[1]<<" "<<vtx[2]<<endl;
    //cout<<"lepKE and hadTot_leak "<<lepKE<<" "<<hadTot_leak<<endl;

    if(abs(vtx[0])<50 && abs(vtx[1])<50 && abs(vtx[2])<50 && lepPdg == 11 ){
      h2_11->Fill(lepKE, hadTot_leak);
      h2_12->Fill(lepKE, hadTot_3DST);
      h2_13->Fill(lepKE, hadTot_allECAL);
      h1_3->Fill(lepKE);   
      if(hadTot_leak/lepKE < 0.1) {
	h1_1->Fill(lepKE);      
      }
    }    

    if(abs(vtx[0])<110 && abs(vtx[1])<110 && abs(vtx[2])<90 && lepPdg == 11 ){
      h2_1->Fill(lepKE, hadTot_leak);
      h2_2->Fill(lepKE, hadTot_3DST);
      h2_3->Fill(lepKE, hadTot_allECAL);
      h1_4->Fill(lepKE);
      if(hadTot_leak/lepKE < 0.1) {
        h1_2->Fill(lepKE);
      }
    }
  }


  new TCanvas();
  h2_11->GetXaxis()->SetTitle("Electron Energy (MeV)");
  h2_11->GetYaxis()->SetTitle("leaking energy (MeV)");
  h2_11->Draw("colz");

  TCanvas* c1 = new TCanvas();
  c1->Divide(2,1);
  c1->cd(1);
  h2_11->ProjectionX()->Draw();
  c1->cd(2);
  h2_11->ProjectionY()->Draw();

  new TCanvas();
  h2_12->GetXaxis()->SetTitle("Electron Energy (MeV)");
  h2_12->GetYaxis()->SetTitle("leaking energy (MeV)");
  h2_12->Draw("colz");

  new TCanvas();
  h2_13->GetXaxis()->SetTitle("Electron Energy (MeV)");
  h2_13->GetYaxis()->SetTitle("leaking energy (MeV)");
  h2_13->Draw("colz");

  new TCanvas();
  h2_1->GetXaxis()->SetTitle("Electron Energy (MeV)");
  h2_1->GetYaxis()->SetTitle("leaking energy (MeV)");
  h2_1->Draw("colz");

  new TCanvas();
  h2_2->GetXaxis()->SetTitle("Electron Energy (MeV)");
  h2_2->GetYaxis()->SetTitle("leaking energy (MeV)");
  h2_2->Draw("colz");

  new TCanvas();
  h2_3->GetXaxis()->SetTitle("Electron Energy (MeV)");
  h2_3->GetYaxis()->SetTitle("leaking energy (MeV)");
  h2_3->Draw("colz");

  new TCanvas();
  h2_11->GetXaxis()->SetTitle("Electron Energy (MeV)");
  h2_11->GetYaxis()->SetTitle("leaking energy (MeV)");
  h2_11->Draw("colz");

  h1_2->Divide(h1_4);
  h1_1->Divide(h1_3);

  new TCanvas();
  h1_1->SetTitle("Fraction of 90% contained");
  h1_1->GetXaxis()->SetTitle("Electron Energy (MeV)");
  h1_1->GetYaxis()->SetTitle("Contained fraction");
  h1_1->SetLineWidth(3);
  h1_1->Draw("hist");
  h1_2->SetLineWidth(3);
  h1_2->SetLineColor(2);
  h1_2->Draw("same");

  TLegend* leg = new TLegend(0.6,0.68,0.9,0.9,NULL,"brNDC");
  leg->AddEntry(h1_1 ,"FV 100x100x100 cm^3","l");
  leg->AddEntry(h1_2 ,"FV 220x220x180 cm^3","l");
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

}
