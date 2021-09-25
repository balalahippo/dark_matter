#include <TVector3.h>
#include <TCanvas.h>
#include <iostream>
#include <TLorentzVector.h>
#include <TH1D.h>
#include <string>
#include <cstring>

const double PI = 3.1415926;


class G
{
	public:
		G(string str);
		void SetColor(int numberColor);
		void Scale(double cross,int number,int light);
		int passNumber(Int_t weightPass);
		int computeNumber(Int_t weightCompute);

		TH1D *HminDeltaPhi;
		TH1D *HMjj;
		TH1D *HmissingHT;
		TH1D *HmissingET;
		TH1D *HDeltaEtajj;
		TH1D *HDeltaPhijj;
		int passNumbers = 0;
		int computeNumbers = 0;
};

class STACK
{
	public:
		STACK();

		THStack *STminDeltaPhi;
		THStack *STMjj;
		THStack *STmissingHT;
		THStack *STmissingET;
		THStack *STDeltaEtajj;
		THStack *STDeltaPhijj;
};



char* makeName(string str1,string str2);

void FillInHisto(char *fileAdd,G *g);

void AddInStack(G *g,STACK *sta);



//********************** main function!!! **********************//


void programming_cluster()
{
	G EWK_W("EWK_W");
	G EWK_Z("EWK_Z");
	G QCD_Z("QCD_Z");
	G QCD_W("QCD_W");


	FillInHisto("/run/media/DingYi/BE7C-602E/ewkw/tag_1_delphes_events.root",&EWK_W);
	FillInHisto("/run/media/DingYi/BE7C-602E/ewkz/tag_1_delphes_events.root",&EWK_Z);
	FillInHisto("/run/media/DingYi/BE7C-602E/qcdw/tag_1_delphes_events.root",&QCD_W);
	FillInHisto("/run/media/DingYi/BE7C-602E/qcdw/tag_1_delphes_events.root",&QCD_Z);

	EWK_W.Scale(1.045*1000,100000,3000);  //1.045pb ; 100000 events ; 3000 fb^-1
	EWK_Z.Scale(0.1457*1000,100000,3000);
	QCD_W.Scale(4.148*1000,100000,3000);
	QCD_Z.Scale(11.24*1000,100000,3000);

	EWK_W.SetColor(46);//red
	EWK_Z.SetColor(38);//blue
	QCD_W.SetColor(41);//yellow
	QCD_Z.SetColor(30);//green


	STACK stack;


	AddInStack(&EWK_Z,&stack);
	AddInStack(&QCD_Z,&stack);
	AddInStack(&EWK_W,&stack);
	AddInStack(&QCD_W,&stack);
	

	auto temp = new TCanvas();
	stack.STmissingHT->DrawClone("hist");
	auto legend = new TLegend(0.5,0.7,0.98,0.9);
	legend->AddEntry(EWK_Z.HMjj,"EWK Z#rightarrow#nu#nu","f");
   	legend->AddEntry(QCD_Z.HMjj,"QCD Z#rightarrow#nu#nu","f");
   	legend->AddEntry(EWK_W.HMjj,"EWK W+jets#rightarrowl#nu","f");
	legend->AddEntry(QCD_W.HMjj,"QCD Z+jets#rightarrowl#nu","f");
	legend->DrawClone();

	/*cout<<"@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"<<endl;
	cout<<"@@@@@@@@@@@@@@@@@@ result @@@@@@@@@@@@@@@@@@@@"<<endl;
	cout<<"@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"<<endl;
	cout<<"EWKZ:"<<EWK_Z.passNumber(0)/EWK_Z.computeNumber(0)*0.1457*1000*3000<<endl;
	cout<<"QCDZ:"<<QCD_Z.passNumber(0)/QCD_Z.computeNumber(0)*11.24*1000*3000<<endl;
	cout<<"QCDZ:"<<EWK_W.passNumber(0)/EWK_W.computeNumber(0)*1.045*1000*3000<<endl;
	cout<<"QCDZ:"<<QCD_W.passNumber(0)/QCD_W.computeNumber(0)*4.148*1000*3000<<endl;*/
	
	return 0;
}










