template <class T>
class OdBmIterator;

template <class T>
using OdBmIteratorPtr = std::unique_ptr<OdBmIterator<T>>;

template <class T> class OdBmIterator {
public:
  typedef T value_type;

  //OdBmIterator();
  virtual ~OdBmIterator();
  virtual T object() const;
  virtual bool done() const;
  virtual bool next();

  OdBmIteratorPtr<T> clone() const;
};

%nodefaultctor OdBmIterator;