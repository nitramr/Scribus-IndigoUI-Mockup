#ifndef TRASHBIN_WIDGET_H
#define TRASHBIN_WIDGET_H

#include <QLabel>

class TrashBinWidget : public QLabel
{
    Q_OBJECT

public:
    TrashBinWidget( QWidget * parent );
    ~TrashBinWidget() {};

    void dragEnterEvent( QDragEnterEvent *e );
    void dragLeaveEvent( QDragLeaveEvent * );
    void dropEvent( QDropEvent * e );

protected:
    QPixmap Normal;
    QPixmap Open;

protected slots:
    void iconSetChange();

signals:
    void delPageRequest(int);
    void delMasterRequest(QString);
};

#endif // TRASHBIN_WIDGET_H
