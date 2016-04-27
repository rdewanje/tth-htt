#ifndef SYNCNTUPLEMANAGER_H
#define SYNCNTUPLEMANAGER_H

#include <string> // std::string
#include <vector> // std::vector<>

#include <TFile.h> // TFile
#include <TTree.h> // TTree
#include <Rtypes.h> // Float_t, Int_t

#include "tthAnalysis/HiggsToTauTau/interface/RecoMuon.h"
#include "tthAnalysis/HiggsToTauTau/interface/RecoElectron.h"
#include "tthAnalysis/HiggsToTauTau/interface/RecoHadTau.h"
#include "tthAnalysis/HiggsToTauTau/interface/RecoJet.h"

template <typename T>
struct Traits
{
  static const char * TYPE_NAME;
};

template <typename T> const char * Traits<T>::TYPE_NAME = "unknown";

#define DECLARE_TYPE_TRAIT(type,name) template <> const char * Traits<type>::TYPE_NAME = name;

DECLARE_TYPE_TRAIT(Char_t, "B")
DECLARE_TYPE_TRAIT(UChar_t, "b")
DECLARE_TYPE_TRAIT(Short_t, "S")
DECLARE_TYPE_TRAIT(UShort_t, "s")
DECLARE_TYPE_TRAIT(Int_t, "I")
DECLARE_TYPE_TRAIT(Int_t *, "I")
DECLARE_TYPE_TRAIT(UInt_t, "i")
DECLARE_TYPE_TRAIT(Float_t, "F")
DECLARE_TYPE_TRAIT(Float_t *, "F")
DECLARE_TYPE_TRAIT(Double_t, "D")
DECLARE_TYPE_TRAIT(Long64_t, "L")
DECLARE_TYPE_TRAIT(ULong64_t, "l")
DECLARE_TYPE_TRAIT(Bool_t, "o")

class SyncNtupleManager
{
public:
  SyncNtupleManager(const std::string & outputFileName,
                    const std::string & outputTreeName);
  ~SyncNtupleManager();

  void initializeBranches();
  void read(std::vector<const RecoMuon *> & muons);
  void read(std::vector<const RecoElectron *> & electrons);
  void read(std::vector<const RecoHadTau *> & hadtaus);
  void read(std::vector<const RecoJet *> & jets);
  void fill();
  void write();
private:
  void reset(bool is_initializing);

  TFile * outputFile;
  TTree * outputTree;
  const Int_t placeholder_value;

  const Int_t nof_mus;
  const Int_t nof_eles;
  const Int_t nof_taus;
  const Int_t nof_jets;

  ULong64_t nEvent;
  UInt_t ls;
  UInt_t run;

  Int_t n_presel_mu;
  Int_t n_fakeablesel_mu; // will implement in a moment
  Int_t n_cutsel_mu; // will implement in a moment
  Int_t n_mvasel_mu; // will implement in a moment
  Float_t * mu_pt;
  Float_t * mu_eta;
  Float_t * mu_phi;
  Float_t * mu_E;
  Int_t * mu_charge;
  Float_t * mu_miniRelIso;
  Float_t * mu_miniIsoCharged; // missing
  Float_t * mu_miniIsoNeutral; // missing
  Int_t * mu_jetNDauChargedMVASel; // missing
  Float_t * mu_jetPtRel; // missing
  Float_t * mu_jetPtRatio;
  Float_t * mu_jetCSV;
  Float_t * mu_sip3D;
  Float_t * mu_dxy;
  Float_t * mu_dz;
  Float_t * mu_segmentCompatibility; // missing
  Float_t * mu_leptonMVA;
  Float_t * mu_mediumID; // type ? missing
  Float_t * mu_dpt_div_pt; // ? missing
  Int_t * mu_isfakeablesel; // missing; difficult to implement
  Int_t * mu_iscutsel; // missing; difficult to implement
  Int_t * mu_ismvasel; // missing; difficult to implement

