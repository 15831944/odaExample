#ifndef RO_VAR_DEF
#define RO_VAR_DEF  VAR_DEF /* {Secret} */
#define DOUNDEF_RO_VAR_DEF
#endif

#ifndef RO_VAR_DEF_H
#define RO_VAR_DEF_H  RO_VAR_DEF /* {Secret} */
#define DOUNDEF_RO_VAR_DEF_H
#endif

#ifndef VAR_DEF_H
#define VAR_DEF_H  VAR_DEF /* {Secret} */
#define DOUNDEF_VAR_DEF_H
#endif

#ifndef DICR15VAR
#define DOUNDEF_DICR15VAR
#define DICR15VAR  VAR_DEF /* {Secret} */
#endif

#ifndef DICR21VAR
#define DOUNDEF_DICR21VAR
#define DICR21VAR  VAR_DEF /* {Secret} */
#define DOUNDEF_DICR21VAR_H
#define DICR21VAR_H VAR_DEF_H /* {Secret} */
#else
#define DOUNDEF_DICR21VAR_H
#define DICR21VAR_H DICR21VAR /* {Secret} */
#endif

#ifndef DICR24VAR
#define DOUNDEF_DICR24VAR
#define DICR24VAR  DICR21VAR /* {Secret} */
#define DOUNDEF_DICR24VAR_H
#define DICR24VAR_H DICR21VAR_H /* {Secret} */
#else
#define DOUNDEF_DICR24VAR_H
#define DICR24VAR_H DICR24VAR /* {Secret} */
#endif

#ifndef DICR27VAR
#define DOUNDEF_DICR27VAR
#define DICR27VAR DICR21VAR /* {Secret} */
#define DOUNDEF_DICR27VAR_H
#define DICR27VAR_H DICR21VAR_H /* {Secret} */
#else
#define DOUNDEF_DICR27VAR_H
#define DICR27VAR_H DICR27VAR /* {Secret} */
#endif

#ifndef ANNO_VAR_DEF
#define DOUNDEF_ANNO_VAR_DEF
#define ANNO_VAR_DEF DICR21VAR  /* {Secret} */
#endif

#ifndef MLEADERSTYLE_VAR_DEF
#define DOUNDEF_MLEADERSTYLE_VAR_DEF
#define MLEADERSTYLE_VAR_DEF DICR21VAR  /* {Secret} */
#endif

#ifndef VAR_DEF_2
#define DOUNDEF_VAR_DEF_2
#define VAR_DEF_2  VAR_DEF /* {Secret} */
#endif

#ifndef ODTBOOL
#define ODTBOOL                 bool                    /* {Secret} */
#endif

#ifndef ODTDIST
#define ODTDIST                 double                  /* {Secret} */
#endif

#ifndef ODTORIENT
#define ODTORIENT               double                  /* {Secret} */
#endif

#ifndef ODTUNITLESS4
#define ODTUNITLESS4            double                  /* {Secret} */
#endif

#ifndef ODTUNITLESS8
#define ODTUNITLESS8            double                  /* {Secret} */
#endif

#ifndef ODTDB_MEASUREMENTVALUE
#define ODTDB_MEASUREMENTVALUE  OdDb::MeasurementValue  /* {Secret} */
#endif

#ifndef ODTDB_LINEWEIGHT
#define ODTDB_LINEWEIGHT        OdDb::LineWeight        /* {Secret} */
#endif

#ifndef ODTDB_JOINSTYLE
#define ODTDB_JOINSTYLE         OdDb::JoinStyle         /* {Secret} */
#endif

#ifndef ODTDB_UNITSVALUE
#define ODTDB_UNITSVALUE        OdDb::UnitsValue        /* {Secret} */
#endif

#ifndef ODTDB_PROXYIMAGE
#define ODTDB_PROXYIMAGE        OdDb::ProxyImage        /* {Secret} */
#endif

