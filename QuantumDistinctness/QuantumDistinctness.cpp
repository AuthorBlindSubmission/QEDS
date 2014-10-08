/*
 * QuantumDistinctness.cpp
 *
 *  Created on: 13/02/2014
 *      Author: Alexandre & Matheus
 */

#include "Library.h"

/**
*   Construtor do simulador
*   Inicialização de todas as váriaveis
*
*   Parâmetros:
*      NENHUM
*
*   Retorno:
*      NENHUM
*
*   MINIMUM -> tamanho mínimo da lista.
*   MAXIMUM -> tamanho máximo da lista.
*         N -> tamanho da lista.
*         r -> N^(2/3).
*         k -> quantidade de números distintos que a lista deve possuir.
*      root -> valor para o calculo da amplitude.
*  quantumName -> nome do arquivo em que será guardado todos os passos do algoritmo
*/
QuantumDistinctness::QuantumDistinctness() {
	MINIMUM = 3; //faz r no minimo 2, satisfazendo r >= k

	MAXIMUM = 34;

	N = 0;

	r = 0; //r>= k

	k = 2;

	M = 0;

	root = 0;

	strcpy(quantumFileName, "quantumDistinctness.txt");

	utils = new Utils;
}

/**
*   Destrutor do simulador
*
*   Parâmetros:
*      NENHUM
*
*   Retorno:
*      NENHUM
*/
QuantumDistinctness::~QuantumDistinctness() {
	delete utils;
	cout << "SAINDO DO SIMULADOR2" << endl;
}

/**
*   Início do simulador
*   Cálculo de algumas das variáveis
*   Chama os passos do algoritmo
*
*   Parâmetros:
*      vector<int> elements -> Vetor com os elementos.
*
*   Retorno:
*      NENHUM
*
*   M -> Vetor com os elementos.
*   N -> tamanho da lista.
*   r -> N^(2/3).
*/
void QuantumDistinctness::init(vector<int> _elements) {
	elements = _elements;

	initialStep();

	firstStep();
	secondStep();
	thirdStep();
	fourthStep();

	finalStep();
}

/**
*   Passo inicial do Simulador
*   Guarda no arquivo Quantum algumas informações iniciais.
*
*   Parâmetros:
*      NENHUM
*
*   Retorno:
*      NENHUM
*/
void QuantumDistinctness::initialStep() {
	N = elements.size();

	float exponent = (k) / (k + 1.0);
	r = (int) pow(N, exponent);

	quantumFile.open(quantumFileName, ios::out);
	quantumFile.setf(ios::fixed, ios::floatfield);
	quantumFile.precision(2);
	
	cout.precision(10);
	cout.setf(ios::fixed, ios::floatfield);

	time = clock();

	quantumFile << "Elements: [";
	vector<int>::iterator current = elements.begin(),
					          end = elements.end();
	end--;
	for (; current != end; current++)
		quantumFile << (*current) << ", ";
	quantumFile << (*end) << "]\n";

	quantumFile << "N: " << N << "\n";

	quantumFile << "R: " << r << "\n";

	quantumFile << "K: " << k << "\n";

	quantumFile << "M: " << M << "\n";

	quantumFile << "\n\n";
}

/*

*/
void QuantumDistinctness::finalStep() {
	time = clock() - time;

	quantumFile.precision(5);
	quantumFile << "\n\nTime (secs): " << ((float)time)/CLOCKS_PER_SEC;

	quantumFile.close();
}

/**
*   Primeiro passo do Simulador
*   Primeiro passo do algoritmo 2.
*
*   Parâmetros:
*      NENHUM
*
*   Retorno:
*      NENHUM
*/
void QuantumDistinctness::firstStep() {
	root = (utils->combinatorial(N,r)) * (N - r);

	sub_sets_H();
	sub_sets_H_Line();

	quantumFile << "Step 1 (Algorithm 2: Single-solution algorithm)\n\n";
	display_file_without_x_H();
}

/*

*/
void QuantumDistinctness::secondStep() {
	quantumFile << "Step 2 (Algorithm 2: Single-solution algorithm)\n\n";
	display_file_with_x_H();
}

