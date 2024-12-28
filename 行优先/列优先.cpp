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


//��λ�����±�ָ���Ԫ���������е�λ��
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
	// ����һ����ά���飬��СΪ2x3x5
	if (InitArrary(&arr, 3, 2, 3, 5) == ERROR) {
		cout << "��ʼ������ʧ�ܣ�" << endl;
		return 1;
	}

	int a = 0;
	// ��ֵ����
	for (int i = 0; i < 2; ++i) {
		for (int m = 0; m < 3; ++m) {
			for (int n = 0; n < 5; ++n) {
				a = i + m + n;
				if (Assign(&arr, &a, i, m, n) == ERROR) {
					cout << "��ֵ����ʧ�ܣ�" << endl;
					Distionary(&arr);
					return 1;
				}
			}
		}
	}

	int b = 0;
	// ȡֵ����
	for (int i = 0; i < 2; ++i) {
		for (int m = 0; m < 3; ++m) {
			for (int n = 0; n < 5; ++n) {
				if (Value(&arr, &b, i, m, n) == ERROR) {
					cout << "ȡֵ����ʧ�ܣ�" << endl;
					Distionary(&arr);
					return 1;
				}
				cout << "����" << b << "��ֵΪ[" << i << "," << m << "," << n << "]" << endl;
			}
		}
	}

	Distionary(&arr);
	return 0;
}
