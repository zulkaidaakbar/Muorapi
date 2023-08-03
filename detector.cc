#include "detector.hh"

MySensitiveDetector::MySensitiveDetector(G4String name) : G4VSensitiveDetector(name)
{}

MySensitiveDetector::~MySensitiveDetector()
{}

G4bool MySensitiveDetector::ProcessHits(G4Step *aStep, G4TouchableHistory *ROhist)
{
  G4Track *track = aStep->GetTrack();
  //track->SetTrackStatus(fStopAndKill);
  G4StepPoint *preStepPoint = aStep->GetPreStepPoint();
  G4StepPoint *postStepPoint = aStep->GetPostStepPoint();

  G4ThreeVector posMuon = preStepPoint->GetPosition();
  //G4cout << "Muon Position: " << posMuon << G4endl;
  const G4VTouchable *touchable = aStep->GetPreStepPoint()->GetTouchable();
  G4int copyNo = touchable->GetCopyNumber();
  //G4cout << "Copy number: " << copyNo << G4endl;

  G4VPhysicalVolume *physVol = touchable->GetVolume();
  G4ThreeVector posDetector = physVol->GetTranslation();

  //G4cout << "Detector position" << posDetector << G4endl;
  G4int evt = G4RunManager::GetRunManager()->GetCurrentEvent()->GetEventID();
 
  G4AnalysisManager *man = G4AnalysisManager::Instance();
  man->FillNtupleIColumn(0, evt);
  man->FillNtupleDColumn(1, posMuon[0]);
  man->FillNtupleDColumn(2, posMuon[1]);
  man->FillNtupleDColumn(3, posMuon[2]);
  man->FillNtupleIColumn(4, copyNo);
  man->AddNtupleRow(0);
}
