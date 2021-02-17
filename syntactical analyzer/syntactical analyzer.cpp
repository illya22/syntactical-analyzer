// syntactical analyzer.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include<stack>
#include<map>
#include<string>
#include<Windows.h>

using namespace std;

stack<char> sta;
map<char, map<char, string> > M;
map<char, map<char, string> > m;
string input;
int ip;
char X;

void wrong_data(int i)
{
	cout << "error_" << i << endl;
	cout << "**********************************" << endl;
	system("pause");
	exit(0);
}
void M_map()
{
	M['E']['i'] = "E -> TA";
	M['E']['+'] = "error";
	M['E']['*'] = "error";
	M['E']['('] = "E -> TA";
	M['E'][')'] = "synchronization error";
	M['E']['$'] = "synchronization error";
	M['A']['i'] = "error";
	M['A']['+'] = "A -> +TA";
	M['A']['*'] = "error";
	M['A']['('] = "error";
	M['A'][')'] = "A -> e";
	M['A']['$'] = "A -> e";
	M['T']['i'] = "T -> FB";
	M['T']['+'] = "synchronization error";
	M['T']['*'] = "error";
	M['T']['('] = "T -> FB";
	M['T'][')'] = "synchronization error";
	M['T']['$'] = "synchronization error";
	M['B']['i'] = "error";
	M['B']['+'] = "B -> e";
	M['B']['*'] = "B -> *FB";
	M['B']['('] = "error";
	M['B'][')'] = "B -> e";
	M['B']['$'] = "B -> e";
	M['F']['i'] = "F -> id";
	M['F']['+'] = "synchronization error";
	M['F']['*'] = "synchronization error";
	M['F']['('] = "F -> (E)";
	M['F'][')'] = "synchronization error";
	M['F']['$'] = "synchronization error";
}
void m_map()
{
	m['E']['i'] = "E -> TE2";
	m['E']['+'] = "skip input[ip], missing op!";
	m['E']['*'] = "skip input[ip], missing op!";
	m['E']['('] = "E -> TE2";
	m['E'][')'] = "synchronization error";
	m['E']['$'] = "synchronization error";
	m['A']['i'] = "skip input[ip], missing op!";
	m['A']['+'] = "E2 -> +TE2";
	m['A']['*'] = "skip input[ip], missing op!";
	m['A']['('] = "skip input[ip], missing op!";
	m['A'][')'] = "E2 -> e";
	m['A']['$'] = "E2 -> e";
	m['T']['i'] = "T -> FT2";
	m['T']['+'] = "pop stack, missing id!";
	m['T']['*'] = "skip input[ip], missing op!";
	m['T']['('] = "T -> FT2";
	m['T'][')'] = "synchronization error";
	m['T']['$'] = "synchronization error";
	m['B']['i'] = "skip input[ip], missing op!";
	m['B']['+'] = "T2 -> e";
	m['B']['*'] = "T2 -> *FT2";
	m['B']['('] = "skip input[ip], missing op!";
	m['B'][')'] = "T2 -> e";
	m['B']['$'] = "T2 -> e";
	m['F']['i'] = "F -> id";
	m['F']['+'] = "pop stack, missing id!";
	m['F']['*'] = "pop stack, missing id!";
	m['F']['('] = "F -> (E)";
	m['F'][')'] = "synchronization error";
	m['F']['$'] = "synchronization error";
}
 
void syntactic()
{
	while (X != '$')
	{
		if (X == ' ') { ip++; }
		else if (X == input[ip])
		{
			sta.pop();
			if (input[ip] != 'i')
				ip++;
			else
				ip += 2;
		}
		else if ('i' == X || '*' == X || '+' == X || '(' == X || ')' == X)
		{
			cout << "missing '(' or ')'!" << endl;
			sta.pop();
		}
		else if (M[X][input[ip]] == "error")
		{
			cout << m[X][input[ip]] << endl;
			if (input[ip] != 'i')
				ip++;
			else
				ip += 2;
		}
		else if (M[X][input[ip]] == "synchronization error")
		{
			cout << m[X][input[ip]] << endl;
			sta.pop();
		}
		else if (M[X][input[ip]] != "error" && M[X][input[ip]] != "synchronization error")
		{
			cout << m[X][input[ip]] << endl;
			sta.pop();
			for (int i = M[X][input[ip]].length() - 1; i > 4; i--)
				if (M[X][input[ip]][i] != 'd' && M[X][input[ip]][i] != 'e')
					sta.push(M[X][input[ip]][i]);
		}
		X = sta.top();
	}
}

int main()
{
	input = "";
	while (input != "stop")
	{
		sta.push('$');
		sta.push('E');
		ip = 0;
		X = sta.top();
		M_map();
		m_map();
		cout << "-------------------------------------" << endl;
		cout << "INPUT string:" << endl;
		cin >> input;
		input[input.length()] = '$';
		cout << "OUTPUT:" << endl;
		syntactic();
		cout << "--------------------------------------" << endl;
	}
	return 0;
}

 
