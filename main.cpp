#include"horn.h"

vector<string> constant_name;//用于存储所有常量名的集合
vector<string> variable_name;//用于存储所有变量名的集合
vector<string> function_name;//用于存储所有函数名的集合
vector<clause> clause_set;//存储所有的子句的集合
clause result_clause;//预期得到的结论

//一些函数声明
bool read_in();
int guijie();
ostream&operator<<(ostream &out, clause &c);

void print_process(clause &present_clause)
{
	present_clause.key = true;//在关键路径上
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
	if (!read_in())//进行读入
		return -1;	
	
	int state = guijie();//进行归结
	cout << endl << "*****************************" << endl;
	
	if (state == 1) {//进行结果的输出
		cout << "成功归结出猜测的结论" << endl;
		cout << endl << "*****************************" << endl;
		cout << "归结过程如下所示" << endl;
		print_process(clause_set.back());
		cout << endl << "*****************************" << endl;
		cout << "绘制出归结的树状结构" << endl;
		draw_process();

	}
	else if (state == 0)
		cout << "无法归结出猜测的结论" << endl;
	else if (state == -1) {
		cout << "子句逻辑出错，程序退出"<<endl;
		return -1;
	}

	return 0;
}
