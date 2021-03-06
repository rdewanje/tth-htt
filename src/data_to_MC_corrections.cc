#include "tthAnalysis/HiggsToTauTau/interface/data_to_MC_corrections.h"

#include "tthAnalysis/HiggsToTauTau/interface/lutAuxFunctions.h"
#include "tthAnalysis/HiggsToTauTau/interface/leptonTypes.h"

#include <assert.h> // assert

/**
 * @brief Evaluate data/MC correction for electron and muon trigger efficiency (Table 10 in AN-2015/321)
 * @param type (either kElectron or kMuon), pT and eta of both leptons
 * @return data/MC scale-factor, to be applied as event weight to simulated events
 */
double sf_triggerEff(int lepton1_type, double lepton1_pt, double lepton1_eta, int lepton2_type, double lepton2_pt, double lepton2_eta)
{
  if ( lepton1_type == kElectron && lepton2_type == kElectron ) {
    if ( std::max(lepton1_pt, lepton2_pt) > 40. ) return 0.99;
    else return 0.95;
  } else if ( lepton1_type == kMuon && lepton2_type == kMuon ) {
    return 0.98;
  } else {
    return 1.00;
  }
}

//-------------------------------------------------------------------------------
double sf_electronID_and_Iso_loose(double electron_pt, double electron_eta)
{
  // efficiency for electron to pass loose identification criteria: AN-2015/321, Fig. 10 top left
  static TH2* lut_id_loose = 0;
  if ( !lut_id_loose ) {
    edm::FileInPath fileName_id_loose("tthAnalysis/HiggsToTauTau/data/");
    std::string histogramName_id_loose = "";
    lut_id_loose = loadTH2(fileName_id_loose, histogramName_id_loose);
  }
  assert(lut_id_loose);
  double sf_id_loose = get_sf_from_TH2(lut_id_loose, electron_pt, electron_eta);
  
  // electron isolation efficiency: AN-2015/321, Fig. 10 top right
  static TH2* lut_iso = 0;
  if ( !lut_iso ) {
    edm::FileInPath fileName_iso("tthAnalysis/HiggsToTauTau/data/");
    std::string histogramName_iso = "";
    lut_iso = loadTH2(fileName_iso, histogramName_iso);
  }
  assert(lut_iso);
  double sf_iso = get_sf_from_TH2(lut_iso, electron_pt, electron_eta);

  double sf = sf_id_loose*sf_iso;
  return sf;
}

double sf_electronID_and_Iso_tight_to_loose(double electron_pt, double electron_eta)
{
  // efficiency for electron to pass tight conversion veto and missing inner hits cut: AN-2015/321, Fig. 10 bottom
  static TH2* lut_convVeto = 0;
  if ( !lut_convVeto ) {
    edm::FileInPath fileName_convVeto("tthAnalysis/HiggsToTauTau/data/");
    std::string histogramName_convVeto = "";
    lut_convVeto = loadTH2(fileName_convVeto, histogramName_convVeto);
  }
  assert(lut_convVeto);
  double sf_convVeto = get_sf_from_TH2(lut_convVeto, electron_pt, electron_eta);

  // efficiency for electron to pass tight identification criteria: AN-2015/321, Fig. 12 top left (barrel) and center (endcap)
  double sf_id_tight = 1.;
  if ( fabs(electron_eta) < 1.479 ) {
    static TH1* lut_id_tight_barrel = 0;
    if ( !lut_id_tight_barrel ) {
      edm::FileInPath fileName_id_tight_barrel("tthAnalysis/HiggsToTauTau/data/");
      std::string histogramName_id_tight_barrel = "";
      lut_id_tight_barrel = loadTH1(fileName_id_tight_barrel, histogramName_id_tight_barrel);
    }
    assert(lut_id_tight_barrel);
    sf_id_tight = get_sf_from_TH1(lut_id_tight_barrel, electron_pt);
  } else {
    static TH1* lut_id_tight_endcap = 0;
    if ( !lut_id_tight_endcap ) {
      edm::FileInPath fileName_id_tight_endcap("tthAnalysis/HiggsToTauTau/data/");
      std::string histogramName_id_tight_endcap = "";
      lut_id_tight_endcap = loadTH1(fileName_id_tight_endcap, histogramName_id_tight_endcap);
    }
    assert(lut_id_tight_endcap);
    sf_id_tight = get_sf_from_TH1(lut_id_tight_endcap, electron_pt);
  }

  double sf = sf_convVeto*sf_id_tight;
  return sf;
}

