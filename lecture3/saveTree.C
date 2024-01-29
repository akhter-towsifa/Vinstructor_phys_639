//A script to create and save a TTree object

#include <TRandom.h>
#include <TTree.h>
#include <TFile.h>

void saveTree() {
  //Create a new file, "RECREATE" will delete an existing file and create a new one
  TFile *hfile = new TFile("new_file.root", "RECREATE", "Example");

  //Create a tree object, "tree_name" is the computer name, and "tree title" is the human name
  TTree *tree = new TTree("tree_name", "tree title");

  //Will use TRandom to generate values again
  TRandom random;
  //Initial seed is NOT RANDOM, so results will be the same
  //Setting seed to 0 will give us a new random seed
  random.SetSeed(0);

  //TTrees need to use references for data, the variable must already exist for the branch to be filled
  float uniform_dist;
  float gaus_dist;
  float binomial_dist;
  float landau_dist;
  float breit_wigner_dist;
  double sphere_dist; 

  double sphere_distribution[3];
  for (int i=0; i<3; i++){
    double sphere_distribution[i];
  }

  //Add branches to the Tree, first argument is the branch name, second argument is the value reference, and third argument is the branch name / datatype
  tree->Branch("uniform_distribution", &uniform_dist, "uniform_distribution/F");
  tree->Branch("gaus_distribution", &gaus_dist, "gaus_distribution/F");
  tree->Branch("binomial_distribution", &binomial_dist, "binomial_distribution/F");
  tree->Branch("landau_distribution", &landau_dist, "landau_distribution/F");
  tree->Branch("breit_wigner_distribution", &breit_wigner_dist, "breit_wigner_distribution/F");
  tree->Branch("sphere_distribution", &sphere_distribution, "sphere_distribution[3] (x,y,z)/D");

  for (int i = 0; i < 100000; i++){
    uniform_dist = random.Uniform(0.0,10.0);
    gaus_dist = random.Gaus(5.0, 2.0);
    binomial_dist = random.Binomial(50.0, 0.4);
    landau_dist = random.Landau(10.0, 5.0);
    breit_wigner_dist = random.BreitWigner(15.0, 20.0);

    random.Sphere(sphere_distribution[0], sphere_distribution[1], sphere_distribution[2], 8.0);

    //After setting the reference variables to the values we want, we fill the Tree
    //All branches are filled with whatever their reference is
    //BE SURE TO CHECK ALL REFERENCES, otherwise you will fill incorrect values
    tree->Fill();
  }
  //Write the file
  hfile->Write();
}
