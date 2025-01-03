#ifndef STATUS_STATUSMANAGER_H
#define STATUS_STATUSMANAGER_H

#include "Status.h"
#include "logging/Logger.h"

namespace SlimeVR
{
    namespace Status
    {
        class StatusManager
        {
        public:
            void setStatus(Status status, bool value);
            bool hasStatus(Status status);
            uint32_t getStatus() {
                return m_Status;
            };

            void setActivityTime(uint32_t time) {   m_ActivityTime = time;      m_Logger.info("Activity time updated: %dms", m_ActivityTime);      };
            uint32_t getActivityTime()          {   return m_ActivityTime;      };

        private:
            uint32_t m_Status;
            uint32_t m_ActivityTime;

            Logging::Logger m_Logger = Logging::Logger("StatusManager");
        };
    }
}

#endif
