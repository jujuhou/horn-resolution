/*************************************************
这个cpp主要定义了一些与读入数据相关的函数
main函数中直接调用read_in函数即可
**************************************************/
#include "horn.h"

//通过函数名查找其在function_name中的id,并用bool返回其是否找到
bool find_function_name_id(string present_function_name, int&id)
{
	vector<string>::iterator result = find(function_name.begin(), function_name.end(), present_function_name); //查找
	if (result == function_name.end()) { //没找到
		return false;
	}
	else { //找到
		id = result - function_name.begin();
		return true;
	}
}

//通过这个标识符的名称返回一个identifier,并用bool返回其是否找到
bool find_identifier_name_id(string present_identifier_name, identifier& present_identifier)
{
	//找constant
	vector<string>::iterator result = find(constant_name.begin(), constant_name.end(), present_identifier_name); //查找
	if (result != constant_name.end()) { //找到
		present_identifier.id = result - constant_name.begin();
		present_identifier.type = CONSTANT;
		return true;
	}
	//找variable
	result = find(variable_name.begin(), variable_name.end(), present_identifier_name); //查找
	if (result != variable_name.end()) { //找到
		present_identifier.id = result - variable_name.begin();
		present_identifier.type = VARIABLE;
		return true;
	}
	//都没找到返回false
	cout << "输入错误，子句中含没有说明的变量/常量名" << endl;
	return false;
}


//读入所有常量和变量
bool read_in_v_c()
{
	string tmp = " ";
	cout << "请输入所有的变量名（变量名间以空格隔开，输入结束后以“空格#”结尾）" << endl;
	cout << "本题可以直接复制下面的示例：" << endl<< "x #" << endl;
	while (true) {
		cin >> tmp;
		if (tmp == "#")
			break;
		variable_name.push_back(tmp);
	}
	tmp = " ";
	cout << "请输入所有的常量名（常量名间以空格隔开，输入结束后以“空格#”结尾）" << endl;
	cout << "本题可以直接复制下面的示例：" << endl << "A B C #" << endl;
	while (true) {
		cin >> tmp;
		if (tmp == "#")
			break;
		constant_name.push_back(tmp);
	}
	return true;
}
//读入一个原子句
bool read_in_point(clause& present_clause, string& clause_str, int point_begin, int point_end)
{
	int identifier_begin, identifier_end, i;

	point presnet_point;
	//首先判断是否为非
	if (clause_str[point_begin] == '!') {
		presnet_point.positive = false;
		point_begin++;
	}
	//分离出函数名
	string present_function_name;
	for (i = point_begin; i < point_end; i++) {
		if (clause_str[i] == '(') {
			present_function_name = clause_str.substr(point_begin, i - point_begin);
			identifier_begin = i + 1;
			break;
		}
	}
	if (i == point_end) {
		cout << "输入不符合规范" << endl;
		return false;
	}
	//通过函数名查找其在function_name中的id
	int id;
	bool find = find_function_name_id(present_function_name, id);
	if (!find) { //没找到,新加入
		function_name.push_back(present_function_name);
		presnet_point.function_id = function_name.size() - 1;//减1是因为新加入
	}
	else { //找到
		presnet_point.function_id = id;
	}

	//分离每一个标识符
	for (i = identifier_begin; i < point_end; i++) {
		if (clause_str[i] == ',' | clause_str[i] == ')') {
			identifier_end = i;

			identifier present_identifier;
			//通过这个标识符的名称返回一个identifier
			if (!find_identifier_name_id(clause_str.substr(identifier_begin, identifier_end - identifier_begin), present_identifier))
				return false;
			presnet_point.element.push_back(present_identifier);
			identifier_begin = i + 1;
		}
	}
	present_clause.element.push_back(presnet_point);

	return true;
}
//读入一个子句
bool read_in_clause()
{
	string clause_str;
	cout << "请输入所有的Horn子句(|代表或，!代表非)，单个子句内部不可包含空格或Tab键,输入后以另起一行#结尾" << endl;
	cout << "本题可以直接复制下面的示例："  << endl;
	cout << "Kill(C,A)|Kill(B,A)|Kill(A,A)" << endl;
	cout << "Hate(x,A)|!Kill(x,A)" << endl;
	cout << "!Hate(C,x)|!Hate(A,x)" << endl;
	cout << "Hate(A,A)" << endl;
	cout << "Hate(A,C)" << endl;
	cout << "Richer(x,A)|Hate(B,x)" << endl;
	cout << "!Richer(x,A)|!Hate(B,x)" << endl;
	cout << "Hate(A,x)|!Hate(B,x)" << endl;
	cout << "!Hate(A,x)|Hate(B,x)" << endl;
	cout << "!Hate(A,A)|!Hate(A,B)|!Hate(A,C)" << endl;
	cout << "!Hate(B,A)|!Hate(B,B)|!Hate(B,C)" << endl;
	cout << "!Hate(C,A)|!Hate(C,B)|!Hate(C,C)" << endl;
	cout << "!Richer(x,A)|!Kill(x,A)" << endl;
	cout << "#" << endl;
	while (true) {
		//构造一个子句
		clause present_clause;
		present_clause.mother = -1;
		present_clause.father = -1;
		present_clause.valid = true;
		present_clause.key = false;

		//输入子句
		cin >> clause_str;
		if (clause_str == "#")
			break;

		int i, point_begin = 0, point_end = 0;
		for (i = 0; i < clause_str.size(); i++) {
			if (clause_str[i] == '|' | i == clause_str.size() - 1) {
				point_end = (i == clause_str.size() - 1) ? i + 1 : i;
				if (!read_in_point(present_clause, clause_str, point_begin, point_end))
					return false;
				point_begin = i + 1;
			}
		}
		clause_set.push_back(present_clause);
	}
	return true;
}

//读入猜测的结论
bool read_in_result()
{
	string clause_str;
	cout << "请输入猜测的结论(一个原子句)" << endl;
	cout << "本题可以直接复制下面的示例："<<endl<<"Kill(A,A)" << endl;		
	result_clause.mother = -1;
	result_clause.father = -1;
	result_clause.valid = true;
	result_clause.key = false;

	//输入子句
	cin >> clause_str;
	int i, point_begin = 0, point_end = 0;
	for (i = 0; i < clause_str.size(); i++) {
		if (clause_str[i] == '|' | i == clause_str.size() - 1) {
			point_end = (i == clause_str.size() - 1) ? i + 1 : i;
			if (!read_in_point(result_clause, clause_str, point_begin, point_end))
				return false;
			point_begin = i + 1;
		}
	}
	return true;
}

//综合了所有读入的函数
bool read_in()
{
	if (!read_in_v_c())
		return false;
	cout << endl << "*****************************" << endl;
	if (!read_in_clause())
		return false;
	cout << endl << "*****************************" << endl;
	if (!read_in_result())
		return false;
	cout << endl << "*****************************" << endl;
}
