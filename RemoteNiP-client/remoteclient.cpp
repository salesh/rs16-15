#include "remoteclient.h"
#include "ui_remoteclient.h"
#include "QMessageBox"

RemoteClient::RemoteClient(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::RemoteClient){
    ui->setupUi(this);

    ui->inputWidget->hide();

    tcpSocket = nullptr;

    tcpServer = new QTcpServer(this);
    udpSocket = new QUdpSocket(this);


    ui->scrollArea->setViewport(ui->widget);
    connect(ui->scrollArea, SIGNAL(sendMove(const QPointF&)), this,SLOT(sendMouseMove(const QPointF&)));
    connect(tcpServer, SIGNAL(newConnection()), this, SLOT(newConnection()));
    connect(ui->chooseNetworkButton, SIGNAL(clicked()), this, SLOT(sendConnectionRequest()));
    connect(ui->chooseNetworkButton, SIGNAL(clicked()), this, SLOT(newUi()));
    connect(ui->searchButton,SIGNAL(clicked()),this,SLOT(initialize()));
    connect(ui->altButton,SIGNAL(clicked()),this,SLOT(altButtonIndicator()));
    connect(ui->shiftButton,SIGNAL(clicked()),this,SLOT(shiftButtonIndicator()));
    connect(ui->ctrlButton,SIGNAL(clicked()),this,SLOT(ctrlButtonIndicator()));
    connect(ui->disconnectButton,SIGNAL(clicked()),this,SLOT(disconnectFromNetwork()));
}

RemoteClient::~RemoteClient(){
    delete ui;
    tcpServer->close();
    tcpServer->deleteLater();
    udpSocket->abort();
    udpSocket->deleteLater();
}

void RemoteClient::initialize(){
    ui->chooseNetworkComboBox->clear();
    tcpServer->close();
    tcpServer->listen(QHostAddress::AnyIPv4, 5600);

    QByteArray datagram = "NiP:Broadcast";

    udpSocket->close();

    udpSocket->bind(QHostAddress::AnyIPv4, 5600, QUdpSocket::DontShareAddress | QUdpSocket::ReuseAddressHint);
    connect(udpSocket, SIGNAL(readyRead()), this, SLOT(incomingUdpData()));
    udpSocket->writeDatagram(datagram, QHostAddress::Broadcast, 5600);
}

// send connection request to selected address
void RemoteClient::sendConnectionRequest(){
    m_hostAddress.setAddress((ui->chooseNetworkComboBox->currentText()));

    QByteArray datagram = "NiP:Hello";

    tcpServer->close();
    tcpServer->listen(QHostAddress::AnyIPv4, 5600);
    udpSocket->writeDatagram(datagram, m_hostAddress, 5600);
}

// if there is new pending connection request, establish connection
void RemoteClient::newConnection(){
    if (!tcpSocket) {
        tcpSocket = tcpServer->nextPendingConnection();

        connect(tcpSocket, SIGNAL(disconnected()), this, SLOT(deleteConnection()));
    }
}


void RemoteClient::incomingUdpData(){
    QHostAddress hostAddress;
    QByteArray datagram;

    datagram.resize(udpSocket->pendingDatagramSize());
    udpSocket->readDatagram(datagram.data(), datagram.size(), &hostAddress);

    QString available = "NiP:NotConnected";
    QString bussy = "NiP:Connected";

    if(datagram.indexOf(available) == 0) {
        // if positive broadcast reply add address to combobox
        ui->chooseNetworkComboBox->addItem(hostAddress.toString());
    } else if(datagram.indexOf(bussy) == 0){

    }
}


void RemoteClient::deleteConnection(){
    tcpSocket->deleteLater();
    tcpSocket = nullptr;
    ui->inputWidget->hide();
    ui->chooseNetworkComboBox->clear();
    QMessageBox::information(this, "Kick!","Disconnected!");
}

void RemoteClient::disconnectFromNetwork(){
    tcpSocket->disconnectFromHost();
}

void RemoteClient::newUi(){
    if(ui->chooseNetworkComboBox->currentText()==""){
        QMessageBox::information(this, "Fail!","IP not selected!");
        return;
    }
    ui->inputWidget->show();
}


