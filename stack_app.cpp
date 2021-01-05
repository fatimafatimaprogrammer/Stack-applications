#include <iostream>
using namespace std;

/* defining the max_size of array*/
#define MAX_SIZE 50

class A_Stack {
	int top; //contains the top element of stack in array based implementation

public:
	char stack_array[MAX_SIZE];
	/* CONSTRUCTOR IMPLEMENTATION*/
	A_Stack() {
		top = -1;
	}

	/*FUNCTIONS definations  FOR ARRAY BASED STACK*/
	bool isEmpty();
	bool isFull();
	bool push(char x);
	char pop();
	char peek();
	bool areParanthesisBalanced(string exp,A_Stack obj);
	int PostfixEvaluation(char * exp);

};
/*implementation of functions defined for array_based stack*/
bool A_Stack::isEmpty() {
	return top == -1;
}

bool A_Stack::isFull() {
	return top == MAX_SIZE - 1;
}

char A_Stack::pop() {
	if (!isEmpty())
	{	/*decrementing the top and assigning that value to some variable a*/
		char a = stack_array[top--];
		//cout << "the value: \'" << a << " \' is poped out of stack\n";
		return a;
	}
	else
	{
		/* if stack is empty nothing can be poped so return 0*/
		cout << "stack is empty!!!!!!!!!!! STACK UNDERFLOW OCCURED...... so no element can be popped\n";
		return '0';
	}
}

bool A_Stack::push(char value) {
	if (!isFull())
	{
		//inserting the value at top
		stack_array[++top] = value;
		//cout << "the value : \" " << value << " \" is pushed into stack\n";
		return true;
	}
	else
	{
		//else return false
		cout << "stack_array is full !!!!!!STACK OVERFLOW HAS OCCURED.... so value cannot be pushed\n";
		return false;
	}
}

char A_Stack::peek() {
	/*if stack is not empty so return top value*/
	if (!isEmpty())
	{
		char a = stack_array[top];
		return a;
	}
	else
	{
		cout << "stack is empty!!!!!!!!!!! STACK UNDERFLOW OCCURED...... \n";
		//return '0';
	}
}

bool A_Stack::areParanthesisBalanced(string exp,A_Stack s)
{
		char x;

		// Traversing the Expression 
		for (int i = 0; i < exp.length(); i++)
		{
			
			if (exp[i] == '(' || exp[i] == '['
				|| exp[i] == '{')
			{
				// Push the element in the stack 
				s.push(exp[i]);
				continue;
			}

			// IF current current character is not opening 
			// bracket, then it must be closing. So stack 
			// cannot be empty at this point. 
			if (s.isEmpty())
			{
				return false;
			}
			switch (exp[i]) {
				case ')':
					// Store the top element in x
					x = s.stack_array[top];
					s.pop();
					if (x == '{' || x == '[') 
					return false;
					break;

				case '}':

					// Store the top element in b 
					x = s.stack_array[top];
					s.pop();
					if (x == '(' || x == '[' )
						return false;
					break;

				case ']':

					// Store the top element in c 
					x = s.stack_array[top];
					s.pop();
					if (x == '{' || x == '(' )
						return false;
					break;
				}
			
		}

		// Check Empty Stack 
		return(s.isEmpty());
}

int prec(char c)
{
	if (c == '^')
		return 3;
	else if(c == '*' || c == '/')
		return 2;
	else if(c == '+' || c == '-')
		return 1;
	else
		return -1;
}

