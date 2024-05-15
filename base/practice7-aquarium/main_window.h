#pragma once

#include <QAction>
#include <QDir>
#include <QIcon>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QMainWindow>
#include <QMenuBar>
#include <QPixmap>
#include <QSize>
#include <QTimer>

#include <vector>
#include <random>

#include "settings_window.h"

class MainWindow final : public QMainWindow {
private:
  QGraphicsScene* const _scene;

public:
  MainWindow() : MainWindow(QSize(1024, 768), QSize(64, 64)) {}

  MainWindow(const QSize max_background_size, const QSize max_fish_size) :
    _scene(new QGraphicsScene())
  {
    setWindowIcon(QIcon(QCoreApplication::applicationDirPath() + "/resources/icons/aquarium.png"));
    setWindowTitle(u8"Аквариум");

    QPixmap background(QCoreApplication::applicationDirPath() + "/resources/background.png");
    background = background.scaled(max_background_size, Qt::AspectRatioMode::KeepAspectRatio);
    _scene->addItem(new QGraphicsPixmapItem(background));

    const auto scene_view = new QGraphicsView();
    scene_view->setScene(_scene);
    scene_view->setFrameShape(QFrame::Shape::NoFrame);
    scene_view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scene_view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    setCentralWidget(scene_view);

    setFixedSize(sizeHint());
  }
};
