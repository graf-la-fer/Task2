#include <iostream>
#include <locale.h>
#include <string>
#include <windows.h>
#include <fstream>
#include <limits>

//#define DEBUG

using namespace std;


int main()
{
	setlocale(LC_ALL, "Russian");

	

	fstream fs;

	fstream fs2;
	string path = "myFile.txt";
	string path2= "output.txt";


	cout << endl;

	fs.open(path, fstream::in | fstream::out);
	fs2.open(path2, ios::out | ios::trunc);
	fs2.close();


	if (!fs.is_open())
	{
		cout << "Ошибка открытия файла!" << endl;
	}
	else
	{
		cout << "-Файл открыт" << endl;
		cout << endl;
				

		size_t counter = 0;
		while (fs.ignore((numeric_limits<streamsize>::max)(), '\n')) // пропускаем и считаем строки
			counter++;

		////////////////////////////////////////////////////////////////////////////////////////////////////
		//Создаем массив для проверки уникальности имени
		string* allNames = new string[counter];
		for (size_t p = 0; p < counter; p++)
		{
			allNames[p] = "0";
		}
			

		fs.clear();//очищаем поток
		fs.seekg(0, ios_base::beg);//возвращаемся к началу файла
#ifdef DEBUG
		cout << counter << endl;
#endif
		////////////////////////////////////////////////////////////////////////////////////////////////////

		for (size_t i = 0; i < counter; i++)
		{
			if (i != 0) {
				for (size_t l = 0; l < i-1; l++)
				{
						string trash;
					getline(fs, trash);
				}
			}

			string name, name1, zapros_v_c = "", zapros_v_c1 = "", kol_ch, kol_ch1, dop_inf, dop_inf1;
			int k_zapros = 0, k_zapros1 = 0, k_kol_ch = 0, k_kol_ch1 = 0;

			fs >> name;

			bool t=true;
			for (size_t p = 0; p < counter; p++)
			{
				if (name == allNames[p]) { t = true;  fs.clear();
				fs.seekg(0, ios_base::beg); break; }
				else {
					t = false;
				}

			}
			if (t == false) {
				for (size_t p = 0; p < counter; p++)
				{
					if (allNames[p] == "0")
					{
						allNames[p] = name;
						break;
					}
				}
				


				fs >> zapros_v_c;
				fs >> kol_ch;
				fs >> dop_inf;

#ifdef DEBUG
				cout << "name=" << name << endl;

				cout << "zapros_v_c=" << zapros_v_c << endl;

				cout << "kol_ch=" << kol_ch << endl;

				cout << "dop_inf=" << dop_inf << endl;
#endif
				
				

				k_zapros = stoi(zapros_v_c);
				k_kol_ch = stoi(kol_ch);

#ifdef DEBUG
				cout << "k_zapros=" << k_zapros << endl;
				
				cout << "k_kol_ch=" << k_kol_ch << endl;
#endif

				for (size_t j = 0; j < counter - 1; j++)
				{
					fs >> name1;
					

					if (name == name1)
					{
						fs >> zapros_v_c1;
						fs >> kol_ch1;
						fs >> dop_inf1;

						k_zapros1 = stoi(zapros_v_c1);
						k_kol_ch1 = stoi(kol_ch1);

						k_zapros = k_zapros + k_zapros1;
						k_kol_ch = k_kol_ch + k_kol_ch1;
#ifdef DEBUG
						cout << "*******************************" << endl;

						cout << "name1=" << name1 << endl;
						
						cout << "zapros_v_c1=" << zapros_v_c1 << endl;
						
						cout << "kol_ch1=" << kol_ch1 << endl;
						
						cout << "dop_inf1=" << dop_inf1 << endl;

						
						cout << "k_zapros1=" << k_zapros1 << endl;

						
						cout << "k_kol_ch1=" << k_kol_ch1 << endl;

						
						cout << "*******************************" << endl;
#endif
					}
					else {
						getline(fs, name1);
					}


				}
#ifdef DEBUG
				cout << "k_zapros=" << k_zapros << endl;
				cout << "k_kol_ch=" << k_kol_ch << endl;
#endif

				fs2.open(path2, fstream::app);
				fs2 << name << " " << k_zapros << " " << k_kol_ch << " " << k_zapros * k_kol_ch << " " << dop_inf << endl;
				fs2.close();

				fs.clear();
				fs.seekg(0, ios_base::beg);
				
			}
				
				
						
		}
	
				
		fs.close();
		
		delete[] allNames;
		cout << "\n-Программа выполнена" << endl;
	}


	system("pause");
	return 0;
}