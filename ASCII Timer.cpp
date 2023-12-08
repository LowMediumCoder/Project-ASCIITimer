// Project ASCII Timer 

#define _USE_MATH_DEFINES
#include <iostream>
#include <string>
#include <time.h>
#include <chrono>
#include <windows.h>
#include <math.h>
char output[11][11]{}; //11x11 array of characters

static int AskDuration()
{
	int duration;
	std::cout << "Saisis la duree du chrono (en secondes):" << std::endl;
	std::cin >> duration;
	return duration;
}

static float GetTime()
{
	float timeInSeconds = clock() / (float)CLOCKS_PER_SEC;
	return timeInSeconds;
}

struct Chrono {
	int duration = 0;
	float elapsedTime = 0.0;
	bool isFinished = false;
};

void static UpdateChrono(Chrono chrono, float deltaTime)
{
	if (chrono.isFinished) {
		chrono.isFinished = false;
		return;
	}
	else {
		chrono.elapsedTime += deltaTime;
		if (chrono.elapsedTime >= chrono.duration) {
			chrono.isFinished = true;
		}

	}
}

static void InitializeOutput() {
	for (int i = 0; i < 11; i++) {
		for (int j = 0; j < 11; j++) {
			output[i][j] = '-';
		}
	}

	output[5][5] = 'X';
	for (int i = 1; i < 5; i++) {
		output[5][i] = '|';
	}
}

static void DisplayOutput()
{
	int column;
	int line = 5;
	std::string a;
	for (line = 0; line < 11; line++) {
		for (column = 0; column < 11; column++) {
			a += output[column][line];
		}
		a += "\n";
	}

	std::cout << a << std::endl;

}

static void ResetDisplay() {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos = { 0, 0 };
	SetConsoleCursorPosition(hConsole, pos);
	InitializeOutput();

}


/*
Objectifs: Ecrire '0' dans une case du tableau en fonction
de l'avancement de la seconde actuelle
Parametres: reference vers le chrono
Valeur de retour: aucune

la charactere '0' marquera l'ecoulement d'une seconde. il parcourra la
largeur du tableau en 1 seconde puis reviendra au debut.

la position du '0' dans la sera {posX, 0}:
int posX = ((int) (chrono.elapsedTime * 11)) % 11;
*/
static void WriteSecond(Chrono& c) {
	int posX = ((int)(c.elapsedTime * 11)) % 11;
	output[posX][0] = '0';
}


static void WriteTimeLeft(Chrono& chrono) {
	int posX = (int)((cos(chrono.elapsedTime * 2 * M_PI / chrono.duration - M_PI / 2) * 3) + 5.5f);
	int posY = (int)((sin(chrono.elapsedTime * 2 * M_PI / chrono.duration - M_PI / 2) * 3) + 5.5f);
	output[posX][posY] = '0';
}


//Main()
int main()
{	
	/*int duration = AskDuration();
	//ecrire une boucle "while" s'arretant au bout de 5s
	//Pour realiser cet algorithme:
	//Declarer une variable "currentTime" et l'initialiser avec la fonction GetTime()
	//Implementer une boucle "while" qui s'arrete lorsque "GetTime() - currentTime" est superieur a 5

	// En fin de boucle, afficher un message de fin:
	// "Fin du chrono !" */

	Chrono chrono;
	chrono.duration = AskDuration();

	system("cls");
	float currentTime = GetTime();

	std::cout << GetTime() << std::endl;
	while (chrono.elapsedTime < chrono.duration) {
		ResetDisplay();
		WriteTimeLeft(chrono);
		WriteSecond(chrono);
		DisplayOutput();
		std::cout << chrono.elapsedTime << std::endl;
		float newTime = GetTime();
		float deltaTime = newTime - currentTime;
		chrono.elapsedTime += deltaTime;
		currentTime = newTime;
	}
	
	std::cout << "Fin du chrono !" << std::endl; //Fin du chrono !
}