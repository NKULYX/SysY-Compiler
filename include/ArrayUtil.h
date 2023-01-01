#ifndef TMP_COMPILER_ARRAYUTIL_H
#define TMP_COMPILER_ARRAYUTIL_H

#include "Type.h"
#include "Operand.h"
#include <vector>

class ArrayUtil {
    static Type* currentArrayType;
    static std::vector<int> arrayDims;
    static int currentArrayDim;
    static Operand* arrayAddr;
    static int currentOffset;
public:
    static void init();
    static void setArrayType(Type* type);
    static Type* getArrayType();
    static Type* getElementType();
    static void setcurrentArrayDim(int dim);
    static int getcurrentArrayDim();
    static void incCurrentDim();
    static void decCurrentDim();
    static int getDimSize(int i);
    static void setArrayAddr(Operand* dst);
    static Operand* getArrayAddr();
    static void setCurrentOffset(int offset);
    static int getCurrentOffset();
};


#endif //TMP_COMPILER_ARRAYUTIL_H
