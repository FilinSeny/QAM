#include<random>
#include<vector>
#include<iostream>
class Noise
{
private:
	const double min = 0;
	const double max;
	std::default_random_engine gausGenerator;
	std::normal_distribution<double> noise;
public:
	Noise( double d = 0.1) : max(d), noise(min, max){
	}

	void add_noise(std::vector<double>& v) {
		for (auto& el : v) {
			el += noise(gausGenerator);
			///std::cout << el << ' ';
		}
	}
};

