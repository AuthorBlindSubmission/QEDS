/*
 * QuantumDistinctness.h
 *
 *  Created on: 13/02/2014
 *      Author: Alexandre & Matheus
 */

#ifndef QUANTUMDISTINCTNESS_H_
#define QUANTUMDISTINCTNESS_H_

#include "Library.h"

class QuantumDistinctness {

public:
	QuantumDistinctness();
	virtual ~QuantumDistinctness();

	void init(vector<int> _elements);

private:
	vector<int> elements;
	int N;
	int r;
	int k;
	int M;
	unsigned int root;
	vector<State> statesDimensionH;
	vector<State> statesDimensionHLine;

	int MINIMUM;
	int MAXIMUM;
	clock_t time;

	ofstream quantumFile;
	char quantumFileName[50];

	Utils *utils;

	void initialStep();
	void finalStep();

	void firstStep();
	void secondStep();
	void thirdStep();
	void fourthStep();

	void thirdStepA();
	void thirdStepB();

	void firstStepQuantumWalk();
	void secondStepQuantumWalk();
	void thirdStepQuantumWalk();
	void fourthStepQuantumWalk();
	void fifthStepQuantumWalk();
	void sixthStepQuantumWalk();

	void measure();
	void measure2();

	bool verifyCollision(set<int> S);

	void display_file_without_x_H();
	void display_file_with_x_H();
	void display_file_with_x_H_Line();

	void sub_sets_H();
	void sub_sets_H_Line();
	void combination_H(string before, string after, int quantity);
	void combination_H_Line(string before, string after, int quantity);

};


#endif /* QUANTUMDISTINCTNESS_H_ */
