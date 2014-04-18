#include <QAbstractTableModel>

struct file
{
  QString fileName;
  int progress;
};

class TableModel : public QAbstractTableModel
{
  private:
    QVector<file> m_files;
    QVector<QString> m_columns;

  public:
    TableModel(QObject *parent);
    ~TableModel();
    int rowCount(const QModelIndex &parent) const; 
    int columnCount(const QModelIndex& parent) const;
    QVariant data(const QModelIndex& index, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    void addItem(file m_file);
};

