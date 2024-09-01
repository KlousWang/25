#include <iostream>
#include <vector>
#include <cassert>
#include <cstdarg>

using namespace std;

#define OK 1
#define ERROR -1
#define MAX_DIM 8

typedef int ElemType;

class Array {
public:
    Array() : dim(0) {}

    int Init(int nDim, ...);
    void Destroy();
    int Assign(ElemType elm, ...);
    int Value(ElemType& elm, ...);

private:
    vector<ElemType> base;
    int dim;
    vector<int> bounds;
    vector<int> constants;

    int Locate(int nDim, va_list ap);
};

int Array::Init(int nDim, ...) {
    if (nDim < 1 || nDim > MAX_DIM) {
        return ERROR;
    }

    dim = nDim;

    bounds.resize(nDim);
    int nElemCount = 1;

    va_list ap;
    va_start(ap, nDim);
    for (int i = 0; i < nDim; ++i) {
        bounds[i] = va_arg(ap, int);
        if (bounds[i] < 0) {
            return ERROR;
        }
        nElemCount *= bounds[i];
    }
    va_end(ap);

    base.resize(nElemCount);
    constants.resize(nDim);

    constants[nDim - 1] = 1;
    for (int i = nDim - 2; i >= 0; --i) {
        constants[i] = bounds[i + 1] * constants[i + 1];
    }

    return OK;
}

void Array::Destroy() {
    // Vectors automatically handle memory deallocation
}

int Array::Locate(int nDim, va_list ap) {
    int nPos = 0;
    for (int i = 0; i < nDim; ++i) {
        int ind = va_arg(ap, int);
        assert(ind >= 0 && ind < bounds[i]);
        nPos += constants[i] * ind;
    }
    return nPos;
}

int Array::Assign(ElemType elm, ...) {
    va_list ap;
    va_start(ap, elm);
    int nPos = Locate(dim, ap);
    va_end(ap);
    base[nPos] = elm;
    return OK;
}

int Array::Value(ElemType& elm, ...) {
    va_list ap;
    va_start(ap, elm);
    int nPos = Locate(dim, ap);
    va_end(ap);
    elm = base[nPos];
    return OK;
}
