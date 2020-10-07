/*************************************************
���cpp��Ҫ������һЩ��horn.h�еĽṹ����صĺ���
��Ƚϴ�С��cout�ȵȣ���Ҫ��Ϊ�˷�������������ʵ��
**************************************************/

#include "horn.h"
//Ϊ��ʹ��map,����ʵ������
bool operator<(identifier a, identifier b)
{
	return a.id > b.id;
}
//���һ���Ӿ�
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
//�ж�ԭ�Ӿ��Ƿ�������������ȫ��һ��
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
