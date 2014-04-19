#include "tableModel.hpp"

TableModel::TableModel(QObject *parent = 0)
{
  m_columns.append(QString("1"));
  m_columns.append(QString("2"));

}

TableModel::~TableModel()
{

}


int TableModel::rowCount(const QModelIndex &parent) const
{
  return m_files.size();
}

int TableModel::columnCount(const QModelIndex& parent) const
{
  return 2;
}

QVariant TableModel::data(const QModelIndex& index, int role) const
{
  if(!index.isValid())
  {
    return QVariant::Invalid;
  } else
  {
    switch (role)
    {
      case Qt::UserRole +1:
        return m_files[index.row()].progress;
        break;
      case Qt::UserRole +2:
        return m_files[index.row()].fileName;
        break;
    }
  }
}
 
QVariant TableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
 
  if(role == Qt::DisplayRole && orientation == Qt::Horizontal)
  {
    return m_columns[section];
  } else
  {
    return QVariant::Invalid;
  }
}

void TableModel::addItem(file m_file)
{
  beginInsertRows(QModelIndex(), m_files.size(), m_files.size());
  m_files.append(m_file);
  endInsertRows();
}

void TableModel::addItems(QStringList files)
{
  foreach (QString str, files)
  {
    file tmp;
    tmp.fileName = str;
    tmp.progress = 0;
    addItem(tmp);
  }
}

void TableModel::jobProgressChanged(QString fileName, int percent)
{
  for (int i = 0;i<m_files.size();i++)
  {
    if (m_files[i].fileName.split(".")[0] == fileName.split(".")[0])
    {
      qDebug() << percent;
      QModelIndex index = createIndex(i, 1);
      m_files[i].progress = percent;
      emit dataChanged(index, index);
    }
  }
}
