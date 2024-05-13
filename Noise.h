#include<random>
#include<vector>
class Noise
{
private:
	const double min = -0.5;
	const double max = 0.5;
	std::default_random_engine gausGenerator;
public:
	Noise(std::vector<double>& v) {
		std::normal_distribution<double> noise(min, max);
		for (auto& el : v) {
			el += noise(gausGenerator);
		}
	}
};

