/* SIMPLE MATHS LIBRARY
PREPARED BY GIZEM KAYAR FOR COMPUTER GRAPHICS COURSE/NEW YORK UNIVERSITY
YEAR: 2022
*/

//#include "pch.h"
#include "Simulation.h"
#define SIGN(x) (x >= 0 ? 1.0 : -1.0)
#include <stdlib.h>
#include "math3d.h"


void Simulation::initializeParticles()
{
	srand(0);

	float x, y, z;
	for (int i = 0; i < noPt; i++)
	{
		Particle  particle;

		//Set particle positions and velocities using srand and world positions
		x = ((float)rand() / RAND_MAX) * (halfWorld.getX() - (-halfWorld.getX())) + (-halfWorld.getX());
		y = ((float)rand() / RAND_MAX) * (halfWorld.getY() - (-halfWorld.getY())) + (-halfWorld.getY());
		z = ((float)rand() / RAND_MAX) * (halfWorld.getZ() - (-halfWorld.getZ())) + (-halfWorld.getZ());
		particle.setPosition(vector3f(x, y, z));

		x = ((float)rand() / RAND_MAX) * 1.0f - 0.5f;
		y = ((float)rand() / RAND_MAX) * 1.0f - 0.5f;
		z = ((float)rand() / RAND_MAX) * 1.0f - 0.5f;
		particle.setVelocity(vector3f(x, y, z));

		particle.clearForce();

		//Compute particle's old position for Verlet integration scheme
//		float h = particle.getPosition().getY() + halfWorld.getY();
//		vector3f temp = particle.getPosition() - particle.getVelocity() * h + particle.getForce() * h * h;
//		particle.setOldPosition(temp);


		particle.setIntegration(Euler);
		particle.setColor(vector3f(0, 0, 255));
		particle.setPosition(vector3f(particle.getPosition().getX(),
				(particle.getPosition().getY() + 0.1, 0), particle.getPosition().getZ()));


		particleList.push_back(particle);

	}
}

void Simulation::simulateEuler(Particle* p)
{
	    float mass = 1.0f;
	    float deltaT = timestep;

	    // Calculate acceleration using F = ma
	    vector3f accel = p->getForce() / mass;

	    // Update velocity using v = v0 + at
	    vector3f newVel;
	    vector3f accelDelta = accel * deltaT;
	    vector3f particleVel = p->getVelocity();
	    newVel = particleVel + accelDelta;

	    // Update position using x = x0 + vt
	    vector3f newPos;
	    vector3f newVelDelta = newVel * deltaT;
	    vector3f particlePos = p->getPosition();
		newPos = particlePos + newVelDelta;

	    // Update particle's state
	    p->setVelocity(newVel);
	    p->setPosition(newPos);
}


void Simulation::simulateEulerCromer(Particle* p)
{
    float deltaT = timestep;
    float mass = 1;

    // Calculate acceleration using F = ma
    vector3f force = p->getForce();
    vector3f accel = force / mass;

    // Update velocity using v = v0 + at
    vector3f oldVel = p->getVelocity();
    vector3f newVel;
    vector3f accelDelta = accel * deltaT;
    newVel = oldVel + accelDelta;

    // Update position using x = x0 + vt
    vector3f oldPos = p->getPosition();
    vector3f newPos;
    vector3f newVelDelta = newVel * deltaT;
	newPos = oldPos + newVelDelta;

    // Update particle's state
    p->setVelocity(newVel);
    p->setPosition(newPos);
}


void Simulation::clearForces()
{
	for (int i = 0; i < noPt; i++)
		particleList[i].clearForce();
}

void Simulation::destroyParticles()
{
	particleList.clear();
}

void Simulation::solveWorldCollision()
{
	vector3f tempVel;
	vector3f tempPos;

	for (int i = 0; i < noPt; i++)
	{
		tempVel = particleList[i].getVelocity();
		tempPos = particleList[i].getPosition();

		if (particleList[i].getPosition().getX() <= -halfWorld.getX() || particleList[i].getPosition().getX() >= halfWorld.getX())
		{
			tempVel.setX(tempVel.getX() * -worldColldConst);
			tempPos.setX(SIGN(tempPos.getX()) * halfWorld.getX());
		}

		if (particleList[i].getPosition().getY() <= -halfWorld.getY() || particleList[i].getPosition().getY() >= halfWorld.getY())
		{
			tempVel.setY(tempVel.getY() * -worldColldConst);
			tempPos.setY(SIGN(tempPos.getY()) * halfWorld.getY());
		}

		if (particleList[i].getPosition().getZ() <= -halfWorld.getZ() || particleList[i].getPosition().getZ() >= halfWorld.getZ())
		{
			tempVel.setZ(tempVel.getZ() * -worldColldConst);
			tempPos.setZ(SIGN(tempPos.getZ()) * halfWorld.getZ());
		}

		particleList[i].setVelocity(tempVel);
		particleList[i].setPosition(tempPos);
	}
}

void Simulation::computeSystemEnergies()
{
    float potentialEnergy = 0.0f;
    float kineticEnergy = 0.0f;

    for (int i = 0; i < particleList.size(); i++) {
        Particle& particle = particleList[i];

        // Calculate potential energy
        float mass = 1;
        float g = 9.8;
        vector3f position = particle.getPosition();
        float height = position.getY() + halfWorld.getY();
        float potentialEnergy_i = mass * g * height;
        potentialEnergy += potentialEnergy_i;

        // Calculate kinetic energy
        vector3f velocity = particle.getVelocity();
        float speedSquared = velocity.lengthSquare();
        float kineticEnergy_i = 0.5f * mass * speedSquared;
        kineticEnergy += kineticEnergy_i;
    }

    // Print out the system's total energy
    printf("Total Kinetic Energy: %f\n", kineticEnergy);
    printf("Total Potential Energy: %f\n", potentialEnergy);
}


