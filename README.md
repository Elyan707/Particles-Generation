# Particle Generation
This project simulates the collisions between the following particles and antiparticles:
* Positive and negative pions (π<sup>+</sup>, π<sup>-</sup>) 80%
* Kaons and antikaons (K<sup>+</sup>, K<sup>-</sup>) 10%
* Protons and antiprotons (p<sup>+</sup>, p<sup>-</sup>) 9%
* A kaon resonance (K<sup>*</sup>)  1%

The percentage next to the particles represents the probability with which they are generated.
The resonance is a short-lived state that immediately decays into other particles. As a consequence we can only observe it by reconstructing the invariant mass of its decay products. The K<sup>*</sup> decays
into the couples π<sup>+</sup>K<sup>-</sup> and π<sup>-</sup>K<sup>+</sup> with a 50% probability.

---

## Generation
The number of events considered is 10 <sup>5</sup>, and for each event 100 particles are generated. For each particle the following quantities are generated:
* Azimuthal angle θ in a range [0,2π] according to a uniform distribution;
* Polar angle φ in a range [0,π] according to a uniform distribution;
* Momentum p according to a negative exponantial distribution with mean=1;





