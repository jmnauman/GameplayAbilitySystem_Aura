#include "Actor/MagicCircleActor.h"

#include "Components/DecalComponent.h"

AMagicCircleActor::AMagicCircleActor()
{
	PrimaryActorTick.bCanEverTick = true;
	
	DecalComponent = CreateDefaultSubobject<UDecalComponent>("MagicCircleDecal");
	DecalComponent->SetupAttachment(GetRootComponent());
}

void AMagicCircleActor::BeginPlay()
{
	Super::BeginPlay();
}

void AMagicCircleActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

