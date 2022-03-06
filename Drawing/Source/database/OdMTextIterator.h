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

#ifndef _OD_MTEXT_ITERATOR_H_
#define _OD_MTEXT_ITERATOR_H_

#include <stdlib.h>

#define STL_USING_STACK
#include "OdaSTL.h"
#include "OdList.h"

#include "OdTextIterator.h"
#include "Ge/GePoint3d.h"
#include "DbColor.h"
#include "Ge/GePoint2d.h"
#include "DoubleArray.h"
#include "OdDToStr.h"

class TextProps;

class OdStrPart
{
	const OdChar* m_pMsg;
	int           m_nMsgLen;
public:
  OdStrPart() : m_pMsg(NULL), m_nMsgLen(0) {}
  OdStrPart(const OdChar* pMsg, int nMsgLen)
    : m_pMsg(pMsg), m_nMsgLen(nMsgLen) {}
  void set(const OdChar* pMsg, int nMsgLen)
  {
    m_pMsg = pMsg;
    m_nMsgLen = nMsgLen;
  }
  void setMsg(const OdChar* pMsg)
  {
    m_pMsg = pMsg;
  }
  void setLen(int nMsgLen)
  {
    m_nMsgLen = nMsgLen;
  }
  void clear() { set(NULL, 0); }
  const OdChar* getStart() const
  {
    return m_pMsg;
  }
  int getLength() const
  {
    return m_nMsgLen;
  }
};

class StackedText
{
public:
	OdStrPart  m_Top;
	OdStrPart  m_Bottom;
	OdChar     m_Divider;
	double     m_TopWidth;
	double     m_BottomWidth;
	double     m_UntrimmedTop;
	double     m_UntrimmedBottom;
	double     m_OverallWidth;
	double     m_OverallHeight;
  double     m_BottomHeight;
  double     m_TopHeight;
  double     m_MinXTop;
  double     m_MinXBottom;
  double     m_MaxXTop;
  OdChar     m_DecSeparator;
  double     m_DecShift;

  StackedText()
    : m_Divider('\0')
    , m_TopWidth(0.0)
    , m_BottomWidth(0.0)
    , m_UntrimmedTop(0.0)
    , m_UntrimmedBottom(0.0)
    , m_OverallWidth(0.0)
    , m_OverallHeight(0.0)
    , m_BottomHeight(0.0)
    , m_TopHeight(0.0)
    , m_MinXTop(0.0)
    , m_MinXBottom(0.0)
    , m_MaxXTop(0.0)
    , m_DecSeparator('\0')
    , m_DecShift(0.0)
  {
  }

	void calculateSize(TextProps& tp, OdDbDatabase* pDb, bool bRaw = true);
  OdString getContentString();
};

class OdTextFragmentData : public OdGiTextStyle
{
public:
  OdGePoint3d       m_Position;
  OdString          m_Content;

};

class OdMTextFragmentData : public OdTextFragmentData
{

public:
  OdCmEntityColor m_Color;
  OdGePoint2d     m_Extents;
  OdGePoint3d     m_Min;
  OdGePoint3d     m_Max;
  double          m_LastPointX;
  bool            m_StackTop;
  bool            m_StackBottom;

  bool            m_Underlined;
  bool            m_Overlined;
  bool            m_StrikeThrough;

  OdGePoint3d     m_UnderPoints[2];
  OdGePoint3d     m_OverPoints[2];
  OdGePoint3d     m_StrikePoints[2];

  bool            m_ExtentsValid;

	bool            m_IsLineBreak;
  bool            m_IsTab;
  bool            m_IsNewParagraph;
  bool            m_IsNewColumn;
  bool            m_IsField;
  OdGePoint3dArray m_FieldPoints;
  int           m_Alignment;

