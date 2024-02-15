#include <bits/stdc++.h>
using namespace std;
class book {
    string name="";
    string authorName="";
    int numberOfPages{0};
    int quantity=0;
    vector<string>pages;
public:
    book(){};
    book(string name, string author,int pages,int quantity,    vector<string>page);
    //CRUD
    void setName(string name);
    string getName()const;
    void setAuthorName(string name);
    string getAuthorName()const;
    void setPagesNumber(int n);
    int getPagesNumber()const;
    void setQuantity(int q);
    int getQuantity()const;
    void Add(int number);
    void deleteA_Book();
    string showPage(int ind);
    void viewInfo();


};
book::book(string name,string author,int num,int quantity,vector<string>page)
:name(name),authorName(author),numberOfPages(num),quantity(quantity),pages(page) {}
void book::Add(int number) {quantity+=number;}
void book::deleteA_Book() {quantity--;}
void book::setName(std::string name) { this->name=name;}
string book::getName() const { return name;}
void book ::setAuthorName(std::string name) {authorName=name;}
string book::getAuthorName() const {return authorName;}
void book::setPagesNumber(int n) {numberOfPages=n;}
int book::getPagesNumber() const { return numberOfPages;}
void book::setQuantity(int q) {quantity=q;}
int book::getQuantity() const {return quantity;};
void book::viewInfo() {
    cout<<"      name : "<<getName()<<endl;
    cout<<"      number of pages : "<<getPagesNumber()<<endl;
    cout<<"      author : "<<getAuthorName()<<endl;
    cout<<"      quantity : "<<getQuantity()<<endl;
}
string book::showPage(int ind) {return pages[ind];}

class bookManager {
    vector<book>books;
    long long blackListCounter=0;
    map<string,int>getBookId;
    map<int,bool>blackList; // ids of books that need to be deleted
public:
    bookManager(); // load from database
    ~bookManager(); // load to database
     map<string,book>DataOfBook;  // database_stuff to access objects by name
    //admin database
    void loadData();
    void uploadData();
    //CRUD
    void addBook(book _book);
    void deleteBook(string bN);
    void deleteBookNumber(string bN);
    void listBooks();
    void findBook(string bookN);
    bool IsAvailable(string bookN);
};
bookManager::bookManager() {
    loadData();
}
bookManager::~bookManager() {
    uploadData();
}
void bookManager::loadData() {
    //load number of object
    // start to load the objects as following
    /*
    {
        name $
        auther $
        pages $
        Quantity $
        while(pages)vec of pages
    }
     */
    books.clear();
    blackListCounter=0;
    ifstream sin("books.txt");
    int size;
    sin>>size;
    string a,b;
    int c,d;
    for(int i=0;i<size;i++){
        sin>>a>>b>>c>>d;
        vector<string>pg;
        int cp=c;
        string p;
        while (cp--){
            sin>>p;
            pg.push_back(p);
        }
        books.push_back({a,b,c,d,pg});
        DataOfBook[a]=book(a,b,c,d,pg);
        getBookId[a]=i;
    }
    sin.close();
}
void bookManager::uploadData() {
    // check loadData() implementation to understand the uploading

    ofstream sout("books.txt");
    sout<<books.size()-blackListCounter<<endl;
    blackListCounter=0;
    int counter=0;
    for(auto i:books){
        if(blackList[counter]==1){ // deleted book
            counter++;
            continue;
        }
        sout<<i.getName()<<endl;
        sout<<i.getAuthorName()<<endl;
        sout<<i.getPagesNumber()<<endl;
        sout<<i.getQuantity()<<endl;
        int x=0;
        while (x<i.getPagesNumber()){
            sout<<i.showPage(x)<<endl;
            x++;
        }
        counter++;
    }
    sout.close();
}
void bookManager::addBook(book _book) {
    if(DataOfBook.count(_book.getName())>0){
        books[getBookId[_book.getName()]].Add(1);
    }
    else
    {
        books.push_back(_book);
    }
}
void bookManager::deleteBook(string bN) {
    books[getBookId[bN]].deleteA_Book();
    if( books[getBookId[bN]].getQuantity()==0)
    blackList[getBookId[bN]]=1;
    blackListCounter++;
}
void bookManager::deleteBookNumber(std::string bN) {
    books[getBookId[bN]].deleteA_Book();
}
void bookManager::listBooks() {
    for(auto i:books){
        i.viewInfo();
        cout<<"      ----------- "<<endl;
    }
}
void bookManager::findBook(std::string bookN) {
    string x="     book is not found..";
    for(auto i:books){
        if(i.getName()==bookN){
            i.viewInfo();
            x="-1";
        }
    }
    if(x!="-1")cout<<x<<endl;
}
bool bookManager::IsAvailable(std::string bookN) {
    return (getBookId.count(bookN))>0;
}

