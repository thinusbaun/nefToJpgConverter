#include <QDebug>
#include <QAbstractItemDelegate>
#include <QApplication>
//#include <QSize>

class FileDelegate : public QAbstractItemDelegate
{
  public:
    FileDelegate(QObject *parent);

    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const; 
    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const;
};
