#include "mainWindow.hpp"
#include <QHeaderView>

MainWindow::MainWindow(QWidget *parent)
{
  m_layout = new QVBoxLayout();
  m_widget = new QWidget(this);
  this->setCentralWidget(m_widget);
  m_view = new QTableView(this);
  m_run_button = new QPushButton("Wybierz folder i konwertuj.", this);
  m_widget->setLayout(m_layout);
  m_layout->addWidget(m_view);
  m_layout->addWidget(m_run_button);
  m_file_dialog = new QFileDialog(this);
  m_file_dialog->setFileMode(QFileDialog::Directory);
  m_file_dialog->setOption(QFileDialog::ShowDirsOnly);
  connect(m_run_button, SIGNAL(pressed()), this, SLOT(runDirDialog()));
  m_delegate = new FileDelegate(m_view);
  m_model = new TableModel(m_view);
  m_view->setItemDelegate(m_delegate);
  m_view->setModel(m_model);
  m_view->resizeColumnsToContents();
  m_view->horizontalHeader()->setStretchLastSection(true);
  m_view->setAutoScroll(true);
}

MainWindow::~MainWindow()
{
  delete m_run_button;
  delete m_view;
  delete m_layout;
  delete m_widget;
  delete m_file_dialog;
  delete m_delegate;
  delete m_view;
  delete m_model;
  delete m_queue;
}
  
void MainWindow::runDirDialog()
{
  if (m_file_dialog->exec())
  {
    QDir().mkpath(m_file_dialog->selectedFiles()[0]+"/jpeg/");
    QStringList filters;
    QDir dir(m_file_dialog->selectedFiles()[0]);
    filters << "*.nef";
    dir.setNameFilters(filters);
    m_model->addItems(dir.entryList(filters));
    m_view->resizeColumnsToContents();
    m_queue = new JobsQueue(m_file_dialog->selectedFiles()[0], dir.entryList(filters));
    connect(m_queue, SIGNAL(jobProgressChanged(QString , int )), m_model, SLOT(jobProgressChanged(QString, int)));
    connect(m_queue, SIGNAL(jobsEnded( int )), this, SLOT(jobsEnded(int)));
    m_queue->startJobs();
  }
}

void MainWindow::jobsEnded(int time)
{
    QString formattedTime;
   
    int hours = time/(1000*60*60);
    int minutes = (time-(hours*1000*60*60))/(1000*60);
    int seconds = (time-(minutes*1000*60)-(hours*1000*60*60))/1000;
    int milliseconds = time-(seconds*1000)-(minutes*1000*60)-(hours*1000*60*60);

    formattedTime.append(QString("%1").arg(hours, 2, 10, QLatin1Char('0')) + ":" +
    QString( "%1" ).arg(minutes, 2, 10, QLatin1Char('0')) + ":" +
    QString( "%1" ).arg(seconds, 2, 10, QLatin1Char('0')) + ":" +
    QString( "%1" ).arg(milliseconds, 3, 10, QLatin1Char('0')));
    QMessageBox msgBox;
    msgBox.setText("Zdjęcia skonwertowane w czasie: " + formattedTime);
    msgBox.exec();

}
