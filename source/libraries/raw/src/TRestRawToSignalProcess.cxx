///______________________________________________________________________________
///______________________________________________________________________________
///______________________________________________________________________________
///
///
///             RESTSoft : Software for Rare Event Searches with TPCs
///
///             TRestRawToSignalProcess.cxx
///
///             Template to use to design "event process" classes inherited from
///             TRestRawToSignalProcess
///             How to use: replace TRestRawToSignalProcess by your name,
///             fill the required functions following instructions and add all
///             needed additional members and funcionality
///
///             jun 2014:   First concept
///                 Created as part of the conceptualization of existing REST
///                 software.
///                 Igor G. Irastorza
///_______________________________________________________________________________

#include "TRestRawToSignalProcess.h"

#include <sys/stat.h>
using namespace std;
#include "TTimeStamp.h"

ClassImp(TRestRawToSignalProcess)
    //______________________________________________________________________________
    TRestRawToSignalProcess::TRestRawToSignalProcess() {
    Initialize();
}

TRestRawToSignalProcess::TRestRawToSignalProcess(char* cfgFileName) {
    Initialize();

    if (LoadConfigFromFile(cfgFileName)) LoadDefaultConfig();
}

//______________________________________________________________________________
TRestRawToSignalProcess::~TRestRawToSignalProcess() {
    // TRestRawToSignalProcess destructor
    if (fSignalEvent) delete fSignalEvent;
}

void TRestRawToSignalProcess::LoadConfig(string cfgFilename, string name) {
    if (LoadConfigFromFile(cfgFilename, name) == -1) {
        cout << "Loading default" << endl;
        LoadDefaultConfig();
    }
}

//______________________________________________________________________________
void TRestRawToSignalProcess::Initialize() {
    SetSectionName(this->ClassName());

    if (fSignalEvent) delete fSignalEvent;
    fSignalEvent = new TRestRawSignalEvent();

    fInputBinFile = NULL;

    fMinPoints = 512;

    fSingleThreadOnly = true;
    fIsExternal = true;

    totalBytes = 0;
    totalBytesReaded = 0;
}

void TRestRawToSignalProcess::InitFromConfigFile() {
    fElectronicsType = GetParameter("electronics");
    fShowSamples = StringToInteger(GetParameter("showSamples", "10"));
    fMinPoints = StringToInteger(GetParameter("minPoints", "512"));

    PrintMetadata();

    if (fElectronicsType == "SingleFeminos" || fElectronicsType == "TCMFeminos") return;

    if (GetVerboseLevel() >= REST_Warning) {
        cout << "REST WARNING: TRestRawToSignalProcess::InitFromConfigFile" << endl;
        cout << "Electronic type " << fElectronicsType << " not found " << endl;
        // cout << "Loading default config" << endl;
    }

    LoadDefaultConfig();
}

void TRestRawToSignalProcess::LoadDefaultConfig() {
    // if (GetVerboseLevel() <= REST_Warning) {
    //    cout << "REST WARNING: TRestRawToSignalProcess " << endl;
    //    cout << "Error Loading config file " << endl;
    //}

    // if (GetVerboseLevel() >= REST_Debug) GetChar();

    fElectronicsType = "SingleFeminos";
    fMinPoints = 512;
}

//______________________________________________________________________________
void TRestRawToSignalProcess::EndProcess() {
    // close binary file??? Already done
}

Bool_t TRestRawToSignalProcess::OpenInputFiles(vector<string> files) {
    nFiles = 0;
    // for (auto a : fInputFiles) { delete a; }
    fInputFiles.clear();
    fInputFileNames.clear();
    totalBytes = 0;
    totalBytesReaded = 0;

    for (int i = 0; i < files.size(); i++) {
        FILE* f = fopen(files[i].c_str(), "rb");

        if (f == NULL) {
            warning << "REST WARNING. Input file for " << this->ClassName() << " does not exist!" << endl;
            warning << "File : " << files[i] << endl;
            continue;
        }

        fInputFiles.push_back(f);
        fInputFileNames.push_back(files[i]);

        struct stat statbuf;
        stat(files[i].c_str(), &statbuf);
        totalBytes += statbuf.st_size;

        nFiles++;
    }

    if (nFiles > 0) {
        fInputBinFile = fInputFiles[0];
    } else {
        ferr << "No input file is opened, in process: " << this->ClassName() << "!" << endl;
        exit(1);
    }

    debug << this->GetName() << " : opened " << nFiles << " files" << endl;
    return nFiles;
}

// For debugging
void TRestRawToSignalProcess::printBits(unsigned short num) {
    for (unsigned short bit = 0; bit < (sizeof(unsigned short) * 8); bit++) {
        printf("%i ", num & 0x01);
        num = num >> 1;
    }

    printf("\n");
}

// For debugging
void TRestRawToSignalProcess::printBits(unsigned int num) {
    for (unsigned int bit = 0; bit < (sizeof(unsigned int) * 8); bit++) {
        printf("%i ", num & 0x01);
        num = num >> 1;
    }

    printf("\n");
}

void TRestRawToSignalProcess::PrintMetadata() {
    BeginPrintProcess();

    metadata << " " << endl;
    metadata << " ==================================== " << endl;
    metadata << "DAQ : " << GetTitle() << endl;
    metadata << "Electronics type : " << fElectronicsType << endl;
    metadata << "Minimum number of points : " << fMinPoints << endl;
    metadata << " ==================================== " << endl;

    metadata << " " << endl;

    EndPrintProcess();
}