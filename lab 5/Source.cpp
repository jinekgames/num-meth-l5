/*
*
*	Main.cpp
*	Test of Integral module
*
* 
*	https://github.com/jinekgames
*	no license
*
*/



#include <Windows.h>
#include "conio.h"

#include <iostream>
#include <vector>

#include <math.h>

#include "Integral.h"

#include "Params.h"



using namespace Integral_jnk;



// Get error value
#define GET_DELTA(res) \
	abs(res - tru_res)



int main() {

	// std::cout << Integral(f, 1, 2, INTERVAL_NUM(1)) << std::endl;



	std::cout << "Intergal calculation using trapeze meth\n" <<
		"Correct value calculated on paper by myself\n: " << tru_res <<
		"\n\n\n";


	std::cout << "Test 1\n\n";

	std::vector<DOUBLE> t1_res;

	size_t k = t1_n;
	for (size_t index = 0u; index < 4; index++) {
		const auto i = Integral(f, a, b, INTERVAL_NUM(k));
		t1_res.push_back(i);
		std::cout << " Ih (" << k << ") = " << i << "\n";
		std::cout << "  \t\terror: " << GET_DELTA(i) << "\n";
		k *= 2u;
	}

	std::cout << "\n\n\n";



	std::cout << "Test 2\n\n";

	const auto t2_res1 = Integral(f, a, b, INTERVAL_LEN(t2_l));
	std::cout << " Ih (" << t2_l << ") = " << t2_res1 << "\n";
	std::cout << "  \t\terror: " << GET_DELTA(t2_res1);

	const auto t2_res2 = Integral(f, a, b, INTERVAL_LEN(t2_l/2));
	std::cout << "\n Ih (" << t2_l/2 << ") = " << t2_res2 << "\n";
	std::cout << "  \t\terror: " << GET_DELTA(t2_res2);

	const DOUBLE del = t2_l / 2;
	const auto t2_res3 = Integral(f, a + del, b - del, INTERVAL_LEN(t2_l));
	const auto t2_resf = (t2_res2 + t2_res2) / 2;
	std::cout << "\n Ih (calculated from 2 iterations) t= " << t2_resf << "\n";
	std::cout << "  \t\terror: " << GET_DELTA(t2_resf);

	std::cout << "\n\n\n";








	// 2 fast for benching (
	//std::cout << "Test 3 (benchmark)\n\n";

	//std::cout << "input XTRA large number of intervals: ";
	//DOUBLE t3_n;	// cant be pre set cos compiler will calculate all during compiling 
	//std::cin >> t3_n;

	//auto time_start = GetTickCount64();
	//std::cout << "wait...";

	//std::cout << "Benchmark time: " << t1_l << GetTickCount64() - time_start << " ms\n";
	//const auto t3_res = Integral(f, a, b, INTERVAL_LEN(t3_n));
	//std::cout << " Ih = " << t3_res;
	//std::cout << "\n\n\n";







	_getch();
	return 0;

}


