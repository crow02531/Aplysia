#ifndef _APLYSIA_NSNN
#define _APLYSIA_NSNN

#define APLYSIA_NSNN_THRESHOLD 20

namespace aps
{
    class nsnn final
    {
    public:
        enum phase
        {
        };

        class monitor
        {
        public:
            virtual void begin(const nsnn &n);
            virtual void record(phase p, int id, int vm);
            virtual void end();

        private:
        };

        void tick(monitor *m = nullptr);

    private:
        struct synape final
        {
            int pre, post;
            int factor;
        };

        int size;
        int *vm_table;
        synape *synapes;
    };
}

#endif /* _APLYSIA_NSNN */