class session {
    string bookName;
    string userName;
    string lastReadingDate;
    int lastReadingPage;
public:
    session(string _book,string userName,string lastReadingDate,int lastReadingPage);
    session();
    void view();
    void setUserName(string name);
    void goNext_page();
    void goPrevious_page();
    void jumpTo(int number);
    string getUserName();
    int getLastPage();
    string getLastDate();
    string getBookName();

};
session::session(string book_, std::string userName, std::string lastReadingDate, int lastReadingPage):
bookName(book_),userName(userName),lastReadingDate(lastReadingDate),lastReadingPage(lastReadingPage) {}
string session::getUserName() {
    return userName;
}
string session::getLastDate() {
    return lastReadingDate;
}
int session::getLastPage() {
    return lastReadingPage;
}
string session::getBookName() {
    return bookName;
}
void session::view() {
    cout<<"      Username : "<<getUserName()<<endl;
    cout<<"      Last reading pages : "<<getLastPage()<<endl;
    cout<<"      Last reading date : "<<getLastDate()<<endl;
    cout<<"      Bookname : "<<getBookName()<<endl;
}
void session::setUserName(std::string name) {
    userName=name;
}
void session::goNext_page() {
    lastReadingPage++;
}
void session::goPrevious_page() {
    lastReadingPage--;
}
void session::jumpTo(int number) {
    lastReadingPage=number;
}

class sessionManager {
    vector<session>sessions;
    long long blackListCounter=0;
    map<pair<string,string>,int>getSessionId; // access id by username & bookname
    map<int,bool>blackList; // ids of sessions that need to be deleted
public:
    sessionManager(); //loadFrom_database
    ~sessionManager(); //loadInto_database
    //sessions database
    void loadData();
    void uploadData();
    //crud
    void goNext_page(int ind);
    void goPrevious_page(int ind);
    void jumpTo(int ind,int inx);
    void setLastPage(int ind);
    void viewA_session(string bookN,string userName);
    void listSessionsOfUser(string userName);
    void addA_session(string bookN,string userName);
    void deleteAsession(string bookN,string userName);
    void runA_session(string bookN,string userName);
};
void sessionManager::uploadData() {
    // check loadData() implementation to understand the uploading

    ofstream sout("sessions.txt");

    sout<<sessions.size()-blackListCounter<<endl;
    blackListCounter=0;
    int counter=0;
    for(auto i:sessions){
        if(blackList[counter]!=1){ // deleted session
            sout<<i.getBookName()<<endl;
            sout<<i.getUserName()<<endl;
            sout<<i.getLastDate()<<endl;
            sout<<i.getLastPage()<<endl;
        }
        counter++;
    }
    sessions.clear();
    blackList.clear();
    getSessionId.clear();
    sout.close();
}
void sessionManager::loadData() {
    // load number of objects
    // start loading as following
    /*
      string bookName;
      string userName;
      string lastReadingDate;
      int    lastReadingPage;
     */
    sessions.clear();
    blackList.clear();
    blackListCounter=0;
    getSessionId.clear();
    ifstream sin("sessions.txt");
    int size;
    sin>>size;
    string b,u,ld;
    int lp;
    for(int i=0;i<size;i++){
        sin>>b>>u>>ld>>lp;
        sessions.push_back(session(b,u,ld,lp));
        getSessionId[{u,b}]=i;
    }
    sin.close();
}
sessionManager::sessionManager() {
    loadData();
}
sessionManager::~sessionManager() {
    uploadData();
}
void sessionManager::viewA_session(std::string bookN, std::string userName) {
    if(getSessionId.count({userName,bookN})==0){
        cout<<"      Y have no sessions of this book "<<endl;
    }
    else{
        sessions[ getSessionId[{userName,bookN}]].view();
    }
}
void sessionManager::listSessionsOfUser(std::string userName) {
    for(auto i:sessions){
        if(i.getUserName()==userName){
            i.view();
            cout<<"      ----------- "<<endl;
        }
    }
}
void sessionManager::deleteAsession(std::string bookN, std::string userName) {
    if(getSessionId.count({userName,bookN})==0){
        cout<<"      Y dont have such a session "<<endl;
    }
    else{
        blackList[getSessionId[{userName,bookN}]]=1;
        blackListCounter++;
        bookManager bmanager;
       book bb= bmanager.DataOfBook[bookN];
        bmanager.addBook(bb);
    }
}
void sessionManager::addA_session(std::string bookN, std::string userName) {
    bookManager bmanager;
    if(bmanager.IsAvailable(bookN)==0){
        cout<<"      Their is no such a book "<<endl;
    }
    else{
        sessions.push_back(session(bookN,userName,"today",0));
        bmanager.deleteBookNumber(bookN);
        cout<<"      Session is Added successfuly... "<<endl;
    }
}

