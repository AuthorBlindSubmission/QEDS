/*
 * Quantum Element Distinctness Simulator
 *
 * File: State.cpp
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
 * This file contains the methods of State class.
 */

#include "Library.h"

/*
 * Builder
 */
State::State() {

}

/*
 * Destructor
 */
State::~State() {

}

/*
 * Insert In S
 *
 *
 * Parameters:
 * elements = elements to be added in S.
 * length = Elements' size.
 *
 * Computational Complexity (Big-O Notation):
 * O(r*log(r))
 */
void State::insert_in_S(int *elements, int length) { //O(r*log(r))
	for(int position = 0; position < length; position++) //O(r)
		S.insert(elements[position]); //O(log(r))
}

/*
 * Insert In Y
 *
 *
 * Parameters:
 * elements = elements to be added in Y.
 * length = elements' size.
 *
 * Computational Complexity (Big-O Notation):
 * O((n-r)*log(n-r))
 */
void State::insert_in_y(int *elements, int length) { //O((n-r)*log(n-r))
	for(int position = 0; position < length; position++) //O(n-r)
		y.insert(pair<int, double>(elements[position], 1.0)); //O(log(n-r))
}

/*
 * Display in File Without X
 *
 * Show in output file the state without X
 * |S>|y>
 *
 * Parameters:
 * quantumFile = files pointer to save informations.
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
    for(; currentS != endS; currentS++) //O(r)
        stateS << (*currentS) << ",";
    stateS << (*endS) << "}>";

    map<int, double>::iterator currentY = y.begin(),
                                   endY = y.end();
    for(; currentY != endY; currentY++) { //O(n-r) -> (n-r) >= r
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
 * Shows in output file the state with X
 * |S>|x>|y>
 *
 * Parameters:
 * quantumFile = files pointer to save informations. 
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
    for(; currentY != endY; currentY++) { //O(n-r) -> (n-r) >= r
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
 * Display in File With X With 0
 *
 * S>|x>|0>
 *
 * Parameters:
 * quantumFile = files pointer to save informations.
 *
 * Computational Complexity (Big-O Notation):
 * O(nr)
 */
void State::display_in_file_with_x_with_0(ofstream& quantumFile, int *elements) { //O(nr)
    set<int>::iterator currentS = S.begin(),
                           endS = S.end();
    endS--;
    stringstream stateS, stateX;
    stateS << "|{";
    for(; currentS != endS; currentS++) //O(r)
        stateS << (*currentS) << ",";
    stateS << (*endS) << "}>";

    map<int, double>::iterator currentY = y.begin(),
                                   endY = y.end();
    for(; currentY != endY; currentY++) { //O(n-r) -> (n-r) >= r
		
		currentS = S.begin();
        endS = S.end();
		for(; currentS != endS; currentS++) { //O(r)
			if((*currentS) == (*currentY).first)
				stateX << "|0>" ;
			else
				stateX << "|" << elements[(*currentS) - 1] << ">" ;
		}
		
		quantumFile << "\t";

        if((*currentY).second >= 0)
            quantumFile << "+";

        quantumFile << (*currentY).second << " ";

        quantumFile << stateS.str();

        quantumFile << stateX.str();

        quantumFile << "|" << (*currentY).first << ">\n";

		stateX.str(std::string()); //O(r)
    }
}

/*
 * Search Equals Change Signal
 *
 * Search for k equal values of X and 
 * change the phase.
 *
 * Parameters:
 * elements = list of elements
 * kDistinctness = number of distinct numbers
 *
 * Computational Complexity (Big-O Notation):
 * O(rn)
 */
void State::search_equals_change_signal(int *elements, int kDistinctness) { //O(rn)
    set<int>::iterator currentS = S.begin(),
                           endS = S.end(),
                      auxiliarS;
    int count = 0;
    map<int, double>::iterator currentY, endY;
    for(; currentS != endS; currentS++) { //O(r)
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
 * Changes the state's amplitude.
 *
 * Parameters:
 * factor = new value to amplitude
 *
 * Computational Complexity (Big-O Notation):
 * O(n^2)
 */
void State::transformation_mapping(float factor) { //O(n^2)
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
 *
 * Parameters:
 * cumulativeProbability = lower range of probability.
 * random = randum value to get the interval for the measure.
 * root = amplitude value.
 * found = used to see if the state is the marked state.
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
 * Verify if the y values are equal to the same |S>
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
 * Returns the first y value of a |S>
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
 * Returns the first y value of a |S>
 *
 * Parameters:
 * first = y value that will have its amplitude value changed.
 * amplitude = new amplitude.
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
 * Returns the y values of a S
 *
 * Computational Complexity (Big-O Notation):
 * O(n-r)
 */
map<int, double> State::getY() { //O(n-r)
    return y;
}

/*
 * Get S
 *
 * Returns S
 *
 * Computational Complexity (Big-O Notation):
 * O(r)
 */
set<int> State::getS() { //O(r)
    return S;
}