  OdMTextFragmentData() :
     m_Extents(0.0, 0.0)
    , m_LastPointX(0.0)
    , m_StackTop(false)
    , m_StackBottom(false)
    , m_Underlined(false)
    , m_Overlined(false)
    , m_StrikeThrough(false)
    , m_ExtentsValid(false)
	  , m_IsLineBreak(false)
    , m_IsTab(false)
    , m_IsNewParagraph(false)
    , m_IsNewColumn(false)
    , m_IsField(false)
    , m_Alignment(0)
    {}
  void calculateExtents(OdDbDatabase* pDb);
  void tranformBy(const OdGeMatrix3d& mat);
  void makeUnderline(TextProps* word);
  void makeOverline(TextProps* word);
  void makeStrike(TextProps* word);

  void setExtentsFrom(TextProps* textProp);

  bool isEqualToProperty(const OdMTextFragmentData& fragData, bool bGiStyle = false);
  OdString getStylePrefix(const OdMTextFragmentData& globalStyle);
  OdString getFontPrefix();
  OdString getWSpace(double dSpace, OdDbDatabase* pDb, bool bR15);
};

typedef OdArray<OdMTextFragmentData> FragmentsArray;


class OdTabulation
{
public:
  enum TabulationTypes{
    kTAB_LEFT  = 0,
    kTAB_CENTER,
    kTAB_RIGHT,
    kTAB_DECIMAL_PERIOD,
    kTAB_DECIMAL_COMMA,
    kTAB_DECIMAL_SPACE,
  };

  double m_Tab;
  TabulationTypes m_TabType;
  bool m_bUserDefined;
  OdTabulation()
  {
    m_Tab = 0.0; 
    m_TabType = kTAB_LEFT;
    m_bUserDefined = true;
  }
};

typedef OdArray<OdTabulation> OdTabulationArray;

class OdTextIndent
{
public:
  enum Alignment{
    kNOALIGNMENT = 0,
    kLEFT,
    kCENTER,
    kRIGHT,
    kJUSTIFIED,
    kDISTRIBUTED
  };

  enum LineSpacing{
    kNOLINESPASING = 0,
    kEXACTLY,
    kATLEAST,
    kMULTIPLE
  };

private:
  double  m_FirstLineInd;
  double  m_ParagraphInd;
  double  m_RightInd;  // new 2008

  double  m_StepTab;
  OdTabulationArray m_Tabulations;
  // new 2008
  bool    m_bXIndent;
  Alignment  m_alignment;
  double   m_spaceBefore;
  double   m_spaceAfter;
  LineSpacing  m_lineSpacingType;
  double   m_lineSpacing;

  bool     m_bAlignment;
  bool     m_bSpacingBefore;
  bool     m_bSpacingAfter;
  bool     m_bLineSpacing;
  bool     m_bSetIndent;
  bool     m_bUseIndent;

public:
  OdTextIndent() : m_FirstLineInd(0.0), m_ParagraphInd(0.0), m_RightInd(0), m_StepTab(0.0),
    m_bXIndent(false), m_alignment(kNOALIGNMENT), m_spaceBefore(0.0), m_spaceAfter(0.0),
    m_lineSpacingType(kNOLINESPASING), m_lineSpacing(0.0), 
    m_bAlignment(false), m_bSpacingBefore(false), m_bSpacingAfter(false), m_bLineSpacing(false), m_bSetIndent(false), m_bUseIndent(true)
  {}

  OdTextIndent(double textSize) : m_FirstLineInd(0.0), m_ParagraphInd(0.0), m_RightInd(0), m_StepTab(0.0),
    m_bXIndent(false), m_alignment(kNOALIGNMENT), m_spaceBefore(0.0), m_spaceAfter(0.0),
    m_lineSpacingType(kNOLINESPASING), m_lineSpacing(0.0),
    m_bAlignment(false), m_bSpacingBefore(false), m_bSpacingAfter(false), m_bLineSpacing(false), m_bSetIndent(false), m_bUseIndent(true)
  {
    m_StepTab = textSize * 4.0;
  }

  ~OdTextIndent() {}

  bool isXIndent()
  {
    return m_bXIndent;
  }
  void setXIndent()
  {
    m_bXIndent = true;
  }

