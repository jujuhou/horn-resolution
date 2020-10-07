#include"horn.h"

vector<string> constant_name;//���ڴ洢���г������ļ���
vector<string> variable_name;//���ڴ洢���б������ļ���
vector<string> function_name;//���ڴ洢���к������ļ���
vector<clause> clause_set;//�洢���е��Ӿ�ļ���
clause result_clause;//Ԥ�ڵõ��Ľ���

//һЩ��������
bool read_in();
int guijie();
ostream&operator<<(ostream &out, clause &c);

void print_process(clause &present_clause)
{
	present_clause.key = true;//�ڹؼ�·����
	if (present_clause.father == -1 && present_clause.mother == -1)
		return;
	print_process(clause_set[present_clause.father]);
	print_process(clause_set[present_clause.mother]);
	cout << clause_set[present_clause.father] << "  &  " << clause_set[present_clause.mother] << "  ==>  " << present_clause << endl;
}

void draw_process()
{
	fstream out;
	out.open("graph.dot", ios::out);
	out<< "digraph G{ " <<endl<<"rankdir=LR;"<<endl;
	for (int i = 0; i < clause_set.size(); i++) {
		out << "node" << i << "[label=\""<<i<<":" << clause_set[i] << "\"";
		if (clause_set[i].key)
			out << ",color=red";
		out << "];" << endl;
		if (clause_set[i].father != -1 && clause_set[i].mother != -1) {
			out << "node" << clause_set[i].father << " -> node" << i;
			if (clause_set[clause_set[i].father].key&&clause_set[i].key)
				out << "[color=red]";
			out<<";"<<endl;
			out << "node" << clause_set[i].mother << " -> node" << i;
			if (clause_set[clause_set[i].mother].key&&clause_set[i].key)
				out << "[color=red]";
			out << ";" << endl;
		}
	}

	out << "}" << endl;
	system("dot -T png graph.dot -o tree.png");
	system("tree.png");
	return;
}

int main()
{
	if (!read_in())//���ж���
		return -1;	
	
	int state = guijie();//���й��
	cout << endl << "*****************************" << endl;
	
	if (state == 1) {//���н�������
		cout << "�ɹ������²�Ľ���" << endl;
		cout << endl << "*****************************" << endl;
		cout << "������������ʾ" << endl;
		print_process(clause_set.back());
		cout << endl << "*****************************" << endl;
		cout << "���Ƴ�������״�ṹ" << endl;
		draw_process();

	}
	else if (state == 0)
		cout << "�޷������²�Ľ���" << endl;
	else if (state == -1) {
		cout << "�Ӿ��߼����������˳�"<<endl;
		return -1;
	}

	return 0;
}
