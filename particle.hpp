#ifndef PARTICLE_HPP
#define PARTICLE_HPP

#include "particleType.hpp"
#include "resonanceType.hpp"

class Particle
{
public:
    Particle(std::string name, const double px, const double py, const double pz);
    Particle() = default;
    int GetIndex() const;
    double GetPx() const;
    double GetPy() const;
    double GetPz() const;

    double GetMass() const;
    int GetCharge() const;
    double Energy() const;
    double InvMass(Particle &p) const;

    void SetIndex(const int index);
    void SetIndex(std::string name);
    void SetP(const double px, const double py, const double pz);

    static void AddParticleType(std::string name, const double mass, const int charge, const double width);
    static void PrintArray();
    void PrintParticle();

    int Decay2body(Particle &dau1,Particle &dau2) const;

private:
    static const int fMaxNumParticleType = 10;
    static ParticleType* fParticleType[fMaxNumParticleType];
    static int fNParticleType;
    int fIndex{};
    double fPx{};
    double fPy{};
    double fPz{};

    static int FindParticle(std::string name);
    void Boost(double bx, double by, double bz);
};

#endif