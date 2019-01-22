#ifndef HEADER_H
#define HEADER_H

bool randomFirst = true;

unsigned int randomize(
    unsigned int min,
    unsigned int max
  )
{
  if (randomFirst)
  {
    srand(time(NULL));
    randomFirst = false;
  }

  return (rand()% max + min);
}

std::string randomizeStr(int len)
{
  if (randomFirst)
  {
    srand(time(NULL));
    randomFirst = false;
  }
  std::string str = "abcdefghijklmnopqrstuvwxyz";
  std::string newstr;
  int pos;
  while(newstr.size() != len)
  {
    pos = ((rand()%(str.size() - 1)));
    newstr += str.substr(pos, 1);
  }
  return newstr;
}

template <typename TData>
class CArray
{
public: // Interface

  CArray(
      unsigned int _size
    )
  {
    t_size = 0;
    max_size = _size;
    t_data = new TData[max_size];
  }

  CArray(
      const CArray & _array
    );

  ~CArray()
  {
    delete []t_data;
  }

  CArray & operator=(
      const CArray & array
    )
  {
    if (this != &array)
    {
      delete []t_data;
      t_size = array.t_size;
      t_data = new TData;
      for (unsigned int i = 0; i != t_size; ++i)
        t_data[i] = array.t_data[i];
    }
    return *this;
  }

  void push_back(
      const TData & _value
    )
  {
    if (t_size + 1 > max_size)
    {
      std::cout << "in push_back(): No more free space!" << "\n";
      return;
    }
    ++t_size;
    t_data[t_size - 1] = _value;
  }

  void insert(
      unsigned int _index,
      const TData & _value
    )
  {
    ++t_size;
    for (unsigned int i = 1; i != t_size - _index; ++i)
      t_data[t_size - i] = t_data[t_size - i - 1];
    t_data[_index] = _value;
  }

  void erase(
      unsigned int _index
  )
  {
    if (_index >= t_size)
      return;
    for (unsigned int i = _index; i != t_size - 1; ++i)
      t_data[i] = t_data[i + 1];
    --t_size;
  }

  void clear()
  {
    t_size = 0;
  }

  unsigned int size() const
  {
    return t_size;
  }

  TData & operator[](
      unsigned int _index
  )
  {
    return t_data[_index];
  }

  void print()
  {
    if (t_size == 0)
      std::cout << "( )";
    for (unsigned int i = 0; i != t_size; ++i)
      std::cout << t_data[i] << " ";
    std::cout << "\n";
  }

  void sortData()
  {
    if (t_size < 2)
    {
      std::cout << "in sortData(): Nothing to sort!" << "\n";
      return;
    }

    TData n;
    for(unsigned int i = 0; i != (t_size - 1); ++i)
      for(unsigned int j = (i+1); j != t_size ; ++j)
        if (t_data[i] > t_data[j])
        {
          n = t_data[j];
          t_data[j] = t_data[i];
          t_data[i] = n;
        }
  }

  void sortData(
      const TData & _value
    )
  {
    if (t_size < 2)
    {
      std::cout << "in sortData(): Nothing to sort!" << "\n";
      return;
    }

    TData n;
    for(unsigned int i = 0; i != (t_size - 1); ++i)
      for(unsigned int j = (i+1); j != t_size ; ++j)
        if (t_data[i].size() > t_data[j].size())
        {
          n = t_data[j];
          t_data[j] = t_data[i];
          t_data[i] = n;
        }
  }

  void randNumInsert(
      unsigned int _num
    )
  {
    if (t_size < 2)
    {
      std::cout << "in randNumInsert(): Empty array!" << "\n";
      return;
    }
    int index = 0;
    for (unsigned int i = 0; i != _num; ++i)
    {
      index = randomize(0, t_size - 1);
      insert(index, randomize(0, 100));
    }
  }

  void randNumInsert(
      unsigned int _num,
      const TData & _value
    )
  {
    if (t_size < 2)
    {
      std::cout << "in randNumInsert(): Empty array!" << "\n";
      return;
    }
    int index = 0;
    for (unsigned int i = 0; i != _num; ++i)
    {
      index = randomize(0, t_size - 1);
      insert(index, randomizeStr(randomize(1, 8)));
    }
  }

protected: // Attributes
  unsigned int t_size, max_size;
  TData *t_data;

};

#endif // HEADER_H
