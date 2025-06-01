#ifndef PARTICLETYPE_HPP
#define PARTICLETYPE_HPP

#include <iostream>

class ParticleType
{
public:
    ParticleType(const std::string name, const double mass, const int charge);
    ParticleType() = default;

    std::string GetName() const;
    double GetMass() const;
    int GetCharge() const;
    virtual double GetWidth() const;

    virtual void Print() const;

private:
    const std::string fName{};
    const double fMass{};
    const int fCharge{};
};

#endif