#pragma once

#include<vector>
#include<complex>
#include<string>
#include<iostream>


# define M_PI           3.14159265358979323846  /* pi */
class QAMmodulator
{
private:
	int frd = 80000;
	int Br = 2000, M;
	double I, Q;
	std::complex<double> val;
	double qamEl;
	int type;
	void modulate(const std::string & digital_word);

public:
	std::vector<double> modulated;
	std::vector<std::complex<double>> IQ;
	const int fr = 4000;
	/// <summary>
	/// 
	/// </summary>
	/// <param name="digitalData"></param>
	/// <param name="type"></param> must be 4, 16, 64
	QAMmodulator(const std::vector<std::string> & digitalData, const int & type);

};

