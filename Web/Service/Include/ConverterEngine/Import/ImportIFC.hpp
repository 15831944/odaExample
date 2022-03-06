#include "OdaCommon.h"
#include "OdString.h"
#include "ImportBase.hpp"

class ImportIFC : public BaseImportWorker {
protected:
  virtual OdTvDatabaseId subImport
  (
    const OdString& sourcePath,
    OdBaseConvertOptions* opt,
    const OdString &model = L"",
    bool autoFind = true
  ) override;

  virtual void actionAfterGsUpdate(const OdTvDatabaseId& dbId) override;

  std::tuple<bool, bool> subFilter(const OdString& name, const std::vector<OdString>& all) override;
public:
  std::shared_ptr<OdTvBaseImportParams> getImportParams(const OdString& pathToFile, bool isNeedGenerateCDA = true) override;

  std::shared_ptr<OdTvBaseImportParams> getAppendParams(const OdString& pathToFile, bool isNeedGenerateCDA = true) override;
};