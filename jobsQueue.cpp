#include "jobsQueue.hpp"

JobsQueue::JobsQueue(QString directory, QStringList fileList)
{
  m_directory = directory;
  m_file_list = fileList;
  m_timer = NULL;
  ended = false;
}

JobsQueue::~JobsQueue()
{
  for (int i = 0; i<m_dwarfs.size(); i++)
  {
    delete m_dwarfs[i];
  }
  m_dwarfs.clear();
  if (!m_timer)
  {
    delete m_timer;
  }
}

void JobsQueue::startJobs()
{
  m_timer = new QElapsedTimer();
  m_timer->start();
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
  } else
  {
    if (!ended)
    {
      ended = true;
      emit jobsEnded(m_timer->elapsed());
    }
  }
}

void JobsQueue::passJobPercentChanged(QString fileName, int percent)
{
  emit  jobProgressChanged(fileName, percent);
  if (percent == 100)
  {
    startNextJob();
  }
}
