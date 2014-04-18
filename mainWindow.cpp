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

}

MainWindow::~MainWindow()
{
  delete m_run_button;
  delete m_view;
  delete m_layout;
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
    m_queue = new JobsQueue(m_file_dialog->selectedFiles()[0], dir.entryList(filters));
    //dodać tutaj dodanie do listy i do kolejki
  }
}

