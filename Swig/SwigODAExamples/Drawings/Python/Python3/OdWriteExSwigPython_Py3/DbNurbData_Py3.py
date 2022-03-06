#######################################################################################
# Copyright (C) 2002-2022, Open Design Alliance (the "Alliance").
# All rights reserved.
#
# This software and its documentation and related materials are owned by
# the Alliance.  The software may only be incorporated into application
# programs owned by members of the Alliance, subject to a signed
# Membership Agreement and Supplemental Software License Agreement with the
# Alliance.  The structure and organization of this software are the valuable
# trade secrets of the Alliance and its suppliers.  The software is also
# protected by copyright law and international treaty provisions.  Application
# programs incorporating this software must include the following statement
# with their copyright notices:
#
#   This application incorporates Open Design Alliance software pursuant to a
#   license
#   agreement with Open Design Alliance.
#   Open Design Alliance Copyright (C) 2002-2022 by Open Design Alliance.
#   All rights reserved.
#
# By use of this software, its documentation or related materials, you
# acknowledge and accept the above terms.
#######################################################################################
from ODA_PyMemManager_Py3 import *
from ODA_Kernel_Py3 import *
from ODA_Drawings_Py3 import *

class DbNurbData():  
    degreeInUt0 = 3
    degreeInVt0 = 3
    propsInUt0 = (OdGe.kOpen | OdGe.kNoPoles)
    propsInVt0 = (OdGe.kOpen | OdGe.kNoPoles)
    numControlPointsInUt0 = 6
    numControlPointsInVt0 = 6

    arrHoleLoopKnotsh00 = OdGeDoubleArray()
    arrHoleLoopKnotsh00.push_back(-48.125460674052619)
    arrHoleLoopKnotsh00.push_back(-48.125460674052619)
    arrHoleLoopKnotsh00.push_back(-48.125460674052619)
    arrHoleLoopKnotsh00.push_back(-48.125460674052619)
    arrHoleLoopKnotsh00.push_back(-16.041820224684201)
    arrHoleLoopKnotsh00.push_back(16.041820224684209)
    arrHoleLoopKnotsh00.push_back(48.125460674052619)
    arrHoleLoopKnotsh00.push_back(48.125460674052619)
    arrHoleLoopKnotsh00.push_back(48.125460674052619)
    arrHoleLoopKnotsh00.push_back(48.125460674052619)

    arrHoleLoopParCPSh00 = OdGePoint2dArray()
    arrHoleLoopParCPSh00.push_back(OdGePoint2d(46.304913083018910, -30.324126422369094))
    arrHoleLoopParCPSh00.push_back(OdGePoint2d(46.304913083018889, -39.949218557179620))

    arrHoleLoopParKnotsh00 = OdGeDoubleArray()
    arrHoleLoopParKnotsh00.push_back(-48.125460674052619)
    arrHoleLoopParKnotsh00.push_back(-48.125460674052619)
    arrHoleLoopParKnotsh00.push_back(48.125460674052619)
    arrHoleLoopParKnotsh00.push_back(48.125460674052619)

    #edge2
    arrHoleLoopCPSh01 = OdGePoint3dArray()
    arrHoleLoopCPSh01.push_back(OdGePoint3d(-865.59771257789123,197.05848201972219,98.221357298149528))
    arrHoleLoopCPSh01.push_back(OdGePoint3d(-864.37352815795521,197.05848201972219,98.221357298149513))
    arrHoleLoopCPSh01.push_back(OdGePoint3d(-861.92515931808339,197.05848201972219,98.221357298149528))
    arrHoleLoopCPSh01.push_back(OdGePoint3d(-858.25260605827555,197.05848201972219,98.221357298149513))
    arrHoleLoopCPSh01.push_back(OdGePoint3d(-855.80423721840361,197.05848201972219,98.221357298149513))
    arrHoleLoopCPSh01.push_back(OdGePoint3d(-854.58005279846782,197.05848201972219,98.221357298149528))

    arrHoleLoopKnotsh01 = OdGeDoubleArray()
    arrHoleLoopKnotsh01.push_back(-55.088298897117014)
    arrHoleLoopKnotsh01.push_back(-55.088298897117014)
    arrHoleLoopKnotsh01.push_back(-55.088298897117014)
    arrHoleLoopKnotsh01.push_back(-55.088298897117014)
    arrHoleLoopKnotsh01.push_back(-18.362766299039009)
    arrHoleLoopKnotsh01.push_back(18.362766299038995)
    arrHoleLoopKnotsh01.push_back(55.088298897116999)
    arrHoleLoopKnotsh01.push_back(55.088298897116999)
    arrHoleLoopKnotsh01.push_back(55.088298897116999)
    arrHoleLoopKnotsh01.push_back(55.088298897116999)

    arrTrimmingLoopParCPSh01 = OdGePoint2dArray()
    arrTrimmingLoopParCPSh01.push_back(OdGePoint2d(46.304913083018910, -39.949218557179698))
    arrTrimmingLoopParCPSh01.push_back(OdGePoint2d(35.287253303595314, -39.949218557179577))

    arrTrimmingLoopParKnotsh01 = OdGeDoubleArray()
    arrTrimmingLoopParKnotsh01.push_back(-55.088298897116999)
    arrTrimmingLoopParKnotsh01.push_back(-55.088298897116999)
    arrTrimmingLoopParKnotsh01.push_back(55.088298897116999)
    arrTrimmingLoopParKnotsh01.push_back(55.088298897116999)

    #edge3
    arrHoleLoopCPSh02 = OdGePoint3dArray()
    
    arrHoleLoopCPSh02.push_back(OdGePoint3d(-854.58005279846782,197.05848201972219,98.221357298149528))
    arrHoleLoopCPSh02.push_back(OdGePoint3d(-854.58005279846782,193.85011797478538,98.221357298149528))
    arrHoleLoopCPSh02.push_back(OdGePoint3d(-854.58005279846770,190.64175392984851,98.221357298149513))
    arrHoleLoopCPSh02.push_back(OdGePoint3d(-854.58005279846782,187.43338988491166,98.221357298149528))
    
    arrHoleLoopKnotsh02 = OdGeDoubleArray()
    arrHoleLoopKnotsh02.push_back(-48.125460674052619)
    arrHoleLoopKnotsh02.push_back(-48.125460674052619)
    arrHoleLoopKnotsh02.push_back(-48.125460674052619)
    arrHoleLoopKnotsh02.push_back(-48.125460674052619)
    arrHoleLoopKnotsh02.push_back(48.125460674052619)
    arrHoleLoopKnotsh02.push_back(48.125460674052619)
    arrHoleLoopKnotsh02.push_back(48.125460674052619)
    arrHoleLoopKnotsh02.push_back(48.125460674052619)

    arrHoleLoopParCPSh02 = OdGePoint2dArray()
    arrHoleLoopParCPSh02.push_back(OdGePoint2d(35.287253303595399, -39.949218557179591))
    arrHoleLoopParCPSh02.push_back(OdGePoint2d(35.287253303595357, -30.324126422369066))

    arrHoleLoopParKnotsh02 = OdGeDoubleArray()
    arrHoleLoopParKnotsh02.push_back(-48.125460674052619)
    arrHoleLoopParKnotsh02.push_back(-48.125460674052619)
    arrHoleLoopParKnotsh02.push_back(48.125460674052619)
    arrHoleLoopParKnotsh02.push_back(48.125460674052619)

    #edge4
    arrHoleLoopCPSh03 = OdGePoint3dArray()
    
    arrHoleLoopCPSh03.push_back(OdGePoint3d(-854.58005279846782,187.43338988491166,98.221357298149528))
    arrHoleLoopCPSh03.push_back(OdGePoint3d(-858.25260605827543,187.43338988491166,98.221357298149513))
    arrHoleLoopCPSh03.push_back(OdGePoint3d(-861.92515931808339,187.43338988491166,98.221357298149513))
    arrHoleLoopCPSh03.push_back(OdGePoint3d(-865.59771257789123,187.43338988491166,98.221357298149528))
    
    arrHoleLoopKnotsh03 = OdGeDoubleArray()
    arrHoleLoopKnotsh03.push_back(-55.088298897116999)
    arrHoleLoopKnotsh03.push_back(-55.088298897116999)
    arrHoleLoopKnotsh03.push_back(-55.088298897116999)
    arrHoleLoopKnotsh03.push_back(-55.088298897116999)
    arrHoleLoopKnotsh03.push_back(55.088298897116999)
    arrHoleLoopKnotsh03.push_back(55.088298897116999)
    arrHoleLoopKnotsh03.push_back(55.088298897116999)
    arrHoleLoopKnotsh03.push_back(55.088298897116999)

    arrHoleLoopParCPSh03 = OdGePoint2dArray()
    arrHoleLoopParCPSh03.push_back(OdGePoint2d(35.287253303595342, -30.324126422369062))
    arrHoleLoopParCPSh03.push_back(OdGePoint2d(46.304913083018860, -30.3241264223691))
    arrHoleLoopParKnotsh03 = OdGeDoubleArray()
    arrHoleLoopParKnotsh03.push_back(-55.088298897116999)
    arrHoleLoopParKnotsh03.push_back(-55.088298897116999)
    arrHoleLoopParKnotsh03.push_back(55.088298897116999)
    arrHoleLoopParKnotsh03.push_back(55.088298897116999)

    arrHoleLoopCPSh00 = OdGePoint3dArray()
    
    arrHoleLoopCPSh00.push_back(OdGePoint3d(-865.59771257789123,187.43338988491166,98.221357298149528))
    arrHoleLoopCPSh00.push_back(OdGePoint3d(-865.59771257789123,188.50284456655729,98.221357298149513))
    arrHoleLoopCPSh00.push_back(OdGePoint3d(-865.59771257789123,190.64175392984851,98.221357298149528))
    arrHoleLoopCPSh00.push_back(OdGePoint3d(-865.59771257789112,193.85011797478535,98.221357298149513))
    arrHoleLoopCPSh00.push_back(OdGePoint3d(-865.59771257789123,195.98902733807660,98.221357298149528))
    arrHoleLoopCPSh00.push_back(OdGePoint3d(-865.59771257789123,197.05848201972219,98.221357298149528))
    

    arrCPNURBSt0 = OdGePoint3dArray()
    arrCPNURBSt0.push_back(OdGePoint3d(-764.20450059775521,205.23472413659516,98.221357298149513))
    arrCPNURBSt0.push_back(OdGePoint3d(-764.20450059775544,194.54017732013909,98.221357298149556))
    arrCPNURBSt0.push_back(OdGePoint3d(-764.20450059775521,173.15108368722673,98.221357298149499))
    arrCPNURBSt0.push_back(OdGePoint3d(-764.20450059775533,141.06744323785836,98.221357298149542))
    arrCPNURBSt0.push_back(OdGePoint3d(-764.20450059775499,119.67834960494608,98.221357298149485))
    arrCPNURBSt0.push_back(OdGePoint3d(-764.20450059775521,108.98380278848995,98.221357298149513))
    arrCPNURBSt0.push_back(OdGePoint3d(-776.44634479711408,205.23472413659510,98.221357298149499))
    arrCPNURBSt0.push_back(OdGePoint3d(-776.44634479711431,194.54017732013912,98.221357298149542))
    arrCPNURBSt0.push_back(OdGePoint3d(-776.44634479711408,173.15108368722665,98.221357298149499))
    arrCPNURBSt0.push_back(OdGePoint3d(-776.44634479711431,141.06744323785844,98.221357298149513))
    arrCPNURBSt0.push_back(OdGePoint3d(-776.44634479711397,119.67834960494601,98.221357298149499))
    arrCPNURBSt0.push_back(OdGePoint3d(-776.44634479711408,108.98380278848991,98.221357298149499))
    arrCPNURBSt0.push_back(OdGePoint3d(-800.93003319583340,205.23472413659513,98.221357298149499))
    arrCPNURBSt0.push_back(OdGePoint3d(-800.93003319583363,194.54017732013907,98.221357298149542))
    arrCPNURBSt0.push_back(OdGePoint3d(-800.93003319583352,173.15108368722670,98.221357298149499))
    arrCPNURBSt0.push_back(OdGePoint3d(-800.93003319583340,141.06744323785836,98.221357298149513))
    arrCPNURBSt0.push_back(OdGePoint3d(-800.93003319583340,119.67834960494606,98.221357298149499))
    arrCPNURBSt0.push_back(OdGePoint3d(-800.93003319583340,108.98380278848997,98.221357298149499))
    arrCPNURBSt0.push_back(OdGePoint3d(-837.65556579391148,205.23472413659525,98.221357298149556))
    arrCPNURBSt0.push_back(OdGePoint3d(-837.65556579391171,194.54017732013921,98.221357298149599))
    arrCPNURBSt0.push_back(OdGePoint3d(-837.65556579391159,173.15108368722673,98.221357298149542))
    arrCPNURBSt0.push_back(OdGePoint3d(-837.65556579391159,141.06744323785844,98.221357298149570))
    arrCPNURBSt0.push_back(OdGePoint3d(-837.65556579391136,119.67834960494605,98.221357298149542))
    arrCPNURBSt0.push_back(OdGePoint3d(-837.65556579391148,108.98380278848994,98.221357298149556))
    arrCPNURBSt0.push_back(OdGePoint3d(-862.13925419262989,205.23472413659513,98.221357298149499))
    arrCPNURBSt0.push_back(OdGePoint3d(-862.13925419263012,194.54017732013907,98.221357298149542))
    arrCPNURBSt0.push_back(OdGePoint3d(-862.13925419262989,173.15108368722670,98.221357298149499))
    arrCPNURBSt0.push_back(OdGePoint3d(-862.13925419262989,141.06744323785838,98.221357298149513))
    arrCPNURBSt0.push_back(OdGePoint3d(-862.13925419262966,119.67834960494601,98.221357298149499))
    arrCPNURBSt0.push_back(OdGePoint3d(-862.13925419262989,108.98380278848992,98.221357298149499))
    arrCPNURBSt0.push_back(OdGePoint3d(-874.38109839198921,205.23472413659516,98.221357298149513))
    arrCPNURBSt0.push_back(OdGePoint3d(-874.38109839198944,194.54017732013907,98.221357298149556))
    arrCPNURBSt0.push_back(OdGePoint3d(-874.38109839198898,173.15108368722670,98.221357298149499))
    arrCPNURBSt0.push_back(OdGePoint3d(-874.38109839198933,141.06744323785836,98.221357298149542))
    arrCPNURBSt0.push_back(OdGePoint3d(-874.38109839198933,119.67834960494606,98.221357298149485))
    arrCPNURBSt0.push_back(OdGePoint3d(-874.38109839198921,108.98380278848992,98.221357298149513))

    arrUKnotst0 = OdGeDoubleArray()
    arrUKnotst0.push_back(-55.088298897116999)
    arrUKnotst0.push_back(-55.088298897116999)
    arrUKnotst0.push_back(-55.088298897116999)
    arrUKnotst0.push_back(-55.088298897116999)
    arrUKnotst0.push_back(-18.362766299038995)
    arrUKnotst0.push_back(18.362766299039009)
    arrUKnotst0.push_back(55.088298897117014)
    arrUKnotst0.push_back(55.088298897117014)
    arrUKnotst0.push_back(55.088298897117014)
    arrUKnotst0.push_back(55.088298897117014)

    arrVKnotst0 = OdGeDoubleArray()
    arrVKnotst0.push_back(-48.125460674052619)
    arrVKnotst0.push_back(-48.125460674052619)
    arrVKnotst0.push_back(-48.125460674052619)
    arrVKnotst0.push_back(-48.125460674052619)
    arrVKnotst0.push_back(-16.041820224684209)
    arrVKnotst0.push_back(16.041820224684201)
    arrVKnotst0.push_back(48.125460674052619)
    arrVKnotst0.push_back(48.125460674052619)
    arrVKnotst0.push_back(48.125460674052619)
    arrVKnotst0.push_back(48.125460674052619)

    arrTrimmingLoopCPSt0 = OdGePoint3dArray()
    arrTrimmingLoopCPSt0.push_back(OdGePoint3d(-874.38109839198921,205.23472413659516,98.221357298149513))
    arrTrimmingLoopCPSt0.push_back(OdGePoint3d(-874.38109839198944,194.54017732013907,98.221357298149556))
    arrTrimmingLoopCPSt0.push_back(OdGePoint3d(-874.38109839198898,173.1510836872267,98.221357298149499))
    arrTrimmingLoopCPSt0.push_back(OdGePoint3d(-874.38109839198933,141.06744323785836,98.221357298149542))
    arrTrimmingLoopCPSt0.push_back(OdGePoint3d(-874.38109839198933,119.67834960494606,98.221357298149485))
    arrTrimmingLoopCPSt0.push_back(OdGePoint3d(-874.38109839198921,108.98380278848992,98.221357298149513))
    

    arrTrimmingLoopKnotst0 = OdGeDoubleArray()
    arrTrimmingLoopKnotst0.push_back(-48.125460674052619)
    arrTrimmingLoopKnotst0.push_back(-48.125460674052619) 
    arrTrimmingLoopKnotst0.push_back(-48.125460674052619)
    arrTrimmingLoopKnotst0.push_back(-48.125460674052619)
    arrTrimmingLoopKnotst0.push_back(-16.041820224684209)
    arrTrimmingLoopKnotst0.push_back(16.041820224684201)
    arrTrimmingLoopKnotst0.push_back(48.125460674052619)
    arrTrimmingLoopKnotst0.push_back(48.125460674052619)
    arrTrimmingLoopKnotst0.push_back(48.125460674052619)
    arrTrimmingLoopKnotst0.push_back(48.125460674052619)

    arrTrimmingLoopParCPSt0 = OdGePoint2dArray()
    arrTrimmingLoopParCPSt0.push_back(OdGePoint2d(55.088298897117006, -48.125460674052619))
    arrTrimmingLoopParCPSt0.push_back(OdGePoint2d(55.088298897117014, 48.125460674052619))

    arrTrimmingLoopParKnotst0 = OdGeDoubleArray()
    arrTrimmingLoopParKnotst0.push_back(-48.125460674052619)
    arrTrimmingLoopParKnotst0.push_back(-48.125460674052619)
    arrTrimmingLoopParKnotst0.push_back(48.125460674052619)
    arrTrimmingLoopParKnotst0.push_back(48.125460674052619)

    #edge2
    arrTrimmingLoopCPSt01 = OdGePoint3dArray()
    arrTrimmingLoopCPSt01.push_back(OdGePoint3d(-874.38109839198921,108.98380278848994,98.221357298149513))
    arrTrimmingLoopCPSt01.push_back(OdGePoint3d(-837.65556579391125,108.98380278848994,98.221357298149471))
    arrTrimmingLoopCPSt01.push_back(OdGePoint3d(-800.93003319583181,108.98380278848983,98.221357298149471))
    arrTrimmingLoopCPSt01.push_back(OdGePoint3d(-764.20450059775521,108.98380278848995,98.221357298149513))
    


    arrTrimmingLoopKnotst01 = OdGeDoubleArray()
    arrTrimmingLoopKnotst01.push_back(-55.08829889711699934)
    arrTrimmingLoopKnotst01.push_back(-55.08829889711699934)
    arrTrimmingLoopKnotst01.push_back(-55.08829889711699934)
    arrTrimmingLoopKnotst01.push_back(-55.08829889711699934)
    arrTrimmingLoopKnotst01.push_back(55.08829889711699934)
    arrTrimmingLoopKnotst01.push_back(55.08829889711699934)
    arrTrimmingLoopKnotst01.push_back(55.08829889711699934)
    arrTrimmingLoopKnotst01.push_back(55.08829889711699934)

    arrTrimmingLoopParCPSt01 = OdGePoint2dArray()
    arrTrimmingLoopParCPSt01.push_back(OdGePoint2d(55.08829889711700645, 48.12546067405261141))
    arrTrimmingLoopParCPSt01.push_back(OdGePoint2d(-55.08829889711699934, 48.12546067405261141))

    arrTrimmingLoopParKnotst01 = OdGeDoubleArray()
    arrTrimmingLoopParKnotst01.push_back(-55.08829889711699934)
    arrTrimmingLoopParKnotst01.push_back(-55.08829889711699934)
    arrTrimmingLoopParKnotst01.push_back(55.08829889711699934)
    arrTrimmingLoopParKnotst01.push_back(55.08829889711699934)

    #edge3
    arrTrimmingLoopCPSt02 = OdGePoint3dArray()
    arrTrimmingLoopCPSt02.push_back(OdGePoint3d(-764.20450059775521,108.98380278848995,98.221357298149513))
    arrTrimmingLoopCPSt02.push_back(OdGePoint3d(-764.20450059775453,141.0674432378583,98.221357298149428))
    arrTrimmingLoopCPSt02.push_back(OdGePoint3d(-764.2045005977559,173.15108368722696,98.221357298149641))
    arrTrimmingLoopCPSt02.push_back(OdGePoint3d(-764.20450059775521,205.23472413659516,98.221357298149513))
    

    arrTrimmingLoopKnotst02 = OdGeDoubleArray()
    arrTrimmingLoopKnotst02.push_back(-48.125460674052619)
    arrTrimmingLoopKnotst02.push_back(-48.125460674052619)
    arrTrimmingLoopKnotst02.push_back(-48.125460674052619)
    arrTrimmingLoopKnotst02.push_back(-48.125460674052619)
    arrTrimmingLoopKnotst02.push_back(48.125460674052619)
    arrTrimmingLoopKnotst02.push_back(48.125460674052619)
    arrTrimmingLoopKnotst02.push_back(48.125460674052619)
    arrTrimmingLoopKnotst02.push_back(48.125460674052619)

    arrTrimmingLoopParCPSt02 = OdGePoint2dArray() 
    arrTrimmingLoopParCPSt02.push_back(OdGePoint2d(-55.088298897116999, 48.125460674052611))
    arrTrimmingLoopParCPSt02.push_back(OdGePoint2d(-55.088298897116999, -48.125460674052619))

    arrTrimmingLoopParKnotst02 = OdGeDoubleArray()
    arrTrimmingLoopParKnotst02.push_back(-48.125460674052619)
    arrTrimmingLoopParKnotst02.push_back(-48.125460674052619)
    arrTrimmingLoopParKnotst02.push_back(48.125460674052619)
    arrTrimmingLoopParKnotst02.push_back(48.125460674052619)

    #edge4
    arrTrimmingLoopCPSt03 = OdGePoint3dArray()
    arrTrimmingLoopCPSt03.push_back(OdGePoint3d(-764.20450059775521,205.23472413659516,98.221357298149513))
    arrTrimmingLoopCPSt03.push_back(OdGePoint3d(-776.44634479711408,205.2347241365951,98.221357298149499))
    arrTrimmingLoopCPSt03.push_back(OdGePoint3d(-800.9300331958334,205.23472413659513,98.221357298149499))
    arrTrimmingLoopCPSt03.push_back(OdGePoint3d(-837.65556579391148,205.23472413659525,98.221357298149556))
    arrTrimmingLoopCPSt03.push_back(OdGePoint3d(-862.13925419262989,205.23472413659513,98.221357298149499))
    arrTrimmingLoopCPSt03.push_back(OdGePoint3d(-874.38109839198921,205.23472413659516,98.221357298149513))
    

    arrTrimmingLoopKnotst03 = OdGeDoubleArray()
    arrTrimmingLoopKnotst03.push_back(-55.088298897116999)
    arrTrimmingLoopKnotst03.push_back(-55.088298897116999)
    arrTrimmingLoopKnotst03.push_back(-55.088298897116999)
    arrTrimmingLoopKnotst03.push_back(-55.088298897116999)
    arrTrimmingLoopKnotst03.push_back(-18.362766299038995)
    arrTrimmingLoopKnotst03.push_back(18.362766299039009)
    arrTrimmingLoopKnotst03.push_back(55.088298897117014)
    arrTrimmingLoopKnotst03.push_back(55.088298897117014)
    arrTrimmingLoopKnotst03.push_back(55.088298897117014)
    arrTrimmingLoopKnotst03.push_back(55.088298897117014)

    arrTrimmingLoopParCPSt03 = OdGePoint2dArray()
    arrTrimmingLoopParCPSt03.push_back(OdGePoint2d(-55.088298897116999, -48.125460674052619))
    arrTrimmingLoopParCPSt03.push_back(OdGePoint2d(55.088298897117014, -48.125460674052619))

    arrTrimmingLoopParKnotst03 = OdGeDoubleArray()
    arrTrimmingLoopParKnotst03.push_back(-55.08829889711699934)
    arrTrimmingLoopParKnotst03.push_back(-55.08829889711699934)
    arrTrimmingLoopParKnotst03.push_back(55.08829889711699934)
    arrTrimmingLoopParKnotst03.push_back(55.08829889711699934)

    
    @staticmethod
    def fillNurbData(nurbSurf,arrLoops,arrLoopsPar):
       #*******************************************************************/
       # Create NURBS surface */
       #*******************************************************************/
       controlPoints = None
       arrWeights = OdGeDoubleArray()
       controlPoints = OdGePoint3dArray(DbNurbData.arrCPNURBSt0)
       uKnots = OdGeKnotVector(DbNurbData.arrUKnotst0)
       vKnots = OdGeKnotVector(DbNurbData.arrVKnotst0)
       nurbSurf.set(3, DbNurbData.degreeInVt0, DbNurbData.propsInUt0, DbNurbData.propsInVt0, DbNurbData.numControlPointsInUt0, DbNurbData.numControlPointsInVt0, controlPoints, arrWeights, uKnots, vKnots)
       #*******************************************************************/
       # Create trimming-loop, edge0 */
       #*******************************************************************/
       controlPoints = OdGePoint3dArray(DbNurbData.arrTrimmingLoopCPSt0)
       vecTrimmingLoopKnots00 = OdGeKnotVector(DbNurbData.arrTrimmingLoopKnotst0)
       pTrimmigLoopCurve00 = OdGeNurbCurve3d(3, vecTrimmingLoopKnots00, controlPoints, arrWeights, False)
       #*******************************************************************/
       # Trimming-loop, edge1 */
       #*******************************************************************/
       controlPoints = OdGePoint3dArray(DbNurbData.arrTrimmingLoopCPSt01)
       vecTrimmingLoopKnots01 = OdGeKnotVector(DbNurbData.arrTrimmingLoopKnotst01)
       pTrimmigLoopCurve01 = OdGeNurbCurve3d(3, vecTrimmingLoopKnots01, controlPoints, arrWeights, False)
       #*******************************************************************/
       # Trimming-loop, edge2 */
       #*******************************************************************/
       controlPoints = OdGePoint3dArray(DbNurbData.arrTrimmingLoopCPSt02)
       vecTrimmingLoopKnots02 = OdGeKnotVector(DbNurbData.arrTrimmingLoopKnotst02)
       pTrimmigLoopCurve02 = OdGeNurbCurve3d(3, vecTrimmingLoopKnots02, controlPoints, arrWeights, False)
       #*******************************************************************/
       # Trimming-loop, edge3 */
       #*******************************************************************/
       controlPoints = OdGePoint3dArray(DbNurbData.arrTrimmingLoopCPSt03)
       vecTrimmingLoopKnots03 = OdGeKnotVector(DbNurbData.arrTrimmingLoopKnotst03)
       pTrimmigLoopCurve03 = OdGeNurbCurve3d(3, vecTrimmingLoopKnots03, controlPoints, arrWeights, False)
       
       #*******************************************************************/
       # Create second loop curve(hole), edge0 */
       #*******************************************************************/
       controlPoints = OdGePoint3dArray(DbNurbData.arrHoleLoopCPSh00)
       vecHoleLoopKnots00 = OdGeKnotVector(DbNurbData.arrHoleLoopKnotsh00)
       pHoleLoopCurve00 = OdGeNurbCurve3d(3, vecHoleLoopKnots00, controlPoints, arrWeights, False)
       #*******************************************************************/
       # Hole, edge1 */
       #*******************************************************************/
       controlPoints = OdGePoint3dArray(DbNurbData.arrHoleLoopCPSh01)
       vecHoleLoopKnots01 = OdGeKnotVector(DbNurbData.arrHoleLoopKnotsh01)
       pHoleLoopCurve01 = OdGeNurbCurve3d(3, vecHoleLoopKnots01, controlPoints, arrWeights, False)
       #*******************************************************************/
       # Hole, edge2 */
       #*******************************************************************/
       controlPoints = OdGePoint3dArray(DbNurbData.arrHoleLoopCPSh02)
       vecHoleLoopKnots02 = OdGeKnotVector(DbNurbData.arrHoleLoopKnotsh02)
       pHoleLoopCurve02 = OdGeNurbCurve3d(3, vecHoleLoopKnots02, controlPoints, arrWeights, False)
       #*******************************************************************/
       # Hole, edge3 */
       #*******************************************************************/
       controlPoints = OdGePoint3dArray(DbNurbData.arrHoleLoopCPSh03)
       vecHoleLoopKnots03 = OdGeKnotVector(DbNurbData.arrHoleLoopKnotsh03)
       pHoleLoopCurve03 = OdGeNurbCurve3d(3, vecHoleLoopKnots03, controlPoints, arrWeights, False)
       #*******************************************************************/
       # Create arrays - first is a trimming-loop, next - hole */
       #*******************************************************************/
       
       arrCurvesTrimmingLoop = OdGeNurbCurve3dArrayPtr()
       arrCurvesHole = OdGeNurbCurve3dArrayPtr()

       pTrimmigLoopCurve00.thisown = False
       pTrimmigLoopCurve01.thisown = False
       pTrimmigLoopCurve02.thisown = False
       pTrimmigLoopCurve03.thisown = False

       arrCurvesTrimmingLoop.push_back(pTrimmigLoopCurve00)
       arrCurvesTrimmingLoop.push_back(pTrimmigLoopCurve01)
       arrCurvesTrimmingLoop.push_back(pTrimmigLoopCurve02)
       arrCurvesTrimmingLoop.push_back(pTrimmigLoopCurve03)
       arrLoops.push_back(arrCurvesTrimmingLoop)
       
       pHoleLoopCurve00.thisown = False
       pHoleLoopCurve01.thisown = False
       pHoleLoopCurve02.thisown = False
       pHoleLoopCurve03.thisown = False
       arrCurvesHole.push_back(pHoleLoopCurve00)
       arrCurvesHole.push_back(pHoleLoopCurve01)
       arrCurvesHole.push_back(pHoleLoopCurve02)
       arrCurvesHole.push_back(pHoleLoopCurve03)
       arrLoops.push_back(arrCurvesHole)
       
       
       #*******************************************************************/
       # Create parametric curves.  For geometry of edge0 */
       #*******************************************************************/
       controlPoints2d = None
       controlPoints2d = OdGePoint2dArray(DbNurbData.arrTrimmingLoopParCPSt0)
       vecTrimmingLoopParKnots = OdGeKnotVector(DbNurbData.arrTrimmingLoopParKnotst0)
       pParTrimmigLoopCurve00 = OdGeNurbCurve2d(1, vecTrimmingLoopParKnots, controlPoints2d, arrWeights, False)
       #*******************************************************************/
       # For geometry of edge1 */
       #*******************************************************************/
       controlPoints2d = OdGePoint2dArray(DbNurbData.arrTrimmingLoopParCPSt01)
       vecTrimmingLoopParKnots01 = OdGeKnotVector(DbNurbData.arrTrimmingLoopParKnotst01)
       pParTrimmigLoopCurve01 = OdGeNurbCurve2d(1, vecTrimmingLoopParKnots01, controlPoints2d, arrWeights, False)
       #*******************************************************************/
       # For geometry of edge2 */
       #*******************************************************************/
       controlPoints2d = OdGePoint2dArray(DbNurbData.arrTrimmingLoopParCPSt02)
       vecTrimmingLoopParKnots02 = OdGeKnotVector(DbNurbData.arrTrimmingLoopParKnotst02)
       pParTrimmigLoopCurve02 = OdGeNurbCurve2d(1, vecTrimmingLoopParKnots02, controlPoints2d, arrWeights, False)
       #*******************************************************************/
       # For geometry of edge3 */
       #*******************************************************************/
       controlPoints2d = OdGePoint2dArray(DbNurbData.arrTrimmingLoopParCPSt03)
       vecTrimmingLoopParKnots03 = OdGeKnotVector(DbNurbData.arrTrimmingLoopParKnotst03)
       pParTrimmigLoopCurve03 = OdGeNurbCurve2d(1, vecTrimmingLoopParKnots03, controlPoints2d, arrWeights, False)
       #*******************************************************************/
       #  Create parametric curves for hole.  For edge0 */
       #*******************************************************************/
       controlPoints2d = OdGePoint2dArray(DbNurbData.arrHoleLoopParCPSh00)
       vecHoleLoopParKnots = OdGeKnotVector(DbNurbData.arrHoleLoopParKnotsh00)
       pParHoleLoopCurve00 = OdGeNurbCurve2d(1, vecTrimmingLoopParKnots, controlPoints2d, arrWeights, False)
       #*******************************************************************/
       #  Create parametric curves for hole.  For edge1 */
       #*******************************************************************/
       controlPoints2d = OdGePoint2dArray(DbNurbData.arrTrimmingLoopParCPSh01)
       vecHoleLoopParKnots01 = OdGeKnotVector(DbNurbData.arrTrimmingLoopParKnotsh01)
       pParHoleLoopCurve01 = OdGeNurbCurve2d(1, vecHoleLoopParKnots01, controlPoints2d, arrWeights, False)
       #*******************************************************************/
       #  Create parametric curves for hole.  For edge2 */
       #*******************************************************************/
       controlPoints2d = OdGePoint2dArray(DbNurbData.arrHoleLoopParCPSh02)
       vecHoleLoopParKnots02 = OdGeKnotVector(DbNurbData.arrHoleLoopParKnotsh02)
       pParHoleLoopCurve02 = OdGeNurbCurve2d(1, vecHoleLoopParKnots02, controlPoints2d, arrWeights, False)
       #*******************************************************************/
       #  Create parametric curves for hole.  For edge3 */
       #*******************************************************************/
       controlPoints2d = OdGePoint2dArray(DbNurbData.arrHoleLoopParCPSh03)
       vecHoleLoopParKnots03 = OdGeKnotVector(DbNurbData.arrHoleLoopParKnotsh03)
       pParHoleLoopCurve03 = OdGeNurbCurve2d(1, vecHoleLoopParKnots03, controlPoints2d, arrWeights, False)
       
       #*******************************************************************/
       # Create parametric curves arrays */
       #*******************************************************************/
       arrTrimmingLoopPar = OdGeNurbCurve2dArrayPtr()
       arrCurvesParHole = OdGeNurbCurve2dArrayPtr()

       pParTrimmigLoopCurve00.thisown = False
       pParTrimmigLoopCurve01.thisown = False
       pParTrimmigLoopCurve02.thisown = False
       pParTrimmigLoopCurve03.thisown = False

       arrTrimmingLoopPar.push_back(pParTrimmigLoopCurve00)
       arrTrimmingLoopPar.push_back(pParTrimmigLoopCurve01)
       arrTrimmingLoopPar.push_back(pParTrimmigLoopCurve02)
       arrTrimmingLoopPar.push_back(pParTrimmigLoopCurve03)
       
       pParHoleLoopCurve00.thisown = False
       pParHoleLoopCurve01.thisown = False
       pParHoleLoopCurve02.thisown = False
       pParHoleLoopCurve03.thisown = False

       arrCurvesParHole.push_back(pParHoleLoopCurve00)
       arrCurvesParHole.push_back(pParHoleLoopCurve01)
       arrCurvesParHole.push_back(pParHoleLoopCurve02)
       arrCurvesParHole.push_back(pParHoleLoopCurve03)
       
       arrLoopsPar.push_back(arrTrimmingLoopPar)
       arrLoopsPar.push_back(arrCurvesParHole)
       return