#include "../include/ArrayUtil.h"


Type* ArrayUtil::currentArrayType;
std::vector<int> ArrayUtil::arrayDims;
int ArrayUtil::currentArrayDim;
Operand* ArrayUtil::arrayAddr;
int ArrayUtil::currentOffset;

void ArrayUtil::init() {
    currentArrayType = nullptr;
    arrayDims.clear();
    currentArrayDim = -1;
    arrayAddr = nullptr;
    currentOffset = 0;
};

void ArrayUtil::setArrayType(Type* type) {
    currentArrayType = type;
    if(type->isIntArray()) {
        arrayDims = dynamic_cast<IntArrayType*>(type)->getDimensions();
    }
    else if(type->isFloatArray()) {
        arrayDims = dynamic_cast<FloatArrayType*>(type)->getDimensions();
    }
    else if(type->isConstIntArray()) {
        arrayDims = dynamic_cast<ConstIntArrayType*>(type)->getDimensions();
    }
    else if(type->isConstFloatArray()) {
        arrayDims = dynamic_cast<ConstFloatArrayType*>(type)->getDimensions();
    }
    else {
        throw "Invalid array type";
    }
    arrayDims.push_back(1);
};

Type* ArrayUtil::getArrayType() {
    return currentArrayType;
};

Type* ArrayUtil::getElementType() {
    if(currentArrayType->isIntArray()) {
        return TypeSystem::intType;
    }
    else if(currentArrayType->isFloatArray()) {
        return TypeSystem::floatType;
    }
    else if(currentArrayType->isConstIntArray()) {
        return TypeSystem::constIntType;
    }
    else if(currentArrayType->isConstFloatArray()) {
        return TypeSystem::constFloatType;
    }
    else {
        throw "Invalid array type";
    }
}

void ArrayUtil::setcurrentArrayDim(int dim) {
    currentArrayDim = dim;
};

int ArrayUtil::getcurrentArrayDim() {
    return currentArrayDim;
};

void ArrayUtil::incCurrentDim() {
    currentArrayDim++;
};

void ArrayUtil::decCurrentDim() {
    currentArrayDim--;
};

int ArrayUtil::getDimSize(int i) {
    return arrayDims[i];
};

void ArrayUtil::setArrayAddr(Operand* dst) {
    arrayAddr = dst;
};

Operand* ArrayUtil::getArrayAddr() {
    return arrayAddr;
};

void ArrayUtil::setCurrentOffset(int offset) {
    currentOffset = offset;
};

int ArrayUtil::getCurrentOffset() {
    return currentOffset;
};