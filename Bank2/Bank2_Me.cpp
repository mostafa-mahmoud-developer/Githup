#include <iostream>
#include <string> 
#include <vector>
#include <iomanip>
#include <fstream>
using namespace std;

string ClientFileName = "MyFile.txt";

void Bank1();

enum eBankMenu {
	eShowClientsList = 1, eAddNewClient = 2,
	eDeletClient = 3, eUpdateClientInfo = 4,
	eFindClient = 5, Transactions = 6, eExit = 7
};
enum eTransaction { eDeposit = 1, eWhithdarw = 2, eTotalBalance = 3, eMainMenu = 4 };
struct sClient
{
	string AccountNumber;
	string PinCode;
	string Name;
	string Phone;
	double AccountSalary = 0.0;
};

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
	string sMain = "Clients List (" + to_string(vClients.size())+ ") Client (s)";
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
	cout << "\t[7] Exist.";
	cout << "\n=========================================\n\n" << endl;
	cout << "Choose what do you want to do ? [1 to 7]? ";
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
void WhithdrawClientInFolder(string FileName, string AccountNumber,sClient Client, vector<sClient>& vClients)
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
	WhithdrawClientInFolder(ClientFileName, AccountNumber,Client, vClients);
}


void GoBachToMainMenu()
{
	cout << "\n\nPress any key to go back to main meny.....";
	system("pause>0");
	Bank1();
}
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
void Bank1()
{
	system("cls");
	eBankMenu UserChoose = ReadMainScreen();
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
	case eBankMenu::eExit:
		PrintTopic("Program Ends :-)");
		break;
	default:
		system("pause>0");
		Bank1();

	}

	if (UserChoose != eBankMenu::eExit)
	{
		cout << "\n\n\nPress any key to go back to main menu.";
		system("pause>0");
		Bank1();
	}
}

int main()
{
	Bank1();
	system("pause>0");
}