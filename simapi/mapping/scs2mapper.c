#include <stddef.h>
#include <math.h>
#include <string.h>

#include "../simmap.h"
#include "../simdata.h"
#include "../simapi.h"
#include "../simmapper.h"
#include "../scs2.h"

#include "../../include/scs2data.h"

static int droundint(double d)
{
    return trunc(nearbyint(d));
}

void map_trucks_data(SimData* simdata, SimMap* simmap)
{
    const char* a = simmap->d.scs2.telemetry_map_addr;
    // char* b;
    // char* c;
    // char* d;

    memset(simdata, 0, sizeof(SimData));

    simdata->simstatus = 2;

    strncpy(simdata->car, a + offsetof(struct scs2TelemetryMap_s, config_s.truckName), sizeof(simdata->car)-1);


    simdata->velocity = droundint(3.6 * (*(float*) (char*) (a + offsetof(struct scs2TelemetryMap_s, truck_f.speed))));
    simdata->rpms = droundint(*(float*) (char*) (a + offsetof(struct scs2TelemetryMap_s, truck_f.engineRpm)));
    simdata->brake = droundint(*(float*) (char*) (a + offsetof(struct scs2TelemetryMap_s, truck_f.userBrake)));
    simdata->gas = droundint(*(float*) (char*) (a + offsetof(struct scs2TelemetryMap_s, truck_f.userThrottle)));
    simdata->gear = *(uint32_t*) (char*) (a + offsetof(struct scs2TelemetryMap_s, truck_i.gear));
    simdata->tyreRPS[0] = *(float*) (char*) (a + offsetof(struct scs2TelemetryMap_s, truck_f.truck_wheelVelocity));
    simdata->tyreRPS[1] = *(float*) (char*) (a + offsetof(struct scs2TelemetryMap_s, truck_f.truck_wheelVelocity) + (sizeof(float) * 1));
    simdata->tyreRPS[2] = *(float*) (char*) (a + offsetof(struct scs2TelemetryMap_s, truck_f.truck_wheelVelocity) + (sizeof(float) * 2));
    simdata->tyreRPS[3] = *(float*) (char*) (a + offsetof(struct scs2TelemetryMap_s, truck_f.truck_wheelVelocity) + (sizeof(float) * 3));
    simdata->maxrpm = droundint( *(float*) (char*) (a + offsetof(struct scs2TelemetryMap_s, config_f.engineRpmMax)));
    simdata->fuel = *(float*)(a + offsetof(struct scs2TelemetryMap_s, truck_f.fuel));

    if(simdata->gear>0)
    {
        simdata->gearc[0] = (simdata->gear/2) + 48;
        if(simdata->gear % 2 == 0)
        {
            simdata->gearc[1] = 72;
        }
        else
        {
            simdata->gearc[1] = 76;
            simdata->gearc[0]++;
        }
        simdata->gearc[2] = 0;
    }
    else
    {
        if (simdata->gear < 0)
        {
            simdata->gearc[0] = 82;
        }
        if (simdata->gear == 0)
        {
            simdata->gearc[0] = 78;
        }
        simdata->gearc[1] = 0;
    }

    simdata->altitude = 1;

}
