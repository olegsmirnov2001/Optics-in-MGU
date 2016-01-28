//{///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////КЛАСС <<array_t>>///////////////////////////////////////////////////////
//}///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <typename T, int Sz = 0>
struct stt
    {
    T data [Sz];
    int sz;

    stt () :
        data (),
        sz (Sz)
        {
        for (int number = 0; number < sz; number++)
            data [number] = T ();

        DEBUG printf ("\nСоздан массив stt размера %d\n", sz);
        }

    stt (int);

    ~stt () {};

    stt (const stt <T, Sz> & arr)
        {
        for (int number = 0; number < arr.sz; number++)
            data [number] = arr.data [number];
        }

    T* Move (int);

    stt <T, Sz> & operator = (const stt <T, Sz> & arr)
        {
        for (int number = 0; number < arr.sz; arr++)
            data [number] = arr [number];
        }
    };

template <typename T, int Sz = 0>
struct dyn
    {
    public:

    T* data;
    int sz;

    dyn () :
        data (NULL),
        sz (0)
        {
        DEBUG printf ("Создался объект типа dyn размера 0\n");
        }

    dyn (int szNew) :
        data ((T*) new T [szNew]),
        sz (szNew)
        {
        for (int number = 0; number < sz; number++)
            data [number] = T ();

        DEBUG printf ("Создался объект типа dyn размера %d\n", sz);
        }

    ~dyn ()
        {
        delete (data);
        DEBUG printf ("Удален объект типа dyn размера %d\n", sz);
        }

    dyn (const dyn <T, Sz> & arr)
        {
        for (int number = 0; number < arr.sz; number++)
            data [number] = arr.data [number];
        }

    T* Move (int szNew)
        {
        if (data == NULL)
            data = (T*) new T [szNew];
        else
            data = (T*) realloc (data, sizeof (*data) * szNew);

        for (int number = sz; number < szNew; number++)
            data [number] = T ();

        DEBUG printf ("\nУ массива dyn изменен размер с %d на %d\n", sz, szNew);

        sz = szNew;

        return data;
        }

    dyn <T, Sz> & operator = (const dyn <T, Sz> & arr)
        {
        for (int number = 0; number < arr.sz; number++)
            data [number] = arr.data [number];

        sz = arr.sz;
        }
    };

template <template <typename, int> class Type, typename T, int Sz = 0>
class array_t : public Type <T, Sz>
    {
    public:

    array_t () :
        Type <T, Sz> ()
        {}

    array_t (int szNew) :
        Type <T, Sz> (szNew)
        {}

    T& operator [] (int num)
        {
        if (((num < 0) || (num >= this->sz)))
            {
            char err [LengthText] = "";
            sprintf (err, "You made an error in array using <0, %d, %d>", num, Type<T, Sz> :: sz);

            AllGoneBad (err);
            }

        return this->data [num];
        }

    array_t (const array_t & arr) :
        Type <T, Sz> ()
        {}
    };

//{///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////КЛАСС МАТРИЦЫ (МАССИВ МАССИВОВ)///////////////////////////////////////////////
//}///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <typename T, int Sz1 = 0, int Sz2 = 0>
class matrix_t : public array_t <stt, array_t <stt, T, Sz2>, Sz1>
    {
    int sz1, sz2;

    public:

    matrix_t () :
        array_t <stt, array_t <stt, T, Sz2>, Sz1> (),
        sz1 (Sz1),
        sz2 (Sz2)
        {}

    matrix_t (int, int);
    };

template <>
template <typename T>
class matrix_t <T, 0, 0> : public array_t <dyn, array_t <dyn, T> >
    {
    public:

    int sz1, sz2;

    matrix_t (int Size1, int Size2) :
        array_t <dyn, array_t <dyn, T> > (),
        sz1 (Size1),
        sz2 (Size2)
        {
        array_t <dyn, array_t <dyn, T> >::Move (sz1);
        for (int number = 0; number < sz1; number++)
            array_t <dyn, array_t <dyn, T> >::data[number].Move (sz2);
        }
    };

template <int Sz1, int Sz2>
bool PrintfMatrix (matrix_t <int, Sz1, Sz2> & matr)
    {
    DEBUG printf ("Распечатывается матрица размера %d %d\n", matr.sz1, matr.sz2);

    for (int number1 = 0; number1 < matr.sz1; number1++, printf ("\n"))
        for (int number2 = 0; number2 < matr.sz2; number2++)
            printf ("%d ", matr [number1][number2]);

    return true;
    }
















