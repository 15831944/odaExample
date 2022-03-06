#pragma once

#include "OdaCommon.h"
#include "OdString.h"
#include "ImportBase.hpp"

class AbstructBimImport : public BaseImportWorker {
protected:
  std::tuple<bool, bool> subFilter(const OdString& name, const std::vector<OdString>& all) override {
    auto isHave3DView = false;
    for (const auto& viewName : all)
    {
      if (viewName.find(L"3D Views\\{3D}") != -1)
      {
        isHave3DView = true;
        break;
      }
    }

    const OdString view3dFilterName = isHave3DView ? L"3D Views\\{3D}" : L"3D Views\\";

    const auto isSheets = name.find(L"Sheets\\") != -1;
    const auto is3D = name.find(view3dFilterName) != -1;
    return std::make_tuple(is3D || isSheets, is3D);
  }

  void subOrderModelList() override {
    std::sort(m_listModels.begin(), m_listModels.end(), AbstructBimImport::BimModelListLess);
  }

  struct {
    bool operator() (const OdString& a, const OdString& b) const {
      return a.find(L"3D Views\\{3D}") != -1;
    }
  } BimModelListLess;
};