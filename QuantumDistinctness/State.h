/*
 * State.h
 *
 *  Created on: 15/02/2014
 *      Author: Alexandre & Matheus
 */

#ifndef STATE_H_
#define STATE_H_

#include "Library.h"

class State {

public:
    State();
    virtual ~State();

    void insert_in_S(string elements);
    void insert_in_S(int element);
    void insert_in_S(vector<int> elements);
    void insert_in_y(string elements);
    void insert_in_y(int element);
    void insert_in_y(vector<int> elements);

    void display_file_without_x(ofstream& quantumFile);
    void display_file_with_x(ofstream& quantumFile, vector<int> elements);

    void search_distinctness_change_signal(int kDistinctness, vector<int> elements);
    void transformation_mapping(float factor);

    void change_amplitude(int first, double second);

    double measure(double cumulativeProbability, int random, unsigned int root, ofstream& quantumFile);

    bool amplitudes_equals_of_y();
    double getAmplitude();

    set<int> getS();
    map<int, double> getY();

private:
    set<int> S;
    map<int, double> y;

};

#endif
