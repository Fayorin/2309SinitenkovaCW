#include <iostream> 
#include <stack> 
#include <algorithm> 
#include <math.h> 
using namespace std;

class TNode {
public:
	char inf;
	double var;
	TNode* left;
	TNode* right;
};
typedef TNode* ExpTree;
struct Node {
	char val;
	float var;
	Node* next;
	Node(char _val, float _var)
	{
		val = _val;
		var = _var;
		next = nullptr;
	}
};

ExpTree Create_Node(int inf);
ExpTree constructTree(ExpTree T, char postfix[]);
int getPriority(char ch);
void Exp_to_Post(string infix, char postfix[]);
float resultExpression(char postfix[]);
void show(ExpTree T);
void preorder(ExpTree T);
void postorder(ExpTree T);
void inorder(ExpTree T);
void printExtra(char postfix[], ExpTree tree);
void display(ExpTree tree, char postfix[]);
bool IsExpCorrect(string infix);
bool isOperator(char ch);
bool isDigit(char c);
double evaluateExpression(ExpTree root);

struct Linkedlist {
	Node* first;
	Node* last;

	bool is_empty() {
		return first == nullptr;
	}
	Node* find(char _val) {
		Node* p = first;
		while (p && p->val != _val) p = p->next;
		return (p && p->val == _val) ? p : nullptr;
	}
	Linkedlist() : first(nullptr), last(nullptr) {}
	Node* push_back(char _val, float _var) {
		Node* p = new Node(_val, _var);
		if (is_empty()) {
			first = p;
			last = p;
			return p;
		}
		last->next = p;
		last = p;
		return p;
	}
};
void main()
{
	bool yes = true;
	string infix;
	string a;
	cout << "The program is designed to represent an arithmetic expression using an expression tree." << endl;
	cout << "If you want to work with numbers greater than 9, enter letter variables and assign values to them.";
	cout << endl;
	while (yes)
	{
		while (true) {

			cout << "\n Enter Expression : ";

			cin >> infix;
			if (!IsExpCorrect(infix)) {
				cout << " Error " << endl;

			}
			else break;
		}
		char* postfix = (char*)malloc(sizeof(char) * infix.length());
		Exp_to_Post(infix, postfix);
		ExpTree tree1 = NULL;
		tree1 = constructTree(tree1, postfix);
		display(tree1, postfix);
		cout << "\nDo you want to continue?";
		cin >> a;
		if (a != "yes")
			break;

	}
}

void display(ExpTree tree, char postfix[])
{
	cout << "__________________________________________________________________" << endl;
	cout << "\n PreOrder: ";
	preorder(tree);
	//line();
	cout << "\n PostOrder: ";
	postorder(tree);
	//line();
	cout << "\n InOrder: ";
	inorder(tree);
	//line();
	cout << endl;
	printExtra(postfix, tree);
}
void printExtra(char postfix[], ExpTree tree)
{

	cout << "Result = " << evaluateExpression(tree);
}
bool isDigit(char ch)
{
	if ((ch <= '9') && (ch >= '1'))
		return true;
	return false;
}
bool isOperator(char ch)
{
	if (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '%' || ch == '^')
		return true;
	return false;
}

bool IsExpCorrect(string infix)
{
	if ((infix.length() < 2) && isOperator(infix[0]))
		return false;
	for (unsigned int i = 0; i < infix.length(); i++) {
		if (!isDigit(infix[i]) && !(isalpha(infix[i])) && !isOperator(infix[i]) && infix[i] != '(' && infix[i] != ')' && infix[i] != '!')
			return false;
	}
	return true;
}
ExpTree Create_Node(int inf)
{
	TNode* temp;
	temp = (TNode*)malloc(sizeof(TNode));
	if (temp == NULL)
	{
		return (temp);
	}
	temp->left = NULL;
	temp->right = NULL;
	temp->inf = inf;
	return temp;
};

ExpTree constructTree(ExpTree tree, char postfix[])
{
	int i = 0;
	stack<TNode*> st;
	TNode* temp_tree1;
	TNode* temp_tree2;
	while (postfix[i] != '\0')
	{
		if (!(postfix[i] == '+' || postfix[i] == '-' || postfix[i] == '*' || postfix[i] == '/'
			|| postfix[i] == '%' || postfix[i] == '^' || postfix[i] == '!'))
		{
			tree = Create_Node(postfix[i]);
			st.push(tree);
		}
		else
		{
			if (postfix[i] == '!')
			{
				tree = Create_Node(postfix[i]);
				temp_tree1 = st.top(); st.pop();
				tree->right = NULL;
				tree->right = temp_tree1;
				st.push(tree);
			}
			else {
				tree = Create_Node(postfix[i]);
				temp_tree1 = st.top(); st.pop();
				temp_tree2 = st.top(); st.pop();
				tree->right = temp_tree1;
				tree->left = temp_tree2;
				st.push(tree);
			}
		}
		i++;
	}
	return tree;
}

