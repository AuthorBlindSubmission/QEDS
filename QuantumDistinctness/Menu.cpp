/*
 * Menu.cpp
 *
 *  Created on: 04/02/2014
 *      Author: Alexandre & Matheus
 */

#include "Library.h"

vector<int> aleatorio();
vector<int> usuario();
vector<int> menu(char opcao);

int main() {
	char opcao = 'a';
	printf("Bem-Vindo ao Simulador de Distinção de Elementos\n");
	printf("Selecione sua opcao\n");
	printf("1 - Selecionar Valores Aleatórios\n");
	printf("2 - Definir Valores\n");
	printf("Opcao: ");
	cin >> opcao;

	vector<int> vector = menu(opcao);

	/*do{
		switch(opcao){
			case '1':
				vector = aleatorio();
				break;
			case '2':
				vector = usuario();
				break;
			default:
				printf("Opcao Invalida");
		}

	}while(opcao!='1' && opcao!='2');
	vector = usuario();*/
	
	QuantumDistinctness quantum;
	quantum.init(vector, (int) vector.size());


	//vector<int> vetor;

	//int n, valor;
	//printf("Diga a quantidade de numeros: ");
	//scanf_s("%d", &n);
	//for (int i = 0; i < n; i++) {
	//	printf("Diga o numero %d: ", i + 1); scanf_s("%d", &valor); vetor.push_back(valor);
	//	vetor.push_back(i);
	//}

	//vetor.push_back(1);
	//vetor.push_back(2);
	//vetor.push_back(1);
	//vetor.push_back(4);
	//vetor.push_back(5);
	//vetor.push_back(6);
	//vetor.push_back(7);
	//vetor.push_back(8);
	//vetor.push_back(9);
	//vetor.push_back(10);
	//vetor.push_back(11);
	//vetor.push_back(12);
	//vetor.push_back(13);
	//vetor.push_back(14);
	//vetor.push_back(15);
	//vetor.push_back(16);
	//vetor.push_back(17);
	//vetor.push_back(18);
	//vetor.push_back(19);
	//vetor.push_back(20);

	//QuantumDistinctness quantum;
	//quantum.init(vetor);

	/*set<int> set1;
	set1.insert(1);
	set1.insert(2);
	set<int> set2;
	set2.insert(1);
	set2.insert(2);

	Utils *utils = new Utils;
	set1 = utils->set_intersection(set1, set2);

	set<int>::iterator current = set1.begin(),
						   end = set1.end();

	for (; current != end; current++) {
		cout << (*current) << " ";
	}

	delete utils;*/

	system("pause");

	return 0;
}

vector<int> menu(char opcao){
	switch(opcao){
		case '1':
			return aleatorio();
		case '2':
			return usuario();
		default:
			printf("Opcao Invalida");
			printf("Opcao: ");
			cin >> opcao;
			return menu(opcao);
	}
};

vector<int> aleatorio(){
	int n, valor;
	vector<int> vector;
	printf("Diga a quantidade de numeros: ");
	scanf_s("%d", &n);
	for (int i = 0; i < n; i++) {
		printf("Diga o numero %d: ", i + 1);
		scanf_s("%d", &valor);
		vector.push_back(valor);
	}
	return vector;
}

vector<int> usuario(){
	int n, valor;
	vector<int> vector;
	printf("Diga a quantidade de numeros: ");
	scanf_s("%d", &n);
	for (int i = 0; i < n; i++) {
		printf("Diga o numero %d: ", i + 1);
		scanf_s("%d", &valor);
		vector.push_back(valor);
	}
	return vector;
}