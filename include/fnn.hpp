#ifndef _APLYSIA_FNN
#define _APLYSIA_FNN

namespace aps
{
    class fnn final
    {
    public:
        int num_input() const;
        int num_output() const;

        void compute(const float *in, float *out) const;

        fnn(const int *dimension, int length, const float **weights, const float **bais);
        ~fnn();

    private:
        int depth;
        int width;
        int *num_table;

        float **weights;
        float **bais;
    };
}

#endif /* _APLYSIA_FNN */
