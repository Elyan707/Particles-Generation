#ifndef RESONANCETYPE_HPP
#define RESONANCETYPE_HPP

#include "particleType.hpp"

class ResonanceType : public ParticleType
{
public:
    ResonanceType(const std::string name, const double mass, const int charge, const double width);
    ResonanceType()=default;
    double GetWidth() const;
    void Print() const;

private:
    const double fWidth{};
};

#endif