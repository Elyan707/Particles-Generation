#include "particleType.hpp"
#include "resonanceType.hpp"
#include "particle.hpp"
#include "TRandom.h"
#include "TH1.h"
#include "TH2.h"
#include "TCanvas.h"
#include "TFile.h"
#include "TBenchmark.h"

#include <cmath>

void Generate()
{
    gBenchmark->Start("With the generation");

    gRandom->SetSeed();
    Particle::AddParticleType("π+", 0.13957, 1, 0);
    Particle::AddParticleType("π-", 0.13957, -1, 0);
    Particle::AddParticleType("k+", 0.49367, 1, 0);
    Particle::AddParticleType("k-", 0.49367, -1, 0);
    Particle::AddParticleType("p+", 0.93827, 1, 0);
    Particle::AddParticleType("p-", 0.93827, -1, 0);
    Particle::AddParticleType("k*", 0.89166, 0, 0.050);

    Particle EventParticles[120];
    Double_t phi, theta, p, x, y, transverse_p = 0;
    Int_t n = 0;

    TH1F *h1 = new TH1F("h1", "Particle Type", 7, 0, 7);
    TH1F *h2 = new TH1F("h2", "Theta Ditribution", 1000, 0, M_PI);
    TH1F *h3 = new TH1F("h3", "Phi Ditribution", 1000, 0, 2 * M_PI);
    TH1F *h4 = new TH1F("h4", "Impulse distribution", 1000, 0, 10);
    TH1F *h5 = new TH1F("h5", "Transverse Impulse", 1000, 0, 10);
    TH1F *h6 = new TH1F("h6", "Energy", 1000, 0, 10);
    TH1F *h7 = new TH1F("h7", "Invariant mass between concordant charge particles", 100, 0.5, 1.5);
    TH1F *h8 = new TH1F("h8", "Invariant mass between discordant charge particles", 100, 0.5, 1.5);
    TH1F *h9 = new TH1F("h9", "Invariant mass between pion+/kaon- and pion-/kaon+", 100, 0.5, 1.5);
    TH1F *h10 = new TH1F("h10", "Invariant mass between pion+/kaon+ and pion-/kaon-", 100, 0.5, 1.5);
    TH1F *h11 = new TH1F("h11", "Invariant mass between particles generated from decayment", 100, 0.5, 1.5);

    h6->Sumw2();
    h7->Sumw2();
    h8->Sumw2();
    h9->Sumw2();
    h10->Sumw2();

    for (Int_t i = 0; i < 1E5; ++i)
    {
        n = 0;

        for (Int_t j = 0; j < 100; ++j)
        {
            phi = gRandom->Uniform(0, 2 * M_PI);
            theta = gRandom->Uniform(0, M_PI);
            p = gRandom->Exp(1);

            x = gRandom->Rndm();
            EventParticles[j].SetP(p * sin(theta) * cos(phi), p * sin(theta) * sin(phi), p * cos(theta));
            if (x < 0.4)
            {
                EventParticles[j].SetIndex("π+");
            }
            else if (x < 0.8)
            {
                EventParticles[j].SetIndex("π-");
            } 
            else if (x < 0.85)
            {
                EventParticles[j].SetIndex("k+");
            }
            else if (x < 0.90)
            {
                EventParticles[j].SetIndex("k-");
            }
            else if (x < 0.945)
            {
                EventParticles[j].SetIndex("p+");
            }
            else if (x < 0.99)
            {
                EventParticles[j].SetIndex("p-");
            }
            else
            {
                EventParticles[j].SetIndex("k*");
                y = gRandom->Rndm();
                if (y < 0.50)
                {
                    EventParticles[100 + n].SetIndex("π+");
                    EventParticles[101 + n].SetIndex("k-");
                }
                else
                {
                    EventParticles[100 + n].SetIndex("π-");
                    EventParticles[101 + n].SetIndex("k+");
                }

                EventParticles[j].Decay2body(EventParticles[100 + n], EventParticles[101 + n]);
                Double_t Invariant_Decay = EventParticles[100 + n].InvMass(EventParticles[101 + n]);
                h11->Fill(Invariant_Decay);
                n += 2;
            }
            transverse_p = sqrt((p * sin(theta) * cos(phi)) * (p * sin(theta) * cos(phi)) + (p * sin(theta) * sin(phi)) * (p * sin(theta) * sin(phi)));
            h1->Fill(EventParticles[j].GetIndex());
            h2->Fill(theta);
            h3->Fill(phi);
            h4->Fill(p);
            h5->Fill(transverse_p);
            h6->Fill(EventParticles[j].Energy()); 
        }

        for (Int_t f = 0; f < 100+n; ++f)
        {
            if (EventParticles[f].GetMass() != 0 && EventParticles[f].GetIndex() != 7)
            {
                for (Int_t g = f + 1; g < 100+n; ++g)
                {
                    if (EventParticles[f].GetCharge() * EventParticles[g].GetCharge() == 1)
                    {
                        Double_t Concordant_Invariant = EventParticles[f].InvMass(EventParticles[g]);
                        h7->Fill(Concordant_Invariant);
                    }
                    else if (EventParticles[f].GetCharge() * EventParticles[g].GetCharge() == -1)
                    {
                        Double_t Discordant_Invariant = EventParticles[f].InvMass(EventParticles[g]);
                        h8->Fill(Discordant_Invariant);
                    }
                }
                
                    for (Int_t g = f + 1; g < 100+n; ++g)
                    {
                        if ((EventParticles[f].GetIndex() == 0 && EventParticles[g].GetIndex() == 3) || (EventParticles[f].GetIndex() == 3 && EventParticles[g].GetIndex() == 0) || (EventParticles[f].GetIndex() == 1 && EventParticles[g].GetIndex() == 2) || (EventParticles[f].GetIndex() == 2 && EventParticles[g].GetIndex() == 1))
                        {
                            Double_t Discordant_pk = EventParticles[f].InvMass(EventParticles[g]);
                            h9->Fill(Discordant_pk);
                        }
                        else if ((EventParticles[f].GetIndex() == 0 && EventParticles[g].GetIndex() == 2) || (EventParticles[f].GetIndex() == 2 && EventParticles[g].GetIndex() == 0) || (EventParticles[f].GetIndex() == 1 && EventParticles[g].GetIndex() == 3) || (EventParticles[f].GetIndex() == 3 && EventParticles[g].GetIndex() == 1))
                        {
                            Double_t Concordant_pk = EventParticles[f].InvMass(EventParticles[g]);
                            h10->Fill(Concordant_pk);
                        }
                    }
                
            }
        }
    }
    TCanvas *c1 = new TCanvas();
    h1->Draw();
    TCanvas *c2 = new TCanvas();
    h2->Draw();
    TCanvas *c3 = new TCanvas();
    h3->Draw();
    TCanvas *c4 = new TCanvas();
    h4->Draw();
    TCanvas *c5 = new TCanvas();
    h5->Draw();
    TCanvas *c6 = new TCanvas();
    h6->Draw();
    TCanvas *c7 = new TCanvas();
    h7->Draw();
    TCanvas *c8 = new TCanvas();
    h8->Draw();
    TCanvas *c9 = new TCanvas();
    h9->Draw();
    TCanvas *c10 = new TCanvas();
    h10->Draw();
    TCanvas *c11 = new TCanvas();
    h11->Draw();

    TFile *file = new TFile("generate.root", "recreate");

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

    file->Close();

    gBenchmark->Show("With the generation");

}
