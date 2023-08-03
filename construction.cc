#include "construction.hh"

MyDetectorConstruction::MyDetectorConstruction()
{}

MyDetectorConstruction::~MyDetectorConstruction()
{}

G4VPhysicalVolume *MyDetectorConstruction::Construct()
{
  G4NistManager *nist = G4NistManager::Instance();
  G4Material *worldMat = nist->FindOrBuildMaterial("G4_AIR");
  
  G4Box *solidWorld = new G4Box("solidWorld", 2*m , 2*m, 2*m);
  G4LogicalVolume *logicWorld = new G4LogicalVolume(solidWorld, worldMat, "logicWorld");
  G4VPhysicalVolume *physWorld = new G4PVPlacement(0, G4ThreeVector(0.,0.,0.), logicWorld, "physWorld", 0, false, 0, true );

  G4Element *Fe = nist->FindOrBuildElement("Fe");
  G4Material *Pipe = new G4Material("Pipe",7.874*g/cm3,1 );
  Pipe->AddElement(Fe, 100.*perCent);

  G4Tubs *solidPipe = new G4Tubs("solidPipe", 10.*cm, 40.*cm, 50.*cm, 0.*deg, 360.*deg);
  G4LogicalVolume *logicPipe = new G4LogicalVolume(solidPipe, Pipe, "logicPipe");
  G4VPhysicalVolume *physPipe = new G4PVPlacement(0, G4ThreeVector(0., 0., 0.), logicPipe, "physPipe", logicWorld, false, 0, true ) ;

  G4Material* scintillator = nist->FindOrBuildMaterial("G4_PLASTIC_SC_VINYLTOLUENE");
  G4Material* ScintMat = scintillator;

  G4Box *solidDetector = new G4Box("solidDetector", 0.01*m , 1*m, 1*m);
  logicDetector = new G4LogicalVolume(solidDetector, worldMat, "logicDetector");
  /*for(G4int i=0; i<2; i++)
   {
    G4VPhysicalVolume *physDetector = new G4PVPlacement(0, G4ThreeVector( (90+i*20)*cm, 0.,0.), logicDetector, "physDetector", logicWorld,false, i,true);
   }

  for(G4int i=0; i<2; i++)
   {
    G4VPhysicalVolume *physDetector = new G4PVPlacement(0, G4ThreeVector( (-90-i*20)*cm, 0.,0.), logicDetector, "physDetector", logicWorld,false, i,true);
   }*/

   for(G4int i=0; i<4; i++)
   {
    if (i<2) 
     {
      G4VPhysicalVolume *physDetector = new G4PVPlacement(0, G4ThreeVector( (90+i*20)*cm, 0.,0.), logicDetector, "physDetector", logicWorld,false, i,true);      
     }
   if (i>=2 && i<4)
     {
      G4VPhysicalVolume *physDetector = new G4PVPlacement(0, G4ThreeVector( (-90-(i-2)*20)*cm, 0.,0.), logicDetector, "physDetector", logicWorld,false, i,true);
     } 
   }

  //G4VPhysicalVolume *physDetector = new G4PVPlacement(0, G4ThreeVector(0., 0., 110*cm), logicDetector, "physDetector", logicWorld,false, 1,true);
  //logicScint = new G4LogicalVolume(PlastScint, ScintMat, "PlasticScintillator");

  return physWorld;
}


void MyDetectorConstruction::ConstructSDandField()
{
  MySensitiveDetector *sensDet = new MySensitiveDetector("SensitiveDetector");
  logicDetector->SetSensitiveDetector(sensDet);
}
