/* ========================================================================== */
/*                                                                            */
/*   Test.cpp                                                                 */
/*   (c) 2024 Author f.Pucci                                                  */
/*                                                                            */
/*   Description                                                              */
/*     Linux test for AriannaDLL (libarianna.so)                              */
/* ========================================================================== */
#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>
#include <string.h>
#include <iostream>

int main(int argc, char *argv[])
{
    bool use_fabrizio_test = false; // change this when using Fabrizio's test data
    const char *input_file = use_fabrizio_test ? "./data/fabrizio/input_raw.74h" : "./data/custom/input_thesia.74h";
    const char *output_file = use_fabrizio_test ? "./data/fabrizio/output_in_coords.txt" : "./data/custom/output_in_coords.txt";

    void *handle;
    int *iptr,
        (*getAriannaPostprocVersion)(),
        (*initAriannaLib)(),
        (*initAriannaPath)(int op, int winStepNum98h, int calPeriod98h),
        (*freeAriannaPath)(int op),
        (*freeAriannaAllPath)(),
        (*getAriannanStep)(int op),
        (*getAriannanMsg)(int op),
        (*setAriannaMessage)(int op, char *messageHex);

    float *(*getAriannaPath)(int op, float X0, float Y0, float rotation, float deskewingT, float deskewingS, int type);

    double *(*getAriannaPath_GPS)(int op, float X0, float Y0, float rotation, float deskewingT, float deskewingS, int type, double lat0, double lon0);

    int ret = 1;
    int id = 1; // operator id = 1 !!!!!!
    char messageHex[200];
    FILE *pf = NULL;
    FILE *pfout = NULL;

    printf("Linux test for AriannaDLL (libarianna.so)\n");

    /// PAY ATTENTION
    /// id is the device id. In this example id ia 1. look at the 74h messages for the id value
    /// #010000000000B9000000000000000000000000000000000000000000000100000000F934 -> #01 -> id = 1
    /// PAY ATTENTION

    pf = fopen(input_file, "r");
    if (pf == NULL)
    {
        fprintf(stderr, "Error opening input file: %s\n", input_file);
        return 1;
    }

    pfout = fopen(output_file, "w");
    if (pfout == NULL)
    {
        fprintf(stderr, "Error opening output file: %s\n", output_file);
        fclose(pf);
        return 1;
    }

    /* open the needed object */
    handle = dlopen("./lib/libarianna.so", RTLD_LOCAL | RTLD_LAZY);

    /* find the address of function and data objects */
    *(void **)(&getAriannaPostprocVersion) = dlsym(handle, "getAriannaPostprocVersion");
    *(void **)(&initAriannaLib) = dlsym(handle, "initAriannaLib");
    *(void **)(&initAriannaPath) = dlsym(handle, "initAriannaPath");
    *(void **)(&setAriannaMessage) = dlsym(handle, "setAriannaMessage");
    *(void **)(&freeAriannaPath) = dlsym(handle, "freeAriannaPath");
    *(void **)(&freeAriannaAllPath) = dlsym(handle, "freeAriannaAllPath");
    *(void **)(&getAriannanStep) = dlsym(handle, "getAriannanStep");
    *(void **)(&getAriannanMsg) = dlsym(handle, "getAriannanMsg");
    *(void **)(&getAriannanMsg) = dlsym(handle, "getAriannanMsg");
    *(void **)(&getAriannaPath) = dlsym(handle, "getAriannaPath");
    *(void **)(&getAriannaPath_GPS) = dlsym(handle, "getAriannaPath_GPS");

    /* invoke function, passing value of integer as a parameter */
    if (getAriannaPostprocVersion != NULL)
    {
        int ret1 = initAriannaLib();
        int ret2 = initAriannaPath(id, 0, 0);
        int ret3 = 0;
        int version = (*getAriannaPostprocVersion)();

        printf("libarianna.so Linux Version : 0x%04x\n", version);
        printf("Init result :%d/%d\n", ret1, ret2);

        while (!feof(pf))
        {
            fscanf(pf, "%s\n", messageHex);
            if (messageHex[0] == '#')
            {
                //              printf("%s\n",messageHex);
                ret3 = setAriannaMessage(id, messageHex);
            }
        }
        int nStep = getAriannanStep(id);
        int nMsg = getAriannanMsg(id);
        printf("nStep/nMsg :%d/%d\n", nStep, nMsg);

        float x0 = 0;    // X offset of the starting point in meters
        float y0 = 0;    // Y offset of the starting point in meters
        float rot = 0;   // track rotation in radiants
        float corrT = 0; // correction smal values usually in a rangge close to 1e-5
        float corrW = 0; // correction (let 0) !!!

        double startCoord[2] = {
            use_fabrizio_test ? 41.878969366803155 : 47.615030999999995, // Rome
            use_fabrizio_test ? 12.508015473880215 : -122.177495         // Bellevue
        };

        double *vector;

        bool is_using_lat_long = true;
        if (is_using_lat_long)
            vector = getAriannaPath_GPS(id, x0, y0, rot, corrT, corrW, 1, startCoord[0], startCoord[1]); // in Lat,Lon
        else
            vector = (double *)getAriannaPath(id, x0, y0, rot, corrT, corrW, 1); // in meters

        for (int i = 0; i < nMsg; i++)
        {
            fprintf(pfout, "%f,%f\n", -vector[i], vector[nMsg + i]);
        }
        std::cout << "\n✨ Wrote to " << output_file << std::endl;
        ret = 0;
    }
    else
    {
        printf("\nAriannalib: Something went wrong.\n\n");
    }
    freeAriannaPath(id);
    freeAriannaAllPath();
    fclose(pf);
    fclose(pfout);
    return ret;
}
