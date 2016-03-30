/*
 * Quantum Element Distinctness Simulator
 *
 * File: QuantumDistinctness.cpp
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
 * This file contains the methods of the class 
 * QuantumDistinctness used by QEDS.
 * In this simulator, we have fixed k = 2, i.e.,
 * we are finding a 2-collision, or 2-distinctness.
 */

#include "Library.h"

/*
 * Builder of the simulator
 *
 * Initialization of all variables
 *
 * Parameters:
 * elements = List of values.
 * minimum = Minimum list's size.
 * maximum = Maximum list's size.
 * N = List's size.
 * r = N^(2/3).
 * k = Number of elements distinctness in the list. 
 * This value is fixed in 2.
 * root = variable that is used for calculate the amplitude.
 * quantumName = File's name where we save every step of Element
 * Distinctness Algorithm.
 */
QuantumDistinctness::QuantumDistinctness() { //O(2^n)
	system("title Element Distinctness Simulator");

	N = 0;

	r = 0;

	k = 2;

	M = 0;

	root = 0;

	strcpy(quantumFileName, "quantumDistinctness.txt");

	utils = new Utils;

	elements = NULL;

	/* N^(2/3) = r --> r >= k */
	/* Minimum value is 4. If we had 3 elements our graph would be a tree.*/

	MINIMUM = utils->max_value(ceil(pow(k, ((k + 1.0)/k))), 4);

	MAXIMUM = 34; // The maximum supported by the computer used in tests.

	menu();

	init(); //O(2^n)
}

/*
 * Desctructor
 */
QuantumDistinctness::~QuantumDistinctness() {
	if(elements != NULL)
		free(elements);
	
	delete utils;

	cout << "\nPress any key to continue...";
	system("pause > nul");
}

/*
 * Init
 *
 * Init of simulator.
 * Here we calculate some variables and call the steps of the algorithm.
 * 
 */
void QuantumDistinctness::init() { //O(2^n)
	float exponent = (k) / (k + 1.0);
	r = (int) pow(N, exponent);
	
	quantumFile.open(quantumFileName, ios::out);
	quantumFile.setf(ios::fixed, ios::floatfield);
	quantumFile.precision(20);

	time = clock();

	quantumFile << "Elements: [";
	
	for(int i = 0; i < N-1; i++) //O(n)
		quantumFile << elements[i] << ", ";
	quantumFile << elements[N-1] << "]\n";

	quantumFile << "N: " << N << "\n";

	quantumFile << "R: " << r << "\n";

	quantumFile << "K: " << k << "\n";

	//quantumFile << "M: " << M << "\n";

	quantumFile << "\n\n";

	firstStep(); //O(2^n)
	secondStep(); //O(En)
	thirdStep(); //O(P*(n^2))
	fourthStep(); //O(En)

	end();
}

/*
 * End
 *
 * The last part of simulator.
 * We calculate the running time of the simulator.
 * Here we close the file with the information of the simulation.
 */
void QuantumDistinctness::end() {
	time = clock() - time;

	quantumFile.precision(5);
	quantumFile << "\nTime (secs): " << ((float)time)/CLOCKS_PER_SEC;

	quantumFile.close();
}

/*Here we start the quantum steps of algorithm*/

/*
 * First Step
 *
 * First step of simulator.
 * First step of algorithm 2 (see Ambainis' paper for Element Distinctness).
 *
 * Computational Complexity (Big-O Notation):
 * O(2^n)
 */
void QuantumDistinctness::firstStep() { //O(2^n)
	root = (utils->combinatorial(N,r)) * (N - r); //O(n^2)

	sub_sets(); //O(2^n)

	quantumFile << "Step 1 (Algorithm 2: Single-solution algorithm)\n";
	display_in_file_without_x_H(); //O(En)
}

/*
 * Second Step
 *
 * Second step of simulator.
 * Second step of algorithm 2.
 *
 * Computational Complexity (Big-O Notation):
 * O(En)
 */
void QuantumDistinctness::secondStep() { //O(En)
	quantumFile << "Step 2 (Algorithm 2: Single-solution algorithm)\n";
	display_in_file_with_x_H(); //O(En)
}

/*
 * Third Step
 *
 * Third step of simulator.
 * Third step of algorithm 2.
 *
 * Computational Complexity (Big-O Notation):
 * O(P*(n^2))
 */
