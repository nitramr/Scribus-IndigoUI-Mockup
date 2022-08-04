#include "colorlist.h"
#include "scribusdoc.h"

ColorList::ColorList(/*ScribusDoc* doc, */bool retainDoc)
    : //m_doc(doc),
      m_retainDoc(retainDoc)
{

}

//void ColorList::setDocument(ScribusDoc* doc)
//{
//    m_doc = doc;
//}

ColorList& ColorList::operator= (const ColorList& list)
{
    clear();
    //    if (!m_retainDoc)
    //        m_doc = list.m_doc;
    addColors(list);
    return *this;
}

void ColorList::addColors(const ColorList& colorList, bool overwrite)
{
    ColorList::ConstIterator it;
    ColorList::ConstIterator itend;
    itend = colorList.end();
    for (it = colorList.begin(); it != itend; ++it)
    {
        if (overwrite || !contains(it.key()))
            insert(it.key(), it.value());
    }
}

void ColorList::copyColors(const ColorList& colorList, bool overwrite)
{
    clear();
    addColors(colorList, overwrite);
}

//ScribusDoc* ColorList::document() const
//{
//    return m_doc;
//}

void ColorList::ensureDefaultColors()
{
    ensureBlack();
    ensureWhite();
    ensureRegistration();
}

void ColorList::ensureBlack()
{
    ColorList::Iterator itb = find("Black");
    if (itb == end())
    {
        insert("Black", ScColor(0, 0, 0, 255));
        return;
    }

    ScColor& black = itb.value();
    ColorModel model = black.getColorModel();

    switch(model){
    case ColorModel::HSV:
        black.setHsvF(0,0,0);
        break;
    case ColorModel::RGB:
        black.setRgbF(0.0, 0.0, 0.0);
        break;
    case ColorModel::Lab:
        black.setLab(0.0, 0.0, 0.0);
        break;
    case ColorModel::CMYK:
    default:
        black.setCmykF(0.0, 0.0, 0.0, 1.0);
    }

}

void ColorList::ensureWhite()
{
    ColorList::Iterator itw = find("White");
    if (itw == end())
    {
        insert("White", ScColor(0, 0, 0, 0));
        return;
    }

    ScColor& white = itw.value();
    ColorModel model = white.getColorModel();

    switch(model){
    case ColorModel::HSV:
        white.setHsvF(0,0,1);
        break;
    case ColorModel::RGB:
        white.setRgbF(1.0, 1.0, 1.0);
        break;
    case ColorModel::Lab:
        white.setLab(100.0, 0.0, 0.0);
        break;
    case ColorModel::CMYK:
    default:
        white.setCmykF(0.0, 0.0, 0.0, 0.0);
    }

}

void ColorList::ensureRegistration()
{
    ScColor cc(255, 255, 255, 255);
    cc.setRegistrationColor(true);
    insert("Registration", cc);
}

QString ColorList::tryAddColor(QString name, const ScColor& col)
{
    if (contains(name))
        return name;
    bool found = false;
    QString ret = name;
    ColorList::Iterator it;
    for (it = begin(); it != end(); ++it)
    {
        if (it.value() == col)
        {
            ret = it.key();
            found = true;
            break;
        }
    }
    if (!found)
        insert(name, col);
    return ret;
}
