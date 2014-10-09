/*
 * Simulador de Distin��o de Elementos
 *
 * File: QuantumDistinctness.cpp
 *
 * Created on: 13/02/2014
 *    Authors: Alexandre Santiago de Abreu
 *             Matheus Manzoli Ferreira
 *
 *      Email: alexandresantiago@id.uff.br
 *             matheusmanzoli@gmail.com
 *
 * Trabalho de Monografia para a 
 * Universidade Federal Fluminense.
 * Instituto de Computa��o.
 * Niter�i, Rio de Janeiro, Brasil.
 *
 * Este arquivo cont�m m�todos da classe 
 * QuantumDistinctness usadas no Simulador 
 * de Distin��o de Elementos.
 */

#include "Library.h"

/*
 * Construtor do simulador
 *
 * Inicializa��o de todas as vari�veis
 *
 * Par�metros:
 * elements = lista de valores para achar a distin��o
 * minimum = tamanho m�nimo da lista.
 * maximum = tamanho m�ximo da lista.
 * N = tamanho da lista, definida posteriormente
 * r = N^(2/3), definida posteriormente
 * k = quantidade de n�meros distintos que a lista deve possuir.
 * root = valor para o calculo da amplitude.
 * quantumName = nome do arquivo em que ser� guardado todos os passos do algoritmo
 */
QuantumDistinctness::QuantumDistinctness() {
	N = 0;

	r = 0; //r>= k

	k = 2;

	M = 0;

	root = 0;

	strcpy(quantumFileName, "quantumDistinctness.txt");

	utils = new Utils;

	elements = NULL;

	MINIMUM = 3; //faz r no minimo 2, satisfazendo r >= k

	MAXIMUM = 34;

	menu();

	init();
}

/*
 * Destrutor do simulador
 */
QuantumDistinctness::~QuantumDistinctness() {
	if(elements != NULL)
		free(elements);
	
	delete utils;
}

/*
 * Init
 *
 * In�cio do simulador
 * C�lculo de algumas das vari�veis
 * Chama os passos do algoritmo
 */
void QuantumDistinctness::init() {
	float exponent = (k) / (k + 1.0);
	r = (int) pow(N, exponent);
	
	quantumFile.open(quantumFileName, ios::out);
	quantumFile.setf(ios::fixed, ios::floatfield);
	quantumFile.precision(2);

	time = clock();

	quantumFile << "Elements: [";
	
	for(int i = 0; i < N-1; i++)
		quantumFile << elements[i] << ", ";
	quantumFile << elements[N-1] << "]\n";

	quantumFile << "N: " << N << "\n";

	quantumFile << "R: " << r << "\n";

	quantumFile << "K: " << k << "\n";

	//quantumFile << "M: " << M << "\n";

	quantumFile << "\n\n";

	firstStep();
	secondStep();
	thirdStep();
	fourthStep();

	end();
}

/*
 * End
 *
 * �ltima parte do simulador
 * Calculo do tempo total do simulador
 * Fechamento do arquivo
 */
void QuantumDistinctness::end() {
	time = clock() - time;

	quantumFile.precision(5);
	quantumFile << "\n\nTime (secs): " << ((float)time)/CLOCKS_PER_SEC;

	quantumFile.close();
}

/*
 * First Step
 *
 * Primeiro passo do Simulador
 * Primeiro passo do algoritmo 2.
 *
 * Computational Complexity (Big-O Notation):
 * 
 */
void QuantumDistinctness::firstStep() {
	root = (utils->combinatorial(N,r)) * (N - r); //O(n^2)

	sub_sets_H();
	sub_sets_H_Line();

	quantumFile << "Step 1 (Algorithm 2: Single-solution algorithm)\n";
	display_in_file_without_x_H();
}

/*
 * Second Step
 *
 * Segundo passo do Simulador
 * Segundo passo do algoritmo 2.
 *
 * Computational Complexity (Big-O Notation):
 * 
 */
void QuantumDistinctness::secondStep() {
	quantumFile << "Step 2 (Algorithm 2: Single-solution algorithm)\n";
	display_in_file_with_x_H();
}

/*
 * Third Step
 *
 * Terceiro passo do Simulador
 * Terceiro passo do algoritmo 2.
 *
 * Computational Complexity (Big-O Notation):
 * 
 */
void QuantumDistinctness::thirdStep() {
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
		display_in_file_with_x_H();

		time2 = (int) sqrt((double)r);
		quantumFile << "Step 3 - B\n";
		quantumFile << "Time2 = " << time2 << " time(s)\n\n";
		for(int j = 1; j <= time2; j++) {
			quantumFile << "Step 3 - B - Time: " << j << " of " << time2 << "\n\n";
			thirdStepB();
		}
	}
}

