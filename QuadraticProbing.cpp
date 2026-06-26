#include "QuadraticProbing.h"

void QuadraticProbing::createAccount(std::string id, int count) {
    
    int g=hash(id);

    if(bankStorage1d.size() == 0){
       bankStorage1d.resize(100000,{"null",0});
    }

    int x=1;
    while (bankStorage1d[g].id != "null" ){
        g = (g+(x*x))%99983;
        x++;
    }

    bankStorage1d[g].id = id;
    bankStorage1d[g].balance = count;
    size++;

    v1.push_back(count);

    int m=v1.size();
    for (int i=0; i<m-1; i++) {
        for (int j=0; j<m-i-1; j++) {
            if (v1[j] < v1[j + 1]) {
                int temp = v1[j];
                v1[j] = v1[j + 1];
                v1[j + 1] = temp;
            }
        }
    }

    // IMPLEMENT YOUR CODE HERE
}

std::vector<int> QuadraticProbing::getTopK(int k) {

    std::vector<int>v2;
    /*std::vector<int>v2;

    int x=0;
    while(x<99983){
        if(bankStorage1d[x].id != "null"){
        v1.push_back(bankStorage1d[x].balance);
        }
        x++;
    }
    */

    int m=v1.size();
    for (int i=0; i<m-1; i++) {
        for (int j=0; j<m-i-1; j++) {
            if (v1[j] < v1[j + 1]) {
                int temp = v1[j];
                v1[j] = v1[j + 1];
                v1[j + 1] = temp;
            }
        }
    }


    for(int i=0;i<k;i++){
        v2.push_back(v1[i]);
    }

/*
    int i = 0;
    int n = v1.size() - 1;
    while(i < k){
        v2.push_back(v1[n-i]);
        i++;
    }
*/
    // IMPLEMENT YOUR CODE HERE
    return std::vector<int>(v2); // Placeholder return value
}

int QuadraticProbing::getBalance(std::string id) {

    int g=hash(id);
    int x=1;
    for(int i=0;i<99983;i++){
        if(bankStorage1d[g].id == id){
            return bankStorage1d[g].balance;
            break;
        }
        g=(g+(x*x))%99983;
        x++;
    }

    return -1;

    // IMPLEMENT YOUR CODE HERE
    // Placeholder return value
}

void QuadraticProbing::addTransaction(std::string id, int count) {

    int g=hash(id);

    for(int i=0;i<99983;i++){
        if(bankStorage1d[g].id == id){
            int bal = bankStorage1d[g].balance;
            bankStorage1d[g].balance=bal+count;
            int new_bal=bal+count;

            for (int i=0; i<100000; i++) {
                    if (v1[i] == bal) {
                        v1.erase(v1.begin()+i);
                        v1.push_back(new_bal);
                        break;
                    }   
            }
            break;
        }
        g=(g+1)%99983;
    }

    if(bankStorage1d[g].id == "null"){
    createAccount(id,count);
    }
    // IMPLEMENT YOUR CODE HERE
}

bool QuadraticProbing::doesExist(std::string id) {

    int g=hash(id);
    int x=1;

    while(bankStorage1d[g].id != "null"){
        if(bankStorage1d[g].id == id){
            return true;
        }
        g = (g+(x*x))%99983;
        x++;
    }

    // IMPLEMENT YOUR CODE HERE
    return false; // Placeholder return value
}

bool QuadraticProbing::deleteAccount(std::string id) {

    int g=hash(id);
    int x=1;
    for(int i=0;i<99983;i++){
        if(bankStorage1d[g].id == id){
            int bal = bankStorage1d[g].balance;
            bankStorage1d[g].id="null";
            bankStorage1d[g].balance=0; 
            size--;

                for (int i=0; i<v1.size(); i++) {
                    if (v1[i] == bal) {
                        v1.erase(v1.begin()+i);
                        break;
                    }   
                } 
            return true;
        }
        g = (g+(x*x))%99983;
    }

/*
    int g=hash(id);
    int x=1;

    while(bankStorage1d[g].id != "null"){
        if(bankStorage1d[g].id == id){
            int bal = bankStorage1d[g].balance;
            bankStorage1d[g].id="null";
            bankStorage1d[g].balance=0; 
            size--;

                for (int i=0; i<v1.size(); i++) {
                    if (v1[i] == bal) {
                        v1.erase(v1.begin()+i);
                    }   
                } 
            return true;
        }
        g = (g+(x*x))%99983;
        x++;
    }
    */
    // IMPLEMENT YOUR CODE HERE
    return false; // Placeholder return value
}
int QuadraticProbing::databaseSize() {
    // IMPLEMENT YOUR CODE HERE
    return v1.size(); // Placeholder return value
}

