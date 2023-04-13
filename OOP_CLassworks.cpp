#include <iostream>
#include <string>
#include <Windows.h>

using namespace std;

class User {
protected:
	string login;
	string password;

public:
	User(string login, string password) : login(login), password(password) {}

	string getLogin() const { return login; }
	void setLogin(string login) { this->login = login; }
	string getPassword() const { return password; }
	void setPassword(string password) { this->password = password; }
};

class Administrator : public User {
public:
	Administrator(string login, string password) : User(login, password) {}

	void changeLogin(User* user, string newLogin) {
		user->setLogin(newLogin);
	}

	void changePassword(User* user, string newPassword) {
		user->setPassword(newPassword);
	}
};

class Moderator : public User {
public:
	Moderator(string login, string password) : User(login, password) {}

	void changeLogin(User* user, string newLogin) {
		user->setLogin(newLogin);
	}
};

void printUsers(User** users, int numUsers) {
	cout << "-> Список усіх користувачів:\n";
	for (int i = 0; i < numUsers; i++) {
		cout << "\t-> Користувач № " << i + 1 << "\n\tЛогін = " << users[i]->getLogin() << "\n\tПароль = " << users[i]->getPassword() << endl;
	}
}

int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	const int MAX_USERS = 10;
	User* users[MAX_USERS];
	int numUsers = 0;

	int option;
	while (true) {
		cout << "-> Меню:\n";
		cout << "\t-> 1. Реєстрація\n";
		cout << "\t-> 2. Змінити логін користувача\n";
		cout << "\t-> 3. Змінити логін та пароль користувача\n";
		cout << "\t-> 4. Вийти\n";
		cout << "-> Ваш вибір: ";
		cin >> option;

		if (option == 1) {
			cout << "--------------------------------------------------------------------------\n";
			if (numUsers == MAX_USERS) {
				cout << "-> Перевищено ліміт користувачів.\n";
			}
			else {
				string login, password;
				cout << "-> Введіть логін для нового користувача: ";
				cin >> login;
				cout << "-> Введіть пароль для нового користувача: ";
				cin >> password;
				users[numUsers++] = new User(login, password);
			}
			cout << "--------------------------------------------------------------------------\n";
			printUsers(users, numUsers);
			cout << "--------------------------------------------------------------------------\n";
		}
		else if (option == 2) {
			cout << "--------------------------------------------------------------------------\n";
			if (numUsers == 0) {
				cout << "-> Наразі користувачі не знайдені.\n";
			}
			else {
				int userIndex;
				string newLogin;
				cout << "-> Введіть ідентифікатор користувача для зміни його логіну: ";
				cin >> userIndex;
				if (userIndex < 1 || userIndex > numUsers) {
					cout << "-> Користувача під таким номером не зайдено.\n";
				}
				else {
					cout << "-> Введіть новий логін: ";
					cin >> newLogin;
					users[userIndex - 1]->setLogin(newLogin);
				}
			}
			cout << "--------------------------------------------------------------------------\n";
			printUsers(users, numUsers);
			cout << "--------------------------------------------------------------------------\n";
		}
		else if (option == 3) {
			cout << "--------------------------------------------------------------------------\n";
			if (numUsers == 0) {
				cout << "-> Наразі користувачі не знайдені.\n";
			}
			else {
				int userIndex;
				string newLogin, newPassword;
				cout << "-> Введіть ідентифікатор користувача для зміни його логіну та паролю: ";
				cin >> userIndex;
				if (userIndex < 1 || userIndex > numUsers) {
					cout << "-> Користувача під таким номером не зайдено.\n";
				}
				else {
					cout << "-> Введіть новий логін: ";
					cin >> newLogin;
					cout << "-> Введіть новий пароль: ";
					cin >> newPassword;
					users[userIndex - 1]->setLogin(newLogin);
					users[userIndex - 1]->setPassword(newPassword);
				}
			}
			cout << "--------------------------------------------------------------------------\n";
			printUsers(users, numUsers);
			cout << "--------------------------------------------------------------------------\n";
		}
		else if (option == 4) {
			break;
		}
		else {
			cout << "--------------------------------------------------------------------------\n";
			cout << "-> Функцію меню не зайдено.\n";
			cout << "--------------------------------------------------------------------------\n";
		}
	}

	for (int i = 0; i < numUsers; i++) {
		delete users[i];
	}

	cout << "--------------------------------------------------------------------------\n";
	system("pause");
	return 0;
}