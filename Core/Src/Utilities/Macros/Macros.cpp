#include "Macros.hh"

void setSystemstatus(const char *msg, const bool &condition)
{
    try
    {
        if(condition)
        {
            throw(msg);
        }
    }
    catch(char *msg)
    {
        systemStatus = msg;
    }
    
}
