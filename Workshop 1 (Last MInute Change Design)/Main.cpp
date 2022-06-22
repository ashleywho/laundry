#include<mysql.h>
#include<sstream>
#include<conio.h>
#include<iostream>
#include<fstream>

using namespace std;

//global var
int qstate;
MYSQL* conn;
MYSQL_ROW row;
MYSQL_RES* res;

//Database Connection
class db_response
{
public:
	static void ConnectionFunction()
	{
		conn = mysql_init(0);
		//UNCOMMENT IF WANT TO CHECK DB CONNECTION
		/*if (conn)
		{
			cout << "Database connected!" << endl;
			system("cls");
		}
		else
			cout << "Error connecting database" << mysql_errno(conn) << endl;*/
		

		conn = mysql_real_connect(conn, "localhost", "root", "", "laundry", 3306, NULL, 0);
		//UNCOMMENT IF WANT TO CHECK DB CONNECTION
		/*if (conn)
		{
			cout << "Database connected to MySQL " << conn << endl;
			system("pause");
		}
		else
			cout << "Failed to connect!" << mysql_errno(conn) << endl;*/
		
	}
};

//Declaration Function
void displayMenu();
void customerCart();
void login();
void customerRegister();
void customerDashboard();
void customerProfile();
void customerOrder();
void mainMenu();
void adminPro();
void adminInterface();
void adminView();
void adminAdd();
void updateItems();
void adminUpdate();
void adminReport();
string readSession();
void destroySession();


