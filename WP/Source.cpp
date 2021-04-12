#include <iostream>

using namespace std;

int main() {
	int tab[] = { 1, 3, 5, 7, 9, 11, 13, 15 };
	int wanted = 2;
	int startTab = 0;
	int endTab = 8;
	bool done = false;
	int search = (startTab + endTab) / 2;
	int iteration = 1;
	int tmp = 0;

	do {
		if (wanted == tab[search]) {
			cout << "Znalezione!!!\nMiejsce w tablicy: " << search << endl;
			done = true;
			break;
		}
		else if (wanted < tab[search]) {
			endTab = search;
			search = (startTab + endTab)/2;
		}
		else if (wanted > tab[search]) {
			 startTab = search;
			 search = (startTab + endTab)/2;
		}
		
		if (endTab == startTab)
		{
			tmp++;
			if (tmp > 1) {
				cout << "Nie znaleziono" << endl;
				break;
			}
		}

		iteration++;
	} while (!done);

	cout << "Ilosc iteracji: " << iteration << endl;


	system("PAUSE");
	return 0;
}