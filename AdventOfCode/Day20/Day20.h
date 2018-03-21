#pragma once
#include "vector"
#include "string"
#include "map"

class Day20
{
public:
	int Main();
private:
	struct Vector3D {
		int x = 0;
		int y = 0;
		int z = 0;

		bool operator==(Day20::Vector3D v) const{
			return x == v.x && y == v.y && z == v.z;
		}

		bool operator<(Day20::Vector3D v) const{
			return x < v.x || (x == v.x && y < v.y) || (x == v.x && y == v.y && z < v.z);
		}
	};

	struct Particle {
		int id;
		Vector3D p;
		Vector3D v;
		Vector3D a;

		bool operator==(Particle par) const {
			return p == par.p && v == par.v && a == par.a;
		}

		bool operator<(Particle par) const{
			return p < par.p;
		}
	};

	void InitParticles(std::vector<Particle*>& particles, std::vector<std::string> particleString);
	void UpdateParticles(std::vector<Particle*>& particles);
	void UpdateParticle(std::vector<Particle*>& particles, int id);
	void ManhattanDistanceForParticles(std::vector<Particle*> particles, std::map<Particle*, int>& manhattan);
	void ManhattanDistance(Particle* particles, std::map<Particle*, int>& manhattan);
	Particle* GetClosestToOrigin(std::map<Particle*, int> manhattan);

	//Part 2
	void DestroyOnCollision(std::vector<Particle*>& particles);

	//Print
	void PrintParticles(std::vector<Particle*> particles);
	void PrintParticle(Particle* par);
};

