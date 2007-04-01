#ifndef ISOVOLUMEATTRIBUTES_H
#define ISOVOLUMEATTRIBUTES_H
#include <string>
#include <AttributeSubject.h>

// ****************************************************************************
// Class: IsovolumeAttributes
//
// Purpose:
//    This class contains attributes for the isovolume operator.
//
// Notes:      Autogenerated by xml2atts.
//
// Programmer: xml2atts
// Creation:   Fri Jan 30 14:49:59 PST 2004
//
// Modifications:
//   
// ****************************************************************************

class IsovolumeAttributes : public AttributeSubject
{
public:
    IsovolumeAttributes();
    IsovolumeAttributes(const IsovolumeAttributes &obj);
    virtual ~IsovolumeAttributes();

    virtual void operator = (const IsovolumeAttributes &obj);
    virtual bool operator == (const IsovolumeAttributes &obj) const;
    virtual bool operator != (const IsovolumeAttributes &obj) const;

    virtual const std::string TypeName() const;
    virtual bool CopyAttributes(const AttributeGroup *);
    virtual AttributeSubject *CreateCompatible(const std::string &) const;
    virtual AttributeSubject *NewInstance(bool) const;

    // Property selection methods
    virtual void SelectAll();
    void SelectVariable();

    // Property setting methods
    void SetLbound(double lbound_);
    void SetUbound(double ubound_);
    void SetVariable(const std::string &variable_);

    // Property getting methods
    double            GetLbound() const;
    double            GetUbound() const;
    const std::string &GetVariable() const;
          std::string &GetVariable();

    // Persistence methods
    virtual bool CreateNode(DataNode *node, bool completeSave, bool forceAdd);
    virtual void SetFromNode(DataNode *node);


    // Keyframing methods
    virtual std::string               GetFieldName(int index) const;
    virtual AttributeGroup::FieldType GetFieldType(int index) const;
    virtual std::string               GetFieldTypeName(int index) const;
    virtual bool                      FieldsEqual(int index, const AttributeGroup *rhs) const;

private:
    double      lbound;
    double      ubound;
    std::string variable;
};

#endif
