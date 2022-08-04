#ifndef TRASHBIN_H
#define TRASHBIN_H

#include <QLabel>

class TrashBin : public QLabel
{
    Q_OBJECT

public:
    TrashBin( QWidget * parent );
    ~TrashBin() {};

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

#endif // TRASHBIN_H
