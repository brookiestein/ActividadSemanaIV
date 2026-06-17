#include "mainwindow.hpp"
#include "ui_mainwindow.h"

#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , m_ui(new Ui::MainWindow)
{
    m_ui->setupUi(this);

    // Aquí hago la conexión con el evento que emite el campo de la contraseña cuando
    // se modifica el texto.
    connect(m_ui->passwordEdit, &QLineEdit::textChanged, this, &MainWindow::onTextChanged);
    // Aquí hago la conexión con el evento que emite el botón de iniciar sesión cuando se
    // hace clic sobre él.
    connect(m_ui->loginButton, &QPushButton::clicked, this, &MainWindow::onLogin);
    // Lo mismo, pero con el botón de salir.
    connect(m_ui->exitButton, &QPushButton::clicked, this, &MainWindow::onExit);
}

MainWindow::~MainWindow()
{
    delete m_ui;
}

void MainWindow::onTextChanged(const QString &text)
{
    QString textColor{text.size() < 8 ? "red" : "white"};

    m_ui->passwordEdit->setStyleSheet(QString("QLineEdit { color: %1; }").arg(textColor));
}

void MainWindow::onLogin()
{
    auto username = m_ui->usernameEdit->text().trimmed();
    if (username.isEmpty() or username.size() < 3) {
        QMessageBox::critical(this, tr("Error"), tr("El nombre de usuario no es válido."));
        m_ui->usernameEdit->setFocus();
        return;
    }

    if (auto password = m_ui->passwordEdit->text().trimmed();
        password.isEmpty() or password.size() < 8) {
        QMessageBox::critical(this, tr("Error"), tr("La contraseña no es válida."));
        m_ui->passwordEdit->setFocus();
        return;
    }

    QMessageBox::information(this,
                             tr("Inicio de Sesión Exitoso"),
                             tr("¡Bienvenido %1!").arg(username));
}

void MainWindow::onExit()
{
    auto reply = QMessageBox::question(this,
                                       tr("Confirmación"),
                                       tr("¿Estás seguro que deseas salir?"));

    if (reply != QMessageBox::Yes)
        return;

    QApplication::instance()->quit();
}
