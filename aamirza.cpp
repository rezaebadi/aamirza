

/*reza ebadi ozan
sh.daneshjoie:4002023025 */


#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <ctime>
#include <stdlib.h>
#include <iomanip>
#include <algorithm>
using namespace std;

struct word {

	char *str;
	bool state;
};
struct Marahel {
	char *Horof;
	int NUMAsli;
	int NumFArei;
	word *Kalamt;
	int Count;
};

struct user {
	char *username;
	int password;
	int YourLevel;
	int Coins;
	int NumerOfExt;
	int Chance;
};
user *read_users(int *empty_count);//tamame user hara khande va zakhire mikonad
Marahel Ebtedaei(string a);//bakhsh bakhsh kardan file
void MainMenu(int);
int Random(string str);// dar challange khat aval ra az level gerefte va yek adad be sorat random midahad
void Challange(int a);
word *split(string a, int *count2);//joda kardan kalamt level ha
void ShowLetters(string a);//namayesh
user *Signup(user *users_array, int *count);
user *Login(user *users_array, int *count);
void Rank(user *users_array, int num_of_users);
void Play(int a, user *login_user, int num_of_users, user * users_array);
int users = 0;
char *stoc(string input);//tabdil string be char
void InternalMenu(int a, user *login_user, int num_of_users, user * users_array);
void WheelofLuck(user *login_user, int num_of_users, user * users_array);
void Edit(user *login_user, int num_of_users, user * users_array);
int Random(string str) {

	int number_of_line;
	int fasl = str[0] - 48;
	number_of_line = fasl - 1;
	for (int i = 2; i < (fasl * 2) - 1; i++) {
		if (i % 2 == 0) {
			int step = str[i] - 48;
			number_of_line += step;
		}
	}
	srand(time(0));
	int ans = (rand() % number_of_line - 1);
	return ans;

};

user *read_users(int *empty_count) {
	fstream users_file("user.txt", ios::app | ios::in);
	string read;
	string Username = "";
	int Password;
	int level = 1;
	int coins = 0;
	int numer_of_ext = 0;
	int chance = 0;
	int count = 0;
	getline(users_file, read);
	user *users_array = (user *)malloc(1 * sizeof(user));
	while (users_file >> Username >> Password >> level >> coins >> numer_of_ext >> chance) {
		users_array[count].username = stoc(Username);
		users_array[count].password = Password;
		users_array[count].YourLevel = level;
		users_array[count].Coins = coins;
		users_array[count].NumerOfExt = numer_of_ext;
		users_array[count].Chance = chance;
		users_array = (user *)realloc(users_array, (count + 2)*sizeof(user));
		count++;
	}
	*empty_count = count;
	users_file.close();
	return users_array;
}

user *Signup(user *users_array, int *count) {
	cout << "#############################" << endl;
	string Username;
	int Password;
	int YourLevel = 1;
	int Coins = 0;
	int NumerOfExt = 0;
	int Chance = 0;
	char wrong = 0;
	string temp;
	while (1) {
		bool check = true;
		if (wrong == 1) {
			cout << "for return to main menu enter *" << endl;
			cout << "please enter another username" << endl;
		}
		else {
			cout << "for return to main menu enter *" << endl;
			cout << "please enter your username" << endl;
		}
		cin >> Username;
		if (Username == "*") return users_array;
		cout << "please enter your password" << endl;
		cin >> Password;
		int num_of_users = *count;
		for (int i = 0; i < num_of_users; i++) {
			if (users_array[i].username == Username) {
				check = false;
				break;
			}
		}
		if (check) {
			fstream users_file("user.txt", ios::app);
			users_file << "\n" << left << setw(12) << Username << fixed << left << setw(12) << Password << fixed << left << setw(8) << YourLevel << fixed << left << setw(8) << Coins << fixed << setw(4) << NumerOfExt << fixed << Chance;
			users_file.close();
			users_array = (user *)realloc(users_array, (*count + 1)*sizeof(user));
			users_array[*count].username = stoc(Username);
			users_array[*count].password = Password;
			users_array[*count].YourLevel = YourLevel;
			users_array[*count].Coins = Coins;
			users_array[*count].Chance = Chance;
			users_array[*count].NumerOfExt = NumerOfExt;
			cout << "Registration completed successfully" << endl;
			break;
		}
		else { wrong = 1; }
	}
	cout << "#############################" << endl;
	*count = *count + 1;
	return users_array;
};

