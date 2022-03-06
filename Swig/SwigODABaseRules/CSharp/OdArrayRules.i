%ignore OdArrayBuffer;

%include "OdArrayPreDef.h"
%include "OdArray.h"

%define STRINGIZE(X)
#X
%enddef

%define ODARRAY_IMPL(CSINTERFACE, ALLOCATOR, CONST_REFERENCE, CTYPE...)
%typemap(csinterfaces) OdArray< CTYPE, ALLOCATOR<CTYPE> >, OdArray< CTYPE > "IDisposable, System.Collections.IEnumerable\n, System.Collections.Generic.CSINTERFACE<$typemap(cstype, CTYPE)>\n";
%typemap(cscode) OdArray< CTYPE, ALLOCATOR<CTYPE> >, OdArray< CTYPE > %{
  public $csclassname(System.Collections.ICollection c) : this() {
    if (c == null)
      throw new ArgumentNullException("c");
    foreach ($typemap(cstype, CTYPE) element in c) {
      this.Add(element);
    }
  }

  public $csclassname()
      : this($modulePINVOKE.new_$csclassname__SWIG_0(), MemoryManager.GetMemoryManager().GetCurrentTransaction() == null)
  {
      MemoryTransaction mTr = MemoryManager.GetMemoryManager().GetCurrentTransaction(); // MemoryTransaction #9
      if (null != mTr)
      {
          mTr.AddObject(new $csclassname(swigCPtr.Handle, true));
      }
      if ($modulePINVOKE.SWIGPendingException.Pending) throw $modulePINVOKE.SWIGPendingException.Retrieve();
  }

  public $csclassname($csclassname other) : this($modulePINVOKE.new_$csclassname__SWIG_1($csclassname.getCPtr(other)), MemoryManager.GetMemoryManager().GetCurrentTransaction() == null) {
      MemoryTransaction mTr = MemoryManager.GetMemoryManager().GetCurrentTransaction(); // MemoryTransaction #10
      if (null != mTr)
      {
          mTr.AddObject(new $csclassname(swigCPtr.Handle, true));
      }
    if ($modulePINVOKE.SWIGPendingException.Pending) throw $modulePINVOKE.SWIGPendingException.Retrieve();
  }

  public $csclassname(int capacity) : this($modulePINVOKE.new_$csclassname__SWIG_2(capacity), MemoryManager.GetMemoryManager().GetCurrentTransaction() == null) {
      MemoryTransaction mTr = MemoryManager.GetMemoryManager().GetCurrentTransaction(); // MemoryTransaction #11
      if (null != mTr)
      {
          mTr.AddObject(new $csclassname(swigCPtr.Handle, true));
      }
    if ($modulePINVOKE.SWIGPendingException.Pending) throw $modulePINVOKE.SWIGPendingException.Retrieve();
  }

  public bool IsFixedSize {
    get {
      return false;
    }
  }

  public bool IsReadOnly {
    get {
      return false;
    }
  }

  public $typemap(cstype, CTYPE) this[int index]  {
    get {
      return getitem(index);
    }
    set {
      setitem(index, value);
    }
  }

  public int Capacity {
    get {
      return (int)capacity();
    }
    set {
      if (value < size())
        throw new ArgumentOutOfRangeException("Capacity");
      reserve((uint)value);
    }
  }

  public int Count {
    get {
      return (int)size();
    }
  }

  public bool IsSynchronized {
    get {
      return false;
    }
  }

  public void CopyTo($typemap(cstype, CTYPE)[] array)
  {
    CopyTo(0, array, 0, this.Count);
  }

  public void CopyTo($typemap(cstype, CTYPE)[] array, int arrayIndex)
  {
    CopyTo(0, array, arrayIndex, this.Count);
  }

  public void CopyTo(int index, $typemap(cstype, CTYPE)[] array, int arrayIndex, int count)
  {
    if (array == null)
      throw new ArgumentNullException("array");
    if (index < 0)
      throw new ArgumentOutOfRangeException("index", "Value is less than zero");
    if (arrayIndex < 0)
      throw new ArgumentOutOfRangeException("arrayIndex", "Value is less than zero");
    if (count < 0)
      throw new ArgumentOutOfRangeException("count", "Value is less than zero");
    if (array.Rank > 1)
      throw new ArgumentException("Multi dimensional array.", "array");
    if (index+count > this.Count || arrayIndex+count > array.Length)
      throw new ArgumentException("Number of elements to copy is too large.");
    for (int i=0; i<count; i++)
      array.SetValue(getitemcopy(index+i), arrayIndex+i);
  }

  System.Collections.Generic.IEnumerator<$typemap(cstype, CTYPE)> System.Collections.Generic.IEnumerable<$typemap(cstype, CTYPE)>.GetEnumerator() {
    return new $csclassnameEnumerator(this);
  }

  System.Collections.IEnumerator System.Collections.IEnumerable.GetEnumerator() {
    return new $csclassnameEnumerator(this);
  }

  public $csclassnameEnumerator GetEnumerator() {
    return new $csclassnameEnumerator(this);
  }

  // Type-safe enumerator
  /// Note that the IEnumerator documentation requires an InvalidOperationException to be thrown
  /// whenever the collection is modified. This has been done for changes in the size of the
  /// collection but not when one of the elements of the collection is modified as it is a bit
  /// tricky to detect unmanaged code that modifies the collection under our feet.
  public sealed class $csclassnameEnumerator : System.Collections.IEnumerator
    , System.Collections.Generic.IEnumerator<$typemap(cstype, CTYPE)>
  {
    private $csclassname collectionRef;
    private int currentIndex;
    private object currentObject;
    private int currentSize;

    public $csclassnameEnumerator($csclassname collection) {
      collectionRef = collection;
      currentIndex = -1;
      currentObject = null;
      currentSize = collectionRef.Count;
    }

    // Type-safe iterator Current
    public $typemap(cstype, CTYPE) Current {
      get {
        if (currentIndex == -1)
          throw new InvalidOperationException("Enumeration not started.");
        if (currentIndex > currentSize - 1)
          throw new InvalidOperationException("Enumeration finished.");
        if (currentObject == null)
          throw new InvalidOperationException("Collection modified.");
        return ($typemap(cstype, CTYPE))currentObject;
      }
    }

    // Type-unsafe IEnumerator.Current
    object System.Collections.IEnumerator.Current {
      get {
        return Current;
      }
    }

    public bool MoveNext() {
      int size = collectionRef.Count;
      bool moveOkay = (currentIndex+1 < size) && (size == currentSize);
      if (moveOkay) {
        currentIndex++;
        currentObject = collectionRef[currentIndex];
      } else {
        currentObject = null;
      }
      return moveOkay;
    }

    public void Reset() {
      currentIndex = -1;
      currentObject = null;
      if (collectionRef.Count != currentSize) {
        throw new InvalidOperationException("Collection modified.");
      }
    }

    public void Dispose() {
        currentIndex = -1;
        currentObject = null;
    }
  }
%}
  public:
    %rename(Clear) clear;
    void clear();
    %rename(Add) push_back;
    void push_back(CONST_REFERENCE x);
    size_t size() const;
    size_t capacity() const;
    void reserve(size_t n);
    void resize(size_t logicalLength);
    %newobject GetRange(int index, int count);
    %newobject Repeat(CONST_REFERENCE value, int count);
    //OdArray();
    //OdArray(const OdArray &other);
    %extend {
      /*OdArray(int capacity) {
      return new OdArray< CTYPE, ALLOCATOR<CTYPE> >(capacity);
      }*/
      CTYPE getitemcopy(int index) const {
        if (index>=0 && index<(int)$self->size())
          return (*$self)[index];
        else
          throw OdError_InvalidIndex();
      }
      CONST_REFERENCE getitem(int index) const {
        if (index>=0 && index<(int)$self->size())
          return (*$self)[index];
        else
          throw OdError_InvalidIndex();
      }
      void setitem(int index, CONST_REFERENCE val) {
        if (index>=0 && index<(int)$self->size())
          (*$self)[index] = val;
        else
          throw OdError_InvalidIndex();
      }
      // Takes a deep copy of the elements unlike ArrayList.AddRange
      void AddRange(const OdArray< CTYPE, ALLOCATOR<CTYPE> >& values) {
        $self->insert($self->end(), values.begin(), values.end());
      }
      // Takes a deep copy of the elements unlike ArrayList.GetRange
      OdArray< CTYPE, ALLOCATOR<CTYPE> > *GetRange(int index, int count)  const
      {
        if (index < 0)
          throw OdError_InvalidIndex();
        if (count < 0)
          throw OdError_InvalidIndex();
        if (index >= (int)$self->size()+1 || index+count > (int)$self->size())
          throw OdError_InvalidIndex();
        OdArray< CTYPE, ALLOCATOR<CTYPE> > *result = new OdArray< CTYPE, ALLOCATOR<CTYPE> >();
        result->assign($self->begin()+index, $self->begin()+index+count);
        return result;
      }
      void Insert(int index, CONST_REFERENCE x)  {
        if (index>=0 && index<(int)$self->size()+1)
          $self->insert($self->begin()+index, x);
        else
          throw OdError_InvalidIndex();
      }
      // Takes a deep copy of the elements unlike ArrayList.InsertRange
      void InsertRange(int index, const OdArray< CTYPE, ALLOCATOR<CTYPE> >& values)  {
        if (index>=0 && index<(int)$self->size()+1)
          $self->insert($self->begin()+index, values.begin(), values.end());
        else
          throw OdError_InvalidIndex();
      }
      void RemoveAt(int index)  {
        if (index>=0 && index<(int)$self->size())
          $self->erase($self->begin() + index);
        else
          throw OdError_InvalidIndex();
      }
      void RemoveRange(int index, int count)  {
        if (index < 0)
          throw OdError_InvalidIndex();
        if (count < 0)
          throw OdError_InvalidIndex();
        if (index >= (int)$self->size()+1 || index+count > (int)$self->size())
          throw OdError_InvalidIndex();
        $self->erase($self->begin()+index, $self->begin()+index+count);
      }
      static OdArray< CTYPE, ALLOCATOR<CTYPE> > *Repeat(CONST_REFERENCE value, int count)  {
        if (count < 0)
          throw OdError_InvalidIndex();
        OdArray< CTYPE, ALLOCATOR<CTYPE> >* result = new OdArray< CTYPE, ALLOCATOR<CTYPE> >();
        result->resize(count, value);
        return result;
      }
      void Reverse() {
        $self->reverse();
      }
      void Reverse(int index, int count)  {
        if (index < 0)
          throw OdError_InvalidIndex();
        if (count < 0)
          throw OdError_InvalidIndex();
        if (index >= (int)$self->size()+1 || index+count > (int)$self->size())
          throw OdError_InvalidIndex();
        std::reverse($self->begin()+index, $self->begin()+index+count);
      }
      // Takes a deep copy of the elements unlike ArrayList.SetRange
      void SetRange(int index, const OdArray< CTYPE, ALLOCATOR<CTYPE> >& values)  {
        if (index < 0)
          throw OdError_InvalidIndex();
        if (index+values.size() > $self->size())
          throw OdError_InvalidIndex();
        std::copy(values.begin(), values.end(), $self->begin()+index);
      }
      bool Contains(CONST_REFERENCE value) const {
        return $self->contains(value);
      }
      int IndexOf(CONST_REFERENCE value) const {
        int index = -1;
        OdArray< CTYPE, ALLOCATOR<CTYPE> >::const_iterator it = std::find($self->begin(), $self->end(), value);
        if (it != $self->end())
          index = (int)(it - $self->begin());
        return index;
      }
      int LastIndexOf(CONST_REFERENCE value) const {
    if(!$self->empty())
    {
      OdArray< CTYPE, ALLOCATOR<CTYPE> >::size_type len = $self->length();
      CTYPE* pData = const_cast<CTYPE*>(&const_cast<OdArray< CTYPE, ALLOCATOR<CTYPE> >*>($self)->first());
      for(OdArray< CTYPE, ALLOCATOR<CTYPE> >::size_type i = len-1; i >= 0; --i)
      {
        if(pData[i] == value)
        {
          return i;
        }
      }
    }
    return -1;
      }
      bool Remove(CONST_REFERENCE value) {
        return $self->remove(value);
      }
    }