void QuantumDistinctness::thirdStep() { //O(P*(n^2))
	double base = N / r;
	double exponent = k / 2;
	int time1 = (int) pow(base, exponent);
	int time2;

	quantumFile << "Step 3 (Algorithm 2: Single-solution algorithm)\n";
	quantumFile << "Time1 = " << time1 << " time(s)\n\n";

	for(int i = 1; i <= time1; i++) {
		thirdStepA();
		quantumFile << "Step 3 - Time: " << i << " of " << time1 << "\n\n";
		quantumFile << "Step 3 - A\n\n";
		display_in_file_with_x_H(); //O(En)

		time2 = (int) sqrt((double)r);
		quantumFile << "Step 3 - B\n";
		quantumFile << "Time2 = " << time2 << " time(s)\n\n";
		for(int j = 1; j <= time2; j++) {
			quantumFile << "Step 3 - B - Time: " << j << " of " << time2 << "\n\n";
			thirdStepB(); //O(P*(n^2))
		}
	}
}

/*
 * Fourth Step
 *
 * Fourth step of simulator
 * Fourth step of algorithm 2.
 *
 * Computational Complexity (Big-O Notation):
 * O(En)
 */
void QuantumDistinctness::fourthStep() { //O(En)
	quantumFile << "Show the result\n";
	quantumFile << "Step 4 (Algorithm 2: Single-solution algorithm)\n";
	display_in_file_with_x_H(); //O(En)

	deterministic_measurement(); //O(En)
	probabilistic_measurement(); //O(En)
}

/*
 * Third Step A
 *
 * Third step of simulator, part A.
 * Third step of algorithm 2, part A
 *
 * Computational Complexity (Big-O Notation):
 * O(Ern)
 */
void QuantumDistinctness::thirdStepA() { //O(Ern)
	vector<State>::iterator current = statesDimensionH.begin(),
								end = statesDimensionH.end();
	for(; current != end; current++) //O(E)
		(*current).search_equals_change_signal(elements, k); //O(rn)
}

/*
 * Third Step B
 *
 * Third step of simulator, part B
 * Third step of algorithm 2, part B
 * This part calls the quantum steps 
 *
 * Computational Complexity (Big-O Notation):
 * O(P*(n^2))
 */
void QuantumDistinctness::thirdStepB() { //O(Pnn)
	firstStepQuantumWalk(); //O(Enn)
	secondStepQuantumWalk(); //O(Pnr)
	thirdStepQuantumWalk(); //O(En)
	fourthStepQuantumWalk(); //O(Pnn)
	fifthStepQuantumWalk();
	sixthStepQuantumWalk(); //O(Pn)
}

/*
 * First Step Quantum Walk
 *
 * This step makes a mapping.
 *
 * Computational Complexity (Big-O Notation):
 * O(E*(n^2))
 */
void QuantumDistinctness::firstStepQuantumWalk() { //O(E*(n^2))
	float factor = (2.0 / ((float)N - (float)r));
	vector<State>::iterator current = statesDimensionH.begin(),
								end = statesDimensionH.end();
	for(; current != end; current++) //O(E)
		(*current).transformation_mapping(factor); //O(n^2)

	quantumFile << "Step 1 (Quantum Walk)\n\n";
	display_in_file_with_x_H(); //O(En)
}

/*
 * Second Step Quantum Walk
 *
 * Change the Hilbert space H, transforming this in H' 
 *
 * Computational Complexity (Big-O Notation):
 * O(Pnr)
 */
void QuantumDistinctness::secondStepQuantumWalk() { //O(Pnr)
	vector<State>::iterator current = statesDimensionH.begin(),
								end = statesDimensionH.end();
	map<int, double>::iterator yCurrent, yEnd;
	map<int, double> y;
	set<int> s;
	int position;
	for(; current != end; current++) { //O(E)
		y = (*current).getY(); //O(n-r)
		yCurrent = y.begin();
		yEnd = y.end();
		for(; yCurrent != yEnd; yCurrent++) { //O(n-r)
			s = (*current).getS(); //O(1)
			s.insert((*yCurrent).first); //O(log(r))
			vector<int> v(s.begin(), s.end()); //O(r)
			position = utils->calculate_position(v, 0, N, r+1, 0);
			statesDimensionHLine[position].change_amplitude((*yCurrent).first, (*yCurrent).second); //O(log(n-r))
			s.clear(); //O(r)
		}
		y.clear(); //O(n-r)
	}

	quantumFile << "Step 2 (Quantum Walk)\n\n";
	display_in_file_with_x_H_Line_with_0(); //O(Pnr)
}

/*
 * Third Step Quantum Walk
 *
 * Computational Complexity (Big-O Notation):
 * 
 */
void QuantumDistinctness::thirdStepQuantumWalk() {
	quantumFile << "Step 3 (Quantum Walk)\n\n";
	display_in_file_with_x_H_Line(); //O(En)
}

