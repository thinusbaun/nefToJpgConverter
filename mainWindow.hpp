#include <QDebug>
#include <QMainWindow>
#include <QVBoxLayout>
#include <QTableView>
#include <QPushButton>
#include <QWidget>
#include <QFileDialog>
#include <QDir>

class MainWindow : public QMainWindow
{
  Q_OBJECT
  private:
    QVBoxLayout *m_layout;
    QTableView *m_view;
    QPushButton *m_run_button;
    QWidget *m_widget;
    QFileDialog *m_file_dialog;
  private slots:
    void runDirDialog();
  public: 
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
};