/*
 * Fourth Step
 *
 * Quarto passo do Simulador
 * Quarto passo do algoritmo 2.
 *
 * Computational Complexity (Big-O Notation):
 * 
 */
void QuantumDistinctness::fourthStep() {
	quantumFile << "Show the result\n";
	quantumFile << "Step 4 (Algorithm 2: Single-solution algorithm)\n";
	display_in_file_with_x_H();

	deterministic_measurement();
	probabilistic_measurement();
}

/*

*/
void QuantumDistinctness::thirdStepA() {
	vector<State>::iterator current = statesDimensionH.begin(),
								end = statesDimensionH.end();
	for (; current != end; current++)
		(*current).search_equals_change_signal(elements, k);
}

/*

*/
void QuantumDistinctness::thirdStepB() {
	firstStepQuantumWalk();
	secondStepQuantumWalk();
	thirdStepQuantumWalk();
	fourthStepQuantumWalk();
	fifthStepQuantumWalk();
	sixthStepQuantumWalk();
}

/*

*/
void QuantumDistinctness::firstStepQuantumWalk() {
	float factor = (2.0 / ((float)N - (float)r));
	vector<State>::iterator current = statesDimensionH.begin(),
								end = statesDimensionH.end();
	for (; current != end; current++)
		(*current).transformation_mapping(factor);

	quantumFile << "Step 1 (Quantum Walk)\n\n";
	display_in_file_with_x_H();
}

/*

*/
void QuantumDistinctness::secondStepQuantumWalk() {
	vector<State>::iterator current = statesDimensionH.begin(),
								end = statesDimensionH.end();
	map<int, double>::iterator yCurrent, yEnd;
	map<int, double> y;
	set<int> s;
	for (; current != end; current++) {
		y = (*current).getY();
		yCurrent = y.begin();
		yEnd = y.end();
		for (; yCurrent != yEnd; yCurrent++){
			s = (*current).getS();//N
			s.insert((*yCurrent).first);//log N
			vector<int> v(s.begin(), s.end());//N
			int posicao = utils->calculate_position(v, 0, N, r+1, 0);
			statesDimensionHLine[posicao].change_amplitude((*yCurrent).first, (*yCurrent).second);
		}
	}

	quantumFile << "Step 2 (Quantum Walk)\n\n";
	display_in_file_with_x_H_Line();
}

/*

*/
void QuantumDistinctness::thirdStepQuantumWalk() {

}

/*

*/
void QuantumDistinctness::fourthStepQuantumWalk() {
	float factor = (2.0 / ((float)r + 1));
	vector<State>::iterator current = statesDimensionHLine.begin(),
								end = statesDimensionHLine.end();
	for (; current != end; current++)
		(*current).transformation_mapping(factor);

	quantumFile << "Step 4 (Quantum Walk)\n\n";
	display_in_file_with_x_H_Line();
}

/*

*/
void QuantumDistinctness::fifthStepQuantumWalk() {

}

/*

*/
void QuantumDistinctness::sixthStepQuantumWalk() {
	vector<State>::iterator current = statesDimensionHLine.begin(),
								end = statesDimensionHLine.end();
	map<int, double>::iterator yCurrent, yEnd;
	map<int, double> y;
	set<int> s;
	for (; current != end; current++) {
		y = (*current).getY();
		yCurrent = y.begin();
		yEnd = y.end();
		for (; yCurrent != yEnd; yCurrent++){
			s = (*current).getS();
			set<int>::iterator it;
			s.erase((*yCurrent).first);
			vector<int> v(s.begin(), s.end());
			int posicao = utils->calculate_position(v, 0, N, r, 0);
			statesDimensionH[posicao].change_amplitude((*yCurrent).first, (*yCurrent).second);
		}
	}

	quantumFile << "Step 6 (Quantum Walk)\n\n";
	display_in_file_with_x_H();
}

/*

*/
void QuantumDistinctness::deterministic_measurement(){
	vector<State>::iterator current = statesDimensionH.begin(),
							    end = statesDimensionH.end();
	bool condition;
	double amplitude, amplitudeCandidate = 0.0f;
	set<int> sCandidate;
	for (; current != end; current++){
		condition = (*current).amplitudes_equals_of_y();
		if(condition){
			amplitude = (*current).getAmplitude();
			if(amplitude > amplitudeCandidate){
				amplitudeCandidate = amplitude;
				sCandidate = (*current).getS();
			}else{
				if(amplitude == amplitudeCandidate){
					sCandidate = utils->set_intersection(sCandidate, (*current).getS());
				}
			}
		}
	}

	stringstream answer;
	if(sCandidate.size() == 0)
		answer << "There is no "<< k << "-collision";
	else{
		answer << "There is a " << k << "-collision\nPositions: ";
		set<int>::iterator currentS = sCandidate.begin(),
							   endS = sCandidate.end();
		for (; currentS != endS; currentS++){
			answer << (*currentS) << " ";
		}
	}
	quantumFile << answer.str() << "\n";
	cout << answer.str() << "\n";

}

