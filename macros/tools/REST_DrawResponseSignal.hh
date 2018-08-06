#include "TRestTask.h"
#include "TRestSignal.h"
Int_t REST_Tools_DrawResponseSignal( TString fName )
{
    TFile *f = new TFile( fName );

    TRestSignal *signal = new TRestSignal();
    signal = (TRestSignal *) f->Get("signal Response" );

    TCanvas *c = new TCanvas();
    TGraph *gr = signal->GetGraph();

    gr->Draw();

    return 0;
}