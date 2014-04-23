#include "dwarf.hpp"

Dwarf::Dwarf(QString inputFolder, QString outputFolder, bool saveExif, QObject *parent = 0)
{
  this->parent = parent;
  this->inputFolder = inputFolder;
  this->outputFolder = outputFolder;
  this->saveExif = saveExif;
  this->stage = 0;
  this->setWorkingDirectory(inputFolder);
  connect(this,SIGNAL(finished(int , QProcess::ExitStatus )), this, SLOT(insideFinished(int , QProcess::ExitStatus )));
}

Dwarf::~Dwarf()
{

}

void Dwarf::start()
{
  QStringList arguments;
  arguments << "-b" << "-JpgFromRaw" << "-w" << "jpeg/%f.jpg" << "-ext" << "NEF" << file;
  QProcess::start("exiftool", arguments);
}

void Dwarf::insideFinished(int exitCode, QProcess::ExitStatus exitStatus)
{
  if (exitCode  != 1 && exitCode != 0)
  {
    qDebug() << exitCode;
    emit jobPercentChanged(file, -1);
  } else
  {
    unsigned char finalState = (saveExif) ? 2 : 1;
    if(++stage == finalState)
    {
      emit jobPercentChanged(file, 100);
    } else
    {
      emit jobPercentChanged(file, 50);
      QStringList arguments;
      arguments << "-overwrite_original_in_place" << "-tagsfromfile" <<  file << "-ext";
      arguments << "JPG" << "jpeg/"+changeFileExt();
      QProcess::start("exiftool", arguments);
    }
  }
}

QString Dwarf::changeFileExt()
{
  return file.replace("NEF", "jpg", Qt::CaseInsensitive);
}

void Dwarf::startNewJob(QString file)
{
  this->file = file;
  this->stage = 0;
  this->start();
}
