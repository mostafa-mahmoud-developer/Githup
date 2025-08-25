#include <iostream>
#include <vector>
#include <string>
#include <fstream>
using namespace std;
string ClientFileName = "MyFile.txt";
void ATM();
void Login();
struct sClient
{
	string AccountNumber;
	string PinCode;
	string Name;
	string Phone;
	double Salary = 0.0;
};
sClient ClientLogin;
enum eATM { eQuickWithdary = 1, eNormalWithdraw = 2, eDeposit = 3,
	eCheckBalance = 4, eLogout = 5 };

vector <string>SplitString(string S1, string Separator)
{
	short pos = 0;
	string sWord = "";
	vector<string>vString;
	while ((pos = S1.find(Separator)) != std::string::npos)
	{
		sWord = S1.substr(0, pos);
		if (sWord != "")
		{
			vString.push_back(sWord);
			S1.erase(0, pos + Separator.length());
		}
	}
	vString.push_back(S1);

	return vString;
}
sClient ConvertLineToRecord(string S1, string Separator = "#//#")
{
	sClient Client;
	vector<string>vString = SplitString(S1, Separator);

	Client.AccountNumber = vString[0];
	Client.PinCode = vString[1];
	Client.Name = vString[2];
	Client.Phone = vString[3];
	Client.Salary = stod(vString[4]);

	return Client;
}