/*
 * Fourth Step Quantum Walk
 *
 * Makes a new mapping.
 *
 * Computational Complexity (Big-O Notation):
 * O(P*(n^2))
 */
void QuantumDistinctness::fourthStepQuantumWalk() { //O(P*(n^2))
	float factor = (2.0 / ((float)r + 1));
	vector<State>::iterator current = statesDimensionHLine.begin(),
								end = statesDimensionHLine.end();
	for(; current != end; current++) //O(P)
		(*current).transformation_mapping(factor); //O(n^2)

	quantumFile << "Step 4 (Quantum Walk)\n\n";
	display_in_file_with_x_H_Line(); //O(Pn)
}

/*
 * Fifth Step Quantum Walk
 *
 *
 * Computational Complexity (Big-O Notation):
 * O(Pnr)
 */
void QuantumDistinctness::fifthStepQuantumWalk() { //O(Pnr)
	quantumFile << "Step 5 (Quantum Walk)\n\n";
	display_in_file_with_x_H_Line_with_0(); //O(Pnr)
}

/*
 * Sixth Step Quantum Walk
 *
 * Comes back to the initial Hilbert Space, H. 
 *
 * Computational Complexity (Big-O Notation):
 * O(Pn)
 */
void QuantumDistinctness::sixthStepQuantumWalk() { //O(Pn)
	vector<State>::iterator current = statesDimensionHLine.begin(),
								end = statesDimensionHLine.end();
	map<int, double>::iterator yCurrent, yEnd;
	map<int, double> y;
	set<int> s;
	int position;
	for(; current != end; current++) { //O(P)
		y = (*current).getY(); //O(n-r)
		yCurrent = y.begin();
		yEnd = y.end();
		for(; yCurrent != yEnd; yCurrent++) { //O(n-r)
			s = (*current).getS(); //O(r)
			s.erase((*yCurrent).first); //O(log(r))
			vector<int> v(s.begin(), s.end()); //O(r)
			position = utils->calculate_position(v, 0, N, r, 0);
			statesDimensionH[position].change_amplitude((*yCurrent).first, (*yCurrent).second); //O(log(n-r))
			s.clear(); //O(r)
		}
		y.clear(); //O(n-r)
	}

	quantumFile << "Step 6 (Quantum Walk)\n\n";
	display_in_file_with_x_H(); //O(En)
}

/*
 * Deterministic Measurement
 * Here we verify the correct answer to compare with the answer gave by the probabilistic measurement.
 *
 * Computational Complexity (Big-O Notation):
 * O(En)
 */
void QuantumDistinctness::deterministic_measurement(){ //O(En)
	vector<State>::iterator current = statesDimensionH.begin(),
							    end = statesDimensionH.end();
	bool condition;
	double amplitude, amplitudeCandidate = 0.0f;
	set<int> sCandidate;
	for(; current != end; current++) { //O(E)
		condition = (*current).amplitudes_equals_of_y(); //O(n-r)
		if(condition){
			amplitude = (*current).getAmplitude(); //O(1)
			if(amplitude > amplitudeCandidate){
				amplitudeCandidate = amplitude;
				sCandidate.clear(); //O(n)
				sCandidate = (*current).getS(); //O(r)
			}else{
				if(amplitude == amplitudeCandidate){
					sCandidate = utils->set_intersection(sCandidate, (*current).getS()); //O(r*log(r))
				}
			}
		}
	}

	stringstream answer;
	answer << "\nDeterministic Measurement:" << endl;
	if(sCandidate.size() == 0 || sCandidate.size() < k)
		answer << "There is no simple "<< k << "-collision";
	else{
		answer << "There is a simple " << k << "-collision" << endl;
		answer << "Positions: ";
		set<int>::iterator currentS = sCandidate.begin(),
							   endS = sCandidate.end();
		for(; currentS != endS; currentS++) //O(r)
			answer << (*currentS) << " ";
	}
	quantumFile << answer.str() << "\n";
	cout << answer.str() << "\n";
}

/*
 * Probabilistic Measurement
 * Here we simulates de measurement. We get, randomly, a number
 * and we check which range, represented by the states of superposition,
 * this number is, getting the state measured.
 *
 * Computational Complexity (Big-O Notation):
 * O(En)
 */
