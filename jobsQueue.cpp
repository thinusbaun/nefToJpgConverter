#include "jobsQueue.hpp"

JobsQueue::JobsQueue(QString directory, QStringList fileList)
{
  m_directory = directory;
  m_file_list = fileList;
}

JobsQueue::~JobsQueue()
{

}

void JobsQueue::startJobs()
{
  for (int i = 0; i<QThread::idealThreadCount(); i++)
  {
    m_dwarfs.append(new Dwarf(m_directory, m_directory+QString("/jpeg/"), this));
    connect(m_dwarfs.last(), SIGNAL(jobPercentChanged(QString, int)), this, SLOT(passJobPercentChanged(QString, int)));
  }
  for (int i = 0; i<m_dwarfs.size();i++)
  {
    startNextJob();
  }
}

void JobsQueue::startNextJob()
{
  if (m_file_list.size() != 0)
  {
    for (int i = 0;i<m_dwarfs.size();i++)
    {
      Dwarf *dw = m_dwarfs[i];
      if (dw->state() == QProcess::NotRunning)
      {
        dw->startNewJob(m_file_list.first());
        m_file_list.removeAt(0);
        break;
      }
    }
  }
}

void JobsQueue::passJobPercentChanged(QString fileName, int percent)
{
  qDebug() << "passJobPercentChanged  " << fileName << percent;
  if (percent == 100)
  {
    startNextJob();
  }
}