void sessionManager::goNext_page(int ind) {
    sessions[ind].goNext_page();
 }
void sessionManager::goPrevious_page(int ind) {
    sessions[ind].goPrevious_page();
}

void sessionManager::jumpTo(int ind,int inx) {
    sessions[ind].jumpTo(inx);
}
/*
void sessionManager::setLastDate(std::string last) {
    lastReadingDate=last;
}
void sessionManager::setLastPage(int last) {
    lastReadingPage=last;
}
*/
void sessionManager::runA_session(std::string bookN, std::string userName) {
    if(getSessionId.count({userName,bookN})==0){
        cout<<"      Y have no sessions of this book "<<endl;
    }
    else{
          bookManager bManager;
          int curSession=getSessionId[{userName,bookN}];
        while (true){
            cout<<" Session MENU:"<<endl;
            cout<<"     1: show Current page"<<endl;
            cout<<"     2: Go to next page"<<endl;
            cout<<"     3: Go to previous page"<<endl;
            cout<<"     4: Jump to a page"<<endl;
            cout<<"     5: Close Session"<<endl;
            int ind;
            cin>>ind;
            if(ind==1){
                cout<<"Page number: "<<sessions[curSession].getLastPage()+1<<"    Content: ";
               cout<< bManager.DataOfBook[bookN].showPage(sessions[curSession].getLastPage())<<endl;
            }
            if(ind==2){
                if(sessions[curSession].getLastPage()+1<bManager.DataOfBook[bookN].getPagesNumber()){
                    goNext_page(curSession);
                    cout<<"Current Page number: [ "<<sessions[curSession].getLastPage()+1<<" - "
                                            <<bManager.DataOfBook[bookN].getPagesNumber()<<" ]"<<endl;
                }
                else{
                    cout<<"     this is already the last page... "<<endl;
                }
            }
            if(ind==3){
                if(sessions[curSession].getLastPage()>=0){
                    goPrevious_page(curSession);
                    cout<<"Current Page number: [ "<<sessions[curSession].getLastPage()+1<<" - "
                        <<bManager.DataOfBook[bookN].getPagesNumber()<<" ]"<<endl;
                }
                else{
                    cout<<"     this is already the first page... "<<endl;
                }
            }
            if(ind==4){
                cout<<"      Enter the number of the page "<<endl;
                int inx;
                cin>>inx;
                if(inx-1>bManager.DataOfBook[bookN].getPagesNumber()){
                    cout<<"      This number is greater then the book pages number "<<endl;
                }
                else{
                    jumpTo(curSession,inx-1);
                    cout<<"Current Page number: [ "<<sessions[curSession].getLastPage()+1<<" - "
                        <<bManager.DataOfBook[bookN].getPagesNumber()<<" ]"<<endl;
                }
            }
            if(ind==5){
                break;
            }
        }
    }
}


class admin {
    string Name;
    string userName;
    string Password;
    int numberOfAddedBooks=0;
public:
    admin();
    admin(string name,string user, string pass,int numberOfAddedBooks);