  void setFirstLineIndentation(double indentation)
  {
    m_bSetIndent = true;
    m_FirstLineInd = indentation;
  }
  void setParagraphIndentation(double indentation)
  {
    m_bSetIndent = true;
    m_ParagraphInd = indentation;
  }
  void setParagraphRightIndentation(double indentation)
  {
    m_RightInd = indentation;
  }
  double paragraphRightIndentation()
  {
    if ( m_bUseIndent )
      return m_RightInd;
    return 0.0;
  }

  void setLineSpacing(OdTextIndent::LineSpacing type, double value)
  {
    if ( type == kNOLINESPASING )
    {
      m_bLineSpacing = false;
    } else
    {
      m_bLineSpacing = true;
      m_lineSpacingType = type;
      m_lineSpacing = value;
    }
  }

  OdTextIndent::LineSpacing lineSpacingType()
  {
    if ( m_bLineSpacing )
      return m_lineSpacingType;
    return kNOLINESPASING;
  }

  double lineSpacing()
  {
    return m_lineSpacing;
  }

  bool isAlignment()
  {
    return m_bAlignment;
  }
  OdTextIndent::Alignment alignment()
  {
    return m_alignment;
  }
  void setAlignment(OdTextIndent::Alignment type)
  {
    if ( type == kNOALIGNMENT )
    {
      m_bAlignment = false;
    } else
    {
      m_bAlignment = true;
      m_alignment = type;
    }
  }
  void setSpaceBefore(bool bSet, double value)
  {
    m_bSpacingBefore = bSet;
    m_spaceBefore = value;
  }
  double spaceBefore()
  {
    if ( m_bSpacingBefore )
    {
      return OdZero(m_spaceBefore) ? m_StepTab/16.0 : m_spaceBefore;
    }
    return 0.0;
  }

  void setSpaceAfter(bool bSet, double value)
  {
    m_bSpacingAfter = bSet;
    m_spaceAfter = value;
  }

  double spaceAfter()
  {
    if ( m_bSpacingAfter )
    {
      return OdZero(m_spaceAfter) ? m_StepTab/16.0 : m_spaceAfter;
    }
    return 0.0;
  }

  void clearTabs()
  {
    m_Tabulations.clear(); 
  }
  double firstLineIndentation()
  {
    if ( m_bUseIndent)
      return (m_FirstLineInd + m_ParagraphInd) < 0.0 ? 0.0 : m_FirstLineInd + m_ParagraphInd;
    return 0.0;
  }
  double paragraphIndentation()
  {
    if (m_bUseIndent)
      return m_ParagraphInd < 0.0 ? 0.0 : m_ParagraphInd;
    return 0.0;
  }
  double tabsStep()
  {
    return m_StepTab;
  }
  void addTabulation(OdTabulation tabVal)
  {
    m_Tabulations.push_back(tabVal);
  }
  const OdTabulationArray& getTabulations()
  {
    return m_Tabulations;
  }
  bool getTabulation(double pos, double trimmedPos, OdTabulation& tabulation, bool bNoUserDef = false);

  bool isBullet()
  {
    return m_FirstLineInd < 0.0;
  }
  // return next tab position relation from pos

  // return next tab position relation from pos in spaces
  OdUInt16 getTabSpaces(double pos);

  OdString getParamAsString(bool bICode = false);
  void setUseIndentation(bool bUseIndent )
  {
    m_bUseIndent = bUseIndent;
  }
  bool useIndentation()
  {
    return m_bUseIndent;
  }

};

class TextProps : public OdMTextFragmentData
{
public:
	double      m_WordWidth;
	double      m_WordHeight;
	double      m_TrimmedWidth;
	double      m_TrimmedHeight;
	double      m_TrimmedSpaceWidth;

  OdGePoint3d m_Min, m_Max;
  double      m_VertMaxX;
  double      m_FirstCharMinX;
  double      m_LastPos;

	StackedText m_Stacked;
	bool        m_IgnoreWordAdjustment;
	bool        m_IsToleranceDivider;
	bool        m_IsStacked;
	bool        m_IsNonBreaking;
  bool        m_ParamChange;
  bool        m_Asian;
  bool        m_InBigFont;
  OdUInt32    m_flagChanges;
  OdInt16     m_charSet;
  OdStrPart   m_Str;
  OdStrPart   m_FullStr;

