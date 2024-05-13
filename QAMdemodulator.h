#pragma once
#include<vector>
#include<complex>
#include<string>
#include<iostream>


# define M_PI           3.14159265358979323846  /* pi */
# define EPS			0.01
class QAMdemodulator
{
private:
	int frd = 80000;
	int Br = 2000, M;
	double I, Q;
	std::complex<double> val;
	double qamEl;
	int type;
	
public:
	std::vector<std::complex<double>> demodulated;
	std::vector<std::string> str_res;

	const int fr = 4000;
	/// <summary>
	/// 
	/// </summary>
	/// <param name="digitalData"></param>
	/// <param name="type"></param> must be 4, 16, 64
	QAMdemodulator(const std::vector<double>& Signal, const int& type, const int sig_len);
	std::string QAM4d(const std::complex<double>& z);
	std::string QAM16dc(const double& c);
	std::string QAM64dc(const double& c);
};

