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

    public:
      Dwarf(QString inputFolder, QString outputFolder, QString file, QObject *parent);
      ~Dwarf();
      void start();

    signals:
      void jobPercentChanged(int percent);
      void jobFinished();

    private slots:
      void insideFinished(int exitCode, QProcess::ExitStatus exitStatus);

};
