#include <QAbstractTableModel>
#include <QDebug>
#include <QTableView>

struct file
{
  QString fileName;
  int progress;
};

class TableModel : public QAbstractTableModel
{
  Q_OBJECT
  private:
    QVector<file> m_files;
    QVector<QString> m_columns;
    QTableView *m_view;

  public slots:
    void jobProgressChanged(QString fileName, int percent);
  
  public:
    TableModel(QObject *parent);
    ~TableModel();
    int rowCount(const QModelIndex &parent) const; 
    int columnCount(const QModelIndex& parent) const;
    QVariant data(const QModelIndex& index, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    void addItem(file m_file);
    void addItems(QStringList files);
};

