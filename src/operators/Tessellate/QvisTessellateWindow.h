// Copyright (c) Lawrence Livermore National Security, LLC and other VisIt
// Project developers.  See the top-level LICENSE file for dates and other
// details.  No copyright assignment is required to contribute to VisIt.

#ifndef QVISTESSELLATEWINDOW_H
#define QVISTESSELLATEWINDOW_H

#include <QvisOperatorWindow.h>
#include <AttributeSubject.h>

class TessellateAttributes;
class QLabel;
class QCheckBox;
class QLineEdit;

// ****************************************************************************
// Class: QvisTessellateWindow
//
// Purpose:
//    Defines QvisTessellateWindow class.
//
// Notes:      Autogenerated by xml2window.
//
// Programmer: xml2window
// Creation:   omitted
//
// Modifications:
//   
// ****************************************************************************

class QvisTessellateWindow : public QvisOperatorWindow
{
    Q_OBJECT
  public:
    QvisTessellateWindow(const int type,
                         TessellateAttributes *subj,
                         const QString &caption = QString::null,
                         const QString &shortName = QString::null,
                         QvisNotepadArea *notepad = 0);
    virtual ~QvisTessellateWindow();
    virtual void CreateWindowContents();
  protected:
    void UpdateWindow(bool doAll);
    virtual void GetCurrentValues(int which_widget);
  private slots:
    void chordErrorProcessText();
    void mergePointsChanged(bool val);
  private:
    QLineEdit *chordError;
    QCheckBox *mergePoints;
    QLabel *chordErrorLabel;

    TessellateAttributes *atts;
};



#endif
