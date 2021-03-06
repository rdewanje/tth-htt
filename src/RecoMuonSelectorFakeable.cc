#include "tthAnalysis/HiggsToTauTau/interface/RecoMuonSelectorFakeable.h" // RecoMuonSelectorFakeable

#include <cmath> // fabs

RecoMuonSelectorFakeable::RecoMuonSelectorFakeable()
  : min_pt_(10.)
  , max_absEta_(2.4)
  , max_dxy_(0.05)
  , max_dz_(0.1)
  , max_relIso_(0.4)
  , max_sip3d_(8.)
  , apply_looseIdPOG_(true)
  , binning_mvaTTH_({ 0.75 })
  , min_jetPtRatio_({ 0.30, -1.e+3 })   
  , max_jetBtagCSV_({ 0.605, 0.89 })  
  , apply_mediumIdPOG_(false)
  , apply_tightCharge_(false)
{}

bool RecoMuonSelectorFakeable::operator()(const RecoMuon& muon) const
{
  if ( muon.pt_ >= min_pt_ &&
       muon.absEta_ <= max_absEta_ &&
       std::fabs(muon.dxy_) <= max_dxy_ &&
       std::fabs(muon.dz_) <= max_dz_ &&
       muon.relIso_ <= max_relIso_ &&
       muon.sip3d_ <= max_sip3d_ &&
       (muon.passesLooseIdPOG_ || !apply_looseIdPOG_) && 
       (muon.passesMediumIdPOG_ || !apply_mediumIdPOG_) &&
       (muon.tightCharge_ >= 2 || !apply_tightCharge_) ) {
    int idxBin = -1;
    if   ( muon.mvaRawTTH_ >= binning_mvaTTH_[0] ) idxBin = 0;
    else                                           idxBin = 1;
    assert(idxBin >= 0 && idxBin <= 1);
    if ( muon.jetPtRatio_ >= min_jetPtRatio_[idxBin] &&
	 muon.jetBtagCSV_ <= max_jetBtagCSV_[idxBin] ) return true;
  }
  return false;
}
