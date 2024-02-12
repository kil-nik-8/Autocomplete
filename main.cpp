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

	// ��������� ����� �� �����-������� � ��������� ���������� ������
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
		// ���� �������� 3 ���� ������ ������ �������� ��������������,
		// ������ ������������ ������ ����� �������
		// � ��������� ��� � ������
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
		// ���������� ����� �����������, ����� ����� ����� ������ ��� ������
		cout << "q - close" << endl;							
		cout << "CLEAR - clear the text " << endl;
		cout << "--------------------------------"
			<< "-------------------------------" << endl;
		// ����� ���������������� ������� �� ����� �������
		cout << "Your text:" << text;
		// ���� ����� ����� ������ �� ������������, �� ������
		if (check)
			cin >> input;
		// ������� ���������������� ������� � ��������� ������ �����
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
		// ���� �������� ����� �� �������� �����������
		if (!search(Dictionary, input))
		{
			// �������� �� ������� ������ �� ���������
			if (input != "q")
			{
				// �������� ���� �� ��������� ����������� �����
				// ��� ������ �������, ���� ����������� � ������ ���
				line = searchSequence(Dictionary, input);
				if (line != "")
				{
					if (!check)
						cout << endl;
					// ����������, �������� �� ������������ ����� ������������
					cout << "Do you want to write \"" << line << "\"? (enter Yes/No)" << endl;
					cin >> input2;
					// ������ �� ��������� ������� ������
					while (input2 != "Yes" && input2 != "No")
					{
						cout << "Wrong input data. Please, enter Yes or No." << endl;
						cin >> input2;
					}
					// ���� ��������� ��������� ����� � ������������ check = true
					// ���� check = false � �������� ����� ������ �����
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
				// ���� ������ ��������  � ������ ���
				// ���������� ���� ������� �����, ���� ��������
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
			// ���������� ������ �� ���������
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
		// ���� ��������� ����� �������� �����������
		else
			text += " " + input;
	}
	return 0;
}