double sf_electronID_and_Iso_tight(double electron_pt, double electron_eta)
{
  double sf_loose = sf_electronID_and_Iso_loose(electron_pt, electron_eta);
  double sf_tight_to_loose = sf_electronID_and_Iso_tight_to_loose(electron_pt, electron_eta);
  return sf_loose*sf_tight_to_loose;
}
//-------------------------------------------------------------------------------

//-------------------------------------------------------------------------------
double sf_muonID_and_Iso_loose(double muon_pt, double muon_eta)
{
  // efficiency for muon to pass loose identification criteria: AN-2015/321, Fig. 11 bottom
  static TH2* lut_id_loose = 0;
  if ( !lut_id_loose ) {
    edm::FileInPath fileName_id_loose("tthAnalysis/HiggsToTauTau/data/");
    std::string histogramName_id_loose = "";
    lut_id_loose = loadTH2(fileName_id_loose, histogramName_id_loose);
  }
  assert(lut_id_loose);
  double sf_id_loose = get_sf_from_TH2(lut_id_loose, muon_pt, muon_eta);

  // muon isolation efficiency: AN-2015/321, Fig. 11 top left (barrel) and center (endcap)
  double sf_iso = 1.;
  if ( fabs(muon_eta) < 1.2 ) {
    static TH1* lut_iso_barrel = 0;
    if ( !lut_iso_barrel ) {
      edm::FileInPath fileName_iso_barrel("tthAnalysis/HiggsToTauTau/data/");
      std::string histogramName_iso_barrel = "";
      lut_iso_barrel = loadTH1(fileName_iso_barrel, histogramName_iso_barrel);
    }
    assert(lut_iso_barrel);
    sf_iso = get_sf_from_TH1(lut_iso_barrel, muon_pt);
  } else {
    static TH1* lut_iso_endcap = 0;
    if ( !lut_iso_endcap ) {
      edm::FileInPath fileName_iso_endcap("tthAnalysis/HiggsToTauTau/data/");
      std::string histogramName_iso_endcap = "";
      lut_iso_endcap = loadTH1(fileName_iso_endcap, histogramName_iso_endcap);
    }
    assert(lut_iso_endcap);
    sf_iso = get_sf_from_TH1(lut_iso_endcap, muon_pt);
  }
  
  // efficiency for muon to pass transverse impact parameter cut: AN-2015/321, Fig. 11 top right
  static TH1* lut_ip = 0;
  if ( !lut_ip ) {
    edm::FileInPath fileName_ip("tthAnalysis/HiggsToTauTau/data/");
    std::string histogramName_ip = "";
    lut_ip = loadTH2(fileName_ip, histogramName_ip);
  }
  assert(lut_ip);
  double sf_ip = get_sf_from_TH1(lut_ip, muon_eta);
  
  double sf = sf_id_loose*sf_iso*sf_ip;
  return sf;
}

