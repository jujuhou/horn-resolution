/*************************************************
这个cpp主要实现了子句的归结
main函数中直接调用guijie()即可
**************************************************/

#include "horn.h"
bool operator<(identifier a, identifier b);
ostream&operator<<(ostream &out, clause &c);
bool equal_except_v(point &point1, point &point2);//原子句除变量和真假外全部相等


//判断clause1是否是clause2的孩子节点
bool is_child(int clause1, int clause2)
{
	if (clause_set[clause1].father == -1 || clause_set[clause1].mother == -1)
		return false;
	if (clause_set[clause1].father == clause2 || clause_set[clause1].mother == clause2)
		return true;
	return(is_child(clause_set[clause1].father, clause2) || is_child(clause_set[clause1].mother, clause2));
}

//father是事实，mother是被替换的子句，mother_delete是待删除的原子句
//归结出来了空子句：return -1
//归结出来了结论：return 1
//其它：return 0
int replace_and_new(int father, int mother, int mother_delete)
{
	clause new_clause;
	map<identifier, identifier> replace_map;//<变量，常量>
	//构建替换的键值对
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
		cout << "错误！归结出矛盾" << endl;
		return -1;
	}
	clause_set.push_back(new_clause);
	cout << clause_set.size() - 1 << ":" << new_clause << "......... " << new_clause.father << " & " << new_clause.mother <<" 归结而来"<< endl;

	if (new_clause.element.size() == result_clause.element.size() &&
		equal_except_v(new_clause.element[0], result_clause.element[0]) &&
		new_clause.element[0].positive == result_clause.element[0].positive)
		return 1;

	return 0;
}

//用clause[num]替换clause[i]
//归结出来了空子句：return -1
//归结出来了结论：return 1
//其它：return 0
int substitude(int num)//num为进行替换的事实所在位置
{
	int function_id = clause_set[num].element[0].function_id;
	for (int i = 0; i < clause_set.size(); i++) {
		if (clause_set[i].valid && !is_child(num, i)) {//可以访问且i不是num的祖结点则用num的事实替换i中的原子句
			for (int j = 0; j < clause_set[i].element.size(); j++) {
				if (equal_except_v(clause_set[num].element[0], clause_set[i].element[j]) &&
					clause_set[num].element[0].positive != clause_set[i].element[j].positive) {//真假相反则可删去
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
	cout << "将已输入的子句集进行如下的编号" << endl;
	for (int i = 0; i < clause_set.size(); i++) {
		cout << i << ":" << clause_set[i] << endl;
	}
	cout << endl << "*****************************" << endl;

	cout << "下面进行归结" << endl;
	//归结的主体
	for (int i = 0; i < clause_set.size(); i++) {
		if (clause_set[i].element.size() == 1) {//如果是事实，则对其它子句进行替换，并将这一子句置为不可访问（valid=false）
			clause_set[i].valid = false;//valid置为否
			int state = substitude(i);
			if (state == -1 || state == 1)
				return state;
		}
	}
	return 0;
}
