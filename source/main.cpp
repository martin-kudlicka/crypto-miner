#include <MkWidgets/MApplication>
#include "mainwindow.h"
#include <MkAnalytics/MAnalytics>

int main(int argc, char *argv[])
{
  MApplication application(argc, argv);

  mAnalytics->setId("UA-115441303-4");

  {
    QSettings settings;
    auto alpha = settings.value("maintenance/alpha").toUInt();
    if (alpha < 1)
    {
      settings.remove("miningUnits");
    }
    settings.setValue("maintenance/alpha", 1);
  }

  MainWindow mainWindow;
  mainWindow.show();

  return application.exec();
}