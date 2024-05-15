#include "QAMdemodulator.h"
# define _EPS			0.1

QAMdemodulator::QAMdemodulator(const std::vector<double>& Signal, const int& type, const int sig_len) {
	int coef = 0;
	std::vector<std::complex<double>> coefs;
	switch (type)
	{
	case 4:
		coef = 2;
		break;
	case 16:
		coef = 4;
		break;
	case 64:
		coef = 6;
		break;
	default:
		break;
	}
	double real_LPF = 0;
	double im_LPF = 0;
	double t = 0, dt = 1.0 / frd;
	for (int i = 0; i < sig_len * coef * (frd / Br); ++i, t += dt) {
		double Re = Signal[i] * cos(M_PI * 2 * t * fr);
		double Im = Signal[i] * sin(M_PI * 2 * t * fr);
		real_LPF += Re;
		im_LPF += Im;
		if (i % (coef * (frd / Br)) == (coef * (frd / Br)) - 1) {
			coefs.push_back({ 2 * real_LPF / coef / (frd / Br), 2 * im_LPF / coef / (frd / Br) });
			real_LPF = 0;
			im_LPF = 0;
		}
	}



	for (int i = 0; i < coefs.size(); ++i) {
		switch (type)
		{
		case 4:
			str_res.push_back(QAM4d(coefs[i]));
			break;
		case 16:
			str_res.push_back(QAM16dc(coefs[i].real()) + QAM16dc(coefs[i].imag()));
			break;
		case 64:
			str_res.push_back(QAM64dc(coefs[i].real()) + QAM64dc(coefs[i].imag()));
			break;
		default:
			break;
		}
	}

}



std::string QAMdemodulator::QAM4d(const std::complex<double>& z) {

	std::string str = "00";
	std::complex<double> _z = { z.real() * sqrt(2), z.imag() * sqrt(2) };
	if (_z.real() > 0) {
		str[0] = '1';
	}
	if (_z.imag() > 0) {
		str[1] = '1';
	}

	return str;
}

std::string QAMdemodulator::QAM16dc(const double & c) {
	std::string str = "00";

	if (c > _EPS) {
		str[0] = '1';
		if (c > 1 + _EPS) {
			str[1] = '1';
		}
	}
	else if (c < -1 - _EPS) {
		str[1] = '1';
	}

	return str;

	return str;
}

std::string QAMdemodulator::QAM64dc(const double& c) {
	std::string str = "000";

	if (c > EPS) {
		str[0] = '1';
		if (c > 3 + EPS) {
			str[1] = '0';
			if (c > 5 + EPS) {
				str[2] = '0';
			}
			else {
				str[2] = '1';
			}
		}
		else {
			str[1] = '1';
			if (c > 1 + EPS) {
				str[2] = '1';
			}
		}
	}
	else {
		if (c < -3 - EPS) {
			str[1] = '0';
			if (c >= -5 - EPS) {
				str[2] = '1';
			}
		}
		else {
			str[1] = '1';
			if (c < -1 - EPS) {
				str[2] = '1';
			}
		}
	}

	return str;
}



