/*
   Copyright 2020 Daniel S. Buckstein

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
*/

/*
	GPRO-Graphics1-TestConsole-main.c/.cpp
	Main entry point source file for a Windows console application.

	Modified by: Ryan Burns
	Modified because: Code for creating a .ppm image had to be added in main()
*/


#include <stdio.h>
#include <stdlib.h>

#include <string>
#include <fstream>
#include <iostream>

#include "gpro/gpro-math/gproVector.h"


void testVector()
{
	// test array vector initializers and functions
	float3 av, bv, cv, dv;
	vec3default(av);								// -> a = (0, 0, 0)
	vec3init(bv, 1.0f, 2.0f, 3.0f);					// -> b = (1, 2, 3)
	vec3copy(dv, vec3init(cv, 4.0f, 5.0f, 6.0f));	// -> d = c = (4, 5, 6)
	vec3copy(av, dv);								// a = d			-> a = (4, 5, 6)
	vec3add(dv, bv);								// d += b			-> d = (4 + 1, 5 + 2, 6 + 3) = (5, 7, 9)
	vec3sum(dv, bv, bv);							// d = b + b		-> d = (1 + 1, 2 + 2, 3 + 3) = (2, 4, 6)
	vec3add(vec3sum(dv, cv, bv), av);				// d = c + b + a	-> d = (4 + 1 + 4, 5 + 2 + 5, 6 + 3 + 6) = (9, 12, 15)

#ifdef __cplusplus
	// test all constructors and operators
	vec3 a, b(1.0f, 2.0f, 3.0f), c(cv), d(c);		// default; init; copy array; copy
	a = d;											// assign						-> a = (4, 5, 6)
	d += b;											// add assign					-> d = (5, 7, 9)
	d = b + b;										// sum, init, assign			-> d = (2, 4, 6)
	d = c + b + a;									// sum, init, sum, init, assign	-> d = (9, 12, 15)
#endif	// __cplusplus
}


int main(int const argc, char const* const argv[])
{
	testVector();

#ifdef __cplusplus

	//Citation for this section
	https://raytracing.github.io/books/RayTracingInOneWeekend.html

	const int image_width = 256; //image dimensions
	const int image_height = 256;

	std::ofstream fout("image.ppm"); //file output stream (creates .ppm file)

	fout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

	for (int j = image_height - 1; j >= 0; j--) //int j starts at 255, subtracts 1 for every loop
	{
		std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush; //progress indicator

		for (int i = 0; i < image_width; i++) //int i starts at 0, adds 1 for every loop
		{
			double r = double(i) / static_cast<double>(image_width - 1); //increases as i increases (0 to 1)
			double g = double(j) / static_cast<double>(image_height - 1); //decreases as j decreases (1 to 0)
			double b = 0.25f; //always 0.25

			int ir = static_cast<int>(255.999 * r); //value for red: 0 -> 255
			int ig = static_cast<int>(255.999 * g); //value for green: 255 -> 0
			int ib = static_cast<int>(255.999 * b); //value for blue: constant 63

			fout << ir << ' ' << ig << ' ' << ib << '\n'; //output the sets of values to image.ppm
		}
	}

	std::cerr << "\nDone.\n"; //file has been read

	fout.close(); //close output file


	// I thought I should include this somewhere, but I'm really sorry that I didn't get very far in this assignment.
	// I was working on Chapter 3 in the reading, but what I was doing wasn't working.
	// I've been mostly focusing on an assignment for CSI-281 this week, and it took most of the time that I planned
	// to spend on this assignment. I decided that I would be auditing CSI-281 on Thursday, but most of my time for
	// this assignment was already gone. I just wanted to say that the quality of my work will not be like this
	// going forward, since I now only have one programming class this semester. My plan is to just do a short recording
	// of what I have right now, submit it, and read through the rest of Ray Tracing in One Weekend sometime before
	// I start working on Lab 2. It's been a very stressful week for me, I hope you understand.

#else

#endif

	printf("\n\n");
	system("pause");
}
