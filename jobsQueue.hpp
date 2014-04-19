#include <QDebug>
#include <QQueue>
#include <QThread>
#include <QVector>
#include "dwarf.hpp"

class JobsQueue : public QObject
{
  Q_OBJECT

  private:
    QString m_directory;
    QStringList m_file_list;
    QVector<Dwarf*> m_dwarfs;
  private slots:
    void passJobFinished(QString fileName);
    void passJobPercentChanged(QString fileName, int percent);
  public:
    JobsQueue(QString directory, QStringList fileList);
    ~JobsQueue();
    void startJobs();
    void startNextJob();
  signals:
    void jobFinished(QString fileName);
    void jobPercentChanged(QString fileName, int percent);
};