%enddef

%define ODARRAY_TYPEMAP_SEPARETE_CS_AND_CPP_TYPES(CS_ARRAYTYPE,CPP_ARRAYTYPE)
%typemap(cstype, out="CS_ARRAYTYPE") CPP_ARRAYTYPE, CPP_ARRAYTYPE&, const CPP_ARRAYTYPE&, CPP_ARRAYTYPE* "CS_ARRAYTYPE"
%typemap(csout, excode=SWIGEXCODE) CPP_ARRAYTYPE, CPP_ARRAYTYPE&, const CPP_ARRAYTYPE&, CPP_ARRAYTYPE* 
{
// csout array 
  CS_ARRAYTYPE res = new CS_ARRAYTYPE($imcall,false); 
  $excode
  return res;
}
%typemap(csvarout, excode=SWIGEXCODE) CPP_ARRAYTYPE, CPP_ARRAYTYPE&, const CPP_ARRAYTYPE& , CPP_ARRAYTYPE*
%{
  get 
  {
  // csvarout array
    CS_ARRAYTYPE res = new CS_ARRAYTYPE($imcall,false); 
    $excode
    return res;
  }
%}
%typemap(csin) CPP_ARRAYTYPE, CPP_ARRAYTYPE&, const CPP_ARRAYTYPE&, CPP_ARRAYTYPE* "CS_ARRAYTYPE.getCPtr($csinput)"
%typemap(csdirectorin) CPP_ARRAYTYPE, CPP_ARRAYTYPE&, const CPP_ARRAYTYPE&, CPP_ARRAYTYPE* "new CS_ARRAYTYPE($iminput, false)"
%enddef

