#include "OdaCommon.h"
#include "OdString.h"
#include "ImportBase.hpp"

class ImportDWG : public BaseImportWorker {
protected:
  OdTvDatabaseId subImport
  (const OdString& sourcePath, OdBaseConvertOptions* opt, const OdString &model = L"", bool autoFind = true) override;

  OdTvDatabaseId subImportAll(const OdString& sourcePath, OdBaseConvertOptions* opt) override;
public:
  std::shared_ptr<OdTvBaseImportParams> getImportParams(const OdString& pathToFile, bool isNeedGenerateCDA = true) override;


  std::shared_ptr<OdTvBaseImportParams> getAppendParams(const OdString& pathToFile, bool isNeedGenerateCDA = true) override;

};