    void setName(string name);
    string getName()const;
    void setUserName(string username);
    string getUserName()const;
    void setPassword(string password);
    string getPassword()const;
    int getNumOfAddedBooks()const;
    string viewProfile();
    void addBook();
    void deleteA_book();
    //  void logout();
    // list books
    // search
};
admin::admin() {}
admin::admin(std::string name, std::string user, std::string pass,int numberOfAddedBooks)
:userName(user),Name(name),Password(pass),numberOfAddedBooks(numberOfAddedBooks) {}
void admin::setName(std::string name) {
    this->Name=name;
}
string admin::getName() const {
    return Name;
}
void admin::setUserName(string username){
    this->userName=username;
}
string admin::getUserName()const{
    return userName;
}
void admin::setPassword(string password){
    this->Password=password;
}
string admin::getPassword()const{
    return Password;
}
int admin::getNumOfAddedBooks() const
{return numberOfAddedBooks;}
string admin::viewProfile() {
    string prof="",en="\n";
    prof+="     Name: ";
    prof+=getName() +en;
    prof+="     UserName: ";
    prof+=getUserName()+en;
    prof+="     Password: ";
    prof+=getPassword()+en ;
    prof+="     Number of Added Books: ";
    prof+= to_string(numberOfAddedBooks)+en ;
    return prof;
}
void admin::addBook() {
   numberOfAddedBooks++;
}
void admin::deleteA_book()
{numberOfAddedBooks--;}


class adminManager{

