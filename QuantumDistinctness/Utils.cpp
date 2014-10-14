/*
 * Element Distinctness Simulator
 *
 * File: Utils.cpp
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
 * Este arquivo contém métodos úteis usadas no
 * Simulador de Distinção de Elementos.
 */

#include "Library.h"

/*
 * Construtor da Classe Utils
 */
Utils::Utils() {
    binomialCoefficients = NULL;
}

/*
 * Destrutor da Classe Utils
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
 * Método que calcula o Coeficiente Binomial, utilizada 
 * na Combinação.
 *
 * Parameters:
 * n = tamanho do conjunto.
 * r = tamanho do subconjunto.
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
 * Calcula a nova posição para a mudança do estado de Hilbert H.
 * Calcula tanto a mudança de H para H', quanto o inverso.
 *
 * Parameters:
 * S = 
 * initialPositionS = posição inicial do vetor S.
 * N = tamanho total dos valores.
 * r = tamanho do subconjunto.
 * previousValueS = valor anterior a posição inicial do vetor S.
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
 * Calcula a interseção de dois conjuntos.
 *
 * Parameters:
 * set1 = conjunto 1.
 * set2 = conjunto 2.
 *
 * Computational Complexity (Big-O Notation):
 * s1 = tamanho de set1 ==>  s1 <= r
 * s2 = tamanho de set2 ==>  s2 == r
 * O Set utiliza a árvore rubro-negra
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