user *Login(user *users_array, int *count) {
	string Username;
	int Password;
	while (1) {
		cout << "please enter your username \n";
		cin >> Username;
		cout << "please enter your password\n";
		cin >> Password;
		for (int i = 0; i < *count; i++) {
			if (users_array[i].username == Username && users_array[i].password == Password) {
				cout << "done" << endl;
				return &users_array[i];
			}
		}
		cout << "username or password is wrong" << endl;
	}

}

int max_level() {
	int e, b, c, d;
	fstream users_file("levels.txt", ios::in);
	users_file >> e >> b >> c >> d;
	int max = b + c + d;
	users_file.close();
	return max;
}

void Rank(user *users_array, int num_of_users) {
	int rank = 1;
	int max = max_level();
	for (int level = max; level > 0; level--) {
		for (int i = 0; i < num_of_users; i++) {
			if (users_array[i].YourLevel == level) {
				cout <<rank <<"-" <<users_array[i].username << endl;
				rank++;
			}
		}
	}
}
char *stoc(string input) {
	char *output = (char *)malloc(2 * sizeof(char));
	int i = 0;
	while (input[i] != '\0') {
		output[i] = input[i];
		output[i + 1] = '\0';
		output = (char *)realloc(output, (i + 3)*sizeof(char));
		i++;
	}
	return output;
}
void Challange(int a) {
	int counthads = 0;
	string hads;
	int turn = 1;
	struct details {
		string name;
		int score;
	}player1, player2;
	player1.score = 0;
	player2.score = 0;
	cout << "Welcome to CHALLANGE " << endl;
	cout << "please enter the name of first player " << endl;
	cin >> player1.name;
	cout << "please enter the name of second player " << endl;
	cin >> player2.name;
	ifstream levels("levels.txt", ios::in);
	string line;
	string RandomLevel;
	getline(levels, line);
	string temp3 = line;
	int RandomStep = Random(temp3);
	getline(levels, line);

	for (int i = 0; i <= RandomStep; i++) {
		getline(levels, line);
		RandomLevel = line;
	}

	if (RandomLevel == "") {
		getline(levels, line);
		RandomLevel = line;
	}
	levels.close();
	int count = 0;
	word *words = split(RandomLevel, &count);

	while (1) {
		hads = "";
		cout << "player1:" << "  " << player1.name << "\t" << "score:" << player1.score << "\t" << "player2:" << "  " << player2.name << "\t" << "score:" << player2.score << endl;
		if (turn == 1)cout << "turn: " << player1.name;
		if (turn == -1)cout << "turn: " << player2.name;
		cout << endl;
		ShowLetters(RandomLevel);
		cout << endl;
		cin >> hads;
		if (hads == "*" && turn == 1)
		{
			cout << player2.name << "win the game";
		}
		for (int i = 0; i<count; ++i) {
			if (words[i].str == hads && words[i].state == 0) {
				if (turn == 1) { player1.score += hads.length(); ++counthads; break; }

				if (turn == -1) { player2.score += hads.length(); ++counthads; break; }
			}
		}
		turn = turn * -1;

		if (counthads == count) {
			break;
		}
	}
	if (player1.score>player2.score) { cout << player1.name << "  win the game"; MainMenu(0); }
	if (player1.score<player2.score) { cout << player2.name << "  win the game"; MainMenu(0); }
};

void InternalMenu(int a, user *login_user, int num_of_users, user *users_array) {
	cout << "******* Internal Menu *******\n" << endl;
	cout << "1.Continue game" << endl;
	cout << "2.Choose level" << endl;
	cout << "3.Wheel of Luck" << endl;
	cout << "4.Edit profile" << endl;
	cout << "5.Logout" << endl;
	cout << "for return to main menu enter *";
	cout << "Please enter your choice:" << endl;
	string choice;
	cin >> choice;

	if (choice == "*") {
		return;
	}

	if (choice == "1") { Play(login_user[0].YourLevel, login_user, num_of_users, users_array); }
	//if (choice == "2") {ChooseLevel(0); }
	if (choice == "3") {WheelofLuck(login_user ,num_of_users,users_array); }
	if (choice == "4") { Edit(login_user, num_of_users,users_array) ; }
	//if (choice == "5") {break;}

}

word *split(string a, int *count2) {//joda kardan kalamat az ham v zakhire anha dar araye
	word *ans = (word *)malloc(1 * sizeof(word));
	int i = 0;
	int count = 0;
	while (count != 3) {
		if (a[i] == ' ')++count;
		++i;
	}
	count = 0;
	while (1) {
		char *temp = (char *)malloc(2 * sizeof(char));
		int j = 0;
		while (1) {
			temp[j] = a[i];
			temp[j + 1] = '\0';
			temp = (char *)realloc(temp, (j + 3)*sizeof(char));
			++i; ++j;
			if (a[i] == '\0' || a[i] == ' ')break;
		}
		word joda;
		joda.state = 0;
		joda.str = temp;
		ans[count] = joda;
		ans = (word *)realloc(ans, (2 + count)*sizeof(word));
		++count;
		if (a[i] == '\0')break;
		++i;
	}
	*count2 = count;
	return ans;
}
void ShowLetters(string a) {
	int i = 0;
	for (int j = 0; a[i] != ' '; ++j) {

		cout << a[i] << " ";
		++i;
	}
}

