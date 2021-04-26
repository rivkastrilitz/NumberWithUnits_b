#include "NumberWithUnits.hpp"



using namespace std;
using namespace ariel;


namespace ariel{

    
    static map<string,map<string,double>>mp;

    NumberWithUnits::NumberWithUnits(double num,const string str){
        this->number=num;
        this->unit=str;
    }



    NumberWithUnits n(0,"9");

    void ariel::NumberWithUnits::read_units(ifstream& units){
        // Read from the text file
        ifstream MyFile("units.txt");
        string line;

        // Use a while loop together with the getline() function to read the file line by line
        string unit1;
        string unit2;
        string num;
        while(getline(MyFile, line))
        {
            u_int i=2;
            string unit1;
            string num;
            string unit2;

            while(line[i]!='='){
               unit1+=line[i];
               i++; 
            }
            i+=2;
            while(line[i]!=' '){
               num+=line[i];
               i++; 
            }
            while(line[i]!='\0'){
               unit2+=line[i];
               i++; 
            }

            mp[unit1][unit2]=stod(num);  
            mp[unit2][unit1]=1/stod(num);
        
        }
        
        // Close the file
        MyFile.close();
    }

    static double find_connection(string str1,string str2){

        

        double convert_cost=1;
        list <string> queue;
        map<string,bool>visited;
        queue.push_back(str1);
        string curr_key;
        while(!queue.empty()){
            curr_key=queue.front();
            queue.pop_front();
            if(mp.find(curr_key)!=mp.end()){
                if(visited.find(curr_key)==visited.end()){
                    for(pair<string,double>curr_pair : mp[curr_key]){
                        
                        if(visited.find(curr_pair.first)==visited.end()){
                            queue.push_back(curr_pair.first);
                        }
                        if(curr_pair.first!=str2){
                        convert_cost*=curr_pair.second;
                        }
                        if(curr_key==str1 && curr_pair.first==str2){
                           return curr_pair.second;
                        }  
                        if(curr_key!=str1 && curr_pair.first==str2){
                            return convert_cost*curr_pair.second;
                        }
                        visited[curr_key]=true;   
                    }
                }
            }
              
        }

        return -1;
    }

    
    



    // to do compare the units 
    int compare(const NumberWithUnits& num1,const NumberWithUnits& num2){
        if(num1.number<num2.number){
           return 1;
        }
        if(num1.number>num2.number){
            return 2;
        }
        
        return 0;
    }


    // onary
    NumberWithUnits operator+ (const NumberWithUnits& n1){
        return n1;
    }

    // return n1 after changes
    NumberWithUnits operator += (const NumberWithUnits &n1 ,const NumberWithUnits& n2){
        return n;
    }
    NumberWithUnits operator+ (const NumberWithUnits& n1,const NumberWithUnits& n2){
        return n;
    }

    // onary
    NumberWithUnits operator- (const NumberWithUnits& n1){
       return NumberWithUnits (n1.number*-1,n1.unit);
    }

    // return n1 after changes
    NumberWithUnits operator-= (const NumberWithUnits& n1,const NumberWithUnits& n2){
        return n;
    }
    NumberWithUnits operator- (const NumberWithUnits& n1,const NumberWithUnits& n2){
        return n;
    }

    NumberWithUnits operator *(const NumberWithUnits& n1,double d){
        return NumberWithUnits (n1.number *d,n1.unit);
    }
            
    NumberWithUnits operator *(double d, NumberWithUnits& n1){
        return NumberWithUnits (n1.number *d,n1.unit);
    }
            

    bool operator <(const NumberWithUnits&  n1,const NumberWithUnits& n2){
        return true;
    }
    bool operator <=(const NumberWithUnits&  n1,const NumberWithUnits& n2){
        return true;
    }
    bool operator >(const NumberWithUnits& n1,const NumberWithUnits& n2){
        return true;
    }
    bool operator >=(const NumberWithUnits& n1,const NumberWithUnits& n2){
        return true;
    }
    bool operator ==(const NumberWithUnits & n1,const NumberWithUnits& n2){
        return true;
    }
    bool operator !=(const NumberWithUnits& n1,const NumberWithUnits& n2){
        return true;
    }

     // // // // prefix and postfix 
        // ++x
        NumberWithUnits operator++(NumberWithUnits& n1){
              
            return NumberWithUnits (++n1.number,n1.unit);
        }
        // x++
        NumberWithUnits operator++(NumberWithUnits& n1,int num){
            
            return NumberWithUnits (n1.number++,n1.unit);
            
        } 
        
         // --x
        NumberWithUnits operator--(NumberWithUnits& n1){
            return NumberWithUnits (--n1.number,n1.unit);
        }

        // x--
        NumberWithUnits operator--(NumberWithUnits& n1,int num){
            return NumberWithUnits (n1.number--,n1.unit);
        }
     // // // // // //  input and output 
        std::ostream& operator << (std::ostream& out,const NumberWithUnits& n1){
            out<<n1.number<<" ["<<n1.unit <<" ]"<<endl;
            return out;
        }
        std::istream& operator >>(std::istream& in, NumberWithUnits& n1){
            return in;
        }
}
