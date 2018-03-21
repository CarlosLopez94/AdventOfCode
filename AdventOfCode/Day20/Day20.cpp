#include "Day20.h"
#include "../Util.h"
#include "iostream"
#include "set"

int Day20::Main() {
	std::cout << "Day 20 - Part 1" << std::endl;
	std::vector<std::string> input = Util::ReadFile("../AdventOfCode/Day20/input.txt");
	std::vector<Particle*> particles;
	std::map<Particle*, int> manhattan;
	std::map<Particle*, int> closest;
	//Init particles and print it
	InitParticles(particles, input);
	PrintParticles(particles);
	int const LIMIT_CLOSEST = 500;
	int maximumClosest = 0;
	Particle* closestParticle = nullptr;
	while (maximumClosest < LIMIT_CLOSEST) {
		UpdateParticles(particles);
		//PrintParticles(particles);

		//Destroy particles that collide this iteration
		DestroyOnCollision(particles);

		//Calculate manhattan
		ManhattanDistanceForParticles(particles, manhattan);
		//manhattan map is sorted, closest will be in the first position

		//Get Closest this iteration
		closestParticle = GetClosestToOrigin(manhattan);
		if (closest.find(closestParticle) != closest.end()) {//already inserted
			closest[closestParticle] = closest[closestParticle] + 1;
		} else {
			closest[closestParticle] = 1;
		}

		maximumClosest = closest[closestParticle];
		if (maximumClosest % 500 == 0) {
			std::cout << "Id particle '" << closestParticle->id << "' is getting closer with: " << maximumClosest << std::endl;
		}
	}

	std::cout << "Id of closest particle: " << closestParticle->id << std::endl;
	std::cout << "Part 2" << std::endl;
	std::cout << "There are only " << particles.size() << " particles remains"<<std::endl;

	return 0;
}

void Day20::InitParticles(std::vector<Particle*>& particles, std::vector<std::string> particlesString) {
	int id = 0;
	for (std::string line : particlesString) {
		Particle* newParticle = new Particle();
		newParticle->id = id;
		auto tokens = Util::Split(line, ">");
		//position
		auto posTokens = Util::Split(Util::Split(tokens[0], "<")[1], ",");
		newParticle->p.x = std::stoi(posTokens[0]);
		newParticle->p.y = std::stoi(posTokens[1]);
		newParticle->p.z = std::stoi(posTokens[2]);
		//velocity
		auto velTokens = Util::Split(Util::Split(tokens[1], "<")[1], ",");
		newParticle->v.x = std::stoi(velTokens[0]);
		newParticle->v.y = std::stoi(velTokens[1]);
		newParticle->v.z = std::stoi(velTokens[2]);
		//aceleration
		auto acelTokens = Util::Split(Util::Split(tokens[2], "<")[1], ",");
		newParticle->a.x = std::stoi(acelTokens[0]);
		newParticle->a.y = std::stoi(acelTokens[1]);
		newParticle->a.z = std::stoi(acelTokens[2]);

		particles.push_back(newParticle);
		id++;
	}
}

void Day20::UpdateParticles(std::vector<Particle*>& particles) {
	for (int i = 0; i < particles.size(); i++) {
		UpdateParticle(particles, i);
	}
}

void Day20::UpdateParticle(std::vector<Particle*>& particles, int id) {
	Particle* par = particles[id];
	//Increase velocitity
	par->v.x += par->a.x;
	par->v.y += par->a.y;
	par->v.z += par->a.z;

	//Increase position
	par->p.x += par->v.x;
	par->p.y += par->v.y;
	par->p.z += par->v.z;

	particles[id] = par;
}

void Day20::ManhattanDistanceForParticles(std::vector<Particle*> particles, std::map<Particle*, int>& manhattan) {
	for (Particle* par : particles) {
		ManhattanDistance(par, manhattan);
	}
}

void Day20::ManhattanDistance(Particle* particle, std::map<Particle*, int>& manhattan) {
	manhattan[particle] = std::abs(particle->p.x) + std::abs(particle->p.y) + std::abs(particle->p.z);
}

Day20::Particle* Day20::GetClosestToOrigin(std::map<Particle*, int> manhattan) {
	Particle* par;
	auto it = manhattan.begin();
	par = it->first;
	while (it != manhattan.end()) {
		if (manhattan[par] > it->second) {
			par = it->first;
		}
		it++;
	}
	return par;
}


void Day20::DestroyOnCollision(std::vector<Particle*>& particles) {
	////Get positions of all particles
	std::map<Vector3D, std::set<Particle*>> positions;
	for (Particle* par : particles) {
		const Vector3D a = par->p;
		positions[a].insert(par);
	}

	auto it = positions.begin();
	while (it != positions.end()) {
		if (it->second.size()>1) { //there is a collision
			for (Particle* parCollide : it->second) {
				//Destroy particle
				particles.erase(std::remove(particles.begin(), particles.end(), parCollide), particles.end());
			}
		}

		it++;
	}

}

void Day20::PrintParticles(std::vector<Particle*> particles) {
	for (Particle* particle : particles) {
		PrintParticle(particle);
	}
	std::cout << std::endl;
}

void Day20::PrintParticle(Particle* par) {
	//p=<-3787,-3683,3352>, v=<41,-25,-124>, a=<5,9,1>
	//position
	std::cout << "(p=<" << par->p.x << ',' << par->p.y << ',' << par->p.z << ">, ";
	//velocity
	std::cout << "v=<" << par->v.x << ',' << par->v.y << ',' << par->v.z << ">, ";
	//aceleration
	std::cout << "a=<" << par->a.x << ',' << par->a.y << ',' << par->a.z << ">)" << std::endl;
}
