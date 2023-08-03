#include "generator.hh"


MyPrimaryGenerator::MyPrimaryGenerator()
{
   fParticleGun = new G4ParticleGun(1);
}

MyPrimaryGenerator::~MyPrimaryGenerator()
{
   delete fParticleGun;
}

void MyPrimaryGenerator::GeneratePrimaries(G4Event *anEvent)
{
  G4ParticleTable  *particleTable = G4ParticleTable::GetParticleTable();
  G4String particleName = "mu-";
  G4ParticleDefinition *particle = particleTable->FindParticle("mu-");

  G4double size = 200.*cm;
  G4double rand_1 = ( (rand() %200) + 1) - 100.;
  G4double rand_2 = ( (rand() %200) + 1) - 100.;
  G4ThreeVector pos(-150.*cm, rand_1*cm, rand_2*cm);
  G4ThreeVector mom(1., 0., 0.);

  fParticleGun->SetParticlePosition(pos);
  fParticleGun->SetParticleMomentumDirection(mom);
  fParticleGun->SetParticleMomentum(4. *GeV);
  fParticleGun->SetParticleDefinition(particle);

  fParticleGun->GeneratePrimaryVertex(anEvent);
}
