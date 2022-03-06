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
#include "tvifileopenthreadtask.h"

#include "tvidatabaseinfo.h"

#include <QElapsedTimer>

#include "tviutils.h"

TviFileOpenThreadTask::TviFileOpenThreadTask(OdTvBaseImportParams *params, TviDatabaseInfo info, const OdString& filePath
                                             , TviAppearanceParams *generalParams, bool bLowMemory)
    : m_baseParams(params), m_dbInfo(info), m_filePath(filePath), m_pGeneralParams(generalParams), m_bLowMemory(bLowMemory)
{
}

void TviFileOpenThreadTask::run()
{
    try
    {
        OdTvResult rc = tvOk;

        if(m_dbInfo.getType() == TviDatabaseInfo::kFromFile)
        {

            QElapsedTimer timer;
            timer.start();
            OdTvVsfImportParams params;
            params.setFilePath( m_dbInfo.getFilePath() );
            params.setMtImport( !m_pGeneralParams->getPartialOpen() );
            m_TvDatabaseId = odTvGetFactory().importFile(&params, &rc);

            // fill profiling info
            if (m_baseParams->getProfiling())
              m_baseParams->getProfiling()->setImportTime(OdInt64(timer.elapsed()));

            if (rc != tvOk)
            {
                OdString msg = "Reading of file failed";
                getController()->error( toQString(msg) );
            }
        }
        else
        {
            m_baseParams->setFilePath(m_filePath);
            m_dbInfo.setFilePath(m_filePath);

            if ( !m_bLowMemory )
              m_TvDatabaseId = odTvGetFactory().importFile(m_baseParams, &rc);
            else
            {
              rc = odTvGetFactory().lowMemoryImportFile(m_baseParams, m_dbInfo.getFilePath() + L".vsf");
              if( rc == tvOk )
              {
                OdTvVsfImportParams params;
                params.setFilePath( m_dbInfo.getFilePath() + L".vsf" );
                params.setMtImport( false );
                m_TvDatabaseId = odTvGetFactory().importFile( &params, &rc );
              }
            }

            if (rc != tvOk)
            {
                OdString msg;
                if (rc == tvMissingFilerModule)
                    msg = "Missing filer module.";
                else
                    msg = "Error during open file.";
                getController()->error( toQString(msg) );
            }
        }

    }
    catch (OdTvError &err)
    {
        getController()->error( toQString(err.description()) );
    }

}


