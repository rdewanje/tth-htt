#ifndef tthAnalysis_HiggsToTauTau_RecoMuon_h
#define tthAnalysis_HiggsToTauTau_RecoMuon_h

#include "tthAnalysis/HiggsToTauTau/interface/RecoLepton.h" // RecoLepton

// KE: set the following flag to 1 if the branch exists
#define DPT_DIV_PT_FLAG 0

#if DPT_DIV_PT_FLAG == 1
#define DPT_DIV_PT
#endif

class RecoMuon
  : public RecoLepton
{
public:
  RecoMuon() = default;
  RecoMuon(Double_t pt,
           Double_t eta,
           Double_t phi,
           Double_t mass,
           Int_t pdgId,
           Double_t dxy,
           Double_t dz,
           Double_t relIso,
           Double_t miniIsoCharged,
           Double_t miniIsoNeutral,
           Double_t sip3d,
           Double_t mvaRawTTH,
           Double_t jetNDauChargedMVASel,
           Double_t jetPtRel,
           Double_t jetPtRatio,
           Double_t jetBtagCSV,
           Int_t passesTightCharge,
           Int_t charge,
           Int_t passesLooseIdPOG,
           Int_t passesMediumIdPOG,
#ifdef DPT_DIV_PT
           Float_t dpt_div_pt,
#endif
           Float_t segmentCompatibility);

  /**
   * @brief Checks whether a given lepton is an electron by its PDG id
   * @return True if it is an electron; false otherwise
   */
  bool
  is_electron() const { return false; }

  /**
   * @brief Checks whether a given lepton is a muon by its PDG id
   * @return True if it is a muon; false otherwise
   */
  bool
  is_muon() const { return true; }

//--- observables specific to muons
  Int_t passesLooseIdPOG_;       ///< flag indicating if muon passes (1) or fails (0) loose PFMuon id
  Int_t passesMediumIdPOG_;      ///< flag indicating if muon passes (1) or fails (0) medium PFMuon id
#ifdef DPT_DIV_PT
  Float_t dpt_div_pt_;           ///< relative pT error
#endif
  Float_t segmentCompatibility_; ///< muon segment compatibility
};

#endif // tthAnalysis_HiggsToTauTau_RecoMuon_h