#ifndef ODTDB_MEASUREMENTVALUE
#define ODTDB_MEASUREMENTVALUE  OdDb::MeasurementValue  /* {Secret} */
#endif

#ifndef ODTDB_ENDCAPS
#define ODTDB_ENDCAPS           OdDb::EndCaps           /* {Secret} */
#endif

#ifndef ODTDB_JOINSTYLE
#define ODTDB_JOINSTYLE         OdDb::JoinStyle         /* {Secret} */
#endif

#ifndef ODTDB_PLOTSTYLENAMETYPE
#define ODTDB_PLOTSTYLENAMETYPE OdDb::PlotStyleNameType /* {Secret} */
#endif

#ifndef ODDBOBJECTID
#define ODDBOBJECTID            OdDbObjectId            /* {Secret} */
#endif

#ifndef ODDBHARDPOINTERID
#define ODDBHARDPOINTERID       ODDBOBJECTID            /* {Secret} */
#endif

#ifndef ODTTEXTSTYLEID
#define ODTTEXTSTYLEID          ODDBOBJECTID            /* {Secret} */
#endif

#ifndef ODTLAYERID
#define ODTLAYERID              ODDBOBJECTID            /* {Secret} */
#endif

#ifndef ODTLAYERIDDEF
#define ODTLAYERIDDEF           ODTLAYERID              /* {Secret} */
#endif

#ifndef ODTLINETYPEID
#define ODTLINETYPEID           ODDBOBJECTID            /* {Secret} */
#endif

#ifndef ODTDIMSTYLEID
#define ODTDIMSTYLEID           ODDBOBJECTID            /* {Secret} */
#endif

#ifndef ODTUCSID
#define ODTUCSID                ODDBOBJECTID            /* {Secret} */
#endif

#ifndef ODTMLSTYLEID
#define ODTMLSTYLEID            ODDBOBJECTID            /* {Secret} */
#endif

#ifndef ODTDB_TIMEZONE
#define ODTDB_TIMEZONE          OdDb::TimeZone         /* {Secret} */
#endif

#ifndef ODTDB_SHADOWFLAGS
#define ODTDB_SHADOWFLAGS       OdGiSubEntityTraits::ShadowFlags      /* {Secret} */
#endif

#ifndef ODVISTYLEID
#define ODVISTYLEID             ODDBOBJECTID            /* {Secret} */
#endif

#ifndef ODTMATERIALID
#define ODTMATERIALID           ODDBOBJECTID            /* {Secret} */
#endif

#ifndef ODTDB_LOFTPARAMTYPE
#define ODTDB_LOFTPARAMTYPE     OdDb::LoftParamType      /* {Secret} */
#endif

#ifndef ODTDB_LOFTNORMALSTYPE
#define ODTDB_LOFTNORMALSTYPE   OdDb::LoftNormalsType      /* {Secret} */
#endif

#ifndef ODTTABLESTYLEID
#define ODTTABLESTYLEID         ODDBOBJECTID            /* {Secret} */
#endif

#ifndef ODTMLEADERSTYLEID
#define ODTMLEADERSTYLEID       ODDBOBJECTID            /* {Secret} */
#endif

#ifndef ODTVIEWDETAILSTYLEID
#define ODTVIEWDETAILSTYLEID    ODDBOBJECTID            /* {Secret} */
#endif

#ifndef ODTVIEWSECTIONSTYLEID
#define ODTVIEWSECTIONSTYLEID   ODDBOBJECTID            /* {Secret} */
#endif

#ifndef ODANNOSCALE
#define ODANNOSCALE             OdDbAnnotationScalePtr /* {Secret} */
#endif

#ifndef ODTTRANSPARENCYDEF
#define ODTTRANSPARENCYDEF OdCmTransparency
#endif

#ifndef ODTCOLORDEF
#define ODTCOLORDEF OdCmColor
#endif

#define SVARS_FUNC_MODIFIER virtual
