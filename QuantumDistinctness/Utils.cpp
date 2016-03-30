/*
 * Quantum Element Distinctness Simulator
 *
 * File: Utils.cpp
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
 */

#include "Library.h"

/*
 * Builder
 */
Utils::Utils() {
    binomialCoefficients = NULL;
}

/*
 * Destructor
 */
Utils::~Utils() {
    if(binomialCoefficients != NULL)
        free(binomialCoefficients);
}

/*
 * Combinatorial
 * http://www.ebah.com.br/content/ABAAAfTVEAG/tabela-coeficientes-binomiais
 * http://www.brpreiss.com/books/opus5/html/img1869.gif
 *
 * This method calculates the binomial coeficient used in combination.
 *
 * Parameters:
 * n = set's size.
 * r = subset's size.
 *
 * Computational Complexity (Big-O Notation):
 * O(n^2)
 */
unsigned int Utils::combinatorial(int n, int r) { //O(n^2)
    if(n == 0)
        return 1;

    if(binomialCoefficients != NULL && binomialCoefficients[1] == n)
        return binomialCoefficients[r];
		
    if(binomialCoefficients != NULL)
        free(binomialCoefficients);
	
    binomialCoefficients = (unsigned int *) malloc(sizeof(unsigned int) * (n+1));
    binomialCoefficients[0] = 1;
    for(int i = 1; i <= n; i++) { //O(n)
        binomialCoefficients[i] = 1;
        for(int j = i - 1; j > 0; j--) { //O(n)
            binomialCoefficients[j] += binomialCoefficients[j - 1];
        }
    }

    return binomialCoefficients[r];
}

/*
 * Calculate Position
 *
 * Calculates the new position for the change in Hilbert Space H.
 * Calculates the both, H->H' and H'->H.
 *
 * Parameters:
 * S = 
 * initialPositionS = Initial position of vector S.
 * N = Total size of values.
 * r = subset's size.
 * previousValueS = Previous value of initial position of vector S.
 *
 * Computational Complexity (Big-O Notation):
 * O()
 * O()
 */
int Utils::calculate_position(vector<int> S, int initialPositionS, int n, int r, int previousValueS) {
    int t = 0;
    for(int i = previousValueS + 1; i <= S[initialPositionS] - 1; i++)
        t = t + combinatorial(n-i, r-1);
    if(r == 2)
        return S[initialPositionS+1] - S[initialPositionS] - 1 + t;
    else{
        int t1 = calculate_position(S, initialPositionS + 1, n, r - 1, S[initialPositionS]);
        return t + t1;
    }
}

/*
 * Set Intersection
 *
 * Calculate the intersection of two sets.
 *
 * Parameters:
 * set1 = set 1.
 * set2 = set 2.
 *
 * Computational Complexity (Big-O Notation):
 * s1 = size of set1 ==>  s1 <= r
 * s2 = size of set2 ==>  s2 == r
 * O Set uses the red-black tree.
 * O(r*log(r))
 */
set<int> Utils::set_intersection(set<int> set1, set<int> set2) { //O(r*log(r))
    set<int> result;
    set<int>::iterator current = set1.begin(),
                           end = set1.end();

    for(; current != end; current++) { //O(r)
        if(set2.find(*current) != set2.end()) 
            result.insert((*current)); //O(log(r))
    }

    return result;
}

/*
 * Max Value
 *
 * Calculate the maximum value between two numbers
 *
 * Parameters:
 * value1 = value 1.
 * value2 = value 2.
 *
 * Computational Complexity (Big-O Notation):
 * O(1)
 */
int Utils::max_value(int value1, int value2){ //O(1)
	return (value1 > value2) ? value1 : value2;
}
