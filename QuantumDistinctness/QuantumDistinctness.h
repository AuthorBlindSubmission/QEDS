/*
 * Quantum Element Distinctness Simulator
 *
 * File: QuantumDistinctness.h
 *
 * Created on: 2014
 *    Authors: Alexandre Santiago de Abreu
 *             Matheus Manzoli Ferreira
 *
 *      Email: santiago@cos.ufrj.br
 *             matheusmanzoli@gmail.com
 *
 * B.Sc. dissertation for the 
 * Universidade Federal Fluminense.
 * Institute of Computing.
 * Niter�i, Rio de Janeiro, Brazil.
 *
 * This file contains the methods of the class 
 * QuantumDistinctness used by QEDS.
 * In this simulator, we have fixed k = 2, i.e.,
 * we are finding a 2-collision, or 2-distinctness.
 *
 * All descriptions of classes are in cpp file.
 */

#ifndef QUANTUMDISTINCTNESS_H_
#define QUANTUMDISTINCTNESS_H_

#include "Library.h"

class QuantumDistinctness {

public:
	QuantumDistinctness();
	virtual ~QuantumDistinctness();

private:
	int *elements;
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

	void init();
	void end();

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

	void deterministic_measurement();
	void probabilistic_measurement();

	bool verifyCollision(set<int> S);

	void display_in_file_without_x_H();
	void display_in_file_with_x_H();
	void display_in_file_with_x_H_Line();
	void display_in_file_with_x_H_Line_with_0();

	void sub_sets();

	void menu();
	void randomList();
	void userList();

};

#endif