void QuantumDistinctness::probabilistic_measurement() { //O(En)
    srand(std::time(0));
    int random = rand() % 101;
    vector<State>::iterator current = statesDimensionH.begin(),
							    end = statesDimensionH.end();
    double cumulativeProbability = 0.0f;
	int found = 0;
	for(; current != end; current++) { //O(E)

		cumulativeProbability = (*current).measurement(cumulativeProbability, (double)random, root, found); //O(n-r)

		if(found == 1){
			stringstream answer;
			answer << endl;
			answer << "Probabilistic Measurement:" << endl;
			answer << "Random: " << random << endl;

			if(!verifyCollision((*current).getS())){
				answer << "There is no simple "<< k << "-collision";
			} else{
				answer << "There is a simple " << k << "-collision" << endl;
				answer << "Positions: ";
				set<int> s = (*current).getS();
				set<int>::iterator currentS = s.begin(),
								       endS = s.end();
				for(; currentS != endS; currentS++) { //O(r)
					answer << (*currentS) << " ";
				}
			}
			
			quantumFile << answer.str() << "\n";
			cout << answer.str() << "\n";

			found = 0;
			//return;
		}
	}
}

/*
 * Display In File Without X - Dimension H
 *
 * |S>|y>
 *
 * Computational Complexity (Big-O Notation):
 * O(En)
 */
void QuantumDistinctness::display_in_file_without_x_H() {
	quantumFile << "|Phi> = (1 / sqrt(" << root << "))*\n[\n";

	vector<State>::iterator current = statesDimensionH.begin(),
							    end = statesDimensionH.end();
	for(; current != end; current++) //O(E)
		(*current).display_in_file_without_x(quantumFile); //O(n-r)

	quantumFile << "]\n\n\n";
}

/*
 * Display In File With X - Dimension H
 *
 * |S>|x>|y>
 *
 * Computational Complexity (Big-O Notation):
 * O(En)
 */
void QuantumDistinctness::display_in_file_with_x_H() {
	quantumFile << "|Phi> = (1 / sqrt(" << root << "))*\n[\n";

	vector<State>::iterator current = statesDimensionH.begin(),
							    end = statesDimensionH.end();
	for(; current != end; current++) //O(E)
		(*current).display_in_file_with_x(quantumFile, elements); //O(n-r)

	quantumFile << "]\n\n\n";
}

/*
 * Display In File With X - Dimension H'
 *
 * |S>|x>|y>
 *
 * Computational Complexity (Big-O Notation):
 * O(Pn)
 */
void QuantumDistinctness::display_in_file_with_x_H_Line() { //O(Pn)
	quantumFile << "|Phi> = (1 / sqrt(" << root << "))*\n[\n";

	vector<State>::iterator current = statesDimensionHLine.begin(),
							    end = statesDimensionHLine.end();
	for(; current != end; current++) //O(P)
		(*current).display_in_file_with_x(quantumFile, elements); //O(n-r)

	quantumFile << "]\n\n\n";
}

/*
 * Display In File With X With 0 - Dimension H'
 *
 *|S>|x>|0>
 *
 * Computational Complexity (Big-O Notation):
 * O(Pnr)
 */
void QuantumDistinctness::display_in_file_with_x_H_Line_with_0(){ //O(Pnr)
	quantumFile << "|Phi> = (1 / sqrt(" << root << "))*\n[\n";
	
	vector<State>::iterator current = statesDimensionHLine.begin(),
							    end = statesDimensionHLine.end();
	for(; current != end; current++) //O(P)
		(*current).display_in_file_with_x_with_0(quantumFile, elements); //O(nr)

	quantumFile << "]\n\n\n";
}

/*
 * Verify Collision to discover which positions has collision.
 *
 * Computational Complexity (Big-O Notation):
 * O(r^2)
 */
bool QuantumDistinctness::verifyCollision(set<int> S){ //O(r^2)
	set<int>::iterator current = S.begin(),
		                   end = S.end(),
					  auxiliar;
	int count = 0;
	for(; current != end; current++) { //O(r)
		auxiliar = ++current;
		current--;
		for(; auxiliar != end; auxiliar++) { //O(r)
			if(elements[(*current) - 1] == elements[(*auxiliar) - 1]) {
				count++;
			}
		}
		if(count == (k-1))
			return true;
		count = 0;
	}
	return false;
}

/*
 * Subsets
 *
 * Calculate the subsets
 *
 * Computational Complexity (Big-O Notation):
 * O((2^n)*n*log(n-r)) -> O(2^n)
 */
