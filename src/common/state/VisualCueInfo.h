// Copyright (c) Lawrence Livermore National Security, LLC and other VisIt
// Project developers.  See the top-level LICENSE file for dates and other
// details.  No copyright assignment is required to contribute to VisIt.

#ifndef VISUALCUEINFO_H
#define VISUALCUEINFO_H
#include <state_exports.h>
#include <string>
#include <AttributeSubject.h>

#include <ColorAttribute.h>
#include <PickAttributes.h>
#include <Line.h>

// ****************************************************************************
// Class: VisualCueInfo
//
// Purpose:
//    attributes necessary to describe a visual cue in a VisWindow (e.g. pick point or refline)
//
// Notes:      Autogenerated by xml2atts.
//
// Programmer: xml2atts
// Creation:   omitted
//
// Modifications:
//
// ****************************************************************************

class STATE_API VisualCueInfo : public AttributeSubject
{
public:
    enum CueType
    {
        PickPoint,
        RefLine,
        Unknown
    };

    // These constructors are for objects of this class
    VisualCueInfo();
    VisualCueInfo(const VisualCueInfo &obj);
protected:
    // These constructors are for objects derived from this class
    VisualCueInfo(private_tmfs_t tmfs);
    VisualCueInfo(const VisualCueInfo &obj, private_tmfs_t tmfs);
public:
    virtual ~VisualCueInfo();

    virtual VisualCueInfo& operator = (const VisualCueInfo &obj);
    virtual bool operator == (const VisualCueInfo &obj) const;
    virtual bool operator != (const VisualCueInfo &obj) const;
private:
    void Init();
    void Copy(const VisualCueInfo &obj);
public:

    virtual const std::string TypeName() const;
    virtual bool CopyAttributes(const AttributeGroup *);
    virtual AttributeSubject *CreateCompatible(const std::string &) const;
    virtual AttributeSubject *NewInstance(bool) const;

    // Property selection methods
    virtual void SelectAll();
    void SelectPoints();
    void SelectColor();
    void SelectGlyphType();
    void SelectLabel();
    void SelectHighlightColor();

    // Property setting methods
    void SetPoints(const doubleVector &points_);
    void SetCueType(CueType cueType_);
    void SetColor(const ColorAttribute &color_);
    void SetGlyphType(const std::string &glyphType_);
    void SetLabel(const std::string &label_);
    void SetShowLabel(bool showLabel_);
    void SetLineWidth(int lineWidth_);
    void SetOpacity(double opacity_);
    void SetHighlightColor(const float *highlightColor_);
    void SetShowHighlight(bool showHighlight_);

    // Property getting methods
    const doubleVector   &GetPoints() const;
          doubleVector   &GetPoints();
    CueType              GetCueType() const;
    const ColorAttribute &GetColor() const;
          ColorAttribute &GetColor();
    const std::string    &GetGlyphType() const;
          std::string    &GetGlyphType();
    const std::string    &GetLabel() const;
          std::string    &GetLabel();
    bool                 GetShowLabel() const;
    int                  GetLineWidth() const;
    double               GetOpacity() const;
    const float          *GetHighlightColor() const;
          float          *GetHighlightColor();
    bool                 GetShowHighlight() const;

    // Enum conversion functions
    static std::string CueType_ToString(CueType);
    static bool CueType_FromString(const std::string &, CueType &);
protected:
    static std::string CueType_ToString(int);
public:

    // Keyframing methods
    virtual std::string               GetFieldName(int index) const;
    virtual AttributeGroup::FieldType GetFieldType(int index) const;
    virtual std::string               GetFieldTypeName(int index) const;
    virtual bool                      FieldsEqual(int index, const AttributeGroup *rhs) const;

    // User-defined methods
    void SetPointF(int i, const float *pt);
    bool GetPointF(int i, float *pt) const;
    void SetFromP(const PickAttributes *pa);
    void SetFromL(const Line *line);
    void SetPointD(int i, const double *pt);
    bool GetPointD(int i, double *pt) const;

    // IDs that can be used to identify fields in case statements
    enum {
        ID_points = 0,
        ID_cueType,
        ID_color,
        ID_glyphType,
        ID_label,
        ID_showLabel,
        ID_lineWidth,
        ID_opacity,
        ID_highlightColor,
        ID_showHighlight,
        ID__LAST
    };

protected:
    bool           showHighlight;
private:
    doubleVector   points;
    int            cueType;
    ColorAttribute color;
    std::string    glyphType;
    std::string    label;
    bool           showLabel;
    int            lineWidth;
    double         opacity;
    float          highlightColor[3];

    // Static class format string for type map.
    static const char *TypeMapFormatString;
    static const private_tmfs_t TmfsStruct;
};
#define VISUALCUEINFO_TMFS "d*iassbidFb"

#endif