void RemoteClient::keyboardPressed(){
    QPushButton *clickedButton=qobject_cast<QPushButton *>(sender());
    quint8 mode1=1;
    quint32 key;
    quint32 modifiers=Qt::NoModifier;
    bool keyPressed=true;
    if(clickedButton->objectName()=="aButton"){
        key=Qt::Key_A;
    }
    else if(clickedButton->objectName()=="bButton"){
        key=Qt::Key_B;
    }
    else if(clickedButton->objectName()=="cButton"){
        key=Qt::Key_C;
    }
    else if(clickedButton->objectName()=="dButton"){
        key=Qt::Key_D;
    }
    else if(clickedButton->objectName()=="eButton"){
        key=Qt::Key_E;
    }
    else if(clickedButton->objectName()=="fButton"){
        key=Qt::Key_F;
    }
    else if(clickedButton->objectName()=="gButton"){
        key=Qt::Key_G;
    }
    else if(clickedButton->objectName()=="hButton"){
        key=Qt::Key_H;
    }
    else if(clickedButton->objectName()=="iButton"){
        key=Qt::Key_I;
    }
    else if(clickedButton->objectName()=="jButton"){
        key=Qt::Key_J;
    }
    else if(clickedButton->objectName()=="kButton"){
        key=Qt::Key_K;
    }
    else if(clickedButton->objectName()=="lButton"){
        key=Qt::Key_L;
    }
    else if(clickedButton->objectName()=="mButton"){
        key=Qt::Key_M;
    }
    else if(clickedButton->objectName()=="nButton"){
        key=Qt::Key_N;
    }
    else if(clickedButton->objectName()=="oButton"){
        key=Qt::Key_O;
    }
    else if(clickedButton->objectName()=="pButton"){
        key=Qt::Key_P;
    }
    else if(clickedButton->objectName()=="qButton"){
        key=Qt::Key_Q;
    }
    else if(clickedButton->objectName()=="rButton"){
        key=Qt::Key_R;
    }
    else if(clickedButton->objectName()=="sButton"){
        key=Qt::Key_S;
    }
    else if(clickedButton->objectName()=="tButton"){
        key=Qt::Key_T;
    }
    else if(clickedButton->objectName()=="uButton"){
        key=Qt::Key_U;
    }
    else if(clickedButton->objectName()=="vButton"){
        key=Qt::Key_V;
    }
    else if(clickedButton->objectName()=="wButton"){
        key=Qt::Key_W;
    }
    else if(clickedButton->objectName()=="xButton"){
        key=Qt::Key_X;
    }
    else if(clickedButton->objectName()=="yButton"){
        key=Qt::Key_Y;
    }
    else if(clickedButton->objectName()=="zButton"){
        key=Qt::Key_Z;
    }
    else if(clickedButton->objectName()=="_0Button"){
        key=Qt::Key_0;
    }
    else if(clickedButton->objectName()=="_1Button"){
        key=Qt::Key_1;
    }
    else if(clickedButton->objectName()=="_2Button"){
        key=Qt::Key_2;
    }
    else if(clickedButton->objectName()=="_3Button"){
        key=Qt::Key_3;
    }
    else if(clickedButton->objectName()=="_4Button"){
        key=Qt::Key_4;
    }
    else if(clickedButton->objectName()=="_5Button"){
        key=Qt::Key_5;
    }
    else if(clickedButton->objectName()=="_6Button"){
        key=Qt::Key_6;
    }
    else if(clickedButton->objectName()=="_7Button"){
        key=Qt::Key_7;
    }
    else if(clickedButton->objectName()=="_8Button"){
        key=Qt::Key_8;
    }
    else if(clickedButton->objectName()=="_9Button"){
        key=Qt::Key_9;
    }
    else if(clickedButton->objectName()=="slashButton"){
        key=Qt::Key_Slash;
    }
    else if(clickedButton->objectName()=="backslashButton"){
        key=Qt::Key_Backslash;
    }
    else if(clickedButton->objectName()=="comaButton"){
        key=Qt::Key_Comma;
    }
    else if(clickedButton->objectName()=="dotNetButton"){
        key=Qt::Key_Period;
    }
    else if(clickedButton->objectName()=="eqButton"){
        key=Qt::Key_Equal;
    }
    else if(clickedButton->objectName()=="cbButton"){
        key=Qt::Key_BracketRight;
    }
    else if(clickedButton->objectName()=="obButton"){
        key=Qt::Key_BracketLeft;
    }
    else if(clickedButton->objectName()=="semicolonButton"){
        key=Qt::Key_Semicolon;
    }
    else if(clickedButton->objectName()=="dashButton"){
        key=Qt::Key_Minus;
    }
    else if(clickedButton->objectName()=="upperComaButton"){
        key=Qt::Key_Apostrophe;
    }
    else if(clickedButton->objectName()=="spaceButton"){
        key=Qt::Key_Space;
    }
    else if(clickedButton->objectName()=="backspaceButton"){
        key=Qt::Key_Backspace;
    }
    else if(clickedButton->objectName()=="enterButton"){
        key=Qt::Key_Return;
    }

    if(shiftIndicator==true)
        modifiers=modifiers | Qt::ShiftModifier;
    if(ctrlIndicator==true)
        modifiers=modifiers | Qt::ControlModifier;
    if(altIndicator==true)
        modifiers=modifiers | Qt::AltModifier;

    QByteArray data;
    QDataStream streamOut(&data, QIODevice::WriteOnly);
    streamOut << mode1;
    streamOut << key;
    streamOut << modifiers;
    streamOut << keyPressed;

    tcpSocket->write(data);

}

