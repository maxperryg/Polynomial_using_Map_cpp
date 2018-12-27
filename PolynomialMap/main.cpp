//
//  main.cpp
//  PolynomialMap
//
//  Created by Maxwell Perry Grossman on 12/9/18.
//  Copyright © 2018 Maxwell Perry Grossman. All rights reserved.
//
#include <iostream>
#include <fstream>
#include <sstream>
#include<map>
using namespace std;

void constructPolynomial(map<int, int> &polynomial, string line){
    for (int i=0; i<line.length(); i++) {
        int degree = 0;
        int coef = 0;
        string sub = "";
        
        if(line.substr(i,1) == "-"){
            stringstream(line.substr(i,2))>>coef;
            stringstream(line.substr(i+2,1))>>degree;
            polynomial.insert({degree, coef});
            //polynomial[degree]+=coef;
            i+=2;
            continue;
        }
        else{
            sub = line.substr(i,1);
            stringstream(sub)>>coef;
            sub = line.substr((i+1),1);
            stringstream(sub)>>degree;
            polynomial.insert({degree, coef});
            //polynomial[degree]+=coef;
            i+=1;
        }
    }
}

string printPoly(map<int, int> &polynomial){
    stringstream convert;
    string ans="";
    for (auto i = polynomial.rbegin(); i != polynomial.rend(); ++i){
        if(i->second==-1){
            convert<<"-";
        }else if(i->second==1){
            convert<<"+";
        }else if(i->second>1){
            convert<<"+"<<i->second;
        }else convert<<i->second;
        
        if(i->first!=1){
            convert<<"X^"<<i->first;
        }else convert<<"X";
    }
    ans =convert.str();
    if(ans.substr(0,1) == "+") ans = ans.substr(1);
    if(ans == "") cout<<0;
    return ans;
}

string addPoly(map<int, int> &left, map<int, int> &right){
    map<int, int> ans;
    auto l = left.rbegin();
    auto r = right.rbegin();
    while (l != left.rend() && r != right.rend()){
        if(l->first == r->first){
            if(l->second+r->second != 0)
                ans.insert({l->first,l->second+r->second});
            ++l;
            ++r;
        }
        else if(l->first > r->first){
            ans.insert({l->first,l->second});
            ++l;
        }
        else{
            ans.insert({r->first,r->second});
            ++r;
        }
    }
    while(l != left.rend()){
        ans.insert({l->first,l->second});
        ++l;
    }
    while(r != right.rend()){
        ans.insert({r->first,r->second});
        ++r;
    }
    return printPoly(ans);
}

string subtractPoly(map<int, int> &left, map<int, int> &right){
    map<int, int> ans;
    auto l = left.rbegin();
    auto r = right.rbegin();
    while (l != left.rend() && r != right.rend()){
        if(l->first == r->first){
            if(l->second-r->second != 0) ans.insert({l->first,l->second-r->second});
            ++l;
            ++r;
        }
        else if(l->first > r->first){
            ans.insert({l->first,l->second});
            ++l;
        }
        else{
            ans.insert({r->first,(r->second)*-1});
            ++r;
        }
    }
    while(l != left.rend()){
        ans.insert({l->first,l->second});
        ++l;
    }
    while(r != right.rend()){
        ans.insert({r->first,(r->second)*-1});
        ++r;
    }
    return printPoly(ans);
    
}

string multiplyPoly(map<int, int> &left, map<int, int> &right){
    map<int, int> ans;
    for (auto l = left.rbegin(); l != left.rend(); ++l){
        for (auto r = right.rbegin(); r != right.rend(); ++r){
            if(ans.find(l->first+r->first) != ans.end())
                ans.at(l->first+r->first)+=l->second*r->second;
            else ans.insert({l->first+r->first,l->second*r->second});
        }
    }
    return printPoly(ans);
}

int main() {
    string line;
    ifstream myfile ("/Users/MaxGrossman/Documents/C++WorkSpace/Polynomial/Polynomial/en.lproj/Numbers.txt");
    while(getline(myfile,line)){
        map<int,int> left;
        map<int,int> right;
        
        constructPolynomial(left, line);
        getline(myfile,line);
        constructPolynomial(right, line);
        
//        ofstream output("/output.txt");
        ofstream output;
        output.open("/Users/MaxGrossman/Documents/C++WorkSpace/PolynomialMap/output.txt");
        if(output.is_open()){
            output<<"left polynomial: "<<printPoly(left)<<endl;
            output<<"Right polynomial: "<<printPoly(right)<<endl;
            output<<"Sum: "<<printPoly(left)<<" + "<<printPoly(right)<<" = "<<addPoly(left, right)<<endl;
            output<<"Difference: "<<printPoly(left)<<" - ("<<printPoly(right)<<") = "<<subtractPoly(left, right)<<endl;
            output<<"Product: "<<"("<<printPoly(left)<<")("<<printPoly(right)<<") = "<<multiplyPoly(left, right)<<endl;
            output.close();
        }
        else cout<<"couldn't open the file"<<endl;
        cout<<"left polynomial: "<<printPoly(left)<<endl;
        cout<<"Right polynomial: "<<printPoly(right)<<endl;
        cout<<"Sum: "<<printPoly(left)<<" + "<<printPoly(right)<<" = "<<addPoly(left, right)<<endl;
        cout<<"Difference: "<<printPoly(left)<<" - ("<<printPoly(right)<<") = "<<subtractPoly(left, right)<<endl;
        cout<<"Product: "<<"("<<printPoly(left)<<")("<<printPoly(right)<<") = "<<multiplyPoly(left, right)<<endl;
    }
    myfile.close();
    
    return 0;
}
