/*
 * Quantum Element Distinctness Simulator
 *
 * File: Utils.h
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
 * Niterói, Rio de Janeiro, Brazil.
 *
 * This file contains methods useful used in QEDS.
 * All description of methods are in cpp file.
 */

#ifndef UTILS_H_
#define UTILS_H_

#include "Library.h"

class Utils {

public:
	Utils();
	virtual ~Utils();

	unsigned int combinatorial(int n, int r);
	int calculate_position(vector<int> S, int initialPositionS, int n, int r, int previousValueS);
	set<int> set_intersection(set<int> set1, set<int> set2);
	int max_value(int value1, int value2);

private:
	unsigned int *binomialCoefficients;

};

#endif
