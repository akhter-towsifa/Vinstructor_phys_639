//ROOT is a large library of classes for C++, which can all be read about here
//https://root.cern.ch/doc/master/index.html

//Each object has decent documentation on what functions are available and what it can do
//All ROOT classes start with T, don't ask me why
//Today we will use 3 main classes:
//TH1 (Histogram 1 dimmension) https://root.cern.ch/doc/master/classTH1.html
//TCanvas (The thing we will plot our histograms on) https://root.cern.ch/doc/master/classTCanvas.html
//TRandom (how we will fill our histograms) https://root.cern.ch/doc/master/classTRandom.html

#include <TH1.h>
#include <TCanvas.h>
#include <TRandom.h>

//C++ requires declaring functions first, will write code later
void create_histogram();

//ROOT will run FILENAME() when called
void lecture2(){
    create_histogram();
}

//First function we want to run
void create_histogram(){
    //Create a histogram object
    TH1F *hist = new TH1F("hist1", "Uniform Hist", 20, -10, 10);

    //Fill the histogram with random values
    TRandom random;
    for (int i = 0; i < 100000; i++){
        float value = random.Uniform(-10.0, 10.0);
        hist->Fill(value);
    }

    //Create a canvas to draw the histogram
    TCanvas *c1 = new TCanvas("c1", "Uniform", 800, 1000);

    //Draw the hist onto the loaded canvas
    hist->Draw();

    //Save the current state of the canvas
    c1->SaveAs("test.pdf");
}


//This code runs and makes a plot, but it isn't perfect and there are many things that can be done
//Most learning will come from having a goal, so here are some ideas we can try

//1. The histogram looks pretty bumpy, but we see the numbers are all very close to eachother, its misleading
//   Lets change the Y axis to show us the big picture (that its actually very flat)

//2. A uniform distribution is not very exciting, lets look at TRandom to see what else we can do

//3. Now that we can change what we plot, what if we plot multiple things at once? Lets add another histogram

//4. How do we know which histogram is which? Lets change the color of one of them, maybe even create a legend
//   https://root.cern.ch/doc/master/classTLegend.html