    vector<admin>admins;
    string adminKey;  // y give if y are signing up as an admin and only admins can modify
    map<string,admin>DataOfUser;  // database_stuff to access objects by username
    map<string,int>getUserId; // get id by username
public:
    adminManager();  //loadFrom_database
    ~adminManager(); //loadInto_database
    //admin database
    void loadData();
    void uploadData();
    //CRUD
    void DoLogIn();
    void DOSignIn();
    void viewProfile(int id);
    void setName(int id);
    string getName()const;
    void setUserName(int id);
    string getUserName()const;
    void setPassword( int id);
    string getPassword()const;
    void addBook(int id);
    void deleteA_Book(int id);
    // running as interface
    void run(int id);


};
adminManager::adminManager() {
    loadData();
}
adminManager::~adminManager() {
    uploadData();
}
void adminManager::loadData() {
    //load number of object
    //load the admin-key
    // start to load the objects as following
    /*
    {
        name $
        username $
        password $
        numberOfAddedBooks
    }
     */
    admins.clear();
    ifstream sin("admins.txt");
    int size,numberOfAddedBook=0;
    sin>>size;
    sin>>adminKey;
    string a,b,c;
    for(int i=0;i<size;i++){
        sin>>a>>b>>c>>numberOfAddedBook;
        admins.push_back({a,b,c,numberOfAddedBook});
        DataOfUser[b]=admin(a,b,c,numberOfAddedBook);
        getUserId[b]=i;
    }
    sin.close();
}
void adminManager::uploadData() {
    // check loadData() implementation to understand the uploading
    ofstream sout("admins.txt");
    sout<<admins.size()<<endl;
    sout<<adminKey<<endl;
    for(auto i:admins){
        sout<<i.getName()<<endl;
        sout<<i.getUserName()<<endl;
        sout<<i.getPassword()<<endl;
        cout<<i.getNumOfAddedBooks()<<endl;
    }
    sout.close();
}
void adminManager::DOSignIn() {
    while (true){
        cout<<"     ENTER the Key of admins: "<<endl;
        string key;
        cin>>key;
        if(key!=adminKey){
            cout<<"     Invalid key, Please choose 1 try again or -1 to Cancel:  "<<endl;
            int ch; cin>>ch;
            if(ch!=1)break;
            continue;
        }
        string n,u,p;
        cout<<"     ENTER YOUR NAME"<<endl;
        cin>>n;
        cout<<"     ENTER YOUR USERNAME"<<endl;
        cin>>u;
        cout<<"     ENTER YOUR PASSWORD"<<endl;
        cin>>p;
        if( DataOfUser.count(u)==0){
            admin _admin(n,u,p,0);
            admins.push_back(_admin);
            getUserId.clear();
            DataOfUser.clear();
            uploadData(); // to save the new object in database
            break;
        }
        else{
            cout<<"     THE USERNAME ALREADY EXIST...PLEASE TRY AGAIN WITH A DIFFERENT ONE..."<<endl;
            cout<<"     ENTER -1 to GO Back or 1 to Continue"<<endl;
            int x;  cin>>x;
            if(x==-1)break;
            continue;
        }
    }
}
void adminManager::DoLogIn() {
    loadData();
    while (true){
        string u,p;

        cout<<"     ENTER YOUR USERNAME"<<endl;
        cin>>u;
        cout<<"     ENTER YOUR PASSWORD"<<endl;
        cin>>p;
        if( DataOfUser.count(u)==0){
            cout<<"     THE USERNAME DOES NOT EXIST...PLEASE TRY AGAIN WITH A DIFFERENT ONE..."<<endl;
            cout<<"     ENTER -1 to GO Back or 1 to Continue"<<endl;
            int x;  cin>>x;
            if(x==-1)break;
            continue;        }
        else{
            if(DataOfUser[u].getPassword()!=p)
            {
                cout<<"     THE PASSWORD IS NOT CORRECT...PLEASE TRY AGAIN.."<<endl;
                cout<<"     ENTER -1 to GO Back or 1 to Continue"<<endl;
                int x;  cin>>x;
                if(x==-1)break;
                continue;
            }
            else{
                cout<<"   Welcome "<< u <<endl;
                run(getUserId[u]);
                break;
            }
        }
    }
}
void adminManager::viewProfile(int id) {
    cout<<" My profile:"<<endl;
    cout<<admins[id].viewProfile()<<endl;
}
void adminManager::setName(int id) {
    cout<<"     Enter the new name"<<endl;
    string newN;    cin>>newN;
    admins[id].setName(newN);
    cout<<"     Name is Successfully changed.  "<<endl;
    cout<<"      ----------- \n"<<endl;

    uploadData();
    loadData();
}
void adminManager::setUserName(int id) {
    cout<<"     Enter the new Username"<<endl;
    string newN;    cin>>newN;
    admins[id].setUserName(newN);
    cout<<"     UserName is Successfully changed.  "<<endl;
    cout<<"      ----------- \n"<<endl;
    uploadData();
    loadData();
}
void adminManager::setPassword(int id) {
    cout<<"     Enter the Password"<<endl;
    string newN;    cin>>newN;
    admins[id].setPassword(newN);
    cout<<"     Password is Successfully changed.  "<<endl;
    cout<<"      ----------- \n"<<endl;
    uploadData();
    loadData();
}
void adminManager::addBook(int id) {
    cout<<"     Enter the book name"<<endl;
    string bN;    cin>>bN;
    cout<<"     Enter the book auther name"<<endl;
    string auN;    cin>>auN;
    cout<<"     Enter the number of Pages"<<endl;
    int num;    cin>>num;
    vector<string>pg(num);
    for(int i=0;i<num;i++){
        cout<<"     Enter page number "<<i+1<<endl;
        cin>>pg[i];
    }
    bookManager manageR;
    manageR.addBook(book(bN,auN,num,1,pg));
    admins[id].addBook();
    cout<<"     New book is Successfully added.  "<<endl;
    cout<<"      ----------- \n"<<endl;
    uploadData();
    loadData();
}
void adminManager::deleteA_Book(int id) {
    cout<<"     Enter the book name"<<endl;
    string bN;    cin>>bN;
    bookManager manageR;
    manageR.deleteBook(bN);
    admins[id].deleteA_book();
    cout<<"     A book is Successfully Deleted.  "<<endl;
    cout<<"      ----------- \n"<<endl;
    uploadData();
    loadData();
}
void adminManager::run(int id) {
    while (true){
        cout<<" Admin Actions MENU:"<<endl;
        cout<<"     1: View Profile"<<endl;
        cout<<"     2: Change Name"<<endl;
        cout<<"     3: Change UserName"<<endl;
        cout<<"     4: Change Password"<<endl;
        cout<<"     5: Add a New Book"<<endl;
        cout<<"     6: Delete A Book"<<endl;
        cout<<"     7: EXIT"<<endl;

        int choice; cin>>choice;
        if(choice==1){
            viewProfile(id);
        }
        if(choice==2){
            setName(id);
        }
        if(choice==3){
            setUserName(id);
        }
        if(choice==4){
            setPassword(id);
        }
        if(choice==5){
            addBook(id);
            //need to find a bookManager to load data of book and do operations of adding and deleting
        }
        if(choice==6){
            deleteA_Book(id);
        }
        if(choice==7){
            break;
        }
    }
}