  // for rendering underline/overline text with oblique
  double  m_StartedGap;
  double  m_EndedGap;

  double  m_StartUnderline;
  double  m_EndUnderline;
  double  m_StartOverline;
  double  m_EndOverline;

  TextProps()
    : OdMTextFragmentData()
    , m_WordWidth(0.0)
    , m_WordHeight(0.0)
    , m_TrimmedWidth(0.0)
    , m_TrimmedHeight(0.0)
    , m_TrimmedSpaceWidth(0.0)
    , m_Min(0.0,0.0,0.0)
    , m_Max(0.0,0.0,0.0)
    , m_FirstCharMinX(0.0)
    , m_LastPos(0.0)
    , m_IgnoreWordAdjustment(false)
    , m_IsToleranceDivider(false)
    , m_IsStacked(false)
    , m_IsNonBreaking(false)
    , m_ParamChange(false)
    , m_Asian(false)
    , m_InBigFont(false)
    , m_flagChanges(0)
    , m_StartedGap(0.0)
    , m_EndedGap(0.0)
    , m_StartUnderline(0.0)
    , m_EndUnderline(0.0)
    , m_StartOverline(0.0)
    , m_EndOverline(0.0)
    , m_charSet(0)
    , m_VertMaxX(0.0)
    // , m_AddedNextFrag(0.0)
  {}

  double leadingSpace();
  double endingSpace();

	void   setAsLineBreak();
	void   calculateSize(OdDbDatabase* pDb, bool bRaw = true);
	void   drawAsStacked(OdGiWorldDraw* pWd, OdGiTextStyle& ts, const OdGeMatrix3d& cordSys);
  double drawAsNonBreaking(OdGiWorldDraw* pWd, OdDbDatabase* pDb,  OdGiTextStyle& ts, const OdGeMatrix3d& cordSys, bool bRaw );

	double getActualHeight(bool bVertical) const;
  double getHeightForAligned(bool bVertical) const;
  void   getStackedFragments(OdMTextFragmentData& top, OdMTextFragmentData& bottom) const;
  double getNonBreakingFragments(OdDbDatabase* pDb, FragmentsArray* fragments, bool bRaw ) const;
  void   calculateScorePos();
  OdString getSpaces(double dSpace, OdDbDatabase* pDb);
  bool   isHasText();
  OdString getString()
  {
    return OdString(m_Str.getStart(), m_Str.getLength());
  }
  OdString formatWord(OdMTextFragmentData*& pActiveStyle, const OdMTextFragmentData& globalStyle);
};

typedef std::stack<TextProps> TextPropsStack;
typedef OdList<TextProps> TextPropsList;
typedef OdArray<OdTextIndent> ParagraphsList;
typedef OdArray<TextProps*> OdWordsArray;

// this class is used for breaking paragraph to line 
class OdMTextComplexWord
{
public:
  OdMTextComplexWord() :
    m_width(0.0)
    , m_trimmedSpaceWidth(0.0)
    , m_minX(0.0)
    , m_Height(0.0)
    , m_Alignment(0)
    , m_addedToWidth(0)
    , m_needCalcExt(true)
    , m_bVertical(false)
  {}

  double m_width;
  double m_trimmedSpaceWidth;
  double m_minX;
  double m_Height;
  double m_addedToWidth;
  OdInt32 m_Alignment;
  OdWordsArray m_words;
  bool m_needCalcExt;
  bool m_bVertical;

