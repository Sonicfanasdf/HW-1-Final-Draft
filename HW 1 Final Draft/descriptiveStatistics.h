//Credit: Otoniel Torres Bernal and Oscar Gallardo 
#pragma once
#include <cstdlib>
#include <iomanip>
#include <stdexcept>
#include <limits>
#include <cmath>
#include <algorithm>
#include <sstream>

void menu();
void chooseOption();
void displayArray(int* array, int size);

// PRECONDITION: none
// POSTCONDITION: the menu options for descriptive statistics are displayed on the standard output.
void displayDescriptiveStatisticsMenu()
{
	cout << "3> Descriptive Statistics" << endl;
	cout << "************************************************************" << endl;
	cout << "A> Read, store, and display data set   M> Mid Range" << endl;
	cout << "B> Minimum                             N> Quartiles " << endl;
	cout << "C> Maximum                             O> Interquartile Range" << endl;
	cout << "D> Range                               P> Outliers" << endl;
	cout << "E> Size                                Q> Sum of Squares" << endl;
	cout << "F> Sum                                 R> Mean Absolute Deviation" << endl;
	cout << "G> Mean                                S> Root Mean Square" << endl;
	cout << "H> Median                              T> Standard Error of the Mean" << endl;
	cout << "I> Frequencies                         U> Coefficient of Variation" << endl;
	cout << "J> Mode                                V> Relative Standard Deviation" << endl;
	cout << "K> Standard Deviation                  W> Display and write all results to text file" << endl;
	cout << "L> Variance                                         " << endl;
	cout << "************************************************************" << endl;
	cout << "X. Return" << endl;
	cout << "************************************************************" << endl;
	cout << "Option: ";
}
// PRECONDITION: the 'array' should be a dynamically allocated array sorted in ascending order, 'size' should represent the number of elements in 'array'.
// POSTCONDITION: 'array' will be resized, and 'element' will be inserted in a way that keeps the array sorted, 'size' will be incremented by 1 to reflect the new size of the array.
void insertSorted(int*& arr, int& n, int num) {
	int* newArr = new int[n + 1];

	int i;
	for (i = 0; i < n; ++i) {
		if (arr[i] > num) break;
		newArr[i] = arr[i];
	}

	newArr[i] = num;

	for (; i < n; ++i) {
		newArr[i + 1] = arr[i];
	}

	delete[] arr;
	arr = newArr;
	++n;
}
// PRECONDITION: 'filename' should be a valid file name, 'arrayInts' should be a pointer to an array of integers, 'count' should be an integer representing the number of elements in 'arrayInts'.
// POSTCONDITION: 'arrayInts' will be resized to hold the integers read from the file, 'count' will be updated to reflect the new size of 'arrayInts'.
void readIntsFromFile(const string& filename, int*& arrayInts, int& count) {
	ifstream file(filename);

	if (!file.is_open()) {
		throw runtime_error("Unable to open the file");
	}

	count = 0;
	int number;

	while (file >> number) {
		insertSorted(arrayInts, count, number);
	}

	file.close();
}
// PRECONDITION: arrayInts is a non-null pointer, count > 0
// POSTCONDITION: finds the minimum value in 'arrayInts' and returns it, throws an error if 'arrayInts' is empty.
int findMinimum(int* arrayInts, int count) {
	if (count == 0) {
		throw runtime_error("The array is empty, cannot find minimum.");
	}

	int minVal = numeric_limits<int>::max();
	for (int i = 0; i < count; ++i) {
		if (arrayInts[i] < minVal) {
			minVal = arrayInts[i];
		}
	}

	return minVal;
}
// PRECONDITION: arrayInts is a non-null pointer, count > 0
// POSTCONDITION: finds the maximum value in 'arrayInts' and returns it, throws an error if 'arrayInts' is empty.
int findMaximum(int* arrayInts, int count) {
	if (count == 0) {
		throw runtime_error("The array is empty, cannot find maximum.");
	}

	int maxVal = numeric_limits<int>::min();
	for (int i = 0; i < count; ++i) {
		if (arrayInts[i] > maxVal) {
			maxVal = arrayInts[i];
		}
	}

	return maxVal;
}
// PRECONDITION: arrayInts is a non-null pointer, count > 0
// POSTCONDITION: calculates the average of the values in 'arrayInts' and returns it as a double, throws an error if 'arrayInts' is empty.
double calculateAverage(int* arrayInts, int count) {
	if (count == 0) {
		throw runtime_error("The array is empty, cannot calculate average.");
	}

	int sum = 0;
	for (int i = 0; i < count; ++i) {
		sum += arrayInts[i];
	}

	return static_cast<double>(sum) / count;
}
// PRECONDITION: arrayInts is a non-null pointer, count > 0, and count should be at least 2.
// POSTCONDITION: calculates the sample standard deviation of the values in 'arrayInts' and returns it as a double, throws an error if 'arrayInts' contains fewer than two elements.
double calculateStandardDeviation(int* arrayInts, int count) {
	if (count == 0) {
		throw runtime_error("The array is empty, cannot calculate standard deviation.");
	}

	double mean = calculateAverage(arrayInts, count);
	double sumOfSquares = 0;

	for (int i = 0; i < count; ++i) {
		sumOfSquares += (arrayInts[i] - mean) * (arrayInts[i] - mean);
	}

	return sqrt(sumOfSquares / (count - 1));
}
// PRECONDITION: arrayInts is a non-null pointer, count > 0
// POSTCONDITION: calculates the sum of the values in 'arrayInts' and returns it as an integer, throws an error if 'arrayInts' is empty.
int findSum(int* arrayInts, int count) {
	if (count == 0) {
		throw runtime_error("The array is empty, cannot find sum.");
	}

	int sum = 0;
	for (int i = 0; i < count; ++i) {
		sum += arrayInts[i];
	}

	return sum;
}
// PRECONDITION: arrayInts is a non-null pointer, count > 0
// POSTCONDITION: calculates the mean (average) of the values in 'arrayInts' and returns it as a double, throws an error if 'arrayInts' is empty.
double findMean(int* arrayInts, int count) {
	if (count == 0) {
		throw runtime_error("The array is empty, cannot find mean.");
	}

	return calculateAverage(arrayInts, count);  // average and mean are the same
}
// PRECONDITION: arrayInts is a non-null pointer, count > 0
// POSTCONDITION: sorts the array 'arrayInts' and calculates the median, returning it as a double, throws an error if 'arrayInts' is empty.
double findMedian(int* arrayInts, int count) {
	if (count == 0) {
		throw runtime_error("The array is empty, cannot find median.");
	}

	sort(arrayInts, arrayInts + count);

	if (count % 2 == 0) {
		return (arrayInts[count / 2 - 1] + arrayInts[count / 2]) / 2.0;
	}
	else {
		return arrayInts[count / 2];
	}
}
// PRECONDITION: arrayInts is a non-null pointer, count > 0
// POSTCONDITION: finds the range of the integers in 'arrayInts' and returns it, throws an error if 'arrayInts' is empty.
int findRange(int* arrayInts, int count) {
	if (count == 0) {
		throw runtime_error("The array is empty, cannot find range.");
	}

	int minVal = arrayInts[0];
	int maxVal = arrayInts[0];

	for (int i = 1; i < count; ++i) {
		if (arrayInts[i] < minVal) minVal = arrayInts[i];
		if (arrayInts[i] > maxVal) maxVal = arrayInts[i];
	}

	return maxVal - minVal;
}
// PRECONDITION: arrayInts is a non-null pointer, count > 0, the array should also be sorted for frequency counts to be accurate.
// POSTCONDITION: calculates the frequencies and percentages of each unique integer, in 'arrayInts' and displays them, throws an error if 'arrayInts' is empty, returns nothing.
void findFrequencies(int* arrayInts, int count) {
	if (count == 0) {
		throw runtime_error("The array is empty, cannot find freqencies.");
	}

	cout << "ELEMENT\tFREQUENCY\tPECENTAGE" << endl;
	cout << "=======\t=========\t==========" << endl;

	int frequency = 1;
	for (int i = 0; i < count; ++i) {
		if (i < count - 1 && arrayInts[i] == arrayInts[i + 1]) {
			++frequency;
		}
		else {
			double percentage = ((double)frequency / count) * 100;
			cout << arrayInts[i] << "\t" << frequency << "\t\t" << percentage << "%" << endl;
			frequency = 1;
		}
	}
}
// PRECONDITION:  arrayInts is a non-null pointer, count > 0, 'arrayInts' should be sorted in ascending order for accurate mode calculation.
// POSTCONDITION: finds the mode (most frequent element) in 'arrayInts' and prints it along with its frequency. If no mode is found (i.e., all numbers appear only once),
// a message is printed indicating that no mode exists, throws an error if 'arrayInts' is empty.
void findMode(int* arrayInts, int count) {
	if (count == 0) {
		throw runtime_error("The array is empty, cannot find mode.");
	}

	int highestFreq = 0;
	int mode = arrayInts[0];
	int freq = 1;

	for (int i = 1; i < count; ++i) {
		if (arrayInts[i] == arrayInts[i - 1]) {
			++freq;
		}
		else {
			freq = 1;
		}
		if (freq > highestFreq) {
			highestFreq = freq;
			mode = arrayInts[i];
		}
	}

	if (highestFreq == 1) {
		cout << "No mode found, all numbers appear only once." << endl;
	}
	else {
		cout << "Mode: " << mode << " (Frequency: " << highestFreq << ")" << endl;
	}
}
// PRECONDITION:  arrayInts is a non-null pointer, count > 0, 'count' should be greater than or equal to 2 for a valid variance calculation.
// POSTCONDITION: calculates the sample variance of the integers in 'arrayInts' and returns it, hrows an error if 'arrayInts' has fewer than two elements.
double findVariance(int* arrayInts, int count) {
	if (count == 0) {
		throw runtime_error("The array is empty, cannot find variance.");
	}
	if (count == 1) {
		throw runtime_error("Variance is undefined for a single-element dataset.");
	}

	// First calculate the mean
	int sum = 0;
	for (int i = 0; i < count; ++i) {
		sum += arrayInts[i];
	}
	double mean = static_cast<double>(sum) / count;

	// Now calculate the variance
	double variance = 0;
	for (int i = 0; i < count; ++i) {
		variance += pow(arrayInts[i] - mean, 2);
	}
	variance /= count - 1;

	return variance;
}
// PRECONDITION:  arrayInts is a non-null pointer, count > 0
// POSTCONDITION: calculates the midrange of the integers in 'arrayInts' and returns it, throws an error if 'arrayInts' is empty.
double findMidrange(int* arrayInts, int count) {
	if (count == 0) {
		throw runtime_error("The array is empty, cannot find midrange.");
	}

	int minVal = arrayInts[0];
	int maxVal = arrayInts[0];

	for (int i = 1; i < count; ++i) {
		if (arrayInts[i] < minVal) {
			minVal = arrayInts[i];
		}
		if (arrayInts[i] > maxVal) {
			maxVal = arrayInts[i];
		}
	}

	return static_cast<double>(minVal + maxVal) / 2;
}
// PRECONDITION: assumes findMedian is defined above this code, arrayInts is a non-null pointer, count > 0,
// POSTCONDITION: calcualtes and prints the first, second (median), and third quartiles of the integers in 'arrayInts', throws an error if 'arrayInts' is empty.
void findQuartiles(int* arrayInts, int count) {
	if (count == 0) {
		throw std::runtime_error("The array is empty, cannot find quartiles.");
	}

	// calculate Q2 (second quartile / median)
	double q2 = findMedian(arrayInts, count);
	std::cout << "Q2 (Second Quartile/Median): " << q2 << std::endl;

	if (count < 4) {
		std::cout << "The dataset is too small for first and third quartile calculation." << std::endl;
		return;
	}

	int lowerCount = count / 2;
	int upperCount = lowerCount;

	// if the dataset has an odd number, the upper half will have one more element.
	if (count % 2 != 0) {
		++upperCount;
	}

	int* lowerHalf = new int[lowerCount];
	int* upperHalf = new int[upperCount];

	for (int i = 0; i < lowerCount; ++i) {
		lowerHalf[i] = arrayInts[i];
	}

	int startIdxForUpper = (count % 2 == 0) ? lowerCount : (lowerCount + 1);
	for (int i = 0; i < upperCount; ++i) {
		upperHalf[i] = arrayInts[startIdxForUpper + i];
	}

	// calculate Q1 (first quartile) and Q3 (third quartile)
	double q1 = findMedian(lowerHalf, lowerCount);
	double q3 = findMedian(upperHalf, upperCount);

	// output the quartiles
	std::cout << "Q1 (First Quartile): " << q1 << std::endl;
	std::cout << "Q3 (Third Quartile): " << q3 << std::endl;

	delete[] lowerHalf;
	delete[] upperHalf;
}
// PRECONDITION: assumes findMedian is defined above this code.
// arrayInts is a non-null pointer, count > 0, 'count' should be greater or equal to 4 for valid interquartile range calculations.
// POSTCONDITION: calculates and returns the interquartile range of the integers in 'arrayInts', throws an error if 'arrayInts' has fewer than 4 elements.
double findInterquartileRange(int* arrayInts, int count) {
	if (count < 4) {
		throw std::runtime_error("The dataset is too small to calculate the interquartile range.");
	}

	int lowerCount = count / 2;
	int upperCount = lowerCount;

	// if the dataset has an odd number, the upper half will have one more element.
	if (count % 2 != 0) {
		++upperCount;
	}

	int* lowerHalf = new int[lowerCount];
	int* upperHalf = new int[upperCount];

	for (int i = 0; i < lowerCount; ++i) {
		lowerHalf[i] = arrayInts[i];
	}

	int startIdxForUpper = (count % 2 == 0) ? lowerCount : (lowerCount + 1);
	for (int i = 0; i < upperCount; ++i) {
		upperHalf[i] = arrayInts[startIdxForUpper + i];
	}

	// calculate Q1 and Q3
	double q1 = findMedian(lowerHalf, lowerCount);
	double q3 = findMedian(upperHalf, upperCount);

	delete[] lowerHalf;
	delete[] upperHalf;

	// calculate and return the interquartile range
	return q3 - q1;
}
// PRECONDITION: assumes findInterquartileRange and findMedian are defined above this code, arrayInts is a non-null pointer, count > 0, 'count' should be greater or equal to 4 for valid outlier identification.
// POSTCONDITION: calculates and outputs any outliers found in the dataset to the console, throws an error if 'arrayInts' has fewer than 4 elements.
void findOutliers(int* arrayInts, int count) {
	if (count < 4) {
		throw std::runtime_error("The dataset is too small to identify outliers.");
	}

	double iqr = findInterquartileRange(arrayInts, count);

	int lowerCount = count / 2;
	int upperCount = lowerCount;
	if (count % 2 != 0) {
		++upperCount;
	}

	int* lowerHalf = new int[lowerCount];
	int* upperHalf = new int[upperCount];

	for (int i = 0; i < lowerCount; ++i) {
		lowerHalf[i] = arrayInts[i];
	}

	int startIdxForUpper = (count % 2 == 0) ? lowerCount : (lowerCount + 1);
	for (int i = 0; i < upperCount; ++i) {
		upperHalf[i] = arrayInts[startIdxForUpper + i];
	}

	double q1 = findMedian(lowerHalf, lowerCount);
	double q3 = findMedian(upperHalf, upperCount);

	delete[] lowerHalf;
	delete[] upperHalf;

	double lowerFence = q1 - 1.5 * iqr;
	double upperFence = q3 + 1.5 * iqr;

	cout << "\nOutliers in the dataset: ";

	bool hasOutliers = false;
	for (int i = 0; i < count; ++i) {
		if (arrayInts[i] < lowerFence || arrayInts[i] > upperFence) {
			cout << arrayInts[i] << ' ';
			hasOutliers = true;
		}
	}

	if (!hasOutliers) {
		cout << "No outliers found.";
	}

	cout << endl << endl;
}
// PRECONDITION: arrayInts is a non-null pointer, count > 0
// POSTCONDITION: calculates and returns the sum of squares of deviations from the mean
double findSumOfSquares(int* arrayInts, int count) {
	if (count == 0) {
		throw std::runtime_error("The array is empty, cannot find sum of squares.");
	}

	double mean = findMean(arrayInts, count);
	double sumOfSquares = 0.0;

	for (int i = 0; i < count; ++i) {
		double deviation = static_cast<double>(arrayInts[i]) - mean;
		sumOfSquares += deviation * deviation;
	}

	return sumOfSquares;
}
// PRECONDITION: arrayInts is a non-null pointer, count > 0
// POSTCONDITION: calculates and returns the sum of absolute deviations from the mean
double findSumAbsoluteDeviation(int* arrayInts, int count, double mean) {
	if (count == 0) {
		throw std::runtime_error("The array is empty, cannot calculate sum of absolute deviations.");
	}

	double sumAbsoluteDeviation = 0;
	for (int i = 0; i < count; ++i) {
		sumAbsoluteDeviation += std::abs(arrayInts[i] - mean);
	}

	return sumAbsoluteDeviation;
}
// PRECONDITION: arrayInts is a non-null pointer, count > 0
// POSTCONDITION: calculates and returns the mean absolute deviation of the array
double findMeanAbsoluteDeviation(int* arrayInts, int count) {
	if (count == 0) {
		throw std::runtime_error("The array is empty, cannot calculate mean absolute deviation.");
	}

	double mean = findMean(arrayInts, count);  // use existing findMean function
	double sumAbsoluteDeviation = findSumAbsoluteDeviation(arrayInts, count, mean);
	double mad = sumAbsoluteDeviation / count;

	return mad;
}
// PRECONDITION: arrayInts is a non-null pointer, count > 0
// POSTCONDITION: calculates and returns the root mean square (RMS) of the array
double findRootMeanSquare(int* arrayInts, int count) {
	if (count == 0) {
		throw std::runtime_error("The array is empty, cannot calculate root mean square.");
	}

	double sumSquared = 0;
	for (int i = 0; i < count; ++i) {
		sumSquared += arrayInts[i] * arrayInts[i];
	}

	double rms = sqrt(sumSquared / count);
	return rms;
}
// PRECONDITION: arrayInts is a non-null pointer, count > 0, standardDeviation >= 0
// POSTCONDITION: calculates and returns the standard error of the array based on the provided standard deviation
double findStandardError(int* arrayInts, int count, double standardDeviation) {
	if (count == 0) {
		throw std::runtime_error("The array is empty, cannot calculate standard error.");
	}

	double standardError = standardDeviation / sqrt(count);
	return standardError;
}
// PRECONDITION: arrayInts is a non-null pointer, count > 0, standardDeviation >= 0, mean != 0
// POSTCONDITION: calculates and returns the coefficient of variation for the array based on the provided standard deviation and mean
double findCoefficientOfVariation(int* arrayInts, int count, double standardDeviation, double mean) {
	if (count == 0) {
		throw std::runtime_error("The array is empty, cannot calculate coefficient of variation.");
	}
	if (mean == 0) {
		throw std::runtime_error("Mean is zero, cannot calculate coefficient of variation.");
	}

	double coefficientOfVariation = (standardDeviation / mean);
	return coefficientOfVariation;
}
// PRECONDITION: arrayInts is a non-null pointer, count > 0, standardDeviation >= 0, mean != 0
// POSTCONDITION: calculates and returns the relative standard deviation for the array based on the provided standard deviation and mean
double findRelativeStandardDeviation(int* arrayInts, int count, double standardDeviation, double mean) {
	if (count == 0) {
		throw std::runtime_error("The array is empty, cannot calculate relative standard deviation.");
	}
	if (mean == 0) {
		throw std::runtime_error("Mean is zero, cannot calculate relative standard deviation.");
	}

	double relativeStandardDeviation = (standardDeviation / mean) * 100;  // As a percentage
	return relativeStandardDeviation;
}
// PRECONDITION: function expects that any function it calls is properly defined and assumes that any data file it tries to read from is properly formatted.
// POSTCONDITION: the function will perform multiple descriptive statistical operations based on the user's choice, the function will display the results on the screen and may write them to an output file.
// any dynamic memory allocated will be managed properly.
int descriptiveStatistics() {
	int* arrayInts = nullptr;
	int count = 0;
	char option;
	string inputLine;

	do {
		displayDescriptiveStatisticsMenu();
		std::getline(std::cin, inputLine);  // read the whole line

		std::stringstream ss(inputLine);
		ss >> option;  // try to extract a char

		if (ss.fail()) {  // failed to extract a char
			std::cin.clear();
			cout << "Invalid option. Please try again." << endl;
			system("pause");
			system("cls");
			continue;  // skip the remaining code in the loop and start from the beginning
		}

		// If the user entered extra characters after the first one
		if (!ss.eof()) {
			string extra;
			ss >> extra;
			if (!ss.fail()) {
				cout << "Invalid option. Please enter only a single character." << endl;
				system("pause");
				system("cls");
				continue;
			}
		}

		switch (toupper(option))
		{

		case 'A': // read, store, and display into sorted dynamic array
		{

			string filename;
			cout << "\nPlease enter the filename: ";
			cin >> filename;

			// clear the input buffer before reading the next line
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

			try {
				readIntsFromFile(filename, arrayInts, count);
				displayArray(arrayInts, count);
			}
			catch (const runtime_error& e) {
				cout << e.what() << endl;
			}
			break;
		}

		case 'B': // minimum


			try {
				int minVal = findMinimum(arrayInts, count);
				cout << "\nThe minimum value of the given data set is: " << minVal << endl << endl;
			}
			catch (const runtime_error& e) {
				cerr << e.what() << endl;
			}

			break;

		case 'C': // maximum

			try {
				int maxVal = findMaximum(arrayInts, count);
				cout << "\nThe maximum value of the given data set is: " << maxVal << endl << endl;
			}
			catch (const runtime_error& e) {
				cerr << e.what() << endl;
			}

			break;

		case 'D': // range


			try {
				int range = findRange(arrayInts, count);
				cout << "\nThe range of the given data set is: " << range << endl << endl;
			}
			catch (const runtime_error& e) {
				cerr << e.what() << endl;
			}

			break;

		case 'E': // size


			cout << "\nThe size of the given data set is: " << count << endl << endl;

			break;

		case 'F': // sum


			try {
				int sum = findSum(arrayInts, count);
				cout << "\nThe sum of the given data set is: " << sum << endl << endl;
			}
			catch (const runtime_error& e) {
				cerr << e.what() << endl;
			}

			break;

		case 'G': // mean


			try {
				double meanVal = findMean(arrayInts, count);
				cout << "\nThe mean of the given data set is: " << meanVal << endl << endl;
			}
			catch (const runtime_error& e) {
				cerr << e.what() << endl;
			}

			break;

		case 'H': // median


			try {
				double median = findMedian(arrayInts, count);
				cout << "\nThe median of the given data set is: " << median << endl << endl;
			}
			catch (const runtime_error& e) {
				cerr << e.what() << endl;
			}

			break;

		case 'I': // frequencies


			try {
				cout << endl;
				findFrequencies(arrayInts, count);
				cout << endl;
			}
			catch (const runtime_error& e) {
				cerr << e.what() << endl;
			}

			break;

		case 'J': // mode


			try {
				cout << endl;
				findMode(arrayInts, count);
				cout << endl;
			}
			catch (const runtime_error& e) {
				cerr << e.what() << endl;
			}

			break;

		case 'K': // standard deviation

			// new line
			cout << endl;

			try {
				double stddev = calculateStandardDeviation(arrayInts, count);
				cout << "The standard deviation of the given data set is: " << stddev << endl;

			}
			catch (const runtime_error& e) {
				cerr << e.what() << endl;
			}

			// new line
			cout << endl;



			break;

		case 'L': // variance


			try {
				double varianceVal = findVariance(arrayInts, count);
				cout << "\nThe variance of the given data set is: " << varianceVal << endl << endl;
			}
			catch (const runtime_error& e) {
				cerr << e.what() << endl;
			}

			break;

		case 'M': // midrange


			try {
				double midrangeVal = findMidrange(arrayInts, count);
				cout << "\nThe midrange of the given data set is: " << midrangeVal << endl << endl;
			}
			catch (const runtime_error& e) {
				cerr << e.what() << endl;
			}

			break;

		case 'N': // quartiles


			try {
				cout << endl;
				findQuartiles(arrayInts, count);
				cout << endl;
			}
			catch (const std::runtime_error& e) {
				std::cerr << e.what() << std::endl;
			}

			break;

		case 'O': // interquartile range


			try {
				double iqr = findInterquartileRange(arrayInts, count);
				cout << "\nThe interquartile range (IQR) of the given data set is: " << iqr << endl << endl;
			}
			catch (const std::runtime_error& e) {
				cerr << e.what() << endl;
			}

			break;

		case 'P': // outliers


			try {
				findOutliers(arrayInts, count);

			}
			catch (const std::runtime_error& e) {
				cerr << e.what() << endl;
			}

			break;

		case 'Q': // sum of squares


			try {
				double sumOfSquaresVal = findSumOfSquares(arrayInts, count);
				cout << "\nThe sum of squares for the given data set is: " << sumOfSquaresVal << endl << endl;
			}
			catch (const std::runtime_error& e) {
				cerr << e.what() << endl;
			}

			break;

		case 'R': // mean absolute deviation


			try {
				double mad = findMeanAbsoluteDeviation(arrayInts, count);
				std::cout << "\nThe Mean Absolute Deviation (MAD) of the given data set is: " << mad << std::endl << endl;
			}
			catch (const std::runtime_error& e) {
				std::cerr << e.what() << std::endl;
			}

			break;

		case 'S': // root mean square


			try {
				double rms = findRootMeanSquare(arrayInts, count);
				std::cout << "\nThe Root Mean Square (RMS) of the given data set is: " << rms << std::endl << endl;
			}
			catch (const std::runtime_error& e) {
				std::cerr << e.what() << std::endl;
			}

			break;

		case 'T': // standard error of the mean


			try {
				double stdDev = calculateStandardDeviation(arrayInts, count);
				double standardError = findStandardError(arrayInts, count, stdDev);
				std::cout << "\nThe Standard Error of the Mean for the given data set is: " << standardError << std::endl << endl;
			}
			catch (const std::runtime_error& e) {
				std::cerr << e.what() << std::endl;
			}

			break;

		case 'U': // coefficient of variation


			try {
				double mean = findMean(arrayInts, count);
				double stdDev = calculateStandardDeviation(arrayInts, count);
				double coefficientOfVariation = findCoefficientOfVariation(arrayInts, count, stdDev, mean);
				std::cout << "\nThe Coefficient of Variation for the given data set is: " << coefficientOfVariation << std::endl << endl;
			}
			catch (const std::runtime_error& e) {
				std::cerr << e.what() << std::endl;
			}

			break;

		case 'V': // relative standard deviation


			try {
				double mean = findMean(arrayInts, count);
				double stdDev = calculateStandardDeviation(arrayInts, count);
				double relativeStandardDeviation = findRelativeStandardDeviation(arrayInts, count, stdDev, mean);
				std::cout << "\nThe Relative Standard Deviation for the given data set is: " << relativeStandardDeviation << "%" << std::endl << endl;
			}
			catch (const std::runtime_error& e) {
				std::cerr << e.what() << std::endl;
			}

			break;

		case 'W': // display all results and write to an output text file
		{
			system("cls");
			string outputFile; // Variable to store the output file name
			cout << "Enter output file name: "; // Prompt user for output file name
			cin >> outputFile; // Read the file name from user

			ofstream outFile(outputFile); // Open the output file with the given name
			if (!outFile) {
				cerr << "Error opening output file." << std::endl;
				break;
			}
			try {
				// writing to file (and this will overwrite the file if it already exists)

				// Temporarily replace cout's buffer with the stringstream's buffer

				displayArray(arrayInts, count);

				stringstream ss;
				streambuf* coutbuf = cout.rdbuf();
				cout.rdbuf(ss.rdbuf());

				displayArray(arrayInts, count); // A

				// Restore cout's original buffer
				cout.rdbuf(coutbuf);

				// Write the captured output to the file
				outFile << ss.str();
				cout << "\n" << endl;

				int minVal = findMinimum(arrayInts, count); // B
				outFile << "Minimum Value: " << minVal << endl;
				cout << "Minimum Value: " << minVal << "" << endl;
				cout << "\n" << endl;

				int maxVal = findMaximum(arrayInts, count); // C
				outFile << "Maximum Value: " << maxVal << endl;
				cout << "Maximum Value: " << maxVal << endl;
				cout << "\n" << endl;

				int range = findRange(arrayInts, count); // D
				outFile << "Range: " << range << endl;
				cout << "Range: " << range << endl;
				cout << "\n" << endl;

				outFile << "Size: " << count << endl; // E 
				cout << "Size: " << count << endl;
				cout << "\n" << endl;

				int sum = findSum(arrayInts, count); // F 
				outFile << "Sum: " << sum << endl;
				cout << "Sum: " << sum << endl;
				cout << "\n" << endl;

				double mean = findMean(arrayInts, count); // G 
				outFile << "Mean: " << mean << endl;
				cout << "Mean: " << mean << endl;
				cout << "\n" << endl;

				double median = findMedian(arrayInts, count); // H
				outFile << "Median: " << median << endl;
				cout << "Median: " << median << endl;
				cout << "\n" << endl;

				findMode(arrayInts, count);

				// Clear stringstream
				ss.str(string());

				// Capture output of findMode
				cout.rdbuf(ss.rdbuf());
				findMode(arrayInts, count); // J
				cout.rdbuf(coutbuf);
				outFile << "Mode: " << ss.str() << endl;
				cout << "\n" << endl;

				double stdDev = calculateStandardDeviation(arrayInts, count); // K
				outFile << "Standard Deviation: " << stdDev << endl;
				cout << "Standard Deviation: " << stdDev << endl;
				cout << "\n" << endl;

				double variance = findVariance(arrayInts, count); // L
				outFile << "Variance: " << variance << endl;
				cout << "Variance: " << variance << endl;
				cout << "\n" << endl;

				double midrangeVal = findMidrange(arrayInts, count); // M
				outFile << "Midrange: " << midrangeVal << endl;
				cout << "Midrange: " << midrangeVal << endl;
				cout << "\n" << endl;

				findQuartiles(arrayInts, count);

				// Clear stringstream
				ss.str(string());

				// Capture output of findQuartiles
				cout.rdbuf(ss.rdbuf());
				findQuartiles(arrayInts, count); // N
				cout.rdbuf(coutbuf);
				outFile << "Quartiles: " << ss.str() << endl;
				cout << "\n" << endl;

				double iqr = findInterquartileRange(arrayInts, count); // O
				outFile << "Interquartile Range (IQR): " << iqr << endl;
				cout << "Interquartile Range (IQR): " << iqr << endl;
				cout << "\n" << endl;

				findOutliers(arrayInts, count);

				// Clear stringstream
				ss.str(string());

				// Capture output of findOutliers
				cout.rdbuf(ss.rdbuf());
				findOutliers(arrayInts, count); // P
				cout.rdbuf(coutbuf);
				outFile << "Outliers: " << ss.str() << endl;
				cout << "\n" << endl;

				double sumOfSquaresVal = findSumOfSquares(arrayInts, count); // Q
				outFile << "Sum of Squares: " << sumOfSquaresVal << endl;
				cout << "Sum of Squares: " << sumOfSquaresVal << endl;
				cout << "\n" << endl;

				double mad = findMeanAbsoluteDeviation(arrayInts, count); // R
				outFile << "Mean Absolute Deviation (MAD): " << mad << endl;
				cout << "Mean Absolute Deviation (MAD): " << mad << endl;
				cout << "\n" << endl;

				double rms = findRootMeanSquare(arrayInts, count); // S
				outFile << "Root Mean Square (RMS): " << rms << endl;
				cout << "Root Mean Square (RMS): " << rms << endl;
				cout << "\n" << endl;

				double standardError = findStandardError(arrayInts, count, stdDev); // T
				outFile << "Standard Error of the Mean: " << standardError << endl;
				cout << "Standard Error of the Mean: " << standardError << endl;
				cout << "\n" << endl;

				double coefficientOfVariation = findCoefficientOfVariation(arrayInts, count, stdDev, mean); // U
				outFile << "Coefficient of Variation: " << coefficientOfVariation << endl;
				cout << "Coefficient of Variation: " << coefficientOfVariation << endl;
				cout << "\n" << endl;

				double relativeStandardDeviation = findRelativeStandardDeviation(arrayInts, count, stdDev, mean); // V
				outFile << "Relative Standard Deviation: " << relativeStandardDeviation << "%" << endl;
				cout << "Relative Standard Deviation: " << relativeStandardDeviation << "%" << endl;
				cout << "\n" << endl;

				findFrequencies(arrayInts, count);

				// clear 
				ss.str(string());

				// Capture output of findFrequencies
				cout.rdbuf(ss.rdbuf());
				findFrequencies(arrayInts, count); // I
				cout.rdbuf(coutbuf);
				outFile << "Frequencies: " << ss.str() << endl;
				cout << "\n" << endl;

			}
			catch (const runtime_error& e) {
				cerr << e.what() << endl;
				outFile << "Error: " << e.what() << endl;
			}

			outFile.close();
			system("pause");
			system("cls");
		}
		break;

		case 'X': // exit

			cout << "Exiting to previous menu." << endl;
			system("pause");
			system("cls");
			menu();
			chooseOption();
			break;

		default: // invalid option

			cout << "Invalid option. Please try again." << endl;
			system("pause");
			system("cls");
			break;

		}

		//cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	} while (toupper(option) != 'X');
	delete[] arrayInts;
	return 0;
}
// PRECONDITION: 'array' should be a dynamically allocated array of integers, 'size' should represent the number of elements in 'array'.
// POSTCONDITION: 'array' will be displayed on the standard output.
void displayArray(int* array, int size) {
	cout << "\nData set with " << size << " data: \n";
	cout << "{ ";
	for (int i = 0; i < size - 1; ++i)
	{
		cout << array[i] << ", ";
	}
	cout << array[size - 1] << " }\n\n";
}

