#include "tthAnalysis/HiggsToTauTau/interface/RecoHadTauSelectorTight.h" // RecoHadTauSelectorTight

#include <cmath> // fabs

RecoHadTauSelectorTight::RecoHadTauSelectorTight()
  : min_pt_(20.)
  , max_absEta_(2.3)
  , max_dz_(0.2)
  , min_decayModeFinding_(1)
  , min_id_mva_dR03_(-1000)
  , min_raw_mva_dR03_(-1.e+6)
  , min_id_mva_dR05_(-1000)
  , min_raw_mva_dR05_(-1.e+6)
  , min_id_cut_dR03_(-1000)
  , max_raw_cut_dR03_(1.e+6)
  , min_id_cut_dR05_(1) // HPS combined isolation 3-hit loose
  , max_raw_cut_dR05_(1.e+6) 
  , min_antiElectron_(-1000)
  , min_antiMuon_(-1000)   
{}

bool RecoHadTauSelectorTight::operator()(const RecoHadTau& hadTau) const
{
  if ( hadTau.pt_ >= min_pt_ &&
       hadTau.absEta_ <= max_absEta_ &&
       std::fabs(hadTau.dz_) <= max_dz_ &&
       hadTau.decayModeFinding_ >= min_decayModeFinding_ &&
       hadTau.id_mva_dR03_ >= min_id_mva_dR03_ &&
       hadTau.raw_mva_dR03_ >= min_raw_mva_dR03_ &&
       hadTau.id_mva_dR05_ >= min_id_mva_dR05_ &&
       hadTau.raw_mva_dR05_ >= min_raw_mva_dR05_ &&
       hadTau.id_cut_dR03_ >= min_id_cut_dR03_ &&
       hadTau.raw_cut_dR03_ <= max_raw_cut_dR03_ &&
       hadTau.id_cut_dR05_ >= min_id_cut_dR05_ &&
       hadTau.raw_cut_dR05_ <= max_raw_cut_dR05_ &&
       hadTau.antiElectron_ >= min_antiElectron_ &&
       hadTau.antiMuon_ >= min_antiMuon_ ) {
    return true;
  } 
  return false;
}