//**********************************************************//

G::G(string str)
{
	char *name;

	name = makeName(str,"minDeltaPhi");
	HminDeltaPhi = new TH1D(name,"minDeltaPhi",30,0.5,5);
	delete name;

	name = makeName(str,"Mjj");
	HMjj = new TH1D(name,"Mjj",30,2500,5000);
	delete name;

	name = makeName(str,"missingHT");
	HmissingHT = new TH1D(name,"missingHT",30 ,300 ,2500);
	delete name;

	name = makeName(str,"MissingET");
	HmissingET = new TH1D(name,"MissingET",30,190,850);
	delete name;

	name = makeName(str,"deltaEtajj");
	HDeltaEtajj = new TH1D(name,"deltEtajj",35,4,9);
	delete name;

	name = makeName(str,"deltaPhijj");
	HDeltaPhijj = new TH1D(name,"deltaPhijj",30,0,3.5);
	delete name;
}




//**********************************************************//

void G::SetColor(int numberColor)
{
	HminDeltaPhi->SetFillColor(numberColor);
	HminDeltaPhi->SetLineColor(numberColor);
	
	HMjj->SetFillColor(numberColor);
	HMjj->SetLineColor(numberColor);
	
	HmissingHT->SetFillColor(numberColor);
	HmissingHT->SetLineColor(numberColor);
	
	HmissingET->SetFillColor(numberColor);
	HmissingET->SetLineColor(numberColor);
	
	HDeltaEtajj->SetFillColor(numberColor);
	HDeltaEtajj->SetLineColor(numberColor);
	
	HDeltaPhijj->SetFillColor(numberColor);
	HDeltaPhijj->SetLineColor(numberColor);

}


//**********************************************************//


void G::Scale(double cross,int number,int light)
{
	HminDeltaPhi->Scale(cross*light/number);
	HMjj->Scale(cross*light/number);
	HmissingHT->Scale(cross*light/number);
	HmissingET->Scale(cross*light/number);
	HDeltaEtajj->Scale(cross*light/number);
	HDeltaPhijj->Scale(cross*light/number);

}


//**********************************************************//


int G::passNumber(int weightPass)
{
	passNumbers += weightPass;
	return passNumbers;
}


//**********************************************************//


int G::computeNumber(int weightCompute)
{
	computeNumbers += weightCompute;
	return computeNumbers;
}




//***********************************************************//


STACK::STACK()
{
	STminDeltaPhi = new THStack("minDeltaPhi","minDeltaPhi");
	STMjj = new THStack("Mjj","Mjj");
	STmissingHT = new THStack("missingHT","missingHT");
	STmissingET = new THStack("missingET","missingET");
	STDeltaEtajj = new THStack("DeltaEtajj","DeltaEtajj");
	STDeltaPhijj = new THStack("DeltaPhijj","DeltaPhijj");
}



//**********************************************************//

char* makeName(string str1,string str2)
{
	string stringName = str1 + str2;
	string particleName2 = "minDeltaPhi";
	char *name;
	name = new char[strlen(stringName.c_str())+1];
	strcpy(name,stringName.c_str());
	return name;
}





//***********************************************************//



void AddInStack(G *g,STACK *sta)
{
	sta->STDeltaEtajj->Add(g->HDeltaEtajj);
	sta->STDeltaPhijj->Add(g->HDeltaPhijj);
	sta->STminDeltaPhi->Add(g->HminDeltaPhi);
	sta->STmissingET->Add(g->HmissingET);
	sta->STmissingHT->Add(g->HmissingHT);
	sta->STMjj->Add(g->HMjj);
}


//***********************************************************//

