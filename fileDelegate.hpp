#include <QDebug>
#include <QAbstractItemDelegate>
#include <QApplication>
#include <QFont>
#include <QFontMetrics>
#include <QPainter>

class FileDelegate : public QAbstractItemDelegate
{
  public:
    FileDelegate(QObject *parent);

    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const; 
    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const;
};
