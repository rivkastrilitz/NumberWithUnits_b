#include "NumberWithUnits.hpp"



using namespace std;
using namespace ariel;



namespace ariel{

     const double EPS=0.0001;
    map <string,map<string,double>> NumberWithUnits::mp;

    NumberWithUnits::NumberWithUnits(double num,const string& str){
        if(NumberWithUnits::mp.find(str)==NumberWithUnits::mp.end()){
            throw invalid_argument ("this unit does not exists in map - cant create this num");
        }
        this->number=num;
        this->unit=str;    
    }


    void NumberWithUnits::read_units(ifstream& units){
       
        string line;

        // Use a while loop together with the getline() function to read the file line by line
        string unit1;
        string unit2;
        string num;
        while(getline(units, line))
        {
            u_int i=2;
            string unit1;
            string num;
            string unit2;

            while(line[i]!=' '){
               unit1+=line[i];
               i++; 
            }
            i+=3;
            while(line[i]!=' '){
               num+=line[i];
               i++; 
            }
            i++;
            while(line[i]!='\0'){
               unit2+=line[i];
               i++; 
            }

            NumberWithUnits::mp[unit1][unit2]=stod(num);  
            NumberWithUnits::mp[unit2][unit1]=1/stod(num);
            NumberWithUnits::mp[unit1][unit1]=1;
            NumberWithUnits::mp[unit2][unit2]=1;
        
        }
         
    }

    double NumberWithUnits::find_connection(const string& str1,const string& str2){
     
        map<string,double>convert;
        stack<string>st;
        st.push(str1);
        convert[str1]=1;
        while (!st.empty()){
           string curr_key=st.top();
           st.pop();
           for(pair<string,double>curr_pair:NumberWithUnits::mp[curr_key]){
               if(convert.find(curr_pair.first)==convert.end()&& NumberWithUnits::mp.find(curr_pair.first)!=NumberWithUnits::mp.end()){
               st.push(curr_pair.first);
               }
               convert[curr_pair.first]=curr_pair.second*convert[curr_key];
               if(curr_pair.first==str2){
                   return convert[curr_pair.first];
               }
           }

        }
        
       return -1;
    }


    
    
    int compare(const NumberWithUnits& num1,const NumberWithUnits& num2){
        double convert=NumberWithUnits::find_connection(num2.unit,num1.unit);
        if(convert==-1){
            throw invalid_argument("can't compare unrelated unites"); 
        }
        if(num1.unit==num2.unit){
            if(abs(num1.number-num2.number)<EPS){
                return 0;
            }else if(num1.number>num2.number){
                return 1;
            }else if(num1.number<num2.number ){
                return -1;   
            }

        }else{
            if(abs(num1.number-num2.number*convert)<EPS){
                return 0;
            }else if(num1.number>num2.number*convert){
                return 1;
            }else if(num1.number<num2.number*convert){
                return -1;
            }
        }
        return 2;  
    }



    // onary
    NumberWithUnits NumberWithUnits:: operator+ (){
        return NumberWithUnits(this->number,this->unit);
    }

    // return this after changes
    NumberWithUnits& NumberWithUnits::operator += (const NumberWithUnits &n1 ){
        double convert=NumberWithUnits::find_connection(n1.unit,this->unit);
         if(convert==-1){
            throw invalid_argument("cant sum unrelated units"); 
        }else{
            this->number+=n1.number*convert;
            return *this;
            
        }
       
    }
    NumberWithUnits NumberWithUnits:: operator+ (const NumberWithUnits& n1){
        double convert=NumberWithUnits::find_connection(n1.unit,this->unit);
        if(convert==-1){
             throw invalid_argument("cant sum unrelated units"); 
        }else{
            double num=this->number+n1.number*convert;
            return NumberWithUnits(num,this->unit);
          
        }
       
    }

    // onary
    NumberWithUnits NumberWithUnits::operator- (){
      return NumberWithUnits(this->number*-1,this->unit);
    }

    // return this after changes
    NumberWithUnits& NumberWithUnits::operator-= (const NumberWithUnits& n1){
        double convert=NumberWithUnits::find_connection(n1.unit,this->unit);
        if(convert==-1){
            throw invalid_argument("can't sub unrelated units"); 
        }else{
            this->number-=n1.number*convert;
            return *this;
            
        }
    }
    NumberWithUnits NumberWithUnits::operator- (const NumberWithUnits& n1){
        double convert=NumberWithUnits::find_connection(n1.unit,this->unit);
        if(convert==-1){
            throw invalid_argument("can't sub unrelated units"); 
        }else{
            double num=this->number-n1.number*convert;
            return NumberWithUnits(num,this->unit);
          
        }
    }

    NumberWithUnits NumberWithUnits::operator *(double d){
        return NumberWithUnits (this->number*d,this->unit);
    }
            
    NumberWithUnits operator *(double d, const NumberWithUnits& n1){
        return NumberWithUnits (n1.number*d,n1.unit);
    }
            

    bool NumberWithUnits::operator <(const NumberWithUnits& n2)const{
        return (compare(*this,n2)==-1);
           
    }
    bool NumberWithUnits::operator <=(const NumberWithUnits& n2)const{
        return (compare(*this,n2)==-1 || compare(*this,n2)==0 );
            
        
    }
    bool NumberWithUnits::operator >(const NumberWithUnits& n2)const{
        return (compare(*this,n2)==1 );
        
    }
    bool NumberWithUnits::operator >=(const NumberWithUnits& n2)const{
        return(compare(*this,n2)==1 || compare(*this,n2)==0 );
       
    }
    bool NumberWithUnits::operator ==(const NumberWithUnits& n2)const{
        return(compare(*this,n2)==0 );
        
    }
    bool NumberWithUnits::operator !=(const NumberWithUnits& n2)const{
        return !(compare(*this,n2)==0);
         
    }

    // // // // prefix and postfix 
    // ++x
    NumberWithUnits& NumberWithUnits::operator++(){    
        this->number++;
        return *this;
    }
    // x++
    NumberWithUnits NumberWithUnits::operator++(int n){
        
        NumberWithUnits temp{this->number,this->unit};
        this->number++;
        return temp;

        
    } 
    
        // --x
    NumberWithUnits& NumberWithUnits::operator--(){
        this->number--;
        return *this;
    }

    // x--
    NumberWithUnits NumberWithUnits::operator--(int n){
        NumberWithUnits temp{this->number,this->unit};
        this->number--;
        return temp;
    }

    // // // // // //  input and output 
    std::ostream& operator << (std::ostream& out,const NumberWithUnits& n1){
        out<<n1.number<<"["<<n1.unit <<"]";
        return out;
    }

    std::istream& operator >>(std::istream& in, NumberWithUnits& n1){
        char left_bracket=0;
        char right_bracket=0;
        double num=NAN;
        string unit;
        in >> num >> left_bracket >> unit;
        if(unit.find(']')!=string::npos)//if there is a right ]
        {
            size_t position = unit.find(']');
            unit = unit.substr(0, position);
        }else{
            in>>right_bracket;
        }

        if(NumberWithUnits::mp.find(unit)==NumberWithUnits::mp.end())
        {
            throw invalid_argument("no such unit in map");
        }
        n1.number=num;
        n1.unit=unit;
        
        return in;
    }
}
