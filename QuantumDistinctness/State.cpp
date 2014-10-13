/*
 * Simulador de Distinção de Elementos
 *
 * File: State.cpp
 *
 * Created on: 15/02/2014
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
 * Este arquivo contém métodos da classe State
 * usadas no Simulador de Distinção de Elementos.
 */

#include "Library.h"

/*
 * Construtor da Classe State
 */
State::State() {

}

/*
 * Destrutor da Classe State
 */
State::~State() {

}

/*
 * Insert In S
 *
 * Inserção de valores em S
 *
 * Parâmetros:
 * elements = elementos a serem inseridos no S
 * length = tamanhos dos elementos a serem 
 * inseridos no S
 *
 * Computational Complexity (Big-O Notation):
 * Árvore Rubro-Negra
 * O(r*log(r))
 */
void State::insert_in_S(int *elements, int length){
	for(int position = 0; position < length; position++) //O(r)
		S.insert(elements[position]); //O(log(r))
}

/*
 * Insert In Y
 *
 * Inserção de valores em Y
 *
 * Parâmetros:
 * elements = elementos a serem inseridos no Y
 * length = tamanhos dos elementos a serem 
 * inseridos no Y
 *
 * Computational Complexity (Big-O Notation):
 * Árvore Rubro-Negra
 * O((n-r)*log(n-r))
 */
void State::insert_in_y(int *elements, int length){
	for(int position = 0; position < length; position++) //O(n-r)
		y.insert(pair<int, double>(elements[position], 1.0)); //O(log(n-r))
}

/*
 * Display in File Without X
 *
 * Mostra no arquivo o estado sem o estado X
 * |S>|y>
 *
 * Parâmetros:
 * quantumFile = ponteiro do arquivo para salvar as informações
 *
 * Computational Complexity (Big-O Notation):
 * O(n-r)
 */
void State::display_in_file_without_x(ofstream& quantumFile) { //O(n-r)
    set<int>::iterator currentS = S.begin(),
                           endS = S.end();
    endS--;
    stringstream stateS;
    stateS << "|{";
    for (; currentS != endS; currentS++) //O(r)
        stateS << (*currentS) << ",";
    stateS << (*endS) << "}>";

    map<int, double>::iterator currentY = y.begin(),
                                   endY = y.end();
    for(; currentY != endY; currentY++) { //O(n-r) -> n-r acaba sendo maior que r
        quantumFile << "\t";

        if((*currentY).second >= 0)
            quantumFile << "+";

        quantumFile << (*currentY).second << " ";

        quantumFile << stateS.str();

        quantumFile << "|" << (*currentY).first << ">\n";
    }
}

/*
 * Display in File With X
 *
 * Mostra no arquivo o estado com o estado X
 * |S>|x>|y>
 *
 * Parâmetros:
 * quantumFile = ponteiro do arquivo para salvar as informações
 *
 * Computational Complexity (Big-O Notation):
 * O(n-r)
 */
void State::display_in_file_with_x(ofstream& quantumFile, int *elements) { //O(n-r)
    set<int>::iterator currentS = S.begin(),
                           endS = S.end();
    endS--;
    stringstream stateS, stateX;
    stateS << "|{";
    for(; currentS != endS; currentS++) { //O(r)
        stateS << (*currentS) << ",";
        stateX << "|" << elements[(*currentS) - 1] << ">" ;
    }
    stateS << (*endS) << "}>";
    stateX << "|" << elements[(*endS) - 1] << ">" ;

    map<int, double>::iterator currentY = y.begin(),
                                   endY = y.end();
    for(; currentY != endY; currentY++) { //O(n-r) -> n-r acaba sendo maior que r
        quantumFile << "\t";

        if((*currentY).second >= 0)
            quantumFile << "+";

        quantumFile << (*currentY).second << " ";

        quantumFile << stateS.str();

        quantumFile << stateX.str();

        quantumFile << "|" << (*currentY).first << ">\n";
    }
}

/*
 * Search Equals Change Signal
 *
 * Procurar por k valores de X iguais e 
 * inverte a fase
 *
 * Parâmetros:
 * elements = lista com os elementos
 * kDistinctness = quantidade de números distintos
 *
 * Computational Complexity (Big-O Notation):
 * O(r^2) ou O(rn - r^2)
 */
