#include <iostream>
#include <cstdlib>
#include <string>
#include <algorithm>
using namespace std;
class hamming{
	public:
		string data; //it is the raw data received
		int m , r = 0; // n is the length of raw data and r is the number of redundant bits
		char * msg; // it will store the all bits (data + redundant). We made it dynamic because at compile time we dont know how much redundant bits will be there, we will initialize memory to it once we know the number of redundant bits.
		hamming(string data){
			this->data = data;
			//reversing the data received
			cout<<"data is "<<data<<endl;
			m = data.size();
			int power = 1;

			//finding the number of redundant bits and storing them in r
			while(power < (m + r + 1)){
				r++;
				power*=2;
			}
            cout<<"power is "<<power<<" redundant bits are "<<r<<endl;
			//Allocating memory to our dynamic msg array(Note we are using one based indexing).
			msg = new char[m+r+1];
			int curr = 0;

			//initializing the msg with data bits and for redundant bits, an initial value of n
			for(int i = 1 ; i <= m+r ; i++){
				if(i & (i-1)){
					msg[i] = data[curr++];
				}
				else msg[i] = 'n';
			}
            showmsg(1);
			//function call to set the redundant bits
			setRedundantBits();
		}
		//function to show the whole msg
		void showmsg(int a){
			if(a)cout << "the data packet to be sent is : ";
			else cout << "the codeword to be Recieved is : ";
			for(int i = 1 ; i <=m+r ; i++){
				cout << msg[i] << " ";
			}
			cout << endl;
		}
        int bin_to_int(){
            string num = data;
            int dec_value = 0;
        
            // Initializing base value to 1, i.e 2^0
            int base = 1;
        
            int len = num.length();
            for (int i = len-1 ; i >= 0; i--) {
                if (num[i] == '1')
                    dec_value += base;
                base = base * 2;
            }
        
            return dec_value;
        }
		void setRedundantBits(){
			//for first redundant bit, check all those data bits at index where the first bit of index is set(1) similarly for second redundant bit, check all those data bits at index where the second bit of index is set(1), similarly for third redundant bit check all those data bits at index where the third bit of index is set to 1 and so on.
			int bit = 0;
			//outer loop runs for redundant bits (1 ,2 ,4 ,8 ....)
			for(int i = 1 ; i <= m+r ; i*=2){
				int count = 0;
				//inner loop runs for data bits
				for(int j = i+1 ; j<=m+r ; j++){
					// checking if the data bit corresponds to our redundant bit or not using bit manipulation
					if(j & (1 << bit)){
						if(msg[j] == '1') count++; // counting the number of ones in corresponding data bits
					}
				}
				//setting up redundant bits
				if(count & 1) msg[i] = '1';
				else msg[i] = '0';
				//increasing the bit position.
				bit++;
			}
			showmsg(1);
			//showing up the message to be sent(data + redundant)
		}
		string binary(int v){
		    string ans="";
		    while(v>0){
		        char c=(v%2+'0');
		        ans=c+ans;
		        v=v/2;
		    }
		    return ans;
		}
		void receiver(){
			//this ans will store the redundant bits, if they were right then according to even parity they will store 0 else if some error was made in a bit it will store 1
			string ans = "";
			int bit = 0;
			//this loop corresponds to the logic used in set redundant bits function
			for(int i = 1 ; i <= m+r ; i*=2){
				int count = 0;
				for(int j = i+1 ; j<=m+r ; j++){
					if(j & (1 << bit)){
						if(msg[j] == '1') count++;
					}
				}
				//incrementing the ans variable with the parity of redundant bit
				// if it was right then add 0 else 1
				if(count & 1){
					if(msg[i] == '1') ans.push_back('0');
					else ans.push_back('1');
				}
				else{
					if(msg[i]=='0') ans.push_back('0');
					else ans.push_back('1');
				}
				bit++;
			}
            char ch;
            cout<<"Do you want to change the bits Y/N -> ";cin>>ch;
			// if the ans had any occurrence of 1 then there is some fault
			if(ch=='y' || ch=='Y'){
                int k= (rand() % (m+r));
                cout<<"Pos Modified is "<<k<<endl;
                msg[k]-'0'==0 ? msg[k]='1':msg[k]='0';
                showmsg(1);
                //function call to set the redundant bits
                string val1=binary(k);
                cout<<"\t\t Index is "<<k<<" with binary "<<val1<<endl;
                
                msg[k]-'0'==0 ? msg[k]='1':msg[k]='0';
                showmsg(0);
                cout<<"Dataword extracted out of codeword is "<<data<<endl;
                int val=bin_to_int();
                char c=val;
                cout<<"val is "<<val<<" character is "<<c<<endl;
            }
			// if the ans dont have any occurrence of 1 then it is correct
			else{
				cout<<"Data recieved is ";
			    for(int j =1 ; j<=m+r ; j++){
					cout<<msg[j]<<" ";
				}cout<<endl;
				int k2=bin_to_int();
				char l2;
				if(k2>='a' and k2<='z') l2=k2;
				else l2=k2;
				cout<<"Fetched Datwword out of codeword is "<<data<<endl;
				cout<<"The Ascii of data recieved is "<<k2<<" character is "<<l2<<endl;
				cout << "\tcorrect data packet received" <<endl;
				cout << "\t------------------------------"<<endl;
			}
		}
};
class hamming_odd{
	public:
		string data; //it is the raw data received
		int m , r = 0; // n is the length of raw data and r is the number of redundant bits
		char * msg; // it will store the all bits (data + redundant). We made it dynamic because at compile time we dont know how much redundant bits will be there, we will initialize memory to it once we know the number of redundant bits.
		hamming_odd(string data){
			this->data = data;
			//reversing the data received
			cout<<"data is "<<data<<endl;
			m = data.size();
			int power = 1;

			//finding the number of redundant bits and storing them in r
			while(power < (m + r + 1)){
				r++;
				power*=2;
			}
            cout<<"Redundant bits are "<<r<<endl;
			//Allocating memory to our dynamic msg array(Note we are using one based indexing).
			msg = new char[m+r+1];
			int curr = 0;

			//initializing the msg with data bits and for redundant bits, an initial value of n
			for(int i = 1 ; i <= m+r ; i++){
				if(i & (i-1)){
					msg[i] = data[curr++];
				}
				else msg[i] = 'n';
			}
            showmsg(1);
			//function call to set the redundant bits
			setRedundantBits();
		}
		//function to show the whole msg
		void showmsg(int a){
			if(a)cout << "the data packet to be sent is : ";
			else cout << "the codeword to be Recieved is : ";
			for(int i = 1 ; i <=m+r ; i++){
				cout << msg[i] << " ";
			}
			cout << endl;
		}
        int bin_to_int(){
            string num = data;
            int dec_value = 0;
        
            // Initializing base value to 1, i.e 2^0
            int base = 1;
        
            int len = num.length();
            for (int i = len-1 ; i >= 0; i--) {
                if (num[i] == '1')
                    dec_value += base;
                base = base * 2;
            }
        
            return dec_value;
        }
		void setRedundantBits(){
			//for first redundant bit, check all those data bits at index where the first bit of index is set(1) similarly for second redundant bit, check all those data bits at index where the second bit of index is set(1), similarly for third redundant bit check all those data bits at index where the third bit of index is set to 1 and so on.
			int bit = 0;
			//outer loop runs for redundant bits (1 ,2 ,4 ,8 ....)
			for(int i = 1 ; i <= m+r ; i*=2){
				int count = 0;
				//inner loop runs for data bits
				for(int j = i+1 ; j<=m+r ; j++){
					// checking if the data bit corresponds to our redundant bit or not using bit manipulation
					if(j & (1 << bit)){
						if(msg[j] == '1') count++; // counting the number of ones in corresponding data bits
					}
				}
				//setting up redundant bits
				if(count & 1) msg[i] = '0';
				else msg[i] = '1';
				//increasing the bit position.
				bit++;
			}
			showmsg(1);
			//showing up the message to be sent(data + redundant)
		}
		string binary(int v){
		    string ans="";
		    while(v>0){
		        char c=(v%2+'0');
		        ans=c+ans;
		        v=v/2;
		    }
		    return ans;
		}
		void receiver(){
			//this ans will store the redundant bits, if they were right then according to even parity they will store 0 else if some error was made in a bit it will store 1
			string ans = "";
			int bit = 0;
			//this loop corresponds to the logic used in set redundant bits function
			for(int i = 1 ; i <= m+r ; i*=2){
				int count = 0;
				for(int j = i+1 ; j<=m+r ; j++){
					if(j & (1 << bit)){
						if(msg[j] == '1') count++;
					}
				}
				//incrementing the ans variable with the parity of redundant bit
				// if it was right then add 0 else 1
				if(count & 1){
					if(msg[i] == '1') ans.push_back('0');
					else ans.push_back('1');
				}
				else{
					if(msg[i]=='0') ans.push_back('0');
					else ans.push_back('1');
				}
				bit++;
			}
            char ch;
            cout<<"Do you want to change the bits Y/N -> ";cin>>ch;
			// if the ans had any occurrence of 1 then there is some fault
			if(ch=='y' || ch=='Y'){
                int k= (rand() % (m+r));
                cout<<"Pos Modified is "<<k<<endl;
                msg[k]-'0'==0 ? msg[k]='1':msg[k]='0';
                showmsg(1);
                //function call to set the redundant bits
                string val1=binary(k);
                cout<<"\t\t Index is "<<k<<" with binary "<<val1<<endl;
                
                msg[k]-'0'==0 ? msg[k]='1':msg[k]='0';
                showmsg(0);
                cout<<"Data worfd fetched out of codeword is "<<data<<endl;
                int val=bin_to_int();
                char c=val;
                cout<<"val is "<<val<<" character is "<<c<<endl;
            }
			// if the ans dont have any occurrence of 1 then it is correct
			else{
			    cout<<"Data recieved is ";
			    for(int j =1 ; j<=m+r ; j++){
					cout<<msg[j]<<" ";
				}cout<<endl;
				int k2=bin_to_int();
				char l2;
				if(k2>='a' and k2<='z') l2=k2;
				else l2=k2;
				cout<<"Fetched Datwword out of codeword is "<<data<<endl;
				cout<<"The binary data recieved is "<<k2<<" character is "<<l2<<endl;
				cout << "\tcorrect data packet received" <<endl;
				cout << "\t------------------------------"<<endl;
			}
		}
};
string ConvertToBinary(int n){
    string ans="";
    while(n){
        if(n%2==0)ans.push_back('0');
        else{
            ans.push_back('1');
        }
        n=n/2;
    }
    reverse(ans.begin(),ans.end());
    return ans;
}
int main(){
	string data;
	char y;
    cout<<"Enter the data string ";cin>>data;
	cout<<"Even parity enter y ";cin>>y;
    if(y=='y' || y=='Y'){
        for (int i = 0; i < data.length(); i++)
        {
            if(data[i]!=' '){
                cout<<""<<i+1<<" "<<data[i]<<" "<<"Ascii "<<int(data[i])<<endl;
                string val=ConvertToBinary(data[i]);
                cout<<"Binary of "<<data[i]<<" is "<<val<<endl;
                hamming h(val);
                // manipulating any ith data bit to check if receiver is detecting a error in that bit. If you eliminate the following line then correct code will be sent to receiver following that no error is received
                
                //h.msg[i] == '0' ? h.msg[i] = '1' : h.msg[i] = '0';
    
                h.receiver();
                cout<<endl;
            }
        }
    }
    else{
        for (int i = 0; i < data.length(); i++)
        {
            if(data[i]!=' '){
                cout<<""<<i+1<<" "<<data[i]<<" "<<"Ascii "<<int(data[i])<<endl;
                string val=ConvertToBinary(data[i]);
                cout<<"Binary of "<<data[i]<<" is "<<val<<endl;
                hamming_odd h(val);
                // manipulating any ith data bit to check if receiver is detecting a error in that bit. If you eliminate the following line then correct code will be sent to receiver following that no error is received
                
                //h.msg[i] == '0' ? h.msg[i] = '1' : h.msg[i] = '0';
    
                h.receiver();
                cout<<endl;
            }
        }
    }
	return 0;
}

//time complexity = O(nlogn) where , n = databits + redundant bits