double sf_muonID_and_Iso_tight_to_loose(double muon_pt, double muon_eta)
{
  // efficiency for muon to pass tight identification criteria: AN-2015/321, Fig. 13 top left (barrel) and center (endcap)
  double sf_id_tight = 1.;
  if ( fabs(muon_eta) < 1.2 ) {
    static TH1* lut_id_tight_barrel = 0;
    if ( !lut_id_tight_barrel ) {
      edm::FileInPath fileName_id_tight_barrel("tthAnalysis/HiggsToTauTau/data/");
      std::string histogramName_id_tight_barrel = "";
      lut_id_tight_barrel = loadTH1(fileName_id_tight_barrel, histogramName_id_tight_barrel);
    }
    assert(lut_id_tight_barrel);
    sf_id_tight = get_sf_from_TH1(lut_id_tight_barrel, muon_pt);
  } else {
    static TH1* lut_id_tight_endcap = 0;
    if ( !lut_id_tight_endcap ) {
      edm::FileInPath fileName_id_tight_endcap("tthAnalysis/HiggsToTauTau/data/");
      std::string histogramName_id_tight_endcap = "";
      lut_id_tight_endcap = loadTH1(fileName_id_tight_endcap, histogramName_id_tight_endcap);
    }
    assert(lut_id_tight_endcap);
    sf_id_tight = get_sf_from_TH1(lut_id_tight_endcap, muon_pt);
  }

  double sf = sf_id_tight;
  return sf;
}

double sf_muonID_and_Iso_tight(double muon_pt, double muon_eta)
{
  double sf_loose = sf_muonID_and_Iso_loose(muon_pt, muon_eta);
  double sf_tight_to_loose = sf_muonID_and_Iso_tight_to_loose(muon_pt, muon_eta);
  return sf_loose*sf_tight_to_loose;
}
//-------------------------------------------------------------------------------

//-------------------------------------------------------------------------------
double sf_leptonID_and_Iso_loose(int lepton1_type, double lepton1_pt, double lepton1_eta, int lepton2_type, double lepton2_pt, double lepton2_eta)
{
  double lepton1_sf = 1.;
  if      ( lepton1_type == kElectron ) lepton1_sf = sf_electronID_and_Iso_loose(lepton1_pt, lepton1_eta);
  else if ( lepton1_type == kMuon     ) lepton1_sf = sf_muonID_and_Iso_loose(lepton1_pt, lepton1_eta);
  else assert(0);

  double lepton2_sf = 1.;
  if      ( lepton2_type == kElectron ) lepton2_sf = sf_electronID_and_Iso_loose(lepton2_pt, lepton2_eta);
  else if ( lepton2_type == kMuon     ) lepton2_sf = sf_muonID_and_Iso_loose(lepton2_pt, lepton2_eta);
  else assert(0);

  double sf = lepton1_sf*lepton2_sf;
  return sf;
}

double sf_leptonID_and_Iso_fakeable_to_loose(int lepton1_type, double lepton1_pt, double lepton1_eta, int lepton2_type, double lepton2_pt, double lepton2_eta)
{
  return 1.;
}

double sf_leptonID_and_Iso_fakeable(int lepton1_type, double lepton1_pt, double lepton1_eta, int lepton2_type, double lepton2_pt, double lepton2_eta)
{
  double sf_loose = sf_leptonID_and_Iso_loose(lepton1_type, lepton1_pt, lepton1_eta, lepton2_type, lepton2_pt, lepton2_eta);
  double sf_fakeable_to_loose = sf_leptonID_and_Iso_fakeable_to_loose(lepton1_type, lepton1_pt, lepton1_eta, lepton2_type, lepton2_pt, lepton2_eta);
  return sf_loose*sf_fakeable_to_loose;
}

