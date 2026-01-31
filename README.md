# Particle Generation
This project simulates the results of collisions in high-energy physics. The particles/antiparticles produced in such collisions and generated useing Monte Carlo method are the following:
* Positive and negative pions (π<sup>+</sup>, π<sup>-</sup>) 80%
* Kaons and antikaons (K<sup>+</sup>, K<sup>-</sup>) 10%
* Protons and antiprotons (p<sup>+</sup>, p<sup>-</sup>) 9%
* A kaon resonance (K<sup>*</sup>)  1%

The percentage next to the particles represents the probability with which they are generated.
The resonance is a short-lived state that immediately decays into other particles. As a consequence we can only observe it by reconstructing the invariant mass of its decay products. The K<sup>*</sup> decays
into the couples π<sup>+</sup>K<sup>-</sup> and π<sup>-</sup>K<sup>+</sup> with a 50% probability. The other particles/antiparticles are stable.

---

## Generation
The number of events considered is 10 <sup>5</sup>, and for each event 100 particles are generated. For each particle the following quantities are generated:
* Azimuthal angle θ in a range [0,2π] according to a uniform distribution;
* Polar angle φ in a range [0,π] according to a uniform distribution;
* Momentum p according to a negative exponential distribution with mean=1;

## Results


We have three ways to observe the K<sup>*</sup> as a peak in the invariant mass:

### Invariant mass of the decay products

Since  K<sup>*</sup> decays in pairs of π<sup>+</sup>K<sup>-</sup> and π<sup>-</sup>K<sup>+</sup>, the most direct way we can observe it is by renconstructing the invariant mass of its decay products.

### Difference between the invariant masses of particles with concordant and discordant charges

The invariant mass obtained from particles with concordant charges is not related to the K<sup>\*</sup> in any way since K<sup>\*</sup> only decays into pair of kaon/pion with discorcant charges. On the other hand when we consider combinations of particles with discordant charges some of them are the result of the K<sup>\*</sup> decay and others are not. As a consequence by subtructing these invariant masses we get the K<sup>\*</sup> .

### Difference between the invariant masses of Kaons and Pions with concordant and discordant charges

This method is the same as the one before, but in this case we are only considering Kaons and Pions, reducing the rumour.

The peak in these graph represents the mass of the K<sup>\*</sup>, whereas the standard deviation represents half the decay width.

![Invariant mass](invmass.png)






