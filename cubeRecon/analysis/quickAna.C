{

#include <fstream> 

std::ifstream in;
in.open("testResult.txt");

double list[10][1000];
double tag = 0;
double evtnumber = 0;
int ntrack = 0;
int ntraj = 0;
double listTrue[8][5000];

TH2F* h2D = new TH2F("","Nodes vs Hits; Nodes; Hits",10,0,100,10,0,100);
TH1F* h1D_1 = new TH1F("","Length; length; counts",10,0,1000);
TH1F* h1D_2 = new TH1F("","dEdX; dEdx; counts",10,0,100);
TH1F* h1D_3 = new TH1F("","distance to center; distance; counts",10,0,5000);
TH1F* h1D_4 = new TH1F("","angle ; cos#theta; counts",10,0,1);
TH1F* h1D_5 = new TH1F("","minimal dEdX",10,0,100);
TH1F* h1D_6 = new TH1F("","minimal track angle",10,0,1);
TH1F* h1D_7 = new TH1F("","number of tracks",30,0,30);

TH2F* h2D_tan = new TH2F("","tan angle; true angle; reco angle",30,0,1,30,0,1);

cout<<"here"<<endl;
int counter = 0;
double tanReco = 0;
double tanTrue = 0;

double goodCount = 0;
double badCount = 0;

bool tanTrueProcess = false;
int checkItHere = -999;
int checkItHere2 = -999;

while (1){
  if(!in.good()) break;
 
  in>>tag;
  if(tag == 111111) { 

    //cout<<"in tag "<<endl;
    counter++; 
    in>>evtnumber; 
    if(counter > 1){
      //cout<<"in tag with counter > 1"<<endl;
      cout<<"event : "<<evtnumber<<endl;
      double current_dedx = 10000;
      int dedx_loc = -999;
      for(int j=0;j<ntrack;j++){
	if( j > 99 ) break;
        h2D->Fill(list[0][j],list[1][j]);
        h1D_1->Fill(list[2][j]);
	h1D_2->Fill(list[3][j]);
	h1D_3->Fill(sqrt(pow(list[4][j],2) + pow(list[5][j],2) + pow(list[6][j]-5000.,2)));
	h1D_4->Fill(sqrt(pow(list[7][j],2)+ pow(list[8][j],2))/list[9][j]);
	h1D_7->Fill(ntrack);
	if(current_dedx> list[3][j] && list[2][j] > 1000){
	  current_dedx = list[3][j] ;
	  dedx_loc = j;
	}
      }

      cout<<":::::::::::::: checking event result : "<<checkItHere2<<" "<<dedx_loc<<endl;
      if(checkItHere2 == dedx_loc && dedx_loc >= 0 && checkItHere2>=0) goodCount ++;
      else if (checkItHere2 >= 0 && dedx_loc>=0) badCount ++;
      if (list[2][dedx_loc]>250){
        h1D_5->Fill(list[3][dedx_loc]);
        h1D_6->Fill(sqrt(pow(list[7][dedx_loc],2)+ pow(list[8][dedx_loc],2))/list[9][dedx_loc]);
	tanReco = list[9][dedx_loc] / sqrt(pow(list[7][dedx_loc],2)+ pow(list[8][dedx_loc],2) + pow(list[9][dedx_loc],2) );
      }
      //cout<<"------------------------ tan true and reco : "<<tanTrue<<" "<<tanReco<<endl;
      h2D_tan ->Fill(tanTrue, tanReco);
    }
    ntrack = 0;
    tanReco = 0;
    tanTrue = 0;
    ntraj = 0;
    tanTrueProcess = false;
    checkItHere = -999;
    checkItHere2 = -999;
  }
  else if (tag == 22223333){
    //cout<<"in tag 22223333 "<<endl;
    for(int j=0;j<8;j++)
      // PDG, energy, Px, Py, Pz, X, Y , Z	    
      in>>listTrue[j][ntraj];
    //cout<<"traj :: "<<" ";
    //for(int j=0;j<8;j++)
      //cout<<listTrue[j][ntraj]<<" ";
    //cout<<endl;
    if(abs(listTrue[0][ntraj]) == 13 && tanTrueProcess == false){
      checkItHere = 100;
      //cout<<"found a muon .. "<<checkItHere<<endl;
      tanTrue = listTrue[4][ntraj]/ sqrt(pow(listTrue[2][ntraj],2)+pow(listTrue[3][ntraj],2) + pow(listTrue[4][ntraj],2) );
      tanTrueProcess = true;
    }
    ntraj ++;
  }
  else{
    //cout<<"in track fit "<<endl;
    list[0][ntrack] = tag;
    for(int j=1;j<10;j++)
      in>>list[j][ntrack];
    //cout<<"reco tracks :: "<<" ";
    //for(int j=0;j<10;j++)
      //cout<<list[j][ntrack]<<" ";
    //cout<<endl;
    //cout<<":::::::::::::: checkItHere : "<<checkItHere<<endl;
    if(checkItHere == 100) { 
      //cout<<"^^^^^^^^^^^^^^^^ "<<endl;
      checkItHere2 = ntrack;
    }
    checkItHere = -999;
    ntrack ++;
  }
}

cout<<"::::::::::::::::::: results ~ good and bad are : "<<goodCount<<" "<<badCount<<endl;

new TCanvas();
h2D_tan->Draw("colz");

new TCanvas();
h2D->Draw("colz");

new TCanvas();
h1D_1->Draw("hist");
new TCanvas();
h1D_2->Draw("hist");
new TCanvas();
h1D_3->Draw("hist");
new TCanvas();
h1D_4->Draw("hist");

new TCanvas();
h1D_5->Draw("hist");
new TCanvas();
h1D_6->Draw("hist");

}
