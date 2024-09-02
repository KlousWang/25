#include<iostream>
#include<cstdarg>
#include<cassert>
using namespace std;

#define OK 1  //define预处理
#define ERROR -1

#define MAX_DIM 8 //允许的最大数组维数

typedef int ElemType;  //typedef 关键字   只是给int取一个名字，而不是声明一个int类型的变量

typedef struct
{
	ElemType* base;     //数组元素地址
	int dim;            //数组维度  比如二维数组那么值就是2
	int* bounds;        //数组维界地址    表示数组的各维度的界限
	int* constants;      //数组映像函数常量地址     指向整数的指针，表示数组映像函数的常量地址
}Array;

int InitArray(Array* pArr, int nDim,...);        ///初始化数组 pArr
void DistoryArrary(Array* pArr);             ///释放
int Locate(Array* ptr, int nDim, va_list ap);  ///定位数组下标指向的的元素的在数组中的位置
int Assign(Array* pArr, ElemType* elm,...);
int Value(Array* pArr, ElemType* elm,...);
//初始化数组
//pArr指向待初始化的数组
//pDim指向数组的维度

int InitArray(Array* pArr, int nDim,...)
{
	if (nDim < 1 || nDim>MAX_DIM) {
		return ERROR;
	}

	//初始化pArr数组维数属性
	pArr->dim = nDim;


	//构造数组维界基数
	pArr->bounds = new int[nDim];//注意new的使用方法
	if (!pArr->bounds) {
		return ERROR;
	}
	int i = 0, nElemCount = 1;
	va_list ap;      //这是一个类型，用于声明一个可变参数列表的变量。它用来存储当前参数列表的状态
	va_start(ap, nDim); //这是一个宏，用于初始化 va_list 变量。
	//它将 va_list 变量准备好，使其可以访问从函数参数列表中获取的可变参数。
	//你需要传递最后一个固定参数（通常是函数的最后一个固定参数），它告诉 va_start 可变参数列表的起始位置。
	for (i = 0; i < nDim; ++i) {
		pArr->bounds[i] = va_arg(ap, int);
		if (pArr->bounds[i] < 0) {
			return ERROR;

			nElemCount *= pArr->bounds[i];
		}
	}
	va_end(ap);


	//初始化元素基址
	pArr->base = new ElemType[nElemCount];
	if (!pArr->base) {
		return ERROR;
	}

	//初始化函数映像常数基址
	pArr->constants = new int[nDim];

	//递推求常量基址
	pArr->constants[nDim - 1] = 1;
	for (i = nDim - 2; i >= 0; --i) {
		pArr->constants[i] = pArr->bounds[i + 1] * pArr->constants[i + 1];
	}
	return OK;
}

void DistoryArrary(Array* pArr)
{
	delete[]pArr->base;
	delete[]pArr->bounds;
	delete[]pArr->constants;
}


//定位数组下标指向的元素在数组中的位置
//pArr指向的数组

int Locate(Array* pArr, int nDim, va_list ap)
{
	int nPos = 0, ind = 0, i = 0;
	for (int i = 0; i < pArr->dim; ++i) {
		ind = va_arg(ap, int);

		//使用断言，确保下标合格
		assert(ind >= 0 && ind < pArr->bounds[i]);
		nPos += pArr->constants[i] * ind;
	}

	return nPos;
}

/**
* @brief 数组赋值
*
* @param pArr 指向待赋值的数组
* @param elm 指向赋值元素
* @param nDim 数组维数
* @param ... 数组下标
*
* @param 赋值成功返回 OK, 否则返回 ERROR
*/
int Assign(Array* pArr, ElemType* elm,...)
{
	int nPos = 0;
	va_list ap;
	va_start(ap, elm);
	nPos = Locate(pArr, pArr->dim, ap);
	*(pArr->base + nPos) = *elm;

	return OK;
}

int Value(Array* pArr, ElemType* elm,...)
{
	int nPos = 0;
	va_list ap;
	va_start(ap, elm);
	nPos = Locate(pArr, pArr->dim, ap); //计算多维数组在一维数组中存放的函数
	*elm = *(pArr->base + nPos);
	return OK;
}

int main() {
	Array arr;
	int dims = 2;
	int result;
	ElemType value;

	
	//初始化一个3x4的二维数组
	if (InitArray(&arr, dims, 3, 4) == ERROR)
	{
		cerr << "数据初始化失败" << endl;
		return -1;
	}
	//给（1，2）的位置赋值未10
	value = 10;
	if (Assign(&arr, &value, dims, 1, 2) == ERROR) {
		cerr << "赋值失败" << endl;
		DistoryArrary(&arr);
		return -1;
	}

	//读取（1，2）的值
	if (Value(&arr, &value, dims, 1, 2) == ERROR) {
		cerr << "读取失败" << endl;
		DistoryArrary(&arr);
		return -1;
	}

	cout << "数组（1，2）的值是:" << value << endl;

	//释放数组资源
	DistoryArrary(&arr);
	return 0;
}