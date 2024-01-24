//A script to read a File with a TTree and plot some branches

#include <TFile.h>
#include <TTree.h>
#include <TH1.h>
#include <TCanvas.h>
#include <TPaveText.h>
#include <TCut.h>
#include <TH2.h>

void readTree()
{
  //Load the file and get the tree
  TFile *hfile = new TFile("new_file.root");
  TTree *tree = (TTree*)hfile->Get("tree_name");

  //TTrees need to have a reference variable to put the data into
  float uniform_dist;
  float gaus_dist;
  tree->SetBranchAddress("uniform_distribution", &uniform_dist);
  tree->SetBranchAddress("gaus_distribution", &gaus_dist);

  //Create a canvas to put plots onto
  TCanvas *c1 = new TCanvas("c1", "Canvas", 1200, 1000);
  //You can use the same canvas to draw multiple plots!
  //canvas->Divide(n) will divide the canvas into n number of sections
  //canvas->Divide(n,m) is also alowed
  c1->Divide(2,2);


  //Create some histograms to fill with the branch in a loop over entries (Option 1)
  TH1F *uniform_hist = new TH1F("UniformHist", "Uniform Hist", 100, 0, 10);
  TH1F *gaus_hist = new TH1F("GaussianHist", "Gaussian Hist", 100, 0, 10);

  int nEntries = tree->GetEntries();
  for (int i=0; i<nEntries; i++){
    tree->GetEntry(i);

    uniform_hist->Fill(uniform_dist);
    gaus_hist->Fill(gaus_dist);
  }

  //Change to the first subplot of the canvas
  c1->cd(1);
  //hist->Draw("option") has many options
  //Can find all draw options here https://root.cern/doc/master/classTHistPainter.html
  //Lets use "E" to draw error bars
  uniform_hist->Draw("E");
  //Set the Y axis limits to be nicer to see
  float uniform_hist_max = uniform_hist->GetMaximum();
  uniform_hist->GetYaxis()->SetRangeUser(0.0, 1.5*uniform_hist_max);

  //Change to the second subplot
  c1->cd(2);
  gaus_hist->Draw();
  float gaus_hist_max = gaus_hist->GetMaximum();
  gaus_hist->GetYaxis()->SetRangeUser(0.0, 1.5*gaus_hist_max);
  //Change the line color, fill color, and fill style
  gaus_hist->SetLineColor(kRed);
  gaus_hist->SetFillColor(kOrange);
  gaus_hist->SetFillStyle(3005);

  //Add text onto the plot, use option "NDC" to use x/y positions in percentages
  TPaveText *pt1 = new TPaveText(0.1,0.7,0.5,0.9, "NDC");
  pt1->AddText("Example Text!");
  pt1->Draw();


  //Change to third subplot
  c1->cd(3);

  //Create some histograms to fill with tree->Draw("name >> hist", cut, option) (Option 2)
  TH1F *hist_test = new TH1F("hist_test", "Hists cut by Gaus", 100, 0, 10);
  TH1F *hist_test2 = new TH1F("hist_test2", "this_name_doesnt_matter", 100, 0, 10);
  //TTree entries are connected, so each entry has both distributions
  //We can cut the uniform distribution on what value the gaus distribution has
  TCut cut1 = "gaus_distribution < 5";
  //If we use tree->Draw("name >> hist") we can push branches directly into a histogram without looping all events!
  tree->Draw("uniform_distribution >> hist_test", cut1);
  tree->Draw("gaus_distribution >> hist_test2", cut1, "same");
  hist_test2->SetLineColor(kRed);
  hist_test->GetYaxis()->SetRangeUser(0.0, max(1.5*hist_test->GetMaximum(), 1.5*hist_test2->GetMaximum()));

  TPaveText *pt2 = new TPaveText(0.1, 0.7, 0.7, 0.9, "NDC");
  pt2->AddText("Variables in Trees are connected");
  pt2->AddText("Notice the uniform dist lost half its entries");
  pt2->Draw();



  c1->cd(4);
  //Just for fun, lets plot a 2D histogram and cut it by a function of both of values
  TH2F *hist_2d = new TH2F("gaus_by_uniform", "2D Hist", 100, 0, 10, 100, 0, 10);
  TCut cut2 = "(gaus_distribution * uniform_distribution) > 10";
  tree->Draw("gaus_distribution:uniform_distribution", cut2, "colz");

  c1->SaveAs("example_plot.pdf");


}
