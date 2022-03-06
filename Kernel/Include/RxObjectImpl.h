/////////////////////////////////////////////////////////////////////////////// 
// Copyright (C) 2002-2022, Open Design Alliance (the "Alliance"). 
// All rights reserved. 
// 
// This software and its documentation and related materials are owned by 
// the Alliance. The software may only be incorporated into application 
// programs owned by members of the Alliance, subject to a signed 
// Membership Agreement and Supplemental Software License Agreement with the
// Alliance. The structure and organization of this software are the valuable  
// trade secrets of the Alliance and its suppliers. The software is also 
// protected by copyright law and international treaty provisions. Application  
// programs incorporating this software must include the following statement 
// with their copyright notices:
//   
//   This application incorporates Open Design Alliance software pursuant to a license 
//   agreement with Open Design Alliance.
//   Open Design Alliance Copyright (C) 2002-2022 by Open Design Alliance. 
//   All rights reserved.
//
// By use of this software, its documentation or related materials, you 
// acknowledge and accept the above terms.
///////////////////////////////////////////////////////////////////////////////




#if !defined(OdRxObjectImpl_INCLUDED_)
#define OdRxObjectImpl_INCLUDED_

#include "OdaCommon.h"
#include "TD_PackPush.h"

#include "RxObject.h"
#include "OdMutex.h"

/** \details
    <group OdRx_Classes> 

    The template class provides the <link smart_pointers_definition_standard.html, standard implementation of the counting references> 
    for instances of objects derived from the OdRxObject class.

    \sa
    TD_Db

    \sa
    <link smart_pointers_example_count_standard.html, Example of Counting References>

    \sa
    <link smart_pointers_overview.html, Overview of Smart Pointer Classes> 

    The OdStaticRxObject class
*/
template<class T, class TInterface = T>
class OdRxObjectImpl : public T
{
  /** \details
      Allows to create OdRxObjectImpl<T> instances inside this class only.
  */
  OdRefCounter m_nRefCounter;

  /** \details
      Assignment operator prohibited.
  */
  OdRxObjectImpl& operator = (const OdRxObjectImpl&);

protected:
  ODRX_HEAP_OPERATORS();

public:
  /** \details
      Constructor sets the reference counter to one.
  */
  OdRxObjectImpl() 
  { 
    m_nRefCounter = 1; 
  }

  /** \details
      Increments the reference counter.
  */
  void addRef()
  {
    ++m_nRefCounter;
  }

  /** \details
      Decrements the reference counter, checks the reference counter, and destroys the instance 
      when the reference counter reaches zero.
  */
  void release()
  {
		ODA_ASSERT((m_nRefCounter > 0));
		if (!(--m_nRefCounter))
		{
      delete this;
		}
  }

  /** \details
      Returns the number of references to an instance of this class.
  */
  long numRefs() const { return m_nRefCounter; }

  /** \details
      It is the pseudo-constructor that creates an instance of this class  and returns the typified smart pointer to it.
  */
  static OdSmartPtr<TInterface> createObject()
  {
    return OdSmartPtr<TInterface>(static_cast<TInterface*>(new OdRxObjectImpl<T, TInterface>), kOdRxObjAttach);
  }
};

#if (defined(_MSC_VER) && (_MSC_VER > 1700)) || (defined(__cplusplus) && (__cplusplus > 199711L))
/** \details
    <group OdRx_Classes>

    The template class provides the <link smart_pointers_definition_standard.html, standard implementation of the counting references>
    for instances of objects derived from the OdRxObject class.

    \sa
    TD_Db

    \sa
    <link smart_pointers_example_count_standard.html, Example of Counting References>

    \sa
    <link smart_pointers_overview.html, Overview of Smart Pointer Classes>

    The OdStaticRxObject class
*/
template<class T, class TInterface = T>
class OdRxObjectImpl2 : public T
{
  /** \details
      Allows to create OdRxObjectImpl<T> instances inside this class only.
  */
  OdRefCounter m_nRefCounter;

  /** \details
      Assignment operator prohibited.
  */
  OdRxObjectImpl2& operator = (const OdRxObjectImpl2&);

protected:
  ODRX_HEAP_OPERATORS();

public:
  /** \details
      Perfect forwarding constructor of T.
      Constructor sets the reference counter to one.
  */
  template<typename... Args>
  OdRxObjectImpl2(Args&&... args)
    : T(std::forward<Args>(args)...)
  {
    m_nRefCounter = 1;
  }

  /** \details
      Increments the reference counter.
  */
  void addRef()
  {
    ++m_nRefCounter;
  }

  /** \details
      Decrements the reference counter, checks the reference counter, and destroys the instance
      when the reference counter reaches zero.
  */
  void release()
  {
    ODA_ASSERT((m_nRefCounter > 0));
    if (!(--m_nRefCounter))
    {
      delete this;
    }
  }

  /** \details
      Returns the number of references to an instance of this class.
  */
  long numRefs() const { return m_nRefCounter; }

  /** \details
      Perfect forwarding pseudo-constructor that creates an instance of this class and returns the typified smart pointer to it.
  */
  template<typename... Args>
  static OdSmartPtr<TInterface> createObject(Args&&... args)
  {
    return OdSmartPtr<TInterface>(static_cast<TInterface*>(new OdRxObjectImpl2<T, TInterface>(std::forward<Args>(args)...)), kOdRxObjAttach);
  }
};

#endif

/** \details
    Defines the pseudo-constructor for the specified class that is equivalent the pseudo-constructor of the wrapper class using the standard implementation.
*/
#define RXIMPL_CONSTR(ClassName) OdRxObjectImpl<ClassName>::createObject()

/** \details
    Defines a pseudo-constructor for the specified class.
*/
#define ABSTRACTIMPL_CONSTR(CLASS) OdRxObjectImpl<CLASS##Impl>::createObject()

template<class T, class TImpl>
class OdObjectWithImpl : public T
{
protected:
#ifdef ODA_NEED_TEMP_USING
  using T::m_pImpl;
#endif
public:
  TImpl m_Impl;
  inline OdObjectWithImpl() : T(&m_Impl)
  {
  }
  inline ~OdObjectWithImpl()
  {
    m_pImpl = NULL;
  }
  static OdSmartPtr<T> createObject()
  {
    return OdSmartPtr<T>((T*)new OdObjectWithImpl<T, TImpl>, kOdRxObjAttach);
  }
};

#define OD_IDCAT(ID, Postf) ID##Postf

#define RXIMPLOBJCONSTRUCT(ClassName) OdRxObjectImpl<OdObjectWithImpl<ClassName, OD_IDCAT(ClassName,Impl)> >::createObject()

#define IMPLOBJCONSTRUCT(ClassName) OdObjectWithImpl<ClassName, OD_IDCAT(ClassName,Impl)>::createObject()


#include "TD_PackPop.h"

#endif // !defined(OdRxObjectImpl_INCLUDED_)