void RemoteClient::keyboardReleased(){
    QPushButton *clickedButton=qobject_cast<QPushButton *>(sender());
    quint8 mode1=1;
    quint32 key;
    quint32 modifiers=Qt::NoModifier;
    bool keyPressed=false;


    if(clickedButton->objectName()=="aButton"){
        key=Qt::Key_A;
    }
    else if(clickedButton->objectName()=="bButton"){
        key=Qt::Key_B;
    }
    else if(clickedButton->objectName()=="cButton"){
        key=Qt::Key_C;
    }
    else if(clickedButton->objectName()=="dButton"){
        key=Qt::Key_D;
    }
    else if(clickedButton->objectName()=="eButton"){
        key=Qt::Key_E;
    }
    else if(clickedButton->objectName()=="fButton"){
        key=Qt::Key_F;
    }
    else if(clickedButton->objectName()=="gButton"){
        key=Qt::Key_G;
    }
    else if(clickedButton->objectName()=="hButton"){
        key=Qt::Key_H;
    }
    else if(clickedButton->objectName()=="iButton"){
        key=Qt::Key_I;
    }
    else if(clickedButton->objectName()=="jButton"){
        key=Qt::Key_J;
    }
    else if(clickedButton->objectName()=="kButton"){
        key=Qt::Key_K;
    }
    else if(clickedButton->objectName()=="lButton"){
        key=Qt::Key_L;
    }
    else if(clickedButton->objectName()=="mButton"){
        key=Qt::Key_M;
    }
    else if(clickedButton->objectName()=="nButton"){
        key=Qt::Key_N;
    }
    else if(clickedButton->objectName()=="oButton"){
        key=Qt::Key_O;
    }
    else if(clickedButton->objectName()=="pButton"){
        key=Qt::Key_P;
    }
    else if(clickedButton->objectName()=="qButton"){
        key=Qt::Key_Q;
    }
    else if(clickedButton->objectName()=="rButton"){
        key=Qt::Key_R;
    }
    else if(clickedButton->objectName()=="sButton"){
        key=Qt::Key_S;
    }
    else if(clickedButton->objectName()=="tButton"){
        key=Qt::Key_T;
    }
    else if(clickedButton->objectName()=="uButton"){
        key=Qt::Key_U;
    }
    else if(clickedButton->objectName()=="vButton"){
        key=Qt::Key_V;
    }
    else if(clickedButton->objectName()=="wButton"){
        key=Qt::Key_W;
    }
    else if(clickedButton->objectName()=="xButton"){
        key=Qt::Key_X;
    }
    else if(clickedButton->objectName()=="yButton"){
        key=Qt::Key_Y;
    }
    else if(clickedButton->objectName()=="zButton"){
        key=Qt::Key_Z;
    }
    else if(clickedButton->objectName()=="_0Button"){
        key=Qt::Key_0;
    }
    else if(clickedButton->objectName()=="_1Button"){
        key=Qt::Key_1;
    }
    else if(clickedButton->objectName()=="_2Button"){
        key=Qt::Key_2;
    }
    else if(clickedButton->objectName()=="_3Button"){
        key=Qt::Key_3;
    }
    else if(clickedButton->objectName()=="_4Button"){
        key=Qt::Key_4;
    }
    else if(clickedButton->objectName()=="_5Button"){
        key=Qt::Key_5;
    }
    else if(clickedButton->objectName()=="_6Button"){
        key=Qt::Key_6;
    }
    else if(clickedButton->objectName()=="_7Button"){
        key=Qt::Key_7;
    }
    else if(clickedButton->objectName()=="_8Button"){
        key=Qt::Key_8;
    }
    else if(clickedButton->objectName()=="_9Button"){
        key=Qt::Key_9;
    }
    else if(clickedButton->objectName()=="slashButton"){
        key=Qt::Key_Slash;
    }
    else if(clickedButton->objectName()=="backslashButton"){
        key=Qt::Key_Backslash;
    }
    else if(clickedButton->objectName()=="comaButton"){
        key=Qt::Key_Comma;
    }
    else if(clickedButton->objectName()=="dotNetButton"){
        key=Qt::Key_Period;
    }
    else if(clickedButton->objectName()=="eqButton"){
        key=Qt::Key_Equal;
    }
    else if(clickedButton->objectName()=="cbButton"){
        key=Qt::Key_BracketRight;
    }
    else if(clickedButton->objectName()=="obButton"){
        key=Qt::Key_BracketLeft;
    }
    else if(clickedButton->objectName()=="semicolonButton"){
        key=Qt::Key_Semicolon;
    }
    else if(clickedButton->objectName()=="dashButton"){
        key=Qt::Key_Minus;
    }
    else if(clickedButton->objectName()=="upperComaButton"){
        key=Qt::Key_Apostrophe;
    }
    else if(clickedButton->objectName()=="spaceButton"){
        key=Qt::Key_Space;
    }
    else if(clickedButton->objectName()=="backspaceButton"){
        key=Qt::Key_Backspace;
    }
    else if(clickedButton->objectName()=="enterButton"){
        key=Qt::Key_Return;
    }

    if(shiftIndicator==true)
        modifiers=modifiers | Qt::ShiftModifier;
    if(ctrlIndicator==true)
        modifiers=modifiers | Qt::ControlModifier;
    if(altIndicator==true)
        modifiers=modifiers | Qt::AltModifier;

    QByteArray data;
    QDataStream streamOut(&data, QIODevice::WriteOnly);
    streamOut << mode1;
    streamOut << key;
    streamOut << modifiers;
    streamOut << keyPressed;

    tcpSocket->write(data);

}