//Checked
int main(){
	//call connection fx
	db_response::ConnectionFunction();

	int choice;

	system("cls");
	cout << "\n\t\t\t\tWelcome to Familia Laundry";
	cout << "\n\t\t\t\t[1] Login";
	cout << "\n\t\t\t\t[2] Services";
	cout << "\n\t\t\t\t[3] Register";
	cout << "\n\t\t\t\t[4] Admin";
	cout << "\n\t\t\t\t[5] Exit";
	cout << "\n\t\t\t\tSelect : ";
	cin >> choice;

	switch (choice) {
	case 1:
		cout << "\n\n\t\t\t\tYou have choose Login\n\t\t\t\t";
		system("pause");
		login();
		break;
	case 2:
		cout << "\n\n\t\t\t\tYou have choose Services\n\t\t\t\t";
		system("pause");
		displayMenu();
		break;
	case 3:
		cout << "\n\n\t\t\t\tYou have choose Register\n\t\t\t\t";
		system("pause");
		customerRegister();
		break;
	case 4:
		cout << "\n\n\t\t\t\tYou have choose Admin\n\t\t\t\t";
		system("pause");
		adminPro();
		break;
	case 5:
		cout << "\n\n\t\t\t\tPress Any Key To Exit\n\t\t\t\t";
		exit(EXIT_SUCCESS);
		break;
	default:
		main();
	}
	
	return 0;
}
//Checked
void displayMenu() {
	string items[5000];
	int indexForNo = 0;
	string status;
	string desc;
	string amount;
	int choice;
	system("cls");
	cout << "\n\t\t\t\t          Welcome to Laundry!";
	
	//Read
	qstate = mysql_query(conn, "SELECT * FROM service");
	if (!qstate) {
		res = mysql_store_result(conn);
		printf("\n\t\t-------------------------------------------------------------------------\n");
		printf("\t\t| %-5s | %-15s | %-30s | %-10s |\n", "ID", "Name", "Description", "Price (RM)");
		printf("\t\t-------------------------------------------------------------------------\n");

		while ((row = mysql_fetch_row(res)))
		{
			printf("\t\t| %-5s | %-15s | %-30s | %-10s |\n", row[0], row[1], row[2], row[3]);
			printf("\t\t-------------------------------------------------------------------------\n");
			items[indexForNo] = row[0];
			indexForNo++;
		}
	} 
	else {
		cout << "Query Execution Problem !" << mysql_errno(conn) << endl;
	}
	
	cout << "\n\t\t\t\tPlease login to use our services.";
	cout << "\n\t\t\t\t[1]Login";
	cout << "\n\t\t\t\t[2]Main";
	cout << "\n\t\t\t\t[3]Exit";
	cout << "\n\t\t\t\tSelect : ";
	cin >> choice;

	switch (choice) {
	case 1:
		login();
		break;
	case 2:
		main();
		break;
	case 3:
		exit(EXIT_SUCCESS);
		break;
	default:
		cout << "\n\t\t\t\tPlease select an option!\n\t\t\t\t";
		displayMenu();
	}
}
//Checked
void login() {	//DONE VERIFICATION, HASH PASS

	system("cls");

	string uname, passw;
	char ch;
	string id = readSession();

	cout << "\n\t\t\t\t      Login Page\n";
	cin.ignore(1, '\n');
	cout << "\n\t\t\t\tUsername : ";
	getline(cin, uname);
	cout << "\n\t\t\t\tPassword : ";
	ch = _getch();
	passw = "";
	while (ch != 13) {
		if (ch != 8) {
			passw.push_back(ch);
			cout << "*";
		}
		else if (ch == 8 && passw.length() != 0) {
			passw.pop_back();
			cout << "\b\b";
		}
		ch = _getch();
	}

	if (uname == "admin" && passw == "admin")
	{
		cout << "HARD CODE";
	}
	else
	{
		string logCustomer_query = ("SELECT * FROM customer WHERE customerName = '" + uname + "' and customerPassword = '" + passw + "'");
		const char* qCust = logCustomer_query.c_str();
		qstate = mysql_query(conn, qCust);
		if (!qstate == 1)
		{
			res = mysql_store_result(conn);
			if ((row = mysql_fetch_row(res)))
			{
				ofstream sessionFile("$ession.txt");

				if (sessionFile.is_open())
				{
					sessionFile << row[0];
					sessionFile.close();
				}
				else
				{
					cout << "Error.\n";
				}
				cout << "\n\n\t\t\t\tSuccessfully logged in.\n\n\t\t\t\t";
				system("pause");
				customerDashboard();
			}
			else
			{
				cout << "\n\n\t\t\t\tWrong Credentials\n\n\t\t\t\t";
				system("pause");
				login();
			}
		}
		else
		{
			cout << "Error";
		}
	}
}
//Checked
void customerDashboard() {
	int choice;
	system("cls");

	string session_query = "SELECT * FROM customer where customerId =('" + readSession() + "')";
	const char* q = session_query.c_str();
	qstate = mysql_query(conn, q);
	res = mysql_store_result(conn);
	row = mysql_fetch_row(res);
	string a = row[1];
	string id = readSession();
	string b = row[3];


	system("cls");
	cout << "\n\t\t\t\tWelcome to Familia Laundry, " << a << endl;
	cout << "\n\t\t\t\t[1] Services";
	cout << "\n\t\t\t\t[2] Profile";
	cout << "\n\t\t\t\t[3] Orders";
	cout << "\n\t\t\t\t[4] Logout";
	cout << "\n\t\t\t\tSelect : ";
	cin >> choice;

	switch (choice) {
	case 1:
		cout << "\n\n\t\t\t\tYou have choose Services\n\t\t\t\t";
		system("pause");
		mainMenu();
		break;
	case 2:
		cout << "\n\n\n\t\t\t\tYou have choose Profile\n\t\t\t\t";
		system("pause");
		customerProfile();
		break;
	case 3:
		cout << "\n\n\t\t\t\tYou have choose Orders\n\t\t\t\t";
		system("pause");
		customerCart();
		break;
	case 4:
		exit(EXIT_SUCCESS);
		break;
	default:
		main();
	}
}
//Checked (Error selection)
void mainMenu() {
mainpage:
	//Declare
	int indexForNo = 0;
	string items[5000];
	string select;
	string confirmation;
	string nameServ;
	string amountServ;
	string descServ;
	bool HaveException = false;
	bool NotInDatabase = false;
	system("cls");
	char choose;
	//Try
	string quantity;
	int amountQuan;
	
	//DB Logged In
	string session_query = "SELECT * FROM customer where customerId =('" + readSession() + "')";
	const char* q = session_query.c_str();
	qstate = mysql_query(conn, q);
	res = mysql_store_result(conn);
	row = mysql_fetch_row(res);
	string a = row[1];
	string id = readSession();
	string b = row[3];

	//Interface
	cout << "\n\t\t\t\t Hi. Welcome to our laundry, " << a << endl;
	qstate = mysql_query(conn, "SELECT * FROM service");
	if (!qstate) {
		res = mysql_store_result(conn);
		printf("\n\t\t-------------------------------------------------------------------------\n");
		printf("\t\t| %-5s | %-15s | %-30s | %-10s |\n", "ID", "Name", "Description", "Price (RM)");
		printf("\t\t-------------------------------------------------------------------------\n");
		while ((row = mysql_fetch_row(res)))
		{
			
			printf("\t\t| %-5s | %-15s | %-30s | %-10s |\n", row[0], row[1], row[2], row[3]);
			printf("\t\t-------------------------------------------------------------------------\n");
			items[indexForNo] = row[0];
			indexForNo++;
		
		}
	}
	else {
		cout << "Query Execution Problem !" << mysql_errno(conn) << endl;
	}
	
	cout << "\n\t\t\t\t     Select item : ";
	cin >> select;

	string selectedService_query = "SELECT * FROM service where serviceId = ('" + select + "')";
	const char* q1 = selectedService_query.c_str();
	qstate = mysql_query(conn, q1);
	res = mysql_store_result(conn);
	row = mysql_fetch_row(res);
	nameServ = row[1]; //Service Name
	descServ = row[2]; // Description
	amountServ = row[3]; //Amount Item
	if (HaveException == false)
	{
		stringstream streamid;
		string idid;
		streamid << select;
		streamid >> idid;

		for (int i = 0; i < indexForNo; i++)
		{
			if (idid != items[i])
			{
				NotInDatabase = true;
			}
			else
			{
				NotInDatabase = false;
				break;
			}
		}
		if (NotInDatabase == false)
		{
			cout << "\n\t\t\t\t     Quantity : ";
			cin >> quantity;

			//Test
			int convertAmountServ = stoi(amountServ); //Convert string array to int
			int convertQuan = stoi(quantity);
			amountQuan = convertAmountServ * convertQuan;
			//cout << "\n\t\t\t\t" << amountQuan << endl << nameServ << endl << descServ;

			//DB Insert Cart
			string addtocart_query = "INSERT INTO payment (serviceId, customerId, itemQuantity) VALUES ('" + select + "', '" + readSession() + "', '" + quantity + "')";
			const char* qatc = addtocart_query.c_str();
			qstate = mysql_query(conn, qatc);
			if (!qstate)
			{
				cout << "\n\t\t\t     Item successfully added to your cart!" << endl;
				cout << "\n\t\t\t     Keep browsing 'B', Go to cart 'C', Logout 'X' : ";
				cin >> choose;

				if (choose == 'b' || choose == 'B') {
					mainMenu();
				}
				else if (choose == 'c' || choose == 'C')
				{
					customerOrder();
					return;
				}
				else if (choose == 'x' || choose == 'X')
				{
					destroySession();
					exit(EXIT_SUCCESS);
				}
				else
					cout << "\nPlease enter a valid choice.";
			}
			else
			{
				cout << "\n\nError adding item to cart." << mysql_errno(conn) << endl;
			}
		}
		else
		{
			cout << "\nThe product ID you entered does not exist." << endl;
			system("pause");
			customerDashboard();

		}
	}
}
//Checked (Error selection, display)
void customerOrder() {

cart:
	system("Laundry Management System");
	system("cls");
	string items[5000];
	int indexForNo = 0;
	string choice;
	char choose;
	bool HaveException = false;
	bool NotInDatabase = false;
	string quantity;
	string choosing;
	string a, b, c, d, e, f, g;
	string status = "Ordered";
	string pickup = "Not Ready Yet";
	int subtotal;
	
	string session_query = "SELECT * FROM customer where customerId =('" + readSession() + "')";
	const char* q = session_query.c_str();
	qstate = mysql_query(conn, q);
	res = mysql_store_result(conn);
	row = mysql_fetch_row(res);
	string name = row[1];
	string id = readSession();


	cout << "\n\t\t\t\t\t\t" << name << "'s Cart";
	string cart_query = "SELECT * FROM service INNER JOIN payment using (serviceId) WHERE customerId = '" + readSession() + "'";
	const char* qc = cart_query.c_str();
	qstate = mysql_query(conn, qc);
	if (!qstate) {
		res = mysql_store_result(conn);
		printf("\n\t\t\t----------------------------------------------------------\n");
		printf("\t\t\t| %-5s | %-20s | %-10s | %-10s |\n", "ID", "Name", "Price", "Quantity");
		printf("\t\t\t----------------------------------------------------------\n");
		while ((row = mysql_fetch_row(res)))
		{

			a = row[0];
			b = row[1];
			c = row[2];
			d = row[3];
			e = row[4];
			f = row[5];
			g = row[6];
			
			printf("\t\t\t| %-5s | %-20s | %-10s | %-10s |\n", row[4], row[1], row[3], row[6]);
			items[indexForNo] = row[0];
			indexForNo++;
			
			
		}
		printf("\t\t\t----------------------------------------------------------\n\n");
	}
	else
	{
		cout << "\nQuery execution problem!" << mysql_errno(conn) << endl;
	}

	//cout << a << b << c << d << e << f << g; //Check DATA

	try
	{
		//DB Display Total
		string sum_query = "SELECT SUM(price * itemQuantity) FROM service INNER JOIN payment USING (serviceId) INNER JOIN customer USING (customerId) WHERE customerId  = '" + readSession() + "'";
		const char* qs = sum_query.c_str();
		qstate = mysql_query(conn, qs);
		if (!qstate)
		{
			res = mysql_store_result(conn);

			cout << "\n\t\t\t\t           Your total is RM ";
			while (row = mysql_fetch_row(res))
			{
				cout << row[0];
			}

			cout << endl << endl;
		}
		else
		{
			cout << "\nSystem failed to display your total.\n";
		}

		//
		cout << "\n\t\tInsert the ID of the items you want to remove, 'P' to confirm Order and 'X' to go Cancel. : ";
		cin >> choice;
		cout << endl;
		if (choice == "P" || choice == "p")
		{
			//Code Order Masuk Sini *WORK*
			string insertOrder_query = "INSERT INTO ordering (customerId,serviceId,list,quantity,amount,status,pickUpStatus) SELECT '" + f + "','" + a + "','" + b + "', '" + g + "', '" + d + "','" + status + "','" + pickup + "' FROM payment WHERE customerId = '" + readSession() + "'";
			const char* q2 = insertOrder_query.c_str();
			qstate = mysql_query(conn, q2);

			

			//delete cart
			string deleteOrder_query = "DELETE FROM payment WHERE customerId = '" + readSession() + "'";
			const char* qDel = deleteOrder_query.c_str();
			qstate = mysql_query(conn, qDel);
			if (!qstate) {
				cout << "\n\t\t\tOrder completed. Proceed to Payment in Orders Section\n\n\t\t\t";
				system("pause");
				customerDashboard();
			}
			else {
				cout << "Error.";
			}
			return;
		}
		else if (choice == "X" || choice == "x")
		{
			string deleteOrder1_query = "DELETE FROM payment WHERE customerId = '" + readSession() + "'";
			const char* qDel1 = deleteOrder1_query.c_str();
			qstate = mysql_query(conn, qDel1);
			if (!qstate) {
				cout << "\n\t\t\t\tOrder Cancelled. You will be direct to Menu.\n\n\t\t\t\t";
				system("pause");
				customerDashboard();
			}
			else {
				cout << "Error.";
			}
			return;
		}
	}
	catch (exception e)
	{
		cout << "Please enter a valid option.\n";
		HaveException = true;
		exit(EXIT_SUCCESS);
	}
	int conG;
	int convPrice = stoi(d);
	int convQuan = stoi(g);
	conG = convPrice * convQuan;
	/*cout << convPrice << " " << convQuan << " " << g << endl;
	cout << conG;*/
	if (HaveException == false)
	{
		if (NotInDatabase == false)
		{

			
			cout << "\n\t\t\tRemove a certain amount (a) or remove completely (b) ? : ";
			cin >> choosing;
			if (choosing == "A" || choosing == "a")
			{
				if (conG > 0 || conG == 0) {
					cout << "\n\t\t\tEnter your new quantity: ";
					cin >> quantity;

					string updateprod_query = "UPDATE payment SET itemQuantity = itemQuantity - ('" + quantity + "') WHERE cartId = '" + choice + "'";
					const char* qup = updateprod_query.c_str();
					qstate = mysql_query(conn, qup);
					cout << "\n\t\t\tUPDATED.";
					system("pause");
					goto cart;
				}
				else if (conG < 0 || conG == 0) {
					
					cout << "\n\t\t\tQuantity in Cart is already 0. You cannot remove.";
					system("pause");
					goto cart;
				}
				else {
					cout << "Error.";
				}
				/*cout << "Enter your new quantity: ";
				cin >> quantity;

				string updateprod_query = "UPDATE payment SET itemQuantity = itemQuantity - ('" + quantity + "') WHERE cartId = '" + choice + "'";
				const char* qup = updateprod_query.c_str();
				qstate = mysql_query(conn, qup);
				system("pause");
				goto cart;*/

			}
			else if (choosing == "B" || choosing == "b")
			{
				string deletecart_query = "DELETE FROM payment WHERE cartId = '" + choice + "'";
				const char* qdc = deletecart_query.c_str();
				qstate = mysql_query(conn, qdc);

				if (!qstate)
				{
					cout << "\n\t\t        Product successfully removed from your cart." << endl;
					cout << "\t\t        Remove another item 'r' or proceed to order 'p' ? : ";
					cin >> choose;

					if (choose == 'r' || choose == 'R')
						goto cart;
					else if (choose == 'p' || choose == 'P')
					{
						customerCart();
						return;
					}
					else
					{
						cout << "\nPlease enter a valid option." << endl;
						system("pause");
						goto cart;
					}
				}
				else
				{
					cout << "\nFailed to remove product from your cart.\n";
				}
			}
		}
		else
		{
			cout << "Product not found in the database.\n";
			cout << "Try again? (Y/N): ";
			cin >> choose;
			if (choose == 'y' || choose == 'Y')
				goto cart;
			else
				//goto adminMenu;
				exit(EXIT_SUCCESS);

		} 
	}
}
//Checked
void customerRegister() {
	string name = "";
	string phone = "";
	string passw = "";
	string email = "";
	int choice;

	system("Registration Form");
	system("cls");
	
	printf("\t\t\t\tRegistration Form");
	cin.ignore(1, '\n');
	cout << "\n\t\t\t\tName : ";
	getline(cin, name);
	cout << "\n\t\t\t\tPhone : ";
	getline(cin, phone);
	cout << "\n\t\t\t\tPassword : ";
	getline(cin, passw);
	cout << "\n\t\t\t\tEmail : ";
	getline(cin, email);

	//Insert into DB
	string insert_query1 = "INSERT INTO customer(customerName,customerPassword,customerPhone,customerEmail) VALUES('" + name + "','" + passw + "','" + phone + "','" + email + "')";
	const char* q = insert_query1.c_str();
	qstate = mysql_query(conn, q);
	if (!qstate) {
loop:
		cout << "\n\t\t\t\tRegistration Successful.\n";
		cout << "\n\t\t\t\t[1]Login";
		cout << "\n\t\t\t\t[2]Main\n";
		cout << "\n\t\t\t\tSelect an option : ";
		cin >> choice;

		switch (choice) {
		case 1:
			login();
			break;
		case 2:
			main();
			break;
		default:
			cout << "\n\t\t\t\tPlease select an option.\n\t\t\t\t";
			goto loop;

		}
	}
	else {
		cout << "\n\t\t\t\tRegistration Failed.\t\t\t\t";
		system("pause");
		exit(EXIT_SUCCESS);
	}

}
//Checked
void customerCart() { //DISPLAY ORDERS ONLY
cart:
	system("Customer Orders");
	system("cls");
	
	string amount;
	string items[5000];
	int indexForNo = 0;
	string total;
	string continuePay;
	string descServ;
	string status = "Payment Needed";
	string stat = "Paid";

	string session_query = "SELECT * FROM customer where customerId =('" + readSession() + "')";
	const char* q = session_query.c_str();
	qstate = mysql_query(conn, q);
	res = mysql_store_result(conn);
	row = mysql_fetch_row(res);
	string a = row[1];
	string id = readSession();

	cout << "\n\t\t\t\t\t\t " << a << "'s Orders\n";

	string selectOrder_query = "SELECT * FROM ordering WHERE customerID =('" + readSession() + "')";
	const char* q1 = selectOrder_query.c_str();
	qstate = mysql_query(conn, q1);	

	if (!qstate) {
		res = mysql_store_result(conn);
		printf("\n\t\t---------------------------------------------------------------------------------------------------\n");
		printf("\t\t| %-5s | %-20s | %-10s | %-10s | %-20s | %-15s |\n", "ID", "Name", "Quantity", "Amount", "Status", "Pick Up Status");
		printf("\t\t---------------------------------------------------------------------------------------------------\n");
		while ((row = mysql_fetch_row(res)))
		{
			printf("\t\t| %-5s | %-20s | %-10s | %-10s | %-20s | %-15s |\n", row[0], row[3], row[4], row[5], row[6], row[7]);
			printf("\t\t---------------------------------------------------------------------------------------------------\n");
			items[indexForNo] = row[0];
			indexForNo++;
			descServ = row[3];
		}
	}
	else {
		cout << "Query Execution Problem !" << mysql_errno(conn) << endl;
	}
	
checkStatus:
	string check;
	int donePay;
	string checkStat_query = "SELECT status FROM ordering WHERE customerID =('" + readSession() + "') AND status =('" + status + "')";
	const char* qc = checkStat_query.c_str();
	qstate = mysql_query(conn, qc);
	if (!qstate) {
		res = mysql_store_result(conn);
		while (row = mysql_fetch_row(res)) {
			check = row[0];
			
		}
		if (check == "Payment Needed") {
			goto pay;
		}
		else if(check != "Payment Needed") {

			cout << "\n\t\t\t\t[1]Main";
			cout << "\n\t\t\t\t[2]Exit";
			cout << "\n\t\t\t\tSelect : ";
			cin >> donePay;
			switch (donePay) {
			case 1:
				cout << "\n\t\t\t\t";
				system("pause");
				customerDashboard();
				break;
			case 2:
				exit(EXIT_SUCCESS);
				break;
			default:
				customerCart();
			}
		}
	}
	else {
		cout << "ERROR";
	}

pay:
	string count_query = "SELECT SUM(amount) FROM ordering WHERE customerID =('" + readSession() + "') AND status =('" + status + "')";
	const char* q2 = count_query.c_str();
	qstate = mysql_query(conn, q2);
	if (!qstate) {
		res = mysql_store_result(conn);

		cout << "\n\t\t\t\t Amount To Pay : RM";
		while (row = mysql_fetch_row(res)) {
			printf(row[0]);
			amount = row[0];
		}
		cout << endl << endl;

		cout << "\n\t\t\t\t\tPay (y/n) : ";
		cin >> continuePay;
		if (continuePay == "y" || continuePay == "Y") {
			goto payment;
		}
		else if (continuePay == "n" || continuePay == "N") {
			customerDashboard();
		}
		else {
			goto cart;
		}
	} 
	else {
		cout << "\n\t\t\tSystem Failed.\n";
	}

payment:
	int balance;
	int pay;
	int num;
	string paid = "Paid";

	system("cls");
	cout << "\n\t\t\t\tPayment Transaction";
	string selectOrder1_query = "SELECT * FROM ordering WHERE customerID =('" + readSession() + "') AND status =('" + status + "')";
	const char* q3 = selectOrder1_query.c_str();
	qstate = mysql_query(conn, q3);

	if (!qstate) {
		res = mysql_store_result(conn);
		printf("\n\t\t\t----------------------------------------\n");
		printf("\t\t\t| %-5s | %-15s | %-10s |\n", "ID", "Name", "Amount");
		printf("\t\t\t----------------------------------------\n");
		while ((row = mysql_fetch_row(res)))
		{
			printf("\t\t\t| %-5s | %-15s | %-10s |\n", row[0], row[3], row[4]);
			printf("\t\t\t----------------------------------------\n");
			items[indexForNo] = row[0];
			indexForNo++;
		}
	}
	else {
		cout << "Query Execution Problem !" << mysql_errno(conn) << endl;
	}

	cout << "\n\t\t\t\tYou have to pay is : RM " << amount << endl;
	cout << "\t\t\t\tInsert money : RM ";
	cin >> pay;
	num = stoi(amount);
	if (pay >= num) {
		balance = pay - num;
		if (balance == 0) {
			cout << "\n\t\t\t\t0 Balance. \n\t\t\t\tThank You For Using Our Service.";
		}
		else if (pay - num) {
			cout << "\n\t\t\t\tBalance RM :" << balance << ". \n\n\t\t\t\tThank You For Using Our Service.";
		}
		
		string updateOrder_query = "UPDATE ordering SET status =  ('" + paid + "') WHERE customerId = '" + readSession() + "' AND status = '" + status + "'";
		const char* qUpd = updateOrder_query.c_str();
		qstate = mysql_query(conn, qUpd);

		if (!qstate) {
			cout << "\n\n\t\t\t\tOrders has been proceed.";
			system("pause");
			customerDashboard();
		}
		else {
			cout << "\n\t\t\t\tError.";
		}
	}
	else if (pay < num) {
		balance = num - pay;
		cout << "\n\t\t\t\tInsufficient Fund.\n\n\t\t\t\t";
		system("pause");
		goto payment;
	}
}
//Checked
void customerProfile() {

head:
	system("Profile");
	system("cls");

	string id = readSession();
	string custName, custPass, custPhone, custEmail;
	int option;
	string updateName, updatePass, updatePhone, updateEmail;

	string session_query = "SELECT * FROM customer where customerId =('" + readSession() + "')";
	const char* q = session_query.c_str();
	qstate = mysql_query(conn, q);
	res = mysql_store_result(conn);
	row = mysql_fetch_row(res);
	custName = row[1];
	custPass = row[2];
	custPhone = row[3];
	custEmail = row[4];

	cout << "\n\t\t\t\tHi, " << custName << ". Welcome to your profile." << endl;

	cout << "\n\t\t\t\t[1]Name : " << custName << endl;
	cout << "\n\t\t\t\t[2]Password : " << custPass << endl;
	cout << "\n\t\t\t\t[3]Phone : " << custPhone << endl;
	cout << "\n\t\t\t\t[4]Email : " << custEmail << endl;
	cout << "\n\t\t\t\t[5]Main" << endl;
	cout << "\n\t\t\t\t[6]Exit" << endl;
	cout << "\n\t\t\t\tSelect 1-4 to Update, 5 Main, 6 Exit : ";
	cin >> option;

	if (option == 1) {
		cout << "\n\n\t\t\t\tUpdate Your Name.\n";
		cin.ignore(1, '\n');
		cout << "\n\t\t\t\tNew Name : ";
		getline(cin, updateName);

		string updateInfo_query = "UPDATE customer SET customerName = ('" + updateName + "') WHERE customerId = '" + readSession() + "'";
		const char* qUpdate = updateInfo_query.c_str();
		qstate = mysql_query(conn, qUpdate);
		if (!qstate) {
			cout << "\n\t\t\t\tUpdate Successful.\n\t\t\t\t";
			system("pause");
			customerProfile();
		}
		else {
			cout << "\n\t\t\t\t\tError.";
		}
	}
	else if (option == 2) {
		cout << "\n\n\t\t\t\tUpdate Your Password.\n";
		cout << "\n\t\t\t\tNew Password :";
		cin >> updatePass;

		string updateInfo_query = "UPDATE customer SET customerPassword = ('" + updatePass + "') WHERE customerId = '" + readSession() + "'";
		const char* qUpdate = updateInfo_query.c_str();
		qstate = mysql_query(conn, qUpdate);
		if (!qstate) {
			cout << "\n\t\t\t\tUpdate Successful.\n\t\t\t\t";
			system("pause");
			customerProfile();
		}
		else {
			cout << "\n\t\t\t\t\tError.";
		}
	}
	else if (option == 3) {
		cout << "\n\n\t\t\t\tUpdate Your Phone Number.\n";
		cin.ignore(1, '\n');
		cout << "\n\t\t\t\tNew Phone Number :";
		getline(cin, updatePhone);

		string updateInfo_query = "UPDATE customer SET customerPhone = ('" + updatePhone + "') WHERE customerId = '" + readSession() + "'";
		const char* qUpdate = updateInfo_query.c_str();
		qstate = mysql_query(conn, qUpdate);
		if (!qstate) {
			cout << "\n\t\t\t\tUpdate Successful.\n\t\t\t\t";
			system("pause");
			customerProfile();
		}
		else {
			cout << "\n\t\t\t\t\tError.";
		}
	}
	else if (option == 4) {
		cout << "\n\n\t\t\t\tUpdate Your Email.\n";
		cin.ignore(1, '\n');
		cout << "\n\t\t\t\tNew Email :";
		getline(cin, updateEmail);

		string updateInfo_query = "UPDATE customer SET customerEmail = ('" + updateEmail + "') WHERE customerId = '" + readSession() + "'";
		const char* qUpdate = updateInfo_query.c_str();
		qstate = mysql_query(conn, qUpdate);
		if (!qstate) {
			cout << "\n\t\t\t\tUpdate Successful.\n\t\t\t\t";
			system("pause");
			customerProfile();
		}
		else {
			cout << "\n\t\t\t\t\tError.";
		}
	}
	else if (option == 5) {
		customerDashboard();
	}
	else if (option == 6) {
		destroySession();
		exit(EXIT_SUCCESS);
	}
	else {
		goto head;
	}
	
}
//Checked
void adminPro() {

	system("Admin");
	system("cls");

	string username, passw;
	char ch;

head:
	cout << "\n\t\t\t\tADMINISTRATOR ONLY";
	cout << "\n\n\t\t\t\tRequired Admin Username and Password!";
	cin.ignore(1, '\n');
	cout << "\n\n\t\t\t\tUsername : ";
	getline(cin, username);
	cout << "\n\t\t\t\tPassword : ";
	ch = _getch();
	passw = "";
	while (ch != 13) {
		if (ch != 8) {
			passw.push_back(ch);
			cout << "*";
		}
		else if (ch == 8 && passw.length() != 0) {
			passw.pop_back();
			cout << "\b\b";
		}
		ch = _getch();
	}
	
	if (username == "admin" && passw == "admin")
	{
		cout << "HARD CODE";
	}
	else
	{
		string logAdmin_query = ("SELECT * FROM staff WHERE staffUName = '" + username + "' and staffPassword = '" + passw + "'");
		const char* qAdmin = logAdmin_query.c_str();
		qstate = mysql_query(conn, qAdmin);
		if (!qstate == 1)
		{
			res = mysql_store_result(conn);
			if ((row = mysql_fetch_row(res)))
			{
				ofstream sessionFile("$ession.txt");

				if (sessionFile.is_open())
				{
					sessionFile << row[0];
					sessionFile.close();
				}
				else
				{
					cout << "Error.\n";
				}
				cout << "\n\n\t\t\t\tSuccessfully logged in.\n\n\t\t\t\t";
				system("pause");
				adminInterface();
			}
			else
			{
				cout << "\n\n\t\t\t\tWrong Credentials\n\n\t\t\t\t";
				system("pause");
				adminPro();
			}
		}
		else
		{
			cout << "Error";
		}
	}
}
//Checked
void adminInterface() { 
	system("Admin");
	system("cls");

	int indexForNo = 0;
	string items[5000];
	int selection;
	string update;
head:
	string sessionAdmin_query = "SELECT * FROM staff where staffId =('" + readSession() + "')";
	const char* q = sessionAdmin_query.c_str();
	qstate = mysql_query(conn, q);
	res = mysql_store_result(conn);
	row = mysql_fetch_row(res);
	string staffName = row[1];
	string id = readSession();

	cout << "\n\t\t\t\tHello, Staff : " << staffName;
	cout << "\n\n\t\t\t\t [1] View";
	cout << "\n\t\t\t\t [2] Add";
	cout << "\n\t\t\t\t [3] Update";
	cout << "\n\t\t\t\t [4] Report";
	cout << "\n\t\t\t\t [5] Exit";
	cout << "\n\t\t\t\tSelect : ";
	cin >> selection;

	switch (selection) {
	case 1:
		adminView();
		break;
	case 2:
		adminAdd();
		break;
	case 3:
		adminUpdate();
		break;
	case 4:
		adminReport();
		break;
	case 5:
		exit(EXIT_SUCCESS);
	default:
		system("cls");
		goto head;

	}
}
//Checked
void adminView() {
	system("Admin");
	system("cls");

	int indexForNo = 0;
	string items[5000];
	int selection;
	string update;

head:
	string sessionAdmin_query = "SELECT * FROM staff where staffId =('" + readSession() + "')";
	const char* q = sessionAdmin_query.c_str();
	qstate = mysql_query(conn, q);
	res = mysql_store_result(conn);
	row = mysql_fetch_row(res);
	string staffName = row[1];
	string id = readSession();

	cout << "\n\t\t\t\t Hello, Staff : " << staffName;
	cout << "\n\n\t\t\t\t Please Select Any Data You Want to View.";
	cout << "\n\n\t\t\t\t [1] Services";
	cout << "\n\t\t\t\t [2] Customer";
	cout << "\n\t\t\t\t [3] Orders";
	cout << "\n\t\t\t\t [4] Staff";
	cout << "\n\t\t\t\t [5] Menu";
	cout << "\n\t\t\t\t [6] Logout";
	cout << "\n\t\t\t\t Select : ";
	cin >> selection;

	
	if (selection == 1) { //Checked
		system("You have selected Services data.");
		system("cls");
		cout << "\n\t\t\t\t\t   List of Items";
		qstate = mysql_query(conn, "SELECT * FROM service");
		if (!qstate) {
			res = mysql_store_result(conn);
			printf("\n\t\t-------------------------------------------------------------------------\n");
			printf("\t\t| %-5s | %-15s | %-30s | %-10s |\n", "ID", "Name", "Description", "Price (RM)");
			printf("\t\t-------------------------------------------------------------------------\n");
			while ((row = mysql_fetch_row(res)))
			{

				printf("\t\t| %-5s | %-15s | %-30s | %-10s |\n", row[0], row[1], row[2], row[3]);
				printf("\t\t-------------------------------------------------------------------------\n");
				items[indexForNo] = row[0];
				indexForNo++;
			}
		}
		else {
			cout << "Query Execution Problem !" << mysql_errno(conn) << endl;
		}
		cout << "\n\t\t\t\t";
		
	selection:
		cout << "\n\t\t\t\tPress any key to go back to Admin Menu.\n\t\t\t\t";
		system("pause");
		adminInterface();
	}

	else if (selection == 2) { //Checked
		system("You have selected Customer data.");
		system("cls");
		cout << "\n\t\t\t\t\t   List of Customer";
		qstate = mysql_query(conn, "SELECT * FROM customer");
		if (!qstate) {
			res = mysql_store_result(conn);
			printf("\n\t\t------------------------------------------------------------------------------\n");
			printf("\t\t| %-5s | %-15s | %-15s | %-30s |\n", "ID", "Name", "Phone", "Email");
			printf("\t\t------------------------------------------------------------------------------\n");
			while ((row = mysql_fetch_row(res)))
			{
				printf("\t\t| %-5s | %-15s | %-15s | %-30s |\n", row[0], row[1], row[3], row[4]);
				printf("\t\t------------------------------------------------------------------------------\n");
				items[indexForNo] = row[0];
				indexForNo++;
			}
		}
		else {
			cout << "Query Execution Problem !" << mysql_errno(conn) << endl;
		}
		cout << "\n\t\t\t\t";
	selection2:
		cout << "\n\t\t\t\tPress any key to go back to Admin Menu.\n\t\t\t\t";
		system("pause");
		adminInterface();
	}
	
	else if (selection == 3) {
		system("You have selected Orders data.");
		system("cls");

		cout << "\n\t\t\t\t\t\t List of Orders";
		string selectOrder_query = "SELECT * FROM ordering";
		const char* q1 = selectOrder_query.c_str();
		qstate = mysql_query(conn, q1);
		if (!qstate) {
			res = mysql_store_result(conn);
			printf("\n\n\t---------------------------------------------------------------------------------------------------\n");
			printf("\t| %-5s | %-20s | %-10s | %-10s | %-20s | %-15s |\n", "ID", "Item", "Quantity", "Amount", "Status", "Pick Up Status");
			printf("\t---------------------------------------------------------------------------------------------------\n");
			while ((row = mysql_fetch_row(res)))
			{
				printf("\t| %-5s | %-20s | %-10s | %-10s | %-20s | %-15s |\n", row[0], row[3], row[4], row[5], row[6], row[7]);
				printf("\t---------------------------------------------------------------------------------------------------\n");
				items[indexForNo] = row[0];
				indexForNo++;

			}
		}
		else {
			cout << "Query Execution Problem !" << mysql_errno(conn) << endl;
		}
	selection3:
		cout << "\n\t\t\t\tUpdate ? (y/n) , Admin Menu (m) : ";
		cin >> update;
		if (update == "y" || update == "Y") {
			adminUpdate();
		}
		else if (update == "n" || update == "N") {
			system("cls");
			goto head;
		}
		else if (update == "m" || update == "M") {
			adminInterface();
		}
		else {
			goto selection3;
		}
	}

	else if (selection == 4) {
	system("You have selected Staff data.");
	system("cls");
	cout << "\n\t\t\t\t\tAdmin Data";
	qstate = mysql_query(conn, "SELECT * FROM staff");
	if (!qstate) {
		res = mysql_store_result(conn);
		printf("\n\t\t---------------------------------------------------------------\n");
		printf("\t\t| %-5s | %-15s | %-20s | %-10s |\n", "ID", "Name", "Email", "No Phone");
		printf("\t\t---------------------------------------------------------------\n");
		while ((row = mysql_fetch_row(res)))
		{
			printf("\t\t| %-5s | %-15s | %-20s | %-10s |\n", row[0], row[1], row[3], row[4]);
			printf("\t\t---------------------------------------------------------------\n");
			items[indexForNo] = row[0];
			indexForNo++;
		}
	}
	else {
		cout << "Query Execution Problem !" << mysql_errno(conn) << endl;
	}
	selection4:
		cout << "\n\t\t\t\tPress any key to go back to Admin Menu.\n\t\t\t\t";
		system("pause");
		adminInterface();
	}

	else if (selection == 5) {
		adminInterface();
	}

	else if (selection == 6) {
		destroySession();
		main();
	}

	else {
		goto head;
	}
}
//Checked
void adminAdd() {
	system("Add Services");
	system("cls");

	string itemName;
	string itemDesc;
	string itemPrice;
	int choice;

head:
	cout << "\n\t\t\t\tAdd Items";
	cin.ignore(1, '\n');
	cout << "\n\t\t\t\tItem Name : ";
	getline(cin, itemName);
	cout << "\n\t\t\t\tDescription : ";
	getline(cin, itemDesc);
	cout << "\n\t\t\t\tPrice : ";
	cin >> itemPrice;

	string insert_query1 = "INSERT INTO service(name,description,price) VALUES('" + itemName + "','" + itemDesc + "','" + itemPrice + "')";
	const char* q = insert_query1.c_str();
	qstate = mysql_query(conn, q);
	if (!qstate) {
	loop:
		cout << "\n\t\t\t\tItems Inserted.\n";
		cout << "\n\t\t\t\tPress Enter To View The Data\n\t\t\t\t";
		system("pause");
		adminView();
	}
	else {
		cout << "\n\t\t\t\tInsertion Failed\n\t\t\t\t";
		system("pause");
		system("cls");
		goto head;
	}
}
//OUT
void updateItems() {
head:
	system("cls");

	int select;
	string selection;
	string choice;
	bool HaveException = false;
	bool NotInDatabase = false;
	char choose;
	string quantity;
	int indexForNo = 0;
	string items[5000];

	cout << "\n\t\t\t\t\t     Update Items Section";
	string selectOrder_query = "SELECT * FROM service";
	const char* q1 = selectOrder_query.c_str();
	qstate = mysql_query(conn, q1);
	if (!qstate) {
		res = mysql_store_result(conn);
		printf("\n\t\t\t\t---------------------------------------------\n");
		printf("\t\t\t\t| %-5s | %-20s | %-10s |\n", "ID", "Item Name", "Price");
		printf("\t\t\t\t---------------------------------------------\n");
		while ((row = mysql_fetch_row(res)))
		{
			printf("\t\t\t\t| %-5s | %-20s | %-10s |\n", row[0], row[1], row[3]);
			printf("\t\t\t\t---------------------------------------------\n");
			items[indexForNo] = row[0];
			indexForNo++;
		}
	}
	else {
		cout << "Query Execution Problem !" << mysql_errno(conn) << endl;
	}

	try
	{
		cout << "\n\t\t     Select order ID to update, 'M' to Menu, 'X' to Logout. : ";
		cin >> choice;

		if (choice == "M" || choice == "m")
		{
			adminInterface();
			return;

		}
		else if (choice == "x" || choice == "X")
		{
			destroySession();
			main();
		}

	}
	catch (exception e)
	{
		cout << "Please enter a valid number." << endl;
		HaveException = true;
		exit(EXIT_SUCCESS);
	}
	if (HaveException == false)
	{
		stringstream streamid;
		string idid;
		streamid << choice;
		streamid >> idid;

		for (int i = 0; i < indexForNo; i++)
		{
			if (idid != items[i])
			{
				NotInDatabase = true;
			}
			else
			{
				NotInDatabase = false;
				break;
			}
		}

		if (NotInDatabase == false)
		{
			cout << "\n\t\t     Items Completed ? (y/n) : ";
			cin >> selection;

			if (selection == "y" || selection == "Y") {
				/*string updateInfo_query = "UPDATE customer SET customerName = ('" + updateName + "') WHERE customerId = '" + readSession() + "'";*/
				//string updateprod_query = "UPDATE ordering SET pickUpStatus =  ('" + readyPick + "') WHERE orderId = '" + choice + "'";
				//const char* qup = updateprod_query.c_str();
				//qstate = mysql_query(conn, qup);
				if (!qstate)
				{
					cout << "\n\t\t     Pick Up Status Updated. 'M' to Menu, 'X' to Exit";
					cin >> choose;

					if (choose == 'm' || choose == 'M') {
						adminInterface();
					}
					else if (choose == 'x' || choose == 'X') {
						destroySession();
						exit(EXIT_SUCCESS);
					}
					else
						cout << "\nPlease enter a valid choice.";
				}
				else
				{
					cout << "\n\nError adding item to cart." << mysql_errno(conn) << endl;
				}
			}
			else if (selection == "n" || selection == "N") {
				system("cls");
				goto head;
			}
		}
		else
		{
			cout << "\nThe product ID you entered does not exist." << endl;
			system("pause");
			adminInterface();

		}
	}
}
//Checked
void adminUpdate() {
head:
	system("Update");
	system("cls");
	int select;
	string selection;
	string choice;
	bool HaveException = false;
	bool NotInDatabase = false;
	char choose;
	string quantity;
	int indexForNo = 0;
	string items[5000];
	string statusPaid = "Paid and Processing";
	string readyPick = "Completed";
	string statusUnpaid = "Ordered";
	
	cout << "\n\t\t\t\t\t\tUpdate Order Section";
	cout << "\n\t\t\t\t[1] Update Payment Status";
	cout << "\n\t\t\t\t[2] Update Pick Up Status";
	cout << "\n\t\t\t\tSelect : ";
	cin >> select;

	if (select == 1){

		string selectOrder_query = "SELECT * FROM ordering WHERE status ='" + statusUnpaid + "'";
		const char* q1 = selectOrder_query.c_str();
		qstate = mysql_query(conn, q1);
		if (!qstate) {
			res = mysql_store_result(conn);
			printf("\n\t---------------------------------------------------------------------------------------------------\n");
			printf("\t| %-5s | %-20s | %-10s | %-10s | %-20s | %-15s |\n", "ID", "Item", "Quantity", "Amount", "Status", "Pick Up Status");
			printf("\t---------------------------------------------------------------------------------------------------\n");
			while ((row = mysql_fetch_row(res)))
			{
				printf("\t| %-5s | %-20s | %-10s | %-10s | %-20s | %-15s |\n", row[0], row[3], row[4], row[5], row[6], row[7]);
				printf("\t---------------------------------------------------------------------------------------------------\n");
				items[indexForNo] = row[0];
				indexForNo++;

			}
		}
		else {
			cout << "Query Execution Problem !" << mysql_errno(conn) << endl;
		}
		try
		{
			cout << "\n\t\t     Select order ID to update, 'M' to Menu, 'X' to Logout. : " ;
			cin >> choice;

			if (choice == "M" || choice == "m")
			{
				adminInterface();
				return;

			}
			else if (choice == "x" || choice == "X")
			{
				destroySession();
				main();
			}

		}
		catch (exception e)
		{
			cout << "Please enter a valid number." << endl;
			HaveException = true;
			exit(EXIT_SUCCESS);
		}
		if (HaveException == false)
		{
			stringstream streamid;
			string idid;
			streamid << choice;
			streamid >> idid;

			for (int i = 0; i < indexForNo; i++)
			{
				if (idid != items[i])
				{
					NotInDatabase = true;
				}
				else
				{
					NotInDatabase = false;
					break;
				}
			}

			if (NotInDatabase == false)
			{
				cout << "\n\t\t     Pay (y/n) : ";
				cin >> selection;

				if (selection == "y" || selection == "Y") {
					/*string updateInfo_query = "UPDATE customer SET customerName = ('" + updateName + "') WHERE customerId = '" + readSession() + "'";*/
					string updateprod_query = "UPDATE ordering SET status =  ('" + statusPaid + "') WHERE orderId = '" + choice + "'";
					const char* qup = updateprod_query.c_str();
					qstate = mysql_query(conn, qup);
					if (!qstate)
					{
						cout << "\n\t\t     Payment Status Updated. 'M' to Menu, 'X' to Exit : ";
						cin >> choose;

						if (choose == 'm' || choose == 'M') {
							adminInterface();
						}
						else if (choose == 'x' || choose == 'X') {
							destroySession();
							exit(EXIT_SUCCESS);
						}
						else
							cout << "\nPlease enter a valid choice.";
					}
					else
					{
						cout << "\n\nError adding item to cart." << mysql_errno(conn) << endl;
					}
				}
				else if (selection == "n" || selection == "N") {
					system("cls");
					goto head;
				}
			}
			else
			{
				cout << "\nThe product ID you entered does not exist." << endl;
				system("pause");
				adminInterface();

			}
		}
	}

	else if (select == 2) {
	string selectOrder_query = "SELECT * FROM ordering WHERE status ='" + statusPaid + "'";
	const char* q1 = selectOrder_query.c_str();
	qstate = mysql_query(conn, q1);
		if (!qstate) {
			res = mysql_store_result(conn);
			printf("\n\t---------------------------------------------------------------------------------------------------\n");
			printf("\t| %-5s | %-20s | %-10s | %-10s | %-20s | %-15s |\n", "ID", "Item", "Quantity", "Amount", "Status", "Pick Up Status");
			printf("\t---------------------------------------------------------------------------------------------------\n");
			while ((row = mysql_fetch_row(res)))
			{
				printf("\t| %-5s | %-20s | %-10s | %-10s | %-20s | %-15s |\n", row[0], row[3], row[4], row[5], row[6], row[7]);
				printf("\t---------------------------------------------------------------------------------------------------\n");
				items[indexForNo] = row[0];
				indexForNo++;

			}
		}
		else {
			cout << "Query Execution Problem !" << mysql_errno(conn) << endl;
		}
		try
		{
			cout << "\n\t\t     Select order ID to update, 'M' to Menu, 'X' to Logout. : ";
			cin >> choice;

			if (choice == "M" || choice == "m")
			{
				adminInterface();
				return;

			}
			else if (choice == "x" || choice == "X")
			{
				destroySession();
				main();
			}

		}
		catch (exception e)
		{
			cout << "Please enter a valid number." << endl;
			HaveException = true;
			exit(EXIT_SUCCESS);
		}
		if (HaveException == false)
		{
			stringstream streamid;
			string idid;
			streamid << choice;
			streamid >> idid;

			for (int i = 0; i < indexForNo; i++)
			{
				if (idid != items[i])
				{
					NotInDatabase = true;
				}
				else
				{
					NotInDatabase = false;
					break;
				}
			}

			if (NotInDatabase == false)
			{
				cout << "\n\t\t     Items Completed ? (y/n) : ";
				cin >> selection;

				if (selection == "y" || selection == "Y") {
					/*string updateInfo_query = "UPDATE customer SET customerName = ('" + updateName + "') WHERE customerId = '" + readSession() + "'";*/
					string updateprod_query = "UPDATE ordering SET pickUpStatus =  ('" + readyPick + "') WHERE orderId = '" + choice + "'";
					const char* qup = updateprod_query.c_str();
					qstate = mysql_query(conn, qup);
					if (!qstate)
					{
						cout << "\n\t\t     Pick Up Status Updated. 'M' to Menu, 'X' to Exit : ";
						cin >> choose;

						if (choose == 'm' || choose == 'M') {
							adminInterface();
						}
						else if (choose == 'x' || choose == 'X') {
							destroySession();
							exit(EXIT_SUCCESS);
						}
						else
							cout << "\nPlease enter a valid choice.";
					}
					else
					{
						cout << "\n\nError adding item to cart." << mysql_errno(conn) << endl;
					}
				}
				else if (selection == "n" || selection == "N") {
					system("cls");
					goto head;
				}
			}
			else
			{
				cout << "\nThe product ID you entered does not exist." << endl;
				system("pause");
				adminInterface();

			}
		}
	}
	else {
	cout << "Error.";
	}
}
//Checked
void adminReport() {
head:
	system("cls");
	
	cout << "\n\t\t\t\tLaundry Sales\n";

	string sum_query = "SELECT SUM(amount * quantity) FROM ordering";
	const char* qs = sum_query.c_str();
	qstate = mysql_query(conn, qs);
	if (!qstate)
	{
		res = mysql_store_result(conn);
		printf("\t\t-------------------------------------------");
		cout << "\n\t\t|\tYour Total Sales is RM ";

		while (row = mysql_fetch_row(res))
		{
			cout << row[0];
		}
		printf("       |");
		printf("\n\t\t-------------------------------------------");
		cout << endl << endl;
	}
	else
	{
		cout << "\nSystem failed to display your total.\n";
	}

	cout << "\n\t\tPress any key to go back to Menu.\n\t\t";
	system("pause");
	adminInterface();
}

string readSession()
{
	string sessionid;
	ifstream sessionFile("$ession.txt");

	if (sessionFile.is_open())
	{
		getline(sessionFile, sessionid);
		sessionFile.close();
	}
	else
	{
		cout << "Error opening file.\n";
	}

	return sessionid;
}

void destroySession()
{
	ofstream destroySession("$ession.txt", ofstream::out | ofstream::trunc);
	destroySession.close();
}