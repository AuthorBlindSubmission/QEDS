/*
 * Element Distinctness Simulator
 *
 * File: Utils.h
 *
 * Created on: 2014
 *    Authors: Alexandre Santiago de Abreu
 *             Matheus Manzoli Ferreira
 *
 *      Email: alexandresantiago@id.uff.br
 *             matheusmanzoli@gmail.com
 *
 * Trabalho de Monografia para a 
 * Universidade Federal Fluminense.
 * Institute of Computing.
 * Niterói, Rio de Janeiro, Brazil.
 *
 * Este arquivo contém as chamadas dos métodos
 * úteis usadas no Simulador de Distinção 
 * de Elementos.
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

private:
	unsigned int *binomialCoefficients;

};

#endif