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

  double sRes = 3e-3;
  double factor1 = 0.3;
  double Bfield = 0.4;
  double TrackLength = 1;
  double factor2 = 720;
  double nPoint = 100;
  double factor3 = 4;
  double factor4 = 0.045;
  double radiationLength = 0.4;

  //TF1* fun1 = new TF1("","x*radiationLength",0.1,10);
  //TF1* fun1 = new TF1("","TMath::Sqrt(TMath::Power((sRes*x)/(factor1*Bfield*TMath::Power(TrackLength,2))*TMath::Sqrt(factor2/(nPoint + factor3)),2) + TMath::Power(factor4*(1./Bfield*TMath::Sqrt(TrackLength*radiationLength)),2) )",0.1,10);
  TF1* fun1 = new TF1("Total","TMath::Sqrt(TMath::Power((0.003*x)/(0.3*0.6*TMath::Power(1.5,2))*TMath::Sqrt(720/(150.6)),2) + TMath::Power(0.045*(1./(0.6*TMath::Sqrt(1.5*0.6))),2))",0.1,10);
  TF1* fun2 = new TF1("MCS","TMath::Sqrt(TMath::Power(0.045*(1./(0.6*TMath::Sqrt(1.5*0.6))),2))",0.1,10);
  TF1* fun3 = new TF1("Point resolution","TMath::Sqrt(TMath::Power((0.003*x)/(0.3*0.6*TMath::Power(1.5,2))*TMath::Sqrt(720/(150.6)),2))",0.1,10);

  new TCanvas();
  fun1->SetLineColor(4);
  fun1->SetLineWidth(3);
  fun2->SetLineColor(1);
  fun3->SetLineColor(2);
  fun1->Draw();
  fun2->Draw("same");
  fun3->Draw("same");

  fun1->GetXaxis()->SetTitle("momentum (GeV)");
  fun1->GetYaxis()->SetTitle("dP/P");

  TLegend* leg = new TLegend(0.4,0.48,0.9,0.9,NULL,"brNDC");
  leg->AddEntry(fun1 ,"total","l");
  leg->AddEntry(fun2 ,"multiple scattering","l");
  leg->AddEntry(fun3 ,"point resolution","l");
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