void QuantumDistinctness::probabilistic_measurement() {
    srand(std::time(0));
    int random = rand() % 101;
	//int random = 109;
	cout << "\nRandom: " << random << endl;
    vector<State>::iterator current = statesDimensionH.begin(),
							    end = statesDimensionH.end();
    double cumulativeProbability = 0.0f;
	int found = 0;
	for (; current != end; current++){
		//cout << "Probabilidade: " <<  cumulativeProbability;
		cumulativeProbability = (*current).measurement(cumulativeProbability, (double)random, root, found);

		//if(cumulativeProbability > 0)
			//cout << " " <<  cumulativeProbability << endl;
		//else
			//cout << " " << -cumulativeProbability << endl;
		//if(cumulativeProbability == -1.0f){
		//if(cumulativeProbability < 0){	
		if(found == 1){
			stringstream answer;

			if(verifyCollision((*current).getS())){
				cout << endl;
				answer << "There is a " << k << "-collision\nPositions: ";
			} else{
				answer << "\nThere is no "<< k << "-collision\n\n";
			}

			set<int> S = (*current).getS();
			set<int>::iterator currentS = S.begin(),
								   endS = S.end();
			for (; currentS != endS; currentS++){
				answer << (*currentS) << " ";
			}
			quantumFile << answer.str() << "\n";
			cout << answer.str() << "\n\n";

			//return; 
			//cumulativeProbability*=-1;
			found = 0;//return;
		}
	}
}

/*
 * Display In File Without X - Dimension H
 *
 * Mostra no Arquivo os estados sem o X
 * |S>|y>
 *
 * Computational Complexity (Big-O Notation):
 * 
 */
void QuantumDistinctness::display_in_file_without_x_H() {
	quantumFile << "|Phi> = (1 / sqrt(" << root << "))*\n[\n";

	vector<State>::iterator current = statesDimensionH.begin(),
							    end = statesDimensionH.end();
	for(; current != end; current++)
		(*current).display_in_file_without_x(quantumFile);

	quantumFile << "]\n\n\n";
}

/*
 * Display In File With X - Dimension H
 *
 * Mostra no Arquivo os estados com o X
 * |S>|x>|y>
 *
 * Computational Complexity (Big-O Notation):
 * 
 */
void QuantumDistinctness::display_in_file_with_x_H() {
	quantumFile << "|Phi> = (1 / sqrt(" << root << "))*\n[\n";

	vector<State>::iterator current = statesDimensionH.begin(),
							    end = statesDimensionH.end();
	for(; current != end; current++)
		(*current).display_in_file_with_x(quantumFile, elements);

	quantumFile << "]\n\n\n";
}

/*
 * Display In File With X - Dimension H'
 *
 * Mostra no Arquivo os estados com o X
 * |S>|x>|y>
 *
 * Computational Complexity (Big-O Notation):
 * 
 */
void QuantumDistinctness::display_in_file_with_x_H_Line() {
	quantumFile << "|Phi> = (1 / sqrt(" << root << "))*\n[\n";

	vector<State>::iterator current = statesDimensionHLine.begin(),
							    end = statesDimensionHLine.end();
	for (; current != end; current++)
		(*current).display_in_file_with_x(quantumFile, elements);

	quantumFile << "]\n\n\n";
}

/*

*/
void QuantumDistinctness::sub_sets_H() {
	string before = "";
	string after = "";
	for (int value = 1; value <= N; value++)
		after += (char) (((int) '0') + value);

	combination_H(before, after, r);
}

/*

*/
void QuantumDistinctness::combination_H(string before, string after,
		int quantity) {
	if (quantity == 0) {
		State newState;
		newState.insert_in_S(before);

		int positionBefore = 0;
		int value;
		int candidate;
		for (candidate = 1; candidate <= N; candidate++) {
			if (positionBefore == (int) before.size())
				break;

			value = (int) (before[positionBefore] - '0');

			if (value == candidate)
				positionBefore++;
			else
				newState.insert_in_y(candidate);
		}

		for (; candidate <= N; candidate++)
			newState.insert_in_y(candidate);

		statesDimensionH.push_back(newState);

	} else {
		int length = after.size();
		for (int position = 0; position < length; position++) {
			string firstPart = after.substr(0, position);

			string secondPart;
			stringstream secondPartAuxiliar;
			char secondPartChar = after.at(position);
			secondPartAuxiliar << secondPartChar;
			secondPartAuxiliar >> secondPart;

			bool condition = true;
			if (!firstPart.find(secondPart) != std::string::npos)
				condition = false;

			if (!condition) {
				string newBefore = before + after[position];
				string newAfter = after.substr(position + 1, after.size());
				combination_H(newBefore, newAfter, quantity - 1);
			}
		}
	}
}

