/*
 * Simulador de Distinção de Elementos
 *
 * File: QuantumDistinctness.h
 *
 * Created on: 13/02/2014
 *    Authors: Alexandre Santiago de Abreu
 *             Matheus Manzoli Ferreira
 *
 *      Email: alexandresantiago@id.uff.br
 *             matheusmanzoli@gmail.com
 *
 * Trabalho de Monografia para a 
 * Universidade Federal Fluminense.
 * Instituto de Computação.
 * Niterói, Rio de Janeiro, Brasil.
 *
 * Este arquivo contém as chamadas dos métodos
 * da Classe QuantumDistinctness usadas no 
 * Simulador de Distinção de Elementos.
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

	void sub_sets();

	void menu();
	void randomList();
	void userList();

};

#endif
