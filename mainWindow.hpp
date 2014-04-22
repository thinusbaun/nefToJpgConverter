#include <QDebug>
#include <QMainWindow>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QTableView>
#include <QPushButton>
#include <QWidget>
#include <QFileDialog>
#include <QDir>
#include "fileDelegate.hpp"
#include "tableModel.hpp"
#include "jobsQueue.hpp"
#include <QMessageBox>
#include <QCheckBox>

class MainWindow : public QMainWindow
{
  Q_OBJECT
  private:
    QVBoxLayout *m_layout;
    QHBoxLayout *m_h_layout;
    QTableView *m_view;
    QPushButton *m_run_button;
    QPushButton *m_abort;
    QWidget *m_widget;
    QFileDialog *m_file_dialog;
    QCheckBox *m_exif_box;
    TableModel *m_model;
    FileDelegate *m_delegate;
    JobsQueue *m_queue;
  private slots:
    void runDirDialog();
    void jobsEnded(int time);
    void abortClicked();
  public: 
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
};
