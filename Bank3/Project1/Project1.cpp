#include <iostream>
#include <string> 
#include <vector>
#include <iomanip>
#include <fstream>
#include <cmath>
using namespace std;

string ClientFileName = "MyFile.txt";
string UserFileName = "UsersFile.txt";
void Bank1();
void Login();
enum eBankMenu {
	eShowClientsList = 1, eAddNewClient = 2,
	eDeletClient = 3, eUpdateClientInfo = 4,
	eFindClient = 5, Transactions = 6, eManageUsers = 7 , eLogout = 8
};
enum eTransaction { eDeposit = 1, eWhithdarw = 2, eTotalBalance = 3, eMainMenu = 4 };
enum enManageUsers {
	eListUsers = 1, eAddNewUser = 2, eDeleltUser = 3, eUpdateUser = 4,
	eFindUser = 5, enMainMenu = 6
};
struct sClient
{
	string AccountNumber;
	string PinCode;
	string Name;
	string Phone;
	double AccountSalary = 0.0;
};
struct sUser
{
	string UserName;
	string Password;
	int Permission;
};
sUser UserLogin;
vector<string>SplitString(string S1, string separator)
{
	short pos = 0;
	string sWord;
	vector<string>vString;
	while ((pos = S1.find(separator)) != std::string::npos)
	{
		sWord = S1.substr(0, pos);
		if (sWord != "")
		{
			vString.push_back(sWord);
			S1.erase(0, pos + separator.length());
		}
	}
	vString.push_back(S1);
	return vString;
}