/*

*/
void QuantumDistinctness::thirdStep() {
	double base = N / r;
	double exponent = k / 2;
	int time1 = (int) pow(base, exponent);

	quantumFile << "Step 3 (Algorithm 2: Single-solution algorithm)\n";
	quantumFile << "t1 = " << time1 << " times\n\n";

	for (int i = 1; i <= time1; i++) {
		thirdStepA();
		quantumFile << "Step 3 - Time: " << i << " of " << time1 << "\n\n";
		quantumFile << "Step 3 - A\n\n";
		display_file_with_x_H();

		int time2 = (int) sqrt((double)r);
		quantumFile << "Step 3 - B\n";
		quantumFile << "t2 = " << time2 << " times\n\n";
		for (int j = 1; j <= time2; j++) {
			quantumFile << "Step 3 - B - Time: " << j << " of " << time2 << "\n\n";
			thirdStepB();
		}
	}
}

/*

*/
void QuantumDistinctness::fourthStep() {
	quantumFile << "Mostrando o resultado\n";
	quantumFile << "Step 4 (Algorithm 2: Single-solution algorithm)\n";
	display_file_with_x_H();

	measure();
	measure2();
}

/*

*/
void QuantumDistinctness::thirdStepA() {
	vector<State>::iterator current = statesDimensionH.begin(),
								end = statesDimensionH.end();
	for (; current != end; current++)
		(*current).search_distinctness_change_signal(k, elements);
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
	display_file_with_x_H();
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
			s = (*current).getS();
			s.insert((*yCurrent).first);
			vector<int> v(s.begin(), s.end());
			int posicao = utils->calculate_position(v, 0, N, r+1, 0);
			statesDimensionHLine[posicao].change_amplitude((*yCurrent).first, (*yCurrent).second);
		}
	}

	quantumFile << "Step 2 (Quantum Walk)\n\n";
	display_file_with_x_H_Line();
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
	display_file_with_x_H_Line();
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
	display_file_with_x_H();
}

/*

*/
void QuantumDistinctness::measure(){
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

void QuantumDistinctness::measure2() {
    srand(std::time(0));
    int random = rand() % 101;
	//int random = 109;
	cout << "\nRandom: " << random << endl;
    vector<State>::iterator current = statesDimensionH.begin(),
							    end = statesDimensionH.end();
    double cumulativeProbability = 0.0f;
	for (; current != end; current++){
		cout << "Probabilidade: " <<  cumulativeProbability;
		cumulativeProbability = (*current).measure(cumulativeProbability, random, root, quantumFile);

		if(cumulativeProbability > 0)
			cout << " " <<  cumulativeProbability << endl;
		else
			cout << " " << -cumulativeProbability << endl;
		//if(cumulativeProbability == -1.0f){
		if(cumulativeProbability < 0){	
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
			cumulativeProbability*=-1;
		}
	}
}
/*

*/
void QuantumDistinctness::display_file_without_x_H() {
	quantumFile << "|Phi> = (1 / sqrt(" << root << "))*\n[\n";
	vector<State>::iterator current = statesDimensionH.begin(),
							    end = statesDimensionH.end();
	for (; current != end; current++)
		(*current).display_file_without_x(quantumFile);

	quantumFile << "]\n\n\n";
}

/*

*/
void QuantumDistinctness::display_file_with_x_H() {
	quantumFile << "|Phi> = (1 / sqrt(" << root << "))*\n[\n";

	vector<State>::iterator current = statesDimensionH.begin(),
							    end = statesDimensionH.end();
	for (; current != end; current++)
		(*current).display_file_with_x(quantumFile, elements);

	quantumFile << "]\n\n\n";
}

/*

*/
void QuantumDistinctness::display_file_with_x_H_Line() {
	quantumFile << "|Phi> = (1 / sqrt(" << root << "))*\n[\n";

	vector<State>::iterator current = statesDimensionHLine.begin(),
							    end = statesDimensionHLine.end();
	for (; current != end; current++)
		(*current).display_file_with_x(quantumFile, elements);

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