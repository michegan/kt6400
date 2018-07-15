#ifndef _COMPUTE_H_
#define _COMPUTE_H_


#include <QtCore/qmath.h>


namespace Compute
{
    // ����������
    template<typename T>
    T* newArray(int size)
    {
        T* array = new T[size];
        if (array)
        {
            memset(array, 0, sizeof(T) * size);
        }
        return array;
    }

    // ���
    template<typename T>
    double getSum(const T* datas, int dataLen)
    {
        double sum = 0;

        for (int i = 0; i < dataLen; i++)
        {
            T value = *(datas + i);
            sum += value;
        }

        return sum;
    }

    template<typename T>
    double getMultiSum(const T* datas, int to, int from)
    {
        double sum = 0;

        for (int i = from; i < to; i++)
        {
            T value = *(datas + i);
            sum += (value * i);
        }

        return sum;
    }

    // ��ƽ��ֵ
    template<typename T>
    double getMean(const T* datas, int dataLen)
    {
        double sum = getSum<T>(datas, dataLen);
        return (0 < dataLen ? sum / dataLen : 0.0);
    }

    // �󷽲�
    template<typename T>
    double getSd(const T* datas, int dataLen, int multiply = 1)
    {
        double mean = getMean<T>(datas, dataLen);

        double sum = 0;
        for (int i = 0; i < dataLen; i++)
        {
            T v = *(datas + i);
            sum += (v - mean) * (v - mean);
        }

        double sd = (0 < dataLen ? qSqrt(sum / dataLen) : 0.0);
        return (sd * multiply);
    }

    // �����ϵ��
    template<typename T>
    double getCv(const T* datas, int dataLen)
    {
        double sd = Compute::getSd<T>(datas, dataLen);
        double mean = Compute::getMean<T>(datas, dataLen);

        return (mean ? sd / mean : 0.0);
    }

    // ����ָ����������ֵ����Сֵ��
    template<typename T>
    T getMinimum(const T* datas, int dataLen, int* index = 0)
    {
        T min = 0;
        int k = 0;

        for (int i = 0; i < dataLen; i++)
        {
            T v = *(datas + i);

            if (i == 0)
            {
                min = v;
                k = 0;
            }
            else if (v < min)
            {
                min = v;
                k = i;
            }
        }

        if (index)
        {
            *index = k;
        }

        return min;
    }

    template<typename T>
    T getMaximum(const T* datas, int dataLen, int* index = 0)
    {
        T max = 0;
        int k = 0;

        for (int i = 0; i < dataLen; i++)
        {
            T v = *(datas + i);

            if (i == 0)
            {
                max = v;
                k = 0;
            }
            else if (max < v)
            {
                max = v;
                k = i;
            }
        }

        if (index)
        {
            *index = k;
        }

        return max;
    }

    template<typename T>
    T getMaximum(const T* datas, int dataLen, T target, int* index = 0)
    {
        int k = 0;
        T max = target;

        for (int i = 0; i < dataLen; i++)
        {
            T v = *(datas + i);

            if (max < v)
            {
                max = v;
                k = i;
            }
        }

        if (index)
        {
            *index = k;
        }

        return max;
    }

    template<typename T>
    T getMaxDelta(const T* datas, int dataLen, T target, int* index = 0)
    {
        T max = 0;
        int k = 0;
        T delta = 0;

        for (int i = 0; i < dataLen; i++)
        {
            T v = *(datas + i);

            if (delta < qAbs<T>(v - target))
            {
                delta = qAbs<T>(v - target);
                k = i;
            }
        }

        if (index)
        {
            *index = k;
        }

        return max;
    }

    // ����ָ����������ֵ����Сֵ
    template<typename T>
    T getLastMinimum(const T* datas, int dataLen, int* index = 0)
    {
        T min = 0;
        int k = 0;

        for (int i = 0; i < dataLen; i++)
        {
            T v = *(datas + i);

            if (i == 0)
            {
                min = v;
                k = 0;
            }
            else if (v <= min)
            {
                min = v;
                k = i;
            }
        }

        if (index)
        {
            *index = k;
        }

        return min;
    }

    template<typename T>
    T getLastMaximum(const T* datas, int dataLen, int* index = 0)
    {
        T max = 0;
        int k = 0;

        for (int i = 0; i < dataLen; i++)
        {
            T v = *(datas + i);

            if (i == 0)
            {
                max = v;
                k = 0;
            }
            else if (max <= v)
            {
                max = v;
                k = i;
            }
        }

        if (index)
        {
            *index = k;
        }

        return max;
    }

    // �������ݷ�Χ��������ֵ
    template<typename T>
    T rangeData(T data, T min, T max)
    {
        if (data < min)
        {
            return min;
        }
        else if (max < data)
        {
            return max;
        }
        else
        {
            return data;
        }
    }

    // ����
    template<typename T>
    void sort(T* datas, int dataLen)
    {
        // ð�ݷ�
        for (int i = 0; i < dataLen; i++)
        {
            int k = i;
            T max = *(datas + i);

            for (int j = i + 1; j < dataLen; j++)
            {
                T v = *(datas + j);
                if (max < v)
                {
                    max = v;
                    k = j;
                }
            }

            // ����
            if (i != k)
            {
                T t = *(datas + i);
                *(datas + i) = *(datas + k);
                *(datas + k) = t;
            }
        }
    }

    template<typename T>
    void sort(const T* datas, int* indexes, int dataLen)
    {
        bool* states = new bool[dataLen];
        for (int i = 0; i < dataLen; i++)
        {
            *(states + i) = false;
        }

        for (int i = 0; i < dataLen; i++)
        {
            int k = i;

            // Ѱ�ҵ�һ��Ϊ״̬Ϊfalse��
            for (int j = 0; j < dataLen; j++)
            {
                bool state = *(states + j);
                if (!state)
                {
                    k = j;
                    break;
                }
            }

            // �Ӹõ㿪ʼ�������ֵ
            T max = *(datas + k);

            for (int j = 0; j < dataLen; j++)
            {
                T v = *(datas + j);
                bool state = *(states + j);

                if (max < v && false == state)
                {
                    max = v;
                    k = j;
                }
            }

            // �������ֵ���ڵ�λ��
            *(states + k) = true;
            *(indexes + i) = k;
        }

        delete [] states;
    }
}


#endif // _COMPUTE_H_