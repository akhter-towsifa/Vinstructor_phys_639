//A script to create and save a TTree object

#include <TRandom.h>
#include <TTree.h>
#include <TFile.h>

void saveTree() {
  TFile *hfile = new TFile("dist_file.root", "RECREATE", "Example");

  TTree *tree = new TTree("dist_tree", "tree title");

  TRandom random;
  random.SetSeed(0);

  float binomial;
  float landau;
  float breitwigner;
  double x;
  double y;
  double z;

  tree->Branch("A", &binomial, "A/F");
  tree->Branch("B", &landau, "B/F");
  tree->Branch("C", &breitwigner, "C/F");
  tree->Branch("x", &x, "x/D");
  tree->Branch("y", &y, "y/D");
  tree->Branch("z", &z, "z/D");

  for (int i = 0; i < 100000; i++){
    binomial = random.Binomial(50, 0.4);
    landau = random.Landau(10.0, 5.0);
    breitwigner = random.BreitWigner(15.0, 20.0);
    random.Sphere(x, y, z, 8.0);
    tree->Fill();
  }
  hfile->Write();
}
