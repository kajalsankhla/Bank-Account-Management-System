#include "CubicProbing.h"

void CubicProbing::createAccount(std::string id, int count) {
    
    int g=hash(id);

    if(bankStorage1d.size() == 0){
       bankStorage1d.resize(1000000,{"null",0});
    }

    int x=1;
    while (bankStorage1d[g].id != "null" ){
        g = (g+(x*x*x))%99983;
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

std::vector<int> CubicProbing::getTopK(int k) {

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

int CubicProbing::getBalance(std::string id) {

    int g=hash(id);
    int x=1;
    for(int i=0;i<99983;i++){
        if(bankStorage1d[g].id == id){
            return bankStorage1d[g].balance;
            break;
        }
        g=(g+(x*x*x))%99983;
        x++;
    }

    return -1;

    // IMPLEMENT YOUR CODE HERE
    // Placeholder return value
}

void CubicProbing::addTransaction(std::string id, int count) {

    int g=hash(id);
int x=1;
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
        g=(g+x*x*x)%99983;
        x++;
    }

    if(bankStorage1d[g].id == "null"){
    createAccount(id,count);
    }
    // IMPLEMENT YOUR CODE HERE
}

bool CubicProbing::doesExist(std::string id) {

    int g=hash(id);
    int x=1;

    while(bankStorage1d[g].id != "null"){
        if(bankStorage1d[g].id == id){
            return true;
        }
        g = (g+(x*x*x))%99983;
        x++;
    }

    // IMPLEMENT YOUR CODE HERE
    return false; // Placeholder return value
}

bool CubicProbing::deleteAccount(std::string id) {

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
        g = (g+(x*x*x))%99983;
       // x++;
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
int CubicProbing::databaseSize() {
    // IMPLEMENT YOUR CODE HERE
    return v1.size(); // Placeholder return value
}

int CubicProbing::hash(std::string id) {

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
