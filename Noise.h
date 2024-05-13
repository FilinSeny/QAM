#include<random>
#include<vector>
class Noise
{
private:
	const double min = 0;
	const double max;
	std::default_random_engine gausGenerator;
public:
	Noise(std::vector<double>& v, double d = 0.1) : max(d) {
		std::normal_distribution<double> noise(min, max);
		for (auto& el : v) {
			el += noise(gausGenerator);
		}
	}
};

