#include <QDebug>
#include <QMainWindow>
#include <QVBoxLayout>
#include <QTableView>
#include <QPushButton>
#include <QWidget>
#include <QFileDialog>
#include <QDir>
#include "fileDelegate.hpp"
#include "tableModel.hpp"
#include "jobsQueue.hpp"
#include <QMessageBox>

class MainWindow : public QMainWindow
{
  Q_OBJECT
  private:
    QVBoxLayout *m_layout;
    QTableView *m_view;
    QPushButton *m_run_button;
    QWidget *m_widget;
    QFileDialog *m_file_dialog;
    TableModel *m_model;
    FileDelegate *m_delegate;
    JobsQueue *m_queue;
  private slots:
    void runDirDialog();
    void jobsEnded(int time);
  public: 
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
};
