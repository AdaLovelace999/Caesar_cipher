#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

const int ALPH_SIZE = 26; //Размер латинского алфавита

char low_case[] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l',
 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z' }; //Массив строчных букв, которые шифруются также строчными

char high_case[] = { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L',
 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z' }; //Массив заглавных букв, которые шифруются также заглавными

void initFreq(vector<pair<char, double> > &F) { /*Инициализируем массив пар буква-частота (вектор, составленный из структур pair)*/

	F.push_back(make_pair('a', 8.17)); //метод push_back - добавление элемента в конец вектора, make_pair - создать пару
	F.push_back(make_pair('b', 1.49));
	F.push_back(make_pair('c', 2.78));
	F.push_back(make_pair('d', 4.25));
	F.push_back(make_pair('e', 12.70));
	F.push_back(make_pair('f', 2.23));
	F.push_back(make_pair('g', 2.02));
	F.push_back(make_pair('h', 6.09));
	F.push_back(make_pair('i', 6.97));
	F.push_back(make_pair('j', 0.15));
	F.push_back(make_pair('k', 0.77));
	F.push_back(make_pair('l', 4.03));
	F.push_back(make_pair('m', 2.41));
	F.push_back(make_pair('n', 6.75));
	F.push_back(make_pair('o', 7.51));
	F.push_back(make_pair('p', 1.93));
	F.push_back(make_pair('q', 0.10));
	F.push_back(make_pair('r', 5.99));
	F.push_back(make_pair('s', 6.33));
	F.push_back(make_pair('t', 9.06));
	F.push_back(make_pair('u', 2.76));
	F.push_back(make_pair('v', 0.98));
	F.push_back(make_pair('w', 2.36));
	F.push_back(make_pair('x', 0.15));
	F.push_back(make_pair('y', 1.97));
	F.push_back(make_pair('z', 0.07));

	return;
}

bool checkChar(char c) //Пробелы, цифры и прочие символы пропускаются. Проверка на такой символ осуществляется с помощью функции checkChar()
{
	if (c == ' ' || c == '.' || c == ',' ||
		c == '!' || c == '?' || c == ':' ||
		c == ';' || c == '0' || c == '1' || c == '2' || c == '3' || c == '4' || c == '5' || c == '6' || c == '7' || c == '8' || c == '9')
	{
		return true;
	}
	else
		return false;
}

/*
* Функция шифрования
* Параметры: string message - исходное сообщение, int key - ключ (значение сдвига)
*/
void encryptCaesar(string message, int key) //принимает сообщение которое надо зашифровать и ключ
{
	string cipher = ""; //строка, в которую будут записываться зашифрованные символы исходного сообщения

	for (int i = 0; i < message.size(); i++) //проходимся в цикле по каждому символу введенной строки
	{
		if (checkChar(message[i])) //проверяем является ли текущий символ пробелом, цифрой, знаком препинания и т. д.
		{
			cipher += message[i]; //если да, записываем его в строку без изменений
		}
		else
		{
			for (int j = 0; j < ALPH_SIZE; j++) //ищем текущий символ в алфавите
			{

				if (message[i] == low_case[j]) //если текущий символ является строчной буквой
				{
					cipher += (message[i] - 'a' + key) % 26 + 'a'; //шифруем как строчный символ и записываем в строку {(код текущей буквы - код буквы 'а' + ключ) ищем остаток от деления на 26 и прибавляем код буквы 'а'}
				}
				else if (message[i] == high_case[j]) //если текущий символ является заглавной буквой
				{
					cipher += (message[i] - 'A' + key) % 26 + 'A'; //шифруем как заглавный символ и записываем в строку
				}
			}
		}
	}

	cout << cipher; //выводим зашифрованное сообщение
	return;
}

/*
* Функция дешифрования
* Параметры: string message - исходное сообщение, int key - ключ (значение сдвига)
*/
void decryptCaesar(string message, int key)
{
	string de_cipher = "";
	for (int i = 0; i < message.size(); i++)
	{
		if (checkChar(message[i]))
		{
			de_cipher += message[i];
		}
		else
		{
			for (int j = 0; j < ALPH_SIZE; j++)
			{

				if (message[i] == low_case[j])
				{
					de_cipher += (message[i] - 'a' - key + 26) % 26 + 'a';
				}
				else if (message[i] == high_case[j])
				{
					de_cipher += (message[i] - 'A' - key + 26) % 26 + 'A';
				}
			}
		}
	}

	cout << de_cipher;
	return;
}

/*
* Функция взлома
*/
void hackCaesar()
{
	vector<pair<char, double> > standFreq;
	initFreq(standFreq);

	vector<pair<char, double> > currentFreq(ALPH_SIZE);
	char symb = 'a';
	for (unsigned int i = 0; i < ALPH_SIZE; i++)
	{
		currentFreq[i].first = symb; //первое значение пары pair<char, double>
		currentFreq[i].second = 0.0; //второе значение пары pair<char, double>

		symb++;
	}

	//Считываем зашифрованный текст из файла

	string path = "Saint_Petersburg_cipher_key1.txt"; //London_cipher_key30.txt, Saint_Petersburg_cipher_key1.txt, New_Zeland_cipher_key2.txt, message_cipher_key1.txt
	ifstream fin;
	fin.open(path);

	vector<string> code; //сюда считываем зашифрованный текст

	if (!fin.is_open())
	{
		cout << "Ошибка открытия файла" << endl;
	}
	else
	{
		cout << "Файл открыт:" << endl;
		string str;
		while (!fin.eof())
		{
			getline(fin, str);
			code.push_back(str);
		}
	}

	fin.close();

	cout << "Зашифрованный текст: \n" << code[0] << endl;

	//Посчитать среднюю частоту появления каждого символа 

	//Всего символов
	int symbCount = 0;
	for (unsigned int i = 0; i < code.size(); i++) { //цикл по всему тексту
		for (unsigned int j = 0; j < code[i].length(); j++) { //цикл по символам
			if (checkChar(code[i][j])) { //если текущий символ не пробел, не .,:;!?..., и не число
				continue;
			}
			else {
				symbCount++; //увеличиваем счетчик количества символов
				for (unsigned int k = 0; k < ALPH_SIZE; k++) { //цикл который сравнивает символы зашифрованного текста с символами запмсанными в currentFreq и подсчитывает сколько раз данный символ встретился в тексте
					if (code[i][j] == currentFreq[k].first) { //сравниваем текущий символ с полем "first" k-й пары currentFreq
						//Одновременно считаем количество символов в тексте
						currentFreq[k].second += 1.0; //каждый раз когда встречаем такой символ увеличиваем на 1 поле "second" k-й пары currentFreq
						break;
					}
				}
			}
		}
	}
	//Текущая частота каждого
	for (unsigned int i = 0; i < ALPH_SIZE; i++) {
		currentFreq[i].second = (currentFreq[i].second / symbCount) * 100.0; //число сколько раз какой-то определенный символ встретился в тексте делим на общее количество символов в тексте и умножаем на 100 и получаем частоту каждого символа в данном тексте
	}

	//Сравнить со стандартной частотой
	double deff = 0.25; //Допустимое отклонение (отвечает за интервал, в который должна попасть частота символа)
	vector<int> slides; 
	for (unsigned int i = 0; i < ALPH_SIZE; i++) { //для каждого символа в алфавите
		for (unsigned int j = 0; j < ALPH_SIZE; j++) {
			if (currentFreq[i].second >= (standFreq[j].second - deff) && //если текущая частота попадает в промежуток стандартная частота +- допустимое отклонение
				currentFreq[i].second <= (standFreq[j].second + deff)) {
				//Запоминаем возможное смещение
				slides.push_back(currentFreq[i].first - standFreq[j].first); //текущ. частота - стандарт. частота данного символа
			}
		}
	}

	//Выбираем смещение (в vector<int> slides мы собрали все возможные смещения и теперь берем в качестве результирующего самое часто встречающееся)
	sort(slides.begin(), slides.end()); //сортируем смещения по возрастанию
	int count = 0;
	int maxCount = count;
	int slide = 0;
	for (unsigned int i = 1; i < slides.size(); i++) { 
		if (slides[i - 1] == slides[i]) {
			count++;
		}
		else {
			if (count > maxCount) {
				maxCount = count;
				slide = slides[i - 1];
			}
			count = 0;
		}
	}

	cout << "\nСмещение = " << slide << endl;

	//Дешифровать с использованием найденного смещения

	cout << "\nРасшифрованный текст: " << endl;
	decryptCaesar(code[0], slide);
}

// Ввод из консоли с проверкой
int consoleInt()
{
	int result = 0;
	string strFromConsole = "";
	while (true)
	{
		getline(cin, strFromConsole);
		try
		{
			result = stoi(strFromConsole);
			break;
		}
		catch (const exception& ex)
		{
			//cout << "Error: " << ex.what() << endl;
			//cout << "Enter a value again: " << endl;
		}
	}
	return result;
}

int main()
{
	setlocale(LC_ALL, "ru");
	cout << "Данная программа осуществляет шифровку, дешифровку текста шифром Цезаря, а также взлом шифра методом частотного анализа.\nДля шифровки и дешифровки вы можете вводить текст в консоли или из файла. Выберите что вы хотите сделать: " << endl;
	while (true)
	{
		cout << "\n\nЗашифровать - 1, Расшифровать - 2, Взломать - 3, Выйти - 4: " << endl;
		int action = 0;
		cin >> action;

		if (action == 1)
		{
			cout << "Для ввода в консоли нажмите 1, для ввода из файла нажмите 2: ";
			int inputChoose = 0;

			while (true)
			{
				inputChoose = consoleInt();
				if (inputChoose == 1 || inputChoose == 2)
				{
					break;
				}
				else
				{
					cout << "Введите 1 или 2!" << endl;
				}
			}
			//Чтение из консоли
			if (inputChoose == 1)
			{
				cout << "Введите сообщение:\n";
				string message;
				getline(cin, message); //Чтобы считать всю строку применяется метод getline(): он принимает два объекта - std::cin и переменную, в которую надо считать строку.

				cout << "Введите ключ:\n";
				int key;
				cin >> key;

				cout << "\n\nЗашифрованное сообщение: " << endl;
				encryptCaesar(message, key);

			}
			else
				//Чтение из файла
			{
				cout << "Введите ключ:\n";
				int key;
				cin >> key;

				string path = "London.txt"; //Saint_Petersburg.txt, New_Zeland.txt, message.txt
				ifstream fin;
				fin.open(path);
				if (!fin.is_open())
				{
					cout << "Ошибка открытия файла" << endl;
				}
				else
				{
					cout << "Файл открыт:" << endl;
					string str;
					cout << "\n\nЗашифрованное сообщение: " << endl;
					while (!fin.eof())
					{
						getline(fin, str);
						encryptCaesar(str, key);
					}
				}
				fin.close();
			}
		}
		else if (action == 2)
		{
			cout << "Для ввода в консоли нажмите 1, для ввода из файла нажмите 2: ";
			int inputChoose = 0;

			while (true)
			{
				inputChoose = consoleInt();
				if (inputChoose == 1 || inputChoose == 2)
				{
					break;
				}
				else
				{
					cout << "Введите 1 или 2! " << endl;
				}
			}
			//Чтение из консоли
			if (inputChoose == 1)
			{
				cout << "Введите зашифрованное сообщение:\n";
				string message;
				getline(cin, message);

				cout << "Введите ключ:\n";
				int key;
				cin >> key;

				cout << "\n\nРасшифрованное сообщение: " << endl;
				decryptCaesar(message, key);
			}
			else
				//Чтение из файла
			{
				cout << "Введите ключ:\n";
				int key;
				cin >> key;

				string path = "Saint_Petersburg_cipher_key1.txt"; // New_Zeland_cipher_key2.txt, London_cipher_key30.txt, message_cipher_key1.txt
				ifstream fin;
				fin.open(path);
				if (!fin.is_open())
				{
					cout << "Ошибка открытия файла" << endl;
				}
				else
				{
					cout << "Файл открыт:" << endl;
					string str;
					cout << "\n\nРасшифрованное сообщение: " << endl;
					while (!fin.eof())
					{
						getline(fin, str);
						decryptCaesar(str, key);
					}
				}
				fin.close();
			}
		}
		else if (action == 3)
		{
			hackCaesar();
		}
		else if (action == 4)
		{
			break;
		}
		else
		{
			cout << "Неверный ввод! Введите 1, 2, 3 или 4! " << endl;
		}
	}
}
