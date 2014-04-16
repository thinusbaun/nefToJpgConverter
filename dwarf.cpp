#include "dwarf.hpp"

Dwarf::Dwarf(QObject *parent = 0, QString inputFolder, QString outputFolder, QString file)
{
  this->parent = parent;
  this->inputFolder = inputFolder;
  this->outputFolder = outputFolder;
  this->file = file;
  this->stage = 0;
  connect(this,SIGNAL(finished()), this, SLOT(insideFinished()));
}

void Dwarf::start()
{
  QStringList arguments;
  arguments << "-b" << "-JpgFromRaw" << "-w" << "jpeg/%f.jpg" << "-ext" << "NEF" << file;
  QProcess::start("exiftool", arguments);
}

void Dwarf::insideFinished()
{
  if(++stage == 2)
  {
    emit jobPercentChanged(100);
    emit jobFinished();
  } else
  {
    emit jobPercentChanged(50);
    QStringList arguments;
    arguments << "-overwrite_original_in_place" << "-tagsfromfile" <<  "COŚŚŚŚ" << "-ext";
    arguments << "JPG" << "jepg/changeFilename!";
    QProcess::start("exiftool", arguments);
  }
}

QString Dwarf::changeFileExt()
{
  return file.replace("NEF", "jpg", Qt::CaseInsensitive);
}
