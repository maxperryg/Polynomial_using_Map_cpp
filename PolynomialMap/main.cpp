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
using namespace std;

void constructPolynomial(int polynomial[], string line){
    for (int i=0; i<line.length(); i++) {
        int degree = 0;
        int coef = 0;
        string sub = "";
        
        if(line.substr(i,1) == "-"){
            stringstream(line.substr(i,2))>>coef;
            stringstream(line.substr(i+2,1))>>degree;
            polynomial[degree]+=coef;
            i+=2;
            continue;
        }
        else{
            sub = line.substr(i,1);
            stringstream(sub)>>coef;
            sub = line.substr((i+1),1);
            stringstream(sub)>>degree;
            polynomial[degree]+=coef;
            i+=1;
        }
    }
}

void printPoly(int polynomial[]){
    stringstream convert;
    string ans="";
    for(int i = 99; i>=0; i--){
        if(polynomial[i] == 0){
            continue;
        }
        
        //if negative
        //-1 is a special case, otherwise just print the negative coefficient
        if(polynomial[i]<0){
            if (polynomial[i] == -1){
                convert<<"-";
            }
            else convert<<polynomial[i];
        }
        
        //if positive
        //1 is a special case
        if(polynomial[i]>0){
            if (polynomial[i] == 1){
                convert<<"+";
            }
            else convert<<"+"<<polynomial[i];
        }
        
        if (i==1){
            convert<<"X";
        }
        else if (i==0){
            convert<<"";
        }
        else
            convert<<"X^"<<i;
    }
    
    ans =convert.str();
    if(ans.substr(0,1) == "+") ans = ans.substr(1);
    if(ans == "") cout<<0;
    cout<<ans<<endl;
}

void addPoly(int left[], int right[]){
    int ans[100];
    for(int i=99;i>=0;i--){
        ans[i]= left[i]+right[i];
    }
    printPoly(ans);
}

void subtractPoly(int left[], int right[]){
    int ans[100];
    for(int i=99;i>=0;i--){
        ans[i]= left[i]-right[i];
    }
    printPoly(ans);
}

void multiplyPoly(int left[], int right[]){
    int ans[100];
    for(int i = 99; i>=0; i--)ans[i]=0;
    for(int i = 99; i>=0; i--){
        if(left[i]!=0){
            for(int j=99; j>=0;j--){
                if(right[j]!=0){
                    ans[i+j] += left[i]*right[j];
                }
            }
        }
    }
    printPoly(ans);
}

int main() {
    string line;
    ifstream myfile ("/Users/MaxGrossman/Documents/C++WorkSpace/Polynomial/Polynomial/en.lproj/Numbers.txt");
    while(getline(myfile,line)){
        int left[100];
        int right[100];
        for(int i=0;i<100; i++){
            left[i]=0;
            right[i]=0;
        }
        
        constructPolynomial(left, line);
        getline(myfile,line);
        constructPolynomial(right, line);
        
        printPoly(left);
        printPoly(right);
        
        addPoly(left, right);
        subtractPoly(left, right);
        multiplyPoly(left, right);
    }
    myfile.close();
    
    return 0;
}
