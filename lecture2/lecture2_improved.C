//ROOT is a large library of classes for C++, which can all be read about here
//https://root.cern.ch/doc/master/index.html

//Each object has decent documentation on what functions are available and what it can do
//All ROOT classes start with T, don't ask me why
//Today we will use 3 main classes:
//TH1 (Histogram 1 dimmension) https://root.cern.ch/doc/master/classTH1.html
//TCanvas (The thing we will plot our histograms on) https://root.cern.ch/doc/master/classTCanvas.html
//TRandom (how we will fill our histograms) https://root.cern.ch/doc/master/classTRandom.html

#include <TCanvas.h>
#include <TH1.h>
#include <TRandom.h>
#include <TLegend.h>

//C++ requires declaring functions first, will write code later
void create_histogram();
void create_histogram2();
void create_histogram3();
void create_histogram4();
void create_histogram5();

//ROOT will run FILENAME() when called
void lecture2_improved(){
    create_histogram();
    create_histogram2();
    create_histogram3();
    create_histogram4();
    create_histogram5();
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

//We made a histogram and saved it!
//But it doesn't look the best, lets start with fixing the Y axis on TH1
void create_histogram2(){
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
    //Lets make the y-axis easier to understand
    hist->GetYaxis()->SetRangeUser(0.0, 1.5*hist->GetMaximum());

    //Save the current state of the canvas
    c1->SaveAs("test2.pdf");
}

//Can we do something other than a flat histogram?
//Look at TRandom to see what other shapes we can make
//Also, I don't like having plots in my work folder
//Lets create a plot folder and put them in there
//Run ```mkdir plots/``` before doing this step
void create_histogram3(){
    //Create a histogram object
    TH1F *hist = new TH1F("Gaus Dist", "Gaus Hist", 20, -10, 10);

    //Fill the histogram with random values
    TRandom random;
    for (int i = 0; i < 100000; i++){
        float value = random.Gaus(0.0, 5.0);
        hist->Fill(value);
    }

    //Create a canvas to draw the histogram
    TCanvas *c1 = new TCanvas("c1", "Uniform", 800, 1000);

    //Draw the hist onto the loaded canvas
    hist->Draw();
    //Lets make the y-axis easier to understand
    hist->GetYaxis()->SetRangeUser(0.0, 1.5*hist->GetMaximum());

    //Save the current state of the canvas
    c1->SaveAs("plots/gaus_dist.pdf");
}



//Lets go crazy and plot 2 distributions at once!
void create_histogram4(){
    //Create a histogram object
    TH1F *hist_gaus = new TH1F("Gaus Dist", "Gaus Hist", 20, -10, 10);
    TH1F *hist_landau = new TH1F("Landau Dist", "Landau Hist", 20, -10, 10);

    //Fill the histograms with random values
    TRandom random;
    for (int i = 0; i < 100000; i++){
        float value_gaus = random.Gaus(0.0, 5.0);
        float value_landau = random.Landau(0.0, 5.0);
        hist_gaus->Fill(value_gaus);
        hist_landau->Fill(value_landau);
    }

    //Create a canvas to draw the histograms
    //Multiple histograms can be drawn to the same canvas!
    TCanvas *c1 = new TCanvas("c1", "Uniform", 800, 1000);

    //Draw the hist onto the loaded canvas
    hist_gaus->Draw();
    //Draw the second hist onto the same canvas!
    //Draw actually calls a new ROOT class, THistPainter https://root.cern/doc/master/classTHistPainter.html
    //You don't need to know much now, but option "same" is what we want for now
    hist_landau->Draw("same");

    //Lets make the y-axis easier to understand, we must change the FIRST hist drawn
    hist_gaus->GetYaxis()->SetRangeUser(0.0, 1.5*hist_gaus->GetMaximum());

    //Save the current state of the canvas
    c1->SaveAs("plots/gaus_and_landau_dist.pdf");
}


//How will we know which line is which distribution?
//Lets change the line color of one of them
void create_histogram5(){
    //Create a histogram object
    TH1F *hist_gaus = new TH1F("Gaus Dist", "Gaus Hist", 20, -10, 10);
    TH1F *hist_landau = new TH1F("Landau Dist", "Landau Hist", 20, -10, 10);

    //Fill the histograms with random values
    TRandom random;
    for (int i = 0; i < 100000; i++){
        float value_gaus = random.Gaus(0.0, 5.0);
        float value_landau = random.Landau(0.0, 5.0);
        hist_gaus->Fill(value_gaus);
        hist_landau->Fill(value_landau);
    }

    //Create a canvas to draw the histograms
    //Multiple histograms can be drawn to the same canvas!
    TCanvas *c1 = new TCanvas("c1", "Uniform", 800, 1000);

    //Draw the hist onto the loaded canvas
    hist_gaus->Draw();
    //Draw the second hist onto the same canvas!
    //Draw actually calls a new ROOT class, THistPainter https://root.cern/doc/master/classTHistPainter.html
    //You don't need to know much now, but option "same" is what we want for now
    hist_landau->Draw("same");
    //Changing the line color of hist_landau to red
    hist_landau->SetLineColor(kRed);

    //Lets make the y-axis easier to understand, we must change the FIRST hist drawn
    hist_gaus->GetYaxis()->SetRangeUser(0.0, 1.5*hist_gaus->GetMaximum());

    //Create a TLegend and add the two histograms
    TLegend *legend = new TLegend(0.1,0.7,0.48,0.9);
    legend->AddEntry(hist_gaus, "Gausian Distribution");
    legend->AddEntry(hist_landau, "Landau Distribution");
    legend->Draw();
    //Notice for some reason legend doens't need "same" argument, don't ask me why

    //Save the current state of the canvas
    c1->SaveAs("plots/gaus_and_landau_dist.pdf");
}
