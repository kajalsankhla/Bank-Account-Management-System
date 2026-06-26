#include "Comp.h"

void Comp::createAccount(std::string id, int count) {

    int g=hash(id);
    if (bankStorage2d.empty()){
        bankStorage2d.resize(100000);
    }
    bankStorage2d[g].push_back({id,count});
    size++;

    // IMPLEMENT YOUR CODE HERE
}

std::vector<int> Comp::getTopK(int k) {

    std::vector<int> v1;
    std::vector<int> v2;
    int x=0;
    int y=0;

    for (int i=0;i<100000;i++){
        if(bankStorage2d[x].empty()){
            x++; 
        continue;
        }
        else{
            Account account=bankStorage2d[x][y];
            v1.push_back(account.balance);

            if(y<bankStorage2d[x].size()-1){
                y++;
            }
            else{
                x++;
                y=0;
            }
        }
    }

    int n=v1.size();
    for (int i=0; i<n-1; i++) {
        for (int j=0; j<n-i-1; j++) {
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

    // IMPLEMENT YOUR CODE HERE
    return std::vector<int>(v2); // Placeholder return value
}

int Comp::getBalance(std::string id) {

    int g=hash(id);
    if(g<=bankStorage2d.size()){
    for(Account& account: bankStorage2d[g]){
        if(account.id==id){
            return account.balance;
        }
    }
    }
    else{
        return -1;
    }
    // IMPLEMENT YOUR CODE HERE
    return -1; // Placeholder return value
}

void Comp::addTransaction(std::string id, int count) {

    int g=hash(id);

    if(g>bankStorage2d.size()){
    createAccount(id,count);
    return;
    }

    else{
        for(Account& account: bankStorage2d[g]){
            if(account.id==id){
                account.balance=account.balance+count;
            }
        }
    }
    // IMPLEMENT YOUR CODE HERE
}

bool Comp::doesExist(std::string id) {

    int g=hash(id);
    if(g<=bankStorage2d.size()){
    for(Account& account: bankStorage2d[g]){
        if(account.id==id){
            return true;
        }
    }
    }
    else{
        return false;
    }
    // IMPLEMENT YOUR CODE HERE
    return false; // Placeholder return value
}

bool Comp::deleteAccount(std::string id) {

    int g=hash(id);
    int count=0;

    if(g<=bankStorage2d.size()){
            for(Account& account: bankStorage2d[g]){
                if(account.id==id){
                    bankStorage2d[g].erase(bankStorage2d[g].begin()+count);
                    break;
                }
                    count++;
    }
    size--;
    return true;
    }
    else{
        return false;
    }
    // IMPLEMENT YOUR CODE HERE
    return false; // Placeholder return value
}

int Comp::databaseSize() {
    // IMPLEMENT YOUR CODE HERE
    return size; // Placeholder return value
}

int Comp::hash(std::string id) {

    int s1=1;
    int s2=0;

    for(int i=4;i<11;i++){
        s1=s1*(int(id[i]-'0'));
    }
    for(int i=0;i<4;i++){
        s2=s2+int(id[i]);
    }

    int s3=s1*s2;
    int s4=s3%94961;

    // IMPLEMENT YOUR CODE HERE
    return s4; // Placeholder return value
}

/*
int main() {
    Comp db;

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
    db.addTransaction("BCBA7529510_0817878868", -860);
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
