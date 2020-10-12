#include "VectorOfInt.h"

namespace WEIYY
{
    namespace JICPP
    {
        VectorOfInt::VectorOfInt()
        {
            _integersLength = 32;
            _integersLengthUsed = 0;
            _integers = new int[_integersLength];
        }

        VectorOfInt::VectorOfInt(int initialSize)
        {
            if (initialSize < 32)
            {
                initialSize = 32;
            }
            _integersLength = initialSize;
            _integersLengthUsed = 0;
            _integers = new int[_integersLength];
        }

        VectorOfInt::VectorOfInt(const VectorOfInt &other)
        {
            CopyValues(other);
        }

        VectorOfInt::~VectorOfInt()
        {
            if ( _integers != nullptr )
            {
                delete[] _integers;
            }
        }

        int *VectorOfInt::GetInt(int index) const
        {
            if ( (index < 0) || (index >= _integersLengthUsed) )
            {
                return nullptr;
            }

            return &_integers[index];
        }

        void VectorOfInt::SetInt(int index, int value)
        {
            if ( (index < 0) || (index >= _integersLengthUsed) )
            {
                return;
            }

            _integers[index] = value;
        }

        void VectorOfInt::PushBack(int value)
        {
            if (_integersLengthUsed >= _integersLength)
            {
                _integers = growArray(_integers, &_integersLength);
            }
            _integers[_integersLengthUsed] = value;
            _integersLengthUsed++;
        }

        void VectorOfInt::PushFront(int value)
        {
            if (_integersLengthUsed >= _integersLength)
            {
                _integers = growArray(_integers, &_integersLength);
            }

            for (int i = _integersLengthUsed; i > 0; i--)
            {
                _integers[i] = _integers[i - 1];
            }
            _integers[0] = value;
            _integersLengthUsed++;
        }

        void VectorOfInt::Clear()
        {
            _integersLengthUsed = 0;
        }
        int VectorOfInt::size() const
        {
            return _integersLengthUsed;
        }

        VectorOfInt &VectorOfInt::operator=(const VectorOfInt &other)
        {
            if( this == &other)
            {
                return *this;
            }
            if (_integers != nullptr)
            {
                delete[] _integers;
                _integers = nullptr;
            }

            CopyValues(other);

            return *this;
        }

        void VectorOfInt::CopyValues(const VectorOfInt &other)
        {
            _integersLength = other._integersLength;
            _integers = new int[_integersLength];

            _integersLengthUsed = other._integersLengthUsed;
            for (int i = 0; i < _integersLengthUsed; i++)
            {
                int *value = other.GetInt(i);
                if (value != nullptr)
                {
                    _integers[i] = *value;
                }
            }
        }

        int *VectorOfInt::growArray(int *p_values, int *size)
        {
            *size *= 2;

            int *p_newvalues = new int[*size];
            for (int i = 0; i < *size; i++)
            {
                p_newvalues[i] = p_values[i];
            }

            delete[] p_values;

            return p_newvalues;
        }
    }
}
