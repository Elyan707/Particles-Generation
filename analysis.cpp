#include "TFile.h"
#include "TH1.h"
#include "TStyle.h"
#include "TLegend.h"
#include "TBenchmark.h"

#include <string>
#include <array>

void Analysis()
{
    gBenchmark->Start("With the analysis");

    TH1::AddDirectory(kFALSE);
    TFile *file1 = new TFile("generate.root", "READ");

    // Creating ROOT File
    TFile *file2 = new TFile("analysis.root", "RECREATE");

    // Reading histograms in ROOT File
    TH1F *h1 = (TH1F *)file1->Get("h1");
    TH1F *h2 = (TH1F *)file1->Get("h2");
    TH1F *h3 = (TH1F *)file1->Get("h3");
    TH1F *h4 = (TH1F *)file1->Get("h4");
    TH1F *h5 = (TH1F *)file1->Get("h5");
    TH1F *h6 = (TH1F *)file1->Get("h6");
    TH1F *h7 = (TH1F *)file1->Get("h7");
    TH1F *h8 = (TH1F *)file1->Get("h8");
    TH1F *h9 = (TH1F *)file1->Get("h9");
    TH1F *h10 = (TH1F *)file1->Get("h10");
    TH1F *h11 = (TH1F *)file1->Get("h11");

    TH1F *hDiff1 = new TH1F(*h7);
    hDiff1->Add(h8, h7, 1, -1);
    hDiff1->SetTitle("Diffrence in invariant mass between conc/disc particle");

    TH1F *hDiff2 = new TH1F(*h9);
    hDiff2->Add(h9, h10, 1, -1);
    hDiff2->SetTitle("Diffrence in invariant mass between conc/disc pions and kaons");

    std::array<TH1F *, 13> histos{h1, h2, h3, h4, h5, h6, h7,
                                  h8, h9, h10, h11, hDiff1, hDiff2};

    for (TH1F *h : histos)
    {
        h->SetMarkerStyle(25);
        h->SetMarkerSize(0.25);
        h->SetMarkerColor(kBlue + 4);
        h->SetLineColor(kBlue + 2);
        h->SetFillColor(kBlue - 2);
        h->GetYaxis()->SetTitleOffset(1.1);
        h->GetXaxis()->SetTitleSize(0.045);
        h->GetYaxis()->SetTitleSize(0.045);
        h->GetYaxis()->SetTitle("Entries");
        gStyle->SetOptStat(1002200);
        gStyle->SetOptFit(1111);
    }

    TF1 *f1 = new TF1("theta", "pol0", 0., TMath::Pi());
    TF1 *f2 = new TF1("phi", "pol0", 0., 2 * TMath::Pi());
    TF1 *f3 = new TF1("f3", "expo", 0, 10);
    TF1 *f4 = new TF1("f4", "gaus", 0, 2);
    TF1 *f5 = new TF1("f5", "gaus", 0, 2);
    TF1 *f6 = new TF1("f6", "gaus", 0, 2);

    std::array<TF1 *, 6> fits{f1, f2, f3, f4, f5, f6};
    for (TF1 *f : fits)
    {
        f->SetLineColor(kRed);
        f->SetLineWidth(3);
        f->SetLineStyle(2);
    }

    f4->SetParameter(1, 0.89166);
    f4->SetParameter(2, 0.050);
    f5->SetParameter(1, 0.89166);
    f5->SetParameter(2, 0.050);
    f6->SetParameter(1, 0.89166);
    f6->SetParameter(2, 0.050);

    f1->SetParNames("Amplitude");
    f2->SetParNames("Amplitude");
    f3->SetParNames("Constant", "Tau");
    f4->SetParNames("Amplitude", "MassK*", "WidthK*");
    f5->SetParNames("Amplitude", "MassK*", "WidthK*");
    f6->SetParNames("Amplitude", "MassK*", "WidthK*");

    h2->Fit(f1);
    h3->Fit(f2);
    h4->Fit(f3);
    hDiff1->Fit(f4);
    hDiff2->Fit(f5);
    h11->Fit(f6);

    TLegend *leg1 = new TLegend(0.1, 0.75, 0.3, 0.9);
    TLegend *leg2 = new TLegend(0.1, 0.75, 0.3, 0.9);
    TLegend *leg3 = new TLegend(0.1, 0.75, 0.3, 0.9);
    TLegend *leg4 = new TLegend(0.1, 0.75, 0.3, 0.9);
    TLegend *leg5 = new TLegend(0.1, 0.75, 0.3, 0.9);
    TLegend *leg6 = new TLegend(0.1, 0.75, 0.3, 0.9);

    leg1->AddEntry(h2, "#theta distribution");
    leg1->AddEntry(f1, "Uniform distribution");

    leg2->AddEntry(h3, "#phi distribution");
    leg2->AddEntry(f2, "Uniform distribution");

    leg3->AddEntry(h4, "Impulse distribution");
    leg3->AddEntry(f3, "Exponential distribution");

    leg4->AddEntry(hDiff1, "Invariant mass between conc/disc particle");
    leg4->AddEntry(f4, "Gaussian distribution");

    leg5->AddEntry(hDiff2, "Invariant mass between conc/disc pions/kaons");
    leg5->AddEntry(f5, "Gaussian distribution");

    leg6->AddEntry(hDiff2, "Invariant between particles generated from decayment ");
    leg6->AddEntry(f5, "Gaussian distribution");

    TCanvas *c1 = new TCanvas("c1", "Particles, angles, impulse distributions", 200, 10, 600, 400);
    c1->Divide(2, 2);

    c1->cd(1);
    h1->GetXaxis()->SetBinLabel(1, "#pi+");
    h1->GetXaxis()->SetBinLabel(2, "#pi-");
    h1->GetXaxis()->SetBinLabel(3, "K+");
    h1->GetXaxis()->SetBinLabel(4, "K-");
    h1->GetXaxis()->SetBinLabel(5, "p+");
    h1->GetXaxis()->SetBinLabel(6, "p-");
    h1->GetXaxis()->SetBinLabel(7, "K*");
    h1->GetXaxis()->SetLabelSize(0.07);
    h1->GetXaxis()->SetTitle("Particles");
    h1->Draw("H");
    h1->Draw("E,P,SAME");

    c1->cd(2);

    h4->GetXaxis()->SetTitle("Impulse (GeV/c)");
    h4->Draw("H");
    h4->Draw("E,P,SAME");
    leg3->Draw("SAME");

    c1->cd(3);
    h2->GetXaxis()->SetTitle("#theta (rad)");
    h2->Draw("H");
    h2->Draw("E,P,SAME");
    leg1->Draw("SAME");

    c1->cd(4);
    h3->GetXaxis()->SetTitle("#phi (rad)");
    h3->Draw("H");
    h3->Draw("E,P,SAME");
    leg2->Draw("SAME");

    TCanvas *c2 = new TCanvas("c2", "Transverse Impulse", 200, 10, 600, 400);
    h5->GetXaxis()->SetTitle("Transverse Impulse (GeV/c)");
    h5->Draw("H");
    h5->Draw("E,P,SAME");

    TCanvas *c3 = new TCanvas("c3", "Energy", 200, 10, 600, 400);
    h6->GetXaxis()->SetTitle("Energy (GeV)");
    h6->Draw("H");
    h6->Draw("E,P,SAME");

    TCanvas *c4 = new TCanvas("c4", "Invariant mass between concordant charge particles", 200, 10, 600, 400);
    h7->GetXaxis()->SetTitle("Mass (GeV/c^{2})");
    h7->Draw("H");
    h7->Draw("E,P,SAME");

    TCanvas *c5 = new TCanvas("c5", "Invariant mass between discordant charge particles", 200, 10, 600, 400);
    h8->GetXaxis()->SetTitle("Mass (GeV/c^{2})");
    h8->Draw("H");
    h8->Draw("E,P,SAME");

    TCanvas *c6 = new TCanvas("c6", "Invariant mass between pion+/kaon- and pion-/kaon+", 200, 10, 600, 400);
    h9->GetXaxis()->SetTitle("Mass (GeV/c^{2})");
    h9->Draw("H");
    h9->Draw("E,P,SAME");

    TCanvas *c7 = new TCanvas("c7", "Invariant mass between pion+/kaon+ and pion-/kaon-", 200, 10, 600, 400);
    h10->GetXaxis()->SetTitle("Mass (GeV/c^{2})");
    h10->Draw("H");
    h10->Draw("E,P,SAME");

    TCanvas *c8 = new TCanvas("c8", "Invariant mass", 200, 10, 700, 800);
    c8->Divide(1, 3);


    c8->cd(1);

    h11->GetXaxis()->SetTitle("Mass (GeV/c^{2})");
    h11->Draw("H");
    h11->Draw("E,P,SAME");
    leg6->Draw("SAME");

    c8->cd(2);

    hDiff1->GetXaxis()->SetTitle("Mass (GeV/c^{2})");
    hDiff1->Draw("H");
    hDiff1->Draw("E,P,SAME");
    leg4->Draw("SAME");

    c8->cd(3);
    
    hDiff2->GetXaxis()->SetTitle("Mass (GeV/c^{2})");
    hDiff2->Draw("H");
    hDiff2->Draw("E,P,SAME");
    leg5->Draw("SAME");

    c1->Print("particles.png");
    c8->Print("invmass.png");

    h1->Write("h1");
    h2->Write("h2");
    h3->Write("h3");
    h4->Write("h4");
    h5->Write("h5");
    h6->Write("h6");
    h7->Write("h7");
    h8->Write("h8");
    h9->Write("h9");
    h10->Write("h10");
    h11->Write("h11");
    hDiff1->Write("hDiff1");
    hDiff2->Write("hDiff2");

    file2->Close();

    std::cout << "\nTheta distribution: \n";
    std::cout << "Parameter: " << f1->GetParameter(0) << " +- " << f1->GetParError(0) << "\n";
    std::cout << "Chi square: " << f1->GetChisquare() << " NDF: " << f1->GetNDF() << "\n";
    std::cout << "Probability: " << f1->GetProb() << "\n";

    std::cout << "\nPhi distribution: \n";
    std::cout << "Parameter: " << f2->GetParameter(0) << " +- " << f2->GetParError(0) << "\n";
    std::cout << "Chi square: " << f2->GetChisquare() << " NDF: " << f2->GetNDF() << "\n";
    std::cout << "Probability: " << f2->GetProb() << "\n";

    std::cout << "\nImpulse distribution: \n";
    std::cout << "Parameter: " << f3->GetParameter(0) << " +- " << f3->GetParError(0) << "\n";
    std::cout << "Chi square: " << f3->GetChisquare() << " NDF: " << f3->GetNDF() << "\n";
    std::cout << "Probability: " << f3->GetProb() << "\n";

    std::cout << "\nGaus distribution of invariant mass between particles generated from decayment: \n";
    std::cout << "Parameter : " << f6->GetParameter(0) << " +- " << f6->GetParError(0) << "\n";
    std::cout << "Mean: " << f6->GetParameter(1) << " +- " << f6->GetParError(1) << "\n";
    std::cout << "Std dev : " << f6->GetParameter(2) << " +- " << f6->GetParError(2) << "\n";
    std::cout << "Chi square: " << f6->GetChisquare() << " NDF: " << f6->GetNDF() << "\n";
    std::cout << "Probability: " << f6->GetProb() << "\n";

    std::cout << "\nGaus distribution of invariant mass between conc and disc: \n";
    std::cout << "Parameter : " << f4->GetParameter(0) << " +- " << f4->GetParError(0) << "\n";
    std::cout << "Mean: " << f4->GetParameter(1) << " +- " << f4->GetParError(1) << "\n";
    std::cout << "Std dev : " << f4->GetParameter(2) << " +- " << f4->GetParError(2) << "\n";
    std::cout << "Chi square: " << f4->GetChisquare() << " NDF: " << f4->GetNDF() << "\n";
    std::cout << "Probability: " << f4->GetProb() << "\n";

    std::cout << "\nGaus distribution of invariant mass between pion and kaon: \n";
    std::cout << "Parameter : " << f5->GetParameter(0) << " +- " << f5->GetParError(0) << "\n";
    std::cout << "Mean: " << f5->GetParameter(1) << " +- " << f5->GetParError(1) << "\n";
    std::cout << "Std dev : " << f5->GetParameter(2) << " +- " << f5->GetParError(2) << "\n";
    std::cout << "Chi square: " << f5->GetChisquare() << " NDF: " << f5->GetNDF() << "\n";
    std::cout << "Probability: " << f5->GetProb() << "\n";

    std::cout << "\nParticles distribution: \n";
    std::cout << "\nNumber of particles: " << h1->GetEntries() << ";\n\n";
    for (int i = 1; i < 8; ++i)
    {
        std::string type;
        double percentage;
        if (i == 1)
        {
            type = "π+";
            percentage = 40;
        }
        else if (i == 2)
        {
            type = "π-";
            percentage = 40;
        }
        else if (i == 3)
        {
            type = "k+";
            percentage = 5;
        }
        else if (i == 4)
        {
            type = "k-";
            percentage = 5;
        }
        else if (i == 5)
        {
            type = "p+";
            percentage = 4.5;
        }
        else if (i == 6)
        {
            type = "p-";
            percentage = 4.5;
        }
        else if (i == 7)
        {
            type = "k*";
            percentage = 1;
        }
        std::cout << "Number of " << type << ": " << h1->GetBinContent(i) << "; Error: " << h1->GetBinError(i) << ";\n";
        double quantity = ((h1->GetBinContent(i)) / (h1->GetEntries())) * 100;
        double error = ((h1->GetBinError(i)) / (h1->GetEntries())) * 100;
        double k = (quantity - percentage) / error;
        std::cout << "Percentage of " << type << ": " << quantity << " +- " << error;
        if (quantity - error < percentage && percentage < quantity + error)
        {
            std::cout << " as expected;\n";
        }
        else
        {
            std::cout << " not as expected (Real value is distant from the expected value by " << k << "σ\n";
        }
    }

    gBenchmark->Show("With the analysis");
}