void MainMenu(int a) {
	user *login_user;
	int num_of_users;
	user *users_array = read_users(&num_of_users);
	char login_state = 0;
	while (1) {
		cout << "welcome to this game\n" << endl;
		cout << "******* Main Menu *******" << endl;
		cout << "1.Signup" << endl;
		cout << "2.Login" << endl;
		cout << "3.Rank" << endl;
		cout << "4.Challenge" << endl;
		cout << "5.Exit" << endl;
		cout << "Please enter your choice:" << endl;
		int choice;
		while (1) {
			cin >> choice;
			if (0<choice && choice<6)break;
			else {
				cout << "please enter number of your choice again";
			}
		}


		if (choice == 1) { users_array = Signup(users_array, &num_of_users); }
		else if (choice == 2) {
			login_user = Login(users_array, &num_of_users);
			InternalMenu(login_user[0].YourLevel, login_user, num_of_users, users_array);
		}
		else if(choice==3){ Rank(users_array,num_of_users);}
		else if (choice == 4) { Challange(0); }
		else if (choice == 5)break;

	}

}

void Edit(user *login_user, int num_of_users, user * users_array) {
	string Username;
	int Password;
	cout << "please enter your new username \n";
	cin >> Username;
	cout << "please enter your new password\n";
	cin >> Password;
	login_user[0].username = stoc(Username);
	login_user[0].password = Password;
	cout << "done" << endl;
	ofstream users_File("user.txt", ios::out);
	users_File << num_of_users;
	for (int t = 0; t<num_of_users; ++t) {
		users_File << "\n" << left << setw(12) << users_array[t].username << fixed << left << setw(12) << users_array[t].password << fixed << left << setw(8) << users_array[t].YourLevel << fixed << left << setw(8) << users_array[t].Coins << fixed << setw(4) << users_array[t].NumerOfExt << fixed << users_array[t].Chance;
	}
}

void Play(int a, user *login_user, int num_of_users, user * users_array) {
	int e, b, c, d;
	fstream users_file("levels.txt", ios::in);
	users_file >> e >> b >> c >> d;
	int max = b + c + d;
	bool end = false , quit = false;//agar bazi tamam shod = true;
	users_file.close();
	while (1) {

		int PayanMarhale = 0;
		int Season = 1;
		string Marhalee;
		Marahel Select;
		ifstream levels("levels.txt", ios::in);
		getline(levels, Marhalee);
		getline(levels, Marhalee);

		for (int i = 0; i<login_user[0].YourLevel; ++i) {
			getline(levels, Marhalee);
			if (Marhalee == "") {
				--i; ++Season;
				login_user[0].Chance++;
			}
		}
		Select = Ebtedaei(Marhalee);
		string Hadsi;

		int TedadKhatTire = 0;
		while (1) {
			cout << "season: " << Season << "\t" << "level: " << login_user[0].YourLevel << "\t" << "coins:" << login_user[0].Coins << "\t" << "extra words:" << login_user[0].NumerOfExt << endl;

			cout << "if you want go back to internal menu enter * :" << endl;
			cout << "if you want another order of letters enter $ :" << endl;
			cout << "if you need help enter # :" << endl;
			cout << Select.Horof << endl;
			cout << "enter word:" << endl;
			cin >> Hadsi;

			if (Hadsi == "*") {
				quit = true;
				break;
			}


			if (Hadsi == "$") {
				srand(time(0));
				int len = strlen(Select.Horof);
				random_shuffle(Select.Horof, Select.Horof + (len * sizeof(char)));
				continue;
			}


			for (int i = 0; i<Select.Count; ++i) {
				if (Hadsi == Select.Kalamt[i].str) {
					Select.Kalamt[i].state = true; break;
				}
			}
			for (int j = 0; j<Select.Count; ++j) {
				TedadKhatTire = strlen(Select.Kalamt[j].str);
					if (Select.Kalamt[j].state == true && j <= Select.NUMAsli) {
						cout << Select.Kalamt[j].str << endl;
					}

					else if (j>Select.NUMAsli && Select.Kalamt[j].state == true) {
						++login_user[0].NumerOfExt;
						cout<<"one extra word"<< endl;
					}

					else if (Select.Kalamt[j].state == false && j <= Select.NUMAsli) {
						for (int l = 0; l<TedadKhatTire; ++l) {
							cout << "_ ";
						}
						cout << endl;
					}

			}
			PayanMarhale = 0;
			for (int t = 0; t < Select.Count; t++) {
				if(Select.Kalamt[t].state == 1 && t <= Select.NUMAsli){
					PayanMarhale++;
				}
			}

			if (PayanMarhale == Select.NUMAsli) {
				login_user[0].Coins += 100;
				if ((login_user[0].YourLevel == 17)) {
					end = true;
					break;
				}
				++login_user[0].YourLevel;
				break;
			}


		}
		if (end == true) {
			cout << "well done" << endl;
			break;
		}
		if (quit == true) {
			break;
		}
		while (login_user[0].NumerOfExt>6) {
			login_user[0].NumerOfExt -= 6;
			++login_user[0].Chance;
		}

		ofstream users_File("user.txt", ios::out);
		users_File << num_of_users;
		for (int t = 0; t<num_of_users; ++t) {
			users_File << "\n" << left << setw(12) <<users_array[t].username << fixed << left << setw(12) << users_array[t].password << fixed << left << setw(8) << users_array[t].YourLevel << fixed << left << setw(8) << users_array[t].Coins << fixed << setw(4) << users_array[t].NumerOfExt << fixed << users_array[t].Chance;
		}


	}

}