%define ODARRAY_TYPEMAP(ARRAYTYPE)
ODARRAY_TYPEMAP_SEPARETE_CS_AND_CPP_TYPES(ARRAYTYPE,ARRAYTYPE)
%enddef

%define ODARRAY_INNER_IMPL(ARRAYTYPE, CTYPE, ALLOCATOR)
%nodefaultctor OdArray< CTYPE, ALLOCATOR<CTYPE> >;
%ignore OdArray::OdArray;
%pragma(csharp) imclasscode=
%{
  [DllImport("$dllimport", EntryPoint=STRINGIZE(CSharp_new_ ## ARRAYTYPE ## __SWIG_0))]
  public static extern IntPtr new_ ## ARRAYTYPE ## __SWIG_0();

  [DllImport("$dllimport", EntryPoint=STRINGIZE(CSharp_new_ ## ARRAYTYPE ## __SWIG_1))]
  public static extern IntPtr new_ ## ARRAYTYPE ## __SWIG_1(HandleRef jarg1);

  [DllImport("$dllimport", EntryPoint=STRINGIZE(CSharp_new_ ## ARRAYTYPE ## __SWIG_2))]
  public static extern IntPtr new_ ## ARRAYTYPE ## __SWIG_2(int jarg1);
%}

%wrapper
%{
SWIGEXPORT void * SWIGSTDCALL CSharp_new_ ## ARRAYTYPE ## __SWIG_0() {
  void * jresult ;
  OdArray< CTYPE, ALLOCATOR<CTYPE> > *result = 0 ;
  
  {
    try 
    {
      result = (OdArray< CTYPE, ALLOCATOR<CTYPE> > *)new OdArray< CTYPE, ALLOCATOR<CTYPE> >();
    }
    catch (OdError& Err) 
    {
      SWIG_CSharpSetPendingExceptionCustom(Err.context());
    }
  }
  jresult = (void *)result; 
  return jresult;
}


SWIGEXPORT void * SWIGSTDCALL CSharp_new_ ## ARRAYTYPE ## __SWIG_1(void * jarg1) {
  void * jresult ;
  OdArray< CTYPE, ALLOCATOR<CTYPE> > *arg1 = 0 ;
  OdArray< CTYPE, ALLOCATOR<CTYPE> > *result = 0 ;
  
  arg1 = (OdArray< CTYPE, ALLOCATOR<CTYPE> > *)jarg1;
  if (!arg1) {
    SWIG_CSharpSetPendingExceptionArgument(SWIG_CSharpArgumentNullException, STRINGIZE(ARRAYTYPE_ ## const & type is null), 0);
    return 0;
  } 
  {
    try 
    {
      result = (OdArray< CTYPE, ALLOCATOR<CTYPE> > *)new OdArray< CTYPE, ALLOCATOR<CTYPE> >((OdArray< CTYPE, ALLOCATOR<CTYPE> > const &)*arg1);
    }
    catch (OdError& Err) 
    {
      SWIG_CSharpSetPendingExceptionCustom(Err.context());
    }
  }
  jresult = (void *)result; 
  return jresult;
}


SWIGEXPORT void * SWIGSTDCALL CSharp_new_ ## ARRAYTYPE ## __SWIG_2(int jarg1) {
  void * jresult ;
  int arg1 ;
  OdArray< CTYPE, ALLOCATOR<CTYPE> > *result = 0 ;
  
  arg1 = (int)jarg1; 
  {
    try 
    {
      result = (OdArray< CTYPE, ALLOCATOR<CTYPE> > *)new OdArray< CTYPE, ALLOCATOR<CTYPE> >(arg1);
    }
    catch (OdError& Err) 
    {
      SWIG_CSharpSetPendingExceptionCustom(Err.context());
    }
  }
  jresult = (void *)result; 
  return jresult;
}
%}
%enddef

%define ODARRAY_SEPARATE_ARRAY_TYPES(CS_ARRAYTYPE, CPP_ARRAYTYPE, CTYPE...)
  template<> class OdArray< CTYPE, OdObjectsAllocator<CTYPE> > {
    ODARRAY_IMPL(IList, OdObjectsAllocator, %arg(CTYPE const&), %arg(CTYPE))
  };
  template<> class OdArray<CTYPE> {
    ODARRAY_IMPL(IList, OdObjectsAllocator, %arg(CTYPE const&), %arg(CTYPE))
  };
  ODARRAY_INNER_IMPL(CS_ARRAYTYPE, CTYPE, OdObjectsAllocator)
  ODARRAY_TYPEMAP_SEPARETE_CS_AND_CPP_TYPES(CS_ARRAYTYPE,CPP_ARRAYTYPE)
  %template(CS_ARRAYTYPE) OdArray<CTYPE>; 
%enddef

%define ODARRAY(ARRAYTYPE, CTYPE...)
  ODARRAY_SEPARATE_ARRAY_TYPES(ARRAYTYPE, ARRAYTYPE, CTYPE)
%enddef

%define ODPTRARRAY_SEPARATE_ARRAY_TYPES(CS_ARRAYTYPE, CPP_ARRAYTYPE, CTYPE...)
  template<> class OdArray< CTYPE, OdObjectsAllocator<CTYPE> > {
    ODARRAY_IMPL(IList, OdObjectsAllocator, %arg(CTYPE), %arg(CTYPE))
  };
  template<> class OdArray<CTYPE> {
    ODARRAY_IMPL(IList, OdObjectsAllocator, %arg(CTYPE), %arg(CTYPE))
  }; 
  ODARRAY_INNER_IMPL(CS_ARRAYTYPE, CTYPE, OdObjectsAllocator)
  ODARRAY_TYPEMAP_SEPARETE_CS_AND_CPP_TYPES(CS_ARRAYTYPE,CPP_ARRAYTYPE)
  %template(CS_ARRAYTYPE) OdArray<CTYPE>; 
%enddef

%define ODPTRARRAY(ARRAYTYPE,CTYPE...)
  ODPTRARRAY_SEPARATE_ARRAY_TYPES(ARRAYTYPE, ARRAYTYPE, CTYPE) 
%enddef

%define ODARRAY_MEM(ARRAYTYPE,CTYPE...)
  template<> class OdArray< CTYPE, OdMemoryAllocator<CTYPE> > {
    ODARRAY_IMPL(IList, OdMemoryAllocator, %arg(CTYPE const&), %arg(CTYPE))
  };
  ODARRAY_INNER_IMPL(ARRAYTYPE, CTYPE, OdMemoryAllocator)
  ODARRAY_TYPEMAP(ARRAYTYPE)
  %template(ARRAYTYPE) OdArray<CTYPE, OdMemoryAllocator<CTYPE> >; 
%enddef

%define ODPTRARRAY_MEM(ARRAYTYPE,CTYPE...)
  template<> class OdArray< CTYPE, OdMemoryAllocator<CTYPE> > {
    ODARRAY_IMPL(IList, OdMemoryAllocator, %arg(CTYPE), %arg(CTYPE))
  };
  ODARRAY_INNER_IMPL(ARRAYTYPE, CTYPE, OdMemoryAllocator)
  ODARRAY_TYPEMAP(ARRAYTYPE)
  %template(ARRAYTYPE) OdArray<CTYPE, OdMemoryAllocator<CTYPE> >; 
%enddef

%define ODARRAY_CLR_MEM(ARRAYTYPE,CTYPE...)
  template<> class OdArray< CTYPE, OdClrMemAllocator<CTYPE> > {
    ODARRAY_IMPL(IList, OdClrMemAllocator, %arg(CTYPE const&), %arg(CTYPE))
  };
  ODARRAY_INNER_IMPL(ARRAYTYPE, CTYPE, OdClrMemAllocator)
  ODARRAY_TYPEMAP(ARRAYTYPE)
  %template(ARRAYTYPE) OdArray<CTYPE, OdClrMemAllocator<CTYPE> >; 
%enddef

%define ODPTRARRAY_CLR_MEM(ARRAYTYPE,CTYPE...)
  template<> class OdArray< CTYPE, OdClrMemAllocator<CTYPE> > {
    ODARRAY_IMPL(IList, OdClrMemAllocator, %arg(CTYPE), %arg(CTYPE))
  };
  ODARRAY_INNER_IMPL(ARRAYTYPE, CTYPE, OdClrMemAllocator)
  ODARRAY_TYPEMAP(ARRAYTYPE)
  %template(ARRAYTYPE) OdArray<CTYPE, OdClrMemAllocator<CTYPE> >; 
%enddef

%define ODARRAY_PLAIN(ARRAYTYPE,CTYPE...)
  template<> class OdArray< CTYPE, OdPlainObjectsAllocator<CTYPE> > {
    ODARRAY_IMPL(IList, OdPlainObjectsAllocator, %arg(CTYPE const&), %arg(CTYPE))
  };
  ODARRAY_INNER_IMPL(ARRAYTYPE, CTYPE, OdPlainObjectsAllocator)
  ODARRAY_TYPEMAP(ARRAYTYPE)
  %template(ARRAYTYPE) OdArray<CTYPE, OdPlainObjectsAllocator<CTYPE> >; 
%enddef

%define ODPTRARRAY_PLAIN(ARRAYTYPE,CTYPE...)
  template<> class OdArray< CTYPE, OdPlainObjectsAllocator<CTYPE> > {
    ODARRAY_IMPL(IList, OdPlainObjectsAllocator, %arg(CTYPE), %arg(CTYPE))
  };
  ODARRAY_INNER_IMPL(ARRAYTYPE, CTYPE, OdPlainObjectsAllocator)
  ODARRAY_TYPEMAP(ARRAYTYPE)
  %template(ARRAYTYPE) OdArray<CTYPE, OdPlainObjectsAllocator<CTYPE> >; 
%enddef

%csmethodmodifiers OdArray::getitemcopy "private"
%csmethodmodifiers OdArray::getitem "private"
%csmethodmodifiers OdArray::setitem "private"
%csmethodmodifiers OdArray::size "private"
%csmethodmodifiers OdArray::capacity "private"
%csmethodmodifiers OdArray::reserve "private"