class customer{
    vector<session>sessions;
    string Name;
    string userName;
    string Password;
    int numberOfBoughtBooks=0;
public:
    customer(){};
    customer(string name,string user, string pass,int num);

    void setName(string name);
    string getName()const;
    void setUserName(string username);
    string getUserName()const;
    void setPassword(string password);
    string getPassword()const;
    void addA_session();
    void deleteA_session();
    int getNumberOfSessions();

    string viewProfile();
    //  void listCurrentSystemBooks();
    //search for a book

};
customer::customer(std::string name, std::string user, std::string pass,int num):Name(name),userName(user),Password(pass),numberOfBoughtBooks(num) {}
void customer::setName(std::string name) {
    this->Name=name;
}
void customer::addA_session() {numberOfBoughtBooks++;}
void customer::deleteA_session() {numberOfBoughtBooks--;}
int customer::getNumberOfSessions() {return numberOfBoughtBooks;}
string customer::getName() const {
    return Name;
}
void customer::setUserName(string username){
    this->userName=username;
}
string customer::getUserName()const{
    return userName;
}
void customer::setPassword(string password){
    this->Password=password;
}
string customer::getPassword()const{
    return Password;
}
string customer::viewProfile() {
    string prof="",en="\n";
    prof+="     Name: ";
    prof+=getName() +en;
    prof+="     UserName: ";
    prof+=getUserName()+en;
    prof+="     Password: ";
    prof+=getPassword()+en ;
    prof+="     Number of Added Books: ";
    prof+= to_string(getNumberOfSessions())+en ;
    return prof;

}

class customerManager {
    vector<customer>customers;
    map<string,customer>DataOfUser;  // database_stuff to access objects by username
    map<string,int>getUserId;  // get id by username
public:
     customerManager(); //loadFrom_database
    ~customerManager(); //loadInto_database
    //customer database
    void loadData();
    void uploadData();
    //CRUD
    void DoLogIn();
    void DOSignIn();
    void viewProfile(int id);
    void setName(int id);
    string getName()const;
    void setUserName(int id);
    string getUserName(int id)const;
    void setPassword( int id);
    string getPassword(int id)const;

