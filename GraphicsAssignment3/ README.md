William Qin
Professor Kayar
Computer Graphics 
Assignment 3

###Setup:
I am using a M1 Macbook Pro, running MacOS Ventura 13.0.1. I have encountered numerous issues due to m1 arm architecture as well macOS not being compatible with the code. Originally I thought I could just try searching for a mac alternative for WinAPI, but the code is too complex to be converted. I rendered a square to show that I did search for an alternative that works on mac. The program that works for mac m1 is XQuartz. However, getting any further proved impossible without deep knowledge of the GLUT framework, which we didn't learn. I think the purpose of the assignment was to learn about physic simulations systems, not the GLUT framework. Because of this, I wasn't able to thoroughly check the syntax of my code, but I believe the logic should be correct.

###Part 1:

#simulateEuler:
In the simulateEuler function, the velocity of a particle is updated by using the acceleration that is calculated from the current position of the particle. Then, the position of the particle is updated using the new velocity. This implies that the new position of the particle is dependent on the old velocity, and the new velocity of the particle is dependent on the new acceleration.

#simulateEulerCromer:

In the simulation method called simulateEulerCromer, the update process is different compared to simulateEuler. In this method, the position is first updated using the current velocity, and only then the velocity is updated using the new acceleration calculated from the updated position. This update process means that the new velocity is based on the old acceleration, and the new position is based on the new velocity. This method is similar to simulateEuler, but with the order of updating the position and velocity swapped.

#computeSystemEnergies:
The code computes the potential and kinetic energies of each particle in the system. The potential energy is calculated using the formula potentialEnergy_i = mass * g * height, where mass is the mass of the particle, g is the acceleration due to gravity, and height is the distance of the particle from a reference point (halfWorld.getY() in this case, which is half of the world size in the y-direction). It is assumed that the reference point has zero potential energy. On the other hand, the kinetic energy is calculated using the formula kineticEnergy_i = 0.5f * mass * speedSquared, where mass is the mass of the particle, speedSquared is the square of the particle's speed, and the factor of 0.5f is a constant that appears in the formula for kinetic energy. Finally, the code sums up the kinetic and potential energies of each particle to compute the total kinetic and potential energy of the system. These values are then printed out.

###Part 2:

#Simulation.h

#applyForces:
The given function has two parts: the first part applies gravity to all particles, and the second part applies spring forces to particles that are connected by springs. In the first part, a gravitational force is applied to each particle by setting the force variable of each particle to a vector that is scaled by the particle's mass and acceleration. This force is calculated for each particle, and it is applied in the direction opposite to the y-axis. In the second part, the spring forces are applied to all the connected particles. For each spring, the spring vector between the two connected particles is calculated and normalized. This is done to get the direction of the spring force. After that, the Hooke's law is applied to calculate the spring force based on the difference between the current length of the spring and its rest length. This force is added to one of the particles and subtracted from the other. The damping force is also calculated based on the relative velocity of the particles, and it is added to one particle and subtracted from the other.

#Simulation.cpp:

#computeSystemEnergies:
The function computes the total energy of a particle system. It does this by computing the kinetic energy, potential energy, and spring energy of each particle and spring, and adding them up. The variables are initialized to 0.0f. Then, it iterates over all particles in the mesh object, computes their kinetic and potential energy, and adds them to kinEn and potEn.





