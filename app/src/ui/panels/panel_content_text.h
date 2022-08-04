#ifndef PANEL_CONTENT_TEXT_H
#define PANEL_CONTENT_TEXT_H

#include "block_character.h"
#include "block_character_advanced.h"
#include "block_lists.h"
#include "block_paragraph.h"
#include "block_paragraph_advanced.h"
#include "block_text_advanced.h"
#include "block_text_alignment.h"
#include "block_text_font.h"
#include "block_textonpath.h"
#include "sectioncontainer.h"
#include <QWidget>

namespace Ui {
class PanelContentText;
}

class PanelContentText : public QWidget
{
    Q_OBJECT

public:
    explicit PanelContentText(QWidget *parent = nullptr);
    ~PanelContentText();

private:
    Ui::PanelContentText *ui;

    BlockTextFont           * blockTextFont;
    BlockTextAlignment      * blockTextAlignment;
    BlockTextAdvanced       * blockTextAdvanced;
    BlockParagraph          * blockParagraph;
    BlockParagraphAdvanced  * blockParagraphAdvanced;
    BlockCharacter          * blockCharacter;
    BlockCharacterAdvanced  * blockCharacterAdvanced;
    BlockLists              * blockLists;
    BlockTextOnPath         * blockTextOnPath;

    void setup();
    void addMenu(SectionContainer *section, QWidget *menuPanel);
};

#endif // PANEL_CONTENT_TEXT_H