  void calcWidht(bool bFirstWord = true);
  void addWord(TextProps* word);
  void addWordProp(TextProps* word, OdDbDatabase* pDb);
  void clear() { m_words.clear(); }
  bool isEmpty() { return (m_words.size() > 0 ? false : true); }
  void getFragments(OdGePoint3d& pos, FragmentsArray* fragments, bool bFirstLine, bool bLastInLine);
  void getFragmentsAligned(OdGePoint3d& pos, FragmentsArray* fragments, bool bFirstLine, bool bLastInLine,
    double addedShift, OdTextIndent::Alignment alignment);
  // void calculateSize(OdDbDatabase* pDb);
  OdInt32 getAmountSymbols(OdInt32& amSpaces, bool bLast);
  double getWidthToDelimiter(OdChar delim);
  double getTabPosition(double curWidth, double tabPos, double wordWidth, OdTabulation::TabulationTypes types);

};

typedef OdArray<OdMTextComplexWord> OdComplexWordsArray;

class DBENT_EXPORT OdMTextIterator : public OdTextIterator
{
  bool m_bToConvertCp;
  bool m_processField;
  bool m_brocessAsian;
  double m_dataTextSize;

  OdDbDatabase* m_pDb;
  OdUInt16 changeFont(OdGiTextStyle& style, bool bCapitalF = true);
  void changeHeight(OdGiTextStyle& style);
  OdUInt16 changeIndentation(TextPropsList& wordList, TextProps& currProps, OdTextIndent& indent);
  OdUInt16 changeIndentationX(TextProps& currProps, OdTextIndent& indent);

  void changeXScale(OdGiTextStyle& style);
  void changeAlignment(TextProps& currProps);
  OdChar processUndocumentedG();
  inline double readDouble() { return odStrToD(tokenSemicolon()); }
  inline double readDoubleTabs() { return odStrToD(tokenSeparator()); }
  int readInt();
  void newWord(TextPropsList& wordList, TextProps& currProps, bool isTolDivider = false);
  OdUInt16 createStackedText(TextPropsList& wordList, TextProps& currProps);
  const OdChar* m_pHoldCharPos;
  inline OdChar nextChar()
  {
    m_pHoldCharPos = currPos();
    return OdTextIterator::nextChar();
  }
  OdChar  nextCharAsIs()
  {
    m_pHoldCharPos = currPos();
    return OdTextIterator::nextCharAsIs();
  }
  void processSpecialChar(OdString& str, const TextProps& currProps);

public:
	OdMTextIterator(OdDbDatabase* pDb, const OdString& str,
		OdCodePageId codepage, OdFont* pFont, OdFont* pBigFont) :
		OdTextIterator(str, -1, false, codepage, pFont, pBigFont)
      , m_pDb(pDb)
      , m_pHoldCharPos(NULL)
      , m_bToConvertCp(false)
      , m_processField(false)
      , m_dataTextSize(0.0)
      , m_brocessAsian(true)
  {}

	bool process(TextPropsList& wordList, TextPropsStack& state, ParagraphsList& paragraphs, bool Raw);

  OdString tokenSemicolon();
  OdString tokenSeparator();
  void addTab(TextPropsList& wordList, TextProps& currProps);
  void addNewParagraph(TextPropsList& wordList, TextProps& currProps, ParagraphsList& paraList);
  void addForcedBreak(TextPropsList& wordList, TextProps& currProps);
  void addNewColumn(TextPropsList& wordList, TextProps& currProps, ParagraphsList& paraList);
  bool isR15String();
  bool isR27String();
  OdString heightSwitchesCorrect(double height);

  void setToConvertCp()
  {  
    m_bToConvertCp = true;
  }
  void setProcessField(bool b)
  {
    m_processField = b;
  }
  void setProcessAsian(bool b)
  {
    m_brocessAsian = b;
  }
  void setDoParsePercentPercent(bool b)
  {
    m_DoParsePercentPercent = b;
  }
  static bool breakWordByFonts(TextProps* iWord, OdMTextComplexWord& mtextWord, TextPropsList* wordList, OdDbDatabase* pDb, bool bRaw = true);
};

