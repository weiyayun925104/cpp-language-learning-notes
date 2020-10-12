#pragma once
#ifndef VECTOROFINT_H_
#define VECTOROFINT_H_

namespace WEIYY
{
    namespace JICPP
    {
        class VectorOfInt
        {
        public:
            VectorOfInt();
            VectorOfInt(int initialSize);
            VectorOfInt(const VectorOfInt &other);
            ~VectorOfInt();

            int *GetInt(int index) const;
            void SetInt(int index, int value);

            void PushBack(int value);
            void PushFront(int value);
            void Clear();
            int size() const;

            VectorOfInt &operator=(const VectorOfInt &other);
        private:
            int *_integers;
            int _integersLengthUsed;
            int _integersLength;

            void CopyValues(const VectorOfInt &other);
            static int *growArray(int *p_values, int *size);
        };
    }
}

#endif
