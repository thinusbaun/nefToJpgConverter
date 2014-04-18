#include "fileDelegate.hpp"
#include <QPainter>

FileDelegate::FileDelegate(QObject *parent = 0)
{

}

void FileDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
  if(index.column() == 1)
  {
    int progress = index.data(Qt::UserRole+1).toInt();
    QStyleOptionProgressBar progressBar;// = QStyleOptionProgressBar();
    progressBar.rect = option.rect;
    progressBar.minimum = 0;
    progressBar.maximum = 100;
    progressBar.progress = progress;
    progressBar.text = QString::number(progress) + QString("%");
    progressBar.textVisible = true;
    QStyle *st = QApplication::style();
    QApplication::style()->drawControl(QStyle::CE_ProgressBar, &progressBar,  painter);//, progressBar);
  } else if (index.column() == 0)
  {
    painter->drawText(option.rect, Qt::AlignCenter, index.data(Qt::UserRole+2).toString());
  }
}

QSize FileDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
  return QSize(10,12);
}
