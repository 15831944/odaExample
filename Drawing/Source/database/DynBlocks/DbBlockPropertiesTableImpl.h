#ifndef _ODDBBLOCKPROPERTIESTABLEIMPL_INCLUDED_
#define _ODDBBLOCKPROPERTIESTABLEIMPL_INCLUDED_

#include "DbBlockPropertiesTable.h"
#include "DbBlock1PtParameterImpl.h"
#include "DbAttributeDefinition.h"

struct OdDbBlockPropertiesTableImpl : OdDbBlock1PtParameterImpl
{
  DECLARE_GET_IMPL(OdDbBlockPropertiesTable);
  OdString m_sName;
  OdString m_sDesc;
  OdInt32 m_nUnk1; //2 (object version?)

  struct Column
  {
    OdDbObjectId m_pParam;
    OdInt16 m_nUnk1; // 0
    OdInt16 m_nKeyValue; // -1 if unset
    OdString m_sUnk; // ?? (always "")
    OdString m_sConnection;
    OdDbEvalNodeId m_nParamNode;
    OdResBufPtr m_pUnmatchedValue;
    OdResBufPtr m_pDefault;
    bool m_bConstant;
    bool m_bEditable;
    bool m_bRemovable;
    bool m_bAngular;
    bool m_bAttribute;
    OdString m_sFormat;
    OdDbObjectId m_pCustomPropertiesId;
    Column(const OdDbObjectId& param = OdDbObjectId::kNull, const OdString& connection = OdString::kEmpty) : m_pParam(param), m_sConnection(connection),
      m_nUnk1(0), m_nKeyValue(-1), m_nParamNode(0), m_bConstant(false), m_bEditable(true), m_bRemovable(true), m_bAngular(false), m_bAttribute(false)
    {
      OdDbObjectPtr pObj = param.openObject();
      if (!pObj.isNull())
      {
        if (pObj->isKindOf(OdDbBlockParameter::desc()))
        {
          OdDbBlockParameterPtr bp = pObj;
          m_nParamNode = bp->nodeId();
          OdDbBlkParamPropertyDescriptorArray pp;
          bp->getPropertyDescription(pp);
          for (unsigned i = 0; i < pp.size(); ++i)
          {
            if (pp[i].m_sConnection == m_sConnection)
            {
              if (pp[i].m_nUnitsType == OdDbDynBlockReferenceProperty::kAngular)
                m_bAngular = true;
              break;
            }
          }
        }
        else if (pObj->isKindOf(OdDbAttributeDefinition::desc()))
        {
          m_bAttribute = true;
          m_bConstant = OdDbAttributeDefinitionPtr(pObj)->isConstant();
        }
      }
    }
  };
  typedef OdArray<Column> ColumnInfoArray;
  ColumnInfoArray m_Columns;
  struct Row
  {
    OdInt32 id;
    OdResBufArray m_Values;
    Row(OdInt32 _id = 0) : id(_id) {}
  };
  typedef OdArray<Row> RowArray;
  RowArray m_Rows; // rows may be reordered
  int m_nNextRowId; // 
  bool m_bMustMatch;
  bool m_bRuntimeParametersOnly;
  bool m_bInvalid;
  int m_nCurrentRow;

  virtual void getProperties(OdDbBlkParamPropertyDescriptorArray& ar) const ODRX_OVERRIDE
  {
    OdDbBlkParamPropertyDescriptor dsc;
    dsc.m_bListPresent = false;
    dsc.m_bReadonly = false;
    dsc.m_bVisible = m_bShowProperties;
    dsc.m_nType = OdResBuf::kDxfInt16;
    dsc.m_sConnection = L"currentRow";
    dsc.m_sName = m_sName;
    dsc.m_sDescription = m_sDesc;
    ar.append(dsc);
  }

  virtual OdResBufPtr getPropertyValue(const OdString& name, const OdGeMatrix3d& m) const ODRX_OVERRIDE;
  virtual bool setPropertyValue(const OdString& name, const OdResBuf* rb, const OdGeMatrix3d& m) ODRX_OVERRIDE;
  int getCurrentRow() const { return m_nCurrentRow; }
  int getColumnIndex(OdDbEvalNodeId id) const;
  bool evaluate(const OdDbEvalContext*) ODRX_OVERRIDE;

  OdDbBlockPropertiesTableImpl() : OdDbBlock1PtParameterImpl(), m_nNextRowId(0), m_bMustMatch(false), m_nUnk1(2), m_bInvalid(false), m_bRuntimeParametersOnly(true), m_nCurrentRow(-1)
  {
  }
private:
  void getActiveParameters(OdDbEvalGraph* gr, OdIntArray& ) const;
  void setValuesFromCurrentRow(OdDbEvalGraph* gr, OdDbBlockRepresentationContext* rep, std::map<int, OdResBufPtr>* values = 0);
  void findCurrentRow(OdDbEvalGraph* gr, OdDbBlockRepresentationContext* rep);
  void matchRow(std::set<int>& nodesToSkip, std::map<int, OdResBufPtr> values);
};

#endif
