#ifndef tthAnalysis_HiggsToTauTau_GenHadTau_h
#define tthAnalysis_HiggsToTauTau_GenHadTau_h

#include "tthAnalysis/HiggsToTauTau/interface/GenParticle.h" // GenParticle

class GenHadTau
  : public GenParticle
{
 public:
  GenHadTau() = default;
  GenHadTau(Double_t pt,
	    Double_t eta,
	    Double_t phi,
	    Double_t mass);
};

#endif // tthAnalysis_HiggsToTauTau_GenHadTau_h