vector<sClient> LoadDataFromFile(string FileName)
{
	vector <sClient> vClients;
	fstream MyFile;
	MyFile.open(FileName, ios::in);

	if (MyFile.is_open())
	{
		string Line = "";
		while (getline(MyFile, Line))
			vClients.push_back(ConvertLineToRecord(Line));
	}
	return vClients;
}
string ConvertRecordToLine(sClient Client, string separator = "#//#")
{
	string stDataLine = "";

	stDataLine += Client.AccountNumber + separator;
	stDataLine += Client.PinCode + separator;
	stDataLine += Client.Name + separator;
	stDataLine += Client.Phone + separator;
	stDataLine += to_string(Client.Salary);

	return stDataLine;
}
void PrintTopic(string Topic)
{
	system("cls");
	cout << "\n-----------------------------------------\n";
	cout << "\t" << Topic;
	cout << "\n-----------------------------------------\n";

}
eATM ReadMainScreen()
{
	int UserChoose = 1;
	system("cls");
	cout << "\n=========================================\n";
	cout << "          ATM Main Menu Screen";
	cout << "\n=========================================\n";
	cout << "\t[1] Quick Withdraw.\n";
	cout << "\t[2] Normal Withdara.\n";
	cout << "\t[3] Deposit.\n";
	cout << "\t[4] Check Balance.\n";
	cout << "\t[5] Logout.";
	cout << "\n=========================================\n\n" << endl;
	cout << "Choose what do you want to do ? [1 to 5]? ";
	cin >> UserChoose;
	return (eATM)UserChoose;
}
void CheckBalance()
{
	PrintTopic("Check Balance Screen");
	cout << "Your Balance is " << ClientLogin.Salary;
}
enum eQuick {
	Quick1 = 20, Quick2 = 50, Quick3 = 100, Quick4 = 200,
	Quick5 = 400,Quick6 = 600,Quick7 = 800, Quick8 = 1000, Quick9 = 0
};
short ReadQuichWithdraw(sClient Client)
{
	short UserChoose = 1;
	system("cls");
	cout << "\n=========================================\n";
	cout << "         Quick Withdarw";
	cout << "\n=========================================\n";
	cout << "\t[1] 20 \t[2]50\n";
	cout << "\t[3] 100\t[4]200\n";
	cout << "\t[5] 400\t[6]600\n";
	cout << "\t[7] 800\t[8]1000\n";
	cout << "\t[9] Exit\n";
	cout << "\n=========================================\n\n" << endl;
	cout << "Your Balance is " << Client.Salary;
	cout << "\nChoose what do you want to do ? [1 to 9]? ";
	cin >> UserChoose;
	return UserChoose;
}
short FindQuickWhithdraw(short UserChoose)
{
	switch (UserChoose)
	{
	case 1:
		return (short)Quick1;
		break;
	case 2:
		return (short)Quick2;
		break;
	case 3:
		return (short)Quick3;
		break;
	case 4:
		return (short)Quick4;
		break;
	case 5:
		return (short)Quick5;
		break;
	case 6:
		return (short)Quick6;
		break;
	case 7:
		return (short)Quick7;
		break;
	default:
		break;
	}
}
void UpdateBalanceInFile()
{
	vector<sClient>vClients = LoadDataFromFile(ClientFileName);
	fstream MyFile;
	MyFile.open(ClientFileName, ios::out);
	if (MyFile.is_open())
	{
		string Line;
		for (sClient& C : vClients)
		{
			if (C.AccountNumber == ClientLogin.AccountNumber)
			{
				C.Salary = ClientLogin.Salary;
			}
			Line = ConvertRecordToLine(C);
			MyFile << Line << endl;
		}
		MyFile.close();
	}
}
void QuickWithdarw(sClient Client = ClientLogin)
{
	bool isInBalance = true;
	
	do {
		PrintTopic("Quick Withdarw Screen");
		short UserChoose = (short)ReadQuichWithdraw(Client);
		if (UserChoose == 9)
			ATM();
		if (FindQuickWhithdraw(UserChoose) > Client.Salary)
		{
			isInBalance = false;
			cout << "\nThe amount exceeds you balance,make another choice.\n";
			cout << "Press any key to continue...";
			system("pause>0");
		}
		else
		{
			char yes = 'y';
			cout << "Are you sure you want perform this transaction? y/n? ";
			cin >> yes;
			if (tolower(yes) == 'y')
			{
			isInBalance = true;
			ClientLogin.Salary -= FindQuickWhithdraw(UserChoose);
			UpdateBalanceInFile();
			cout << "\nDone Successfully. New Balance is " << ClientLogin.Salary;
			cout << "Press any key to continue...";
			system("pause>0");
			}
		}
	} while (isInBalance == false);
}
void NormalWithdarw(sClient Client = ClientLogin)
{
	bool isInBalance = true;
	do {
		PrintTopic("Normal Withdarw Screen");
		int withdarwAmount = 0;
		cout << "\nEnter an amount multiple 5`s ? " ;
		cin >> withdarwAmount;
		if (withdarwAmount > Client.Salary)
		{
			isInBalance = false;
			cout << "\nThe amount exceeds you balance,Enter another amount.\n";
			cout << "Press any key to continue...";
			system("pause>0");
			ATM();
		}
		else
		{
			char yes = 'y';
			cout << "\nAre you sure you want perform this transaction? y/n? ";
			cin >> yes;
			if (tolower(yes) == 'y')
			{
				isInBalance = true;
				ClientLogin.Salary -= withdarwAmount;
				UpdateBalanceInFile();
				cout << "\nDone Successfully. New Balance is " << ClientLogin.Salary;
				cout << "Press any key to continue...";
				system("pause>0");
			}
		}
	} while (isInBalance == false);
}
void Deposit(sClient Client = ClientLogin)
{
	bool isInBalance = true;
	PrintTopic("Deposit Screen");
	int DepositAmount = 0;
	cout << "\nEnter an amount multiple 5`s ? ";
	cin >> DepositAmount;
	char yes = 'y';
	cout << "\nAre you sure you want perform this transaction? y/n? ";
	cin >> yes;
	if (tolower(yes) == 'y')
	{
		isInBalance = true;
		ClientLogin.Salary += DepositAmount;
		UpdateBalanceInFile();
		cout << "\nDone Successfully. New Balance is " << ClientLogin.Salary;
		cout << "Press any key to continue...";
		system("pause>0");
	}

}
void ATM()
{
	
	eATM UserChoose = ReadMainScreen();

	switch (UserChoose)
	{
	case eQuickWithdary:
		QuickWithdarw();
		ATM();
		break;
	case eNormalWithdraw:
		NormalWithdarw(ClientLogin);
		ATM();
		break;
	case eDeposit:
		Deposit(ClientLogin);
		system("pause>0");
		ATM();
		break;
	case eCheckBalance:
		CheckBalance();
		system("pause>0");
		ATM();
		break;
	case eLogout:
		Login();
		break;
	default:
		break;
	}



}
bool IsClientFoundByAccountNumberAndPinCode(string AccountNumber,string PinCode, vector<sClient>vClients)
{
	for (sClient& C : vClients)
	{
		if (AccountNumber == C.AccountNumber && PinCode == C.PinCode)
		{
			ClientLogin = C;
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
	PrintTopic("Login Screen");
	string AccountNumber = ReadString("Enter Account Number");
	string PinCode = ReadString("Enter PinCode");
	vector<sClient>vClients = LoadDataFromFile(ClientFileName);
	if(IsClientFoundByAccountNumberAndPinCode(AccountNumber, PinCode, vClients))
	{
		ATM();
	}
	else
	{
		do {
			system("cls");
			PrintTopic("Login Screen");
			cout << "\nInvalid Account Number/PinCode!\n";
			AccountNumber = ReadString("Enter Account Number");
			PinCode = ReadString("Enter PinCode");
		} while (!IsClientFoundByAccountNumberAndPinCode(AccountNumber, PinCode, vClients));
	}	
}
int main()
{
	Login();

	system("pause>0");
}