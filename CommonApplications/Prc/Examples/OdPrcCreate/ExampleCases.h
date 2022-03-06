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

//              example name                      description                                                       called method   camera
ODPRCCREATECASE(BrepSphere,                       "sphere brep export example",                                     brepExample,    0.0276325, 0.645045, 0.763645, 0.166373, 0.750313, -0.639805, -0.985676, 0.144729, -0.0865853, 64.8751, -9.52578, 5.69886, 65.8179, 0.023094)
ODPRCCREATECASE(BrepBox,                          "box brep export example",                                        brepExample,    0.245895, -0.963371, -0.107014, 0.757045, 0.259823, -0.599479, 0.605325, 0.0663944, 0.793204, -43.0335, -4.72008, -56.3901, 71.0915, 0.0213809)
ODPRCCREATECASE(MeshBox,                          "box as mesh export example",                                     meshExample,    0.618335, -0.770955, 0.152614, -0.0108689, 0.185779, 0.982531, -0.78584, -0.609192, 0.106494, 3.08612, 2.50479, 0.149538, 1.268, 0.46188)
ODPRCCREATECASE(TriangleFan,                      "triangle fan export example",                                    meshExample,    -0.706769, -0.705836, 0.0476754, -0.70686, 0.707319, -0.0070385, -0.0287537, -0.0386744, -0.998838, 0.154523, 0.207837, 5.36776, 5.37401, 0.204284)
ODPRCCREATECASE(TriangleStripe,                   "triangle stripe export example",                                 meshExample,    -0.625145, 0.780156, 0.02347, 0.147076, 0.0882147, 0.985184, 0.766526, 0.619334, -0.169889, -4.04512, -3.07633, 2.11817, 6.58179, 0.137215)
ODPRCCREATECASE(TessCombination,                  "combination of triangle stripe and triangle fan example",        meshExample,    0.0000000000000000612323, -1.0, 0.00000000000000000000000000000000715595, 1.0, 0.0000000000000000612323, 0.000000000000000116866, -0.000000000000000116866, 0.0, 1.0, 0.000000000000000666134, 0.00000000000000000000000267189, -5.2, 5.7, 0.266667)
ODPRCCREATECASE(SingleWireBodyCrvLine,            "single wire body filled with CrvLine example",                   bodyExample,    -0.785259, -0.618972, -0.0155676, 0.496308, -0.614211, -0.613534, 0.370198, -0.489509, 0.789515, -0.203376, 0.930068, -1.50008, 1.9, 0.507289)
ODPRCCREATECASE(SingleWireBodyCrvNURBS,           "single wire body filled with CrvNURBS example",                  bodyExample,    0.0000000000000000612323, -1.0, 0.0, 1.0, 0.0000000000000000612323, 0.0, 0.0, 0.0, 1.0, 0.7, -0.0893555, -3.43798, 3.79774, 0.400238)
ODPRCCREATECASE(SingleWireBodyCrvCircle,          "single wire body filled with CrvCircle example",                 bodyExample,    0.0000000000000000612323, -1.0, 0.00000000000000000000000000000000759003, 1.0, 0.0000000000000000612323, 0.000000000000000123955, -0.000000000000000123955, 0.0, 1.0, 0.000000000000000666134, 0.00000000000000000000000267189, -5.37401, 5.37401, 0.282843)
ODPRCCREATECASE(SingleWireBodyCrvPolyLine,        "single wire body filled with CrvPolyLine example",               bodyExample,    -0.0152143, -0.882538, -0.469994, 0.999823, -0.00820549, -0.0169575, 0.0111091, -0.470169, 0.882507, 0.463441, 2.04728, -2.40424, 3.2909, 0.46188)
ODPRCCREATECASE(SingleWireBodyCrvHyperbola,       "single wire body filled with CrvHyperbola example",              bodyExample,    0.532466, -0.671237, -0.515675, 0.502887, 0.740907, -0.445153, 0.680871, -0.0222979, 0.732064, -29.0444, 0.951178, -26.466, 42.6577, 0.0198375)
ODPRCCREATECASE(SingleWireBodyCrvParabola,        "single wire body filled with CrvParabola example",               bodyExample,    0.0000000000000000612323, -1.0, 0.0, 1.0, 0.0000000000000000612323, 0.0, 0.0, 0.0, 1.0, 3.412, 0.00000000000000000000000424543, -18.0491, 18.0491, 0.0842148)
ODPRCCREATECASE(SingleWireBodyCrvEllipse,         "single wire body filled with CrvEllipse example",                bodyExample,    0.0000000000000000612323, -1.0, 0.00000000000000000000000000000000751698, 1.0, 0.0000000000000000612323, 0.000000000000000122762, -0.000000000000000122762, 0.0, 1.0, 0.00000000000000355271, 0.00000000000000000000000267189, -28.9399, 28.9399, 0.0525226)
ODPRCCREATECASE(SingleWireBodyCrvOnSurf,          "single wire body filled with CrvOnSurf example",                 bodyExample,    0.0198004, -0.999519, 0.0238635, 0.978368, 0.0144543, -0.206367, 0.205923, 0.0274334, 0.978184, -1.06509, -1.1326, -17.2361, 17.6205, 0.0862631)
ODPRCCREATECASE(SingleWireBodyCrvHelixT0,         "single wire body filled with CrvHelixT0 example",                bodyExample,    0.0000000000000000612323, -1.0, 0.0, 1.0, 0.0000000000000000612323, 0.0, 0.0, 0.0, 1.0, 1.49053, 6.31578, -70.289, 71.8028, 0.0211691)
ODPRCCREATECASE(SingleWireBodyCrvHelixT1,         "single wire body filled with CrvHelixT1 example",                bodyExample,    0.0000000000000000612323, -1.0, 0.0, 1.0, 0.0000000000000000612323, 0.0, 0.0, 0.0, 1.0, -1.14841, 1.0, -212.521, 212.521, 0.00715224)
ODPRCCREATECASE(SingleWireBodyCrvIntersection,    "single wire body filled with CrvIntersection example",           bodyExample,    0.0000000000000000612323, -1.0, 0.0, 1.0, 0.0000000000000000612323, 0.0, 0.0, 0.0, 1.0, 0.130395, 0.0482747, -0.153711, 0.0211527, 71.8584)
ODPRCCREATECASE(SingleWireBodyCrvBlend02Boundary, "single wire body filled with CrvBlend02Boundary example",        bodyExample,    -0.536965, -0.841779, -0.0554752, 0.304497, -0.13207, -0.943313, 0.786734, -0.523418, 0.327236, 0.121358, 0.0528108, 0.0269093, 0.0109118, 139.299)
ODPRCCREATECASE(SingleWireBodyCrvComposite,       "single wire body filled with CrvComposite example",              bodyExample,    0.0000000000000000612323, -1.0, 0.00000000000000000000000000000000751375, 1.0, 0.0000000000000000612323, 0.000000000000000122709, -0.000000000000000122709, 0.0, 1.0, 0.00000000000000233147, 0.00000000000000000000000267189, -19.0, 19.0, 0.08)
ODPRCCREATECASE(SingleWireBodyCrvTransform,       "single wire body filled with CrvTransform example",              bodyExample,    -0.148037, -0.931941, 0.331014, 0.908784, 0.0038429, 0.417249, -0.390123, 0.362589, 0.846365, 4.99167, -2.20994, -6.65984, 10.2318, 0.148556)
ODPRCCREATECASE(SingleWireBodyCrvOffset,          "single wire body filled with CrvOffset example",                 bodyExample,    0.0000000000000000612323, -1.0, 0.0, 1.0, 0.0000000000000000612323, 0.0, 0.0, 0.0, 1.0, 1.5, 1.5, -24.1831, 24.1831, 0.0628539)
ODPRCCREATECASE(SingleWireBodyCrvEquation,        "single wire body filled with CrvEquation example",               bodyExample,    0.0000000000000000612323, -1.0, 0.0000000000000000000000000000000075744, 1.0, 0.0000000000000000612323, 0.000000000000000123699, -0.000000000000000123699, 0.0, 1.0, 0.00000000000000244249, 0.00000000000000000000000267189, -19.7454, 19.7454, 0.07698)
ODPRCCREATECASE(SingleWireBodyCrvPolyLine2d,      "single wire body filled with CrvPolyLine2d example",             bodyExample,    0.0153657, -0.995899, 0.0891578, 0.999865, 0.0158261, 0.00445931, -0.00585204, 0.0890773, 0.996008, 2.0712, -1.58371, -12.1174, 12.1659, 0.124939)
ODPRCCREATECASE(SingleWireBodyCrvEquation2d,      "single wire body filled with CrvEquation2d example",             bodyExample,    0.0000000000000000612323, -1.0, 0.00000000000000000000000000000000736342, 1.0, 0.0000000000000000612323, 0.000000000000000120254, -0.000000000000000120254, 0.0, 1.0, 0.00000000000000266454, 0.00000000000000000000000267189, -22.1576, 22.1576, 0.0685994)
ODPRCCREATECASE(SingleWireBodyCrvNURBS2d,         "single wire body filled with CrvNURBS2d example",                bodyExample,    0.0000000000000000612323, -1.0, 0.00000000000000000000000000000000781733, 1.0, 0.0000000000000000612323, 0.000000000000000127667, -0.000000000000000127667, 0.0, 1.0, 0.00000000000000111022, -0.125122, -8.69626, 8.69626, 0.174788)
ODPRCCREATECASE(SingleWireBodyCrvComposite2d,     "single wire body filled with CrvComposite2d example",            bodyExample,    0.0000000000000000612323, -1.0, 0.00000000000000000000000000000000726643, 1.0, 0.0000000000000000612323, 0.00000000000000011867, -0.00000000000000011867, 0.0, 1.0, 0.00000000000000122125, -1.24976, -9.35557, 9.35557, 0.133656)
ODPRCCREATECASE(SingleWireBodyCrvTransform2d,     "single wire body filled with CrvTransform2d example",            bodyExample,    0.0000000000000000612323, -1.0, 0.0, 1.0, 0.0000000000000000612323, 0.0, 0.0, 0.0, 1.0, 0.00195312, 4.49805, -28.9245, 28.9245, 0.0379548)
ODPRCCREATECASE(SingleWireBodyCrvLine2d,          "single wire body filled with CrvLine2d example",                 bodyExample,    -0.785259, -0.618972, -0.0155676, 0.496308, -0.614211, -0.613534, 0.370198, -0.489509, 0.789515, -0.203376, 0.930068, -1.50008, 1.9, 0.507289)
ODPRCCREATECASE(SingleWireBodyCrvCircle2d,        "single wire body filled with CrvCircle2d example",               bodyExample,    0.0000000000000000612323, -1.0, 0.00000000000000000000000000000000759003, 1.0, 0.0000000000000000612323, 0.000000000000000123955, -0.000000000000000123955, 0.0, 1.0, 0.000000000000000666134, 0.00000000000000000000000267189, -5.37401, 5.37401, 0.282843)
ODPRCCREATECASE(SingleWireBodyCrvHyperbola2d,     "single wire body filled with CrvHyperbola2d example",            bodyExample,    0.532466, -0.671237, -0.515675, 0.502887, 0.740907, -0.445153, 0.680871, -0.0222979, 0.732064, -29.0444, 0.951178, -26.466, 42.6577, 0.0198375)
ODPRCCREATECASE(SingleWireBodyCrvParabola2d,      "single wire body filled with CrvParabola2d example",             bodyExample,    0.0000000000000000612323, -1.0, 0.0, 1.0, 0.0000000000000000612323, 0.0, 0.0, 0.0, 1.0, 3.412, 0.00000000000000000000000424543, -18.0491, 18.0491, 0.0842148)
ODPRCCREATECASE(SingleWireBodyCrvEllipse2d,       "single wire body filled with CrvEllipse2d example",              bodyExample,    0.0000000000000000612323, -1.0, 0.00000000000000000000000000000000751698, 1.0, 0.0000000000000000612323, 0.000000000000000122762, -0.000000000000000122762, 0.0, 1.0, 0.00000000000000355271, 0.00000000000000000000000267189, -28.9399, 28.9399, 0.0525226)
ODPRCCREATECASE(AllSingleWireBodies,              "single wire body filled with all curves example",                CreateAllSingleWireBodies,    0.983145, 0.0094194, -0.182585, 0.0288112, 0.978211, 0.205602, 0.180543, -0.207397, 0.961452, -365.956, 16.5851, -1192.88, 1244.63, 0.00122126)
ODPRCCREATECASE(BrepModelSphere,                  "brep model filled with srfSphere example",                       brepModelExample,    1.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, -6.58179, 6.58179, 0.23094)
ODPRCCREATECASE(BrepModelCylinder,                "brep model filled with srfCylinder example",                     brepModelExample,    0.0734328, -0.0669857, 0.995048, 0.72704, 0.686555, -0.00743612, -0.682657, 0.723986, 0.0991169, 5.48294, -5.81489, -0.796084, 8.03177, 0.166153)
ODPRCCREATECASE(BrepModelCone,                    "brep model filled with srfCone example",                         brepModelExample,    0.999986, 0.00211576, 0.00478651, -0.00438121, 0.838691, 0.54459, -0.00286218, -0.544603, 0.838689, 0.0225832, 3.03402, -7.7275, 7.8902, 0.169134)
ODPRCCREATECASE(BrepModelRuled,                   "brep model filled with srfRuled example",                        brepModelExample,    -0.0371373, 0.999202, -0.0146917, -0.875683, -0.0254562, 0.482215, 0.481456, 0.0307735, 0.87593, -10.2273, -0.825026, -23.4834, 26.8097, 0.0409488)
ODPRCCREATECASE(BrepModelExtrusion,               "brep model filled with srfExtrusion example",                    brepModelExample,    0.479111, 0.10968, 0.870875, -0.297912, 0.953588, 0.0437991, -0.825652, -0.280428, 0.48955, 22.7328, 6.32245, -6.78679, 24.1079, 0.0426689)
ODPRCCREATECASE(BrepModelFromCurves,              "brep model filled with srfFromCurves example",                   brepModelExample,    0.695627, -0.664666, 0.272622, 0.687214, 0.505052, -0.522168, 0.209379, 0.550583, 0.808096, -0.305358, -4.04788, -6.38135, 7.18964, 0.1177)
ODPRCCREATECASE(BrepModelRevolution,              "brep model filled with srfRevolution example",                   brepModelExample,    -0.202793, -0.281765, -0.937808, 0.976957, 0.00688069, -0.213325, 0.0665604, -0.959459, 0.273877, 0.244577, 4.10284, -1.28118, 3.83747, 0.305317)
ODPRCCREATECASE(BrepModelCylindrical,             "brep model filled with srfCylindrical example",                  brepModelExample,    0.985915, 0.164912, 0.0278533, -0.0673854, 0.54411, -0.836304, -0.153072, 0.822647, 0.547559, 0.703449, -3.78052, -2.01634, 4.59556, 0.238888)
ODPRCCREATECASE(BrepModelNURBS,                   "brep model filled with srfNURBS example",                        brepModelExample,    -0.191694, -0.741762, -0.642684, 0.963011, -0.268507, 0.0226625, -0.189376, -0.614568, 0.765796, 4.98578, 20.384, -29.8915, 32.5041, 0.0467634)
ODPRCCREATECASE(BrepModelTorusT1,                 "brep model filled with srfTorusT1 example",                      brepModelExample,    0.0636954, -0.902, -0.427011, 0.992813, 0.0138329, 0.118874, -0.101317, -0.431513, 0.896399, 0.69719, 2.96935, -6.16834, 6.88124, 0.22089)
ODPRCCREATECASE(BrepModelTorusT2,                 "brep model filled with srfTorusT2 example",                      brepModelExample,    0.750754, -0.408218, -0.519352, 0.0219443, 0.801182, -0.598018, 0.660218, 0.437567, 0.610448, -2.22469, -1.47444, -2.05698, 3.36963, 0.451088)
ODPRCCREATECASE(BrepModelOffset,                  "brep model filled with srfOffset example",                       brepModelExample,    -0.991183, 0.0725669, -0.110859, 0.03488, -0.664267, -0.746681, -0.127824, -0.743964, 0.655879, 2.38081, 6.73161, -7.57279, 14.8007, 0.102698)
ODPRCCREATECASE(BrepModelTransform,               "brep model filled with srfTransform example",                    brepModelExample,    -0.0456931, -0.382938, -0.922643, 0.672177, 0.671455, -0.311972, 0.738979, -0.634435, 0.226721, -7.66507, 6.72547, -2.58842, 10.9332, 0.0881578)
ODPRCCREATECASE(BrepModelPlane,                   "brep model filled with srfPlane example",                        brepModelExample,    0.0000000000000000612323, -1.0, 0.0, 1.0, 0.0000000000000000612323, 0.0, 0.0, 0.0, 1.0, 1.0, -0.464627, -4.43325, 4.24853, 0.357771)
ODPRCCREATECASE(BrepModelBlend01,                 "brep model filled with srfBlend01 example",                      brepModelExample,    0.0000000000000000612323, -1.0, 0.0, 1.0, 0.0000000000000000612323, 0.0, 0.0, 0.0, 1.0, 0.506189, 0.301218, -3.24174, 3.92411, 0.387349)
ODPRCCREATECASE(BrepModelBlend02,                 "brep model filled with srfBlend02 example",                      brepModelExample,    -0.552186, 0.197079, -0.810093, 0.809177, 0.360716, -0.463807, 0.200807, -0.911616, -0.358654, -2.12841, -38.5655, 39.813, 16.021, 0.0731315)
ODPRCCREATECASE(BrepModelBlend03,                 "brep model filled with srfBlend03 example",                      brepModelExample,    0.31887, 0.386179, -0.865557, 0.738051, 0.471785, 0.482389, 0.594645, -0.792644, -0.134582, -12.3579, -8831.98, 5466.47, 21.4419, 0.0708871)
ODPRCCREATECASE(AllBrepModelExamples,             "brep model filled with all surface example",                     CreateAllBrepModelExamples,    0.983133, 0.00900139, -0.182672, 0.0292313, 0.978215, 0.205524, 0.180543, -0.207397, 0.961452, -105488.0, 15969.8, -349423.0, 365911.0, 0.00000415402)
ODPRCCREATECASE(PlainTextMarkup,                  "markup example with plain text type",                            markupExample,    -1.0, 0.0, -0.000000000000000122465, 0.0, 1.0, 0.0, 0.000000000000000122465, 0.0, -1.0, 1.0, 12.5, 3.5, 49.3269, 0.0131891)
ODPRCCREATECASE(DistanceDimensionMarkup,          "markup example with distance dimension type",                    markupExample,    -1.0, 0.0, -0.000000000000000122465, 0.0, 1.0, 0.0, 0.000000000000000122465, 0.0, -1.0, 1.0, 4.5, 1.45875, 17.976, 0.0413301)
ODPRCCREATECASE(DimensionRadiusMarkup,            "markup example with dimension radius type",                      markupExample,    -1.0, 0.0, -0.000000000000000122465, 0.0, 1.0, 0.0, 0.000000000000000122465, 0.0, -1.0, 4.66225, 0.942394, 0.91078, 17.3073, 0.0455533)
ODPRCCREATECASE(DiameterDimensionMarkup,          "markup example with diameter dimension type",                    markupExample,    -1.0, 0.0, -0.000000000000000122465, 0.0, 1.0, 0.0, 0.000000000000000122465, 0.0, -1.0, 4.43675, -0.127438, 0.717948, 19.2526, 0.043729)
ODPRCCREATECASE(TangentDiameterDimensionMarkup,   "markup example with tangent diameter dimension type",            markupExample,    -1.0, 0.0, -0.000000000000000122465, 0.0, 1.0, 0.0, 0.000000000000000122465, 0.0, -1.0, 6.59882, 0.0934136, 1.35, 27.329, 0.0456764)
ODPRCCREATECASE(CylinderDiameterDimensionMarkup,  "markup example with cylinder diameter dimension type",           markupExample,    -1.0, 0.0, -0.000000000000000122465, 0.0, 1.0, 0.0, 0.000000000000000122465, 0.0, -1.0, 3.44783, 1.37145, 2.21795, 15.7456, 0.0411207)
ODPRCCREATECASE(LengthDimensionMarkup,            "markup example with length dimension type",                      markupExample,    -1.0, 0.0, -0.000000000000000122465, 0.0, 1.0, 0.0, 0.000000000000000122465, 0.0, -1.0, 6.25181, 1.2331, 2.11795, 24.8637, 0.0470154)
ODPRCCREATECASE(AngleDimensionMarkup,             "markup example with angle dimension type",                       markupExample,    0.99979, 0.0193662, 0.00672469, 0.0204012, -0.907636, -0.419263, -0.00201597, 0.419312, -0.90784, -0.148443, -14.0763, 26.6431, 31.7759, 0.0575617)
ODPRCCREATECASE(DatumIdentifierMarkup,            "markup example with datum identifier type",                      markupExample,    -1.0, 0.0, -0.000000000000000122465, 0.0, 1.0, 0.0, 0.000000000000000122465, 0.0, -1.0, 2.91089, 2.05616, 2.0, 10.748, 0.108762)
ODPRCCREATECASE(DatumTargetMarkup,                "markup example with datum target type",                          markupExample,    -1.0, 0.0, -0.000000000000000122465, 0.0, 1.0, 0.0, 0.000000000000000122465, 0.0, -1.0, 1.0, 2.0, 2.24987, 12.921, 0.0796113)
ODPRCCREATECASE(GDTMarkup,                        "markup example with geometric dimensioning and tolerance type",  markupExample,    -1.0, 0.0, -0.000000000000000122465, 0.0, 1.0, 0.0, 0.000000000000000122465, 0.0, -1.0, 15.5917, -1.32816, 4.0, 59.9931, 0.0170878)
ODPRCCREATECASE(RoughnessMarkup,                  "markup example with roughness type",                             markupExample,    -0.963844, 0.0126802, -0.266164, 0.0203221, 0.999456, -0.0259765, 0.26569, -0.0304463, -0.963578, -176.214, 24.0348, 667.522, 698.669, 0.0829961)
ODPRCCREATECASE(TableMarkup,                      "markup example with table type",                                 markupExample,    -1.0, 0.0, -0.000000000000000122465, 0.0, 1.0, 0.0, 0.000000000000000122465, 0.0, -1.0, 10.407, -0.142571, 1.75752, 38.0262, 0.023642)
ODPRCCREATECASE(AllMarkupExamples,                "markup example with some types",                                 CreateAllMarkupExamples,    -0.997336, -0.000245384, -0.0729446, 0.00540691, 0.996995, -0.0772799, 0.0727444, -0.0774684, -0.994337, 72.4655, -59.0542, 154.853, 170.66, 0.0032778)
ODPRCCREATECASE(CreateComplexExample,             "example with complex topology",                                  CreateComplexExample,    -0.420943, -0.373271, 0.826726, 0.787888, -0.602086, 0.129323, 0.449488, 0.705805, 0.54754, -5.86125, -10.7738, -8.35798, 15.8987, 0.0211404)
ODPRCCREATECASE(MarkupViewExample,                "view example with brep cylinder and markups",                    markupViewExample,    -0.89601, -0.00520776, -0.444003, 0.00819989, 0.999567, -0.0282717, 0.443957, -0.0289725, -0.895579, -20.6076, 5.89136, 45.0441, 45.3382, 0.0548721)
ODPRCCREATECASE(BrepModelConeWithLoops,           "brep model filled with srfCone example With Loops",              brepModelExample,    -0.769835, -0.600464, 0.216328, -0.527719, 0.789484, 0.313412, -0.358981, 0.127115, -0.924648, 0.0123467, 0.0136679, 0.0261193, 0.0107546, 60.6508)
ODPRCCREATECASE(MarkupAnnotationExample,          "annotation example",                                             markupAnnotationExample,    -1.0, 0.0, 0.0, 0.0, 1, 0.214109, 0.0, 0.21361, -1.0, 1.81272, -1.15731, 7.16287, 7.33952, 0.121796)
ODPRCCREATECASE(RepresentationItemPolyWire,       "representation item polyWire example",                           representationItemExample,    -1.0, 0.0, 0.0, 0.0, 1, 0.0, 0.0, 0.0, -1.0, 1.94096, 1.75554, 7.16287, 7.33952, 0.090674)
ODPRCCREATECASE(RepresentationItemPointSet,       "representation item pointSet example",                           representationItemExample,    0.165917, 0.0907678, 0.981954, -0.557587, -0.812664, 0.169333, 0.813368, -0.57562, -0.0842236, -160.601, 113.657, 16.6301, 197.452, 0.0116382)
ODPRCCREATECASE(RepresentationItemPolyBrepModel,  "representation item polyBrepModel example",                      representationItemExample,    -1.0, 0.0, 0.0, 0.0, 1, 0.0, 0.0, 0.0, -1.0, 2.03256, 0.67467, 7.16287, 7.33952, 0.16489)
ODPRCCREATECASE(RepresentationItemSet,            "representation item with all RI type example",                   representationItemExample,    -1.0, 0.0, 0.0, 0.0, 1, 0.0, 0.0, 0.0, -1.0, 1.90432, 1.82882, 7.16287, 7.33952, 0.16489)
ODPRCCREATECASE(TessObjectTexture,                "textured polyBrepModel textured example",                        tessObjectTextureExample,    -1.0, 0.0, 0.0, 0.0, 1, 0.0, 0.0, 0.0, -1.0, 2.03256, 0.67467, 7.16287, 7.33952, 0.16489)
ODPRCCREATECASE(BrepObjectMaterial,               "brep with material model filled with srfPlane example",          brepModelExample,    0.0000000000000000612323, -1.0, 0.0, 1.0, 0.0000000000000000612323, 0.0, 0.0, 0.0, 1.0, 1.0, -0.464627, -4.43325, 4.24853, 0.357771)
ODPRCCREATECASE(WireTessWithFlags,                "3d polywire with flags",                                         representationItemExample,    -1.0, 0.0, 0.0, 0.0, 1, 0.0, 0.0, 0.0, -1.0, 1.94096, 1.75554, 7.16287, 7.33952, 0.090674)
ODPRCCREATECASE(BoxByVerticesExample,             "brep box example generated by list of vertices",                 brepByVerticesExample,    -0.946595, -0.322379, -0.00547274, -0.104743, 0.291412, 0.950846, -0.304938, 0.900639, -0.309616, 30.0704, -49.2782, 30.3783, 65.8179, 0.023094)
ODPRCCREATECASE(PyramidByVerticesExample,         "brep pyramid example generated by list of vertices",             brepByVerticesExample,    -0.961338, -0.262211, 0.0841048, 0.173431, -0.339293, 0.924555, -0.213893, 0.903396, 0.371651, 25.3411, -54.7947, -14.1561, 71.7234, 0.0211925)
ODPRCCREATECASE(TqsSolidByVerticesExample,        "some brep solid example generated by list of vertices",          brepByVerticesExample, -0.946595, -0.322377, -0.00546703, -0.104737, 0.291414, 0.950846, -0.304938, 0.900639, -0.309616, 337.122, -500.345, 365.76, 777.609, 0.00195471)
ODPRCCREATECASE(ManyTqsSolidByVerticesExample,    "many brep solids example generated by list of vertices",         manyBrepByVerticesExample, 0.0500184, -0.998702, 0.00960556, -0.0797079, 0.00559525, 0.996803, -0.995563, -0.0506241, -0.0793246, 156785.0, 14464.3, 10066.0, 125321.0, 0.0000346714)
ODPRCCREATECASE(TessExample2,                     "many boxes as one prc tess per box export example",              createTessExampleMultiTess, -0.885632, -0.422443, 0.192867, -0.187322, 0.705004, 0.684018, -0.424931, 0.56966, -0.703507, 170.899, -116.871, 267.709, 379.824, 0.00676608)
ODPRCCREATECASE(TessExample1,                     "many boxes as single prc tess export example",                   createTessExampleSingleTess,    -0.885632, -0.422443, 0.192867, -0.187322, 0.705004, 0.684018, -0.424931, 0.56966, -0.703507, 170.899, -116.871, 267.709, 379.824, 0.00676608)
// ODPRCCREATECASE(AttributeInt,                     "create sphere and write integer attribute in it",                attributeExample, 0.0276325, 0.645045, 0.763645, 0.166373, 0.750313, -0.639805, -0.985676, 0.144729, -0.0865853, 64.8751, -9.52578, 5.69886, 65.8179, 0.023094)
// ODPRCCREATECASE(AttributeTimeStamp,               "create sphere and write time stamp attribute in it",             attributeExample, 0.0276325, 0.645045, 0.763645, 0.166373, 0.750313, -0.639805, -0.985676, 0.144729, -0.0865853, 64.8751, -9.52578, 5.69886, 65.8179, 0.023094)
// ODPRCCREATECASE(AttributeString,                  "create sphere and write string attribute in it",                 attributeExample, 0.0276325, 0.645045, 0.763645, 0.166373, 0.750313, -0.639805, -0.985676, 0.144729, -0.0865853, 64.8751, -9.52578, 5.69886, 65.8179, 0.023094)
// ODPRCCREATECASE(AttributeDouble,                  "create sphere and write double attribute in it",                 attributeExample, 0.0276325, 0.645045, 0.763645, 0.166373, 0.750313, -0.639805, -0.985676, 0.144729, -0.0865853, 64.8751, -9.52578, 5.69886, 65.8179, 0.023094)
ODPRCCREATECASE(AttributeToRepresentationItem,    "create sphere and write attributes in it",                       attributeExample, 0.0276325, 0.645045, 0.763645, 0.166373, 0.750313, -0.639805, -0.985676, 0.144729, -0.0865853, 64.8751, -9.52578, 5.69886, 65.8179, 0.023094)
ODPRCCREATECASE(AttributeToPartDefinition,        "create sphere and write attributes in it",                       attributeExample, 0.0276325, 0.645045, 0.763645, 0.166373, 0.750313, -0.639805, -0.985676, 0.144729, -0.0865853, 64.8751, -9.52578, 5.69886, 65.8179, 0.023094)
ODPRCCREATECASE(AttributeToProductOccurrence,     "create sphere and write attributes in it",                       attributeExample, 0.0276325, 0.645045, 0.763645, 0.166373, 0.750313, -0.639805, -0.985676, 0.144729, -0.0865853, 64.8751, -9.52578, 5.69886, 65.8179, 0.023094)
ODPRCCREATECASE(TessExample3,                     "textured box example",                                           tessExampleTextured, 0.618335, -0.770955, 0.152614, -0.0108689, 0.185779, 0.982531, -0.78584, -0.609192, 0.106494, 3.08612, 2.50479, 0.149538, 1.268, 0.46188)
ODPRCCREATECASE(SimpleSection,                    "cone with cross section example",                                simpleCrossSectioExample,    0.0276325, 0.645045, 0.763645, 0.166373, 0.750313, -0.639805, -0.985676, 0.144729, -0.0865853, 64.8751, -9.52578, 5.69886, 65.8179, 0.023094)
ODPRCCREATECASE(MarkupViewWithFilteringExample,   "view example with filtering objects",                            markupViewWithFilteringExample,    -0.427792, 0.903807, -0.0112487, 0.180159, 0.0974551, 0.978798, 0.885741, 0.416696, -0.204519, -19.8169, -6.94785, 3.71012, 22.3733, 0.0679382)
ODPRCCREATECASE(BackgroundExample,                "cone with background example",                                   viewWithBackgroundExample, 0.0276325, 0.645045, 0.763645, 0.166373, 0.750313, -0.639805, -0.985676, 0.144729, -0.0865853, 64.8751, -9.52578, 5.69886, 65.8179, 0.023094)
ODPRCCREATECASE(MultipleEntitiesExportExample,    "multiple entities export example",                               multipleEntitiesExportExample,    0.0276325, 0.645045, 0.763645, 0.166373, 0.750313, -0.639805, -0.985676, 0.144729, -0.0865853, 64.8751, -9.52578, 5.69886, 65.8179, 0.023094)
ODPRCCREATECASE(CloneConnexesFromComplexExample,  "example with cloning Connexes from complex example",             cloneConnexesFromComplexExample, -0.420943, -0.373271, 0.826726, 0.787888, -0.602086, 0.129323, 0.449488, 0.705805, 0.54754, -5.86125, -10.7738, -8.35798, 15.8987, 0.0211404)
ODPRCCREATECASE(explodeExample,                   "example with splitting Connexes to set of faces example",        explodeExample, -0.420943, -0.373271, 0.826726, 0.787888, -0.602086, 0.129323, 0.449488, 0.705805, 0.54754, -5.86125, -10.7738, -8.35798, 15.8987, 0.0211404)

#undef ODPRCCREATECASE