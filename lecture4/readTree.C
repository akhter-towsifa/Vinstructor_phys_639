#include <TFile.h>
#include <TTree.h>
#include <TH1.h>
#include <TCanvas.h>
#include <TPaveText.h>
#include <TCut.h>
#include <TH2.h>

void readTree()
{
  TFile *hfile = new TFile("dist_file.root");
  TTree *tree = (TTree*)hfile->Get("dist_tree");

  TCanvas *c1 = new TCanvas("c1", "Canvas", 1200, 1000);
  c1->Divide(3,2);

  c1->cd(1);
  TH1F *hist_A = new TH1F("hist_A", "Binomial Hist (50,0.4)", 100, 0, 50);
  tree->Draw("A >> hist_A", "", "");
  hist_A->SetLineWidth(2);
  hist_A->SetLineColor(kOrange+2);
  hist_A->SetFillColor(kOrange+1);
  hist_A->SetFillStyle(3003);

  c1->cd(2);
  TH1F *hist_B = new TH1F("hist_B", "Landau Hist (10,5)", 100, 0, 50);
  tree->Draw("B >> hist_B", "", "");
  hist_B->SetLineWidth(2);
  hist_B->SetLineColor(kAzure+1);
  hist_B->SetFillColor(kAzure+10);
  hist_B->SetFillStyle(3004);

  c1->cd(3);
  TH1F *hist_C = new TH1F("hist_C", "Breit-Wigner Hist (15,20)", 100, 0, 50);
  tree->Draw("C >> hist_C", "", "");
  hist_C->SetLineWidth(2);
  hist_C->SetLineColor(kViolet+1);
  hist_C->SetFillColor(kViolet-9);
  hist_C->SetFillStyle(3005);

  c1->cd(4);
  TH2F *hist_xy = new TH2F("hist_xy", "XY from sphere", 100, -10, 10, 100, -10, 10);
  tree->Draw("y:x >> hist_xy", "", "colz");

  c1->cd(5);
  TH2F *hist_xy_zgt0 = new TH2F("hist_xy_zgt0", "XY from sphere, cut1", 100, -10, 10, 100, -10, 10);
  tree->Draw("y:x >> hist_xy_zgt0", "z > 0", "colz");

  TPaveText *pt1 = new TPaveText(0.1, 0.85, 0.4, 0.9, "NDC");
  pt1->AddText("z > 0");
  pt1->Draw();

  c1->cd(6);
  TH2F *hist_xy_xygtzp1 = new TH2F("hist_xy_xygtzp1", "XY from sphere, cut2", 100, -10, 10, 100, -10, 10);
  tree->Draw("y:x >> hist_xy_xygtzp1", "(x+y) > (z+1)", "colz");

  TPaveText *pt2 = new TPaveText(0.1, 0.85, 0.4, 0.9, "NDC");
  pt2->AddText("x + y > z + 1");
  pt2->Draw();


  c1->SaveAs("lab0_plots.pdf");
}