  Int_t n_presel_ele;
  Int_t n_fakeablesel_ele; // will implement in a moment
  Int_t n_cutsel_ele; // will implement in a moment
  Int_t n_mvasel_ele; // will implement in a moment
  Float_t * ele_pt;
  Float_t * ele_eta;
  Float_t * ele_phi;
  Float_t * ele_E;
  Int_t * ele_charge;
  Float_t * ele_miniRelIso;
  Float_t * ele_miniIsoCharged; // missing
  Float_t * ele_miniIsoNeutral; // missing
  Int_t * ele_jetNDauChargedMVASel; // missing
  Float_t * ele_jetPtRel; // missing
  Float_t * ele_jetPtRatio;
  Float_t * ele_jetCSV;
  Float_t * ele_sip3D;
  Float_t * ele_dxy;
  Float_t * ele_dz;
  Float_t * ele_ntMVAeleID;
  Float_t * ele_leptonMVA;
  Float_t * ele_isChargeConsistent; // type ? missing
  Float_t * ele_passesConversionVeto; // type ?
  Int_t * ele_nMissingHits; // double-check the branch
  Int_t * ele_isfakeablesel; // missing; difficult to implement
  Int_t * ele_iscutsel; // missing; difficult to implement
  Int_t * ele_ismvasel; // missing; difficult to implement

  Int_t n_presel_tau;
  Float_t * tau_pt;
  Float_t * tau_eta;
  Float_t * tau_phi;
  Float_t * tau_E;
  Int_t * tau_charge;
  Float_t * tau_dxy; // missing
  Float_t * tau_dz;
  Int_t * tau_decayModeFindingOldDMs;
  Int_t * tau_decayModeFindingNewDMs;
  Int_t * tau_byCombinedIsolationDeltaBetaCorr3Hits; // Float_t ?
  Int_t * tau_byLooseCombinedIsolationDeltaBetaCorr3Hits;
  Int_t * tau_byMediumCombinedIsolationDeltaBetaCorr3Hits;
  Int_t * tau_byTightCombinedIsolationDeltaBetaCorr3Hits;
  Int_t * tau_byLooseCombinedIsolationDeltaBetaCorr3HitsdR03;
  Int_t * tau_byMediumCombinedIsolationDeltaBetaCorr3HitsdR03;
  Int_t * tau_byTightCombinedIsolationDeltaBetaCorr3HitsdR03;
  Int_t * tau_byLooseIsolationMVArun2v1DBdR03oldDMwLT;
  Int_t * tau_byMediumIsolationMVArun2v1DBdR03oldDMwLT;
  Int_t * tau_byTightIsolationMVArun2v1DBdR03oldDMwLT;
  Int_t * tau_byVTightIsolationMVArun2v1DBdR03oldDMwLT;
  Int_t * tau_againstMuonLoose3;
  Int_t * tau_againstMuonTight3;
  Int_t * tau_againstElectronVLooseMVA6;
  Int_t * tau_againstElectronLooseMVA6;
  Int_t * tau_againstElectronMediumMVA6;
  Int_t * tau_againstElectronTightMVA6;

  Int_t n_presel_jet;
  Float_t * jet_pt;
  Float_t * jet_eta;
  Float_t * jet_phi;
  Float_t * jet_E;
  Float_t * jet_CSV;

  Float_t PFMET;
  Float_t PFMETphi;
  Float_t MHT;
  Float_t metLD;

  Float_t lep0_conept; // missing
  Float_t lep1_conePt; // missing
  Float_t mindr_lep0_jet; // missing
  Float_t mindr_lep1_jet; // missing
  Float_t MT_met_lep0; // missing
  Float_t avg_dr_jet; // missing
  Float_t MVA_2lss_ttV; // missing
  Float_t MVA_2lss_ttbar; // missing
};

#endif // SYNCNTUPLEMANAGER_H