/*

*/
void QuantumDistinctness::sub_sets_H_Line() {
	string before = "";
	string after = "";
	for (int value = 1; value <= N; value++)
		after += (char) (((int) '0') + value);

	combination_H_Line(before, after, r+1);
}

/*

*/
void QuantumDistinctness::combination_H_Line(string before, string after,
		int quantity) {
	if (quantity == 0) {
		State newState;
		newState.insert_in_S(before);
		newState.insert_in_y(before);

		statesDimensionHLine.push_back(newState);

	} else {
		int length = after.size();
		for (int position = 0; position < length; position++) {
			string firstPart = after.substr(0, position);

			string secondPart;
			stringstream secondPartAuxiliar;
			char secondPartChar = after.at(position);
			secondPartAuxiliar << secondPartChar;
			secondPartAuxiliar >> secondPart;

			bool condition = true;
			if (!firstPart.find(secondPart) != std::string::npos) {
				condition = false;
			}

			if (!condition) {
				string newBefore = before + after[position];
				string newAfter = after.substr(position + 1, after.size());
				combination_H_Line(newBefore, newAfter, quantity - 1);
			}
		}
	}
}

//alterar para k>2
bool QuantumDistinctness::verifyCollision(set<int> S){
	set<int>::iterator current = S.begin(),
		                   end = S.end(),
					  auxiliar;
	for (; current != end; current++) {
		auxiliar = ++current;
		current--;
		for (; auxiliar != end; auxiliar++) {
			if (elements[(*current) - 1] == elements[(*auxiliar) - 1]) {
				return true;
			}
		}
	}
	return false;
}

/*
 * Menu
 *
 * Menu do Simulador
 *
 * Computational Complexity (Big-O Notation):
 * O(1)
 */
void QuantumDistinctness::menu(){
	char option;
	string line;
	cout << "Bem-Vindo ao Simulador de Distincao de Elementos\n" << endl;//cout << "Welcome to Quantum Distinctness Simulator\n" << endl;
	cout << "Selecione sua Opcao\n";//cout << "Select Your Option\n";
	cout << "1 - Definir Valores Aleatorios\n";
	cout << "2 - Definir Valores\n";
	cout << "0 - Sair\n";//cout << "0 - Exit\n";
	cout << endl;
	cout << "Opcao: ";//cout << "Option: ";
	getline(cin, line);
	cout << endl;
	option = line.at(0);
	if(line.length() != 1)
		option = '9';

	switch(option){
		case '0':
			exit(0);
			break;
		case '1':
			randomList();
			break;
		case '2':
			userList();
			break;
		default:
			cout << "Opcao Invalida!!!\n\n";//cout << "Invalid option!!!\n\n";
			cout << "Pressione qualquer tecla para continuar...";
			system("pause > nul");
			system("cls");
			menu();
	}
}

/*
 * Random List
 *
 * Gera Lista Aleat�ria de Valores 
 * o Usu�rio
 *
 * Computational Complexity (Big-O Notation):
 * O(n)
 */
void QuantumDistinctness::randomList(){ //fazer prote��es?
	int lowerLimit, upperLimit;
	cout << "Diga a quantidade de numeros: ";
	cin >> N;
	cout << "Diga o limite inferior: ";
	cin >> lowerLimit;
	cout << "Diga o limite superior: ";
	cin >> upperLimit;

	elements = (int *) malloc(sizeof(int) * N);
	srand(std::time(NULL));
	for(int i = 0; i < N; i++){
		elements[i] = (rand() % (upperLimit - lowerLimit + 1)) + lowerLimit;
	}
	cout << endl;
}

/*
 * User List
 *
 * Pega a Lista de Valores do Usu�rio
 *
 * Computational Complexity (Big-O Notation):
 * O(n)
 */
void QuantumDistinctness::userList(){ //fazer prote��es?
	cout << "Diga a quantidade de numeros: ";
	cin >> N;
	elements = (int *) malloc(sizeof(int) * N);
	for(int i = 0; i < N; i++){
		cout << "Diga o numero " << (i+1) << ": ";
		cin >> elements[i];
	}
	cout << endl;
}