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
#ifndef _OD_AUTO_PTR_H_
#define _OD_AUTO_PTR_H_

/**
 * Helper to deleting an object automatically.
 * Similar to std::auto_ptr and boost::scoped_ptr.
 * The only reasons to prefer it to std::auto_ptr are:
 *   1) Avoid including <memory>, which will transitively pull a lot of STL.
 *   2) "receive" is a very helpful when dealing with raw-pointer code.
 */
template<class T>
class OdAutoPtr {
public:
  inline T *get() const { return m_ptr; }
  inline T &operator* () const { return *m_ptr; }
  inline T *operator-> () const { return m_ptr; }

  inline OdAutoPtr() : m_ptr(NULL) {}
  explicit inline OdAutoPtr(T *ptr) : m_ptr(ptr) {}
  ~OdAutoPtr() { destroy(); }

  void reset(T *ptr = NULL) {
    destroy();
    m_ptr = ptr;
  }

  inline T *release() {
    T *ptr = m_ptr;
    m_ptr = NULL;
    return ptr;
  }

  inline void swap(OdAutoPtr<T> &other) {
    T *tmp = m_ptr;
    m_ptr = other.m_ptr;
    other.m_ptr = tmp;
  }

  inline T*& receive() {
    reset();
    return m_ptr;
  }

private:
  T *m_ptr;

  inline void destroy() {
    delete m_ptr;
  }
  //(noncopyable)
  OdAutoPtr(const OdAutoPtr<T> &);
  void operator= (const OdAutoPtr<T> &);
};


/**
 * Helper to deleting an object automatically.
 * Somewhat similar to std::auto_ptr and boost::scoped_ptr.
 * The difference is: this pointer can be non-owning reference.
 */
template<class T>
class OdSemiAutoPtr {
public:
  inline T *get() const { return m_ptr; }
  inline T &operator* () const { return *m_ptr; }
  inline T *operator-> () const { return m_ptr; }

  inline OdSemiAutoPtr() : m_ptr(NULL), m_own(false) {}
  explicit inline OdSemiAutoPtr(T *ptr, bool own = true) : m_ptr(ptr), m_own(own) {}
  ~OdSemiAutoPtr() { destroy(); }

  void reset(T *ptr = NULL, bool own = true) {
    destroy();
    m_ptr = ptr;
    m_own = own;
  }

  inline T *release() {
    m_own = false;
    return m_ptr;
  }

  inline void swap(OdSemiAutoPtr<T> &other) {
    T *tmp = m_ptr;
    m_ptr = other.m_ptr;
    other.m_ptr = tmp;
    bool to = m_own;
    m_own = other.m_own;
    other.m_own = to;
  }

  inline T*& receive(bool own = true) {
    reset();
    m_own = own;
    return m_ptr;
  }

  bool isOwn() const { return m_own; }

private:
  T *m_ptr;
  bool m_own;

  inline void destroy() {
    if (m_own)
      delete m_ptr;
  }
  //(noncopyable)
  OdSemiAutoPtr(const OdSemiAutoPtr<T> &);
  void operator= (const OdSemiAutoPtr<T> &);
};

#endif
