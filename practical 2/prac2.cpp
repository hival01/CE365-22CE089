#include <iostream>
#include <string>
using namespace std;

int main()
{
    int no_of_input_symbols,no_of_states,initial_state,no_of_acc_states,f=0;
    cout<<"Enter no of input symbols:";
    cin>>no_of_input_symbols;
    cout<<"Enter input symbols:";
    char input_symbols[no_of_input_symbols];
    for(int i=0;i<no_of_input_symbols;i++){
        cin>>input_symbols[i];
    }
    cout<<"Enter no of states:";
    cin>>no_of_states;
    cout<<"Enter Initial State:";
    cin>>initial_state;
    cout<<"Enter no of accepting states:";
    cin>>no_of_acc_states;
    int accepting_states[no_of_acc_states];
    cout<<"Enter accepting states:";
    for(int i=0;i<no_of_acc_states;i++){
        cin>>accepting_states[i];
    }
    cout<<"Enter Transition table :"<<endl;
    
    int transition_table[no_of_states+1][no_of_input_symbols];
    for (int i=0;i<no_of_input_symbols;i++) {
        transition_table[0][i]=0;
    }
    for(int i=1;i<=no_of_states;i++){
        for(int j=0;j<no_of_input_symbols;j++){
            cout<<"Enter transition from "<<i<<" with input symbol "<<input_symbols[j]<<" :";
            cin>>transition_table[i][j];
        }
    }
    
    string inputString;
    cout<<"Enter Input String: ";
    cin>>inputString;
    
    int currState = initial_state;
    for(int i=0;i<inputString.length();i++){
        int j;
        for(j=0;j<no_of_input_symbols;j++){
            if(inputString[i]==input_symbols[j]){
                break;
            }
        }
        currState = transition_table[currState][j];
    }
    for(int i=0;i<no_of_acc_states;i++){
        if(currState==accepting_states[0]){
            cout<<"Valid String!!"<<endl;
            f=1;
            break;
        }
    }
    
    if(f==0){
        cout<<"Invalid String!"<<endl;
    }

    return 0;
}