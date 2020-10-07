#pragma once
#include "head.h"

extern vector<string> constant_name;//声明用于存储所有常量名的集合
extern vector<string> variable_name;//声明用于存储所有变量名的集合
extern vector<string> function_name;//声明用于存储所有函数名的集合

//常量和变量统一为标识符（identifier）,为方便进一步处理用identifier结构体进行区别
enum identifier_type {CONSTANT,VARIABLE};
typedef struct {
	identifier_type type;//常量还是变量
	int id;//vector中的标号
}identifier;

//原子式的定义  function_name(变量或常量集合)
typedef struct {
	vector<identifier> element;//按顺序存储所有的变量和常量名
	int function_id;//存储这个原子式是哪个function_name
	bool positive;//原子式前面有非，则为false，否则为true
}point;

//子句的定义（element的大小为1则可以判定为为事实）
typedef struct {
	vector<point> element;//按顺序存储所有以或连接的原子句
	int mother;//来源1，没有则置为-1
	int father;//来源2，没有则置为-1
	bool valid;//当一个事实将其他子句中的内容全部替换后，将认定其为无效的
	bool key;//是否在关键路径上
}clause;

extern vector<clause> clause_set;//声明存储所有的子句的集合
extern clause result_clause;//声明预期得到的结论

