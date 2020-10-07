#pragma once
#include "head.h"

extern vector<string> constant_name;//�������ڴ洢���г������ļ���
extern vector<string> variable_name;//�������ڴ洢���б������ļ���
extern vector<string> function_name;//�������ڴ洢���к������ļ���

//�����ͱ���ͳһΪ��ʶ����identifier��,Ϊ�����һ��������identifier�ṹ���������
enum identifier_type {CONSTANT,VARIABLE};
typedef struct {
	identifier_type type;//�������Ǳ���
	int id;//vector�еı��
}identifier;

//ԭ��ʽ�Ķ���  function_name(������������)
typedef struct {
	vector<identifier> element;//��˳��洢���еı����ͳ�����
	int function_id;//�洢���ԭ��ʽ���ĸ�function_name
	bool positive;//ԭ��ʽǰ���зǣ���Ϊfalse������Ϊtrue
}point;

//�Ӿ�Ķ��壨element�Ĵ�СΪ1������ж�ΪΪ��ʵ��
typedef struct {
	vector<point> element;//��˳��洢�����Ի����ӵ�ԭ�Ӿ�
	int mother;//��Դ1��û������Ϊ-1
	int father;//��Դ2��û������Ϊ-1
	bool valid;//��һ����ʵ�������Ӿ��е�����ȫ���滻�󣬽��϶���Ϊ��Ч��
	bool key;//�Ƿ��ڹؼ�·����
}clause;

extern vector<clause> clause_set;//�����洢���е��Ӿ�ļ���
extern clause result_clause;//����Ԥ�ڵõ��Ľ���

