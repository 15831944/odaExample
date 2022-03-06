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


#ifndef _OD_DWGR21PAGEDSTREAM_H_INCLUDED_
#define _OD_DWGR21PAGEDSTREAM_H_INCLUDED_

//#include "DwgDumpUtils.h"
//#include "OdLinkedArray.h"
// ODA_MT_DBIO_BEGIN
#include "DwgR21Compressor.h"
#include "OdMutexArray.h"
// ODA_MT_DBIO_END

#define STL_USING_ALGORITHM
#define STL_USING_FUNCTIONAL
#include "OdaSTL.h"

class OdTvDwgR21FileController;
class OdTvDwgR21FileSection;

//----------------------------------------------------------
//
// OdTvRSCoder
//
//----------------------------------------------------------
#define R21_RS_BLOCK_SIZE 255    // Size of Reed-Solomon block
#define R21_RS_MAX_ERRORS 8      // Max number of errors 

class OdTvRSCoder
{
public:
  void generate(OdUInt8* poly, OdUInt32 mm, OdUInt32 errs);

  inline void encode(OdUInt8* data, OdUInt8* parity);
  inline void decode(OdUInt8* data);

  OdUInt32 dsize() const { return _dsize; }
  OdUInt32 psize() const { return _psize; }
private:
  OdUInt32 _dsize; // size of data bytes 
  OdUInt32 _psize; // size of parity bytes
  OdUInt32 _errs;  // number of errors that can be corrected

  OdUInt32 _gpoly[(R21_RS_MAX_ERRORS*2)+1];
  OdUInt32 _alphaTo[R21_RS_BLOCK_SIZE+1];
  OdUInt32 _indexOf[R21_RS_BLOCK_SIZE+1];

  OdBinaryData _mod255;
};

//----------------------------------------------------------
//
// OdTvDwgR21PagedStream
//
//----------------------------------------------------------
class OdTvDwgR21PagedStream : public OdStreamBuf
{
// ODA_MT_DBIO_BEGIN
  // OdArray<OdMutex> can not be copied safely
  OdTvDwgR21PagedStream(const OdTvDwgR21PagedStream&);
  OdTvDwgR21PagedStream& operator = (const OdTvDwgR21PagedStream&);
// ODA_MT_DBIO_END
public:
  OdTvDwgR21PagedStream();
  ~OdTvDwgR21PagedStream();

  void openW();
  void setController(OdTvDwgR21FileController* pController) { m_pController = pController; }

  //
  // OdStreamBuf overridden
  //
  OdUInt8 getByte();
  void getBytes(void* buffer, OdUInt32 len);
  void putByte(OdUInt8 value);
  void putBytes(const void* buffer, OdUInt32 len);
  OdUInt64 seek(OdInt64 offset, OdDb::FilerSeekType whence);
  OdUInt64 tell();
  OdUInt64 length();
  bool isEof();
  void rewind();
  void truncate();

  //
  // Permutation with Reed-Solomon encoding
  //
  static inline void decode(OdUInt8* dst, OdUInt8* src, OdUInt32 dstSize, OdUInt32 factor, OdTvRSCoder& rscoder);
  static inline void encode(OdUInt8* dst, OdUInt8* src, OdUInt32 srcSize, OdTvRSCoder& rscoder, OdUInt8* random);
  static inline void encodeRS(OdUInt8* data, OdUInt32 dataSize, OdTvRSCoder& rscoder, OdUInt8* parity, OdUInt8* random);
  static inline void decodeRS(OdUInt8* data, OdUInt32 dataSize, OdTvRSCoder& rscoder, OdUInt8* parity, OdUInt8* random);

  //
  // Stream attributes
  //
  OdUInt64 m_dataSize;
  OdUInt64 m_pageSize;
  OdUInt64 m_encrypted;   // NotEncrypted = 0, Encrypted = 1, Unknown = 2
  OdUInt64 m_encoded;     // NotEncoded = 1, Encoded = 4
  bool     m_compressed;

  bool isEncoded() const { return m_encoded == 4; }
  bool isEncrypted() const { return m_encrypted == 1; }
  bool isCompressed() const { return m_compressed; }

  //
  // Implementation of the paged structure
  //
  class Page
  {
  public:
    // File data
    OdUInt64 m_dataOffset;
    OdUInt64 m_pageSize;
    OdUInt64 m_pageId;
    OdUInt64 m_dataSize;
    OdUInt64 m_comprSize;
    OdUInt64 m_checksum;
    OdUInt64 m_crc;

    // Run-time data
    OdUInt8* m_data;

// ODA_MT_DBIO_BEGIN
    OdMutex* m_dataLock;
// ODA_MT_DBIO_END

    Page()  // default argument here won't work for array initialization on SGI, separate no-arg constructor required
      : m_dataOffset(0)
      , m_pageSize(0)
      , m_pageId(0)
      , m_dataSize(0)
      , m_comprSize(0)
      , m_checksum(0)
      , m_crc(0)
      , m_data(0)
// ODA_MT_DBIO_BEGIN
      , m_dataLock(0)
// ODA_MT_DBIO_END
    {}

    Page(OdInt64 dataOffset)
    {
      new (this) Page();
      m_dataOffset = dataOffset;
    }

    bool isCompressed() const
    {
      return m_comprSize != m_dataSize;
    }
    bool isFull() const
    {
      return m_dataSize == m_pageSize;
    }
    OdUInt8 getByte(OdUInt32 pos) const
    {
      ODA_ASSERT(m_data && pos < m_dataSize);
      return m_data[pos];
    }
    void getBytes(OdUInt32 pos, OdUInt8* dst, OdUInt32 size) const
    {
      ODA_ASSERT(m_data && pos + size <= m_dataSize);
      ::memcpy(dst, m_data + pos, size);
    }
    void putByte(OdUInt32 pos, OdUInt8 val)
    {
      ODA_ASSERT((OD_T("Writing to the page that has been already saved to raw stream") , !isFull()));
      ODA_ASSERT(m_data && pos < m_pageSize);
      m_data[pos] = val;
      if (pos >= m_dataSize)
        m_dataSize = pos + 1;
    }
    void putBytes(OdUInt32 pos, const OdUInt8* src, OdUInt32 size)
    {
      ODA_ASSERT((OD_T("Writing to the page that has been already saved to raw stream") , !isFull()));
      OdUInt32 newSize = pos + size;
      ODA_ASSERT(m_data && newSize <= m_pageSize);
      ::memcpy(m_data + pos, src, size);
      if (newSize > m_dataSize)
        m_dataSize = newSize;
    }

    OdUInt8* data()
    {
      return m_data;
    }
    void allocData(OdUInt64 size)
    {
      ODA_ASSERT(size >> 32 == 0);
      m_data = (OdUInt8*)::odrxAlloc((OdUInt32)size);
      if (!m_data)
        throw OdError(eOutOfMemory);
    }
    void freeData()
    {
      if (m_data)
      {
        ::odrxFree(m_data);
        m_data = 0;
      }
// ODA_MT_DBIO_BEGIN
      m_dataLock = 0;
// ODA_MT_DBIO_END
    }

// ODA_MT_DBIO_BEGIN
    void setData(OdUInt8* pdata)
    {
      ODA_ASSERT(!m_data);
      m_data = pdata;
    }
// ODA_MT_DBIO_END
  };
  typedef OdArray<Page> OdPageArray;
  typedef OdArray<Page>::iterator OdPageArrayIterator;
  //typedef OdLinkedArray<Page> OdPageArray;
  //typedef OdLinkedArray<Page>::iterator OdPageArrayIterator;

// ODA_MT_DBIO_BEGIN
  OdMutexArray m_pageLocks;
  void createPageLocks()
  {
    ODA_ASSERT(m_pageLocks.size()==0);
    unsigned psize = m_pages.size();
    m_pageLocks.resize(psize);
    for (unsigned i = 0; i < psize; ++i)
    {
      m_pages[i].m_dataLock = &m_pageLocks[i];
    }
  }
  OdPageArray& pages() { return m_pages; }
  void getPage(Page& page, OdBinaryData& pageData, OdBinaryData& decData, OdTvDwgR21Compressor& cmpr);
// ODA_MT_DBIO_END

protected:
  OdPageArray m_pages; 

private:
  OdPageArrayIterator m_curPage; 
  OdUInt64 m_curPosInPage;
  inline OdUInt64 curPos();

  inline void nextPageR();
  inline void nextPageW();
  inline void getPage();
  inline void putPage();

  OdTvDwgR21FileController* m_pController;
};

typedef OdSmartPtr<OdTvDwgR21PagedStream> OdTvDwgR21PagedStreamPtr;

//----------------------------------------------------------
//
// OdTvRSCoder inline methods
//
//----------------------------------------------------------
inline
void OdTvRSCoder::encode(OdUInt8* data, OdUInt8* parity)
{
  memset(parity, 0, _psize); // init memory for calculating parity bytes

  int di = _dsize-1;
  for (; di >= 0; --di)
  {
    int pi = _psize-1;
    unsigned vald = data[di];
    vald ^= parity[pi];
    vald = _indexOf[vald];

    if ((int)vald == -1)
    {
      for (; pi > 0; --pi)
      {
        parity[pi] = parity[pi-1];
      }
      parity[0] = 0;
    }
    else
    {
      unsigned valp;
      for (; pi > 0; --pi)
      {
        parity[pi] = parity[pi-1];
        valp = _gpoly[pi];
        if ((int)valp != -1)
        {
          valp = _mod255[vald + valp];
          valp = _alphaTo[valp] & 0xff;
          parity[pi] ^= valp;
        }
      }
      valp = _gpoly[0];
      valp = _mod255[vald + valp];
      parity[0] = OdUInt8( _alphaTo[valp] & 0xff );
    }
  }

#if 0
  OdUInt8 test[R21_RS_BLOCK_SIZE];
  memcpy(test, data, _dsize);
  memcpy(test+_dsize, parity, _psize);
  decode(test);
#endif
}

inline
void OdTvRSCoder::decode(OdUInt8* data)
{
  // Cache indexes
  unsigned dindex[R21_RS_BLOCK_SIZE];
  unsigned j = 0;
  for (; j < R21_RS_BLOCK_SIZE; ++j)
  {
    dindex[j] = _indexOf[data[j]];
  }
  // Calculate syndromes
  const OdUInt8* pmod255 = _mod255.asArrayPtr();
  bool hasErrors = false;
  unsigned syn[(R21_RS_MAX_ERRORS*2)+1];
  unsigned i = 1;
  for (; i <= _psize; ++i)
  {
    syn[i] = 0;
    for (j = 0; j < R21_RS_BLOCK_SIZE; ++j)
    {
      unsigned val = dindex[j];
      if (val != 0xffffffff)
      {
        val += i * j;
        val = pmod255[val];
        val = _alphaTo[val];
        syn[i] ^= val;
      }
    }
    if (syn[i] != 0)
    {
      hasErrors = true;
    }
    syn[i] = _indexOf[syn[i]];
  }
  // Correct errors
  if (hasErrors)
  {
    // R21 issue. Implement Reed-Solomon error correction.
    // Algorithm is very sensitive for signed/unsigned variables, don't change arrays or variables types here.
    OdInt32 elp[(R21_RS_MAX_ERRORS * 2) + 2][(R21_RS_MAX_ERRORS * 2)], d[(R21_RS_MAX_ERRORS * 2) + 2],
            l[(R21_RS_MAX_ERRORS * 2) + 2], u_lu[(R21_RS_MAX_ERRORS * 2) + 2],
            reg[R21_RS_MAX_ERRORS + 1], root[R21_RS_MAX_ERRORS], loc[R21_RS_MAX_ERRORS], z[R21_RS_MAX_ERRORS + 1],
            err[R21_RS_BLOCK_SIZE];
    OdInt32 u, count, q;
    // Initialise table entries
    d[0] = 0;
    d[1] = syn[1];
    elp[0][0] = 0;
    elp[1][0] = 1;
    for (i = 1; i < _psize; i++)
    {
      elp[0][i] = 0xFFFFFFFF;
      elp[1][i] = 0;
    }
    l[0] = 0;
    l[1] = 0;
    u_lu[0] = 0xFFFFFFFF;
    u_lu[1] = 0;
    u = 0;
    do
    {
      u++;
      if (d[u] == (OdInt32)0xFFFFFFFF)
      {
        l[u + 1] = l[u];
        for (i = 0; i <= (OdUInt32)l[u]; i++)
        {
          elp[u + 1][i] = elp[u][i];
          elp[u][i] = _indexOf[elp[u][i]];
        }
      }
      else
      // Search for words with greatest u_lu[q] for which d[q] != 0
      {
        q = u - 1;
        while ((d[q] == -1) && (q > 0))
        {
          q--;
        }
        // Have found first non-zero d[q]
        if (q > 0)
        {
          j = q;
          do
          {
            j--;
            if ((d[j] != (OdInt32)0xFFFFFFFF) && (u_lu[q] < u_lu[j]))
            {
              q = j;
            }
          } while (j > 0);
        }
        // Have now found q such that d[u] != 0 and u_lu[q] is maximum
        // store degree of new elp polynomial
        if (l[u] > l[q] + u - q)
        {
          l[u + 1] = l[u];
        }
        else
        {
          l[u + 1] = l[q] + u - q;
        }
        // Form new elp(x)
        for (i = 0; i < _psize; i++) 
        {
          elp[u + 1][i] = 0;
        }
        for (i = 0; i <= (OdUInt32)l[q]; i++)
        {
          if (elp[q][i] != (OdInt32)0xFFFFFFFF)
          {
            elp[u + 1][i + u - q] = _alphaTo[pmod255[(d[u] + R21_RS_BLOCK_SIZE - d[q] + elp[q][i])]];
            for (i = 0; i <= (OdUInt32)l[u]; i++)
            {
              elp[u + 1][i] ^= elp[u][i];
              elp[u][i] = _indexOf[elp[u][i]];
            }
          }
        }
      }
      u_lu[u + 1] = u - l[u + 1];
      // Form (u + 1)th discrepancy
      if (u < (OdInt32)_psize) // No discrepancy computed on last iteration
      {
        if (syn[u + 1] != 0xFFFFFFFF)
        {
          d[u + 1] = _alphaTo[syn[u + 1]];
        }
        else
        {
          d[u + 1] = 0;
        }
        for (i = 1; i <= (OdUInt32)l[u + 1]; i++)
        {
          if ((syn[u + 1 - i] != 0xFFFFFFFF) && (elp[u + 1][i] != 0))
          {
            d[u + 1] ^= _alphaTo[pmod255[(syn[u + 1 - i] + _indexOf[elp[u + 1][i]])]];
          }
        }
        d[u + 1] = _indexOf[d[u + 1]];
      }
    } while ((u < (OdInt32)_psize) && (l[u + 1] <= (OdInt32)_errs));
    u++;
    if (l[u] <= (OdInt32)_errs) // Can correct error
    {
      // Put elp into index form
      for (i = 0; i <= (OdUInt32)l[u]; i++)
      {
        elp[u][i] = _indexOf[elp[u][i]];
      }
      // Find roots of the error location polynomial
      for (i = 1; i <= (OdUInt32)l[u]; i++)
      {
        reg[i] = elp[u][i];
      }
      count = 0;
      for (i = 1; i <= R21_RS_BLOCK_SIZE; i++)
      {
        q = 1;
        for (j = 1; j <= (OdUInt32)l[u]; j++)
        {
          if (reg[j] != (OdInt32)0xFFFFFFFF)
          {
            reg[j] = pmod255[(reg[j] + j)];
            q ^= _alphaTo[reg[j]];
          }
        }
        if (!q) // store root and error location number indices
        {
          root[count] = i;
          loc[count] = R21_RS_BLOCK_SIZE - i;
          count++;
        }
      }
      if (count == l[u])
      {
        // Form polynomial z(x)
        for (i = 1; i <= (OdUInt32)l[u]; i++) // Z[0] = 1 always - do not need
        {
          if ((syn[i] != 0xFFFFFFFF) && (elp[u][i] != (OdInt32)0xFFFFFFFF))
          {
            z[i] = _alphaTo[syn[i]] ^ _alphaTo[elp[u][i]];
          }
          else if ((syn[i] != 0xFFFFFFFF) && (elp[u][i] == (OdInt32)0xFFFFFFFF))
          {
            z[i] = _alphaTo[syn[i]];
          }
          else if ((syn[i] == 0xFFFFFFFF) && (elp[u][i] != (OdInt32)0xFFFFFFFF))
          {
            z[i] = _alphaTo[elp[u][i]];
          }
          else
          {
            z[i] = 0;
          }
          for (j = 1; j < i; j++)
          {
            if ((syn[j] != 0xFFFFFFFF) && (elp[u][i - j] != (OdInt32)0xFFFFFFFF))
            {
              z[i] ^= _alphaTo[pmod255[(elp[u][i - j] + syn[j])]];
            }
          }
          z[i] = _indexOf[z[i]];
        }
        // Evaluate errors at locations given by error location numbers loc[i]
        for (i = 0; i < R21_RS_BLOCK_SIZE; i++)
        {
          err[i] = 0;
          if (dindex[i] != 0xFFFFFFFF)
          {
            dindex[i] = _alphaTo[dindex[i]];
          }
          else
          {
            dindex[i] = 0 ;
          }
        }
        for (i = 0; i < (OdUInt32)l[u]; i++) // Compute numerator of error term first
        { 
          err[loc[i]] = 1; // Sccounts for z[0]
          for (j = 1; j <= (OdUInt32)l[u]; j++)
          {
            if (z[j] != (OdInt32)0xFFFFFFFF)
            {
              err[loc[i]] ^= _alphaTo[pmod255[(z[j] + j * root[i])]];
            }
          }
          if (err[loc[i]] != 0)
          {
            err[loc[i]] = _indexOf[err[loc[i]]];
            q = 0; // Form denominator of error term
            for (j = 0; j < (OdUInt32)l[u]; j++)
            {
              if (j != i)
              {
                q += _indexOf[1 ^ _alphaTo[pmod255[(loc[j] + root[i])]]];
              }
            }
            q = q % R21_RS_BLOCK_SIZE;
            err[loc[i]] = _alphaTo[pmod255[(err[loc[i]] - q + R21_RS_BLOCK_SIZE)]];
            dindex[loc[i]] ^= err[loc[i]];
          }
        }
      }
      else // No. roots != degree of elp => tt errors and cannot solve
      {
        for (i = 0; i < R21_RS_BLOCK_SIZE; i++)
        {
          if (dindex[i] != 0xFFFFFFFF)
          {
            dindex[i] = _alphaTo[dindex[i]] ;
          }
          else 
          {
            dindex[i] = 0;
          }
        }
      }
    }
    else // elp has degree has degree > tt hence cannot solve
    {
      for (i = 0; i < R21_RS_BLOCK_SIZE; i++)
      {
        if (dindex[i] != 0xFFFFFFFF)
        {
          dindex[i] = _alphaTo[dindex[i]];
        }
        else
        {
          dindex[i] = 0;
        }
      }
    }
  }
  else 
  {
    // No non-zero syndromes => no errors: output received codeword
    return;
  }

  j = 0;
  //OdTrace(L"Codeblock process . . .\n");
  for (; j < R21_RS_BLOCK_SIZE; ++j)
  {
    //unsigned dbef = data[j];
    data[j] = (OdUInt8)dindex[j];
    //OdTrace(L"Sym %u: dbef %u, rez %u, di %u, ok %u\n", j, dbef, data[j], dindex[j], (unsigned)(data[j] == dbef));
  }
}

//----------------------------------------------------------
//
// OdTvDwgR21PagedStream inline methods
//
//----------------------------------------------------------
inline
OdUInt64 OdTvDwgR21PagedStream::curPos()
{ 
  ODA_ASSERT(m_curPage != m_pages.end());
  return m_curPage->m_dataOffset + m_curPosInPage;
}

inline
void OdTvDwgR21PagedStream::nextPageR()
{
  ODA_ASSERT(m_pages.size() && m_curPage != m_pages.end());
  ++m_curPage;
  m_curPosInPage = 0;
}

inline
void OdTvDwgR21PagedStream::nextPageW()
{
  ODA_ASSERT(m_curPage == m_pages.end());
  m_curPage = m_pages.append();
  ODA_ASSERT(!m_curPage->data());
  m_curPage->allocData(m_pageSize);
  m_curPage->m_pageSize = m_pageSize;
  if (m_curPage != m_pages.begin())
  {
    OdPageArrayIterator prevPage = m_curPage;
    --prevPage;
    m_curPage->m_dataOffset = prevPage->m_dataOffset + prevPage->m_dataSize;
  }
  m_curPosInPage = 0;
}

inline
void encodeBlock(OdUInt8* dst, OdUInt8* src, OdUInt8* parity, OdUInt32 factor, OdTvRSCoder& rscoder)
{
  rscoder.encode(src, parity);

  // Put data bytes
  int len = rscoder.dsize();
  while (len--)
  {
    *dst = *src++;
    dst += factor;
  }

  // Put Reed-Solomon parity bytes
  src = parity;
  len = rscoder.psize();
  while (len--)
  {
    *dst = *src++;
    dst += factor;
  }
}

