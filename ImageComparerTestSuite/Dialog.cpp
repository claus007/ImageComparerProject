/*
  
Copyright 2013 Claus Ilginnis <Claus@Ilginnis.de>

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at
   
     http://www.apache.org/licenses/LICENSE-2.0
     
   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
   
   
*/

#include "Dialog.h"
#include "ui_Dialog.h"
#include <QListWidgetItem>
#include <QPainter>
#include <QDebug>
#include "ImageComparer/ImageComparer.h"

const QString g_ImagesPrefix=":/Images/";
const int g_ImageHeight=128;

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    makePicture("African-Woman_o.jpg","African-Woman_logo.jpg");
    makePicture("African-Woman_o.jpg","African-Woman_unsharp.jpg");
    makePicture("hair_left.jpg","hair_right.jpg");
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::makePicture(QString orgImage, QString newImage)
{
    QIcon image=combine(g_ImagesPrefix+orgImage,g_ImagesPrefix+newImage);

    QListWidgetItem * item= new QListWidgetItem(image,
                                                QString("%1 --> \n    %2")
                                                .arg(orgImage)
                                                .arg(newImage),
                                                ui->listWidget);

    item->setData(Qt::UserRole,QStringList() << orgImage << newImage );
}

QIcon Dialog::combine(QString orgImage, QString newImage)
{
    QImage image1(orgImage);
    QImage image2(newImage);

    // assert is ok for a test suite
    Q_ASSERT( image1.isNull() == false );
    Q_ASSERT( image2.isNull() == false );

    image1=image1.scaledToHeight(g_ImageHeight);
    image2=image2.scaledToHeight(g_ImageHeight);

    QPixmap pixmap(image1.width()+image2.width(),g_ImageHeight);

    QPainter p(&pixmap);

    p.drawImage(0,0,image1);
    p.drawImage(image1.width(),0,image2);

    p.end();

    return QIcon(pixmap);
}

void Dialog::on_listWidget_itemClicked(QListWidgetItem *item)
{
    QStringList list=item->data(Qt::UserRole).toStringList();
    Q_ASSERT( list.size() == 2);

    QString orgImage=g_ImagesPrefix+list[0];
    QString newImage=g_ImagesPrefix+list[1];

    QWidget * widget=ImageComparer::newComparer(orgImage,newImage);

    int index=ui->stackedWidget->addWidget( widget );

    ui->stackedWidget->setCurrentIndex(index);
}
