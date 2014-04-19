#include "fileDelegate.hpp"

FileDelegate::FileDelegate(QObject *parent = 0)
{

}

void FileDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
  if(index.column() == 1)
  {
    int progress = index.data(Qt::UserRole+1).toInt();
    QStyleOptionProgressBar progressBar;
    progressBar.rect = option.rect;
    progressBar.minimum = 0;
    progressBar.maximum = 100;
    progressBar.progress = progress;
    progressBar.text = QString::number(progress) + QString("%");
    progressBar.textVisible = true;
    QApplication::style()->drawControl(QStyle::CE_ProgressBar, &progressBar,  painter);
  } else if (index.column() == 0)
  {
    painter->drawText(option.rect, Qt::AlignCenter, index.data(Qt::UserRole+2).toString());
  }
}

QSize FileDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
  if (index.column() == 0)
  {
    QFontMetrics *metrics = new QFontMetrics(QFont());
    QSize tmp = metrics->size(Qt::TextSingleLine, index.data(Qt::UserRole+2).toString());
    delete metrics;
    return tmp;
  } else
  {
    return QSize(10,15);
  }
}
