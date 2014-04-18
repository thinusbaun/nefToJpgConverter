#include "jobsQueue.hpp"

JobsQueue::JobsQueue(QString directory, QStringList fileList)
{
  m_directory = directory;
  m_file_list = fileList;
}

JobsQueue::~JobsQueue()
{

}
