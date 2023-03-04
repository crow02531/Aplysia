#include "fnn.hpp"

#include <cmath>
#include <bits/stdc++.h>

int aps::fnn::num_input() const
{
    return num_table[0];
}

int aps::fnn::num_output() const
{
    return num_table[depth];
}

void forward(const float *out0, float *out1, int l0, int l1, const float *w, const float *b)
{
    for (int j = 0; j < l1; ++j)
    {
        float v = 0;

        for (int k = 0; k < l0; ++k)
            v += out0[k] * w[j * l0 + k];

        out1[j] = fmaxf(0, v - b[j]);
    }
}

inline void swap(const float *&a, float *&b)
{
    float *t = b;
    b = const_cast<float *>(a);
    a = t;
}

void aps::fnn::compute(const float *in, float *out) const
{
    int l0 = num_table[0], l1 = num_table[1];
    const float *out0 = in;
    float *out1 = depth == 1 ? out : new float[width];

    forward(out0, out1, l0, l1, weights[0], bais[0]);

    if (depth != 1)
    {
        out0 = depth == 2 ? nullptr : new float[width];

        for (int i = 1; i < depth; ++i)
        {
            l0 = l1;
            l1 = num_table[i + 1];
            swap(out0, out1);

            forward(out0, i + 1 == depth ? out : out1, l0, l1, weights[i], bais[i]);
        }

        delete out0;
        delete out1;
    }
}

aps::fnn::fnn(const int *dimension, int length, const float **weights, const float **bais)
{
    memcpy(num_table = new int[length], dimension, length * sizeof(int));
    depth = length - 1;
    width = *std::max_element(dimension, dimension + length);

    float** p = fnn::weights = new float*[depth];
    for(int i = 0; i < depth; ++i) {
        int l = dimension[i] * dimension[i + 1];
        memcpy(p[i] = new float[l], weights[i], l);
    }

    p = fnn::bais = new float*[depth];
    for(int i = 0; i < depth; ++i) {
        int l = dimension[i];
        memcpy(p[i] = new float[l], bais[i], l);
    }
}

aps::fnn::~fnn()
{
    delete num_table;
    delete weights;
    delete bais;
}
