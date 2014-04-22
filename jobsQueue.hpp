#include <QDebug>
#include <QQueue>
#include <QThread>
#include <QVector>
#include "dwarf.hpp"
#include <QElapsedTimer>

class JobsQueue : public QObject
{
  Q_OBJECT

  private:
    QString m_directory;
    QStringList m_file_list;
    QVector<Dwarf*> m_dwarfs;
    QElapsedTimer *m_timer;
    bool ended;
    bool m_save_exif;
    bool aborted;

  private slots:
    void passJobPercentChanged(QString fileName, int percent);

  public:
    JobsQueue(QString directory, QStringList fileList, bool saveExif);
    ~JobsQueue();
    void startJobs();
    void startNextJob();
    void abort();

  signals:
    void jobProgressChanged(QString fileName, int percent);
    void jobsEnded(int time);
};
