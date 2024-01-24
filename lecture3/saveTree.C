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

  //Add branches to the Tree, first argument is the branch name, second argument is the value reference, and third argument is the branch name / datatype
  tree->Branch("uniform_distribution", &uniform_dist, "uniform_distribution/F");
  tree->Branch("gaus_distribution", &gaus_dist, "gaus_distribution/F");

  for (int i = 0; i < 100000; i++){
    uniform_dist = random.Uniform(0.0,10.0);
    gaus_dist = random.Gaus(5.0, 2.0);
    //After setting the reference variables to the values we want, we fill the Tree
    //All branches are filled with whatever their reference is
    //BE SURE TO CHECK ALL REFERENCES, otherwise you will fill incorrect values
    tree->Fill();
  }
  //Write the file
  hfile->Write();
}
