
#include "QAMdemodulator.h"
#include "QAMmodulator.h"
#include <iostream>
#include "Noise.h"
#include<random>


std::vector<std::string> gen_test(const int& type) {
    int n = 0;
    int start = 0;
    int stop = 0;
    std::vector<std::string> res;
    switch (type)
    {
    case 4:
        n = 2;
        stop = 0x4;
        break;
    case 16:
        n = 4;
        stop = 0x10;
        break;
    case 64:
        n = 6;
        stop = 0x1 << 6;

    default:
        break;
    }

    while (start != stop) {
        std::string str;
        unsigned int mask = 0x1 << (n - 1);
        for (int i = 0; i < n; ++i, mask >>= 1) {
            if (start & mask) {
                str += '1';
            }
            else {
                str += '0';
            }
        }
        res.push_back(str);
        start++;
    }

    return res;
}


template<typename T>
std::ostream& operator << (std::ostream & out, const std::vector<T>& v) {
    for (T el : v) {
        out << el << ' ';
    }
    return out;
}

template<typename T>
std::ostream& operator << (std::ostream & out, const std::complex<T>& v) {
    out << "(" << v.real() << " , " << v.imag() << ")";
    return out;
}



int test(int n, double d = 0.1)
{
    
    auto data = gen_test(n);
    ///std::cout << data << std::endl;
    QAMmodulator MyQAMm(data, n);
    ///std::cout << MyQAMm.IQ << std::endl;
    auto signal = MyQAMm.modulated;
    Noise noise(signal, d);

    QAMdemodulator MyQAMd(signal, n, data.size());

    int nerror = 0;
    for (int i = 0; i < data.size(); ++i) {
        for (int j = 0; j < data[i].size(); ++j) {
            if (data[i][j] != MyQAMd.str_res[i][j]) {
                ++nerror;
                ///std::cout << data[i] << ' ' << MyQAMd.str_res[i] << std::endl;
            }
        }
    }

    return nerror;
    
}



std::vector<std::string> seq_test(const int& type, int k = 100) {
    int n = 0;
    int start = 0;
    int stop = 0;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 1);
    std::vector<std::string> res;
    switch (type)
    {
    case 4:
        n = 2;
        stop = 0x4;
        break;
    case 16:
        n = 4;
        stop = 0x10;
        break;
    case 64:
        n = 6;
        stop = 0x1 << 6;

    default:
        break;
    }

    for (int i = 0; i < k; ++i) {
        std::string str;
        for (int j = 0; j < n; ++j) {
            if (dis(gen)) {
                str += '1';
            }
            else {
                str += '0';
            }
        }
        res.push_back(str);
    }

    return res;
}



int main() {
    double d;
    std::cin >> d;
    
    std::cout << test(4, d) << std::endl;
    std::cout << test(16, d) << std::endl;
    std::cout << test(64, d) << std::endl;
}