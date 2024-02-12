#include <iostream>
#include <fstream>
#include <string>
#include "Trie.h"

using namespace std;

int main()
{
	fstream file;
	TrieNode* Dictionary = getNewNode();
	char sup[60000];
	file.open("Dictionary.txt");
	int i = 0;

	// Считываем слова из файла-словаря и заполняем префиксное дерево
	while (!file.eof())
	{
		file.getline(sup, 60000);
		insert(Dictionary, string(sup));
	}
	file.close();
	string input = "", line = "", text = "", input2 ="";
	bool check = true;
	int num = 0;
	while (input != "q")
	{
		system("cls");
		// Если алгоритм 3 раза подряд выдает неверное автодополнение,
		// просим пользователя ввести слово вручную
		// и добавляем его в дерево
		if (num > 2)
		{
			cout << "Enter your word: ";
			cin >> input;
			text += " " + input;
			check = true;
			num = 0;
			insert(Dictionary, input);
			system("cls");
		}
		// Постоянный вывод напоминания, какое слово нужно ввести для выхода
		cout << "q - close" << endl;							
		cout << "CLEAR - clear the text " << endl;
		cout << "--------------------------------"
			<< "-------------------------------" << endl;
		// Вывод пользовательской строчки на экран консоли
		cout << "Your text:" << text;
		// если нужны новые данные от пользователя, то вводим
		if (check)
			cin >> input;
		// Очистка пользовательской строчки и получение нового слова
		if (input == "CLEAR")
		{
			system("cls");
			cout << "q - close" << endl;			
			cout << "CLEAR - clear the text " << endl;
			cout << "--------------------------------"
				<< "-------------------------------" << endl;
			text = "";
			cout << "Your text:" << text;
			cin >> input;
		}
		// Если введеное слово не является законченным
		if (!search(Dictionary, input))
		{
			// Проверка на условие выхода из программы
			if (input != "q")
			{
				// Получаем одно из возможных продолжений слова
				// или пустую строчку, если продолжения в дереве нет
				line = searchSequence(Dictionary, input);
				if (line != "")
				{
					if (!check)
						cout << endl;
					// Спрашиваем, подходит ли предложенное слово пользователю
					cout << "Do you want to write \"" << line << "\"? (enter Yes/No)" << endl;
					cin >> input2;
					// Защита от невверных входных данных
					while (input2 != "Yes" && input2 != "No")
					{
						cout << "Wrong input data. Please, enter Yes or No." << endl;
						cin >> input2;
					}
					// Либо дополняем введенное слово и устанвливаем check = true
					// Либо check = false и пытаемся найти другое слово
					if (input2 == "Yes")
					{
						system("cls");
						text += " " + line;
						cout << "Your text: " << text;
						check = true;
						num = 0;
					}
					else
					{
						check = false;
						num++;
					}
				}
				// Если такого префикса  в дереве нет
				// предлагаем либо стереть слово, либо оставить
				else
				{
					cout << "Unknown word. Clear this word? (Yes/No)" << endl;
					cin >> input2;
					while (input2 != "Yes" && input2 != "No")
					{
						cout << "Wrong input data. Please, enter Yes or No." << endl;
						cin >> input2;
					}
					if (input2 == "No")
					{
						system("cls");
						text += " " + input;
					}
				}
			}
			// реализация выхода из программы
			else
			{
				cout << "Are you sure you want close to quit?(Yes/No)" << endl;
				cin >> input2;
				while (input2 != "Yes" && input2 != "No")
				{
					cout << "Wrong input data. Please, enter Yes or No." << endl;
					cin >> input2;
				}
				if (input2 == "Yes")
					return 0;
				else
					input = "";
			}
		}
		// если введенное слово является законченным
		else
			text += " " + input;
	}
	return 0;
}