// The main function to convert infix expression 
//to postfix expression 
void infixToPostfix(string infinix_string)
{
	A_Stack st;//stack
	st.push('N'); // random character to keep track of the end of stack
	int l = infinix_string.length();
	string postfix_string;//new string to store postfix exp
	char space = ' ';
	for (int i = 0; i < l; i++)
	{

		// WRITE CODE TO CHECK IF THE SCANNED CHARACTER IS  
		// AN OPERAND, ADD IT TO OUTPUT NEW STRING. 
		if (infinix_string[i]>='a' && infinix_string[i]<='z' || infinix_string[i]>='0'&& infinix_string[i]<='9'
			|| infinix_string[i]>='A' && infinix_string[i]<='Z')
			postfix_string = postfix_string +infinix_string[i]+space;
		
		// If the scanned character is an  
		// ‘(‘, push it to the stack. 
		else if (infinix_string[i] == '(')

			st.push('(');

		// If the scanned character is an ‘)’,  
		// pop and to output string from the stack 
		// until an ‘(‘ is encountered. 
		else if (infinix_string[i] == ')')
		{
			//WRITE CODE TO POP AND TO OUTPUT STRING FROM THE STACK 
		 // UNTIL AN ‘(‘ IS ENCOUNTERED. 
			while (st.peek() != '(' )
			{
				postfix_string = postfix_string +st.peek();
				cout << "  ";
				st.pop();
			}
			st.pop();
		}
		else if (infinix_string[i] == '{')

			st.push('{');
		else if (infinix_string[i] == '}' )
		{
			while (st.peek() != '{')
			{
				postfix_string = postfix_string +st.peek();
				cout << "  ";
				st.pop();
			}
			st.pop();
		}
		//If an operator is scanned 
		else {
		while (st.peek() != 'N' && prec(infinix_string[i]) <=
			prec(st.peek()))
		{
			char c = st.peek();
			st.pop();
			postfix_string =postfix_string+c;
			cout << "  ";
		}
		st.push(infinix_string[i]);
		}

	}

	// Pop all the remaining elements from the stack 
	while (st.peek() != 'N')
	{
		// WRITE CODE TO STORE TOP ELEMENT IN A VARIABLE, POP IT AND THEN STORE IT IN NEW STRING        
		char c = st.peek();
		st.pop();
		postfix_string += c;
		postfix_string.append(" ");
		cout << "  ";
	}
	postfix_string.append(" ");
	cout << postfix_string << endl;
}

// The main function that returns value of a given postfix expression  
int PostfixEvaluation(char * exp)
{
	// Create a stack of capacity equal to expression size  
	//struct Stack* stack = createStack(strlen(exp));
	A_Stack stack;
	int i;
	for (i = 0; exp[i]; ++i)
	{
		// If the scanned character is an operand (number here),  
		// push it to the stack.  
		if (isdigit(exp[i]))
			stack.push( exp[i] - '0');

		// If the scanned character is an operator, pop two  
		// elements from stack apply the operator  
		else
		{
			int val1 = stack.pop();
			int val2 = stack.pop();
			switch (exp[i])
			{
			case '+': stack.push( val2 + val1); break;
			case '-': stack.push(val2 - val1); break;
			case '*':  stack.push(val2 * val1); break;
			case '/':  stack.push(val2 / val1); break;
			}
		}
	}
	return stack.pop();
}

/***************************************************************************************************
			"HERE GOES OUR MAIN CODE FOR TESTING THE ARRAY BASED STACK FUNCTIONS"
****************************************************************************************************/

int main() {
	//creating object for accessing functions of A_Stack
	A_Stack obj;
	string exp;

	cout << "Enter expression  : ";
	cin >> exp;
	cout << "\n-----------------------------------------------------------------------------\n";
	cout << "postfix evaluation : \n";
	//PostfixEvaluation("430 103 ^ +");
	cout << "\n-----------------------------------------------------------------------------\n";

	/*if (obj.areParanthesisBalanced(exp, obj))
	{
		cout << endl<< "stack is empty !!!!!!!!!!!! \nbecause no of brackets pushed into stack = no of brackets poped out of stack\n";
		cout << "SO..........Expression is Balanced" << endl;

	}
	else {
		cout <<endl<< "stack is not empty !!!!!!!!!!!! \nbecause no of brackets pushed into stack != no of brackets poped out of stack\n";
		cout << "Expression is not Balanced" << endl;
	}*/
	//cout << "\n-----------------------------------------------------------------------------\n";


	//pushing  2,4,6,8 into array based stack
	/*cout << "\n-----------------------------------------------------------------------------\n";
	cout << "(1)pushing 2,4,6,8 into the stack .........\n";
	obj->push(2);
	obj->push(4);
	obj->push(6);
	obj->push(8);

	cout << "\n-----------------------------------------------------------------------------\n";
	//poping fromthe stack
	cout <<endl<< "(2)poping the top from stack ......\n" << obj->pop()<<endl;
	cout << "\n-----------------------------------------------------------------------------\n";
	//getting the peek element
	cout <<endl<<"(3)peek element in stack is : " << obj->peek() << endl;*/
}