double sf_leptonID_and_Iso_tight_to_loose(int lepton1_type, double lepton1_pt, double lepton1_eta, int lepton2_type, double lepton2_pt, double lepton2_eta)
{
  double lepton1_sf = 1.;
  if      ( lepton1_type == kElectron ) lepton1_sf = sf_electronID_and_Iso_tight_to_loose(lepton1_pt, lepton1_eta);
  else if ( lepton1_type == kMuon     ) lepton1_sf = sf_muonID_and_Iso_tight_to_loose(lepton1_pt, lepton1_eta);
  else assert(0);

  double lepton2_sf = 1.;
  if      ( lepton2_type == kElectron ) lepton2_sf = sf_electronID_and_Iso_tight_to_loose(lepton2_pt, lepton2_eta);
  else if ( lepton2_type == kMuon     ) lepton2_sf = sf_muonID_and_Iso_tight_to_loose(lepton2_pt, lepton2_eta);
  else assert(0);

  double sf = lepton1_sf*lepton2_sf;
  return sf;
}

double sf_leptonID_and_Iso_tight(int lepton1_type, double lepton1_pt, double lepton1_eta, int lepton2_type, double lepton2_pt, double lepton2_eta)
{
  double sf_loose = sf_leptonID_and_Iso_loose(lepton1_type, lepton1_pt, lepton1_eta, lepton2_type, lepton2_pt, lepton2_eta);
  double sf_tight_to_loose = sf_leptonID_and_Iso_tight_to_loose(lepton1_type, lepton1_pt, lepton1_eta, lepton2_type, lepton2_pt, lepton2_eta);
  return sf_loose*sf_tight_to_loose;
}
//-------------------------------------------------------------------------------

/**
 * @brief Evaluate data/MC correction for efficiencies of single electron and single muon triggers 
 * @param type (either kElectron or kMuon), pT and eta 
 * @return data/MC scale-factor, to be applied as event weight to simulated events
 */
double sf_triggerEff(int lepton1_type, double lepton1_pt, double lepton1_eta)
{
  if ( lepton1_type == kElectron ) {
    if ( lepton1_pt > 40. ) return 0.99;
    else return 0.95;
  } else if ( lepton1_type == kMuon ) {
    return 0.98;
  } else {
    return 1.00;
  }
}

//-------------------------------------------------------------------------------
double sf_leptonID_and_Iso_loose(int lepton1_type, double lepton1_pt, double lepton1_eta)
{
  double sf = 1.;
  if      ( lepton1_type == kElectron ) sf = sf_electronID_and_Iso_loose(lepton1_pt, lepton1_eta);
  else if ( lepton1_type == kMuon     ) sf = sf_muonID_and_Iso_loose(lepton1_pt, lepton1_eta);
  else assert(0);
  return sf;
}

double sf_leptonID_and_Iso_fakeable(int lepton1_type, double lepton1_pt, double lepton1_eta)
{
  double sf_loose = sf_leptonID_and_Iso_loose(lepton1_type, lepton1_pt, lepton1_eta);
  double sf_fakeable_to_loose = sf_leptonID_and_Iso_fakeable_to_loose(lepton1_type, lepton1_pt, lepton1_eta);
  return sf_loose*sf_fakeable_to_loose;
}

double sf_leptonID_and_Iso_fakeable_to_loose(int lepton1_type, double lepton1_pt, double lepton1_eta)
{
  return 1.;
}

double sf_leptonID_and_Iso_tight(int lepton1_type, double lepton1_pt, double lepton1_eta)
{
  double sf_loose = sf_leptonID_and_Iso_loose(lepton1_type, lepton1_pt, lepton1_eta);
  double sf_tight_to_loose = sf_leptonID_and_Iso_tight_to_loose(lepton1_type, lepton1_pt, lepton1_eta);
  return sf_loose*sf_tight_to_loose;
}

double sf_leptonID_and_Iso_tight_to_loose(int lepton1_type, double lepton1_pt, double lepton1_eta)
{
  double sf = 1.;
  if      ( lepton1_type == kElectron ) sf = sf_electronID_and_Iso_tight_to_loose(lepton1_pt, lepton1_eta);
  else if ( lepton1_type == kMuon     ) sf = sf_muonID_and_Iso_tight_to_loose(lepton1_pt, lepton1_eta);
  else assert(0);
  return sf;
}
//-------------------------------------------------------------------------------
