/***************************************************************************
 *   Copyright (C) 2009 - 2010 by Christian Doerffel                       *
 *   schdorm@googlemail.com                                                *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/

#include "mainwindow.h"
#include "ui_MainWindow.h"

#include <admsocket.h>

// #include <maphandler.h>
#include "mapthread.h"

#include <QtCore/QDir>
#include <QtGui/QFileDialog>

#include <QtGui/QApplication>

MainWindow::MainWindow()
{
  m_socket = new AdmSocket(this);
//   m_socket->ohconnect();
  ui = new Ui::MainWindow();
  ui->setupUi(this);
  
  ui->actionQuit->setShortcut(QKeySequence::Quit);
  ui->actionConnectToLocal->setShortcut(QKeySequence(Qt::ALT + Qt::Key_C));
  ui->actionStart_Game->setShortcut(QKeySequence(Qt::ALT + Qt::Key_S));
  
  connect(ui->actionConnectToLocal, SIGNAL(triggered()), m_socket, SLOT(ohconnect()));
  connect(ui->actionStart_Game, SIGNAL(triggered()), this, SLOT(startGame()));
  connect(ui->actionReset_Game, SIGNAL(triggered()), m_socket, SLOT(restartGame()));
  
  connect(m_socket, SIGNAL(error(QLocalSocket::LocalSocketError)), this, SLOT(printSocketError(QLocalSocket::LocalSocketError)));
  connect(m_socket, SIGNAL(disconnected()), this, SLOT(disconnected()));
  connect(m_socket, SIGNAL(connected()), this, SLOT(connected()));
  
  connect(ui->actionQuit, SIGNAL(triggered()), qApp, SLOT(quit()));
}


void MainWindow::startGame()
{
  
  QString filename = QFileDialog::getOpenFileName(this, tr("Worldmap"), QDir::homePath(),  tr("Images (*.png *.xpm *.jpg)"));
  if(!filename.isEmpty())
  {
    MapThread *thread = new MapThread(filename, this);
//     connect(thread, SIGNAL(ready()), thread, SLOT(quit()));
    connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
    thread->start();
    m_socket->sendCommand(AdmSocket::StartGame);

//     QImage *img = new QImage(filename);
//     sleep(1);
    
//     maphandling(img);
  }
}

void MainWindow::printSocketError(QLocalSocket::LocalSocketError error)
{
  qWarning() << "An Local Socket Error occured: " << error;
  statusBar()->showMessage("Can't access to server: an error occured - please see in the std io for Details.");
}

void MainWindow::connected()
{
  m_socket->ident();
  ui->actionConnectToLocal->setEnabled(false);
  
}

void MainWindow::disconnected()
{
  ui->actionConnectToLocal->setEnabled(true);  
  ui->actionDisconnect->setEnabled(false);
}