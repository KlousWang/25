#include<iostream>
#include<cstdarg>
using namespace std;

#define OK 1;
#define ERROR -1;
#define MAX_VALUE 8;

typedef int ElemType;

typedef struct {
	ElemType* base; 
	int dim;
	int* bounds;
	int* constants;
}Arrary;

int InitArrary(Arrary* pArr, int nDim, ...);
void Distionary(Arrary* pArr);
//初始化数组
//arr指向待初始化的数据
//nDim 数组的维度
//...数组各维度的长度
int InitArrary(Arrary* pArr, int nDim, ...)
{
	if (nDim < 1 || nDim>8)return ERROR;

	//初始化 pArr数组各属性
	pArr->dim = nDim;
	 //构造函数维界基址
	pArr->bounds = new int[nDim];
	if (!pArr->bounds)return ERROR;

	int i = 0, nElemcount = 1;
	va_list ap;
	va_start(ap, nDim);

	/// i =nDim -1 ,使列优先
	for (i = nDim - 1; i >= 0; --i) {
		pArr->bounds[i] = va_arg(ap, int);
		if (pArr->bounds[i] < 0) {
			return ERROR;

			nElemcount *= pArr->bounds[i];

		}
	}
	va_end(ap);
	pArr->base = new ElemType[nElemcount];
	if (pArr->base) {
		return ERROR;
	}

	pArr->constants = new int[nDim];

	//递推求常量地址，列先出
	pArr->constants[nDim - 1] = 1;
	for (i = nDim - 2; i >= 0; --i) {
		pArr->constants[i] = pArr->bounds[i + 1] * pArr->constants[i + 1];
	}
	return OK;
}

void Distionary(Arrary* pArr)
{
	delete[]pArr->base;
	delete[]pArr->bounds;
	delete[]pArr->constants;
}


