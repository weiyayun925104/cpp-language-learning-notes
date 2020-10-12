#include <iostream>
#include <string>
#include <typeinfo>

using namespace std;

template <typename  Type>
class VectorOf
{
public:
    VectorOf();
    VectorOf(int initialSize);
    VectorOf(const VectorOf<Type> &other);
    ~VectorOf();

    Type *Get(int index) const;
    void Set(int index, Type value);

    void PushBack(Type value);
    void PushFront(Type value);
    void Clear();
    int size() const;

    VectorOf<Type> &operator=(const VectorOf<Type> &other);
private:
    Type *_values;
    int _valuesLengthUsed;
    int _valuesLength;

    void CopyValues(const VectorOf<Type> &other);
    static Type *growArray(Type *p_values, int *size);
};

template <typename Type>
VectorOf<Type>::VectorOf()
{
    _valuesLength = 32;
    _valuesLengthUsed = 0;
    _values = new Type[_valuesLength];
}

template <typename Type>
VectorOf<Type>::VectorOf(int initialSize)
{
    if (initialSize < 32)
    {
        initialSize = 32;
    }
    _valuesLength = initialSize;
    _valuesLengthUsed = 0;
    _values = new Type[_valuesLength];
}

template <typename Type>
VectorOf<Type>::VectorOf(const VectorOf<Type> &other)
{
    CopyValues(other);
}

template <typename Type>
VectorOf<Type>::~VectorOf()
{
    if ( _values != nullptr )
    {
        delete[] _values;
    }
}

template <typename Type>
Type *VectorOf<Type>::Get(int index) const
{
    if ( (index < 0) || (index >= _valuesLengthUsed) )
    {
        return nullptr;
    }

    return &_values[index];
}

template <typename Type>
void VectorOf<Type>::Set(int index, Type value)
{
    if ( (index < 0) || (index >= _valuesLengthUsed) )
    {
        return;
    }

    _values[index] = value;
}

template <typename Type>
void VectorOf<Type>::PushBack(Type value)
{
    if (_valuesLengthUsed >= _valuesLength)
    {
        _values = growArray(_values, &_valuesLength);
    }
    _values[_valuesLengthUsed] = value;
    _valuesLengthUsed++;
}

template <typename Type>
void VectorOf<Type>::PushFront(Type value)
{
    if (_valuesLengthUsed >= _valuesLength)
    {
        _values = growArray(_values, &_valuesLength);
    }

    for (int i = _valuesLengthUsed; i > 0; i--)
    {
        _values[i] = _values[i - 1];
    }
    _values[0] = value;
    _valuesLengthUsed++;
}

template <typename Type>
void VectorOf<Type>::Clear()
{
    _valuesLengthUsed = 0;
}

template <typename Type>
int VectorOf<Type>::size() const
{
    return _valuesLengthUsed;
}

template <typename Type>
VectorOf<Type> & VectorOf<Type>::operator=(const VectorOf<Type> & other)
{
    if( this == &other)
    {
        return *this;
    }
    if (_values != nullptr)
    {
        delete[] _values;
        _values = nullptr;
    }

    CopyValues(other);

    return *this;
}

template <typename Type>
void VectorOf<Type>::CopyValues(const VectorOf<Type> &other)
{
    _valuesLength = other._valuesLength;
    _values = new Type[_valuesLength];

    _valuesLengthUsed = other._valuesLengthUsed;
    for (int i = 0; i < _valuesLengthUsed; i++)
    {
        Type *value = other.Get(i);
        if (value != nullptr)
        {
            _values[i] = *value;
        }
    }
}

template <typename Type>
Type *VectorOf<Type>::growArray(Type *p_values, int *size)
{
    int oldSize = *size;
    *size *= 2;

    Type *p_newvalues = new Type[*size];
    for (int i = 0; i < oldSize; i++)
    {
        p_newvalues[i] = p_values[i];
    }

    delete[] p_values;

    return p_newvalues;
}

template <typename Type>
void print(VectorOf<Type> &vector)
{
    if (vector.size() <= 0)
    {
        cout << "Vector is empty.\n";
        return;
    }
    cout << "Vector Values...\n";
    int index = 0;
    Type *temp;
    while ( ( temp = vector.Get(index) ) != nullptr )
    {
        cout << *temp << '\n';
        index++;
    }
    cout << '\n';
}


template <typename Type>
void run(Type *defaultInitializationValues, const Type *sizedValues, int sizedSize, Type value1, Type value2, Type value3, Type value4)
{
    cout << "Testing Template VectorOf<T> class of T = " << typeid(Type).name() << '\n';

    VectorOf<Type> basicVector;
    for (int i = 0; i < 32; i++)
    {
        basicVector.PushBack(defaultInitializationValues[i]);
    }
    cout << "Basic Vector\n";
    print(basicVector);

    VectorOf<Type> sizedVector(sizedSize);
    for (int i = 0; i < sizedSize; i++)
    {
        sizedVector.PushBack(sizedValues[i]);
    }
    cout << "Vector Sized to " << sizedSize << '\n';
    print(sizedVector);

    VectorOf<Type> copiedVector(sizedVector);
    cout << "Copied Vector Upon Initialization from Sized Vector\n";
    print(copiedVector);

    VectorOf<Type> copiedVectorOperator;
    copiedVectorOperator = basicVector;
    cout << "Copied Vector Operator from Basic Vector\n";
    print(copiedVectorOperator);

    cout << "Adding " << value1 << " to the end of Sized Vector\n"; // This should also resize the vector.
    sizedVector.PushBack(value1);

    cout << "Adding " << value2 << " to the end of Sized Vector\n"; // This should not resize the vector.
    sizedVector.PushBack(value2);
    print(sizedVector);

    cout << "Adding " << value3 << " to the beginning of Copied Vector\n"; // This should also resize the vector.
    copiedVector.PushFront(value3);

    cout << "Adding " << value4 << " to the beginning of Copied Vector\n"; // This should not resize the vector.
    copiedVector.PushFront(value4);
    print(copiedVector);

    cout << "Clearing Basic Vector\n";
    basicVector.Clear();
    print(basicVector);
}

int main()
{
    int arraySize = 10;

    int *defaultInitializationValuesInt = new int[32];
    for (int i = 0; i < 32; i++)
    {
        defaultInitializationValuesInt[i] = i + 1;
    }

    int *sizedValuesInt = new int[arraySize];
    for (int i = 0; i < arraySize; i++)
    {
        sizedValuesInt[i] = i * i;
    }

    int valueInt1 = 50;
    int valueInt2 = -12;
    int valueInt3 = -666;
    int valueInt4 = 999;

    run(defaultInitializationValuesInt, sizedValuesInt, arraySize, valueInt1, valueInt2, valueInt3, valueInt4);

    double counter = 0;
    double *defaultInitializationValuesDbl = new double[32];
    for (int i = 0; i < 32; i++)
    {
        defaultInitializationValuesDbl[i] = counter + (1.3 / (counter + 1));
        counter++;
    }

    counter = 0;
    double *sizedValuesDbl = new double[arraySize];
    for (int i = 0; i < arraySize; i++)
    {
        sizedValuesDbl[i] = counter * (counter / (counter + 1)) + 0.1;
        counter++;
    }

    double valueDbl1 = 50.342;
    double valueDbl2 = -12.99;
    double valueDbl3 = -666.99;
    double valueDbl4 = 999.66;

    run(defaultInitializationValuesDbl, sizedValuesDbl, arraySize, valueDbl1, valueDbl2, valueDbl3, valueDbl4);
}