void show(ExpTree T)
{
	cout << T->inf << " ";
}
void preorder(ExpTree T)
{
	if (T != NULL)
	{
		show(T);
		preorder(T->left);
		preorder(T->right);
	}
}
void postorder(ExpTree T)
{
	if (T != NULL)
	{
		postorder(T->left);
		postorder(T->right);
		show(T);
	}
}
void inorder(ExpTree T)
{
	if (T != NULL)
	{
		if ((T->left != NULL) && (T->right != NULL))
		{
			cout << "(";
			inorder(T->left);
			show(T);
			inorder(T->right);

			cout << ")";
		}
		else {

			inorder(T->left);
			show(T);
			inorder(T->right);
		}
	}
}
int getPriority(char ch)
{
	switch (ch)
	{
	case'^':
		return 4;
	case '!':
		return 3;
	case '/':
	case '*':
		return 2;
	case '+':
	case '-':
		return 1;
	default:
		return 0;
	}
}
bool isUnaryNegative(char ch)
{
	return ch == '-';
}
void Exp_to_Post(string infix, char postfix[])
{
	unsigned int counter1 = 0;
	stack<char> st;
	int postCount = 0;
	char element;
	int count = 0;
	bool negative = false;
	while (counter1 < infix.length())
	{
		element = infix[counter1];
		if (counter1 == 0 && isUnaryNegative(element))
		{
			negative = true;
			//counter1 += 1;
			element = '!';


		}
		if (element == '(')
		{
			st.push(element);
			counter1++;
			element = infix[counter1];
			if (isUnaryNegative(element))
			{
				element = '!';
				continue;
			}
			continue;
		}
		if (element == ')')
		{

			while (!st.empty() && st.top() != '(')
			{
				postfix[postCount++] = st.top();
				st.pop();
			}
			if (!st.empty())
			{
				st.pop();
			}
			counter1++;
			continue;
		}


		if (getPriority(element) == 0)
		{
			postfix[postCount++] = element;
		}
		else
		{
			if (st.empty())
			{
				st.push(element);
			}
			else
			{

				while (!st.empty() && st.top() != '(' &&
					(element != '^' && getPriority(element) <= getPriority(st.top()) || (element == '^' && getPriority(element) < getPriority(st.top()))))
				{
					postfix[postCount++] = st.top();
					st.pop();
				}
				st.push(element);
			}
		}
		counter1++;
	}

	while (!st.empty())
	{
		postfix[postCount++] = st.top();
		st.pop();
	}
	postfix[postCount] = '\0';
}


double evaluateExpression(ExpTree root) {
	if (root == nullptr)
		return 0.0;

	if (root->left == nullptr && root->right == nullptr)
	{
		if (isDigit(root->inf))
		{
			root->var = ((float)root->inf - '0');
		}
		if (isalpha(root->inf))
		{
			char current = root->inf;
			float value;
			std::cout << "Enter the value for " << current << ": ";
			std::cin >> value;
			root->var = value;
		}
		return root->var;
	}

	double leftValue = evaluateExpression(root->left);
	double rightValue = evaluateExpression(root->right);
	if (root->inf == '!')
		return rightValue *= -1;
	if (root->inf == '+')
		return leftValue + rightValue;
	else if (root->inf == '-')
		return leftValue - rightValue;
	else if (root->inf == '*')
		return leftValue * rightValue;
	else if (root->inf == '/')
		return leftValue / rightValue;
	else if (root->inf == '^')
		return pow(leftValue, rightValue);

	return 0.0;
}
//float resultExpression(char postfix[])
//{
//	Linkedlist valueMap;
//	stack<float> result;
//	int k = 0;
//	float a=0;
//	bool error = false;
//	while (postfix[k] && !error)
//	{
//		char ch = postfix[k];
//		if (ch=='!')
//		{
//			//k++;
//			//ch = postfix[k];
//			if (isalpha(ch))
//			{
//				char current = postfix[k];
//				if (valueMap.find(current) == nullptr) {
//					float value;
//					std::cout << "Enter the value for " << current << ": ";
//					std::cin >> value;
//					value *= -1;
//					Node* p = valueMap.push_back(current,value);
//					result.push(p->var);
//				}
//				else { result.push((valueMap.find(current)->var)); }
//			}
//			float num = result.top();
//			result.pop();
//			float calc = -num;
//			result.push(calc);
//		}
//		if (isDigit(ch))
//		{
//			result.push((float)postfix[k] - '0');
//		}
//		if( isalpha(ch))
//		{
//				char current = postfix[k];
//				if (valueMap.find(current)==nullptr) {
//					float value;
//					std::cout << "Enter the value for " << current << ": ";
//					std::cin >> value;
//					Node* p= valueMap.push_back(current, value);
//					result.push(p->var);
//				}
//				else { result.push((valueMap.find(current)->var)); }
//
//		}
//		else
//			if (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '%' || ch == '^')
//			{
//				float num1 = result.top();
//				result.pop();
//				float num2 = result.top();
//				result.pop();
//				float calc = 0;
//				switch (ch)
//				{
//				case '+':
//					calc = num2 + num1;
//					break;
//				case '-':
//					calc = num2 - num1;
//					break;
//				case '*':
//					calc = num2 * num1;
//					break;
//				case '/':
//					if (num1 == 0)
//					{
//						cout << "\n Math Error" << endl;
//						error = true;
//						break;
//					}
//					calc = num2 / num1;
//					break;
//				case '^':
//					calc = pow(num2, num1);
//					break;
//				}
//				result.push(calc);
//			}
//		
//		k++;
//	}
//	if (!error)
//		return result.top();
//}