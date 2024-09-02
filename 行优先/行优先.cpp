#include<iostream>
#include<cstdarg>
#include<cassert>
using namespace std;

#define OK 1  //defineԤ����
#define ERROR -1

#define MAX_DIM 8 //������������ά��

typedef int ElemType;  //typedef �ؼ���   ֻ�Ǹ�intȡһ�����֣�����������һ��int���͵ı���

typedef struct
{
	ElemType* base;     //����Ԫ�ص�ַ
	int dim;            //����ά��  �����ά������ôֵ����2
	int* bounds;        //����ά���ַ    ��ʾ����ĸ�ά�ȵĽ���
	int* constants;      //����ӳ����������ַ     ָ��������ָ�룬��ʾ����ӳ�����ĳ�����ַ
}Array;

int InitArray(Array* pArr, int nDim,...);        ///��ʼ������ pArr
void DistoryArrary(Array* pArr);             ///�ͷ�
int Locate(Array* ptr, int nDim, va_list ap);  ///��λ�����±�ָ��ĵ�Ԫ�ص��������е�λ��
int Assign(Array* pArr, ElemType* elm,...);
int Value(Array* pArr, ElemType* elm,...);
//��ʼ������
//pArrָ�����ʼ��������
//pDimָ�������ά��

int InitArray(Array* pArr, int nDim,...)
{
	if (nDim < 1 || nDim>MAX_DIM) {
		return ERROR;
	}

	//��ʼ��pArr����ά������
	pArr->dim = nDim;


	//��������ά�����
	pArr->bounds = new int[nDim];//ע��new��ʹ�÷���
	if (!pArr->bounds) {
		return ERROR;
	}
	int i = 0, nElemCount = 1;
	va_list ap;      //����һ�����ͣ���������һ���ɱ�����б�ı������������洢��ǰ�����б��״̬
	va_start(ap, nDim); //����һ���꣬���ڳ�ʼ�� va_list ������
	//���� va_list ����׼���ã�ʹ����Է��ʴӺ��������б��л�ȡ�Ŀɱ������
	//����Ҫ�������һ���̶�������ͨ���Ǻ��������һ���̶��������������� va_start �ɱ�����б����ʼλ�á�
	for (i = 0; i < nDim; ++i) {
		pArr->bounds[i] = va_arg(ap, int);
		if (pArr->bounds[i] < 0) {
			return ERROR;

			nElemCount *= pArr->bounds[i];
		}
	}
	va_end(ap);


	//��ʼ��Ԫ�ػ�ַ
	pArr->base = new ElemType[nElemCount];
	if (!pArr->base) {
		return ERROR;
	}

	//��ʼ������ӳ������ַ
	pArr->constants = new int[nDim];

	//����������ַ
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


//��λ�����±�ָ���Ԫ���������е�λ��
//pArrָ�������

int Locate(Array* pArr, int nDim, va_list ap)
{
	int nPos = 0, ind = 0, i = 0;
	for (int i = 0; i < pArr->dim; ++i) {
		ind = va_arg(ap, int);

		//ʹ�ö��ԣ�ȷ���±�ϸ�
		assert(ind >= 0 && ind < pArr->bounds[i]);
		nPos += pArr->constants[i] * ind;
	}

	return nPos;
}

/**
* @brief ���鸳ֵ
*
* @param pArr ָ�����ֵ������
* @param elm ָ��ֵԪ��
* @param nDim ����ά��
* @param ... �����±�
*
* @param ��ֵ�ɹ����� OK, ���򷵻� ERROR
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
	nPos = Locate(pArr, pArr->dim, ap); //�����ά������һά�����д�ŵĺ���
	*elm = *(pArr->base + nPos);
	return OK;
}

int main() {
	Array arr;
	int dims = 2;
	int result;
	ElemType value;

	
	//��ʼ��һ��3x4�Ķ�ά����
	if (InitArray(&arr, dims, 3, 4) == ERROR)
	{
		cerr << "���ݳ�ʼ��ʧ��" << endl;
		return -1;
	}
	//����1��2����λ�ø�ֵδ10
	value = 10;
	if (Assign(&arr, &value, dims, 1, 2) == ERROR) {
		cerr << "��ֵʧ��" << endl;
		DistoryArrary(&arr);
		return -1;
	}

	//��ȡ��1��2����ֵ
	if (Value(&arr, &value, dims, 1, 2) == ERROR) {
		cerr << "��ȡʧ��" << endl;
		DistoryArrary(&arr);
		return -1;
	}

	cout << "���飨1��2����ֵ��:" << value << endl;

	//�ͷ�������Դ
	DistoryArrary(&arr);
	return 0;
}