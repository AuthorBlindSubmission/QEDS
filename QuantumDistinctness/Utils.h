/*
 * Simulador de Distinção de Elementos
 *
 * File: Utils.h
 *
 * Created on: 26/06/2014
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

	unsigned int combinatorial(int n, int s);
	int calculate_position(vector<int> S, int initialPositionS, int N, int r, int previousS);
	set<int> set_intersection(set<int> set1, set<int> set2);

private:
	unsigned int *binomialCoefficients;

};

#endif