void QuantumDistinctness::sub_sets() { //O((2^n)*((n-r)*log(n-r))) -> O((2^n)*n*log(n-r))
	int *elementsH = (int *) malloc(sizeof(int) * r);
	int *elementsHLine = (int *) malloc(sizeof(int) * (r+1));
	int *elementsY = (int *) malloc(sizeof(int) * (N-r));
	int lengthH, lengthHLine, lengthY;
	
	for(int i = (1 << N) - 1; i >= 0; i--) { //O(2^n)
		lengthH = 0;
		lengthHLine = 0;
		lengthY = 0;
		for(int j = (N - 1); j >= 0; j--) { //O(n)
			if((i & (1 << j)) != 0) {
				if(lengthH <= r)
					elementsH[lengthH++] = (N-j);
				if(lengthHLine <= (r+1))
					elementsHLine[lengthHLine++] = (N-j);
			}else{
				if(lengthY <= (N-r))
					elementsY[lengthY++] = (N-j);
			}
		}

		if(lengthH == r){
			State newState;
			newState.insert_in_S(elementsH, lengthH); //O(r*log(r))
			newState.insert_in_y(elementsY, lengthY); //O((n-r)*log(n-r))
			statesDimensionH.push_back(newState);
		}
		if(lengthHLine == (r+1)){
			State newState;
			newState.insert_in_S(elementsHLine, lengthHLine); //O(r*log(r))
			newState.insert_in_y(elementsHLine, lengthHLine); //O((n-r)*log(n-r))
			statesDimensionHLine.push_back(newState);
		}

	}
}

/*
 * Menu
 *
 * Menu of simulator
 *
 * Computational Complexity (Big-O Notation):
 * O(1)
 */
void QuantumDistinctness::menu(){
	char option;
	string line;
	cout << "Welcome to Element Distinctness Simulator\n" << endl;
	cout << "Select Your Option\n";
	cout << "1 - Generate Random Values\n";
	cout << "2 - Define My Own Values\n";
	cout << "0 - Exit\n";
	cout << endl;
	cout << "Option: ";
	getline(cin, line);
	cout << endl;
	option = line.at(0);
	if(line.length() != 1)
		option = '9';

	switch(option){
		case '0':
			cout << "Press any key to continue...";
			system("pause > nul");
			exit(EXIT_SUCCESS);
			break;
		case '1':
			randomList();
			break;
		case '2':
			userList();
			break;
		default:
			cout << "Invalid option!!!\n\n";
			cout << "Press any key to continue...";
			system("pause > nul");
			system("cls");
			menu();
	}
}

/*
 * Random List
 *
 * Generate a list randomly 
 *
 * Computational Complexity (Big-O Notation):
 * O(n)
 */
void QuantumDistinctness::randomList(){
	int lowerLimit, upperLimit;
	cout << "Enter the number of values: ";
	cin >> N;
	if(N < MINIMUM){
		cout << endl;
		cout << "ERROR!! The minimum quantity of the list is " << MINIMUM << endl;
		cout << endl;
		cout << "Press any key to continue...";
		system("pause > nul");
		system("cls");
		cout << "Welcome to Element Distinctness Simulator\n" << endl;
		cout << "Select Your Option\n";
		cout << "1 - Generate Random Values\n";
		cout << "2 - Define My Own Values\n";
		cout << "0 - Exit\n";
		cout << endl;
		cout << "Option: 1";
		cout << endl << endl;
		randomList();
		return;
	}
	cout << "Enter the lower limit: ";
	cin >> lowerLimit;
	cout << "Enter the upper limit: ";
	cin >> upperLimit;

	elements = (int *) malloc(sizeof(int) * N);
	srand(std::time(NULL));
	for(int i = 0; i < N; i++) //O(n)
		elements[i] = (rand() % (upperLimit - lowerLimit + 1)) + lowerLimit;
	cout << endl;
}

/*
 * User List
 *
 * Get a list passed by user.
 *
 * Computational Complexity (Big-O Notation):
 * O(n)
 */
void QuantumDistinctness::userList(){
	cout << "Enter the number of values: ";
	cin >> N;
	if(N < MINIMUM){
		cout << endl;
		cout << "ERROR!! The minimum quantity of the list is " << MINIMUM << endl;
		cout << endl;
		cout << "Press any key to continue...";
		system("pause > nul");
		system("cls");
		cout << "Welcome to Element Distinctness Simulator\n" << endl;
		cout << "Select Your Option\n";
		cout << "1 - Generate Random Values\n";
		cout << "2 - Define My Own Values\n";
		cout << "0 - Exit\n";
		cout << endl;
		cout << "Option: 2";
		cout << endl << endl;
		userList();
		return;
	}
	elements = (int *) malloc(sizeof(int) * N);
	for(int i = 0; i < N; i++) { //O(n)
		cout << "Enter number " << (i+1) << ": ";
		cin >> elements[i];
	}
	cout << endl;
}
