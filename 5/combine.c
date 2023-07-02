#include "csapp.h"

#include "machine.h"
#include "opt/combine.h"

/* Implementation with maximum use of data abstraction */
void
combine1(vec_ptr v, data_t *dest)
{
    long i;

    /* Initialize */
    *dest = IDENT;

    /* Combine */
    for (i = 0; i < vec_length(v); i++) {
        data_t val;
        get_vec_element(v, i, &val);
        *dest = *dest OP val;
    }
}

/*
 * Move call to vec_length out of loop
 * 优化：将vec_length的调用移出循环，称为代码移动（code motion）
 */
void
combine2(vec_ptr v, data_t *dest)
{
    long i;
    long length = vec_length(v);

    /* Initialize */
    *dest = IDENT;

    /* Combine */
    for (i = 0; i < length; i++)
    {
        data_t val;
        get_vec_element(v, i, &val);
        *dest = *dest OP val;
    }
}

/**
 * Direct access to vector data
 * 优化：消除函数调用，直接访问向量数据
*/
void
combine3(vec_ptr v, data_t *dest)
{
    long i;
    long length = vec_length(v);
    data_t *data = get_vec_start(v);

    *dest = IDENT;
    for (i = 0; i < length; i++)
    {
        *dest = *dest OP data[i];
    }
}

/**
 * Accumulate result in local variable
 * 优化：将结果累积到局部变量中
*/
void
combine4(vec_ptr v, data_t *dest)
{
    long i;
    long length = vec_length(v);
    data_t *data = get_vec_start(v);
    data_t acc = IDENT;

    for (i = 0; i < length; i++)
    {
        acc = acc OP data[i];
    }
    *dest = acc;
}

/**
 * 2 x 1 loop unrolling
 * 优化：循环展开
 */
void
combine5(vec_ptr v, data_t *dest)
{
    long i;
    long length = vec_length(v);
    long limit = length - 1;
    data_t *data = get_vec_start(v);
    data_t acc = IDENT;

    /* Combine 2 elements at a time */
    for (i = 0; i < limit; i += 2)
    {
        acc = (acc OP data[i]) OP data[i + 1];
    }

    /* Finish any remaining elements */
    for (; i < length; i++)
    {
        acc = acc OP data[i];
    }
    *dest = acc;
}

/**
 * 2 x 2 loop unrolling
*/
void
combine6(vec_ptr v, data_t *dest)
{
    long i;
    long length = vec_length(v);
    long limit = length - 1;
    data_t *data = get_vec_start(v);
    data_t acc0 = IDENT;
    data_t acc1 = IDENT;

    /* Combine 2 elements at a time */
    for (i = 0; i < limit; i += 2)
    {
        acc0 = acc0 OP data[i];
        acc1 = acc1 OP data[i + 1];
    }

    /* Finish any remaining elements */
    for (; i < length; i++)
    {
        acc0 = acc0 OP data[i];
    }
    *dest = acc0 OP acc1;
}

/**
 * 2 x 1a loop unrolling
*/
void
combine7(vec_ptr v, data_t *dest)
{
    long i;
    long length = vec_length(v);
    long limit = length - 1;
    data_t *data = get_vec_start(v);
    data_t acc = IDENT;

    /* Combine 2 elements at a time */
    for (i = 0; i < limit; i += 2)
    {
        acc = acc OP (data[i] OP data[i + 1]);
    }

    /* Finish any remaining elements */
    for (; i < length; i++)
    {
        acc = acc OP data[i];
    }
    *dest = acc;
}

void
count_cpe(const char *name, void (*func)(vec_ptr v, data_t *dest), vec_ptr v, data_t *dest)
{
    long length = vec_length(v);

    clock_t start = clock();
    func(v, dest);
    clock_t end = clock();

    double cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    double cycles_used = cpu_time_used * CPU_FREQUENCY;  // 你的CPU频率，单位为Hz
    double cpe = cycles_used / length;

    printf("%s-%s-%ld CPE: %f\n", OP_NAME, name, length, cpe);
}

int
main(int argc, char *argv[])
{
    long elemt[] = {1000, 10000, 100000, 1000000, 0};

    for (int i = 0; elemt[i] != 0; i++)
    {
        vec_ptr v = new_vec(elemt[i]);
        data_t dest;

        for (int j = 0; j < elemt[i]; j++)
        {
            set_vec_element(v, j, j + 1);
        }

        count_cpe("combine1", combine1, v, &dest);
        count_cpe("combine2", combine2, v, &dest);
        count_cpe("combine3", combine3, v, &dest);
        count_cpe("combine4", combine4, v, &dest);
        count_cpe("combine5", combine5, v, &dest);
        count_cpe("combine6", combine6, v, &dest);
        count_cpe("combine7", combine7, v, &dest);
    }

    return 0;
}