void RemoteClient::shiftButtonIndicator(){
     if(shiftIndicator==true){
         shiftIndicator=false;
         ui->shiftButton->setStyleSheet("background-color: none");
     }
     else{
         shiftIndicator=true;
         ui->shiftButton->setStyleSheet("background-color: purple;color: white");
     }
 }

 void RemoteClient::altButtonIndicator(){
     if(altIndicator==true){
              altIndicator=false;
              ui->altButton->setStyleSheet("background-color: none");
          }
          else{
              altIndicator=true;
              ui->altButton->setStyleSheet("background-color: purple;color: white");
          }
 }

 void RemoteClient::ctrlButtonIndicator(){
     if(ctrlIndicator==true){
         ctrlIndicator=false;
         ui->ctrlButton->setStyleSheet("background-color: none");
     }
     else{
         ctrlIndicator=true;
         ui->ctrlButton->setStyleSheet("background-color: purple;color: white");
     }
 }



  void RemoteClient::sendMousePress(){
      QPushButton *clickedButton=qobject_cast<QPushButton *>(sender());
      quint8 key;
      bool keyPressed = true;
      if(clickedButton->objectName()=="leftClicked"){
          key = 1;
      }
      else if(clickedButton->objectName()=="rightClicked"){
          key = (quint8)2;
      }

      quint8 mode1 = 2;
      quint8 mode2 = 1;
      QByteArray data;
      QDataStream streamOut(&data, QIODevice::WriteOnly);
      streamOut << mode1;
      streamOut << mode2;
      streamOut << key;
      streamOut << keyPressed;
      udpSocket->writeDatagram(data, tcpSocket->peerAddress(),5600);
  }

  void RemoteClient::sendMouseRelease(){
      QPushButton *clickedButton=qobject_cast<QPushButton *>(sender());
      quint8 key;
      bool keyPressed = false;

      if(clickedButton->objectName()=="leftClicked"){
          key = 1;
      }
      else if(clickedButton->objectName()=="rightClicked"){
          key = 2;
      }

      quint8 mode1 = 2;
      quint8 mode2 = 1;
      QByteArray data;
      QDataStream streamOut(&data, QIODevice::WriteOnly);
      streamOut << mode1;
      streamOut << mode2;
      streamOut << key;
      streamOut << keyPressed;

      udpSocket->writeDatagram(data, tcpSocket->peerAddress(),5600);
  }

  void RemoteClient::sendMouseMove(const QPointF &delta)
  {

      if(delta == QPointF(0,0))
              return;

      quint8 mode1 = 2;
      quint8 mode2 = 0;

      QByteArray data;
      QDataStream streamOut(&data, QIODevice::WriteOnly);

      streamOut << mode1;
      streamOut << mode2;
      streamOut << delta;

      udpSocket->writeDatagram(data, tcpSocket->peerAddress(), 5600);

  }
