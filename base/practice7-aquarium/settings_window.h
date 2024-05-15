#pragma once

#include <QCoreApplication>
#include <QFormLayout>
#include <QIcon>
#include <QPushButton>
#include <QSlider>
#include <QVBoxLayout>
#include <QWidget>

#include "settings.h"

class SettingsWindow final : public QWidget {
private:
  Settings& _settings;

private:
  template<typename TSlot>
  QSlider* create_slider(const int value, const int min_value, const int max_value, TSlot slot) {
    const auto slider = new QSlider(Qt::Horizontal);
    slider->setFixedWidth(200);
    slider->setMinimum(min_value);
    slider->setMaximum(max_value);
    slider->setValue(value);

    connect(slider, &QSlider::valueChanged, this, slot);

    return slider;
  }

public:
  SettingsWindow(Settings& settings) : _settings(settings) {
    QIcon icon(QCoreApplication::applicationDirPath() + "/resources/icons/settings.png");
    setWindowIcon(icon);
    setWindowTitle(u8"Настройки");

    const auto fish_count_slider = create_slider(
      settings.fish_count(),
      Settings::FISH_COUNT_MIN,
      Settings::FISH_COUNT_MAX,
      &SettingsWindow::on_fish_count_changed
    );

    const auto speed_slider = create_slider(
      settings.speed(),
      Settings::SPEED_MIN,
      Settings::SPEED_MAX,
      &SettingsWindow::on_speed_changed
    );

    const auto form_layout = new QFormLayout();
    form_layout->addRow(u8"Количество рыб:", fish_count_slider);
    form_layout->addRow(u8"Скорость:", speed_slider);

    const auto button = new QPushButton(u8"Закрыть");
    connect(button, &QPushButton::clicked, this, &QWidget::close);

    const auto root_layout = new QVBoxLayout();
    root_layout->addLayout(form_layout);
    root_layout->addWidget(button);
    root_layout->setAlignment(button, Qt::AlignRight);
    setLayout(root_layout);

    setFixedSize(sizeHint());
  }

private slots:
  void on_fish_count_changed(int value) {
    _settings.set_fish_count(value);
  }

  void on_speed_changed(int value) {
    _settings.set_speed(value);
  }
};
