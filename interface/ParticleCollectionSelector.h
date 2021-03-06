#ifndef tthAnalysis_HiggsToTauTau_ParticleCollectionSelector_h
#define tthAnalysis_HiggsToTauTau_ParticleCollectionSelector_h

template <typename Tobj, typename Tsel>
class ParticleCollectionSelector
{
 public:
  ParticleCollectionSelector() {}
  ~ParticleCollectionSelector() {}

  /**
   * @brief Select subset of particles passing selection, by applying selector specified as template parameter to each particle in collection passed as function argument
   * @return Collection of selected particles
   */
  std::vector<const Tobj*> operator()(const std::vector<const Tobj*>& particles) const
  {
    std::vector<const Tobj*> selParticles;
    for ( typename std::vector<const Tobj*>::const_iterator particle = particles.begin();
	  particle != particles.end(); ++particle ) {
      if ( selector_(**particle) ) {
	selParticles.push_back(*particle);
      }
    }
    return selParticles;
  }
  
 protected: 
  Tsel selector_;
};

#include "tthAnalysis/HiggsToTauTau/interface/RecoElectron.h"
#include "tthAnalysis/HiggsToTauTau/interface/RecoElectronSelectorLoose.h"
#include "tthAnalysis/HiggsToTauTau/interface/RecoElectronSelectorTight.h"
#include "tthAnalysis/HiggsToTauTau/interface/RecoElectronSelectorFakeable.h"
#include "tthAnalysis/HiggsToTauTau/interface/RecoElectronSelectorCutBased.h"
#include "tthAnalysis/HiggsToTauTau/interface/RecoElectronSelectorMVABased.h"

typedef ParticleCollectionSelector<RecoElectron, RecoElectronSelectorLoose> RecoElectronCollectionSelectorLoose;
typedef ParticleCollectionSelector<RecoElectron, RecoElectronSelectorTight> RecoElectronCollectionSelectorTight;
typedef ParticleCollectionSelector<RecoElectron, RecoElectronSelectorFakeable> RecoElectronCollectionSelectorFakeable;
typedef ParticleCollectionSelector<RecoElectron, RecoElectronSelectorCutBased> RecoElectronCollectionSelectorCutBased;
typedef ParticleCollectionSelector<RecoElectron, RecoElectronSelectorMVABased> RecoElectronCollectionSelectorMVABased;

#include "tthAnalysis/HiggsToTauTau/interface/RecoMuon.h"
#include "tthAnalysis/HiggsToTauTau/interface/RecoMuonSelectorLoose.h"
#include "tthAnalysis/HiggsToTauTau/interface/RecoMuonSelectorTight.h"
#include "tthAnalysis/HiggsToTauTau/interface/RecoMuonSelectorFakeable.h"
#include "tthAnalysis/HiggsToTauTau/interface/RecoMuonSelectorCutBased.h"
#include "tthAnalysis/HiggsToTauTau/interface/RecoMuonSelectorMVABased.h"

typedef ParticleCollectionSelector<RecoMuon, RecoMuonSelectorLoose> RecoMuonCollectionSelectorLoose;
typedef ParticleCollectionSelector<RecoMuon, RecoMuonSelectorTight> RecoMuonCollectionSelectorTight;
typedef ParticleCollectionSelector<RecoMuon, RecoMuonSelectorFakeable> RecoMuonCollectionSelectorFakeable;
typedef ParticleCollectionSelector<RecoMuon, RecoMuonSelectorCutBased> RecoMuonCollectionSelectorCutBased;
typedef ParticleCollectionSelector<RecoMuon, RecoMuonSelectorMVABased> RecoMuonCollectionSelectorMVABased;

#include "tthAnalysis/HiggsToTauTau/interface/RecoHadTau.h"
#include "tthAnalysis/HiggsToTauTau/interface/RecoHadTauSelectorLoose.h"
#include "tthAnalysis/HiggsToTauTau/interface/RecoHadTauSelectorTight.h"
#include "tthAnalysis/HiggsToTauTau/interface/RecoHadTauSelectorFakeable.h"

typedef ParticleCollectionSelector<RecoHadTau, RecoHadTauSelectorLoose> RecoHadTauCollectionSelectorLoose;
typedef ParticleCollectionSelector<RecoHadTau, RecoHadTauSelectorTight> RecoHadTauCollectionSelectorTight;
typedef ParticleCollectionSelector<RecoHadTau, RecoHadTauSelectorFakeable> RecoHadTauCollectionSelectorFakeable;

#include "tthAnalysis/HiggsToTauTau/interface/RecoJet.h"
#include "tthAnalysis/HiggsToTauTau/interface/RecoJetSelector.h"
#include "tthAnalysis/HiggsToTauTau/interface/RecoJetSelectorBtag.h"

typedef ParticleCollectionSelector<RecoJet, RecoJetSelector> RecoJetCollectionSelector;
typedef ParticleCollectionSelector<RecoJet, RecoJetSelectorBtagLoose> RecoJetCollectionSelectorBtagLoose;
typedef ParticleCollectionSelector<RecoJet, RecoJetSelectorBtagMedium> RecoJetCollectionSelectorBtagMedium;

#endif // tthAnalysis_HiggsToTauTau_ParticleCollectionSelector_h

