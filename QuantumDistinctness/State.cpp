/*
 * State.cpp
 *
 * Created on: 15/02/2014
 *     Author: Alexandre & Matheus
 */

#include "Library.h"

/*
 * Constructor
 */
State::State() {

}

/*
 * Destructor
 */
State::~State() {

}

/*
 * O(r * log(r)) - arvore vermelha e preta
 */
void State::insert_in_S(string elements) {
    //int length = elements.size();
    //int element;
    //for(int position = 0; position < length; position++) {
    //    element = (int) (elements[position] - '0');
    //    iteratorS = S.insert(iteratorS, element);
    //}

    for(int position = 0; position < elements.size(); position++)
        S.insert((int) (elements[position] - '0'));
}

/*
 * O(log (r))
 */
void State::insert_in_S(int element) {
    //iteratorS = S.insert(iteratorS, element);
	S.insert(element);
}

/*
 * O(r * log(r))
 */
void State::insert_in_S(vector<int> elements) {
    //vector<int>::iterator current = elements.begin(),
    //                          end = elements.end();
    //int element;
    //for(; current != end; current++) {
    //    element = (*current);
    //    iteratorS = S.insert(iteratorS, element);
    //}

	vector<int>::iterator current = elements.begin(),
                              end = elements.end();
    for(; current != end; current++) {
        S.insert(*current);
    }
}

/*
 *
 */
void State::insert_in_y(string elements) {
    /*int length = elements.size();
    int element;
    for(int position = 0; position < length; position++) {
        element = (int) (elements[position] - '0');
        iteratorY = y.insert(iteratorY, pair<int, double>(element, 1.0));
    }*/

    for(int position = 0; position < elements.size(); position++) {
        y.insert(pair<int, double>((int) (elements[position] - '0'), 1.0));
    }
}

/*
 *
 */
void State::insert_in_y(int element) {
    //iteratorY = y.insert(iteratorY, pair<int, double>(element, 1.0));
    y.insert(pair<int, double>(element, 1.0));
}

/*
 *
 */
void State::insert_in_y(vector<int> elements) {
    /*vector<int>::iterator current = elements.begin(),
                              end = elements.end();
    int element;
    for(; current != end; current++) {
        element = (*current);
        iteratorY = y.insert(iteratorY, pair<int, double>(element, 1.0));
    }*/
	vector<int>::iterator current = elements.begin(),
                              end = elements.end();
    for(; current != end; current++) {
        y.insert(pair<int, double>(*current, 1.0));
    }
}

/*
 *
 */
void State::display_file_without_x(ofstream& quantumFile) {
    set<int>::iterator currentS = S.begin(),
                           endS = S.end();
    endS--;
    stringstream stateS;
    stateS << "|{";
    for (; currentS != endS; currentS++)
        stateS << (*currentS) << ",";
    stateS << (*endS) << "}>";

    map<int, double>::iterator currentY = y.begin(),
                                   endY = y.end();
    for(; currentY != endY; currentY++) {
        quantumFile << "\t";

        if((*currentY).second >= 0)
            quantumFile << "+";

        quantumFile << (*currentY).second << " ";

        quantumFile << stateS.str();

        quantumFile << "|" << (*currentY).first << ">\n";
    }
}

/*
 *
 */
void State::display_file_with_x(ofstream& quantumFile, vector<int> elements) {
    set<int>::iterator currentS = S.begin(),
                           endS = S.end();
    endS--;
    stringstream stateS, stateX;
    stateS << "|{";
    for(; currentS != endS; currentS++) {
        stateS << (*currentS) << ",";
        stateX << "|" << elements[(*currentS) - 1] << ">" ;
    }
    stateS << (*endS) << "}>";
    stateX << "|" << elements[(*endS) - 1] << ">" ;

    map<int, double>::iterator currentY = y.begin(),
                                   endY = y.end();
    for(; currentY != endY; currentY++) {
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
 *
 */
void State::search_distinctness_change_signal(int kDistinctness, vector<int> elements) {
    set<int>::iterator currentS = S.begin(),
                           endS = S.end(),
                      auxiliarS;
    int count = 0;
    map<int, double>::iterator currentY, endY;
    for(; currentS != endS; currentS++) {
        auxiliarS = ++currentS;
        currentS--;
        for(; auxiliarS != endS; auxiliarS++) {
            if(elements[(*currentS) - 1] == elements[(*auxiliarS) - 1]) {
                count++;
            }
        }

        if(count == (kDistinctness - 1)) {
            currentY = y.begin();
            endY = y.end();
            for(; currentY != endY; currentY++) {
                (*currentY).second *= -1;
            }
            return;
        }
        count = 0;
    }
}

/*
 *
 */
void State::transformation_mapping(float factor) {
    map<int, double>::iterator current = y.begin(),
                                   end = y.end(),
                              auxiliar;
    map<int, double> yAuxiliar;
    for(; current != end; current++) {
        auxiliar = y.begin();
        for(; auxiliar != end; auxiliar++) {
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
 *
 */
double State::measure(double cumulativeProbability, int random, unsigned int root, ofstream& quantumFile) {
    map<int, double>::iterator current = y.begin(),
                                   end = y.end();
    double probability = 0.0f;
    bool achou = false;
    for(; current != end; current++) {
        probability = (((*current).second * (*current).second) / root) * 100;
        //cout << " " <<  probability;
        if(((double)random >= cumulativeProbability) && ((double)random < (cumulativeProbability + probability))) {
            cumulativeProbability += probability;
            //qreturn cumulativeProbability *= -1;
            //return -1.0f;
            achou = true;
        }else{
            cumulativeProbability += probability;
        }
    }
    if(achou)
        return -cumulativeProbability;
    return cumulativeProbability;
}

/*
 *
 */
void State::change_amplitude(int first, double second) {
    y[first] = second;
}

/*
 *
 */
map<int, double> State::getY() {
    return y;
}

/*
 *
 */
set<int> State::getS() {
    return S;
}

/*
 *
 */
bool State::amplitudes_equals_of_y() {
    map<int, double>::iterator current = y.begin(),
                                   end = y.end(),
                                 first = y.begin();
    current++;
    for(; current != end; current++) {
        if((*first).second != (*current).second)
            return false;
    }
    return true;
}

/*
 *
 */
double State::getAmplitude() {
    map<int, double>::iterator first = y.begin();
    return (*first).second;
}
