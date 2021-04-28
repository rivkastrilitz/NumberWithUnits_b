#pragma once
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <stack>
#include <cmath>



using namespace std;

namespace ariel{
    
    class NumberWithUnits{
        private:
            double number;
            string unit;
            static map<string,map<string,double>>mp;
            
            
        
        public:
            NumberWithUnits(double num,const string& str);
            
       
        static void read_units(ifstream& units);
        static double find_connection(const string& str1,const string& str2);
        friend int compare(const NumberWithUnits& num1,const NumberWithUnits& num2);

        // // // // + - *
        NumberWithUnits operator+ (); // onary
        NumberWithUnits& operator+= (const NumberWithUnits& n1);
        NumberWithUnits operator+ (const NumberWithUnits& n1);
        
        NumberWithUnits operator- (); // onary
        NumberWithUnits& operator-= (const NumberWithUnits& n1);
        NumberWithUnits operator- (const NumberWithUnits& n1);

        NumberWithUnits operator *(double d);
        friend NumberWithUnits operator *(double d,const NumberWithUnits& n1);
        
        
        bool operator <(const NumberWithUnits& n2)const;
        bool operator <=(const NumberWithUnits& n2)const;
        bool operator >(const NumberWithUnits& n2)const;
        bool operator >=(const NumberWithUnits&  n2)const;
        bool operator ==(const NumberWithUnits&  n2)const;
        bool operator !=(const NumberWithUnits& n2)const;

        // // // // prefix and postfix 
        // ++x
        NumberWithUnits& operator++();
        // x++
        NumberWithUnits operator++(int n); 
        
        // --x
        NumberWithUnits& operator--();
        // x--
        NumberWithUnits operator--(int n); 

        // // // // // //  input and output 
        friend ostream& operator << (ostream& out,const NumberWithUnits& n1);
        friend istream& operator >> (istream& in, NumberWithUnits& n1);

    };
}