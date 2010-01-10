/*****************************************************************************
*
* Copyright (c) 2000 - 2009, Lawrence Livermore National Security, LLC
* Produced at the Lawrence Livermore National Laboratory
* LLNL-CODE-400124
* All rights reserved.
*
* This file is  part of VisIt. For  details, see https://visit.llnl.gov/.  The
* full copyright notice is contained in the file COPYRIGHT located at the root
* of the VisIt distribution or at http://www.llnl.gov/visit/copyright.html.
*
* Redistribution  and  use  in  source  and  binary  forms,  with  or  without
* modification, are permitted provided that the following conditions are met:
*
*  - Redistributions of  source code must  retain the above  copyright notice,
*    this list of conditions and the disclaimer below.
*  - Redistributions in binary form must reproduce the above copyright notice,
*    this  list of  conditions  and  the  disclaimer (as noted below)  in  the
*    documentation and/or other materials provided with the distribution.
*  - Neither the name of  the LLNS/LLNL nor the names of  its contributors may
*    be used to endorse or promote products derived from this software without
*    specific prior written permission.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT  HOLDERS AND CONTRIBUTORS "AS IS"
* AND ANY EXPRESS OR  IMPLIED WARRANTIES, INCLUDING,  BUT NOT  LIMITED TO, THE
* IMPLIED WARRANTIES OF MERCHANTABILITY AND  FITNESS FOR A PARTICULAR  PURPOSE
* ARE  DISCLAIMED. IN  NO EVENT  SHALL LAWRENCE  LIVERMORE NATIONAL  SECURITY,
* LLC, THE  U.S.  DEPARTMENT OF  ENERGY  OR  CONTRIBUTORS BE  LIABLE  FOR  ANY
* DIRECT,  INDIRECT,   INCIDENTAL,   SPECIAL,   EXEMPLARY,  OR   CONSEQUENTIAL
* DAMAGES (INCLUDING, BUT NOT  LIMITED TO, PROCUREMENT OF  SUBSTITUTE GOODS OR
* SERVICES; LOSS OF  USE, DATA, OR PROFITS; OR  BUSINESS INTERRUPTION) HOWEVER
* CAUSED  AND  ON  ANY  THEORY  OF  LIABILITY,  WHETHER  IN  CONTRACT,  STRICT
* LIABILITY, OR TORT  (INCLUDING NEGLIGENCE OR OTHERWISE)  ARISING IN ANY  WAY
* OUT OF THE  USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH
* DAMAGE.
*
*****************************************************************************/

#ifndef PERSISTENTPARTICLESATTRIBUTES_H
#define PERSISTENTPARTICLESATTRIBUTES_H
#include <string>
#include <AttributeSubject.h>


// ****************************************************************************
// Class: PersistentParticlesAttributes
//
// Purpose:
//    This class contains attributes for the PersistentParticles operator.
//
// Notes:      Autogenerated by xml2atts.
//
// Programmer: xml2atts
// Creation:   omitted
//
// Modifications:
//   
// ****************************************************************************

class PersistentParticlesAttributes : public AttributeSubject
{
public:
    // These constructors are for objects of this class
    PersistentParticlesAttributes();
    PersistentParticlesAttributes(const PersistentParticlesAttributes &obj);
protected:
    // These constructors are for objects derived from this class
    PersistentParticlesAttributes(private_tmfs_t tmfs);
    PersistentParticlesAttributes(const PersistentParticlesAttributes &obj, private_tmfs_t tmfs);
public:
    virtual ~PersistentParticlesAttributes();

    virtual PersistentParticlesAttributes& operator = (const PersistentParticlesAttributes &obj);
    virtual bool operator == (const PersistentParticlesAttributes &obj) const;
    virtual bool operator != (const PersistentParticlesAttributes &obj) const;
private:
    void Init();
    void Copy(const PersistentParticlesAttributes &obj);
public:

    virtual const std::string TypeName() const;
    virtual bool CopyAttributes(const AttributeGroup *);
    virtual AttributeSubject *CreateCompatible(const std::string &) const;
    virtual AttributeSubject *NewInstance(bool) const;

    // Property selection methods
    virtual void SelectAll();
    void SelectTraceVariableX();
    void SelectTraceVariableY();
    void SelectTraceVariableZ();
    void SelectIndexVariable();

    // Property setting methods
    void SetStartIndex(int startIndex_);
    void SetStartIndexRelative(bool startIndexRelative_);
    void SetStopIndex(int stopIndex_);
    void SetStopIndexRelative(bool stopIndexRelative_);
    void SetStride(int stride_);
    void SetTraceVariableX(const std::string &traceVariableX_);
    void SetTraceVariableY(const std::string &traceVariableY_);
    void SetTraceVariableZ(const std::string &traceVariableZ_);
    void SetConnectParticles(bool connectParticles_);
    void SetIndexVariable(const std::string &indexVariable_);

    // Property getting methods
    int               GetStartIndex() const;
    bool              GetStartIndexRelative() const;
    int               GetStopIndex() const;
    bool              GetStopIndexRelative() const;
    int               GetStride() const;
    const std::string &GetTraceVariableX() const;
          std::string &GetTraceVariableX();
    const std::string &GetTraceVariableY() const;
          std::string &GetTraceVariableY();
    const std::string &GetTraceVariableZ() const;
          std::string &GetTraceVariableZ();
    bool              GetConnectParticles() const;
    const std::string &GetIndexVariable() const;
          std::string &GetIndexVariable();

    // Persistence methods
    virtual bool CreateNode(DataNode *node, bool completeSave, bool forceAdd);
    virtual void SetFromNode(DataNode *node);


    // Keyframing methods
    virtual std::string               GetFieldName(int index) const;
    virtual AttributeGroup::FieldType GetFieldType(int index) const;
    virtual std::string               GetFieldTypeName(int index) const;
    virtual bool                      FieldsEqual(int index, const AttributeGroup *rhs) const;


    // IDs that can be used to identify fields in case statements
    enum {
        ID_startIndex = 0,
        ID_startIndexRelative,
        ID_stopIndex,
        ID_stopIndexRelative,
        ID_stride,
        ID_traceVariableX,
        ID_traceVariableY,
        ID_traceVariableZ,
        ID_connectParticles,
        ID_indexVariable,
        ID__LAST
    };

private:
    int         startIndex;
    bool        startIndexRelative;
    int         stopIndex;
    bool        stopIndexRelative;
    int         stride;
    std::string traceVariableX;
    std::string traceVariableY;
    std::string traceVariableZ;
    bool        connectParticles;
    std::string indexVariable;

    // Static class format string for type map.
    static const char *TypeMapFormatString;
    static const private_tmfs_t TmfsStruct;
};
#define PERSISTENTPARTICLESATTRIBUTES_TMFS "ibibisssbs"

#endif