void State::search_equals_change_signal(int *elements, int kDistinctness) { //O(r^2) ou O(rn - r^2)
    set<int>::iterator currentS = S.begin(),
                           endS = S.end(),
                      auxiliarS;
    int count = 0;
    map<int, double>::iterator currentY, endY;
    for(; currentS != endS; currentS++) {//O(r) //pode fazer melhor -kDistinctness
		//não adianta verificar os dois ultimos, se K = 3
        auxiliarS = ++currentS;
        currentS--;
        for(; auxiliarS != endS; auxiliarS++) { //O(r)
            if(elements[(*currentS) - 1] == elements[(*auxiliarS) - 1])
                count++;
        }

        if(count == (kDistinctness - 1)) {
            currentY = y.begin();
            endY = y.end();
            for(; currentY != endY; currentY++) //O(n-r)
                (*currentY).second *= -1;
            return;
        }
        count = 0;
    }
}

/*
 * Transformation Mapping
 *
 * Muda a amplitude do estado de acordo 
 * com a caminhada quântica
 *
 * Parâmetros:
 * factor = novo fator para a troca da amplitude
 *
 * Computational Complexity (Big-O Notation):
 * O(n^2)
 */
void State::transformation_mapping(float factor) { //O(n^2 - nr - nr - r^2) -> O(n^2)
    map<int, double>::iterator current = y.begin(),
                                   end = y.end(),
                              auxiliar;
    map<int, double> yAuxiliar;
    for(; current != end; current++) { //O(n-r)
        auxiliar = y.begin();
        for(; auxiliar != end; auxiliar++) { //O(n-r)
            if((*current).first == (*auxiliar).first){
                yAuxiliar[(*auxiliar).first] += (-1 + factor) * ((*current).second);
            }else{
                yAuxiliar[(*auxiliar).first] += (factor) * ((*current).second);
            }
        }
    }
    y.clear();
    y = yAuxiliar;
    yAuxiliar.clear();
}

/*
 * Measurement
 *
 * Medição do resultado
 *
 * Parâmetros:
 * cumulativeProbability = intervalo inferior da probabilidade
 * random = probabilidade do estado ser o correto
 * root = valor da amplitude "geral"
 * found = usado para ver se o estado é marcado como correto
 *
 * Computational Complexity (Big-O Notation):
 * O(n-r)
 */
double State::measurement(double cumulativeProbability, double random, unsigned int root, int &found) { //O(n-r)
    map<int, double>::iterator current = y.begin(),
                                   end = y.end();
    double probability = 0.0f;
	double maximumCumulativeProbability = 0.0f;
    for(; current != end; current++) { //O(n-r)
        probability = (((*current).second * (*current).second) / root) * 100;

		maximumCumulativeProbability = cumulativeProbability + probability;
        
		//cout << "Probability: " << cumulativeProbability << " - " << maximumCumulativeProbability << endl;

        if((random >= cumulativeProbability) && (random < maximumCumulativeProbability)) {
			found = 1;
            //return;
        }

		cumulativeProbability = maximumCumulativeProbability;

    }
    return cumulativeProbability;
}

/*
 * Amplitudes Equals of Y
 *
 * Verifica se os valores de y são iguais
 * para um mesmo |S>
 *
 * Computational Complexity (Big-O Notation):
 * O(n-r)
 */
bool State::amplitudes_equals_of_y() { //O(n-r)
    map<int, double>::iterator current = y.begin(),
                                   end = y.end(),
                                 first = y.begin();
    current++;
    for(; current != end; current++) { //O(n-r)
        if((*first).second != (*current).second)
            return false;
    }
    return true;
}

/*
 * Get Amplitude
 *
 * Retorna o valor da amplitude do primeiro
 * y de um dado |S>
 *
 * Computational Complexity (Big-O Notation):
 * O(1)
 */
double State::getAmplitude() { //O(1)
    map<int, double>::iterator first = y.begin();
    return (*first).second;
}

/*
 * Change Amplitude
 *
 * Retorna o valor da amplitude do primeiro
 * y de um dado |S>
 *
 * Parâmetros:
 * first = valor do y que terá sua amplitude alterada
 * amplitude = nova amplitude
 *
 * Computational Complexity (Big-O Notation):
 * O(log(n-r))
 */
void State::change_amplitude(int first, double amplitude) { //O(log(n-r))
    y[first] = amplitude;
}

/*
 * Get Y
 *
 * Retorna os y de um dados S
 *
 * Computational Complexity (Big-O Notation):
 * O(1)
 */
map<int, double> State::getY() { //O(1)
    return y;
}

/*
 * Get S
 *
 * Retorna o S
 *
 * Computational Complexity (Big-O Notation):
 * O(1)
 */
set<int> State::getS() { //O(1)
    return S;
}