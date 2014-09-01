#include "EvApplicationArgumentsManager.h"

EvApplicationArgumentsManager::EvApplicationArgumentsManager(){}


QStringList EvApplicationArgumentsManager::options()const
{
    return m_options.keys();
}
void EvApplicationArgumentsManager::parseArguments(const QStringList & args)
{
    QString currentOption;
    QStringList currentOptionArgs;
    foreach(const QString & arg,args)
    {
        if(arg.startsWith('-'))
        {
            if(!currentOption.isEmpty())
            {
                m_options.insert(currentOption,currentOptionArgs);
            }
            currentOption = arg;
            currentOptionArgs.clear();
        }
        else
            currentOptionArgs<<arg;
    }
    if(!currentOption.isEmpty())
    {
        m_options.insert(currentOption,currentOptionArgs);
    }
}

bool EvApplicationArgumentsManager::containsOption(const QString & option)const
{
    return m_options.contains(option);
}
QStringList EvApplicationArgumentsManager::optionArguments(const QString & option)const
{
    return m_options.value(option);
}
int EvApplicationArgumentsManager::optionArgumentsSize(const QString & option)
{
    if(!m_options.contains(option))
        return -1;
    return m_options.value(option).size();
}
