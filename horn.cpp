/*************************************************
这个cpp主要定义了一些与horn.h中的结构体相关的函数
如比较大小，cout等等，主要是为了方便其它函数的实现
**************************************************/

#include "horn.h"
//为了使用map,并无实际意义
bool operator<(identifier a, identifier b)
{
	return a.id > b.id;
}
//输出一个子句
ostream&operator<<(ostream &out, clause &c)
{
	for (int i = 0; i < c.element.size(); i++) {
		if (!c.element[i].positive)
			out << "!";
		out << function_name[c.element[i].function_id] << "(";
		for (int j = 0; j < c.element[i].element.size(); j++) {
			if (c.element[i].element[j].type == VARIABLE)
				out << variable_name[c.element[i].element[j].id];
			else
				out << constant_name[c.element[i].element[j].id];
			if (j != c.element[i].element.size() - 1)
				out << ",";
		}
		out << ")";
		if (i != c.element.size() - 1)
			out << "|";
	}

	return out;
}
//判断原子句是否除变量和真假外全部一致
bool equal_except_v(point &point1, point &point2)
{
	if (point1.function_id == point2.function_id&&
		point1.element.size() == point2.element.size()) {
		for (int i = 0; i < point1.element.size() && i < point2.element.size(); i++) {
			if (point1.element[i].type == VARIABLE || point2.element[i].type == VARIABLE)
				continue;
			if (point1.element[i].id != point2.element[i].id)
				return false;
		}
		return true;
	}
	return false;
}
