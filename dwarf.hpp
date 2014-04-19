#ifndef DWARF_HPP
#define DWARF_HPP
#include <QProcess>
#include <QDebug>

class Dwarf : public QProcess
{
    Q_OBJECT	
    private:
      QString file;
      QString inputFolder;
      QString outputFolder;
      char stage;
      QString changeFileExt();
      QObject *parent;
      bool saveExif;

    public:
      Dwarf(QString inputFolder, QString outputFolder, bool saveExif,  QObject *parent);
      ~Dwarf();
      void start();
      void startNewJob(QString file);

    signals:
      void jobPercentChanged(QString fileName, int percent);

    private slots:
      void insideFinished(int exitCode, QProcess::ExitStatus exitStatus);

};
#endif
