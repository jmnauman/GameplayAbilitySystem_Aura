

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MagicCircleActor.generated.h"

class UMaterialInterface;

UCLASS()
class AURA_API AMagicCircleActor : public AActor
{
	GENERATED_BODY()
	
public:	
	AMagicCircleActor();
	virtual void Tick(float DeltaTime) override;
	void SetMaterial(UMaterialInterface* Mat);

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UDecalComponent> DecalComponent;
	
	virtual void BeginPlay() override;
};