void FillInHisto(char *fileAdd,G *g)
{
	g->computeNumber(1); 

	TFile *file = new TFile(fileAdd);
	TTree * delphes = (TTree*)file->Get("Delphes");

	double cut_MET = 190; //GeV


//parameters of jetcuts
	const int NJetPtCut = 2;
	double JetPtCut[NJetPtCut] = {80.,40.};



	Float_t MET[4];
	Float_t MET_Eta = 0;
	Float_t MET_Phi = 0;
	Float_t MET_Magnitude = 0;
	Int_t Jet_Size = 0;
	Float_t Jet_Pt[12];
	Float_t Jet_Eta[12];
	Float_t Jet_Phi[12];
	Float_t Jet_Mass[12];
	UInt_t Jet_BTag[12];
	UInt_t Jet_TauTag[12];
	Int_t Muon_Size = 0;
	Float_t Muon_Pt[10];
	Float_t Muon_Eta[10];
	Float_t Electron_Pt[10];
	Float_t Electron_Eta[10];
	Int_t Electron_Size = 0;

//missingHT
	TVector3 VectorialSum(0,0,0);
	TVector3 GoodJetP(0,0,0);

//number of event
	int Event_Number = 0;


//read the date
	delphes->SetBranchAddress("MissingET.MET",MET);
	delphes->SetBranchAddress("MissingET.Eta",&MET_Eta);
	delphes->SetBranchAddress("MissingET.Phi",&MET_Phi);
	delphes->SetBranchAddress("Muon.PT",&Muon_Pt);
	delphes->SetBranchAddress("Muon.Eta",&Muon_Eta);
	delphes->SetBranchAddress("Muon_size",&Muon_Size);
	delphes->SetBranchAddress("Electron.PT",Electron_Pt);
	delphes->SetBranchAddress("Electron.Eta",Electron_Eta);
	delphes->SetBranchAddress("Electron_size",&Electron_Size);
	delphes->SetBranchAddress("Jet.PT",Jet_Pt);
	delphes->SetBranchAddress("Jet.Eta",Jet_Eta);
	delphes->SetBranchAddress("Jet.Phi",Jet_Phi);
	delphes->SetBranchAddress("Jet.Mass",Jet_Mass);
	delphes->SetBranchAddress("Jet.BTag",Jet_BTag);
	delphes->SetBranchAddress("Jet.TauTag",Jet_TauTag);
	delphes->SetBranchAddress("Jet_size",&Jet_Size);





	Event_Number = delphes->GetEntries();


//do
	for(int i = 0; i<Event_Number; i++)
	{
		delphes->GetEntry(i);

		TLorentzVector leadingJet(0,0,0,0);
		TLorentzVector subLeadingJet(0,0,0,0);
		TLorentzVector sumJet(0,0,0,0);

		Double_t Mjj = 0;

		leadingJet.SetPtEtaPhiM(Jet_Pt[0],Jet_Eta[0],Jet_Phi[0],Jet_Mass[0]);
		subLeadingJet.SetPtEtaPhiM(Jet_Pt[1],Jet_Eta[1],Jet_Phi[1],Jet_Mass[1]);

		sumJet = leadingJet + subLeadingJet ;

		Mjj = sumJet.M();


		double DeltaEtajj;
		double DeltaPhijj1,DeltaPhijj;



//cut
		int flag = 0;
//cut of Muon
		flag = 0;
		for(int i=0; i<Muon_Size; i++)
		{
			if(abs(Muon_Eta[i])<3.0 && Muon_Pt[i]>20)
			{
				flag = 1;
			}
		}
		if(flag==1)
		{
			//cout<<"abs(Electron_Eta[i])<2.8 && Electron_Pt[i]>10"<<endl;
			continue;
		}
//cut of Electron
		flag = 0;
		for(int i=0; i<Electron_Size; i++)
		{
			if(abs(Electron_Eta[i])<2.8 && Electron_Pt[i]>10)
			{
				flag = 1;
			}
		}
		if(flag==1)
		{
			//cout<<"abs(Electron_Eta[i])<2.8 && Electron_Pt[i]>10"<<endl;
			continue;
		}
//cut of tau
		flag = 0;//default flag
		for(int i=0; i<Jet_Size; i++)
		{
			if(Jet_TauTag[i]==1)
			{
				flag = 1;
			}
		}
		if(flag==1)
		{
			//cout<<"Jet_TauTag[i]==1"<<endl;
			continue;
		}
//cut of b-jet
		flag = 0;
		for(int i=0; i<Jet_Size; i++)
		{
			if(Jet_BTag[i]==1)
			{
				flag = 1;
			}
		}
		if(flag==1)
		{
			//cout<<"Jet_BTag[i]==1"<<endl;
			continue;
		}
//cut of leadingJet and sub-leadingJet
		flag = 0;
		for(int i = 0; i< NJetPtCut ; i++)
		{
			if(!(Jet_Pt[i]>JetPtCut[i]))
			{
				flag = 1;
			}
		}
		if(flag==1)
		{
			//cout<<"!(Jet_Pt[i]>JetPtCut[i])"<<endl;
			continue;
		}
		if(Jet_Size <2)
		{
			continue;
		}
//cut of Mjj
		if(Mjj<2500)
		{
			continue;
		}
//cut of missingET
		if(MET[0]<190)
		{
			continue;
		}
//cut end



		DeltaEtajj=abs(Jet_Eta[0]-Jet_Eta[1]);
		DeltaPhijj1=abs(Jet_Phi[0]-Jet_Phi[1]);

		if (DeltaPhijj1>3.1415926)
		{
			DeltaPhijj= 2*3.1415926-DeltaPhijj1 ;
		}
		else
		{
			DeltaPhijj= DeltaPhijj1;
		}

		if(DeltaPhijj>1.8)
		{
			continue;
		}
		if(DeltaEtajj<4)
		{
			continue;
		}


//cut of jet

		int countGoodJet = 0;
		Double_t minDeltaPhi = 4. ;
		Double_t DeltaPhi = 0;
		VectorialSum.SetPtEtaPhi(0,0,0);
		Double_t VectorialSumPt = 0;
		cout<<"###############################"<<endl;
		for(int j=0; j<Jet_Size; j++)
		{
			if((abs(Jet_Eta[j])<5 && Jet_Pt[j]>30))
			{
				GoodJetP.SetPtEtaPhi(Jet_Pt[j], Jet_Eta[j], Jet_Phi[j]) ;
				VectorialSum += GoodJetP ;
				DeltaPhi = abs(Jet_Phi[j] - MET_Phi);
				if(DeltaPhi > PI)
				{
					DeltaPhi = 2*PI - DeltaPhi;
				}
				cout << "************************" << endl;
				cout << "Jet_Phi[" << j << "]:" << Jet_Phi[j] << endl;
				cout << "MET_Phi:" << MET_Phi << endl;
				cout << "Jet_Pt[" << j << "]:" << Jet_Pt[j] << endl;
				cout << "Jet_Eta[" << j << "]:" << Jet_Eta[j] << endl;
				cout << "Jet_Size:" << Jet_Size << endl;
				cout << "deltaPhi:" << DeltaPhi << endl;
				if(DeltaPhi < minDeltaPhi)
				{
					minDeltaPhi = DeltaPhi;
				}
				countGoodJet ++;
			}
		}
		if(countGoodJet == 0)
		{
			continue;
		}
		if(minDeltaPhi < 0.5)
		{
			continue;
		}



		//cout << "minDeltaPhi:" << minDeltaPhi << endl;
		//cout << "GoodJet: " << countGoodJet << endl;

		VectorialSumPt = VectorialSum.Pt();
		g->HminDeltaPhi->Fill(minDeltaPhi);
		g->HMjj->Fill(Mjj);
		g->HmissingHT->Fill(VectorialSumPt);
		g->HmissingET->Fill(MET[0]);
		g->HDeltaEtajj->Fill(DeltaEtajj);
		g->HDeltaPhijj->Fill(DeltaPhijj);

		g->passNumber(1);


	}



}



