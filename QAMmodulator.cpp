#include "QAMmodulator.h"

QAMmodulator::QAMmodulator(const std::vector<std::string>& digitalData, const int& _type) {
	type = _type;
	int dataLen = digitalData.size();
	std::vector<std::complex<double>> data;
	std::vector<double> times;
	double t = 0;
	double dt = 1.0 / frd;

	for (int i = 0; i < dataLen; ++i) {
		modulate(digitalData[i]);
		int n_rep = 0;
		switch (type)
		{
		case 4:
			n_rep = frd / Br * 2;
			break;
		case 16:
			n_rep = frd / Br * 4;
			break;
		case 64:
			n_rep = frd / Br * 6;
			break;
		default:
			break;
		}
		///std::cout << digitalData[i] << ' ' << I << ' ' << Q << std::endl;
		for (int j = 0; j < n_rep; ++j, t += dt) {
			///std::cout << t << std::endl;
			IQ.push_back({ I, Q });
			modulated.push_back((I * cos(2 * M_PI * fr * t) + Q * sin(2 * M_PI * fr * t)));
		}
	}

}


void QAMmodulator::modulate(const std::string& digital_word) {
	I = 1;
	Q = 1;
	if (type == 4) {
		Q /= sqrt(2);
		I /= sqrt(2);
		if (digital_word[0] == '0') {
			I *= -1;
		}
		if (digital_word[1] == '0') {
			Q *= -1;
		}
	}
	else if (type == 16) {
		if (digital_word[0] == '0') {
			I *= -1;
		}
		if (digital_word[2] == '0') {
			Q *= -1;
		}
		if (digital_word[1] == '1') {
			I *= 3;
		}
		if (digital_word[3] == '1') {
			Q *= 3;
		}
	}
	else if (type == 64) {
		if (digital_word[0] == '0') {
			I *= -1;
		}
		if (digital_word[3] == '0') {
			Q *= -1;
		}
		if (digital_word[1] == '0' && digital_word[2] == '0') {
			I *= 7;
		}
		else if (digital_word[1] == '0' && digital_word[2] == '1') {
			I *= 5;
		}
		else if (digital_word[1] == '1' && digital_word[2] == '1') {
			I *= 3;
		}

		if (digital_word[4] == '0' && digital_word[5] == '0') {
			Q *= 7;
		}
		else if (digital_word[4] == '0' && digital_word[5] == '1') {
			Q *= 5;
		}
		else if (digital_word[4] == '1' && digital_word[5] == '1') {
			Q *= 3;
		}

	}
	else {
		std::cerr << "Wrong type of QAM" << std::endl;
	}
}