int QuadraticProbing::hash(std::string id) {

    int s1=1;
    int s2=0;

    for(int i=4;i<11;i++){
        s1=s1*(int(id[i]-'0'));
    }
    for(int i=0;i<4;i++){
        s2=s2+int(id[i]);
    }

    int s3=s1*s2;
    int s4=s3%99983;

    // IMPLEMENT YOUR CODE HERE
    return s4; // Placeholder return value   
}
/*
int main() {
    QuadraticProbing db;
    db.createAccount("ABCD1234567_1234567890",100);
    db.createAccount("BCDA1234567_1234567890",10);
       
    std::cout<<db.databaseSize()<<std::endl;
      db.deleteAccount("ABCD1234567_1234567890");
          std::cout<<db.databaseSize()<<std::endl;
    db.deleteAccount("BCDA1234567_1234567890");
    std::cout<<db.databaseSize()<<std::endl;
   



return 0;
}
*/
/*
int main() {
    QuadraticProbing db;

    // Test Cases
    db.createAccount("CDAD7786825_7990768648", 648);
    db.createAccount("DCDA7547234_9919615552", 552);
    db.createAccount("AACB1850545_7974534788", 788);
    std::cout << "Database size: " << db.databaseSize() << std::endl;
    db.createAccount("CDBD5250777_1124276711", 711);
    db.createAccount("ABCB8377155_0656808575", 575);
    std::vector<int> topK = db.getTopK(1);
    std::cout << "Top 1 balance: " << topK[0] << std::endl;
    db.createAccount("CDDC3792028_3313680038", 38);
    db.createAccount("CBBA9574444_7470182321", 321);
    db.createAccount("DBCC4334636_8057544188", 188);
    topK = db.getTopK(3);
    std::cout << "Top 3 balances:";
    for (int balance : topK) {
        std::cout << " " << balance;
    }
    std::cout << std::endl;
    db.createAccount("BABD5741078_5109455304", 304);
    db.createAccount("BCBA7529510_0817878868", 868);
    std::cout << "Database size: " << db.databaseSize() << std::endl;
    topK = db.getTopK(1);
    std::cout << "Top 1 balance: " << topK[0] << std::endl;
        std::cout<<"teri maa ki chut"<<std::endl;
    db.addTransaction("BCBA7529510_0817878868", -860);
            std::cout << "Database size: " << db.databaseSize() << std::endl;
    int balance = db.getBalance("BCBA7529510_0817878868");
    std::cout << "Balance for account BCBA7529510_0817878868: " << balance << std::endl;
    topK = db.getTopK(1);
    std::cout << "Top 1 balance: " << topK[0] << std::endl;
    db.addTransaction("DCDA7547234_9919615552", 592);
    topK = db.getTopK(5);
    std::cout << "Top 5 balances:";
    for (int balance : topK) {
        std::cout << " " << balance;
    }
    std::cout << std::endl;
    bool deleted = db.deleteAccount("DCDA7547234_9919615552");
    std::cout << "Account DCDA7547234_9919615552 deleted: " << (deleted ? "Yes" : "No") << std::endl;
    topK = db.getTopK(4);
    std::cout << "Top 4 balances:";
    for (int balance : topK) {
        std::cout << " " << balance;
    }
    std::cout << std::endl;
    std::cout << "Database size: " << db.databaseSize() << std::endl;

    return 0;
}
*/
