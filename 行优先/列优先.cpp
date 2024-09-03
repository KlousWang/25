#include<iostream>
#include<cstdarg>
#include<cassert>
using namespace std;

#define OK 1
#define ERROR -1
#define MAX_VALUE 8

typedef int ElemType;

typedef struct {
	ElemType* base; 
	int dim;
	int* bounds;
	int* constants;
}Arrary;

int InitArrary(Arrary* pArr, int nDim, ...);
void Distionary(Arrary* pArr);
int Locate(Arrary* pArr, int nDim, va_list ap);
int Assign(Arrary* pArr, ElemType* elem, ...);
int Value(Arrary* pArr, ElemType* elem, ...);
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
		if (pArr->bounds[i] <= 0) {
			va_end(ap);
			return ERROR;
		}
		nElemcount *= pArr->bounds[i];
	}
	va_end(ap);
	pArr->base = new ElemType[nElemcount];
	if (!pArr->base) {
		return ERROR;
	}

	pArr->constants = new int[nDim];
	if (!pArr->constants) {
		delete[] pArr->base;
		delete[] pArr->bounds;
		return ERROR;
	}

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


//定位数组下标指向的元素在数组中的位置
int Locate(Arrary* pArr, int nDim, va_list ap)
{
	int nPos = 0, ind = 0;
	for (int i = pArr->dim-1; i>=0 ; --i) {
		ind = va_arg(ap, int);
		//
		assert(ind >= 0 && ind < pArr->bounds[i]);
		nPos += pArr->constants[i] * ind;

	}
	return nPos;
}

int Assign(Arrary* pArr, ElemType* elem, ...)
{
	int nPos = 0;
	va_list ap;
	va_start(ap, elem);
	nPos = Locate(pArr, pArr->dim, ap);
	va_end(ap);
	if (nPos == ERROR) return ERROR;
	*(pArr->base + nPos) = *elem;
	return OK;
}

int Value(Arrary* pArr, ElemType* elem, ...)
{
	int nPos = 0;
	va_list ap;
	va_start(ap, elem);
	nPos = Locate(pArr, pArr->dim, ap);
	va_end(ap);
	if (nPos == ERROR) return ERROR;
	*elem = *(pArr->base + nPos);
	return OK;
}

int main() {
	Arrary arr;
	// 创建一个三维数组，大小为2x3x5
	if (InitArrary(&arr, 3, 2, 3, 5) == ERROR) {
		cout << "初始化数组失败！" << endl;
		return 1;
	}

	int a = 0;
	// 赋值操作
	for (int i = 0; i < 2; ++i) {
		for (int m = 0; m < 3; ++m) {
			for (int n = 0; n < 5; ++n) {
				a = i + m + n;
				if (Assign(&arr, &a, i, m, n) == ERROR) {
					cout << "赋值操作失败！" << endl;
					Distionary(&arr);
					return 1;
				}
			}
		}
	}

	int b = 0;
	// 取值操作
	for (int i = 0; i < 2; ++i) {
		for (int m = 0; m < 3; ++m) {
			for (int n = 0; n < 5; ++n) {
				if (Value(&arr, &b, i, m, n) == ERROR) {
					cout << "取值操作失败！" << endl;
					Distionary(&arr);
					return 1;
				}
				cout << "数组" << b << "的值为[" << i << "," << m << "," << n << "]" << endl;
			}
		}
	}

	Distionary(&arr);
	return 0;
}
