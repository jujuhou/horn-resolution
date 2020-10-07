/*************************************************
���cpp��Ҫʵ�����Ӿ�Ĺ��
main������ֱ�ӵ���guijie()����
**************************************************/

#include "horn.h"
bool operator<(identifier a, identifier b);
ostream&operator<<(ostream &out, clause &c);
bool equal_except_v(point &point1, point &point2);//ԭ�Ӿ�������������ȫ�����


//�ж�clause1�Ƿ���clause2�ĺ��ӽڵ�
bool is_child(int clause1, int clause2)
{
	if (clause_set[clause1].father == -1 || clause_set[clause1].mother == -1)
		return false;
	if (clause_set[clause1].father == clause2 || clause_set[clause1].mother == clause2)
		return true;
	return(is_child(clause_set[clause1].father, clause2) || is_child(clause_set[clause1].mother, clause2));
}

//father����ʵ��mother�Ǳ��滻���Ӿ䣬mother_delete�Ǵ�ɾ����ԭ�Ӿ�
//�������˿��Ӿ䣺return -1
//�������˽��ۣ�return 1
//������return 0
int replace_and_new(int father, int mother, int mother_delete)
{
	clause new_clause;
	map<identifier, identifier> replace_map;//<����������>
	//�����滻�ļ�ֵ��
	for (int i = 0; i < clause_set[father].element[0].element.size(); i++) {
		if (clause_set[mother].element[mother_delete].element[i].type == VARIABLE)
			replace_map[clause_set[mother].element[mother_delete].element[i]] = clause_set[father].element[0].element[i];
	}
	new_clause.element = clause_set[mother].element;
	new_clause.father = father;
	new_clause.mother = mother;
	new_clause.valid = true;
	new_clause.key = false;
	new_clause.element.erase(vector<point>::iterator(new_clause.element.begin() + mother_delete));

	for (int i = 0; i < new_clause.element.size(); i++) {
		for (int j = 0; j < new_clause.element[i].element.size(); j++) {
			if (new_clause.element[i].element[j].type == VARIABLE &&
				replace_map.end() != replace_map.find(new_clause.element[i].element[j])) {
				new_clause.element[i].element[j] = replace_map[new_clause.element[i].element[j]];

			}
		}
	}
	if (new_clause.element.size() == 0) {
		cout << "���󣡹���ì��" << endl;
		return -1;
	}
	clause_set.push_back(new_clause);
	cout << clause_set.size() - 1 << ":" << new_clause << "......... " << new_clause.father << " & " << new_clause.mother <<" ������"<< endl;

	if (new_clause.element.size() == result_clause.element.size() &&
		equal_except_v(new_clause.element[0], result_clause.element[0]) &&
		new_clause.element[0].positive == result_clause.element[0].positive)
		return 1;

	return 0;
}

//��clause[num]�滻clause[i]
//�������˿��Ӿ䣺return -1
//�������˽��ۣ�return 1
//������return 0
int substitude(int num)//numΪ�����滻����ʵ����λ��
{
	int function_id = clause_set[num].element[0].function_id;
	for (int i = 0; i < clause_set.size(); i++) {
		if (clause_set[i].valid && !is_child(num, i)) {//���Է�����i����num����������num����ʵ�滻i�е�ԭ�Ӿ�
			for (int j = 0; j < clause_set[i].element.size(); j++) {
				if (equal_except_v(clause_set[num].element[0], clause_set[i].element[j]) &&
					clause_set[num].element[0].positive != clause_set[i].element[j].positive) {//����෴���ɾȥ
					int state = replace_and_new(num, i, j);
					if (state == -1 || state == 1)
						return state;

				}
			}
		}
	}
	return 0;
}

int guijie()
{
	cout << "����������Ӿ伯�������µı��" << endl;
	for (int i = 0; i < clause_set.size(); i++) {
		cout << i << ":" << clause_set[i] << endl;
	}
	cout << endl << "*****************************" << endl;

	cout << "������й��" << endl;
	//��������
	for (int i = 0; i < clause_set.size(); i++) {
		if (clause_set[i].element.size() == 1) {//�������ʵ����������Ӿ�����滻��������һ�Ӿ���Ϊ���ɷ��ʣ�valid=false��
			clause_set[i].valid = false;//valid��Ϊ��
			int state = substitude(i);
			if (state == -1 || state == 1)
				return state;
		}
	}
	return 0;
}