    void openA_session(int ind);
    void viewA_Session(int id);
    void listMySessions(int id);
    void removeA_Session(int id);
    void addA_Session(int id);
    void listCurrentSystemBooks();
    void search_ForA_Book();
    // running as GUI
    void run(int id);
};
customerManager::customerManager() {
    loadData();
}
customerManager::~customerManager() {
    uploadData();
}
string customerManager::getUserName(int id) const {
    return customers[id].getUserName();
}
void customerManager::loadData() {
    // load number of objects
    // start loading as following
    /*
     * string Name;
     * string userName;
     * string Password;
     * int numberOfBoughtBooks;
     */
    customers.clear();
    ifstream sin("customers.txt");
    int size;
    sin>>size;
    string n,u,p;
    int num;
    for(int i=0;i<size;i++){
        sin>>n>>u>>p>>num;
        customer x(n,u,p,num);
        customers.push_back(x);
        DataOfUser[u]=x;
        getUserId[u]=i;
    }
    sin.close();
}
void customerManager::uploadData() {
    // check loadData() implementation to understand the uploading
    ofstream sout("customers.txt");
    sout<<customers.size()<<endl;
    for(auto i:customers){
        sout<<i.getName()<<endl;
        sout<<i.getUserName()<<endl;
        sout<<i.getPassword()<<endl;
        sout<<i.getNumberOfSessions()<<endl;
    }
    sout.close();
}
void customerManager::DOSignIn() {
    while (true){
        string n,u,p;
        cout<<"     ENTER YOUR NAME"<<endl;
        cin>>n;
        cout<<"     ENTER YOUR USERNAME"<<endl;
        cin>>u;
        cout<<"     ENTER YOUR PASSWORD"<<endl;
        cin>>p;
        if( DataOfUser.count(u)==0){
            customer _customer(n,u,p,0);
            customers.push_back(_customer);
            DataOfUser.clear();
            getUserId.clear();
            uploadData(); // to save the new object in database
            break;
        }
        else{
            cout<<"     THE USERNAME ALREADY EXIST...PLEASE TRY AGAIN WITH A DIFFERENT ONE..."<<endl;
            cout<<"     ENTER -1 to GO Back or 1 to Continue"<<endl;
            int x;  cin>>x;
            if(x==-1)break;
            continue;
        }
    }
}
void customerManager::DoLogIn() {
    loadData();
    while (true){
        string u,p;
        cout<<"     ENTER YOUR USERNAME"<<endl;
        cin>>u;
        cout<<"     ENTER YOUR PASSWORD"<<endl;
        cin>>p;
        if( DataOfUser.count(u)==0){
            cout<<"     THE USERNAME DOES NOT EXIST...PLEASE TRY AGAIN WITH A DIFFERENT ONE..."<<endl;
            cout<<"     ENTER -1 to GO Back or 1 to Try again.."<<endl;
            int x;  cin>>x;
            if(x==-1)break;
            else
            continue;
        }
        else{
            if(DataOfUser[u].getPassword()!=p)
            {
                cout<<"     THE PASSWORD IS NOT CORRECT...PLEASE TRY AGAIN.."<<endl;
                cout<<"     ENTER -1 to GO Back or 1 to Try again.."<<endl;
                int x;  cin>>x;
                if(x==-1)break;
                continue;
            }
            else{
                cout<<"   Welcome "<< u <<endl;
                run(getUserId[u]);
                break;
            }
        }

    }
}
void customerManager::viewProfile(int id) {
    cout<<" My profile:"<<endl;
    cout<<customers[id].viewProfile();
    cout<<"      ----------- "<<endl;
}
void customerManager::setName(int id) {
    cout<<"     Enter the new name"<<endl;
    string newN;    cin>>newN;
    customers[id].setName(newN);
    cout<<"     Name is Successfully changed.  "<<endl;
    cout<<"      ----------- \n"<<endl;
    uploadData();
    loadData();
}
void customerManager::setUserName(int id) {
    cout<<"     Enter the new Username"<<endl;
    string newN;    cin>>newN;
    customers[id].setUserName(newN);
    cout<<"     UserName is Successfully changed.  "<<endl;
    cout<<"      ----------- \n"<<endl;
    uploadData();
    loadData();
}
void customerManager::setPassword(int id) {
    cout<<"     Enter the Password"<<endl;
    string newN;    cin>>newN;
    customers[id].setPassword(newN);
    cout<<"     Password is Successfully changed.  "<<endl;
    cout<<"      ----------- \n"<<endl;
    uploadData();
    loadData();
}
void customerManager::listCurrentSystemBooks() {
    bookManager manager_;
    manager_.listBooks();
}
void customerManager::search_ForA_Book() {
    cout<<"      Enter the name of the book : "<<endl;
    string bN;
    cin>>bN;
    bookManager bM;
    bM.findBook(bN);
    cout<<"      ----------- "<<endl;
}
void customerManager::viewA_Session(int id) {
    cout<<"     Enter the name of the book in session"<<endl;
    string bookN;
    cin>>bookN;
    sessionManager smanager;
    smanager.viewA_session(bookN,getUserName(id));
    cout<<"      ----------- "<<endl;

}
void customerManager::listMySessions(int id) {
    sessionManager smanager;
    smanager.listSessionsOfUser(getUserName(id));
}
void customerManager::addA_Session(int id) {
    cout<<"     Enter the book name"<<endl;
    string bookName;
    cin>>bookName;
    sessionManager smanager;
    smanager.addA_session(bookName,getUserName(id));
    customers[id].addA_session();
    cout<<"      ----------- \n"<<endl;
    uploadData();
    loadData();
}
void customerManager::removeA_Session(int id) {
    cout<<"     Enter the book name"<<endl;
    string bookName;
    cin>>bookName;
    sessionManager smanager;
    smanager.deleteAsession(bookName,getUserName(id));
    cout<<"     A session is Successfully deleted.  "<<endl;
    cout<<"      ----------- \n"<<endl;
    uploadData();
    loadData();
    customers[id].deleteA_session();
}
void customerManager::openA_session(int ind) {
    sessionManager smanager;
    cout<<"     Enter the book name"<<endl;
    string bn;
    cin>>bn;
    smanager.runA_session(bn,customers[ind].getUserName());
}
void customerManager::run(int id) {
    while (true){
        cout<<" Customer Actions MENU:"<<endl;
        cout<<"     1: View Profile"<<endl;
        cout<<"     2: Change Name"<<endl;
        cout<<"     3: Change UserName"<<endl;
        cout<<"     4: Change Password"<<endl;
        cout<<"     5: List Current books"<<endl;
        cout<<"     6: Search for A Book"<<endl;
        cout<<"     7: View A Session"<<endl;
        cout<<"     8: View my Sessions"<<endl;
        cout<<"     9: Add A Sessions"<<endl;
        cout<<"     10: Delete A Sessions"<<endl;
        cout<<"     11: Open A Session"<<endl;

        cout<<"     12: EXIT"<<endl;

        int choice; cin>>choice;
        cout<<"      ----------- "<<endl;

        if(choice==1){
            viewProfile(id);
        }
        if(choice==2){
            setName(id);
        }
        if(choice==3){
            setUserName(id);
        }
        if(choice==4){
            setPassword(id);
        }
        if(choice==5){
            listCurrentSystemBooks();
        }
        if(choice==6){
            search_ForA_Book();
        }
        if(choice==7){
            viewA_Session(id);
        }
        if(choice==8){
            listMySessions(id);
        }
        if(choice==9){
            addA_Session(id);
        }
        if(choice==10){
            removeA_Session(id);
        }
        if(choice==11){
            openA_session(id);
        }
        if(choice==12){
            break;
        }
    }
}