class OdMTextRendererData;
class OdMTextLine : public LineStats
{

public:
  OdMTextLine() : LineStats()
  , m_linespacingStyle(0)
  , m_start(0.0) 
  , m_trim(0.0)
  , m_bNewColumn(false)
  , m_trimmedWidth(0.0)
  , m_lineSpaceForNext(0.0)
  , m_MaxLineHeight(0.0)
  , m_lineSpacingParagraph(OdTextIndent::kNOLINESPASING)
  , m_bLastLine(false)
  , m_bVertical(false)
  , m_curCharSet(0)
  , m_maxX2LineSpace(0.0)
  , m_maxXLastWord(0.0)
  , m_lineSpace(1.0)
  {}

  OdComplexWordsArray m_FragWords;
  OdInt16 m_linespacingStyle;
  double m_start;
  double m_trim;
  double m_trimmedWidth;
  double m_lineSpaceForNext;
  double m_MaxLineHeight;
  double m_maxX2LineSpace;
  double m_maxXLastWord;

  double m_lineSpace;
  OdTextIndent::LineSpacing m_lineSpacingParagraph;
  OdInt16 m_curCharSet;

  bool m_bNewColumn;
  bool m_bLastLine;
  bool m_bVertical;

public:
  void calcLineParam(bool bFirstLine, const OdMTextRendererData* data, OdMTextLine* prev, bool bCalcWidth = true);
  void calcLineParam(bool bFirstLine, const OdMTextRendererData* data, OdMTextLine* prevLine, OdTextIndent* indent, bool bCalcWidth = true);
  double calcTrimmLineWidth(OdInt32 startWord = 0);
  void addWord(OdMTextComplexWord* complexWord);
  void addToLineStat(TextProps* );
  void clear();
  void getFragments(OdGePoint3d& pos, bool centerJ, bool rightJ, bool bFirstLine, OdTextIndent* indent, FragmentsArray* fragments, double boxWidth);
  void getFragmentsV(OdGePoint3d& pos, bool centerJ, bool rightJ, bool bFirstLine, FragmentsArray* fragments, double boxWidth);
  OdString getContentString(OdMTextFragmentData& style, OdDbDatabase *pDb, bool bR15 = false);
  OdInt32 getAmountSymbols(OdInt32& amSpaces, OdInt32& startWord);
  virtual double getHeightForAligned(int linespacingStyle);
  virtual double caclulateLineSpace(double linespacingFactor);
  double getLineSpaceForNext(double defHeight);

#ifdef _DEBUG
  void dump();
#else
  void dump(){}
#endif
};

typedef OdArray<OdMTextLine> OdLinesArray;

class OdMTextParagraph
{
public:
  OdMTextParagraph(){}

  OdTextIndent m_indent;
  OdLinesArray m_lines;
  void breakToLines(OdComplexWordsArray& words, const OdMTextRendererData* data, TextPropsList* wordList, OdDbDatabase* pDb);
  void breakToLinesV(OdComplexWordsArray& words, const OdMTextRendererData* data, TextPropsList* wordList, OdDbDatabase* pDb);
  void getFragments(OdGePoint3d& pos, bool centerJ, bool rightJ, double boxWidth, FragmentsArray* fragments);
  void getFragmentsV(OdGePoint3d& pos, bool centerJ, bool rightJ, double boxWidth, FragmentsArray* fragments);
  void alignPosition(OdGePoint3d& pos, bool& centerJ, bool& rightJ, double boxWidth);
  void setUseIndentation(bool bUseIndent)
  {
    m_indent.setUseIndentation(bUseIndent);
  }
#ifdef _DEBUG
  void dumpLines();
#else
  void dumpLines(){}
#endif
};

typedef OdArray<OdMTextParagraph> OdMTextParagraphArray;

#ifdef TD_UNICODE
DBENT_EXPORT OdAnsiString convertMTextToDwgCodePage(const OdString& str, OdDbDatabase* pDb, const OdDbObjectId& textStyleId);
DBENT_EXPORT OdString correctMTextCoding(const OdString& str, OdDbDatabase* pDb, const OdDbObjectId& textStyleId);
#else
OdString convertMTextToCodePage(const OdString& str, OdDbDatabase* pDb, const OdDbObjectId& textStyleId, OdCodePageId  from, OdCodePageId  to);
#endif
#endif /* _OD_MTEXT_ITERATOR_H_ */
