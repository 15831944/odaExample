import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.3

Dialog {
    id: dialog
    title: "Model statistic"
    standardButtons: Dialog.Ok | Dialog.Cancel
    anchors.centerIn: parent
    modal: true

    enum ModelStatisticType {
        NumEntity = 0,
        NumLight = 1,
        NumInsert = 2,
        NumPolyline = 3,
        NumCircle = 4,
        NumCircleWedge = 5,
        NumCircularArc = 6,
        NumEllipse = 7,
        NumEllipticArc = 8,
        NumPolygon = 9,
        NumText = 10,
        NumShell = 11,
        NumSphere = 12,
        NumCylinder = 13,
        NumBox = 14,
        NumGeomInsert = 15,
        NumSubEntity = 16,
        NumNurbs = 17,
        NumRasterImage = 18,
        NumInfiniteLine = 19,
        NumMesh = 20,
        NumPointCloud = 21,
        NumRcsPointCloud = 22,
        NumGrid = 23,
        NumColoredShape = 24,
        NumBrep = 25,
        NumPoints = 26,
        NumFace = 27
    }

    function initEntityObjectsStat() {
        var numEnt = tviController.getStatistic( ModelStatisticDialog.ModelStatisticType.NumEntity );
        var numIns = tviController.getStatistic( ModelStatisticDialog.ModelStatisticType.NumInsert );
        var numLight = tviController.getStatistic( ModelStatisticDialog.ModelStatisticType.NumLight );
        if(numEnt > 0 || numIns  > 0|| numLight > 0) {
            entityTypeGroup.visible = true;
            if( entitiesLt.visible = numEnt > 0 )
                numEntitiesId.text = "" + numEnt;
            if( insertsLt.visible = numIns > 0 )
                numInsertsId.text = "" + numIns;
            if( lightsLt.visible = numIns > 0 )
                numLightsId.text = "" + numLight;
        }
    }

    function initGeometryObjectsStat() {
        var sum = 0;
        for (var i = +ModelStatisticDialog.ModelStatisticType.NumPolyline; i < +ModelStatisticDialog.ModelStatisticType.NumPoints; i++)
            sum += tviController.getStatistic( i );
        if(sum == 0)
            return;
        geometryGroup.visible = true;
        var numPolylines = tviController.getStatistic( ModelStatisticDialog.ModelStatisticType.NumPolyline );
        if( polylineLt.visible = numPolylines > 0 ) numPolylinesId.text = "" + numPolylines;
        var numCirc = tviController.getStatistic( ModelStatisticDialog.ModelStatisticType.NumCircle );
        if( circleLt.visible = numCirc > 0 ) numCirclesId.text = "" + numCirc;
        var numCircWedge = tviController.getStatistic( ModelStatisticDialog.ModelStatisticType.NumCircleWedge );
        if( circWedgeLt.visible = numCircWedge > 0 ) numCircWedgesId.text = "" + numCircWedge;
        var numCircArc = tviController.getStatistic( ModelStatisticDialog.ModelStatisticType.NumCircularArc );
        if( circArcLt.visible = numCircArc > 0 ) numCircArcsId.text = "" + numCircArc;
        var numEllipse = tviController.getStatistic( ModelStatisticDialog.ModelStatisticType.NumEllipse );
        if( ellipseLt.visible = numEllipse > 0 ) numEllipsesId.text = "" + numEllipse;
        var numEllipArc = tviController.getStatistic( ModelStatisticDialog.ModelStatisticType.NumEllipticArc );
        if( ellipArcLt.visible = numEllipArc > 0 ) numEllipArcsId.text = "" + numEllipArc;
        var numPolygon = tviController.getStatistic( ModelStatisticDialog.ModelStatisticType.NumPolygon );
        if( polygonLt.visible = numPolygon > 0 ) numPolygonsId.text = "" + numPolygon;
        var numText = tviController.getStatistic( ModelStatisticDialog.ModelStatisticType.NumText );
        if( textLt.visible = numText > 0 ) numTextId.text = "" + numText;
        var numShell = tviController.getStatistic( ModelStatisticDialog.ModelStatisticType.NumShell );
        if( shellLt.visible = numShell > 0 ) numShellsId.text = "" + numShell;
        var numSphere = tviController.getStatistic( ModelStatisticDialog.ModelStatisticType.NumSphere );
        if( sphereLt.visible = numSphere > 0 ) numSpheresId.text = "" + numSphere;
        var numCylinder = tviController.getStatistic( ModelStatisticDialog.ModelStatisticType.NumCylinder );
        if( cylinderLt.visible = numCylinder > 0 ) numCylindersId.text = "" + numCylinder;
        var numBox = tviController.getStatistic( ModelStatisticDialog.ModelStatisticType.NumBox );
        if( boxesLt.visible = numBox > 0 ) numBoxesId.text = "" + numBox;
        var numGeomInsert = tviController.getStatistic( ModelStatisticDialog.ModelStatisticType.NumGeomInsert );
        if( geomInsertLt.visible = numGeomInsert > 0 ) numGeomInsertsId.text = "" + numGeomInsert;
        var numSubEnt = tviController.getStatistic( ModelStatisticDialog.ModelStatisticType.NumSubEntity );
        if( subEntLt.visible = numSubEnt > 0 ) numSubEntitiesId.text = "" + numSubEnt;
        var numNurbs = tviController.getStatistic( ModelStatisticDialog.ModelStatisticType.NumNurbs );
        if( nurbsLt.visible = numNurbs > 0 ) numNurbsId.text = "" + numNurbs;
        var numRasterImg = tviController.getStatistic( ModelStatisticDialog.ModelStatisticType.NumRasterImage );
        if( rasterImgLt.visible = numRasterImg > 0 ) numRasterImgsId.text = "" + numRasterImg;
        var numInfLine = tviController.getStatistic( ModelStatisticDialog.ModelStatisticType.NumInfiniteLine );
        if( infLinesLt.visible = numInfLine > 0 ) numInfLinesId.text = "" + numInfLine;
        var numMesh = tviController.getStatistic( ModelStatisticDialog.ModelStatisticType.NumMesh );
        if( meshesLt.visible = numMesh > 0 ) numMeshesId.text = "" + numMesh;
        var numPntCloud = tviController.getStatistic( ModelStatisticDialog.ModelStatisticType.NumPointCloud );
        if( pntCloudLt.visible = numPntCloud > 0 ) numPntCloudsId.text = "" + numPntCloud;
        var numGrid = tviController.getStatistic( ModelStatisticDialog.ModelStatisticType.NumGrid );
        if( gridLt.visible = numGrid > 0 ) numGridsId.text = "" + numGrid;
        var numColoredShape = tviController.getStatistic( ModelStatisticDialog.ModelStatisticType.NumColoredShape );
        if( colorShapeLt.visible = numColoredShape > 0 ) numColoredShapesId.text = "" + numColoredShape;
        var numRcsPntCloud = tviController.getStatistic( ModelStatisticDialog.ModelStatisticType.NumRcsPointCloud );
        if( rcsPntCloudLt.visible = numRcsPntCloud > 0 ) numRcsPntCloudsId.text = "" + numRcsPntCloud;
        var numBrep = tviController.getStatistic( ModelStatisticDialog.ModelStatisticType.NumBrep );
        if( brepLt.visible = numBrep > 0 ) numBrepsId.text = "" + numBrep;
    }

    function initGeomObjectsInfoStat() {
        var numPnts = tviController.getStatistic( ModelStatisticDialog.ModelStatisticType.NumPoints );
        var numFaces = tviController.getStatistic( ModelStatisticDialog.ModelStatisticType.NumFace );
        if(numPnts > 0 || numFaces  > 0) {
            geometryInfoGroup.visible = true;
            if( pointsLt.visible = numPnts > 0 ) numPointsId.text = "" + numPnts;
            if( facesLt.visible = numFaces > 0 ) numFacesId.text = "" + numFaces;
        }
    }

    function initializeControls() {
        initEntityObjectsStat();
        initGeometryObjectsStat();
        initGeomObjectsInfoStat();
    }

    onVisibleChanged: {
        if(!visible)
            return;
        initializeControls();
        if( scrollView.contentHeight > parent.height * 0.8 )
            height = parent.height * 0.8;
    }

    ScrollView {
        id: scrollView
        clip: true
        ScrollBar.vertical.interactive: true
        anchors.fill: parent

        ColumnLayout {
            anchors.fill: parent

            // Add entity objects statistic
            GroupBox {
                id: entityTypeGroup
                title: "Entity objects"
                Layout.fillWidth: true

                ColumnLayout {
                    anchors.fill: parent

                    RowLayout {
                        id: entitiesLt
                        Label { text: "Num of entities:"; Layout.fillWidth: true; }
                        Label { id: numEntitiesId; text: "0"; }
                    }

                    RowLayout {
                        id: insertsLt
                        Label { text: "Num of inserts:"; Layout.fillWidth: true; }
                        Label { id: numInsertsId; text: "0"; }
                    }

                    RowLayout {
                        id: lightsLt
                        Label { text: "Num of lights:"; Layout.fillWidth: true; }
                        Label { id: numLightsId; text: "0"; }
                    }
                }
            }

            // Add geometry objects staticstic
            GroupBox {
                id: geometryGroup
                title: "Geometry objects"
                Layout.fillWidth: true

                ColumnLayout {
                    anchors.fill: parent

                    RowLayout {
                        id: polylineLt
                        Label { text: "Num of polylines:"; Layout.fillWidth: true; }
                        Label { id: numPolylinesId; text: "0"; }
                    }

                    RowLayout {
                        id: circleLt
                        Label { text: "Num of circles:"; Layout.fillWidth: true; }
                        Label { id: numCirclesId; text: "0"; }
                    }

                    RowLayout {
                        id: circWedgeLt
                        Label { text: "Num of circle wedges:"; Layout.fillWidth: true; }
                        Label { id: numCircWedgesId; text: "0"; }
                    }

                    RowLayout {
                        id: circArcLt
                        Label { text: "Num of circle arcs:"; Layout.fillWidth: true; }
                        Label { id: numCircArcsId; text: "0"; }
                    }

                    RowLayout {
                        id: ellipseLt
                        Label { text: "Num of ellipses:"; Layout.fillWidth: true; }
                        Label { id: numEllipsesId; text: "0"; }
                    }

                    RowLayout {
                        id: ellipArcLt
                        Label { text: "Num of elliptic arcs:"; Layout.fillWidth: true; }
                        Label { id: numEllipArcsId; text: "0"; }
                    }

                    RowLayout {
                        id: polygonLt
                        Label { text: "Num of polygons:"; Layout.fillWidth: true; }
                        Label { id: numPolygonsId; text: "0"; }
                    }

                    RowLayout {
                        id: textLt
                        Label { text: "Num of text:"; Layout.fillWidth: true; }
                        Label { id: numTextId; text: "0"; }
                    }

                    RowLayout {
                        id: shellLt
                        Label { text: "Num of shells:"; Layout.fillWidth: true; }
                        Label { id: numShellsId; text: "0"; }
                    }

                    RowLayout {
                        id: sphereLt
                        Label { text: "Num of spheres:"; Layout.fillWidth: true; }
                        Label { id: numSpheresId; text: "0"; }
                    }

                    RowLayout {
                        id: cylinderLt
                        Label { text: "Num of cylinders:"; Layout.fillWidth: true; }
                        Label { id: numCylindersId; text: "0"; }
                    }

                    RowLayout {
                        id: boxesLt
                        Label { text: "Num of boxes:"; Layout.fillWidth: true; }
                        Label { id: numBoxesId; text: "0"; }
                    }

                    RowLayout {
                        id: geomInsertLt
                        Label { text: "Num of inserts:"; Layout.fillWidth: true; }
                        Label { id: numGeomInsertsId; text: "0"; }
                    }

                    RowLayout {
                        id: subEntLt
                        Label { text: "Num of sub entities:"; Layout.fillWidth: true; }
                        Label { id: numSubEntitiesId; text: "0"; }
                    }

                    RowLayout {
                        id: nurbsLt
                        Label { text: "Num of nurbs:"; Layout.fillWidth: true; }
                        Label { id: numNurbsId; text: "0"; }
                    }

                    RowLayout {
                        id: rasterImgLt
                        Label { text: "Num of raster images:"; Layout.fillWidth: true; }
                        Label { id: numRasterImgsId; text: "0"; }
                    }

                    RowLayout {
                        id: infLinesLt
                        Label { text: "Num of infinite lines:"; Layout.fillWidth: true; }
                        Label { id: numInfLinesId; text: "0"; }
                    }

                    RowLayout {
                        id: meshesLt
                        Label { text: "Num of meshes:"; Layout.fillWidth: true; }
                        Label { id: numMeshesId; text: "0"; }
                    }

                    RowLayout {
                        id: pntCloudLt
                        Label { text: "Num of point clouds:"; Layout.fillWidth: true; }
                        Label { id: numPntCloudsId; text: "0"; }
                    }

                    RowLayout {
                        id: gridLt
                        Label { text: "Num of grids:"; Layout.fillWidth: true; }
                        Label { id: numGridsId; text: "0"; }
                    }

                    RowLayout {
                        id: colorShapeLt
                        Label { text: "Num of colored shapes:"; Layout.fillWidth: true; }
                        Label { id: numColoredShapesId; text: "0"; }
                    }

                    RowLayout {
                        id: rcsPntCloudLt
                        Label { text: "Num of rcs point clouds:"; Layout.fillWidth: true; }
                        Label { id: numRcsPntCloudsId; text: "0"; }
                    }

                    RowLayout {
                        id: brepLt
                        Label { text: "Num of breps:"; Layout.fillWidth: true; }
                        Label { id: numBrepsId; text: "0"; }
                    }
                }
            }

            // Add geometry info staticstic
            GroupBox {
                id: geometryInfoGroup
                title: "Geometry info"
                Layout.fillWidth: true

                ColumnLayout {
                    anchors.fill: parent
                    RowLayout {
                        id: pointsLt
                        Label { text: "Num of points:"; Layout.fillWidth: true; }
                        Label { id: numPointsId; text: "0"; }
                    }
                    RowLayout {
                        id: facesLt
                        Label { text: "Num of faces:"; Layout.fillWidth: true; }
                        Label { id: numFacesId; text: "0"; }
                    }
                }
            }

        }

    }
}
