#include "particleType.hpp"

ParticleType::ParticleType(const std::string name,const double mass,const int charge) : fName(name) ,fMass(mass), fCharge(charge) {};

std::string ParticleType::GetName() const {return fName; };

double ParticleType::GetMass() const {return fMass;};

int ParticleType::GetCharge() const {return fCharge;};

double ParticleType::GetWidth() const {return 0;};

void ParticleType::Print() const{
std::cout<<"Name: "<< fName<<"\n";
std::cout<<"Mass: "<< fMass<<"\n";
std::cout<<"Charge: "<< fCharge<<"\n";
}