sClient ConvertLineToRecord(string S1, string separator = "#//#")
{
	sClient Client;
	vector<string>vString = SplitString(S1, separator);

	Client.AccountNumber = vString[0];
	Client.PinCode = vString[1];
	Client.Name = vString[2];
	Client.Phone = vString[3];
	Client.AccountSalary = stod(vString[4]);

	return Client;
}
vector<sClient>LoadDataFromFile(string FileName)
{
	vector <sClient>vClient;
	fstream MyFile;
	MyFile.open(FileName, ios::in);

	if (MyFile.is_open())
	{
		string Line = "";
		while (getline(MyFile, Line))
		{
			vClient.push_back(ConvertLineToRecord(Line));
		}
		MyFile.close();
	}
	return vClient;
}
void PrintTopic(string Topic)
{
	system("cls");
	cout << "\n-----------------------------------------\n";
	cout << "\t" << Topic;
	cout << "\n-----------------------------------------\n";

}
void TotalBalance(vector <sClient>& vClients)
{
	long long total = 0.0;
	for (sClient& C : vClients)
	{
		total += C.AccountSalary;
	}
	cout << "\n\nTotal Balance : " << total;
}
void PrintClientDetailsInLine(sClient Client)
{
	cout << "| " << left << setw(15) << Client.AccountNumber;
	cout << "| " << left << setw(13) << Client.PinCode;
	cout << "| " << left << setw(40) << Client.Name;
	cout << "| " << left << setw(15) << Client.Phone;
	cout << "| " << left << setw(15) << Client.AccountSalary;
	cout << endl;

}
void PrintClientsTable(vector<sClient>vClients)
{
	string sMain = "Clients List (" + to_string(vClients.size()) + ") Client (s)";
	PrintTopic(sMain);

	cout << "| " << left << setw(15) << "Account Number";
	cout << "| " << left << setw(13) << "PinCode";
	cout << "| " << left << setw(40) << "Name";
	cout << "| " << left << setw(15) << "Phone";
	cout << "| " << left << setw(15) << "Account Salary";
	cout << "\n______________________________________________________________________________________________________________\n\n";

	for (const sClient& Client : vClients)
	{
		PrintClientDetailsInLine(Client);
	}
	cout << "______________________________________________________________________________________________________________\n\n";
	TotalBalance(vClients);
}
eBankMenu ReadMainScreen()
{
	int UserChoose = 1;
	system("cls");
	cout << "\n=========================================\n";
	cout << "              Main Menu";
	cout << "\n=========================================\n";
	cout << "\t[1] Show Client List.\n";
	cout << "\t[2] Add New Client.\n";
	cout << "\t[3] Delet Client.\n";
	cout << "\t[4] Update Client Info.\n";
	cout << "\t[5] Find Client.\n";
	cout << "\t[6] Transactions.\n";
	cout << "\t[7] Manage Users.\n";
	cout << "\t[8] Logout.";
	cout << "\n=========================================\n\n" << endl;
	cout << "Choose what do you want to do ? [1 to 8]? ";
	cin >> UserChoose;
	return (eBankMenu)UserChoose;
}
bool IsClientFoundByAccountNumber(string AccountNumber, vector<sClient>vClients)
{
	for (sClient& C : vClients)
	{
		if (AccountNumber == C.AccountNumber)
		{
			return true;
		}
	}
	return false;
}
string ReadNewAccontNumber()
{
	vector<sClient>vClients = LoadDataFromFile(ClientFileName);
	string AccountNumber;
	cout << "Enter Account Number?" << endl;
	getline(cin >> ws, AccountNumber);
	while (IsClientFoundByAccountNumber(AccountNumber, vClients))
	{
		cout << "This Account Number is already exist enter, enter another Account Number.\n";
		getline(cin >> ws, AccountNumber);
	}
	return AccountNumber;
}
sClient ReadNewClient()
{
	sClient Client;
	Client.AccountNumber = ReadNewAccontNumber();

	cout << "Enter PinCode?" << endl;
	getline(cin >> ws, Client.PinCode);

	cout << "Enter Name?" << endl;
	getline(cin, Client.Name);

	cout << "Enter Phone Number?" << endl;
	getline(cin, Client.Phone);

	cout << "Enter Account Salary?" << endl;
	cin >> Client.AccountSalary;

	return Client;
}
void SaveDataLineToFile(string FileName, string Line)
{
	fstream MyFile;
	MyFile.open(FileName, ios::out | ios::app);

	if (MyFile.is_open())
	{
		MyFile << Line << endl;

		MyFile.close();
	}
}
string ConvertRecordToLine(sClient Client, string separator = "#//#")
{
	string stDataLine = "";

	stDataLine += Client.AccountNumber + separator;
	stDataLine += Client.PinCode + separator;
	stDataLine += Client.Name + separator;
	stDataLine += Client.Phone + separator;
	stDataLine += to_string(Client.AccountSalary);

	return stDataLine;
}
void AddNewClient()
{
	sClient Client = ReadNewClient();
	SaveDataLineToFile(ClientFileName, ConvertRecordToLine(Client));
}
string ReadAccountNumber()
{
	string AccountNumber;
	cout << "\nEnter Account Number ? \n";
	cin >> AccountNumber;
	return AccountNumber;
}
bool FindClientByAccountNumber(string AccountNumber, sClient& Client, vector<sClient>vClients)
{
	for (sClient& C : vClients)
	{
		if (AccountNumber == C.AccountNumber)
		{
			Client = C;
			return true;
		}
	}
	return false;
}
void AddClients()
{
	char AddMore = 'Y';
	do {
		cout << "Add New Client :\n\n";
		AddNewClient();

		cout << "\nClient Added Successfully , Do Want To Add More? Y/N\n";
		cin >> AddMore;
	} while (toupper(AddMore) == 'Y');
}
void PrintClientDetails(sClient Client)
{
	cout << "\nThe following are the client details:\n";
	cout << "\n----------------------------------------------------------------------\n\n";
	cout << "Account Number:" << Client.AccountNumber << endl;
	cout << "PinCode       :" << Client.PinCode << endl;
	cout << "Name          :" << Client.Name << endl;
	cout << "Number Phone  :" << Client.Phone << endl;
	cout << "Account Salary:" << Client.AccountSalary << endl;
	cout << "----------------------------------------------------------------------\n\n";
}
void FindClient(vector <sClient>vClients)
{
	PrintTopic("Find Client Screen");

	string AccountNumber = ReadAccountNumber();
	sClient Client;
	if (FindClientByAccountNumber(AccountNumber, Client, vClients))
	{
		cout << "\nThe following are the client details:\n\n";

		PrintClientDetails(Client);

	}
	else
	{
		cout << "\nClient With (" << AccountNumber << ") NOT Found.\n";
	}
}
void DeleteClientFromFile(string FileName, string AccountNumber, vector<sClient>vClients)
{
	fstream MyFile;
	MyFile.open(FileName, ios::out);
	if (MyFile.is_open())
	{
		string Line;
		for (sClient& C : vClients)
		{
			if (C.AccountNumber != AccountNumber)
			{
				Line = ConvertRecordToLine(C);
				MyFile << Line << endl;
			}
		}
		MyFile.close();
	}
}
void DeleteClient(vector <sClient>& vClients)
{
	sClient Client;
	PrintTopic("Delet Client");
	char Delet = 'y';
	string AccountNumber = ReadAccountNumber();
	if (FindClientByAccountNumber(AccountNumber, Client, vClients))
	{
		cout << "\nThe following are the client details:\n\n";
		PrintClientDetails(Client);
		cout << "\nDo you want to delet this client? Y/N";
		cin >> Delet;
		if (tolower(Delet) == 'y')
		{
			DeleteClientFromFile(ClientFileName, AccountNumber, vClients);
			vClients = LoadDataFromFile(ClientFileName);
		}
	}
	else
	{
		cout << "\nClient With (" << AccountNumber << ") NOT Found.\n";
	}
}
sClient ReadUpdateClientInfo(string AccountNumber)
{
	sClient Client;
	Client.AccountNumber = AccountNumber;

	cout << "Enter PinCode?" << endl;
	getline(cin >> ws, Client.PinCode);

	cout << "Enter Name?" << endl;
	getline(cin, Client.Name);

	cout << "Enter Phone Number?" << endl;
	getline(cin, Client.Phone);

	cout << "Enter Account Salary?" << endl;
	cin >> Client.AccountSalary;

	return Client;
}
void UpdateClientInFile(string FileName, string AccountNumber, vector<sClient>& vClients)
{
	sClient Client = ReadUpdateClientInfo(AccountNumber);
	fstream MyFile;
	MyFile.open(FileName, ios::out);
	if (MyFile.is_open())
	{
		string Line;
		for (sClient& C : vClients)
		{
			if (C.AccountNumber == AccountNumber)
			{
				C = Client;
			}
			Line = ConvertRecordToLine(C);
			MyFile << Line << endl;
		}
		MyFile.close();
	}
}
void UpdateClientInfo(vector<sClient>vClients)
{
	sClient Client;
	PrintTopic("Update Client Info");
	char update = 'y';
	string AccountNumber = ReadAccountNumber();
	if (FindClientByAccountNumber(AccountNumber, Client, vClients))
	{
		cout << "\nThe following are the client details:\n\n";
		PrintClientDetails(Client);
		cout << "\nDo you want to update this client? Y/N";
		cin >> update;
		if (tolower(update) == 'y')
		{
			UpdateClientInFile(ClientFileName, AccountNumber, vClients);
			//vClients = LoadDataFromFile(ClientFileName);
		}
	}
	else
	{
		cout << "\nClient With (" << AccountNumber << ") NOT Found.\n";
	}
}
void AddDepositClientInFolder(string FileName, string AccountNumber, vector<sClient>& vClients)
{
	fstream MyFile;
	double depositacount = 0;
	char SureTrans = 'Y';
	cout << "\nPlease enter deposit account?  ";
	cin >> depositacount;
	cout << "Are you to you want to perform this transaction? Y/N ?  ";
	cin >> SureTrans;
	if (toupper(SureTrans) == 'Y')
	{
		MyFile.open(FileName, ios::out);
		if (MyFile.is_open())
		{
			string Line;
			for (sClient& C : vClients)
			{
				if (C.AccountNumber == AccountNumber)
				{
					C.AccountSalary += depositacount;
					cout << "\nNew account balance is : " << C.AccountSalary;
				}
				Line = ConvertRecordToLine(C);
				MyFile << Line << endl;
			}
			MyFile.close();
		}
	}

}
void Deposit(vector <sClient>& vClients)
{
	sClient Client;
	string AccountNumber;
	PrintTopic("Deposit Screen");
	cout << "\nEnter AccounNumber ? ";
	cin >> AccountNumber;
	while (!FindClientByAccountNumber(AccountNumber, Client, vClients))
	{
		cout << "\nClient with [" << AccountNumber << "] does not exist.\n";
		cout << "\nPlease Enter Account Number ?\n";
		cin >> AccountNumber;
	}
	PrintClientDetails(Client);
	AddDepositClientInFolder(ClientFileName, AccountNumber, vClients);
}
void WhithdrawClientInFolder(string FileName, string AccountNumber, sClient Client, vector<sClient>& vClients)
{
	fstream MyFile;
	double WhithdrawAcount = 0;
	char SureWhithdraw = 'Y';
	cout << "\nPlease enter withdraw account?  ";
	cin >> WhithdrawAcount;
	while (WhithdrawAcount < 0)
	{
		cout << "\nAmount Exceeds the balanec, you can whithdray up to : " << Client.AccountSalary << endl;
		cout << "Please enter another amount ?";
		cin >> WhithdrawAcount;
	}
	cout << "Are you to you want to perform this transaction? Y/N ?  ";
	cin >> SureWhithdraw;
	if (toupper(SureWhithdraw) == 'Y')
	{
		MyFile.open(FileName, ios::out);
		if (MyFile.is_open())
		{
			string Line;
			for (sClient& C : vClients)
			{
				if (C.AccountNumber == AccountNumber)
				{
					C.AccountSalary -= WhithdrawAcount;
					cout << "\nNew account balance is : " << C.AccountSalary;
				}
				Line = ConvertRecordToLine(C);
				MyFile << Line << endl;
			}
			MyFile.close();
		}
	}

}
void Whithdarw(vector <sClient>& vClients)
{
	sClient Client;
	string AccountNumber;
	PrintTopic("Whithdraw Screen");
	cout << "\nEnter AccounNumber ? ";
	cin >> AccountNumber;
	while (!FindClientByAccountNumber(AccountNumber, Client, vClients))
	{
		cout << "\nClient with [" << AccountNumber << "] does not exist.\n";
		cout << "\nPlease Enter Account Number ?\n";
		cin >> AccountNumber;
	}
	PrintClientDetails(Client);
	WhithdrawClientInFolder(ClientFileName, AccountNumber, Client, vClients);
}
//void GoBachToMainMenu()
//{
//	cout << "\n\nPress any key to go back to main meny.....";
//	system("pause>0");
//	Bank1();
//}
eTransaction ReadTransactionChoose()
{
	int eUserChoose;
	cout << "\t[1] Deposit.\n";
	cout << "\t[2] Withdraw.\n";
	cout << "\t[3] Total Balance.\n";
	cout << "\t[4] Main Menu.\n";
	cout << "\nChoose what do you want to do ? [1/4]\n";
	cin >> eUserChoose;
	return (eTransaction)eUserChoose;
}

