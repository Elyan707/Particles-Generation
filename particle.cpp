#include <cmath>
#include <cstdlib>
#include "particle.hpp"

ParticleType *Particle::fParticleType[Particle::fMaxNumParticleType];
int Particle::fNParticleType = 0;

Particle::Particle(const std::string name, const double px, const double py, const double pz) : fIndex(FindParticle(name)), fPx(px), fPy(py), fPz(pz)
{
    if (FindParticle(name) == -1)
    {
        std::cout << "No correspondence found \n";
    };
};
int Particle::GetIndex() const { return fIndex; };
double Particle::GetPx() const { return fPx; };
double Particle::GetPy() const { return fPy; };
double Particle::GetPz() const { return fPz; };

double Particle::GetMass() const { return fParticleType[fIndex]->GetMass(); };
int Particle::GetCharge() const { return fParticleType[fIndex]->GetCharge(); }
double Particle::Energy() const
{
    double impulse_2 = fPx * fPx + fPy * fPy + fPz * fPz;
    double mass_ = fParticleType[fIndex]->GetMass();
    double energy = sqrt(mass_ * mass_ + impulse_2);
    return energy;
};

double Particle::InvMass(Particle &p) const
{
    double inv_mass = sqrt((Energy() + p.Energy()) * (Energy() + p.Energy()) -
                           ((fPx + p.fPx) * (fPx + p.fPx) + (fPy + p.fPy) * (fPy + p.fPy) +
                            (fPz + p.fPz) * (fPz + p.fPz)));
    return inv_mass;
};

void Particle::SetIndex(const int index) { fIndex = index; };
void Particle::SetIndex(std::string name) { fIndex = FindParticle(name); };
void Particle::SetP(const double px, const double py, const double pz)
{
    fPx = px;
    fPy = py;
    fPz = pz;
};

void Particle::AddParticleType(const std::string name, const double mass, const int charge, const double width=0)
{
    if (fNParticleType < fMaxNumParticleType)
    {
        if (FindParticle(name) == -1)
        {
            if (width == 0)
            {
                ParticleType *p = new ParticleType(name, mass, charge);
                fParticleType[fNParticleType] = p;
                ++fNParticleType;
            }
            else
            {
                ResonanceType *p = new ResonanceType(name, mass, charge, width);
                fParticleType[fNParticleType] = p;
                ++fNParticleType;
            }
        }
    }
}

void Particle::PrintArray()
{

    for (int i = 0; i < fNParticleType; ++i)
    {
        fParticleType[i]->Print();
    };
};
void Particle::PrintParticle()
{
    std::cout << "Index: " << fIndex << "\n";
    std::cout << "Name: " << fParticleType[fIndex]->GetName() << "\n";
    std::cout << "Px: " << fPx << "\n";
    std::cout << "Py: " << fPy << "\n";
    std::cout << "Pz: " << fPz << "\n";
};

int Particle::FindParticle(std::string name)
{
    for (int i = 0; i < fNParticleType; ++i)
    {
        std::string nameP = fParticleType[i]->GetName();
        if (name == nameP)
            return i;
    };
    return -1;
};

int Particle::Decay2body(Particle &dau1, Particle &dau2) const
{
    if (GetMass() == 0.0)
    {
        printf("Decayment cannot be preformed if mass is zero\n");
        return 1;
    }

    double massMot = GetMass();
    double massDau1 = dau1.GetMass();
    double massDau2 = dau2.GetMass();

    if (fIndex > -1)
    { // add width effect

        // gaussian random numbers

        float x1, x2, w, y1;

        double invnum = 1. / RAND_MAX;
        do
        {
            x1 = 2.0 * rand() * invnum - 1.0;
            x2 = 2.0 * rand() * invnum - 1.0;
            w = x1 * x1 + x2 * x2;
        } while (w >= 1.0);

        w = sqrt((-2.0 * log(w)) / w);
        y1 = x1 * w;

        massMot += fParticleType[fIndex]->GetWidth() * y1;
    }

    if (massMot < massDau1 + massDau2)
    {
        printf("Decayment cannot be preformed because mass is too low in this channel\n");
        return 2;
    }

    double pout = sqrt((massMot * massMot - (massDau1 + massDau2) * (massDau1 + massDau2)) * (massMot * massMot - (massDau1 - massDau2) * (massDau1 - massDau2))) / massMot * 0.5;

    double norm = 2 * M_PI / RAND_MAX;

    double phi = rand() * norm;
    double theta = rand() * norm * 0.5 - M_PI / 2.;
    dau1.SetP(pout * sin(theta) * cos(phi), pout * sin(theta) * sin(phi), pout * cos(theta));
    dau2.SetP(-pout * sin(theta) * cos(phi), -pout * sin(theta) * sin(phi), -pout * cos(theta));

    double energy = sqrt(fPx * fPx + fPy * fPy + fPz * fPz + massMot * massMot);

    double bx = fPx / energy;
    double by = fPy / energy;
    double bz = fPz / energy;

    dau1.Boost(bx, by, bz);
    dau2.Boost(bx, by, bz);

    return 0;
}
void Particle::Boost(double bx, double by, double bz)
{

    double energy = Energy();

    // Boost this Lorentz vector
    double b2 = bx * bx + by * by + bz * bz;
    double gamma = 1.0 / sqrt(1.0 - b2);
    double bp = bx * fPx + by * fPy + bz * fPz;
    double gamma2 = b2 > 0 ? (gamma - 1.0) / b2 : 0.0;

    fPx += gamma2 * bp * bx + gamma * bx * energy;
    fPy += gamma2 * bp * by + gamma * by * energy;
    fPz += gamma2 * bp * bz + gamma * bz * energy;
}