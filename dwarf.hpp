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

    public:
      Dwarf(QObject *parent = 0, QString inputFolder, QString outputFolder, QString file);
      ~Dwarf();
      void start();

    signals:
      void jobPercentChanged(int percent);
      void jobFinished();

    private slots:
      void insideFinished();

};