void TotalBalanceScreen(vector <sClient>& vClients)
{
	PrintTopic("Total Balance Screen");
	TotalBalance(vClients);
}
void Transacion(vector <sClient>& vClients)
{
	PrintTopic("Transactions Menu Screen");
	eTransaction eUserChoose = ReadTransactionChoose();

	switch (eUserChoose)
	{
	case eDeposit:
		Deposit(vClients);
		system("pause>0");
		Transacion(vClients);
		break;
	case eWhithdarw:
		Whithdarw(vClients);
		system("pause>0");
		Transacion(vClients);
		break;
	case eTotalBalance:
		TotalBalanceScreen(vClients);
		break;
	case eMainMenu:
		system("pause>0");
		Bank1();
		break;
	default:
		system("pause>0");
		Bank1();
		break;
	}(eUserChoose);
}
sUser UserConvertLineToRecord(string S1, string separator = "#//#")
{
	sUser User;
	vector<string>vString = SplitString(S1, separator);

	User.UserName = vString[0];
	User.Password = vString[1];
	User.Permission = stoi(vString[2]);

	return User;
}
vector<sUser>UserLoadDataFromFile(string FileName)
{
	vector <sUser>vUser;
	fstream MyFile;
	MyFile.open(FileName, ios::in);

	if (MyFile.is_open())
	{
		string Line = "";
		while (getline(MyFile, Line))
		{
			vUser.push_back(UserConvertLineToRecord(Line));
		}
		MyFile.close();
	}
	return vUser;
}
enManageUsers ReadManageUsers()
{
	short UserChoose = 1;
	system("cls");
	cout << "\n=========================================\n";
	cout << "          Manage Users Menu Screen";
	cout << "\n=========================================\n";
	cout << "\t[1] List Users.\n";
	cout << "\t[2] Add New User.\n";
	cout << "\t[3] Delet User.\n";
	cout << "\t[4] Update User.\n";
	cout << "\t[5] Find User.\n";
	cout << "\t[6] Main Menu.\n";
	cout << "\n=========================================\n\n" << endl;
	cout << "Choose what do you want to do ? [1 to 6]? ";
	cin >> UserChoose;
	return (enManageUsers)UserChoose;
}
void PrintUserDetailsInLine(sUser User)
{
	cout << "| " << left << setw(15) << User.UserName;
	cout << "| " << left << setw(13) << User.Password;
	cout << "| " << left << setw(13) << User.Password;
	cout << endl;
}
void ListUsers(vector<sUser>vUsers)
{
	string sManage = "Clients List (" + to_string(vUsers.size()) + ") User (s)";
	PrintTopic(sManage);

	cout << "| " << left << setw(15) << "User Name";
	cout << "| " << left << setw(13) << "Password";
	cout << "| " << left << setw(13) << "Permission";
    cout << "\n_______________________________________________________________\n\n";

	for (const sUser& User : vUsers)
	{
		PrintUserDetailsInLine(User);
	}
	cout << "_______________________________________________________________\n\n";
	
}
bool IsUserFoundByUserName(string UserName, vector<sUser>vUsers)
{
	for (sUser& U : vUsers)
	{
		if (UserName == U.UserName)
		{
			return true;
		}
	}
	return false;
}
string ReadNewUserName()
{
	vector<sUser>vUsers = UserLoadDataFromFile(UserFileName);
	string UserName;
	cout << "Enter User Name?" << endl;
	getline(cin >> ws, UserName);
	while (IsUserFoundByUserName(UserName, vUsers))
	{
		cout << "User with ["<<UserName<< "] already exists, Enter another UserName.\n";
		getline(cin >> ws, UserName);
	}
	return UserName;
}
int FindPermission()
{
	char yes = 'y';
	cout << "\nDo you want to give full access? y/n? ";
	cin >> yes;
	if (tolower(yes) == 'y')
	{
		return -1;
	}
	else
	{
		int Permission = 0;
		cout << "\nDo you want to give access to :\n";
		
        cout << "\nShow Client List? y/n?";
		cin >> yes;
		if (tolower(yes) == 'y')
			Permission += 1;
        cout << "\nAdd New Client? y/n?";
		cin >> yes;
		if (tolower(yes) == 'y')
			Permission += 2;
        cout << "\nDelet Client? y/n?";
		cin >> yes;
		if (tolower(yes) == 'y')
			Permission += 4;
        cout << "\nUpade Client? y/n?";
		cin >> yes;
		if (tolower(yes) == 'y')
			Permission += 8;
        cout << "\nFind Client? y/n?";
		cin >> yes;
		if (tolower(yes) == 'y')
			Permission += 16;
        cout << "\nTransactions? y/n?";
		cin >> yes;
		if (tolower(yes) == 'y')
			Permission += 32;
        cout << "\nManage Uesers? y/n?";
		cin >> yes;
		if (tolower(yes) == 'y')
			Permission += 64;
		return Permission;
	}

}
sUser ReadNewUser()
{
	sUser User;
	User.UserName = ReadNewUserName();

	cout << "Enter Password?" << endl;
	getline(cin >> ws, User.Password);

	User.Permission = FindPermission();
		cout << "\nUser Add Successfully, do you want to add more user? Y/N? ";
	return User;
}
string ConvertRecordToLine(sUser User, string separator = "#//#")
{
	string stDataLine = "";

	stDataLine +=User.UserName + separator;
	stDataLine +=User.Password + separator;
	stDataLine += to_string(User.Permission) + separator;
	
	return stDataLine;
}
void AddNewUser()
{
	sUser User = ReadNewUser();
	SaveDataLineToFile(UserFileName, ConvertRecordToLine(User));
}
string ReadUserName()
{
	string UserName;
	cout << "\nEnter User Name ? \n";
	cin >> UserName;
	return UserName;
}
bool FindUserByUserName(string UserName, sUser& User, vector<sUser>vUsers)
{
	for (sUser& U : vUsers)
	{
		if (UserName == U.UserName)
		{
			User = U;
			return true;
		}
	}
	return false;
}
void AddUsers()
{
	char AddMore = 'Y';
	do {
		cout << "Add New User :\n\n";
		AddNewUser();

		cout << "\nUser Added Successfully , Do Want To Add More? Y/N\n";
		cin >> AddMore;
	} while (toupper(AddMore) == 'Y');
}
void PrintUserDetails(sUser User)
{
	cout << "\nThe following are the User details:\n";
	cout << "\n----------------------------------------------------------------------\n\n";
	cout << "User Name  : " << User.UserName << endl;
	cout << "Passwoed   :" << User.Password << endl;
	cout << "Permission :" << User.Permission << endl;
	cout << "----------------------------------------------------------------------\n\n";
}
void FindUser(vector <sUser>vUsers)
{
	PrintTopic("Find User Screen");

	string UserName = ReadUserName();
	sUser User;
	if (FindUserByUserName(UserName, User, vUsers))
	{
		PrintUserDetails(User);
	}
	else
	{
		cout << "\nUser With (" << UserName << ") NOT Found.\n";
	}
}
void DeleteUserFromFile(string FileName, string UserName, vector<sUser>vUsers)
{
	fstream MyFile;
	MyFile.open(FileName, ios::out);
	if (MyFile.is_open())
	{
		string Line;
		for (sUser& U : vUsers)
		{
			if (U.UserName != UserName)
			{
				Line = ConvertRecordToLine(U);
				MyFile << Line << endl;
			}
		}
		MyFile.close();
	}
}
void DeleteUser(vector <sUser>& vUsers)
{
	sUser User;
	PrintTopic("Delet User");
	char Delet = 'y';
	string UserName = ReadAccountNumber();
	if (FindUserByUserName(UserName, User, vUsers))
	{
		cout << "\nThe following are the User details:\n\n";
		PrintUserDetails(User);
		cout << "\nDo you want to delet this User? Y/N";
		cin >> Delet;
		if (tolower(Delet) == 'y')
		{
			DeleteUserFromFile(UserFileName, UserName, vUsers);
			vUsers = UserLoadDataFromFile(UserFileName);
		}
	}
	else
	{
		cout << "\nUser With (" << UserName << ") NOT Found.\n";
	}
}
sUser ReadUpdateUserInfo(string UserName)
{
	sUser User;
	User.UserName = UserName;

	cout << "Enter Password?" << endl;
	getline(cin >> ws, User.Password);

	User.Permission = FindPermission();
	cout << "\nUser Updated Successfully. ";
	
	return User;
}
void UpdateUserInFile(string FileName, string UserName, vector<sUser>& vUsers)
{
	sUser User = ReadUpdateUserInfo(UserName);
	fstream MyFile;
	MyFile.open(FileName, ios::out);
	if (MyFile.is_open())
	{
		string Line;
		for (sUser& U : vUsers)
		{
			if (U.UserName == UserName)
			{
				U = User;
			}
			Line = ConvertRecordToLine(U);
			MyFile << Line << endl;
		}
		MyFile.close();
	}
}
void UpdateUserInfo(vector<sUser>vUsers)
{
	sUser User;
	PrintTopic("Update User Info");
	char update = 'y';
	string UserName = ReadUserName();
	if (FindUserByUserName(UserName, User, vUsers))
	{
		cout << "\nThe following are the User details:\n\n";
		PrintUserDetails(User);
		cout << "\nDo you want to update this User? Y/N";
		cin >> update;
		if (tolower(update) == 'y')
		{
			UpdateUserInFile(UserFileName, UserName, vUsers);
			//vClients = LoadDataFromFile(ClientFileName);
		}
	}
	else
	{
		cout << "\nUser With (" << UserName << ") NOT Found.\n";
	}
}