inline
void OdTvDwgR21PagedStream::encode(OdUInt8* dst, OdUInt8* src, OdUInt32 srcSize, OdTvRSCoder& rscoder, OdUInt8* random)
{
  OdUInt32 factor = (srcSize + rscoder.dsize() - 1) / rscoder.dsize();
  OdUInt8 buff[R21_RS_BLOCK_SIZE];
  unsigned i = 0;
  while (srcSize >= rscoder.dsize())
  {
    encodeBlock(dst + i, src + i * rscoder.dsize(), buff, factor, rscoder);
    ++i;
    srcSize -= rscoder.dsize();
  }

  if (srcSize)
  {
    ODA_ASSERT(srcSize < rscoder.dsize());
    memcpy(buff + rscoder.psize(), src + i * rscoder.dsize(), srcSize);
    memcpy(buff + rscoder.psize() + srcSize, random, rscoder.dsize() - srcSize);
    encodeBlock(dst + i, buff + rscoder.psize(), buff, factor, rscoder);
  }
}

inline
void OdTvDwgR21PagedStream::decode(OdUInt8* dst, OdUInt8* src, OdUInt32 dstSize, OdUInt32 factor, OdTvRSCoder& rscoder)
{
  OdUInt32 dataSize = dstSize;
  OdUInt8 buff[R21_RS_BLOCK_SIZE + 1]; // buffer to calculate hash tables
  for (unsigned i = 0; i < factor; ++i)
  {
    //
    // Get permuted block of data
    //
    OdUInt8* curDst = buff;
    OdUInt8* curSrc = src;
    int len = R21_RS_BLOCK_SIZE;
    while (len--)
    {
      *curDst++ = *curSrc;
      curSrc += factor;
    }
    //DWG_TRACE_BYTES(buff, R21_RS_BLOCK_SIZE + 1, "Block");

    //
    // Decode Reed-Solomon parity values
    //
    rscoder.decode(buff);

    //
    // Copy decoded data to destination buffer
    //
    OdUInt32 copySize = odmin(dataSize, rscoder.dsize());
    dataSize -= copySize;
    ::memcpy(dst, buff, copySize);
    dst += copySize;
    ++src;
  }
  //DWG_TRACE_BYTES(dstData, dstSize, "N copies of Source Data");
}

//----------------------------------------------------------
//
// OdTvDwgR21Crc64
// Implementation of CRCs calculation
//
//----------------------------------------------------------
#define R21_CRC_BLOCK_SIZE 8    // Size of block used for crc calculation