class OnlineReaderRunner {
public:
    OnlineReaderRunner();
    void run();
};
OnlineReaderRunner::OnlineReaderRunner() {}
void OnlineReaderRunner::run() {
    while (true){
        cout<<" START MENU:"<<endl;
        cout<<"     1: JOIN US AS AN ADMIN"<<endl;
        cout<<"     2: JOIN US AS A USER"<<endl;
        cout<<"     3: EXIT"<<endl;
        int in;
        cin>>in;
        if(in==1)
        {
            while (true){
                cout<<" ADMIN MENU:"<<endl;
                cout<<"     1: SIGN UP"<<endl;
                cout<<"     2: LOG IN"<<endl;
                cout<<"     3: BACK TO START"<<endl;
                int inA;
                cin>>inA;
                if(inA==1){
                    adminManager _admin_;
                    _admin_.DOSignIn();
                    continue;
                }
                else if(inA==2){
                    adminManager _admin_;
                    _admin_.DoLogIn();
                    break;
                }
                else if(inA==3){
                    break;
                }
                else{
                    cout<<"     INVALID CHOICE...PLEASE TRY AGAIN..."<<endl;
                    continue;
                }
            }
        }
        else if(in==2)
        {
            while (true){
                cout<<" USER MENU:"<<endl;
                cout<<"     1: SIGN UP"<<endl;
                cout<<"     2: LOG IN"<<endl;
                cout<<"     3: BACK TO START"<<endl;
                int inU;
                cin>>inU;
                if(inU==1){
                    customerManager user;
                    user.DOSignIn();
                }
                else if(inU==2){
                    customerManager user;
                    user.DoLogIn();
                }
                else if(inU==3){
                    break;
                }
                else{
                    cout<<"     INVALID CHOICE...PLEASE TRY AGAIN..."<<endl;
                    continue;
                }
            }
        }
        else if(in==3)
        {
            cout<<"     Bye bye..."<<endl;
            break;
        }
    }
}

int main() {
    OnlineReaderRunner Runner;
    Runner.run();
    return 0;
}