#ifndef OPTIONS_H
#define OPTIONS_H

#include <MkCore/MSettings>
#include <MkCore/MLazySingleton>

class Options : public MSettings
{
  public:
    struct Property
    {
      static Q_DECL_CONSTEXPR QString Console_OutputLinesInMemory;
      static Q_DECL_CONSTEXPR QString Startup_MineOnStartup;
    };

             Options();
    virtual ~Options() Q_DECL_OVERRIDE Q_DECL_EQ_DEFAULT;

    qintptr consoleOutputLinesInMemory() const;
    bool    mineOnStartup             () const;
};

extern MLazySingleton<Options> gOptions;

#endif