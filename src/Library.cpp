//============================================================================
// Name        : Library.cpp
// Author      : Ahmed Samir
// Version     : v 1.0
// Copyright   : Your copyright notice
// Description : Library system in C++, Ansi-style
//============================================================================

#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <algorithm>
using namespace std;

struct Book {
	int id;
	string name;
	int quantity;
	map<int,int>usersBorrowedBook;
	Book() {
		quantity = 0;
		id = -1;
		name = "";
	}
	Book(int bookId, string bookName, int bookQuantity){
		id=bookId;
		name=bookName;
		quantity=bookQuantity;
	}
	bool has_prefix(string prefix) {
		if(prefix.size() > name.size()){
			return false;
		}
		for(int i=0; i<(int)prefix.size(); ++i){
			if(name[i] != prefix[i])
				return false;
		}
		return true;
	}
	void borrow(int user_id) {
		usersBorrowedBook[user_id]++;
	}
	void return_copy(int user_id){
		usersBorrowedBook[user_id]--;
		if(usersBorrowedBook[user_id]==0)
			usersBorrowedBook.erase(user_id);
	}
	bool is_available_to_borrow(){
		return quantity>0;
	}
	void print_book() {
		cout<<"Book id is: "<<id<<" && Book name is: "<< name << " && book quantity is: "<<quantity<<endl;
	}
};

struct User{
	int userId;
	string name;
	map<int,int> booksUserBorrowed;
	User(){
		userId = -1;
		name = "";
		booksUserBorrowed ={};
	}
	User(int id, string username){
		userId = id;
		name = username;
	}

	void change_user_name(string newName) {
		name = newName;
	}
	void borrow(int bookId){
		booksUserBorrowed[bookId]++;
	}
	void return_copy(int bookId){
		booksUserBorrowed[bookId]--;
		if(booksUserBorrowed[bookId]==0)
			booksUserBorrowed.erase(bookId);
	}

};
struct LibrarySystem {
	map<int,Book> books={};
	map<string,Book> namesOfBooks={};
	map<int,User> users={};
	map<string,User> usersByName={};
	void run() {
		while (true) {
			int choice = menu();

			if (choice == 1)
				add_book();
			else if (choice == 2)
				search_books_by_prefix();
			else if (choice == 3)
				print_who_borrowed_book_by_name();
			else if (choice == 4)
				print_library_by_id();
			else if (choice == 5)
				print_library_by_name();
			else if (choice == 6)
				add_user();
			else if (choice == 7)
				user_borrow_book();
			else if (choice == 8)
				user_return_book();
			else if (choice == 9)
				print_users();
			else
				break;
		}
	}


	int menu() {
		int choice = -1;
		while (choice == -1) {
			if (true) {
				cout << "\nLibrary Menu;\n";
				cout << "1) add_book\n";
				cout << "2) search_books_by_prefix\n";
				cout << "3) print_who_borrowed_book_by_name\n";
				cout << "4) print_library_by_id\n";
				cout << "5) print_library_by_name\n";
				cout << "6) add_user\n";
				cout << "7) user_borrow_book\n";
				cout << "8) user_return_book\n";
				cout << "9) print_users\n";
				cout << "10) Exit\n";
			}

			cout << "\nEnter your menu choice [1 - 10]: ";
			cin >> choice;

			if (!check_choice_validity(1,10,choice)) {
				cout << "Invalid choice. Try again\n";
				choice = -1;	// loop keep working
			}
		}
		return choice;
	}



	bool is_book_existed(int bookInfo) {
		return books.find(bookInfo) != books.end();
	}
	bool is_book_existed(std::string bookInfo) {
		return namesOfBooks.find(bookInfo) != namesOfBooks.end();
	}


	Book get_book_info(int id){
		return books[id];
	}
	Book get_book_info(string book_name){
		return namesOfBooks[book_name];
	}

	void change_book_info(int id, string name, int quantity){

		int choice=-1;
		Book temp = get_book_info(id);
		while(choice==-1) {

			cout<<"The book is already existed\n";
			cout<<"Select which info do you want to change:"<<endl;
			cout<<"1) Change the name of the book from : "<<temp.name<<" to "<< name <<endl;
			cout<<"2) Increase the quantity of "<<temp.name<<" by "<<quantity<<endl;
			cout<<"3) Exit"<<endl;

			cin>>choice;

			if(choice == 1){
				change_book_name(id,name);
			}else if(choice == 2){
				change_book_quantity(id,quantity);
			}else if(choice == 3)
				break;
			if(!check_choice_validity(1,3,choice)){
				cout<<"Invalid choice. Try again"<<endl;
				choice=-1;
			}
		}

	}


	void change_book_name(int id, string name){
		Book temp = get_book_info(id);
		namesOfBooks.erase(temp.name);
		temp.name = name;
		books[id] = temp;
		namesOfBooks[name] = temp;
	}


	void change_book_quantity(int id, int quantity){
		Book temp = get_book_info(id);
		temp.quantity = quantity;
		books[id] = temp;
		namesOfBooks[temp.name] = temp;
	}


	void add_book(){
		int id,total_quantity;
		string name;
		cout << "Enter book info: id & name & total quantity: ";
		cin >> id >> name >> total_quantity;

		if(is_book_existed(id)){
			change_book_info(id,name,total_quantity);
		}else{
			struct Book newBook(id,name,total_quantity);
			books[id] = newBook;
			namesOfBooks[name] = newBook;
		}
	}


	bool check_choice_validity(int minChoice, int maxChoice, int choice) {
		return choice >= minChoice && choice <= maxChoice;
	}


	void search_books_by_prefix() {
		string prefix="";
		bool foundResult = false;
		cin >> prefix;
		for(auto i : books){
			Book book = i.second;
			if(book.has_prefix(prefix)){
				foundResult=true;
				cout<<book.name<<" ";
			}
		}
		if(!foundResult)
			cout<<"No result!!";
		cout<<endl;
	}


