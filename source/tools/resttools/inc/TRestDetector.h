////////////////////////////////////////////////////////////////////////////////////
///
///
///             RESTSoft : Software for Rare Event Searches with TPCs
///
///             TRestDetector.h
///
///             Metadata class to be used to store basic detector setup info
///             inherited from TRestMetadata
///
///             jun 2016:   First concept. Javier Galan
///
////////////////////////////////////////////////////////////////////////////////////

#ifndef RestCore_TRestDetector
#define RestCore_TRestDetector

#include <Rtypes.h>
#include <TVector3.h>
#include <stdio.h>
#include <stdlib.h>

#include <cstdio>
#include <cstring>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "TRestStringOutput.h"
#include "TRestTools.h"

using namespace std;

class TRestDetector {
   protected:
    string fDetectorName;
    Int_t fRunNumber;

   public:
    // Constructors
    TRestDetector() {}
    // Destructor
    ~TRestDetector() {}

    // Utility methods
    string GetDetectorName() { return fDetectorName; }
    Int_t GetRunNumber() { return fRunNumber; }
    void SetRunNumber(Int_t run) { fRunNumber = run; }
    virtual void RegisterMetadata(TObject* ptr) {}
    virtual void RegisterString(string str) {}
    virtual void Print() {}

    //////// Field property ////////
    virtual TVector3 GetDriftField(TVector3 pos) { return TVector3(); }
    virtual TVector3 GetAmplificationField(TVector3 pos) { return TVector3(); }
    virtual Double_t GetDriftField() { return 0; }
    virtual Double_t GetAmplificationField() { return 0; }

    //////// Medium property ////////
    virtual string GetMediumName() { return ""; }
    virtual Double_t GetPressure() { return 0; }
    virtual Double_t GetTemperature() { return 0; }
    virtual Double_t GetWvalue() { return 0; }
    virtual Double_t GetDriftVelocity() { return 0; }
    virtual Double_t GetElectronLifeTime() { return 0; }
    virtual Double_t GetLongitudinalDiffusion() { return 0; }
    virtual Double_t GetTransversalDiffusion() { return 0; }

    //////// TPC geometry ////////
    virtual Double_t GetTargetMass() { return 0; }
    virtual Double_t GetTPCHeight() { return 0; }
    virtual Double_t GetTPCRadius() { return 0; }
    virtual Double_t GetTPCBottomZ() { return 0; };
    virtual Double_t GetTPCTopZ() { return 0; };
    virtual Double_t GetDriftDistance(TVector3 pos) { return 0; }
    virtual Double_t GetAmplificationDistance(TVector3 pos) { return 0; }

    //////// electronics ////////
    virtual Double_t GetDAQShapingTime() { return 0; }
    virtual Double_t GetDAQSamplingTime() { return 0; }
    virtual Double_t GetDAQDynamicRange() { return 0; }
    virtual Double_t GetDAQThreshold() { return 0; }

    //////// readout ////////
    virtual string GetReadoutName() { return ""; }
    virtual Int_t GetNReadoutModules() { return 0; }
    virtual Int_t GetNReadoutChannels() { return 0; }
    virtual Double_t GetReadoutVoltage(int id) { return 0; }
    virtual Double_t GetReadoutGain(int id) { return 0; }
    virtual TVector3 GetReadoutPosition(int id) { return TVector3(); }
    virtual TVector3 GetReadoutDirection(int id) { return TVector3(); }
    virtual Int_t GetReadoutType(int id) { return 0; }

    //////// setters for some frequent-changed parameters ////////
    virtual void SetDriftMedium(string mediumname) {}
    virtual void SetDriftField(Double_t df) {}
    virtual void SetPressure(Double_t p) {}
    virtual void SetDAQSamplingTime(Double_t st) {}
    virtual void SetElectronLifeTime(Double_t elt) {}
};

extern TRestDetector* gDetector;

#endif