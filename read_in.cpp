/*************************************************
���cpp��Ҫ������һЩ�����������صĺ���
main������ֱ�ӵ���read_in��������
**************************************************/
#include "horn.h"

//ͨ����������������function_name�е�id,����bool�������Ƿ��ҵ�
bool find_function_name_id(string present_function_name, int&id)
{
	vector<string>::iterator result = find(function_name.begin(), function_name.end(), present_function_name); //����
	if (result == function_name.end()) { //û�ҵ�
		return false;
	}
	else { //�ҵ�
		id = result - function_name.begin();
		return true;
	}
}

//ͨ�������ʶ�������Ʒ���һ��identifier,����bool�������Ƿ��ҵ�
bool find_identifier_name_id(string present_identifier_name, identifier& present_identifier)
{
	//��constant
	vector<string>::iterator result = find(constant_name.begin(), constant_name.end(), present_identifier_name); //����
	if (result != constant_name.end()) { //�ҵ�
		present_identifier.id = result - constant_name.begin();
		present_identifier.type = CONSTANT;
		return true;
	}
	//��variable
	result = find(variable_name.begin(), variable_name.end(), present_identifier_name); //����
	if (result != variable_name.end()) { //�ҵ�
		present_identifier.id = result - variable_name.begin();
		present_identifier.type = VARIABLE;
		return true;
	}
	//��û�ҵ�����false
	cout << "��������Ӿ��к�û��˵���ı���/������" << endl;
	return false;
}


//�������г����ͱ���
bool read_in_v_c()
{
	string tmp = " ";
	cout << "���������еı����������������Կո����������������ԡ��ո�#����β��" << endl;
	cout << "�������ֱ�Ӹ��������ʾ����" << endl<< "x #" << endl;
	while (true) {
		cin >> tmp;
		if (tmp == "#")
			break;
		variable_name.push_back(tmp);
	}
	tmp = " ";
	cout << "���������еĳ����������������Կո����������������ԡ��ո�#����β��" << endl;
	cout << "�������ֱ�Ӹ��������ʾ����" << endl << "A B C #" << endl;
	while (true) {
		cin >> tmp;
		if (tmp == "#")
			break;
		constant_name.push_back(tmp);
	}
	return true;
}
//����һ��ԭ�Ӿ�
bool read_in_point(clause& present_clause, string& clause_str, int point_begin, int point_end)
{
	int identifier_begin, identifier_end, i;

	point presnet_point;
	//�����ж��Ƿ�Ϊ��
	if (clause_str[point_begin] == '!') {
		presnet_point.positive = false;
		point_begin++;
	}
	//�����������
	string present_function_name;
	for (i = point_begin; i < point_end; i++) {
		if (clause_str[i] == '(') {
			present_function_name = clause_str.substr(point_begin, i - point_begin);
			identifier_begin = i + 1;
			break;
		}
	}
	if (i == point_end) {
		cout << "���벻���Ϲ淶" << endl;
		return false;
	}
	//ͨ����������������function_name�е�id
	int id;
	bool find = find_function_name_id(present_function_name, id);
	if (!find) { //û�ҵ�,�¼���
		function_name.push_back(present_function_name);
		presnet_point.function_id = function_name.size() - 1;//��1����Ϊ�¼���
	}
	else { //�ҵ�
		presnet_point.function_id = id;
	}

	//����ÿһ����ʶ��
	for (i = identifier_begin; i < point_end; i++) {
		if (clause_str[i] == ',' | clause_str[i] == ')') {
			identifier_end = i;

			identifier present_identifier;
			//ͨ�������ʶ�������Ʒ���һ��identifier
			if (!find_identifier_name_id(clause_str.substr(identifier_begin, identifier_end - identifier_begin), present_identifier))
				return false;
			presnet_point.element.push_back(present_identifier);
			identifier_begin = i + 1;
		}
	}
	present_clause.element.push_back(presnet_point);

	return true;
}
//����һ���Ӿ�
bool read_in_clause()
{
	string clause_str;
	cout << "���������е�Horn�Ӿ�(|�����!�����)�������Ӿ��ڲ����ɰ����ո��Tab��,�����������һ��#��β" << endl;
	cout << "�������ֱ�Ӹ��������ʾ����"  << endl;
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
		//����һ���Ӿ�
		clause present_clause;
		present_clause.mother = -1;
		present_clause.father = -1;
		present_clause.valid = true;
		present_clause.key = false;

		//�����Ӿ�
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

//����²�Ľ���
bool read_in_result()
{
	string clause_str;
	cout << "������²�Ľ���(һ��ԭ�Ӿ�)" << endl;
	cout << "�������ֱ�Ӹ��������ʾ����"<<endl<<"Kill(A,A)" << endl;		
	result_clause.mother = -1;
	result_clause.father = -1;
	result_clause.valid = true;
	result_clause.key = false;

	//�����Ӿ�
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

//�ۺ������ж���ĺ���
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