void ManangeUsers()
{
	PrintTopic("Manage Users");
	enManageUsers UserChoose = ReadManageUsers();
	vector <sUser>vUsers = UserLoadDataFromFile(UserFileName);

	switch (UserChoose)
	{
	case eListUsers:
		ListUsers(vUsers);
		break;
	case eAddNewUser:
		AddUsers();
		break;
	case eDeleltUser:
		DeleteUser(vUsers);
		break;
	case eUpdateUser:
		UpdateUserInfo(vUsers);
		break;
	case eFindUser:
		FindUser(vUsers);
		break;
	case enMainMenu:
		Bank1();
		break;
	default:
		break;
	}
	
}
bool isUserHasPermission(int UserChoose, int Permissions)
{
	int Num = 1;
	while (Permissions >= 1)
	{
		while (Permissions >= Num)
		{
			Num *= 2;
		}
		Num /= 2;
		if (Num == pow(2, UserChoose - 1))
			return true;
		Permissions -= Num;
	}
	return false;
}
eBankMenu ReadMainScreenWithPermission(int Permission)
{
	eBankMenu UserChoose = ReadMainScreen();
	if (Permission == -1)
		return UserChoose;
	if (!isUserHasPermission(UserChoose, Permission))
	{
		system("cls");
		cout << "\n-----------------------------------------\n";
		cout << "\nAccess Denied,";
		cout << "\nYou Dont Have Permission To Do This,";
		cout << "\nPlease Conact Your Admin.";
		cout << "\n-----------------------------------------\n";

		cout << "\n\nPress any key to go back to main menu.....";
		system("pause>0");
		Bank1();
	}
	return UserChoose;
}
void Bank1()
{
	system("cls");
	vector <sUser>vUsers = UserLoadDataFromFile(UserFileName);
	eBankMenu UserChoose = ReadMainScreenWithPermission(UserLogin.Permission);
	vector <sClient>vClients = LoadDataFromFile(ClientFileName);

	switch (UserChoose)
	{
	case eBankMenu::eShowClientsList:
		PrintClientsTable(vClients);
		break;
	case eBankMenu::eAddNewClient:
		AddClients();
		break;
	case eBankMenu::eDeletClient:
		DeleteClient(vClients);
		break;
	case eBankMenu::eUpdateClientInfo:
		UpdateClientInfo(vClients);
		break;
	case eBankMenu::eFindClient:
		FindClient(vClients);
		break;
	case eBankMenu::Transactions:
		Transacion(vClients);
		break;
	case eBankMenu::eManageUsers:
		ManangeUsers();
		break;
	case eBankMenu::eLogout:
		PrintTopic("Logout Screen");
		Login();
		break;
	default:
		system("pause>0");
		Bank1();

	}

	if (UserChoose != eBankMenu::eLogout)
	{
		cout << "\n\n\nPress any key to go back to main menu.";
		system("pause>0");
		Bank1();
	}
}
bool isUserExist(string UserName, string Password,int &Permission, vector <sUser>vUsers)
{
	for (sUser& User : vUsers)
	{
		if (User.UserName == UserName && User.Password == Password)
		{
			Permission = User.Permission;
			return true;
		}
	}
	return false;
}
string ReadString(string massege)
{
	string St;
	cout << massege << "? ";
	cin >> St;
	return St;
}
void Login()
{
	vector <sUser>vUsers = UserLoadDataFromFile(UserFileName);
	sUser User;
	system("cls");
	PrintTopic("Longin Screen");
	User.UserName = ReadString("Enter UserName");
	User.Password = ReadString("Enter Password");
	if (isUserExist(User.UserName, User.Password ,User.Permission, vUsers))
	{
		UserLogin = User;
		Bank1();
	}
	else
	{
		while (!isUserExist(User.UserName, User.Password, User.Permission, vUsers))
		{
			system("cls");
			PrintTopic("Longin Screen");
			cout << "Invalid UserName/Passeword!\n";
			User.UserName = ReadString("Enter UserName");
			User.Password = ReadString("Enter Password");
		}
	}
}
int main()
{
	Login();
	system("pause>0");
}