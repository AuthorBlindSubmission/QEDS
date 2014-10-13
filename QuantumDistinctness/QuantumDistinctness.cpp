/*
 * Simulador de Distinção de Elementos
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
 * Instituto de Computação.
 * Niterói, Rio de Janeiro, Brasil.
 *
 * Este arquivo contém métodos da classe 
 * QuantumDistinctness usadas no Simulador 
 * de Distinção de Elementos.
 */

#include "Library.h"

/*
 * Construtor do simulador
 *
 * Inicialização de todas as variáveis
 *
 * Parâmetros:
 * elements = lista de valores para achar a distinção
 * minimum = tamanho mínimo da lista.
 * maximum = tamanho máximo da lista.
 * N = tamanho da lista, definida posteriormente
 * r = N^(2/3), definida posteriormente
 * k = quantidade de números distintos que a lista deve possuir.
 * root = valor para o calculo da amplitude.
 * quantumName = nome do arquivo em que será guardado todos os passos do algoritmo
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

	cout << "\nPress any key to continue...";
	system("pause > nul");
}

/*
 * Init
 *
 * Início do simulador
 * Cálculo de algumas das variáveis
 * Chama os passos do algoritmo
 */
void QuantumDistinctness::init() {
	float exponent = (k) / (k + 1.0);
	r = (int) pow(N, exponent);
	
	quantumFile.open(quantumFileName, ios::out);
	quantumFile.setf(ios::fixed, ios::floatfield);
	quantumFile.precision(20);

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
 * Última parte do simulador
 * Calculo do tempo total do simulador
 * Fechamento do arquivo
 */
void QuantumDistinctness::end() {
	time = clock() - time;

	quantumFile.precision(5);
	quantumFile << "\nTime (secs): " << ((float)time)/CLOCKS_PER_SEC;

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

	sub_sets();

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
 * Third Step A
 *
 * Terceiro passo do Simulador, parte A
 * Terceiro passo do algoritmo 2, parte A
 *
 * Computational Complexity (Big-O Notation):
 * 
 */
void QuantumDistinctness::thirdStepA() {
	vector<State>::iterator current = statesDimensionH.begin(),
								end = statesDimensionH.end();
	for(; current != end; current++)
		(*current).search_equals_change_signal(elements, k);
}

/*
 * Third Step B
 *
 * Terceiro passo do Simulador, parte B
 * Terceiro passo do algoritmo 2, parte B
 * Responsável pela chamada dos métodos 
 * da Caminhada Quântica
 *
 * Computational Complexity (Big-O Notation):
 * 
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
 * First Step Quantum Walk
 *
 * Primeiro passo da Caminhada Quântica
 * Faz o mapeamento da transformação
 *
 * Computational Complexity (Big-O Notation):
 * 
 */
void QuantumDistinctness::firstStepQuantumWalk() {
	float factor = (2.0 / ((float)N - (float)r));
	vector<State>::iterator current = statesDimensionH.begin(),
								end = statesDimensionH.end();
	for(; current != end; current++)
		(*current).transformation_mapping(factor);

	quantumFile << "Step 1 (Quantum Walk)\n\n";
	display_in_file_with_x_H();
}

/*
 * Second Step Quantum Walk
 *
 * Segundo passo da Caminhada Quântica
 * Faz a mudança do Estado de Hilbert 
 * de H para H'
 *
 * Computational Complexity (Big-O Notation):
 * 
 */
void QuantumDistinctness::secondStepQuantumWalk() {
	vector<State>::iterator current = statesDimensionH.begin(),
								end = statesDimensionH.end();
	map<int, double>::iterator yCurrent, yEnd;
	map<int, double> y;
	set<int> s;
	int position;
	for(; current != end; current++) {
		y = (*current).getY();
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
	display_in_file_with_x_H_Line();
}

/*
 * Third Step Quantum Walk
 *
 * Terceiro passo da Caminhada Quântica
 * Imprime com Xy no lugar correspondente ao y
 *
 * Computational Complexity (Big-O Notation):
 * 
 */
void QuantumDistinctness::thirdStepQuantumWalk() {

}

/*
 * Fourth Step Quantum Walk
 *
 * Quarto passo da Caminhada Quântica
 * Faz o mapeamento da transformação
 *
 * Computational Complexity (Big-O Notation):
 * 
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
 * Fifth Step Quantum Walk
 *
 * Quinto passo da Caminhada Quântica
 * Apaga o elemento em X correspondente 
 * ao novo y
 *
 * Computational Complexity (Big-O Notation):
 * 
 */
void QuantumDistinctness::fifthStepQuantumWalk() {

}

/*
 * Sixth Step Quantum Walk
 *
 * Sexto passo da Caminhada Quântica
 * Retorna de volta para o estado de 
 * Hilbert H
 *
 * Computational Complexity (Big-O Notation):
 * 
 */
void QuantumDistinctness::sixthStepQuantumWalk() {
	vector<State>::iterator current = statesDimensionHLine.begin(),
								end = statesDimensionHLine.end();
	map<int, double>::iterator yCurrent, yEnd;
	map<int, double> y;
	set<int> s;
	int position;
	for(; current != end; current++) {
		y = (*current).getY();
		yCurrent = y.begin();
		yEnd = y.end();
		for (; yCurrent != yEnd; yCurrent++){ //O(n-r)
			s = (*current).getS(); //O(1)
			s.erase((*yCurrent).first); //O(log(r))
			vector<int> v(s.begin(), s.end()); //O(r)
			position = utils->calculate_position(v, 0, N, r, 0);
			statesDimensionH[position].change_amplitude((*yCurrent).first, (*yCurrent).second); //O(log(n-r))
			s.clear(); //O(r)
		}
		y.clear(); //O(n-r)
	}

	quantumFile << "Step 6 (Quantum Walk)\n\n";
	display_in_file_with_x_H();
}

/*
 * Deterministic Measurement
 *
 * Medição determinística do estado
 * Medição feita para efeitos de comparação
 *
 * Computational Complexity (Big-O Notation):
 * 
 */
void QuantumDistinctness::deterministic_measurement(){ //O(E*n)
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
					sCandidate = utils->set_intersection(sCandidate, (*current).getS()); //O(n*log(r))
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
		for(; currentS != endS; currentS++) //O(n)
			answer << (*currentS) << " ";
	}
	quantumFile << answer.str() << "\n";
	cout << answer.str() << "\n";
}

/*
 * Probabilistic Measurement
 *
 * Medição probabilística do estado
 *
 * Computational Complexity (Big-O Notation):
 * 
 */
void QuantumDistinctness::probabilistic_measurement() { //O(E*(n-r))
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

//alterar para k>2
/*
 * Verify Collision
 *
 * Verifica o conjunto para ver quais são 
 * as posições que possuem colisões
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
 * Sub Sets
 *
 * Cálculo dos SubConjuntos
 *
 * Computational Complexity (Big-O Notation):
 * O(2^n)
 */
void QuantumDistinctness::sub_sets(){
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
			newState.insert_in_S(elementsH, lengthH);
			newState.insert_in_y(elementsY, lengthY);
			statesDimensionH.push_back(newState);
		}
		if(lengthHLine == (r+1)){
			State newState;
			newState.insert_in_S(elementsHLine, lengthHLine);
			newState.insert_in_y(elementsHLine, lengthHLine);
			statesDimensionHLine.push_back(newState);
		}

	}
		/*printf("H: ");
		mostra(elementsH, tamanhoH, r);
		printf(" - L: ");
		mostra(elementsHLine, tamanhoHLine, r+1);
		printf(" - Y: ");
		mostra(elementsY, tamanhoY, n-r);*/
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
 * Gera Lista Aleatória de Valores 
 * o Usuário
 *
 * Computational Complexity (Big-O Notation):
 * O(n)
 */
void QuantumDistinctness::randomList(){ //fazer proteções?
	int lowerLimit, upperLimit;
	cout << "Enter the number of values: ";
	cin >> N;
	cout << "Enter the lower limit: ";
	cin >> lowerLimit;
	cout << "Enter the upper limit: ";
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
 * Pega a Lista de Valores do Usuário
 *
 * Computational Complexity (Big-O Notation):
 * O(n)
 */
void QuantumDistinctness::userList(){ //fazer proteções?
	cout << "Enter the number of values: ";
	cin >> N;
	elements = (int *) malloc(sizeof(int) * N);
	for(int i = 0; i < N; i++){
		cout << "Enter number " << (i+1) << ": ";
		cin >> elements[i];
	}
	cout << endl;
}