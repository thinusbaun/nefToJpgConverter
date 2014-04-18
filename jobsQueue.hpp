#include <QDebug>
#include <QQueue>

class JobsQueue : public QObject
{
  Q_OBJECT

  private:
    QString m_directory;
    QStringList m_file_list;
  public:
    JobsQueue(QString directory, QStringList fileList);
    ~JobsQueue();
  //private slots:
    //void jobFinished();
};
