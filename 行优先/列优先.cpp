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
//��ʼ������
//arrָ�����ʼ��������
//nDim �����ά��
//...�����ά�ȵĳ���
int InitArrary(Arrary* pArr, int nDim, ...)
{
	if (nDim < 1 || nDim>8)return ERROR;

	//��ʼ�� pArr���������
	pArr->dim = nDim;
	 //���캯��ά���ַ
	pArr->bounds = new int[nDim];
	if (!pArr->bounds)return ERROR;

	int i = 0, nElemcount = 1;
	va_list ap;
	va_start(ap, nDim);

	/// i =nDim -1 ,ʹ������
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

	//����������ַ�����ȳ�
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