Marahel Ebtedaei(string a) {//sakhtane yek strucr marahel



	Marahel ans;
	int count = 0;
	char *hrof = (char *)malloc(2 * sizeof(char));
	int num_asli = 0, num_farei = 0;
	ans.Kalamt = split(a, &count);
	int i = 0;

	while (a[i] != ' ') {
		hrof[i] = a[i];
		hrof[i + 1] = '\0';
		hrof = (char *)realloc(hrof, (i + 3)*sizeof(char));
		i++;
	}
	i++;
	while (a[i] != ' ') {
		num_asli = num_asli * 10 + (a[i] - 48);
		i++;
	}
	i++;
	while (a[i] != ' ') {
		num_farei = num_farei * 10 + (a[i] - 48);
		i++;
	}
	ans.Horof = hrof;
	ans.NUMAsli = num_asli;
	ans.NumFArei = num_farei;
	ans.Count = count;
	return ans;
}
void WheelofLuck(user *login_user, int num_of_users, user * users_array) {
	while (login_user[0].Chance > 0) {
	int choice;
	cout << "your chance:   " << login_user[0].Chance << endl;
	cout << "ther are 6 types of prizes" << endl;
	cout << "50 coins" << endl;
	cout << "70 coins" << endl;
	cout << "90 coins" << endl;
	cout << "110 coins" << endl;
	cout << "150 coins" << endl;
	cout << "220 coins" << endl;
	cout << "it depends on your luck" << endl;
	cout << "enter nomber of your choice" << endl;
	cout << "1 for try your luck \n 2 for internal menu" << endl;
	cin >> choice;
	if (choice == 2) {
		break;
	}
	int first_coin = login_user[0].Coins;
	srand(time(0));
	int mahdode = (rand() % 100) + 1;
	if (mahdode <= 30) {
		login_user[0].Coins = login_user[0].Coins + 50;
	}
	else if (mahdode > 30 && mahdode <= 50) {
		login_user[0].Coins = login_user[0].Coins + 70;
	}
	else if (mahdode > 50 && mahdode <= 70) {
		login_user[0].Coins = login_user[0].Coins + 90;
	}
	else if (mahdode > 70 && mahdode <= 85) {
		login_user[0].Coins = login_user[0].Coins + 110;
	}
	else if (mahdode > 85 && mahdode <= 95) {
		login_user[0].Coins = login_user[0].Coins + 150;
	}
	else if (mahdode > 95 && mahdode <= 100) {
		login_user[0].Coins = login_user[0].Coins + 220;
	}
	login_user[0].Chance--;
	cout << "you earn " << login_user[0].Coins - first_coin << "coins" << endl;
	}
	ofstream users_File("user.txt", ios::out);
	users_File << num_of_users;
	for (int t = 0; t<num_of_users; ++t) {
		users_File << "\n" << left << setw(12) << users_array[t].username << fixed << left << setw(12) << users_array[t].password << fixed << left << setw(8) << users_array[t].YourLevel << fixed << left << setw(8) << users_array[t].Coins << fixed << setw(4) << users_array[t].NumerOfExt << fixed << users_array[t].Chance;
	}
}

int main() {
	MainMenu(0);
	return 0;

}