// 
// TvCrcN is a normal 64-bit CRC, 
// using initial all-ones register contents and a final bit inversion.
// The chosen polynomial is borrowed from the ECMA-182
// (available from http://www.ecma.ch/ecma1/STAND/ECMA-182.HTM): 
// x^64 + x^62 + x^57 + x^55 + x^54 + x^53 + x^52 + x^47 + x^46 + x^45 + 
// x^40 + x^39 + x^38 + x^37 + x^35 + x^33 + x^32 + x^31 + x^29 + x^27 + 
// x^24 + x^23 + x^22 + x^21 + x^19 + x^17 + x^13 + x^12 + x^10 + x^9 + 
// x^7 + x^4 + x + 1 
//
struct TvCrcN
{
  static inline void calc1(OdUInt8* p, OdUInt64& crc)
  {
    crc = m_table[(*p ^ (crc >> 56)) & 0xff] ^ (crc << 8);
  }
  static inline void calc2(OdUInt8* p, OdUInt64& crc)
  {
    calc1(p, crc);
    calc1(p+1, crc);
  }
  static inline OdUInt64 ddnot(OdUInt64 crc)
  {
    return ~crc;
  }
  static const OdUInt64 m_table[];
};

// 
// TvCrcR is a reflected 64-bit CRC
//
struct TvCrcR
{
  static inline void calc1(OdUInt8* p, OdUInt64& crc)
  {
    crc = m_table[(crc ^ *p) & 0xff] ^ (crc >> 8);
  }
  static inline void calc2(OdUInt8* p, OdUInt64& crc)
  {
    calc1(p, crc);
    calc1(p+1, crc);
  }
  static inline OdUInt64 ddnot(OdUInt64 crc)
  {
    return crc;
  }
  static const OdUInt64 m_table[];
};

template <class TCrc>
class OdTvDwgR21Crc64
{
public:
  // Calculation of crc with seed initialization
  static inline
  OdUInt64 calculateS(OdUInt8* p, OdUInt32 sz, OdUInt64 seed = 0)
  {
    seed = (seed + sz) * 0x343fd + 0x269ec3;
    seed |= seed * (OdUInt64(0x343fd) << 32) + (OdUInt64(0x269ec3) << 32);
    seed = ~seed;
    return calculate(p, sz, seed);
  }

  // Calculation of crc with modified seed initialization (used in FileHeader)
  static inline
  OdUInt64 calculateSM(OdUInt8* p, OdUInt32 sz, OdUInt64 seed = 0)
  {
    seed = (seed + sz) * 0x343fd + 0x269ec3;
    seed = seed * ((OdUInt64(1) << 32) + 0x343fd) + (sz + 0x269ec3);
    seed = ~seed;
    return calculate(p, sz, seed);
  }

  static inline
  OdUInt64 calculate(OdUInt8* p, OdUInt32 sz, OdUInt64 crc)
  {
    // Process 8-byte blocks
    OdUInt32 n = sz >> 3;
    while (n--)
    {
      TCrc::calc2(p+6, crc);
      TCrc::calc2(p+4, crc);
      TCrc::calc2(p+2, crc);
      TCrc::calc2(p+0, crc);
      p += 8;
    }

    // Process remain 0..7 bytes
    n = sz & 7;
    if (n)
    {
      switch (n)
      {
      case 1:
        TCrc::calc1(p+0, crc);
        break;
      case 2:
        TCrc::calc2(p+0, crc);
        break;
      case 3:
        TCrc::calc2(p+0, crc);
        TCrc::calc1(p+2, crc);
        break;
      case 4:
        TCrc::calc2(p+2, crc);
        TCrc::calc2(p+0, crc);
        break;
      case 5:
        TCrc::calc2(p+2, crc);
        TCrc::calc2(p+0, crc);
        TCrc::calc1(p+4, crc);
        break;
      case 6:
        TCrc::calc2(p+2, crc);
        TCrc::calc2(p+0, crc);
        TCrc::calc2(p+4, crc);
        break;
      case 7:
        TCrc::calc2(p+2, crc);
        TCrc::calc2(p+0, crc);
        TCrc::calc2(p+4, crc);
        TCrc::calc1(p+6, crc);
        break;
      }
    }

    return TCrc::ddnot(crc);
  }
};

struct PageOffsetLess
{
  bool operator()(const OdTvDwgR21PagedStream::Page& page1, const OdTvDwgR21PagedStream::Page& page2) const
  {
    return page1.m_dataOffset < page2.m_dataOffset;
  }
};

#endif // _OD_DWGR21PAGEDSTREAM_H_INCLUDED_