	void print_library_by_id() {
		int num=1;
		if(books.size() == 0){
			cout<<"No books in the library, please add books first."<<endl;
			return;
		}
		for(auto i: books){
			Book book = i.second;
			cout<<num<<") ";
			book.print_book();
			num++;
		}
	}


	template<typename T>
	bool is_user_existed(T userId) {
		return users.find(userId) != users.end();
	}
	bool is_user_existed(std::string username) {
		return usersByName.find(username) != usersByName.end();
	}


	User get_user_info(int userId){
		return users[userId];
	}


	void change_user_info(int userId, string name) {
		int choice = -1;
		User user = get_user_info(userId);
		while(choice == -1){
			cout<<"This user is already existed."<<endl;
			cout<<"Choose which info you want to change"<<endl;
			cout<<"1) change the user name from "<<user.name<<" to "<<name<<endl;
			cout<<"2) Exit";
			cin>>choice;
			if(check_choice_validity(1,2,choice)){
				if(choice == 1){
					user.change_user_name(name);
					users[userId] = user;
				}else{
					break;
				}
			}else{
				cout<<"Invalid choice, Try again!";
				choice = -1;
			}
		}
	}


	void add_user() {
		int id;
		string name;
		cout<<"Enter user info: id && name: ";
		cin>>id>>name;
		if(is_user_existed(id)){
			change_user_info(id,name);
		}else{
			User newUser(id,name);
			users[id] = newUser;
            usersByName[name] = newUser;
		}
	}

	vector<pair<User,Book>> get_user_and_book_info(){
		int trials = 3;
		while(trials--){
			string userName,bookName;
			cout<<"Enter user name and book name: ";
			cin>>userName>>bookName;
			if(!is_book_existed(bookName)){
				cout<<"Please enter a valid book name";
				continue;
			}
			if(!is_user_existed(userName)){
				cout<<"Please enter a valid user name";
				continue;
			}
			User user = usersByName[userName];
			Book book = namesOfBooks[bookName];
			return {{user,book}};
		}
		cout<<"Please try again later"<<endl;
		return {};
	}


	void update_the_book_quantity_after_borrow(int book_id, int user_id){
		Book book = get_book_info(book_id);

		book.quantity-=1;
		book.borrow(user_id);

		books[book_id]=book;
		namesOfBooks[book.name]=book;
	}


	void update_the_users_after_borrow_book(int user_id, int book_id){
		User user = get_user_info(user_id);
		user.borrow(book_id);
		users[user_id] = user;
		usersByName[user.name] = user;
	}


	void user_borrow_book() {
		vector<pair<User,Book>> info = get_user_and_book_info();
		if(info.size() == 0)
			return;

		User user = info[0].first;
		Book book = info[0].second;

		if(!book.is_available_to_borrow()){
			cout<<"There's no enough copies of this book"<<endl;
			return;
		}

		update_the_book_quantity_after_borrow(book.id,user.userId);
		update_the_users_after_borrow_book(user.userId, book.id);
	}


	void update_the_book_quantity_after_returning(int book_id, int user_id) {
		Book book = get_book_info(book_id);

		book.quantity+=1;
		book.return_copy(user_id);

		books[book_id]=book;
		namesOfBooks[book.name]=book;
	}

	void update_the_user_after_returning(int user_id, int book_id) {
		User user = get_user_info(user_id);

		user.return_copy(book_id);

		users[user_id] = user;
		usersByName[user.name] = user;
	}

	void user_return_book(){
		vector<pair<User,Book>> info = get_user_and_book_info();
		if(info.size() == 0)
			return;

		User user = info[0].first;
		Book book = info[0].second;

		update_the_book_quantity_after_returning(book.id, user.userId);
		update_the_user_after_returning(user.userId, book.id);
	}

	void print_users() {

		if(users.size() == 0){
			cout<<"Currently, there're no users"<<endl;
			return;
		}

		for(auto i: users){
			User user = i.second;
			cout<<"User name: "<<user.name<<" and the books he/she borrowed "<<endl;
			int num = 1;
			for(auto j:user.booksUserBorrowed){
				int quantity = j.second;
				int book_id = j.first;
				Book book = get_book_info(book_id);
				cout<<num<<" )"<<"Book name: "<<book.name<<" and the quantity he/she borrowed: "<<quantity<<endl;
				num++;
			}
			cout<<endl;
		}

	}


	void print_who_borrowed_book_by_name() {
		string book_name;
		cout<<"Please write the book name: ";
		cin>>book_name;
		if(!is_book_existed(book_name)){
			cout<<"Sorry, there's no book holding this name"<<endl;
			return;
		}
		Book book = get_book_info(book_name);
		map<int,int> users_who_borrowed_book = book.usersBorrowedBook;
		if(users_who_borrowed_book.size()==0){
			cout<<"There're no users borrowed this book"<<endl;
			return;
		}
		cout<<"Users who are borrowed "<<book_name<<endl;
		int num = 1;
		for(auto i : users_who_borrowed_book) {
			User user = get_user_info(i.first);
			cout<<num<<" )"<<"User name: "<<user.name<<endl;
			num++;
		}
		cout<<endl;
	}


	void print_library_by_name() {
		if(namesOfBooks.size() == 0){
			cout<<"Currently, there're no books in the library";
			return;
		}
		int num = 1;
		for(auto i : namesOfBooks){
			Book book = i.second;
			cout<<num<<") Book name: "<<book.name<<" && book quantity: "<<book.quantity<<endl;
			num++;
		}
	}
};
int main() {
	LibrarySystem Library;
	Library.run();
	return 0;
}
