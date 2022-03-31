/// @brief Musical Notes Application Programming Interface (API) Implementation File
/// CPSC-298-6 Programming in C++ Project Musical Note Frequencies with Functions
/// @author chinnici@chapman.edu

#include <iostream>
#include <string>
#include <cmath>
#include "MusicalNoteApi_incomplete.h"


double computeFrequency(int nu, int k)
{
	double f = -1.0; // computed frequency in Hertz (Hz) 

	// Preconditions:
	// k > 0
	// k < Number of Halftones (12)
	// n > 0

	// /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/ //
	// TODO: Write a conditional expression that checks the preconditions of the function as
	//       specified in the function's preamble comments in the header file (and also listed
	//       above). The expression consists of three relational expressions (involving the >= 
	//       and < operators) that ANDed togeher (using the && operator).
	//       Observant students will note these preconditions are identical to those of 
	//       another function in the Music Notes API.
	//      if ((? >= 0) && (? < ?) && (?? >= 0))
	// /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/ //
	if ((k >= 0) && (k < k_nHalfTonesInOctave) && (nu >= 0))
	{
        f = k_dFrequencyRef * pow(2 , nu + (k/12.0));
	}
	else
	{
		std::cerr << "ERROR: computeFrequency preconditions not satisfied; dFrequencyHz nu (" << nu << ") or k (" << k << ") invalid" << std::endl;
	}

	return f;
}

double computeWavelengthInCm(double dFrequencyHz)
{

	double dWavelengthCm = -1.0; // Computed wavelength in centimeters returned by computeWavelengthInCm

	// Preconditions:
	// dFrequencyHz > 0.0
	// dFrequencyHz must be finite (i.e. not positive or negative infinity, or a signaling or quiet Not-a-Number).
	//       Infinite frequency makes no sense (not even Jimi Hendrix can do that) and is treated as 
	//       an error.

	// The expressions below check the negation of the preconditions and report an error. 
	// Report an error if dFrequencyHz < 0.0
	// Report an error if dFrequencyHz is not finite (a NaN or positive or negative infinity)
	// Report an error if dFrequencyHz is exactly 0 (including either positive or negative zero).
	//      A frequency of zero produces no wave at all and thus has no wavelength at all; zero 
	//      frequency makes no sense for this
	//      function and is treated as an error.)
	if ((dFrequencyHz < 0.0) || (!std::isfinite(dFrequencyHz)) || (FP_ZERO == std::fpclassify(dFrequencyHz)))
	{
		dWavelengthCm = -1.0; // Indicate Error
		std::cerr << "ERROR: computeWavelengthInCm preconditions not satisfied; dFrequencyHz invalid: " << dFrequencyHz << std::endl;
	}
	else {
		// Input satisfies all preconditions; perform computation

		// /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/ //
		// TODO: Calculate the wavelength in centimeters and assign the value to the double precision
		//       variable dWavelengthCm. Use one of the constants defined in the header file.
		// /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/ //
        dWavelengthCm = k_dSpeedOfSoundCmPerSecond / dFrequencyHz;
	}

	return dWavelengthCm;
}

const std::string getNoteName(int nu, int k)
{

	const static std::string a_strNotePrefix[] = {
			"C", "C#", "D","D#", "E", "F", "F#", "G", "G#", "A", "A#", "B",
	};

	std::string strNote = "UNK";

	// Preconditions:
	// k > 0
	// k < Number of Halftones (12)
	// n > 0
	if ((k >= 0) && (k < k_nHalfTonesInOctave) && (nu >= 0))
	{
		// /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/ //
		// TODO: Express strNote in terms of an element of a_strNotePrefix and the stringized form of
		//       the integer nu.
		// 
		//       Use std::to_string to covert integer nu to a string. 
		// 
		//       Concatenate the prefix with the string representation 
		//       of nu to form the note name. For example, "C#0" = "C#" + "0"
		// 
		//       strNote = a_strNotePrefix[?] + ?
		// /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/ //
        strNote = a_strNotePrefix[nu] + std::to_string(k_nHalfTonesInOctave);
	}

	return strNote; 
}

int main()
{
	int nOctaves = 11; // Number of octaves over which to compute frequencies.

	// Compute for Octaves 0 through 10 (previously you computed only zero through 8)
	for (int nu = 0; nu < nOctaves; nu++)
	{
		for (int k = 0; k < k_nHalfTonesInOctave; k++)
		{
		
            double f = computeFrequency(nu,k);
            double dWavelengthCentimeters = computeWavelengthInCm(f);

            std::string strNote = getNoteName(nu,k);


			std::cout << "Note: " << strNote << "; nu: " << nu << "; k: " << k << "; frequency: " << f << " Hz; wavelength: " << dWavelengthCentimeters << " cm" << std::endl;

		}
	}

	std::cout << std::endl << std::endl;
	std::cout << "------------------------------------------------ CHECK ERROR HANDLING ---------------------------------------------------------------" << std::endl;


    double f = computeFrequency(-1,-1);
    double dWavelengthCentimeters = computeWavelengthInCm(-16.35);

    std::string strNote = getNoteName(-1,-1);

	
	std::cout << "Note: " << strNote << "; nu: -1; k: -1; frequency: " << f << " Hz; wavelength: " << dWavelengthCentimeters << " cm" << std::endl;

	return 0;
}
