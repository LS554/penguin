// Copyright (c) 2025, London Sheard
// Licensed under the 3-Clause Sheard License                                                                               
// See the LICENSE file in project root for details.
// Visit https://github.com/LS554/3CSL for details on the 3CSL.

#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include <QString>
#include <QClipboard>
#include <QMessageBox>
#include <QLineEdit>
#include <QMenuBar>
#include <QToolBar>
#include <QMainWindow>

#include "gen.h"

int main(int argc, char** argv) {
    QApplication app(argc, argv);

    QMainWindow* window = new QMainWindow();
    window->setWindowTitle("Penguin Password Generator");
    window->resize(500, 100);

    QMenu* fileMenu = window->menuBar()->addMenu("File");
    QAction* licenseAction = new QAction("View License", window);
    QAction* exitAction = new QAction("Exit", window);
    fileMenu->addAction(licenseAction);
    fileMenu->addAction(exitAction);

    QMenu* editMenu = window->menuBar()->addMenu("Edit");
    QAction* copyAction = new QAction("Copy password", window);
    editMenu->addAction(copyAction);
    copyAction->setEnabled(false);

    QObject::connect(licenseAction, &QAction::triggered, [=](){
	QMessageBox::information(window, "License",
				 R"(3-Clause Sheard License (https://github.com/LS554/3CSL)

Copyright (c) 2025, London Sheard

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, this
   list of conditions and the following disclaimer.

2. Redistributions in binary form must reproduce the above copyright notice,
   this list of conditions, and the following disclaimer in a publicly accessible
   location provided with the distribution, such as a repository, project website,
   or documentation folder. The same publicly accessible location from which the
   binary is obtained must also clearly state where the complete corresponding
   source code can be accessed.

3. Neither the name of the copyright holder nor the names of its
   contributors may be used to endorse or promote products derived from
   this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.)");
});


    QObject::connect(exitAction, &QAction::triggered, &app, &QApplication::quit);

    
    QWidget* central = new QWidget(window);
    QVBoxLayout* layout = new QVBoxLayout(central);


    QLabel* passLabel = new QLabel("\n");
    passLabel->hide();
    layout->addWidget(passLabel);

    QLabel* blankLabel = new QLabel("\n");
    blankLabel->hide();
    layout->addWidget(blankLabel);

    QLabel* lenLabel = new QLabel("Password length:");
    layout->addWidget(lenLabel);

    QLineEdit* textbox = new QLineEdit();
    textbox->setMaxLength(2);
    textbox->setMinimumWidth(25);
    textbox->setMaximumWidth(25);
    layout->addWidget(textbox);

    QPushButton* genButton = new QPushButton("Generate password");
    layout->addWidget(genButton);

    QPushButton* copyButton = new QPushButton("Copy to clipboard");
    copyButton->hide();
    layout->addWidget(copyButton);

    window->setCentralWidget(central);

    QObject::connect(genButton, &QPushButton::clicked, [passLabel, textbox, copyButton, copyAction]() -> void {
	QString text = textbox->text();
	bool ok;
	int len = text.toInt(&ok);
	if (!ok) {
	    QMessageBox::critical(nullptr, "Error", "Please enter a valid length");
	    textbox->setText("");
	    return;
	}
        std::string password = GenPassword(static_cast<size_t>(len));
        passLabel->setText(QString::fromStdString(password));
        passLabel->show();
	copyButton->show();
	copyAction->setEnabled(true);
	return;
    });

    QObject::connect(copyButton, &QPushButton::clicked, [passLabel](){
	QClipboard* clipboard = QApplication::clipboard();
	clipboard->setText(passLabel->text());
    });

    QObject::connect(copyAction, &QAction::triggered, [passLabel](){
	QClipboard* clipboard = QApplication::clipboard();
	clipboard->setText(passLabel->text());
    });

    window->show();
    return app.exec();
}
