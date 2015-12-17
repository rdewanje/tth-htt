#include "tthAnalysis/HiggsToTauTau/interface/RecoLepton.h"

#include <cmath> // std::abs()

RecoLepton::RecoLepton(Double_t _dxy,
                       Double_t _dz,
                       Double_t _rel_iso,
                       Double_t _sip3d,
                       Double_t _mass,
                       Double_t _pt,
                       Double_t _eta,
                       Double_t _mva_tth,
                       Double_t _phi,
                       Int_t _pdg_id,
                       Int_t _med_mu_id,
                       Int_t _ele_mva_id,
                       Int_t _lost_hits,
                       Int_t _loose_id,
                       Int_t _tight_charge,
                       Int_t _pass_conv_veto)
  : dxy(_dxy)
  , dz(_dz)
  , rel_iso(_rel_iso)
  , sip3d(_sip3d)
  , mass(_mass)
  , pt(_pt)
  , eta(_eta)
  , mva_tth(_mva_tth)
  , phi(_phi)
  , pdg_id(_pdg_id)
  , med_mu_id(_med_mu_id)
  , ele_mva_id(_ele_mva_id)
  , lost_hits(_lost_hits)
  , loose_id(_loose_id)
  , tight_charge(_tight_charge)
  , pass_conv_veto(_pass_conv_veto)
{
  p4 = math::PtEtaPhiMLorentzVector(pt, eta, phi, mass);
}

bool
RecoLepton::is_electron() const
{
  return std::abs(pdg_id) == 11;
}

bool
RecoLepton::is_muon() const
{
  return std::abs(pdg_id) == 13;
}