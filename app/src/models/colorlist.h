#ifndef COLORLIST_H
#define COLORLIST_H

#include <QPointer>
#include <QMap>

#include "scribusapi.h"
#include "sccolor.h"

//class  ScribusDoc;

class SCRIBUS_API ColorList : public QMap<QString, ScColor>
{
public:
    ColorList(/*ScribusDoc* doc = nullptr,*/ bool retainDoc = false);

    ColorList& operator= (const ColorList& list);

    /** \brief Get the document the list is related , return in cpp due to scribusdoc class delcaration */
//    ScribusDoc* document() const;

    /** \brief Assign the doc to which the list belong to.*/
 //   void setDocument(ScribusDoc* doc);

    /** \brief Add colors from the specified list. Colors are added using shadow copy.*/
    void addColors(const ColorList& colorList, bool overwrite = true);

    /** \brief Copy colors from the specified list.*/
    void copyColors(const ColorList& colorList, bool overwrite = true);

    /** \brief Ensure availability of black and white colors. */
    void ensureDefaultColors();

    /** \brief Try to add ScColor col to the list, if col already exists either by name or by value the existing color name is returned. */
    QString tryAddColor(QString name, const ScColor& col);

protected:
//    QPointer<ScribusDoc> m_doc;
    bool m_retainDoc { false };

    /** \brief Ensure availability of black color. */
    void ensureBlack();

    /** \brief Ensure availability of white color. */
    void ensureWhite();

    /** \brief Ensure availability of registration color. */
    void ensureRegistration();
};

#endif
 // COLORLIST_H
