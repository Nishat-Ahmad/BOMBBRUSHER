#include <iostream>
#include <SFML\Graphics.hpp>
#include <fstream>
#include <iostream>
#include <algorithm>
using namespace std;
using namespace sf;

class Score {
	private:
		long long startTime;
		int scores[10];
		string names[10];
		int difficulty;
	public:
		Score(int difficulty = 10) {
			this->difficulty = difficulty;
			ifstream infile("easy.txt", ios::in);
			startTime = time(0);
			switch(difficulty) {
			case 10:
				infile.open("easy.txt");
				break;
			case 15:
				infile.open("medium.txt");
				break;
			case 20:
				infile.open("hard.txt");
				break;
			default:
				infile.open("easy.txt");
			}
			if (infile.is_open()) {
				int num; string name;
				int i = 0;
				while (infile >> num) {
					scores[i] = num;
					infile >> name;
					names[i] = name;
					i++;
				}
				infile.close();
			}
			else {
				std::cout << "Failed to open file for reading." << std::endl;
			}
		}
		void insertionSort() {
			for (int i = 1; i < 10; ++i) {
				int tempscore = scores[i];
				string tempname = names[i];
				int j = i - 1;

				while (j >= 0 && scores[j] > tempscore) {
					scores[j + 1] = scores[j];
					names[j + 1] = names[j];
					j = j - 1;
				}
				scores[j + 1] = tempscore;
				names[j + 1] = tempname;
			}
		}
		int getTime() {
			return time(0) - startTime;
		}
		string* getNames() {
			return names;
		}
		int* getScores() {
			return scores;
		}
		void gameEnd() {
			ofstream outfile("easy.txt");
			switch (difficulty) {
			case 10:
				outfile.open("easy.txt");
				break;
			case 15:
				outfile.open("medium.txt");
				break;
			case 20:
				outfile.open("hard.txt");
				break;
			default:
				outfile.open("easy.txt");
			}
			int score = getTime();
			if (score > scores[0]) {
				scores[0] = score;
			}
			insertionSort();
			for (int i = 0; i < 10; i++) {
				outfile << names[i] << endl;
				outfile << scores[i] << endl;
			}
			outfile.close();
		}
};
